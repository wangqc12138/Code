import openpyxl
import os


wb = openpyxl.load_workbook('./test.xlsx')
sheet = wb['采集中心-cosmic']
f = open('./src.txt','r',encoding='utf-8')
row = 2
col = 9
for line in f:
    for i in range(1,104):
        sheet.cell(row,col).value+=","+line.strip()+"业务标志"
        row+=1
wb.save('result.xlsx')
