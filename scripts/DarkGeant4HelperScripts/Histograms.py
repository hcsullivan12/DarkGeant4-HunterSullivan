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

PrimaryParticleEnergyList = []
IonizationEnergyList = []
SecondaryEnergyList  = []
TotalSecondaryEnergyList = []
DifferenceList = []
dEdxlist = []


'''

	HandleArguments
	
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
	
	Initializes a list of HistogramPlotter objects and returns
	a list of these objects.

'''

def InitializeHistogramObjects():
	
	global PrimaryParticleEnergyList
	global IonizationEnergyList
	global dEdxlist
	
	HistogramObjs = []

	PrimaryHistogram = HistogramPlotter(PrimaryParticleEnergyList,
								"Initial Proton Kinetic Energy",
								"Kinetic Energy (MeV)",
								"Amount",
								XRange = [0,1200])
								
	IonizationHistogram = HistogramPlotter(IonizationEnergyList,
								"Total Ionization Energy",
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
	HistogramObjs.append(IonizationHistogram)
	HistogramObjs.append(dEdxHistogram)
	
	return HistogramObjs
	
'''

	PlotHistogramsWithProcesses()
	
	Takes in a list of HistogramPlotter objects and spawns several
	processes to plot each of the HistogramPlotter objects concurrently.
	
	* Warning
	
		Can lead to an excessive use of computational resources. If you
		experience a computer crash this function might be the cause.

'''

def PlotHistogramsWithProcesses(HistogramObjs):
	
	Processes = []
	for obj in HistogramObjs:
		Processes.append(Process(target = obj.PlotHistogram, args=()))
	for ProcessObj in Processes:
		ProcessObj.start()
	for ProcessObj in Processes:
		ProcessObj.join()
	
	
'''

	SecondarListChunkProcesses()
	
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
	
	Loads the entire IonizationEnergy file and places the data line by
	line in an list called File. It then calls several functions who
	expect this File list to be passed as a parameter.

'''

def ReadIonizationFileAndPopulateLists():
		
	global PrimaryParticleEnergyList
	global IonizationEnergyList
	global TotalSecondaryEnergyList
		
	File = []
	
	try:
		with open("DarkGeantData") as fp:
			for line in fp:
				File.append(line)
	except FileNotFoundError:
		print("FileNotFoundError;Is IonizationEnergy in the same directory?")
		print("Halting Execution")
		exit(0)
			
	MakeList(File, "Primary particle energy", PrimaryParticleEnergyList)
	MakeList(File, "Ionization Energy", IonizationEnergyList)
	MakeList(File, "Total Secondary Energy", TotalSecondaryEnergyList)
	
	MakeSecondaryEnergyList(File)
	MakedEdxList(File)
	FindDifferenceBetweenIonizationAndTotalSecondary()
	
	
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
	
	global IonizationEnergyList
	global TotalSecondaryEnergyList
	global DifferenceList
	
	if len(IonizationEnergyList) != len(TotalSecondaryEnergyList):
		print("The length of the Ionization and Total Secondary energy" +
			" lists do not match.")
		print("Halting execution")
		print(len(IonizationEnergyList))
		print(len(TotalSecondaryEnergyList))
		exit(0)
	
	for i in range(len(IonizationEnergyList)):
		DifferenceList.append(abs(
		IonizationEnergyList[i] - TotalSecondaryEnergyList[i]))

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

if __name__ == '__main__':
    import sys
    HandleArguments(sys.argv)
    exit(main())
