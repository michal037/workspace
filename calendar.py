import calendar

year = int(input())

for i in range(12):
	print(calendar.month(year, i + 1))
