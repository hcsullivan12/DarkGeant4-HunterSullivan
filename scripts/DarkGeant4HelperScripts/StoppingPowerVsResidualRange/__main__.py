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
	
FileToRead = "DarkGeantData"

def main():
	
	File = ReadFileAndGetFileContents()
	dedx_list = Get_dEdX_list(File)
	pos_list = GetPositionListFromFileContents(File)
	
	del File
	
	if len(pos_list) != len(dedx_list):
		print("pos = %d, dedx = %d" % (len(pos_list), len(dedx_list)))
		return
	
	print("FINE")
	
	ResidualRange = ConvertToXList(pos_list)
	
	PlotData(ResidualRange, dedx_list)
	
'''

	ReadFileAndGetFileContents()
	
	* Description
	
		Reads the entire DarkGeantData file and returns a list of the
		file line by line.

'''
		
def ReadFileAndGetFileContents():
	
	global FileToRead
	
	File = []
	try:
		with open(FileToRead) as fp:
			File = fp.readlines()
	except FileNotFoundError:
		print("FileNotFoundError; Is"+  FileToRead + " in the parent directory?")
		exit(0)
		
	return File	
	
'''

	Get_dEdX_List(File)
	
	* Description
	
		...

'''
def Get_dEdX_list(File):
	
	FoundLine = False
	List = []
	for line in File:
		if "Primary Ionization Energy" in line:
			FoundLine = False
		elif "dE/dx" in line:
			FoundLine = True
		elif FoundLine is True:
			List.append(float(line))
			
	return List
	
'''

	GetPositionListFromFileContents(File)
	
	* Description
	
		...

'''
def GetPositionListFromFileContents(File):
	
	Position = []
	PositionChunk = []
	
	FoundPositionStart = False
	for i in range(len(File)):
		
		if FoundPositionStart and len(File[i]) <= 1:
			
			FoundPositionStart = False
			Position.append(list(ListChunk))
			PositionChunk = []
			
		elif "Primary Particle Position" in File[i]:
			
			FoundPositionStart = True
			i += 1
			
		elif FoundPositionStart:
			
			PositionChunk.Append(File[i].split())
				
	return Position
	

#def GetResidualRangeList():
	

'''

	PlotData(XAxis, YAxis)
	
	* Description
	
		...

'''
def PlotData(XAxis, YAxis):

	plt.title("dE/dX vs residual range")
	plt.rcParams['font.size'] = 16.0
	plt.xlabel("residual range (cm)")
	plt.ylabel("dE/dX (MeV/cm)")
	plt.plot(XAxis, YAxis, 'go')
	plt.show()
	
'''

	SortLists(dedx, pos)
	
	* Description
	
		...

'''
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
	
'''

	ConvertToXList(pos)
	
	* Description
	
		...

'''

def ConvertToXList(pos):
	
	XList = []
		
	for i in range(len(pos)):
		XList.append(float(pos[i][3])/10.0)
		
	return XList
	
	
def HandleArguments(argv):
	
	global FileToRead
	
	for i in range(1, len(argv)):
		if "-split" in argv[i] and i+1 != len(argv):
			FileToRead = argv[i+1]

if __name__ == '__main__':
    import sys
    HandleArguments(sys.argv)
    sys.exit(main())
