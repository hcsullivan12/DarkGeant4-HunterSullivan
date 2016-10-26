#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#
#  SplitAndParseDarkGeantData.py
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

from multiprocessing import Process
from DarkGeantData import *
from Content import *

'''

	ParseSplitGeant4Output.py
	
	* Description

		Split and parses data outputted by DarkGeant
	
	

'''


FileToSplit = "DarkGeantOutput.dat"
PrintTree = False
NumberOfEvents = 0


'''

	main()
	
	* Description
	
		...

'''

def main():
	
	global FileToSplit
	
	print("Splitting %s." % (FileToSplit))
	SplitFile()
	print("Done!")
	
	print("Parsing Event Files.")
	SpawnProcesses()
	print("Done!")
	
	return 0
	
	
'''

	SpawnProcesses()
	
	* Description
	
		...

'''
def SpawnProcesses():
	
	global NumberOfEvents
	
	FirstGroup = [1, int(NumberOfEvents/2)]
	SecondGroup = [int(NumberOfEvents/2)+1, NumberOfEvents]
	
	ProcessList = []
	ProcessList.append(Process(target=EventLoop, args=(FirstGroup,)))
	ProcessList.append(Process(target=EventLoop, args=(SecondGroup,)))
	for i in range(2):
		ProcessList[i].start()
	for i in range(2):
		ProcessList[i].join()
	
	
'''

	EventLoop(Group)
	
	* Description
	
		...

'''
def EventLoop(Group):
	
	for i in range(Group[0], Group[1]+1):
		ContentObj = Content("Event_" + str(i))
		DarkGeant4DataObj = DarkGeant4Data(ContentObj.FileContents)
		DarkGeant4DataObj.SaveDarkGeant4Data("DarkGeantData_" + str(i))
	
'''

	SplitFile()
	
	* Description
	
		...

'''
def SplitFile():
	
	global FileToSplit
	global NumberOfEvents
	
	try:
		fp  = open(FileToSplit, "r")
	except FileNotFoundError:
		print("No file called %s found" % (FileToSplit))
		print("Please pass a valid file using -file <filename>")
		exit(0)
		
	fpp = None
	
	IsAtEvent = False
	temp = None
	for line in fp:
		temp = line.split()
		try:
			if temp[0] == "Event" and temp[1] == "=":
				
				# Number of Events from 1 -> temp[2]
				NumberOfEvents = int(temp[2])
				
				if IsAtEvent is False:
					
					fpp = open("Event_" + str(temp[2]), "w")
					IsAtEvent = True
					
				elif IsAtEvent is True:
					
					fpp.close()
					fpp = open("Event_" + str(temp[2]), "w")
					
			else:
				
				if fpp != None:
					fpp.write(line)
					
		except IndexError:
			pass
	
	if fpp != None:
		fpp.close()
	
	fp.close()
	
	return 0
	
'''

	HandleArguments(args)
	
	* Description
	
		Parses the sys.argv list
	

'''
	
def HandleArguments(args):
	
	global FileToSplit
	global PrintTree
	
	for i in range(1, len(args)):
		
		if "-split" == args[i] and len(args) != i+1:
			
			FileToSplit = args[i+1]
			
		elif "-tree" == args[i]:
			
			PrintTree = True				
		
		
if __name__ == '__main__':
	import sys
	HandleArguments(sys.argv)
	sys.exit(main())
