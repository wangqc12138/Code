#coding:utf-8 -*-
import configparser
import xlwt
import os
import chardet
import codecs
row = 0
wk=xlwt.Workbook()
sheet1 = wk.add_sheet("数据", cell_overwrite_ok=True)
def get_cfgName(dir):
    global wk
    for root,dirs,files in os.walk(dir):
        for file in files:
            get_config(root+'/'+file)
    wk.save("result.xls")

def get_config(config_file = "xfer.cfg"):
        
    #定义读取配置文件函数，分别读取各个分栏的配置参数，包含ints、floats、strings
    print(config_file)
    f = open(config_file,'rb')
    data = f.read()
    encoding = chardet.detect(data)
    print(encoding)
    config = configparser.RawConfigParser()
    # config.readfp(codecs.open(config_file, "r", "utf-8-sig"))
    if encoding["encoding"] == 'utf-8' :
        config.read(config_file,encoding="utf-8")
    else:
        config.read(config_file,encoding="gbk") #读取文件

    dHost = config.get("Default","Host")
    dUser = config.get("Default","User")
    dPasswd = config.get("Default","Passwd")
    r = config.sections()
    global row,sheet1
    for a in r:
        if config.has_option(a,"srcdir") == False:
            continue
        col = 0
        sheet1.write(row , col, a)
        col+=1
        t = config.items(a)
        if config.has_option(a,"Host") and config.get(a,"Host") != "":
            tHost = config.get(a,"Host")
        else:
            tHost = dHost
        sheet1.write(row , col, tHost)
        col+=1
        if config.has_option(a,"User") and config.get(a,"User") != "":
            tUser = config.get(a,"User")
        else:
            tUser = dUser
        sheet1.write(row , col, tUser)
        col+=1
        if config.has_option(a,"Passwd") and config.get(a,"Passwd") != "":
            tPasswd = config.get(a,"Passwd")
        else:
            tPasswd = dPasswd
        sheet1.write(row , col, tPasswd)
        col+=1
        if config.has_option(a,"BackupDest") and config.get(a,"BackupDest") == "T":
            tDestBakDir = config.get(a,"DestBakDir")
        row+=1
        # for key,value in t:
        #     print (key, ': ', value)
    
    r = config.options("Common")
    r = config.get("Common","classname")
    r = config.items("Default") 
    r = config.has_option("Common","srcdir")

get_cfgName("/home/wangqc/wangqichao/cfg/92")
# get_config("/home/wangqc/wangqichao/cfg/92/xfer_wlw_scp_volte.cfg")

#输出kkk的值为：{'xiaoming': 1, 'xiaofang': 2, 'xiaohong': 3, 'ming111': 99.0, 'fang222': 98.0, 'hong333': 97.0, 'ming': 'java', 'fang': 'python', 'hong': 'C'}
