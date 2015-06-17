# -*- coding:utf8 -*-

'''
list the file path file
'''

import sys
import os

def ListFilesToTxt(dir1,file1):
    for filename in os.listdir(dir1):
        file1.write(filename + "\n")

def Test():
    dir1 = r"C:\Windows"
    outfile = r"c:\result.txt"    
   
    file1 = open(outfile,"w")
    if not file1:
        print ("cannot open the file %s for writing" % outfile)
    ListFilesToTxt(dir1,file1)
   
    file1.close()


Test()


