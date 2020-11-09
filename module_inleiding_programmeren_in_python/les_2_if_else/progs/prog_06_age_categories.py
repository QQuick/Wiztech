age = int (input ('Hoe oud ben je? '))

if age < 6:
    print (f'Ben je inderdaad pas {age}? Best knap dat je dit al kunt lezen dan!')
elif age < 13:
    print (f'Als je {age} bent, zit je waarschijnlijk nog op de basisschool...')
elif age < 18:
    print (f'Jammer, {age} is te jong voor de sigarenrokers-vereniging.')
else:
    print (f'Jammer, {age} is te oud voor een fopspeen.')
    