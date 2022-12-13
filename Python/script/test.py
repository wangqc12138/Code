import os
import string
import openpyxl


def help(src, tar: string) -> bool:
    # f = os.open(str,'r')
    # for line in f:
    ex = openpyxl.load_workbook(src)
    sh = ex['Sheet1']
    map = dict()
    for i in range(1, sh.max_column+1):
        if "/data" in sh.cell(row=1, column=i):
            map[sh.cell(row=2, column=i)] = sh.cell(row=1, column=i)
    ex = openpyxl.load_workbook(tar)
    sh1 = ex['Sheet1']
    sh2 = ex['Sheet2']
    t = 1
    for dir in map.values:
        for j in range(2, 4):
            for i in range(0, sh1.max_column):
                ch = chr(i+ord('A'))
                print(f'{ch}{t}', f'{ch}{j}')
                sh2[f'{ch}{t}'].value = sh1[f'{ch}{j}'].value.replace(
                    "XXX", dir)
            t += 1
    ex.save("res.xlsx")


help("", "./test.xlsx")
