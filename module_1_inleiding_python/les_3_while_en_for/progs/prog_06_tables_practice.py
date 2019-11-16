'''
Requirements:
- The program asks for the first 10 products of the first 10 multiplication tables in the natural order
- It does so by going through multiple rounds of questions
- Whenever a particular question, e.g. 3 x 4 has been answert correctly for 3 consecutive times, it isn't asked again
- When there are no questions left to ask, the program terminates

Test specification:
- Temporarily set both the nr of tables and the nr of lines per table to 3
- In the second round, answer all questions correctly, except 2 x 2 and 1 x 3
- Keep on answering correctly until only the questions 2 x 2 and 1 x 3 remain
- Answer 2 x 2 correctly, but answer 1 x 3 wrongly
- Keep answering 1 x 3 correctly (should be for 3 times) until the program terminates
- Restore both the nr of tables and the nr of lines to 10

Design:
- As a scoreboard, use a list of lists (one sub-list per table) to hold the nr of successiver right answers for all tables
- If a question is ansered correctly the score is incremented by 1, else it is reset to 0
- Before asking a question, check the scoreboard if it already has been answered correctly for three consecutive times
- In each round, remember if any question has been asked at all, if not the program terminates
'''

nrOfTables = 10
nrOfLines = 10
  
scoreboard = [[0 for lineIndex in range (10)] for tableIndex in range (10)]
requiredScore = 3

while True:
    questionAsked = False
    for tableIndex in range (nrOfTables):
        tableNr = tableIndex + 1
        for lineIndex in range (nrOfLines):
            lineNr = lineIndex + 1
            if scoreboard [tableIndex][lineIndex] < requiredScore:
                answer = int (input (f'Hoeveel is {lineNr} x {tableNr}? '))
                questionAsked = True
                if answer == lineNr * tableNr:
                    scoreboard [tableIndex][lineIndex] += 1
                else:
                    print (f'Niet goed, {lineNr} x {tableNr} = {lineNr * tableNr}!')
                    scoreboard [tableIndex][lineIndex] = 0
        print ()
    if not questionAsked:
        break;
