/*
 * DetectorConfigLuaInstance.cxx
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


#include "DetectorConfigLuaInstance.hh"

/*
 * DetectorConfigLuaInstane::DetectorConfigLuaInstance(string ModulePath)
 * 
 * 
 * */

DetectorConfigLuaInstance::DetectorConfigLuaInstance(string ModulePath)
: LuaInstance(ModulePath, "DetectorConfig.lua")
{
	Initialize_world();
	
	LoadTable("DetectorConfig");
	Initialize_number_of_detector_components();
	Initialize_detector_components();
	
}

/*
 * DetectorConfigLuaInstance::~DetectorConfigLuaInstance()
 * 
 * 
 * */

DetectorConfigLuaInstance::~DetectorConfigLuaInstance() 
{
		
	
}

void DetectorConfigLuaInstance::Initialize_world() {
	
	LoadTable("World");
    this->World = WithVolumeGetDetectorComponent(SetSharedAttributes("0"));
    lua_pop(this->L, 1);
}

/*
 * DetectorConfigLuaInstance::Initialize_number_of_detector_components()
 * 
 * 
 * 
 * */

void DetectorConfigLuaInstance::Initialize_number_of_detector_components() {
	
	this->Number_of_Dectector_Components = GetNumberFromTable_WithHalt(
                                "Number_of_Detector_Components",
                                "Missing Number_of_Detector_Components"
                                + string(" in DetectorConfig table."));
	                            
	if (this->Number_of_Dectector_Components <= 0) {
	
		cout << "You did not define the variable ";
		cout << "Number_of_Detector_Components sufficiently.\n";
		cout << "Please be sure you set it to an integer greater than 0";
		cout << ".\n";
		cout << "Halting execution\n";
		exit(0);
		
	}
	
}

/*
 * DetectorConfigLuaInstance::Initialize_detector_components()
 * 
 * 
 * 
 * */

void DetectorConfigLuaInstance::Initialize_detector_components() {
	
	for (int i = 1; i <= this->Number_of_Dectector_Components;i++) {
	
		//Pop entire stack
		lua_pop(this->L, -1);
		
		string DetectorComponentIndex = ConvertIntToString(i);
		
		cout << "\nDetectorComponent_" + DetectorComponentIndex << ":\n";
		LoadTable("DetectorComponent_" + DetectorComponentIndex);
		          
       /*
        * * Comment
        * 
        * 		Since I've passed true for Halt Execution, I'm going to
        * 		assume that the value that Volume_Type is valid.
        * 
        * */
		this->Components.push_back(WithVolumeGetDetectorComponent(
                           SetSharedAttributes(DetectorComponentIndex)));
		
	}
	cout << "\n";
	
}

SharedAttributes DetectorConfigLuaInstance::SetSharedAttributes(string DetectorComponentIndex) {

	SharedAttributes Attribute;
	string OutputVolumeName;
	
	/*
	 * if DetectorComponentIndex == "0", we are looking at the world
	 * volume. Otherwise we're looking at a regular DetectorComponent
	 * volume.
	 * 
	 * */
	if (DetectorComponentIndex == "0") {
		
		OutputVolumeName = "World";
		
	} else {
	
		OutputVolumeName = "DetectorComponent_" + DetectorComponentIndex;
		
	}


	Attribute.VolumeType = GetStringFromTable_WithHalt("Volume_Type",
		                  "You didn't define an appropriate volume for "
		                  + OutputVolumeName);
		                     
	Attribute.Name = GetStringFromTable_NoHalt("Component_Name",
                                          "Default Component_Name Used",
                                          OutputVolumeName);
                         
	Attribute.Material = GetStringFromTable_WithHalt("Material",
                                        "No Material found."
                                        + string(" Halting Execution"));
                         
	Attribute.Inside = GetStringFromTable_WithHalt("Inside",
                                        "Please define Inside."
                                        + string(" Halting Execution"));
                             
	Attribute.Position = GetG4ThreeVector("Position");
	
	return Attribute;
	
}


DetectorComponent *DetectorConfigLuaInstance::WithVolumeGetDetectorComponent(SharedAttributes Attribute) {
	
	if (Attribute.VolumeType == "Cylinder")
		return MakeDetectorComponent_Cylinder(Attribute);
	else if (Attribute.VolumeType == "Box")
		return MakeDetectorComponent_Box(Attribute);
	
	return NULL;
	
}


/*
 * DetectorConfigLuaInstance::MakeDetectorComponent_Cylinder()
 * 
 * 
 * 
 * 
 * */
 
DetectorComponent_Cylinder *DetectorConfigLuaInstance::MakeDetectorComponent_Cylinder(SharedAttributes Attribute) {     
	                                      
	G4double Inner_Radius = GetNumberFromTable_NoHalt("Inner_Radius",
                                             "No Inner_Radius found."
                                             + string(" Set to 0.0"),
                                             0.0);
                                                                               
	G4double Outer_Radius = GetNumberFromTable_WithHalt("Outer_Radius",
                                             "No Outer_Radius found."
                                        + string(" Halting Execution"));
                                      
	G4double Start_Angle = GetNumberFromTable_NoHalt("Start_Angle",
                                             "No Start_Angle found."
                                             + string(" Set to 0.0"),
                                             0.0);
                                               
	G4double Delta_Angle = GetNumberFromTable_NoHalt("Delta_Angle",
                                             "No Delta_Angle found."
                                             + string(" Set to 360."),
                                             360.);
                                            
	G4double Half_Length = GetNumberFromTable_WithHalt("Half_Length",
                                             "No Half_Length found."
                                        + string(" Halting Execution"));
                                        
                                         
	return new DetectorComponent_Cylinder(Attribute.Name,
                                      Inner_Radius,
                                      Outer_Radius,
                                      Start_Angle,
                                      Delta_Angle,
                                      Half_Length,
                                      Attribute.Position,
                                      Attribute.Material,
                                      Attribute.Inside);
   
}




/*
 * DetectorConfigLuaInstance::MakeDectorComponent_Box()
 * 
 * 
 * 
 * */

DetectorComponent_Box *DetectorConfigLuaInstance::MakeDetectorComponent_Box(SharedAttributes Attribute) {
    
	G4double X = GetNumberFromTable_WithHalt("X", "Did not provide X "+
                                    string("value. Halting Execution"));
	
	G4double Y = GetNumberFromTable_WithHalt("Y", "Did not provide Y "+
                                    string("value. Halting Execution"));
                                     
	G4double Z = GetNumberFromTable_WithHalt("Z", "Did not provide Z "+
                                    string("value. Halting Execution"));
	
	return new DetectorComponent_Box(Attribute.Name, X, Y, Z, 
                                     Attribute.Position, 
                                     Attribute.Material, 
                                     Attribute.Inside);
                                     
}

