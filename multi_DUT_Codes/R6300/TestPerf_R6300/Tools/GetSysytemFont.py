# -*- coding: utf-8 -*-


'''
----------------------------------------------------------------------
pixel Chinese font library generator for embed system
function : this program is to genreate chinese char library for embed system
 in encoding with gb2312 ,gbk, or Big5, in any font type user like and system have.   
 it can also generate Ascii librarys, the char height and width is allways 2:1 
version : 0.1
author :zfh1005
start date :20150706
license: GPL3

----------------------------------------------------------------------
Notice:
for gb2312 chars start form 0xB0A1 ths chars form 0xA0A1 to 0xAFFE is not included 
for gbk,and big5, there are so many while holes start form  0xa1,thought they didn't
 mean any chars, it was also fill with empty 0x00, so as to keep the library linear
----------------------------------------------------------------------   
'''

import wx
import binascii

ID_ENCODE=wx.NewId()
ID_FONT=wx.NewId()
ID_HEIGHT=wx.NewId()
ID_WEIGHT=wx.NewId()
ID_ENCODE=wx.NewId()
class MyFrame(wx.Frame):
    """
    This is the main frame of program
    """
    def __init__(self, parent, title):
        wx.Frame.__init__(self, parent, -1, title,
                          pos = (150, 150), size = (400, 250))
        #global self.dc,self.screen
        self.charheight = 16
        self.charwidth = 8
        self.specwidth = 16

        
        self.chrlist = []
        self.chrpixellist = []
        self.fontName = "System"
        self.encode = "ASCII"
        self.height = 16
        self.weight = wx.NORMAL
        self.font = wx.Font(self.height*0.75, wx.SWISS , wx.NORMAL, self.weight, faceName=self.fontName)
        
        self.buffer = wx.EmptyBitmap(320,240)
        self.dc = wx.BufferedDC(None,self.buffer)#wx.Size(300,200))
        self.dc.SetPen(wx.Pen("WHITE", 1))
        self.dc.SetBackground(wx.Brush((0,0,0,255),wx.SOLID))
        self.dc.SetTextBackground((255,255,255,255))
        self.dc.SetTextForeground((255,255,255,255))
        #self.dc.SetFont(wx.Font(16, wx.SWISS , wx.NORMAL, wx.NORMAL))
        self.dc.SetFont(self.font ) 
        
        # Create the selection bar
        panel1 = wx.Panel(self, -1)
        self.encodeChoise = wx.Choice(panel1, ID_ENCODE,choices=["ASCII","GB2312","GBK","BIG5"])
        self.encodeChoise.Select(0)
        fontEnu = wx.FontEnumerator()
        fontEnu.EnumerateFacenames(encoding = wx.FONTENCODING_CP936|wx.FONTENCODING_GB2312|wx.FONTENCODING_BIG5 ,fixedWidthOnly = True)
        #print(fontEnu.GetFacenames()        )
        self.fontChoise = wx.Choice(panel1,ID_FONT,choices = list(fontEnu.GetFacenames()) )
        self.fontChoise.Select(0)
        #print(self.fontChoise.GetStringSelection())
        self.weightChoise = wx.Choice(panel1, ID_WEIGHT,choices = ["Normal","Light","Bold"])
        self.weightChoise.Select(0)
        self.heightChoise = wx.Choice(panel1,ID_HEIGHT,choices = [str(i) for i in range(8,33)])
        self.heightChoise.Select(8)
        #print(self.heightChoise.GetStringSelection())
        goBtn = wx.Button(panel1,wx.ID_APPLY,"Go")
        sizer = wx.BoxSizer(wx.HORIZONTAL)
        sizer.Add(self.encodeChoise, 0, wx.ALL|wx.ALIGN_LEFT, 1)
        sizer.Add(self.fontChoise, 1, wx.ALL|wx.ALIGN_LEFT, 1)
        sizer.Add(self.weightChoise,0,wx.ALL|wx.ALIGN_LEFT, 1)
        sizer.Add(self.heightChoise, 0, wx.EXPAND |wx.ALL|wx.ALIGN_LEFT, 1)
        sizer.Add(goBtn, 0, wx.ALL|wx.ALIGN_LEFT, 1)
        sizer.Layout()
        panel1.SetSizer(sizer)
               
        panel2 = wx.Panel(self,-1)
        self.showtext = wx.StaticText(panel2,-1,"梦回唐朝 The quick brown fox jump over the lazy dog.")
        self.showExample()
        #self.showtext.SetFont(wx.Font(24, \
        #    wx.SWISS , wx.NORMAL, wx.NORMAL, faceName=self.fontChoise.GetStringSelection()))
        p2sizer = wx.BoxSizer(wx.HORIZONTAL)
        p2sizer.Add(self.showtext, 1, wx.EXPAND |wx.ALL|wx.ALIGN_LEFT, 0) 
        p2sizer.Layout() 
        panel2.SetSizer(p2sizer) 
        #
        vsizer = wx.BoxSizer(wx.VERTICAL)
        vsizer.Add(panel1,0,wx.EXPAND|wx.TOP,0)
        vsizer.Add(panel2,1,wx.EXPAND|wx.TOP,0)        
        self.SetSizer(vsizer)
        self.SetAutoLayout(True)
        
        # bind the menu event to an event handler
        self.Bind(wx.EVT_CHOICE, self.OnSetEncode, id=ID_ENCODE)
        self.Bind(wx.EVT_CHOICE,self.OnSetFont,id=ID_FONT)
        self.Bind(wx.EVT_CHOICE,self.OnSetWeight,id=ID_WEIGHT)
        self.Bind(wx.EVT_CHOICE,self.OnSetSize,id=ID_HEIGHT)
        self.Bind(wx.EVT_BUTTON,self.OnDo,id=wx.ID_APPLY)
        #self.Bind(wx.EVT_PAINT, self.OnPaint)
          
        #self.CreateStatusBar()

#--------------------------------------------------------------------   
    def OnSetEncode(self,evt):
        """set encoding"""
        self.encode=self.encodeChoise.GetStringSelection()
        #print(self.encode)
        
    def OnSetFont(self,evt):
        """set font """
        self.fontName=self.fontChoise.GetStringSelection()
        #print(self.fontName)
        self.showExample()
        
    def OnSetWeight(self,evt):
        """set font weight"""
        #print(self.weightChoise.GetStringSelection())
        weight=self.weightChoise.GetStringSelection()
        if(weight=="Normal"):
            self.weight=wx.NORMAL
        elif(weight=="Light"):
            self.weight=wx.LIGHT
        else:
            self.weight=wx.BOLD            
        self.showExample()
        
    def OnSetSize(self,evt):
        """set font size"""
        self.height=int(self.heightChoise.GetStringSelection())
        #print(self.height)
        self.showExample()
        
    def showExample(self):
        """change the example chars to show the result to user"""
        self.font=wx.Font(self.height*0.75, wx.TELETYPE , wx.NORMAL, self.weight, faceName=self.fontName)
        self.dc.SetFont(self.font) 
        self.showtext.SetFont(self.font) 
        self.showtext.Wrap(-1)
        self.showtext.Wrap(400)

#--------------------------------------------------------------------        
    def getCharPixel(self ,chr,width,height):
        """get the pixels of a given char"""           
        self.dc.Clear()
        print(chr)
        #print("getting char ",chr#,self.charheight,width)
        self.dc.DrawText(chr,0,0)
        #self.screen.Blit(0,0,319,239,self.dc,0,0)
        k=7
        dot=0
        pixel=[]
        for i in range(0,height):
            for j in range(0,width) :
                clr=self.dc.GetPixel(j,i)
                if(clr[0]!=0):
                    dot=dot
                    #print(clr,hex(dot)," k=",k,hex(1<))
                k=k-1
                if (k == -1):
                    pixel.append(dot)
                    dot=0
                    k=7
                
        pixel.append(dot)
        #print(len(pixel),pixel)
        #raw_input("waiting: ")
        return pixel
    
   
    #write it to file
    def writeLib(self,name,charlist,charpixeldic):
        """write the generated library as a c header file,
           the name parm will be use to name the file and the array in file
        """
        print("\n now write the lib file")
        headerFile=open(name+".h",'w')
        headerFile.write("/* char lib header file generate by pyPCLGenerator */\n")
        headerFile.write("/* go vinge.cublog.cn for source code */\n\n")        
        headerFile.write("/* "+name+" char pixel library, char height:"+str(self.height)+"*/\n")
        
        headerFile.write("const unsigned char "+name+"[]["+str(len(charpixeldic[charlist[0]]))+"]={\n")
        result=""
        ct=0
        for i in charlist[0:-1]:
            result=result+"    {/*---char: "+i+" ---*/\n    "
            s=["0x"+binascii.b2a_hex(chr(j)) for j in charpixeldic[i]]            
            for j in s[0:-1] :
                result=result+j+","
            result=result+s[-1]+"\n    },\n"
            ct=ct+1
            if(ct>1000):
                print("writing, please wait")
                headerFile.write(result)
                headerFile.flush()
                result=""                                
        #add the last char
        result=result+"    {/*---char: "+charlist[-1]+" ---*/\n    "
        s=["0x"+binascii.b2a_hex(chr(j)) for j in charpixeldic[charlist[-1]]]        
        for j in s[0:-1] :
            result=result+j+","
        result=result+s[-1]+"\n    }\n};\n"        
        headerFile.write(result)
        headerFile.close()
        
#---------------------------------------------------------------        
    def OnDo(self,evt):
        """ generate the pixel char library"""
        if(self.encode=="ASCII"):
            #print("getting ascii")
            self.genASCII()
        elif(self.encode=="GB2312"):
            #print("getting gb2312")
            self.genGB2312()
        elif(self.encode=="GBK"):
            #print("getting gbk")
            self.genGBK()
        else:
            #print("getting big5")
            self.genBIG5()

    
    def OnPaint(self,evt):
        """Event paint for app"""
        print("painting")

#-------------------------------------------------------------  
    def genASCII(self):
        "generate the ascii char library"
        charList=[]
        charDic={}
        for i in range(32,127):
            charList.append(chr(i))
            charDic[chr(i)]=self.getCharPixel(chr(i),self.height/2,self.height)
        self.writeLib("font"+str(self.height/2)+"X"+str(self.height)+"asciilib",charList,charDic)
        print("\nascii library gen finish")
        
    def genGB2312(self):
        "generate the chinese gb2312 char library"
        charList=[]
        charDic={}        
        for i in range(0xb0,0xf8) :
            for j in range(0xa1,0xff) :
                thechar=chr(i)+chr(j)
                charList.append(thechar)
                charDic[thechar]=self.getCharPixel(thechar,self.height,self.height)
        self.writeLib("font"+str(self.height)+"X"+str(self.height)+"gb2312lib",charList,charDic) 
        print("\ngb2312 library gen finish")
             
    def genGBK(self):
        "generate the chinese gbk char library"
        charList=[]
        charDic={}        
        for i in range(0x81,0xff) :
            for j in range(0x40,0xff) :
                thechar=chr(i)+chr(j)
                charList.append(thechar)
                charDic[thechar]=self.getCharPixel(thechar,self.height,self.height)
        self.writeLib("font"+str(self.height)+"X"+str(self.height)+"gbklib",charList,charDic)
        print ("\ngbk library gen finish")
        
    def genBIG5(self):
        "generate the chinese big5 char library"
        charList=[]
        charDic={}        
        for i in range(0x81,0xff) :
            for j in range(0x40,0x7f) :
                thechar=chr(i)+chr(j)
                charList.append(thechar)
                charDic[thechar]=self.getCharPixel(thechar,self.height,self.height)
            for j in range(0xa1,0xff) :
                thechar=chr(i)+chr(j)
                charList.append(thechar)
                charDic[thechar]=self.getCharPixel(thechar,self.height,self.height)            
        self.writeLib("font"+str(self.height)+"X"+str(self.height)+"big5lib",charList,charDic)        
        print("\nbig5 library gen finish")
        
#----------------------------------------------------------    
class MyApp(wx.App):
    def OnInit(self):
        frame = MyFrame(None, "Resource generator")
        self.SetTopWindow(frame)

        print("This program generate pixel font library for embed system.")
        frame.Show(True)
        return True
 
if __name__ == "__main__":         
    #app = MyApp(redirect=True)
    app = MyApp(redirect=False)
    app.MainLoop()
