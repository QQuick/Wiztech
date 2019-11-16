granniesEuros = 100;

honestBillBankBalance = granniesEuros
trickyDickBankBalance = granniesEuros

year = 1

print ()
print (' YR |  HBBB  |  TDBB')
print (' ===|========|========')

while honestBillBankBalance <= trickyDickBankBalance:
    honestBillBankBalance *= 1.05
    trickyDickBankBalance += 10
    print (f' {year:2d} | {honestBillBankBalance:6.2f} | {trickyDickBankBalance:6.2f}')
    year += 1
    
print ()
