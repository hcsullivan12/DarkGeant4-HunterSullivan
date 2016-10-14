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

'''

	ParseSplitGeant4Output.py
	
	* Description

		Split and parses data outputted by DarkGeant
	
	

'''


FileToSplit = "Output.txt"
ReadFilename = None
OutputIonizationFile = None
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
	
	global ReadFilename
	global OutputIonizationFile
	global FileToSplit
	global PrintTree
	
	for i in range(1, len(args)):
		
		if "-split" == args[i] and len(args) != i+1:
			
			FileToSplit = args[i+1]
			
		elif "-read" == args[i] and len(args) != i+1:
			
			ReadFilename = args[i+1]
			
		elif "-tree" == args[i]:
			
			PrintTree = True
			
		elif "-output-ionization" and len(args) != i+1:
			
			OutputIonizationFile = args[i+1]
		
'''

	Content(object)
	
	* Description
	
		This class handles a large subset of the parsing for this file,
		however I suspect it has grown to big and bloated and goes
		beyond the scope of it's initial design.
	
	TODO
	
		Refactor

'''	
class Content(object):
	
	#Get ready for a hefty amount of computation
	def __init__(self, Filename, PrintTree = False):
		
		#self.ParentName = ""
		#self.ParticleList = []
		#self.levelslist = [""]
		#self.PrintTree = PrintTree
		self.FileContents = []
		
		self.ReadFile(Filename)
		#self.PopulateLevelsList()
		#self.ParseFileContents()
		
		
	def PopulateLevelsList(self):
		
		for i in range(1,50):
			self.levelslist.append(self.levelslist[i-1] + "-")
		
		
	def ReadFile(self, Filename):
		
		# Loads the entire content of the file specified by filename
		# and places it into a list.
		try:
			with open(Filename, "r") as fp:
				for line in fp:
					self.FileContents.append(line)
		except FileNotFoundError:
			print("You need to pass an Event file -read <Event file>")
		
	def ParseFileContents(self):
		
		self.InitializeParticleList()
		self.DetermineLargestParentId()
		self.FindParentParticle()
		
		if self.PrintTree is True:
			self.MakeHierarchy()
		
	def InitializeParticleList(self):
		
		index = 0
		
		for string in self.FileContents:
			if "Parent" in string:
				self.ParticleList.append([])
				tempstringlist = string.split()
				
				#Particle name
				self.ParticleList[index].append(
				self.DetermineAttribute(
				"Particle", 2, tempstringlist))
				
				#Track ID
				self.ParticleList[index].append(
				int(
				self.DetermineAttribute(
				"Track", 3, tempstringlist)))
				
				#Parent ID
				self.ParticleList[index].append(
				int(
				self.DetermineAttribute(
				"Parent", 3, tempstringlist)))
				
				
				index += 1
				
	def DetermineLargestParentId(self):
		
		self.LargestParentId = 0
		for i in range(len(self.ParticleList)):
			if self.ParticleList[i][2] > self.LargestParentId:
				self.LargestParentId = self.ParticleList[i][2]
		
	def FindParentParticle(self):
		
		for i in range(len(self.ParticleList)):
			if self.ParticleList[i][2] == 0:
				self.ParentName = self.ParticleList[i][0]
				break
				
	def MakeHierarchy(self):
		
		self.Heirarchy = []
		self.Heirarchy.append(self.ParticleList[0])
		
		self.FindDaughters(0)
		for i in range(1, len(self.ParticleList)):
			self.FindDaughters(i)
		
	def PutHeirarchyInOrder(self):
		
		for y in range(1, len(self.Heirarchy)):
			for x in range(y+1, len(self.Heirarchy)):
				if self.Heirarchy[y][1] > self.Heirarchy[x][1]:
					temp = []
					temp.append(self.Heirarchy[y][0])
					temp.append(self.Heirarchy[y][1])
					temp.append(self.Heirarchy[y][2])
					
					self.Heirarchy[y][0] = self.Heirarchy[x][0]
					self.Heirarchy[y][1] = self.Heirarchy[x][1]
					self.Heirarchy[y][2] = self.Heirarchy[x][2]
					
					self.Heirarchy[x][0] = temp[0]
					self.Heirarchy[x][1] = temp[1]
					self.Heirarchy[x][2] = temp[2]
					
	def PrintHeirarchy(self, level, index, ParentId):
		
		for i in range(index, len(self.Heirarchy)):
			if self.Heirarchy[i][2] == ParentId:
				print(self.levelslist[level] + self.Heirarchy[i][0])
				self.PrintHeirarchy(level+1,i+1, self.Heirarchy[i][1])
		
	def FindDaughters(self, index):
		
		TrackerId = self.ParticleList[index][1]
		
		for i in range(index+1, len(self.ParticleList)):
			if self.ParticleList[i][2] == TrackerId:
				self.Heirarchy.append(self.ParticleList[i])
				
	def DetermineAttribute(self, AttributeString, Offset, stringlist):
		
		for i in range(len(stringlist)):
			if AttributeString == stringlist[i]:
				return stringlist[i+Offset].replace(",","")
		
				

'''

	DarkGeant4Data(Content)
			

'''		
class DarkGeant4Data(object):
	
	'''
	
		__init__(self, FileContents)
		
		* Parameters
		
			FileContents is a list whereby the file read in the previous
			Content class had placed the contents of the file line by 
			lineinto this list.
			
		* Description
		
			Constructor for the DarkGeant4Data class. It calculates the
			energy of the primary particle for the present Event File,
			the ionization energy of just the primary particle and the
			dE/dX of the primary particle per step.
		
		
	
	'''
	def __init__(self, FileContents):
		
		self.FileContents = FileContents
		
		self.GetPrimaryParticleInitialKineticEnergy()
		self.GetTotalSecondaryEnergyAtFirstStep()
		self.CalculateIonizationEnergyOfPrimaryParticle()
		self.CalculateTotalIonizationEnergy()
		self.Find_dEdx_through_detector()
		self.GetPrimaryPositionPerStep()
		
		
	'''
	
		GetPrimaryPositionPerStep(self)
		
		* Description
		
			...
	
	'''
	def GetPrimaryPositionPerStep(self):
		
		self.PositionList = []
		Pos = 0
		for i in range(4, len(self.FileContents)):
			
			if "*" in self.FileContents[i]:
				
				break
				
			self.PositionList.append([])
			TempSplit = self.FileContents[i].split()
			
			for t in range(3):
				
				self.PositionList[Pos].append(float(
				TempSplit[t+1]))
				
			Pos += 1
			
	'''
	
		GetPrimaryParticleInitialKineticEnergy(self)
		
		* Description
		
			As the function name might imply, it simply obtains
			the primary particle's initial kinetic energy.
	
	'''	
	def GetPrimaryParticleInitialKineticEnergy(self):
		
		self.PrimaryParticleEnergy = float(
		self.FileContents[4].split()[4])
		
		
	'''
	
		GetTotalSecondaryEnergyAtFirstStep(self)
		
		* Description
		
			Initializes a class variable list declared as 
			SecondaryParticleEnergies whose elements are the initial 
			kinetic energy of direct secondary electrons.
			
			This function also defines a class variable float declared
			as TotalSecondaryParticleEnergy where it holds the
			approximate value of the total initial kinetic energy of
			all the direct secondary electrons.
			
		
		TODO
		
			It might be worthwhile to have a function that determines
			the initial kinetic energy of direct secondary particles
			regardless of the type of particle.
	
	'''
	def GetTotalSecondaryEnergyAtFirstStep(self):
		
		self.SecondaryParticleEnergies = []
		self.TotalSecondaryParticleEnergy = 0.0
		for i in range(5, len(self.FileContents)):
			try:
				if  ("Parent ID = 1" in self.FileContents[i] and 
					 "Particle = e-" in self.FileContents[i]):
					
					self.SecondaryParticleEnergies.append(float
					(self.FileContents[i+3].split()[4]))
					
					self.TotalSecondaryParticleEnergy += float(
					self.FileContents[i+3].split()[4])
					
			except IndexError:
				pass
			
	'''
	
		GetTotalSecondaryEnergyAtEveryStep(self)
		
		* Comment
		
			I'm not entirely sure what I intended for this function,
			so I may just remove this at a later date.
		
		TODO
		
			Finish function
	
	'''	
	def GetTotalSecondaryEnergyAtEveryStep(self):
		
		self.TotalSecondaryParticleEnergyAtEveryStep = 0.0
		for i in range(5, len(self.FileContents)):
			continue
		

	'''
	
		CalculateIonizationEnergyOfPrimaryParticle(self)
		
		* Description
		
			Declares a class variable float as 
			PrimaryParticleIonizationEnergy, which holds the total 
			ionization particle caused solely by the primary particle.
	
	'''
	def CalculateIonizationEnergyOfPrimaryParticle(self):
		
		self.PrimaryParticleIonizationEnergy = 0.0
		for i in range(5, len(self.FileContents)):
			try:
				
				if "Particle" in self.FileContents[i]:
					
					break
					
				elif "Detector hIoni" in self.FileContents[i]:
					
					self.PrimaryParticleIonizationEnergy += float(
					self.FileContents[i].split()[5])
				
			except IndexError:
				pass
				
			
	'''
	
		CalculateTotalIonizationEnergy(self)
		
		* Description
		
			...
	
	'''	
	def CalculateTotalIonizationEnergy(self):
		
		self.TotalIonizationEnergy = 0.0
		for i in range(5, len(self.FileContents)):
			try:
				
				if ("Detector" in self.FileContents[i] and
					"Ioni" in self.FileContents[i]):
					
					self.TotalIonizationEnergy += float(
					self.FileContents[i].split()[5])
				
			except IndexError:
				pass
	
	'''
	
		Find_dEdx_through_detector(self)
		
		...
	
	'''
	def Find_dEdx_through_detector(self):
		
		self.dEdXDetector = []
		for i in range(5, len(self.FileContents)):
			try:
				
				if "Particle" in self.FileContents[i]:
					break
				elif "Detector hIoni" in self.FileContents[i]:
					dE = float(self.FileContents[i].split()[5])
					StepLength = float(self.FileContents[i].split()[6])/10.0
					self.dEdXDetector.append(dE/StepLength)
					
			except IndexError:
				pass
		
	'''
	
		CompareIonizationEnergyWithSecondaryEnergy(self)
		
		...
	
	'''		
	def CompareIonizationEnergyWithSecondaryEnergy(self):
		
		print("Ionization energy = %f" % 
		(self.PrimaryParticleIonizationEnergy))
		
		print("Secondary energy  = %f" % (
		self.TotalSecondaryParticleEnergy))
		
		print("Difference        = %f" % (abs(
		self.PrimaryParticleIonizationEnergy - 
		self.TotalSecondaryParticleEnergy)))
		
	'''
	
		SaveDarkGeant4Data(self, OutputIonizationFile)
	
		...
	
	'''
	def SaveDarkGeant4Data(self, OutputIonizationFile):
		
		fp = open(OutputIonizationFile, "w")
		
		fp.write("Primary particle kinetic energy\n")
		fp.write("%f\n" % (self.PrimaryParticleEnergy))
		fp.write("Ionization particle of immediate daughter secondaries\n")
		for element in self.SecondaryParticleEnergies:
			fp.write("%f\n" % (element))
		
		fp.write("dE/dx\n")
		for element in self.dEdXDetector:
			fp.write("%f\n" % (element))
		
		fp.write("Primary Ionization Energy\n")
		fp.write("%f\n" % (self.PrimaryParticleIonizationEnergy))
		fp.write("Total Secondary Energy\n")
		fp.write("%f\n" % (self.TotalSecondaryParticleEnergy))
		fp.write("Total Ionization Energy\n")
		fp.write("%f\n" % (self.TotalIonizationEnergy))
		fp.write("Primary Particle Position\n")
		
		for i in range(len(self.PositionList)):
			for t in range(3):
				if t != 2:
					fp.write("%f " % self.PositionList[i][t])
				else:
					fp.write("%f" % self.PositionList[i][t])
			fp.write("\n")
		
		fp.close()
		
		
		
if __name__ == '__main__':
	import sys
	HandleArguments(sys.argv)
	sys.exit(main())
