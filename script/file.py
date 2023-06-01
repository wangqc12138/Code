import os


def openfile(d):
    if os.path.exists(d):
        return
    for root, dirs, files in os.walk(d):
        for file in files:
            # print(file)
            if file.find("cpp") != -1 or file.find(".h") != -1:
                # deal(d+"/"+file)
                print(d+"/"+file)
        for dir in dirs:
            openfile(d+"/"+dir)


def deal(file):
    if os.path.exists(file)
    for line in open(file):
        if line.find("char") != -1:
            if line.find("host") != -1 or line.find("ip") != -1:
                print(line)


openfile("/data01/xfer_mix_v8/ob_src/xfer_mix")
