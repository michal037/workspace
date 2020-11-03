from math import log10, floor

print('https://www.quora.com/Is-there-a-trick-to-find-how-many-digits-a-certain-exponent-will-yield')
print()
print('base  - liczba podstawy')
print('n     - potega w wzorze')
print('GB    - ilosc miejsca na dysku dla zapisanej liczby jako tekst ASCII w GB')
print('ilosc - ilosc liczb dla wyniku:  base ^ (2 * (2 ^ n))')
print()

for base in range(2, 11):
	print('base:', base)

	for n in range(0, 65):
		wynik = floor(2 * (2 ** n) * log10(base)) + 1
		ile_gb = wynik / (1024 ** 3)
		
		print(f'n: {n:>2}; GB: {ile_gb:>16.4f}; ilosc: {wynik:>20}')

	print('\n')
