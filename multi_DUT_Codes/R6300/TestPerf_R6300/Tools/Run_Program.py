# -*- coding: utf-8 -*-

from Tkinter import *
import os
import traceback
import sys
import time

SCRIPT_PATH = os.path.dirname(os.path.abspath(__file__))

def Button_Demo(root):    
    '''
    function of creat label and button
    '''      
    #Run_Program
    Run_Program_Button = Button(root)  
    Run_Program_Button['text'] = "Run_Program"
    Run_Program_Button['command'] = Run_Program  
    Run_Program_Button.pack()	
  
def Run_Program():
    filename = SCRIPT_PATH + "\\Metertest.exe"
    os.system(filename)
    time.sleep(2)
    f = open('c:\\Meterlog.txt', 'rb')
    data = f.read()
    filename = SCRIPT_PATH + "\\Meterlog.txt"
    writeFile(filename, data + '\n')
    f.close()

def writeFile(e, w):
    try:
        f = open(e, 'a+')
        f.write(w)
        f.flush()
        f.close()
    except:
        traceback.print_exc()
	
def main():
    root = Tk()
    Button_Demo(root)
    root.mainloop()
 
   
if __name__ == "__main__":
    main()