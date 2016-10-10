#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#
#  ParseSplitGeant4Ouput.py
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

'''

	Parses Event_x Files generated from the SplitGeant4Ouput.py script
	
	

'''


ReadFilename = None
OutputIonizationFile = None
PrintTree = False


'''

	main()
	

'''

def main():
	
	global ReadFilename
	global OutputIonizationFile
	global PrintTree
		
	if ReadFilename == None:
		print("You need to pass an Event file to read -read <Event file>")
		return -1
		
	obj = Content(ReadFilename, PrintTree)

	if PrintTree is True:	
		obj.PrintHeirarchy(0, 0, 0)
	
	DarkGeant4DataObj = DarkGeant4Data(
	obj.FileContents)
	
	if OutputIonizationFile != None:
		DarkGeant4DataObj.SaveDarkGeant4Data(OutputIonizationFile)
	
	return 0
	
'''

	HandleArguments(args)
	
	Parses the sys.argv list
	

'''
	
def HandleArguments(args):
	
	global ReadFilename
	global OutputIonizationFile
	global PrintTree
	
	for i in range(1, len(args)):
		
		if "-read" == args[i] and len(args) != i+1:
			
			ReadFilename = args[i+1]
			
		elif "-tree" == args[i]:
			
			PrintTree = True
			
		elif "-output-ionization" and len(args) != i+1:
			
			OutputIonizationFile = args[i+1]
		
'''

	Content(object)
	
	This class handles a large subset of the parsing for this file,
	however I suspect it has grown to big and bloated and goes
	beyond the scope of it's initial design.
	
	TODO
	
		Refactor

'''	
class Content(object):
	
	#Get ready for a hefty amount of computation
	def __init__(self, Filename, PrintTree = True):
		
		self.ParentName = ""
		self.ParticleList = []
		self.levelslist = [""]
		self.PrintTree = PrintTree
		
		self.PopulateLevelsList()
		self.ReadFile(Filename)
		self.ParseFileContents()
		
		
	def PopulateLevelsList(self):
		
		for i in range(1,50):
			self.levelslist.append(self.levelslist[i-1] + "-")
		
		
	def ReadFile(self, Filename):
		
		# Loads the entire content of the file specified by filename
		# and places it into a list.
		fp = open(Filename, "r")
		self.FileContents = []
		for line in fp:
			self.FileContents.append(line)
		fp.close()
		
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
		self.Find_dEdx()
		
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
					
				elif "hIoni" in self.FileContents[i]:
					
					self.PrimaryParticleIonizationEnergy += float(
					self.FileContents[i].split()[5])
				
			except IndexError:
				pass
	
	'''
	
		Find_dEdx(self)
		
		...
	
	'''
	def Find_dEdx(self):
		
		self.dEdxList = []
		for i in range(5, len(self.FileContents)):
			try:
				
				if "Particle" in self.FileContents[i]:
					break
				elif "hIoni" in self.FileContents[i]:
					dE = float(self.FileContents[i].split()[5])
					StepLength = float(self.FileContents[i].split()[6])/10.0
					self.dEdxList.append(dE/StepLength)
					
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
		
		fp.write("Primary particle energy\n")
		fp.write("%f\n" % (self.PrimaryParticleEnergy))
		fp.write("Ionization particle of immediate daughter secondaries\n")
		for element in self.SecondaryParticleEnergies:
			fp.write("%f\n" % (element))
		
		fp.write("dE/dx\n")
		for element in self.dEdxList:
			fp.write("%f\n" % (element))
		
		fp.write("Ionization Energy\n")
		fp.write("%f\n" % (self.PrimaryParticleIonizationEnergy))
		fp.write("Total Secondary Energy\n")
		fp.write("%f\n" % (self.TotalSecondaryParticleEnergy))
		
		fp.close()
		
		
		
if __name__ == '__main__':
	import sys
	HandleArguments(sys.argv)
	sys.exit(main())
