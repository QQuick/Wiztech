class Lookup:
    '''Utility class to look up an item by its abbreviated name'''
    def __init__ (self, fileName):
        self.parser = Parser (fileName)
        self.name = self.parser.tree [0][0][0]
        
    def get (self, key):
        for item in self.items:
            if item.name.startswith (key):
                return item
        raise Exception (f'No item of class {self.__class__.__name__} starts with {key}')
        
class Parser:
    '''Syntax analyser for blocked textfiles'''
    def __init__ (self, fileName):
        with open (fileName) as file:
            self.tree = [[[
                            symbol.strip ()
                        for symbol in line.split ('  ') if symbol
                    ] for line in block.split ('\n') if line
                ] for block in file.read () .split ('\n\n') if block
            ]       
