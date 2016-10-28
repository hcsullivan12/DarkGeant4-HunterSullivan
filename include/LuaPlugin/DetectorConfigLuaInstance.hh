/*
 * DetectorConfigLuaInstance
 * 
 * Copyright 2016 Emma Davenport <Davenport.physics@gmail.com>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */

#ifndef DETECTORCONFIGLUAINSTANCE_HH
#define DETECTORCONFIGLUAINSTANCE_HH

// Third Party Headers
#include "lua.hpp"

// C/C++ Headers
#include <iostream>
#include <string>
#include <exception>
#include <vector>

// User Headers
#include "LuaInstance.hh"

#include "DetectorConstructionV2.hh"
#include "DetectorComponent.hh"
#include "DetectorComponentBox.hh"
#include "DetectorComponentCylinder.hh"

#include "Utilities.hh"


class DetectorConfigLuaInstance : public LuaInstance {
	
	
	/*
	 * 
	 * Class member variables
	 * 
	 * */
	public:
	
		int Number_of_Dectector_Components;
		DetectorComponent *World;
		vector<DetectorComponent *> Components;
		vector<DetectorComponent_Cylinder> CylinderComponents;
		vector<DetectorComponent_Box> BoxComponents;
		
	
	/*
	 * 
	 * Class member functions
	 * 
	 * */
	public:
	
		DetectorConfigLuaInstance(string ModulePath);
		~DetectorConfigLuaInstance();
	
	private:
	
		void Initialize_world();
		void Initialize_number_of_detector_components();
		void Initialize_detector_components();
		
		DetectorComponent *WithVolumeGetDetectorComponent(G4String Volume_Type, G4String Name);
		
		DetectorComponent_Cylinder *MakeDetectorComponent_Cylinder(G4String Name);
		DetectorComponent_Box *MakeDetectorComponent_Box(G4String Name);
		
	/*
	 * 
	 * TODO
	 * 
	 * Finish class
	 * 
	 * */
	
};

#endif

