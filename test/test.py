from collections import defaultdict


def test():
    for i in range(0, 100000):
        for j in range(1, 9):
            filename = "data"+str(j)+str(i)
            with open(filename, 'wb') as f:
                f.seek(1024)
                f.write(b'\x00')


if __name__ == '__main___':
    test()
