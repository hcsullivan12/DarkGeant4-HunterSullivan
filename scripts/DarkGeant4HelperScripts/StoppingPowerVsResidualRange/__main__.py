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
	dedxChunkList = Getdedx(File)
	Position = GetPositionListFromFileContents(File)
	Energy = GetEnergyList(Position)
	ResidualRangeChunkList = GetResidualRangeList(Position)
	
	CompareChunkLengths(dedxChunkList, ResidualRangeChunkList)
	
	print("Length of dedxChunk = %d\n" % LengthOfChunkList(dedxChunkList))
	print("Length of ResidualRangeChunk = %d\n" % LengthOfChunkList(ResidualRangeChunkList))
	
	dedx = ConvertChunkListToList(dedxChunkList)
	ResidualRange = ConvertChunkListToList(ResidualRangeChunkList)
	Energy = GetEnergyList(Position)
	
	PlotData(ResidualRange, dedx, "dE/dX vs residual range", 
	"residual range (cm)", 
	"dE/dX (MeV/cm)")
	
	PlotData(ResidualRange, Energy, "E vs residual range",
	"residual range (cm)",
	"E (MeV)")
	
def LengthOfChunkList(ChunkList):
	
	Length = 0
	for chunk in ChunkList:
		Length += len(chunk)
		
	return Length
	
def CompareChunkLengths(Chunk1, Chunk2):
	
	if len(Chunk1) != len(Chunk2):
		print("Something went wrong")
		print("Length of Chunk1 = %d\n" % (len(Chunk1)))
		print("Length of Chunk2 = %d\n" % (len(Chunk2)))
		return
	
	for i in range(len(Chunk1)):
		if len(Chunk1[i]) != len(Chunk2[i]):
			print(len(Chunk1[i]))
			print(len(Chunk2[i]))
			print("Event %d mismatch\n" % (i+1))
	
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
def Getdedx(File):
	
	dedx = []
	dedxChunk = []
	
	FoundLine = False
	for line in File:
		
		if "Primary Ionization Energy" in line:
			
			FoundLine = False
			# len(dedxChunk) > 1 to skip last element
			# del dedxChunk[-1]
			if len(dedxChunk) > 0:
				del dedxChunk[-1]
				dedx.append(list(dedxChunk))
			dedxChunk = []
			
		elif "dE/dx" in line:
			
			FoundLine = True
			
		elif FoundLine:
			
			dedxChunk.append(float(line))
			
	return dedx
	
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
			if len(PositionChunk) != 0:
				Position.append(list(PositionChunk))
			PositionChunk = []
			
		elif "Primary Particle Position" in File[i]:
			
			FoundPositionStart = True
			i += 1
			
		elif FoundPositionStart:
			
			InsideDetector = "Detector" in File[i]
			IonizedDetector = "hIoni" in File[i]
			
			if InsideDetector and IonizedDetector:
				PositionChunk.append(File[i].split())
				
	# Fixes a super annoying bug
	if len(PositionChunk) != 0:
		Position.append(list(PositionChunk))
				
	return Position
	

def GetResidualRangeList(Position):
	
	ResidualRange = []
	ResidualRangeChunk = []
	for idx, chunk in enumerate(Position):
		
		if len(chunk) == 0:
			continue
			
		TotalTrackLength = float(chunk[-1][6])/10.0
		
		# len(chunk)-1 to skip last elements
		for i in range(0, len(chunk)-1):
			ResidualRangeChunk.append(TotalTrackLength - float(chunk[i][6])/10.0)
			
		ResidualRange.append(list(ResidualRangeChunk))
		ResidualRangeChunk = []
		
	return ResidualRange
	
def GetEnergyList(Position):
	
	EnergyList = []
	for chunk in Position:
		for idx in range(len(chunk)-1):
			EnergyList.append(float(chunk[idx][4]))
			
	return EnergyList
	
def GetIndexOfLastDetectorIonization(chunk):
	
	for i in range(len(chunk)-1, 0, -1):
		
		DetectorInteraction = "Detector" in chunk[i][-2]
		DetectorIonization = "Ioni" in chunk[i][-1]
		
		if DetectorInteraction and DetectorIonization:
			return i
			
	return 0
	
def ConvertChunkListToList(ChunkList):
	
	List = []
	for chunk in ChunkList:
		for element in chunk:
			List.append(float(element))
			
	return List

def SubtractLists(List1, List2):
	
	if len(List1) != len(List2):
		print("Something went wrong")
		return
	
	for idx in range(len(List1)):
		List1[idx] -= List2[idx]

def DeleteBadIndicies(dedx, ResidualRange):
	
	indices = []
	for i, element in enumerate(ResidualRange):
		if element == 0.0:
			indices.append(i)
			
	for i in range(len(indices)-1, 0, -1):
		del dedx[indices[i]]
		del ResidualRange[indices[i]]
'''

	PlotData(XAxis, YAxis)
	
	* Description
	
		...

'''
def PlotData(XAxis, YAxis, title, xlabel, ylabel):

	plt.title(title)
	plt.rcParams['font.size'] = 16.0
	plt.xlabel(xlabel)
	plt.ylabel(ylabel)
	plt.plot(XAxis, YAxis, 'go')
	plt.show()
	
	
def HandleArguments(argv):
	
	global FileToRead
	
	for i in range(1, len(argv)):
		if "-plot" in argv[i] and i+1 != len(argv):
			FileToRead = argv[i+1]

if __name__ == '__main__':
    import sys
    HandleArguments(sys.argv)
    sys.exit(main())
