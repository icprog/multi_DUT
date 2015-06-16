'''
Converent the MAC string to the ASCII and change to base 16 rate.
'''

import sys

def getASCII(MAC):
    result = ''
    for i in range(len(MAC)):        
        temp = hex(ord(MAC[i].lower()))
        result += temp.strip().split('0x')[-1]
    return result




if __name__ == "__main__":
	if len(sys.argv) < 2:
		print(getASCII('ab122222:2222'))
	else:
		print(getASCII(sys.argv[1]))
		


