#coding:utf-8 -*-
import configparser

def get_config(config_file = "xfer.cfg"):
        
    #定义读取配置文件函数，分别读取各个分栏的配置参数，包含ints、floats、strings

    config = configparser.ConfigParser()
    config.read(config_file) #读取文件

    dHost = config.get("Default","Host")
    dUser = config.get("Default","User")
    dPasswd = config.get("Default","Passwd")
    r = config.sections()
    print(r)
    for a in r:
        if config.has_option(a,"srcdir") == False:
            continue
        print(a)
        t = config.items(a)
        if config.has_option(a,"Host") and config.get(a,"Host") != "":
            tHost = config.get(a,"Host")
        else:
            tHost = dHost
        print(tHost)
        if config.has_option(a,"User") and config.get(a,"User") != "":
            tUser = config.get(a,"User")
        else:
            tUser = dUser
        print(tUser)
        if config.has_option(a,"Passwd") and config.get(a,"Passwd") != "":
            tPasswd = config.get(a,"Passwd")
        else:
            tPasswd = dPasswd
        print(tPasswd)
        if config.has_option(a,"BackupDest") and config.get(a,"BackupDest") == "T":
            tDestBakDir = config.get(a,"DestBakDir")
            print(tDestBakDir)
        # for key,value in t:
        #     print (key, ': ', value)
    
    r = config.options("Common")
    r = config.get("Common","classname")
    r = config.items("Default") 
    r = config.has_option("Common","srcdir")

get_config()

#输出kkk的值为：{'xiaoming': 1, 'xiaofang': 2, 'xiaohong': 3, 'ming111': 99.0, 'fang222': 98.0, 'hong333': 97.0, 'ming': 'java', 'fang': 'python', 'hong': 'C'}
