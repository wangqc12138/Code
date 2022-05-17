#coding:utf-8 -*-
import configparser
import xlwt
import os
import chardet
import codecs

# Excel
wk = xlwt.Workbook()
sheet = wk.add_sheet("92", cell_overwrite_ok=True)
row = 0

#cfg
config = configparser.RawConfigParser()

def deal_(dir):
    global wk
    for root,dirs,files in os.walk(dir):
        for file in files:
            get_config(root+'/'+file)
    wk.save("result92.xls")
    print(row)

def getValue(session = "Default", option = ""):
    global config
    if config.has_section(session) == False:
        return ""
    if session == "Default" or session == "Common" or "NameSpecs" in session:
        if config.has_option(session,option):
            return config.get(session,option)
        else:
            return ""
    else:
        if config.has_option(session,option):
            return config.get(session,option)
        else:
            if config.has_option("Default",option):
                return config.get("Default",option)
            else:
                return ""

def get_config(config_file = "xfer.cfg"):
    global row,sheet,config
    print(config_file)
    # f = open(config_file,'rb')
    # data = f.read()
    encoding = chardet.detect(open(config_file,'rb').read())
    pre = row
    if encoding["encoding"] == 'utf-8' :
        config.read(config_file,encoding = "utf-8")
    else:
        config.read(config_file,encoding = 'gbk') 
    cUniCheck = getValue("Common","UniCheck")
    if cUniCheck == "":
        cUniCheck = "T"
    col = 0
    for session in config.sections():
        if "NameSpecs" in session:
            tmatch_spec = getValue(session,"match_spec")
            sheet.write(row , col, tmatch_spec)
            col+=1
            trename_spec = getValue(session,"rename_spec")
            sheet.write(row , col, trename_spec)
            col+=1
            col=0
            row+=1 
            continue
        if config.has_option(session,"srcdir") == False:
            continue
        sheet.write(row , col, config_file)
        col+=1
        sheet.write(row , col, session)
        col+=1
        tXferType = getValue(session,"XferType")
        sheet.write(row , col, tXferType)
        col+=1
        tHost = getValue(session,"Host")
        sheet.write(row , col, tHost)
        col+=1
        tPort = getValue(session,"Port")
        if tPort == "":
            tPort = "21"
        sheet.write(row , col, tPort)
        col+=1
        tUser = getValue(session,"User")
        sheet.write(row , col, tUser)
        col+=1
        tPasswd = getValue(session,"Passwd")
        sheet.write(row , col, tPasswd)
        col+=1
        tSrcDir = getValue(session,"SrcDir")
        sheet.write(row , col, tSrcDir)
        col+=1
        tSrcBakDir = ""
        flag = getValue(session,"BackupSrc")
        if flag != "" and (flag[0]== 'T' or flag[0] == 't'):
            tSrcBakDir = getValue(session,"SrcBakDir")
        sheet.write(row , col, tSrcBakDir)
        col+=1
        tDestDir = getValue(session,"DestDir")
        sheet.write(row , col, tDestDir)
        col+=1
        tDestBakDir = ""
        flag = getValue(session,"BackupDest")
        if flag != "" and (flag[0]== 'T' or flag[0] == 't'):
            tDestBakDir = getValue(session,"DestBakDir")
        sheet.write(row , col, tDestBakDir)
        col+=1
        tUsePtr = getValue(session,"UsePtr")
        if tUsePtr == "":
            tUsePtr = "F"
        sheet.write(row , col, tUsePtr)
        col+=1
        tUniCheck = getValue(session,"UniCheck")
        if tUniCheck == "":
            tUniCheck = "T"
        sheet.write(row , col, cUniCheck)
        col+=1
        tDeleteSrcFile = getValue(session,"DeleteSrcFile")
        if tDeleteSrcFile == "":
            tDeleteSrcFile = "F"
        sheet.write(row , col, tDeleteSrcFile)
        col+=1
    print(row-pre)
    config.clear()
deal_("/home/wangqc/CppPracticeCode/python/cfg/92")
#get_config()
