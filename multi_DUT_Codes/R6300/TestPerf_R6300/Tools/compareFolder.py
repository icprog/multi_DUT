# -*- coding:utf8 -*-

'''
list the file path file
'''

import sys
import os

import listTheFile
import compareString

result_1 = listTheFile.ListFilesToTxt(r'c:\users')
result_2 = listTheFile.ListFilesToTxt(r'c:\FFOutput')

compareString.compareString(result_1, result_2)
