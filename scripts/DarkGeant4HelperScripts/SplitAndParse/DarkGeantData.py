#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
#  DarkGeantData.py
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
			
			#if DetectorComponent in self.FileContents append.
			if "*" in self.FileContents[i]:
				break
				
			self.PositionList.append([])
			TempSplit = self.FileContents[i].split()
			
			# X, Y and Z coordinates in mm
			for t in range(3):
				
				self.PositionList[Pos].append(float(
				TempSplit[t+1]))
				
			# Step length
			self.PositionList[Pos].append(TempSplit[6])
			# Track length
			self.PositionList[Pos].append(TempSplit[7])
			# Particle Action
			self.PositionList[Pos].append(TempSplit[8])
			self.PositionList[Pos].append(TempSplit[9])
				
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
				
				if "*" in self.FileContents[i]:
					break
				elif ("Detector" in self.FileContents[i] 
					and "hIoni" in self.FileContents[i]):
						
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
			for t in range(6):
				if t != 5:
					fp.write(str(self.PositionList[i][t]))
					fp.write(" ")
				else:
					fp.write(str(self.PositionList[i][t]))
			fp.write("\n")
		
		fp.close()

