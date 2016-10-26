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


def ConsolidateDataFromPathObjs(objs):
	
	MagnitudeList = []
	for obj in objs:
		for v in obj.GroupedVectors:
			MagnitudeList.append(obj.MagnitudeOfVector(v))
			
	return MagnitudeList

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
		self.PseudoPath = []
		self.GroupedVectors = []
		self.PseudoPathReconstruction()
		
	'''
	
		PseudoPathReconstruction(self)
		
		* Description
		
			...
	
	'''
	def PseudoPathReconstruction(self):
		
		def ReconstructPath(GroupedVectors):
			
			TotalGroupedVectors = len(GroupedVectors)
			
			# Copies by value not by reference!
			Vector = self.InitialPosition[:]
				
			for i in range(TotalGroupedVectors):
				for x in range(3):
					Vector[x] += GroupedVectors[i][x]
					
			return Vector
		
		self.GroupedVectors = self.GroupNearbyDisplacementVectors(
							self.Make_DisplacementVectorsList())
							
		self.PseudoPath = ReconstructPath(self.GroupedVectors)
		
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
				Magnitude += self.MagnitudeOfVector(V)
				
			return Magnitude >= (3.0 - Threshold)
				
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
			
			if self.MagnitudeOfVector(DisplacementVectorsList[i]) < 3.0:
				
				Temp_List.append(DisplacementVectorsList[i])
				
				if (CheckTempListTotalMagnitude(Temp_List) is True):
					
					GroupedDisplacementVectors.append(
					AverageTempList(Temp_List))
					Temp_List = []
					
			else:
				
				GroupedDisplacementVectors.append(
				DisplacementVectorsList[i])
				
		return GroupedDisplacementVectors
		
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
			self.Make_DisplacementVector(
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
		
		return sqrt(V1[0]**2 + V1[1]**2 + V1[2]**2)
