#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#
#  Histograms.py
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
from multiprocessing import Process
from math import floor
from time import clock

try:
	import numpy as np
except ImportError:
	print("ImportError;Is numpy for python3 installed?")
	print("Halting Execution")
	exit(0)
	
try:
	import matplotlib.pyplot as plt
except ImportError:
	print("ImportError;Is matplotlib for python3 installed?")
	print("Halting Execution")
	exit(0)
	

'''

	Global lists. Will be initialized with the function
	ReadIonizationFileAndPopulateLists().

'''

PrimaryKineticEnergyList = []
PrimaryIonizationList = []
SecondaryEnergyList  = []
TotalSecondaryEnergyList = []
DifferenceList = []
dEdxlist = []
TotalIonizationList = []
PositionList = []
PathReconstructionObjs = []


'''

	HandleArguments
	
	* Comment
	
		Presently doesn't handle any arguments. Subject to change in
		the future!

'''
def HandleArguments(args):
	return 0

def main():
	
	ReadIonizationFileAndPopulateLists()
	PlotHistogramsWithProcesses(InitializeHistogramObjects())
	
	return 0
	
	
'''

	InitializeHistogramObjects()
	
	* Description
	
		Initializes a list of HistogramPlotter objects and returns
		a list of these objects.

'''

def InitializeHistogramObjects():
	
	global PrimaryKineticEnergyList
	global PrimaryIonizationList
	global dEdxlist
	global TotalIonizationList
	
	HistogramObjs = []

	PrimaryHistogram = HistogramPlotter(PrimaryKineticEnergyList,
								"Initial Proton Kinetic Energy",
								"Kinetic Energy (MeV)",
								"Amount",
								XRange = [0,1200])
								
	TotalIonizationHistogram = HistogramPlotter(TotalIonizationList,
                                 "Total Ionization Energy",
                                 "Energy (MeV)",
                                 "Amount",
                                 XRange = [0,1200])
								
	PrimaryIonizationHistogram = HistogramPlotter(PrimaryIonizationList,
								"Primary Ionization Energy",
								"Energy (MeV)",
								"Amount",
								XRange = [0,1200])
								
	dEdxHistogram = HistogramPlotter(dEdxlist,
								"dE/dX Histogram",
								" dE/dX (Mev/cm)",
								"Amount",
								XRange = [0,1200],
								Bins = 9000)
								
	HistogramObjs.append(PrimaryHistogram)
	HistogramObjs.append(TotalIonizationHistogram)
	HistogramObjs.append(PrimaryIonizationHistogram)
	HistogramObjs.append(dEdxHistogram)
	
	return HistogramObjs
	
'''

	PlotHistogramsWithProcesses()
	
	* Description
	
		Takes in a list of HistogramPlotter objects and spawns several
		processes to plot each of the HistogramPlotter objects 
		concurrently.
	
	* Warning
	
		Can lead to an excessive use of computational resources. If you
		experience a computer crash this function might be the cause.

'''

def PlotHistogramsWithProcesses(HistogramObjs):
	
	Processes = []
	for obj in HistogramObjs:
		Processes.append(Process(target=obj.PlotHistogram, args=()))
	for ProcessObj in Processes:
		ProcessObj.start()
	for ProcessObj in Processes:
		ProcessObj.join()
	
	
'''

	SecondarListChunkProcesses()
	
	* Description
	
		For HistogramPlotter objects with a large data set, it might
		be useful to spread the data around to several plots. This
		might be the only way that the data is plottable and some idea
		of any trends might be discernible using this function.
	
	* Warning
	
		This function is not complete
	
	TODO
	
		Make sure all data is plotted

'''

def SecondaryListChunkProcesses():
	
	global SecondaryEnergyList
	
	SubProcessCount = floor(len(SecondaryEnergyList)/50000)
	RemainderRange  = len(SecondaryEnergyList)%50000
	
	print("Remainder = %d" % (RemainderRange))
	for i in range(0, int(SubProcessCount), 3):
		HistogramObjs = []
		SubProcess = []
		for x in range(3):
			HistogramObjs.append(
			HistogramPlotter(Data = SecondaryEnergyList,
							Title = "Chunk " + str(x+i),
							Range = [(x+i)*50000,(x+i+1)*50000]))
							
			SubProcess.append(Process(
			target = HistogramObjs[x].PlotHistogram, args=()))
			SubProcess[x].start()
			
		for x in range(3):
			SubProcess[x].join()
			

'''

	ReadIonizationFileAndPopulateLists()
	
	* Description
	
		Loads the entire IonizationEnergy file and places the data line 
		by line in an list called File. It then calls several functions 
		who expect this File list to be passed as a parameter.

'''

def ReadIonizationFileAndPopulateLists():
		
	global PrimaryKineticEnergyList
	global PrimaryIonizationList
	global TotalSecondaryEnergyList
	global TotalIonizationList
	global PathReconstructionObjs
		
	File = []	
	try:
		with open("DarkGeantData") as fp:
			
			for line in fp:
				File.append(line)
				
	except FileNotFoundError:
		
		print("FileNotFoundError;Is DarkGeantData in the same directory?")
		print("Halting Execution")
		exit(0)
	
	MakeList(File, "Primary particle kinetic energy", PrimaryKineticEnergyList)
	MakeList(File, "Primary Ionization Energy", PrimaryIonizationList)
	MakeList(File, "Total Secondary Energy", TotalSecondaryEnergyList)
	MakeList(File, "Total Ionization Energy", TotalIonizationList)
	MakeSecondaryEnergyList(File)
	MakedEdxList(File)
	
	PositionList = MakePositionList(File)
	for List in PositionList:
		PathReconstructionObjs.append(PathReconstruction)
	
	'''
	
		...
	
	PositionList = MakePositionList(File)
	for List in PositionList:
		PathReconstructionObjs.append(PathReconstruction(List))
	'''
	
'''

	MakeList(File, StringConditional, List)
	
	...

'''

def MakeList(File, StringConditional, List):
	
	for i in range(len(File)):
		if StringConditional in File[i]:
			List.append(float(File[i+1]))
		
'''

	MakedEdxList(File)
	
	...

'''
	
def MakedEdxList(File):
	
	global dEdxlist
	
	AtdEdx = False
	for i in range(len(File)):
	
		if len(File[i]) <= 1 or "Ionization" in File[i]:
			AtdEdx = False
		elif "dE/dx" in File[i]:
			AtdEdx = True
		elif AtdEdx is True:
			dEdxlist.append(float(File[i]))
	
'''

	MakeSecondaryEnergyList(File)
	
	...

'''

def MakeSecondaryEnergyList(File):
	
	global SecondaryEnergyList
	
	AtSecondaryEnergy = False
	for i in range(len(File)):
		if len(File[i]) == 1 or "Ionization Energy" in File[i] or "dE/dx" in File[i]:
			AtSecondaryEnergy = False
		elif "Ionization particle" in File[i]:
			AtSecondaryEnergy = True
		elif AtSecondaryEnergy is True:
			try:
				SecondaryEnergyList.append(float(File[i]))
			except ValueError:
				print(len(File[i]))
				print("Error with string %s" % (File[i]))
				
'''

	FindDifferenceBetweenIonizationAndTotalSecondary()
	
	...

'''
				
def FindDifferenceBetweenIonizationAndTotalSecondary():
	
	global PrimaryIonizationList
	global TotalSecondaryEnergyList
	global DifferenceList
	
	if len(PrimaryIonizationList) != len(TotalSecondaryEnergyList):
		
		print("The length of the Ionization and Total Secondary energy" 
		+ " lists do not match.")
		print("Halting execution")
		print(len(PrimaryIonizationList))
		print(len(TotalSecondaryEnergyList))
		exit(0)
	
	for i in range(len(PrimaryIonizationList)):
		
		DifferenceList.append(abs(
		PrimaryIonizationList[i] - TotalSecondaryEnergyList[i]))
		
		
	'''

	MakePositionList(File)
	
	* Description
	
		...
		
	TODO
	
		This might need a three dimensional array to handle
		appropriately. As of right now, it's not correct.

	'''
def MakePositionList(File):
	
	PositionList = []
	TempPositionList = []
	
	AtPosition = False
	for i in range(len(File)):
		if "Primary Particle Position" in File[i]:
			AtPosition = True
		elif len(File[i]) <= 1:
			AtPosition = False
			PositionList.append(TempPositionList)
			TempPositionList = []
		elif AtPosition is True:
			TempPositionList.append(list(map(float, File[i].split())))
			
	return PositionList

'''

	class HistogramPlotter(object)
	
	* Description
	
		...

'''
class HistogramPlotter(object):
	
	def __init__(self,Data = None, 
				Title = "A Histogram Plot",
				XAxisLabel = "Default Y Axis label",
				YAxisLabel = "Default X Axis label",
				Range = [],
				XRange = [],
				YRange = [],
				Bins = "auto"):
		
		self.Data  = Data
		self.Title = Title
		self.XAxisLabel = XAxisLabel
		self.YAxisLabel = YAxisLabel
		self.Range = Range
		
		self.XRange = XRange
		self.YRange = YRange
		self.Bins = Bins
		
		
	'''
	
		PlotHistogram()
		
		* Description
		
			...
	
	'''
	def PlotHistogram(self):
		
		plt.rcParams['font.size'] = 24.0
		
		if len(self.Range) == 0:
			plt.hist(self.Data, self.Bins)
		else:
			plt.hist(self.Data[self.Range[0]:self.Range[1]], self.Bins)
			
		plt.title(self.Title)
		plt.xlabel(self.XAxisLabel)
		plt.ylabel(self.YAxisLabel)
		
		if len(self.XRange) == 2:
			plt.gca().set_xlim(self.XRange)
		if len(self.YRange) == 2:
			plt.gca().set_ylim(self.YRange)
			
		plt.show()
		plt.close()
		
		
'''

	class PathReconstruction(object)
	
	* Description
	
		This class is used to create pseudopath reconstruction
		vectors.

'''
class PathReconstruction(object):
	
	'''
	
		__init__(selt, List)
		
		* Description
		
			PathReconstruction constructor which takes in a 2d list
			simply titled List.
			
			** List
			
				List is a 2d list which can have an arbitrary amount
				of rows but must have exactly four columns.
				
				The columns are arranged as follows:
				
				[X, Y, Z, steplength]
				
				Note, steplength is the length between two vectors,
				so keep in mind that the steplength of the first
				row is 0.0
			
	
	'''
	def __init__(self, List):
		
		self.List = List
		self.AveragingRadius = 3.0
		
		self.PathList = []
		self.PsuedoPoyntingVector = []
		self.MakePathReconstruction()
				
	'''
	
		MakePathReconstruction(self)
		
		* Description
		
			Obtains a set of displacement vectors from self.List and
			defines the PsudoPoyningVector member variable.
	
	'''
	def MakePathReconstruction(self):
		
		'''
		
			Declares a GenericDisplacementVector list which turns
			into a 2d array with exactly 3 columns and len(self.List)-1
			rows.
			
			GenericDisplacementVector holds the values returned by
			the MakeDisplacementVector member function.
		
		'''
		GenericDisplacementVectors = []
		for i in range(len(self.List) - 1):
			GenericDisplacementVectors.append(
			self.MakeDisplacementVector(self.List[i], self.List[i+1]))
		
		'''
		
			Defines PsudoPoyntingVector by using the 2d array
			GenericDisplacementVectors.
		
		'''
		self.PseudoPoyntingVector = self.PseudoPath(
		self.GroupDisplacementVectors(GenericDisplacementVectors))
		
		
	'''
	
		PseudoPath(self)
		
		* Description
		
			Takes a list of Displacement Vectors and reconstructs a
			psuedopath.
			
			Returns a PoyntingVector with the following information:
			
				V_0 + summation(DisplacementVectors) where V_0
				is the initial position of the primary particle.
	
	'''
	def PseudoPath(self, DisplacementVectors):
		
		PoyntingVector = [self.List[0][0], self.List[0][1], self.List[0][1]]
		for DisplacementVector in DisplacementVectors:
			for i in range(3):
				PoyntingVector[i] += DisplacementVector[i]
			
		return PoyntingVector
	
	'''
	
		GroupDisplacementVectors(self, GenDisplacementVectors)
		
		* Description
		
			Attempts to group the Generic Displacement Vectors if 
			they fall within a 3mm radius. The grouped vectors will
			then be averaged and the averaged vector will be added to
			the list DisplacementVectors.
			
			If a Generic Displacement Vector does not fall within a 3mm
			radius, then it's simply added to DisplacementVectors
	
	'''
	def GroupDisplacementVectors(self, GenDisplacementVectors):
		
		DisplacementVectors = []
		
		Temp_Magnitude = 0.0
		Temp_NumberOfDisplacementVectors = 0
		Temp_DisplacementVector = [0.0, 0.0, 0.0]
		for i in range(len(GenDisplacementVectors)):
			'''
			
				If the Magnitude(GenDisplacementVector[i]) < 3.0
				
				Remember, the magnitude of the displacement vector
				is stored in the 4th column.
			
			'''
			if (self.List[i+1][3] < self.AveragingRadius 
				and Temp_Magnitude < 3.0):
					
				Temp_Magnitude += self.List[i+1][3]
				# TODO Something looks wrong here.
				for elem in range(3):
					Temp_DisplacementVector[elem] += GenDisplacementVectors[i][elem]
					
				Temp_NumberOfDisplacementVectors += 1
				
				
			elif (self.List[i+1][3] < self.AveragingRadius 
				and Temp_Magnitude >= 3.0):
				
				print(Temp_Magnitude)
				for elem in range(3):
					Temp_DisplacementVector[elem] /= Temp_NumberOfDisplacementVectors
			
				DisplacementVectors.append(Temp_DisplacementVector)
				Temp_DisplacementVector = [0.0, 0.0, 0.0]
				Temp_NumberOfDisplacementVectors = 0
				Temp_Magnitude = 0.0
				
				
			else:
				
				DisplacementVectors.append(GenDisplacementVectors[i])
				Temp_DisplacementVector = [0.0, 0.0, 0.0]
				Temp_NumberOfDisplacementVectors = 0
				Temp_Magnitude = 0.0
				
			return DisplacementVectors
	'''
	
		MakeDisplacementVector(self, V1, V2)
		
		* Description
		
			Returns a displacement vector of the form:
			
			V = V2 - V1
			
			** V1/V2
			
				Row vectors with four elements with the following
				format:
				
				[X, Y, Z, steplength]
				
				Note, steplength is ignored.
	
	'''
	def MakeDisplacementVector(self, V1, V2):
		
		DisplacementVector = []
		for i in range(3):
			DisplacementVector.append((V2[i] - V1[i]))
			
		return DisplacementVector
				
		
		
if __name__ == '__main__':
    import sys
    HandleArguments(sys.argv)
    exit(main())
