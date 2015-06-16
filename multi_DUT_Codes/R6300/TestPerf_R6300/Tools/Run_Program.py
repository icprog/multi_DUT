'''
This is used for run the Metertest.exe file, and recode the result to a file.
'''


# -*- coding: utf-8 -*-

from Tkinter import *
import os
import traceback
import sys
import time

'''
The current work path
'''
SCRIPT_PATH = os.path.dirname(os.path.abspath(__file__))


'''
creat a button
'''
def Button_Demo(root):    
    '''
    function of creat label and button
    '''      
    #Run_Program
    Run_Program_Button = Button(root)  
    Run_Program_Button['text'] = "Run_Program"
    Run_Program_Button['command'] = Run_Program  
    Run_Program_Button.pack()	
 
 
'''
run the Metertest.exe program and recode the log file
''' 
def Run_Program():
    filename = SCRIPT_PATH + "\\Metertest.exe"
    os.system(filename)
    time.sleep(2)
    f = open('c:\\Meterlog.txt', 'rb')
    data = f.read()
    filename = SCRIPT_PATH + "\\Meterlog.txt"
    writeFile(filename, data + '\n')
    f.close()

'''
write the data to the file
'''
def writeFile(e, w):
    try:
        f = open(e, 'a+')
        f.write(w)
        f.flush()
        f.close()
    except:
        traceback.print_exc()

'''
the main function
'''		
def main():
    root = Tk()
    Button_Demo(root)
    root.mainloop()
 
   
if __name__ == "__main__":
    main()