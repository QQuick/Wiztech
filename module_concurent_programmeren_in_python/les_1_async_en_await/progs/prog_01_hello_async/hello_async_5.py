import time as tm
import asyncio as ai

async def sayAfter (delay, what):
    await ai.sleep (delay)
    print (tm.strftime ('%X'), what)

async def main ():
    print ()
    print (tm.strftime ('%X'), 'Begin programma')
    
    task1 = ai.create_task (sayAfter (1, 'Hallo'))
    task2 = ai.create_task (sayAfter (2, 'Wereld'))
    print (tm.strftime ('%X'), 'Tasks started')

    await task2     # Will wait 2 s
    await task1     # Will wait 0 s additionally
    
    print (tm.strftime ('%X'), 'Einde programma')
    print ()

ai.run (main ())
  
