# -*- coding: utf-8 -*-


'''

function : this program is to genreate chinese char library for embed system
 in encoding with gb2312 ,gbk, or Big5, in any font type user like and system have.   
 it can also generate Ascii librarys, the char height and width is allways 2:1 
version : 0.1
author :zfh1005
start date :20150706
license: GPL3

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
  
    def OnPaint(self,evt):
        """Event paint for app"""
        print("painting")

		
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
