# (C) GEATEC engineering, license: Apache 2

# MRI viewer

normalizedRotationAngles = (0, 90, 180)

almostRed = (1, 0.2, 0)
almostWhite = (0.85, 1, 0.95)
almostBlue = (0.3, 0.3, 1)
axisColors = (almostRed, almostWhite, almostBlue)

# Subsoil flow simulator

tabViews = [
    modelInitPage.getView (),
    phaseBehaviourPage.getView (),
    propertyModelsPage.getView (),
    productionModelPage.getView (),
    reportGenerationPage.getView (),
    simulationParsPage.getView (),
    runConfigPage.getView ()
]

# Crypto currency trading program

invertedList = dict ((tuple (entry), index) for index, entry in enumerate (aList))

invertedDict = dict ((tuple (value), key) for key, value in aDict.items ())

# In-memory SQL emulator

self.fieldDict = {fieldName: index for index, fieldName in enumerate (fieldNames)}

# Python to JavaScript compiler

dataClassDefaultArgTuple = (['init', True], ['repr', True], ['eq', True], ['order', False], ['unsafe_hash', False], ['frozen', False])

aliases = [
    # Format: ('<Python source identifier>', '<JavaScript target identifier>')
    
                                            ('js_and', 'and'),
    ('arguments', 'py_arguments'),          ('js_arguments', 'arguments'),
    ('case', 'py_case'),
    ('clear', 'py_clear'),                  ('js_clear', 'clear'),
                                            ('js_conjugate', 'conjugate'),
    ('default', 'py_default'),
    ('del', 'py_del'),                      ('js_del', 'del'),
    ('false', 'py_false'),
                                            ('js_from', 'from'),
    ('get', 'py_get'),                      ('js_get', 'get'),
                                            ('js_global', 'global'),
    ('Infinity', 'py_Infinity'),            ('js_Infinity', 'Infinity'),
    ('is', 'py_is'),                        ('js_is', 'is'),
    ('isNaN', 'py_isNaN'),                  ('js_isNaN', 'isNaN'),
    ('iter', 'py_iter'),                    ('js_iter', 'iter'),
    ('items', 'py_items'),                  ('js_items', 'items'),
    ('keys', 'py_keys'),                    ('js_keys', 'keys'),
    ('name', 'py_name'),                    ('js_name', 'name'),
    ('NaN', 'py_NaN'),                      ('js_NaN', 'NaN'),
    ('new', 'py_new'),
    ('next', 'py_next'),                    ('js_next', 'next'),
                                            ('js_not', 'not'),
                                            ('js_or', 'or'),
    ('pop', 'py_pop'),                      ('js_pop', 'pop'),
    ('popitem', 'py_popitem'),              ('js_popitem', 'popitem'),
    ('replace', 'py_replace'),              ('js_replace', 'replace'),
    ('selector', 'py_selector'),            ('js_selector', 'selector'),
    ('sort', 'py_sort'),                    ('js_sort', 'sort'),
    ('split', 'py_split'),                  ('js_split', 'split'),
    ('switch', 'py_switch'),
    ('type', 'py_metatype'),                ('js_type', 'type'),
    ('TypeError', 'py_TypeError'),          ('js_TypeError', 'TypeError'),
    ('update', 'py_update'),                ('js_update', 'update'),
    ('values', 'py_values'),                ('js_values', 'values'),
    ('reversed', 'py_reversed'),            ('js_reversed', 'reversed'),
    ('setdefault', 'py_setdefault'),        ('js_setdefault', 'setdefault'),
                                            ('js_super', 'super'),
    ('true', 'py_true'),
    ('undefined', 'py_undefined'),          ('js_undefined', 'undefined'),
]

# Python obfuscator

skipWordSet = set (keyword.kwlist + ['__init__'] + extraPlainWordList)  # __init__ should be in, since __init__.py is special
skipWordSet.update (re.findall (identifierRegEx, content))
