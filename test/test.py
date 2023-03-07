from collections import defaultdict
from ftplib import FTP
import ctypes
import os


def ftpcheck(host="", port=21, user="", passwd="", dir="", matchruler=""):
    ftp = FTP()
    ftp.connect(host=host, port=port, timeout=120)
    ftp.login(user=user, passwd=passwd)
    res = []
    ftp.dir(dir+"/"+matchruler+"*", res.append)
    index = 0
    for line in res:
        if line[0] != 'd':
            index += 1
    data = host+"|"+dir+"|"+matchruler+"|"+str(index)+"\n"
    # file = open(log)
    # file.write(data)
    print(data)
    return data


def test():
    str = "xferPasswd kt4"
    passwd = os.popen(str)
    print(passwd)
    print(type(passwd))
    passwd.readlines()
    for line in passwd:
        print(line)
    # temp = os.popen(["xferPasswd -d ", passwd])
    # print(temp)


# def save2db(data = ""):
#     return
if __name__ == '__main__':
    # data = ftpcheck("10.10.10.183", 21, "wangqc", "wangqichao",
    #                 "/data03/ktgrp/wangqc/dest", "111")
    # save2db(data)
    test()
