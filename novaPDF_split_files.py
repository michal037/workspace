import csv

# config - file names
input_csv_filename  = 'AllTranslationsND_pl.csv'
output_csv_filename = 'tmp_AllTranslationsND_pl.csv'
output_txt_filename = 'strings.txt'

# open files
input_csv  = open(input_csv_filename,  'r', newline='\r\n', encoding='utf-8')
output_csv = open(output_csv_filename, 'w', newline='',     encoding='utf-8')
output_txt = open(output_txt_filename, 'w', newline='\r\n', encoding='utf-8')

# create csv reader and writer
input_csv_reader  = csv.reader(input_csv,  delimiter=',', quotechar='\"')
output_csv_writer = csv.writer(output_csv, delimiter=',', quotechar='\"')

# write txt file
for row in input_csv_reader:
	output_txt.write(row[6] + '\n')

# write csv file
input_csv.seek(0)
for row in input_csv_reader:
	del row[6]
	output_csv_writer.writerow(row)

# close files
output_txt.close()
output_csv.close()
input_csv .close()
