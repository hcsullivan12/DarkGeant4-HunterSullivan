#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
#  HistogramPlotter.py
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
					
	
