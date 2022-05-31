import shutil
import os
import chardet
import configparser
import xml.etree.ElementTree as ET

def deal(dirname = ""):
    for root,dirs,files in os.walk(dir):
        for file in files:
            dealfile(root,file)

def dealfile(dir = "", file = ""):
    config_file = dir + "/" + file
    print(config_file)
    L = file.split('.')
    src = "./"
    dest = "/home/wangqc/python/92/92xml"+L[0]+".xml"
    shutil.copy(src,dest)

    config = configparser.RawConfigParser()
    encoding = chardet.detect(open(config_file,'rb').read())
    if encoding["encoding"] == 'utf-8' :
        config.read(config_file,encoding = "utf-8")
    else:
        config.read(config_file,encoding = 'gbk') 
    
