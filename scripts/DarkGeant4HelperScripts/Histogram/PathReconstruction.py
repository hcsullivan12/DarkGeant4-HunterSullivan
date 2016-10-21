#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#
#  PathReconstruction.py
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

from math import sqrt

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
		
		

'''

	Class PathReconstructionV2
	
	* Description
	
		...

'''
class PathReconstructionV2(object):
	
	'''
	
		__init__(self, PositionList)
		
		* Description
		
			...
	
	'''
	def __init__(self, PositionList):
		
		self.PositionList = PositionList
		self.InitialPosition = [PositionList[0][0], 
								PositionList[0][1], 
								PositionList[0][2]]
								
		self.PsuedoPath = []
		
	'''
	
		PsuedoPathReconstruction(self)
		
		* Description
		
			...
	
	'''
	def PsuedoPathReconstruction(self):
		
		def ReconstructPath(GroupedVectors):
			
			TotalGroupedVectors = len(GroupedVectors)
			
			# Copies by value not by reference!
			Vector = self.InitialPosition[:]
			if TotalGroupedVectors == 1:
				print("STUB: TotalGroupedVectors == 1")
				
			for i in range(TotalGroupedVectors):
				for x in range(3):
					Vector[x] += GroupedVectors[i][x]
					
			return Vector
		
		GroupedVectors = self.GroupNearbyDisplacementVectors(
							self.Make_DisplacementVectorsList())
							
		self.PsuedoPath = ReconstructPath(GroupedVectors)
		
	'''
	
		GroupNearbyDisplacementVectors(self, DisplacementVectorsList)
		
		* Description
		
			...
	
	'''
	def GroupNearbyDisplacementVectors(self, DisplacementVectorsList):
		
		def CheckTempListTotalMagnitude(Temp_List):
			
			Magnitude = 0.0
			Threshold = 0.5
			for V in Temp_List:
				Magnitude += MagnitudeOfVector(V)
			if Magnitude >= 3.0 - Threshold:
				return True
			else:
				return False
				
		def AverageTempList(Temp_List):
			
			TotalVectors = len(Temp_List)
			
			if TotalVectors == 1:
				return [Temp_List[0][0],Temp_List[0][1],Temp_List[0][2]]
			
			Vector = [0.0, 0.0, 0.0]
			for i in range(TotalVectors):
				for x in range(3):
					Vector[x] += Temp_List[i][x]
					
			for x in range(3):
				Vector[x] /= TotalVectors
				
			return Vector
				
		
		Temp_List = []
		GroupedDisplacementVectors = []
		for i in range(len(DisplacementVectorsList)):
			if MagnitudeOfVector(DisplacementVectorsList[i]) < 3.0:
				Temp_List.append(DisplacementVectorsList[i])
				if (CheckTempListTotalMagnitude(Temp_List) is True):
					GroupDisplacementVectors.append(
					AverageTempList(Temp_List))
					Temp_List = []
			else:
				GroupDisplacementVectors.append(DisplacementVectorsList[i])
	'''
	
		Make_DisplacementVectorsList(self)
		
		* Description
		
			Loops through self.PositionList and returns a set of
			displacement vectors.
	
	'''
	def Make_DisplacementVectorsList(self):
		
		DisplacementVectorsList = []
		for i in range(len(self.PositionList) - 1):
			DisplacementVectorsList.append(
			Make_DisplacementVector(
			self.PositionList[i], self.PositionList[i+1]))
		return DisplacementVectorsList
			
			
	'''
	
		Make_DisplacementVector(self, V1, V2)
		
		* Description
		
			...
	
	'''
	def Make_DisplacementVector(self, V1, V2):
		
		DisplacementVector = []
		for i in range(3):
			DisplacementVector.append(V2[i] - V1[i])
		return DisplacementVector
		
	'''
	
		MagnitudeOfVector(self, V1)
		
		* Description
		
			...
	
	'''
	def MagnitudeOfVector(self, V1):
		
		return sqrt(V1[0]**2 + V2[1]**2 + V1[2]**2)
