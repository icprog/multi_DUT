# -*- coding:utf8 -*-

'''
list the file path file
'''

import sys
import os

import listTheFile
import compareString

PATH_1 = r'C:\Users\Administrator\Desktop\Multi_DUT\Multi-DUT\Multi-DUT\Multi-DUT_codes\WNDR4500&WNDR3400v3\TestPerf\code'
PATH_2 = r'E:\Program\Github\multi_DUT\multi_DUT_Codes\R6300\TestPerf_R6300\code'

if __name__ == '__main__':
    if len(sys.argv) < 2 :
        result_1 = listTheFile.ListFilesToTxt(PATH_1)
        result_2 = listTheFile.ListFilesToTxt(PATH_2)
    else:
        result_1 = listTheFile.ListFilesToTxt(sys.argv[1])
        result_2 = listTheFile.ListFilesToTxt(sys.argv[2])

    compareString.compareString(result_1, result_2)
