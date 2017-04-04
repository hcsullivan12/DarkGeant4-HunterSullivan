#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
#  Content.py
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

