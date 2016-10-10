#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#
#  parse.py
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

from sys import exit


'''

	This program takes what could be a potentially large file generated
	from DarkGeant4 and disseminates the data to many files which hold
	a single event.
	
	If you were to run a simulation with ten thousand events, this
	program will generate ten thousand files each holding a single
	event.
	
	The other helper scripts are designed to just parse a single file
	which helps with multicore support as I'm able to spawn multiple
	python instances to parse through the volume of data.

'''

FileToLoad = "Output.txt"

def main():
	
	global FileToLoad
	
	try:
		fp  = open(FileToLoad, "r")
	except FileNotFoundError:
		print("No file called %s found" % (FileToLoad))
		print("Please pass a valid file using -file <filename>")
		exit(0)
		
	fpp = None
	
	IsAtEvent = False
	for line in fp:
		temp = line.split()
		try:
			if temp[0] == "Event" and temp[1] == "=":
				
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
	
def HandleArguments(args):
	
	global FileToLoad
	
	for i in range(1, len(args)):
		if "-file" in args[i] and i+1 != len(args):
			FileToLoad = args[i+1]

if __name__ == '__main__':
	import sys
	HandleArguments(sys.argv)
	sys.exit(main())
