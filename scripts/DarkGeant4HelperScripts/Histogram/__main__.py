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

from PathReconstruction import *
from HistogramPlotter import *

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
PathReconstructionMagnitude = []

'''

	HandleArguments
	
	* Comment
	
		Presently doesn't handle any arguments. Subject to change in
		the future!

'''
def HandleArguments(args):
	
	print("STUB: HandleArguments")

def main():
	
	MakeLists(ReadDarkGeantData())
	PlotHistogramsWithProcesses(InitializeHistogramObjects())
	
	return 0
	
	
'''

	ReadIonizationFileAndPopulateLists()
	
	* Description
	
		Reads the DarkGeantData file and places the data line 
		by line in an list called File. It then calls several functions 
		who expect this File list to be passed as a parameter.

'''	
def ReadDarkGeantData():
	
	File = []
	try:
		with open("DarkGeantData") as fp:
			File = fp.readlines()
	except FileNotFoundError:
		print("FileNotFoundError;Is DarkGeantData in the same directory?")
		print("Halting Execution")
		exit(0)
		
	return File
	
def MakeLists(File):
	
	global PrimaryKineticEnergyList
	global PrimaryIonizationList
	global TotalSecondaryEnergyList
	global TotalIonizationList
	global PathReconstructionObjs
	global PathReconstructionMagnitude
	
	MakeList(File, "Primary particle kinetic energy", PrimaryKineticEnergyList)
	MakeList(File, "Primary Ionization Energy", PrimaryIonizationList)
	MakeList(File, "Total Secondary Energy", TotalSecondaryEnergyList)
	MakeList(File, "Total Ionization Energy", TotalIonizationList)
	MakeSecondaryEnergyList(File)
	MakedEdxList(File)
	
	PositionList = MakePositionList(File)
	for List in PositionList:
		PathReconstructionObjs.append(PathReconstructionV2(List))
	
	PathReconstructionMagnitude = ConsolidateDataFromPathObjs(
									PathReconstructionObjs)
	
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
	global PathReconstructionMagnitude
	
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
								"dE/dX (Mev/cm)",
								"Amount",
								XRange = [0,1200],
								Bins = 9000)
								
	PathMagnitudeHistogram = HistogramPlotter(
								PathReconstructionMagnitude,
								"Magnitude of displacement per step",
								"Distance (mm)",
								"Amount")
								
	HistogramObjs.append(PrimaryHistogram)
	HistogramObjs.append(TotalIonizationHistogram)
	HistogramObjs.append(PrimaryIonizationHistogram)
	HistogramObjs.append(dEdxHistogram)
	HistogramObjs.append(PathMagnitudeHistogram)
	
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
	
		* Description
		
		

'''

def MakeSecondaryEnergyList(File):
	
	global SecondaryEnergyList
	
	AtSecondaryEnergy = False
	for i in range(len(File)):
		
		if (len(File[i]) == 1 
		or "Ionization Energy" in File[i] 
		or "dE/dx" in File[i]):
			
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
		elif len(File[i]) <= 1 and AtPosition is True:
			AtPosition = False
			PositionList.append(TempPositionList)
			TempPositionList = []
		elif AtPosition is True:
			TempPositionList.append(list(map(float, File[i].split())))
			
	return PositionList	
		
if __name__ == '__main__':
    import sys
    HandleArguments(sys.argv)
    exit(main())
