import openpyxl
import os


wb = openpyxl.load_workbook('./test.xlsx')
sheet = wb['Sheet1']
f = open('./src.txt','r',encoding='utf-8')
row = 2
col = 1
for line in f:
    print(line.strip())
    for i in range(1,3):
        sheet.cell(row,col).value+=line.strip()
        row+=1
wb.save('result.xlsx')
