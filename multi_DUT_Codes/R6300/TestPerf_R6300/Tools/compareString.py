'''
This is a python file, the python version is v2.7.10

it's used for compare the two string.  
'''

import sys

temp1 = "111 222 5555"
temp2 = "aaa bbb ccc 111"

def compareString(temp_1, temp_2):
	result_1 = list()
	result_2 = list()

	'''
	If in string_1's items not in string _2, print it.
	'''
	for i in range(0, len(temp_1)):
		if temp_2.count(temp_1[i]) == 0 :
			result_1.append(temp_1[i])

	print(result_1)

	'''
	If in string_2's items not in string _1, print it.
	'''
	for j in range(0, len(temp_2)):
		if temp_1.count(temp_2[j]) == 0 :
			result_2.append(temp_2[j])        
	print(result_2)

'''
if __name__ == "__main__":
	if len(sys.argv) < 2:
		temp1 = temp1.strip().split(' ')
		temp2 = temp2.strip().split(' ')
		compareString(temp1, temp2)
	else:
		temp1 = sys.argv[1].strip().split(' ')
		temp2 = sys.argv[2].strip().split(' ')
	compareString(temp1, temp2)
		
'''







