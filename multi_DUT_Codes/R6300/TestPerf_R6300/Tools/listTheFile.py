# -*- coding:utf8 -*-

'''
list the file path file
'''

import sys
import os
import traceback

OUTFILE = r"c:\result.txt" 

def ListFilesToTxt(dir1):
    result = list()
    for filename in os.listdir(dir1):
        writeFile(OUTFILE, filename)
        result.append(filename)
    return result

def Test():
    dir1 = r"C:\Windows"
    result = ListFilesToTxt(dir1)
    #print(result)
 
def writeFile(f, d):
    try:
        f = open(f, 'w')
        f.write(d)
        if '\n' not in d:
            f.write('\n')
        f.flush()
        f.close()
    except:
        traceback.print_exc()
        



