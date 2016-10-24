#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#
#  __main__.py
#  
#  Copyright 2016 Emma Davenport <Davenport.physics@gmail.com>
#  
#  This program is free software; you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation; either version 2 of the License, or
#  (at your option) any later version.
#  
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#  
#  You should have received a copy of the GNU General Public License
#  along with this program; if not, write to the Free Software
#  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
#  MA 02110-1301, USA.
#  
#  

try:
	import matplotlib.pyplot as plt
except ImportError:
	print("ImportError: Is matplotlib for python3 installed?")
	exit(0)

def main(args):
	
	File = ReadFile()
	dedx_list = Get_dEdX_list(File)
	pos_list = Get_Position_List(File)
	
	del File
	
	XList = ConvertToXList(pos_list)
	
	if len(XList) != len(dedx_list):
		print("XList = %d, dedx = %d" % (len(XList), len(dedx_list)))
	
	SortedList = SortLists(dedx_list, XList)
	
	plt.title("dE/dX vs residual range")
	plt.rcParams['font.size'] = 16.0
	plt.xlabel("residual range (mm)")
	plt.ylabel("dE/dX (MeV/cm)")
	plt.plot(SortedList[0], SortedList[1],)
	plt.show()
	
	
def SortLists(dedx, pos):
	
	for y in range(len(pos)):
		for x in range(y+1, len(pos)):
			if pos[y] > pos[x]:
				temp = pos[y]
				pos[y] = pos[x]
				pos[x] = temp
				
				temp = dedx[y]
				dedx[y] = dedx[x]
				dedx[x] = temp
				
	return [pos, dedx]
    
def ConvertToXList(pos):
	
	XList = []
		
	for i in range(len(pos)-1):
		XList.append(pos[i+1][3])
		
	return XList
    
def Get_dEdX_list(File):
	
	FoundLine = False
	List = []
	for line in File:
		if "Primary Ionization Energy" in line:
			break
		elif "dE/dx" in line:
			FoundLine = True
		elif FoundLine is True:
			List.append(float(line))
			
	return List
	
def Get_Position_List(File):
	
	FoundLine = False
	List = []
	for line in File:
		if FoundLine is True and len(line) <= 1:
			break
		elif "Primary Particle Position" in line:
			FoundLine = True
		elif FoundLine is True:
			List.append(list(map(float, line.split())))
			
	return List
		
def ReadFile():
	
	File = []
	try:
		with open("DarkGeantData") as fp:
			File = fp.readlines()
	except FileNotFoundError:
		print("FileNotFoundError; Is DarkGeantData in the parent directory?")
		exit(0)
		
	return File

if __name__ == '__main__':
    import sys
    sys.exit(main(sys.argv))
