import time as tm
import asyncio as ai

async def sayAfter (delay, what):
    await ai.sleep (delay)
    print (tm.strftime ('%X'), what)

async def main ():
    print ()
    print (tm.strftime ('%X'), 'Begin programma')
    
    coroutineObject1 = sayAfter (1, 'Hallo')
    coroutineObject2 = sayAfter (2, 'Wereld')
    print (tm.strftime ('%X'), 'Coroutine objecten gecreerd')
    
    await ai.sleep (3)
    print (tm.strftime ('%X'), 'Coroutine objecten geactiveerd')
    
    await coroutineObject1
    await coroutineObject2

    print (tm.strftime ('%X'), 'Einde programma')
    print ()

coroutineObject3 = main ()
ai.run (coroutineObject3)
