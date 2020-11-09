class Generator (ast.NodeVisitor):
    
    def visit_ClassDef (self, node):
        self.adaptLineNrString (node)

        if type (self.getScope () .node) == ast.Module:
            self.emit ('export var {} = '.format (self.filterId (node.name)))
            self.allOwnNames.add (node.name)
        elif type (self.getScope () .node) == ast.ClassDef:
            self.emit ('\n{}:'.format (self.filterId (node.name)))
        else:
            self.emit ('var {} ='.format (self.filterId (node.name)))

        # If it's a dataclass (must currently be last decorator)
        # Remember this fact, to later insert def __init__ into parse tree
        # Pop dataclass decorator from decorator list
        isDataClass = False
        if node.decorator_list:
            if type (node.decorator_list [-1]) == ast.Name and node.decorator_list [-1] .id == 'dataclass':
                isDataClass = True
                dataClassArgDict = dict (dataClassDefaultArgTuple)              # Use default decorator args (or rather there are no args)
                node.decorator_list.pop ()
            elif type (node.decorator_list [-1]) == ast.Call and node.decorator_list [-1] .func.id == 'dataclass':
                isDataClass = True
                dataClassArgDict = {}
                self.visit_Call (node.decorator_list.pop (), dataClassArgDict)   # Adapt dataClassArgDict to decorator args

        decoratorsUsed = 0
        if node.decorator_list:
            self.emit (' ')
            if self.allowOperatorOverloading:
                self.emit ('__call__ (')    # The decorator is called, it may be a ast.Name (paramless) of a function or the result of an ast.Call (with params)

            for decorator in node.decorator_list:
                if decoratorsUsed > 0:
                    self.emit (' (')
                self.visit (decorator)      # This can either be a ast.Name (paramless dec) or and ast.Call (dec with params)
                decoratorsUsed += 1

            if self.allowOperatorOverloading:
                self.emit (', null, ')
            else:
                self.emit (' (')

        self.emit (' __class__ (\'{}\', [', self.filterId (node.name))
        if node.bases:
            for index, expr in enumerate (node.bases):
                try:
                    self.emitComma (index)
                    self.visit (expr)
                except Exception as exception:
                    utils.enhanceException (
                        exception,
                        lineNr = self.lineNr,
                        message = '\n\tInvalid base class'
                    )
        else:
            self.emit ('object')
        self.emit ('], {{')
        self.inscope (node)

        self.indent ()
        self.emit ('\n__module__: __name__,')

        # LHS plays a role in a.o. __repr__ in a dataclass
        inlineAssigns = []      # LHS is simple name, class var assignment generates initialisation of field in object literal
        propertyAssigns = []    # LHS is simple name, RHS is property constructor call
        initAssigns = []        # Dataclass instance var assignment, these are also the params to the generated __init__

        # LHS plays no role in a.o. __repr__ in a dataclass
        delayedAssigns = []     # LHS is array element, attribute or compound destructuring target, class var assignement generates statement after class object literal

        # Assignments whose LHS name is used in __repr__, have to be in ordere encountered, so can't be computed by concatenation of <other>VarAssigns
        reprAssigns = []       # Representation consists of instance vars, class vars and properties, in the order encountered

        # Assignments whose LHS names is used in comparisons, have to be in ordere encountered, so can't be computed by concatenation of <other>VarAssigns
        # Class vars shouln't be included, as only objects of the same class can be compared
        compareAssigns = []     # Comparing is done by instance vars and properties, in the order encountered

        index = 0

        if isDataClass:
            initHoistFragmentIndex = self.fragmentIndex
            initHoistIndentLevel = self.indentLevel

        for statement in node.body:
            if self.isCommentString (statement):
                pass
            elif type (statement) in (ast.FunctionDef, ast.AsyncFunctionDef, ast.ClassDef):
                self.emitComma (index, False)
                self.visit (statement)
                index += 1

            elif type (statement) == ast.Assign:
                if len (statement.targets) == 1 and type (statement.targets [0]) == ast.Name:
                    # LHS is simply a name
                    if type (statement.value) == ast.Call and type (statement.value.func) == ast.Name and statement.value.func.id == 'property':
                        # Property construction, should be generated after the class
                        propertyAssigns.append (statement)
                    else:
                        # Simple class var assignment, can be generated in-line as initialisation field of a JavaScript object literal
                        inlineAssigns.append (statement)
                        self.emitComma (index, False)
                        self.emit ('\n{}: ', self.filterId (statement.targets [0] .id))
                        self.visit (statement.value)
                        self.adaptLineNrString (statement)
                        index += 1
                else:
                    # LHS is attribute, array element or compound destructuring target
                    # Has to be generated after the class because it requires the use of an algorithm and can't be initialisation of field of an object literal
                    # Limitation: Can't properly deal with line number in this case
                    delayedAssigns.append (statement)

            elif type (statement) == ast.AnnAssign:
                # An annotated assignment is never a destructuring assignment
                if type (statement.value) == ast.Call and type (statement.value.func) == ast.Name and statement.value.func.id == 'property':
                    # Property construction, should be generated after the class
                    propertyAssigns.append (statement)
                    if isDataClass:
                        reprAssigns.append (statement)
                        compareAssigns.append (statement)
                elif isDataClass and type (statement.annotation) == ast.Name and statement.annotation.id != 'ClassVar':
                    # Possible data class assignment
                    inlineAssigns.append (statement)    # For defaults a class var will do
                    initAssigns.append (statement)
                    reprAssigns.append (statement)
                    compareAssigns.append (statement)
                    self.emitComma (index, False)
                    self.emit ('\n{}: ', self.filterId (statement.target.id))
                    self.visit (statement.value)
                    self.adaptLineNrString (statement)
                    index += 1
                elif type (statement.target) == ast.Name:
                    try:
                        # Simple class var assignment
                        inlineAssigns.append (statement)
                        self.emitComma (index, False)
                        self.emit ('\n{}: ', self.filterId (statement.target.id))
                        self.visit (statement.value)
                        self.adaptLineNrString (statement)
                        index += 1
                    except:
                        print (traceback.format_exc ())
                else:
                    # LHS is attribute or array element, we can't use it for representation or comparison
                    delayedAssigns.append (statement)

            elif self.getPragmaFromExpr (statement):
                # It's a pragma
                self.visit (statement)
        self.dedent ()

        self.emit ('\n}}')

        if node.keywords:
            if node.keywords [0] .arg == 'metaclass':
                self.emit (', ')
                self.visit (node.keywords [0] .value)
            else:
                raise utils.Error (
                    lineNr = self.lineNr,
                    message = '\n\tUnknown keyword argument {} definition of class {}'.format (node.keywords [0] .arg, node.name)
                )

        self.emit (')')

        # Close brackets of decorator param lists
        if decoratorsUsed:
            self.emit (')' * decoratorsUsed)

        # Emit docstring attribute assignment
        if self.allowDocAttribs:
            docString = ast.get_docstring (node)
            if docString:
               self.emit (' .__setdoc__ (\'{}\')', docString.replace ('\n', '\\n '))

        # Deal with data class var assigns, a flavor of special class var assigns
        if isDataClass: # Constructor + params have to be generated, no real class vars, just syntactically
            nrOfFragmentsToJump = self.fragmentIndex - initHoistFragmentIndex
            self.fragmentIndex = initHoistFragmentIndex

            originalIndentLevel = self.indentLevel
            self.indentLevel = initHoistIndentLevel

            initArgs = [(
                (
                        initAssign.targets [0]
                    if type (initAssign) == ast.Assign else
                        initAssign.target
                ) .id,
                initAssign.value
             ) for initAssign in initAssigns]

            reprNames = [
            (
                reprAssign.targets [0]
            if type (reprAssign) == ast.Assign else
                reprAssign.target
            ) .id
            for reprAssign in reprAssigns]

            compareNames = [
            (
                    compareAssign.targets [0]
                if type (compareAssign) == ast.Assign else
                    compareAssign.target
            ) .id
            for compareAssign in compareAssigns]

            # Generate __init__
            if dataClassArgDict ['repr']:
                originalAllowKeywordArgs = self.allowKeywordArgs
                self.allowKeywordArgs = True
                self.visit (ast.FunctionDef (
                    name = '__init__',
                    args = ast.arguments (
                        args = [ast.arg (arg = 'self', annotation = None)],
                        vararg = ast.arg (arg = 'args', annotation = None),
                        kwonlyargs = [],
                        kw_defaults = [],
                        kwarg = ast.arg (arg = 'kwargs', annotation = None),
                        defaults = []
                    ),
                    body = [
                        ast.Expr (
							value = ast.Call (
								func = ast.Name (
									id = '__pragma__',
									ctx = ast.Load
                                ),
								args = [
									ast.Str (
                                        s = 'js'
                                    ),
									ast.Str (
										s = '{}'
                                    ),
									ast.Str (
										s = '''
let names = self.__initfields__.values ();
for (let arg of args) {
    self [names.next () .value] = arg;
}
for (let name of kwargs.py_keys ()) {
    self [name] = kwargs [name];
}
                                        '''.strip ()
                                    )
                                ],
								keywords = []
                            )
                        )
                    ],
                    decorator_list = [],
                    returns = None,
                    docstring = None
                ))
                self.emit (',')
                self.allowKeywordArgs = originalAllowKeywordArgs

            # Generate __repr__
            if dataClassArgDict ['repr']:
                self.visit (ast.FunctionDef (
                    name = '__repr__',
                    args = ast.arguments (
                        args = [ast.arg (arg = 'self', annotation = None)],
                        vararg = None,
                        kwonlyargs = [],
                        kw_defaults = [],
                        kwarg = None,
                        defaults = []
                    ),
                    body = [
                        ast.Expr (
							value = ast.Call (
								func = ast.Name (
									id = '__pragma__',
									ctx = ast.Load
                                ),
								args = [
									ast.Str (
                                        s = 'js'
                                    ),
									ast.Str (
										s = '{}'
                                    ),
									ast.Str (
										s = '''
let names = self.__reprfields__.values ();
let fields = [];
for (let name of names) {{
    fields.push (name + '=' + repr (self [name]));
}}
return  self.__name__ + '(' + ', '.join (fields) + ')'
                                        '''.strip ()
                                    )
                                ],
								keywords = []
                            )
                        )
                    ],
                    decorator_list = [],
                    returns = None,
                    docstring = None
                ))
                self.emit (',')

             # Generate comparators   !!! TODO: Add check that self and other are of same class
            comparatorNames = []
            if 'eq' in dataClassArgDict:
                comparatorNames += ['__eq__', '__ne__']
            if 'order' in dataClassArgDict:
                comparatorNames += ['__lt__', '__le__', '__gt__', '__ge__']
            for comparatorName in comparatorNames:
                self.visit (ast.FunctionDef (
                    name = comparatorName,
                    args = ast.arguments (
                        args = [
                            ast.arg (arg = 'self', annotation = None),
                            ast.arg (arg = 'other', annotation = None)
                        ],
                        vararg = None,
                        kwonlyargs = [],
                        kw_defaults = [],
                        kwarg = None,
                        defaults = []
                    ),
                    body = [
                        ast.Expr (
							value = ast.Call (
								func = ast.Name (
									id = '__pragma__',
									ctx = ast.Load
                                ),
								args = [
									ast.Str (
                                        s = 'js'
                                    ),
									ast.Str (
										s = '{}'
                                    ),
									ast.Str (
										s = ('''
let names = self.__comparefields__.values ();
let selfFields = [];
let otherFields = [];
for (let name of names) {
    selfFields.push (self [name]);
    otherFields.push (other [name]);
}
return list (selfFields).''' + comparatorName + '''(list (otherFields));
                                        ''').strip ()   # ... Adding is ugly, repair __pragma__
                                    )
                                ],
								keywords = []
                            )
                        )
                     ],
                    decorator_list = []
                ))
                returns = None,
                self.emit (',')

            # After inserting at init hoist location, jump forward as much as we jumped back
            # Simply going back to the original fragment index won't work, since fragments were prepended
            self.fragmentIndex += nrOfFragmentsToJump

            # And restore indent level to where we were
            self.indentLevel = originalIndentLevel

        # Deal with delayed assigns and property assigns
        # Property assigns will be pushed onto a stack
        # They will eventually be dealt with if this class isn't directly local to another class
        for assign in delayedAssigns + propertyAssigns:
            self.emit (';\n')
            self.visit (assign)

        self.mergeList.append (utils.Any (
            className = '.'.join ([scope.node.name for scope in self.getAdjacentClassScopes ()]),
            isDataClass = isDataClass,
            reprAssigns = reprAssigns,
            compareAssigns = compareAssigns,
            initAssigns = initAssigns
        ))

        self.descope () # No earlier, class vars need it

        def emitMerges ():
            def emitMerge (merge):
                # Merge dataclass fields for any class, since parents or descendants may be dataclasses
                # ??? Should __bases__ hold complete dotted classnames in case of local classes?
                if merge.isDataClass:
                    self.emit ('\nfor (let aClass of {}.__bases__) {{\n', self.filterId (merge.className))
                    self.indent ()
                    self.emit ('__mergefields__ ({}, aClass);\n', self.filterId (merge.className))
                    self.dedent ()
                    self.emit ('}}')

                    # Merge dataclass fields for current class
                    self.emit (';\n__mergefields__ ({}, {{', self.filterId (merge.className))
                    self.emit ('__reprfields__: new Set ([{}]), ', ', '.join ('\'{}\''.format (reprAssign.target.id) for reprAssign in merge.reprAssigns))
                    self.emit ('__comparefields__: new Set ([{}]), ', ', '.join ('\'{}\''.format (compareAssign.target.id) for compareAssign in merge.compareAssigns))
                    self.emit ('__initfields__: new Set ([{}])', ', '.join ('\'{}\''.format (initAssign.target.id) for initAssign in merge.initAssigns))
                    self.emit ('}})')

            for merge in self.mergeList:
                emitMerge (merge)

            self.mergeList = []

        def emitProperties ():
            def emitProperty (className, propertyName, getterName, setterName = None):
                self.emit ('\nObject.defineProperty ({}, \'{}\', '.format (className, propertyName))
                if setterName:
                    self.emit ('property.call ({0}, {0}.{1}, {0}.{2})'.format (className, getterName, setterName))
                else:
                    self.emit ('property.call ({0}, {0}.{1})'.format (className, getterName))
                self.emit (');')

            if self.propertyAccessorList:
                self.emit (';')
            while self.propertyAccessorList:
                propertyAccessor = self.propertyAccessorList.pop ()
                className = propertyAccessor.className
                functionName = propertyAccessor.functionName
                propertyName = functionName [5:]
                isGetter = functionName [:5] == '_get_'

                # Find a pair
                for propertyAccessor2 in self.propertyAccessorList:
                    className2 = propertyAccessor2.className
                    functionName2 = propertyAccessor2.functionName
                    propertyName2 = functionName2 [5:]
                    isGetter2 = functionName2 [:5] == '_get_'

                    if className == className2 and propertyName == propertyName2 and isGetter != isGetter2:
                        # Remove pair
                        self.propertyAccessorList.remove (propertyAccessor2)
                        if isGetter:
                            emitProperty (className, propertyName, functionName, functionName2)
                        else:
                            emitProperty (className, propertyName, functionName2, functionName)
                        break
                else:
                    if isGetter:
                        emitProperty (className, propertyName, functionName)
                    else:
                        raise utils.Error(
                            message='\n\tProperty setter declared without getter\n'
                        )

        if type (self.getScope ().node) != ast.ClassDef:  # Emit properties if this class isn't directly local to another class
            emitProperties ()
            emitMerges ()
