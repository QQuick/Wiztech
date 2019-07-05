import random as rd

test = False

if test
    tableNrs = range (2, 5)
    questionNrs = range (2, 5)
    requiredNrOfSuccessiveRightAnswers = 2
else:
    tableNrs = range (1, 11)
    questionNrs = range (1, 11)
    requiredNrOfSuccessiveRightAnswers = 3

class Question:
    def __init__ (self, table, lineNr):
        self.table = table
        self.lineNr = lineNr
        self.nrOfSuccessiveRightAnswers = 0
        
    def ask (self):
        if int (input (f'{self.lineNr} x {self.table.tableNr} = ')) == self.table.tableNr * self.lineNr:
            self.nrOfSuccessiveRightAnswers += 1
            if self.nrOfSuccessiveRightAnswers >= requiredNrOfSuccessiveRightAnswers:
                self.table.questions.remove (self)
        else:
            self.nrOfSuccessiveRightAnswers = 0
            print (f'Helaas, niet goed, {self.lineNr} x {self.table.tableNr} = {self.table.tableNr * self.lineNr}')

class Table:
    def __init__ (self, session, tableNr):
        self.session = session
        self.tableNr = tableNr
        self.questions = [Question (self, questionNr) for questionNr in questionNrs]
        
    def practice (self):
        rd.choice (self.questions) .ask ()
        if not len (self.questions):
            self.session.tables.remove (self)
            print (f'De tafel van {self.tableNr} is klaar, prima!')

class Session:
    def __init__ (self):
        self.tables = [Table (self, tableNr) for tableNr in tableNrs]
        self.perform ()
        
    def perform (self):
        while self.tables:
            rd.choice (self.tables) .practice ()           
        print ('Alle tafels zijn klaar, gefeliciteerd!')
        
Session ()
