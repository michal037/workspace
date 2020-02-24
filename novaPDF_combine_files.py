import csv

# config - file names
input_txt_filename  = 'strings.txt'
input_csv_filename  = 'tmp_AllTranslationsND_pl.csv'
output_csv_filename = 'final_AllTranslationsND_pl.csv'

# open files
input_txt  = open(input_txt_filename,  'r', newline='\r\n', encoding='utf-8')
input_csv  = open(input_csv_filename,  'r', newline='\r\n', encoding='utf-8')
output_csv = open(output_csv_filename, 'w', newline='',     encoding='utf-8')

# create csv reader and writer
input_csv_reader  = csv.reader(input_csv,  delimiter=',', quotechar='\"')
output_csv_writer = csv.writer(output_csv, delimiter=',', quotechar='\"')

# count number of lines
line_count = 0
for row in input_csv_reader:
	line_count += 1

# combine files
input_csv.seek(0)
for i in range(line_count):
	row = input_csv_reader.__next__()
	row.insert(6, input_txt.readline().rstrip('\r\n '))
	output_csv_writer.writerow(row)

# close files
output_csv.close()
input_csv .close()
input_txt .close()
