import time as tm
import asyncio as ai

async def sayAfter (delay, what):
    await ai.sleep (delay)
    print (tm.strftime ('%X'), what)

async def main ():
    print ()
    print (tm.strftime ('%X'), 'Begin programma')
    
    await sayAfter (1, 'Hallo')
    await sayAfter (2, 'Wereld')

    print (tm.strftime ('%X'), 'Einde programma')
    print ()

ai.run (main ())
