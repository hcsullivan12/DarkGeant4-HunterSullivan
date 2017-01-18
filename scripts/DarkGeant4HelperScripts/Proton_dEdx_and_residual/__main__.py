#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
#  dedx.py
#  
#  Copyright 2017 Emma Davenport <Davenport.physics@gmail.com>
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

import matplotlib.pyplot as plt
import pdb

def main(args):
	
	plt.rcParams['font.size'] = 24.0
	FileBuffer = GetFileBuffer()
	
	lists = GetLists(FileBuffer)
	
	dedx = GenerateDeDx(lists[0], lists[1])
	residual = GenerateResidual(lists[0], lists[1], lists[2])
	
	plotdedx(dedx)
	plotdedx_residualrange(dedx, residual)
	
	return 0
	
def plotdedx(dedx):
	
	dedx_1d_array = Generate_1d_array_from_2d(dedx)
	
	plt.title("Proton stopping power in Liquid Argon volume")
	plt.xlabel("dE/dx (MeV/cm)")
	plt.hist(dedx_1d_array, 5000)
	plt.show()
	plt.close()
	
def plotdedx_residualrange(dedx, residual):
	
	dedx_1d_array = Generate_1d_array_from_2d(dedx)
	residual_1d_array = Generate_1d_array_from_2d(residual)
	
	print("length of dedx = %d" % (len(dedx_1d_array)))
	print("length of residual = %d" % (len(residual_1d_array)))
	
	plt.title("dE/dx vs residual range")
	plt.xlabel("residual range (cm)")
	plt.ylabel("dE/dx MeV/cm")
	
	plt.hist2d(dedx_1d_array, residual_1d_array, (500, 500), cmap=plt.cm.jet)
	plt.colorbar()
	plt.show()
	plt.close()
	
	'''
	plt.plot(residual_1d_array, dedx_1d_array, 'ro')
	plt.show()
	plt.close()
	'''
	 
	
def Generate_1d_array_from_2d(array2d):
	
	array1d = []
	
	for vec in array2d:
		for elem in vec:
			array1d.append(elem)
			
	return array1d
	
def GetLists(FileBuffer):
	
	de = []
	dx = []
	track = []
	
	print(len(FileBuffer[0]))
	print(len(FileBuffer))
	print(FileBuffer[3])
	
	#pdb.set_trace()
	AtPrimary = False
	skip = 0
	for idx in range(3, len(FileBuffer)):
		
		if skip != 0:
			
			skip -= 1
			continue
			
		if "proton," in FileBuffer[idx]:
			
			de.append([])
			dx.append([])
			track.append([])
			
			AtPrimary = True
			skip = 2
			
		elif ("**" in FileBuffer[idx] or len(FileBuffer[idx]) == 1) and AtPrimary is True:
			
			AtPrimary = False
			
		elif AtPrimary is True and "DetectorComponent_1 hIon" in FileBuffer[idx]:
			
			de[-1].append(float(FileBuffer[idx].split()[5]))
			dx[-1].append(float(FileBuffer[idx].split()[6])/10.0)
			track[-1].append(float(FileBuffer[idx].split()[7])/10.0)
				
		#print(AtPrimary)
	return [de, dx, track]
	
def GenerateDeDx(de, dx):
	
	dedx = []
	
	for current_vec in range(len(de)):
		dedx.append([])
		for idx in range(len(de[current_vec])):
			try:
				
				dedx[-1].append(de[current_vec][idx]/dx[current_vec][idx])
				
			except:
				pass
	
	return dedx

'''

length of dedx     = 283118
length of residual = 283126

'''	
def GenerateResidual(de, dx, track):
	
	residual = []
	
	for current_vec in range(len(dx)):
		residual.append([])
		for idx in range(len(dx[current_vec])):
			try:
				de[current_vec][idx]/dx[current_vec][idx]
				residual[-1].append(track[current_vec][-1] - dx[current_vec][idx])
			except:
				pass
	
	return residual
	
def GetAveragededx(dedx):
	
	Sum = 0.0
	for elem in dedx:
		Sum += elem
		
	return Sum/len(dedx)

def GetFileBuffer():
	
	File = []
	with open("DarkGeantOutput.dat", "r") as fp:
		for line in fp:
			File.append(line)
			
	return File

if __name__ == '__main__':
	import sys
	sys.exit(main(sys.argv))
