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
        SharedAttributes LocalAttributes = SetSharedAttributes(
                                           DetectorComponentIndex);
                                           
		this->Components.push_back(WithVolumeGetDetectorComponent(
                                   LocalAttributes));
		
		ApplyRotations(LocalAttributes,
		this->Components[this->Components.size()-1]);
		
		
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
	
	if (DetectorComponentIndex != "0") {
	
		Attribute.XRotation = GetNumberFromTable_NoHalt("X_Rotation",
                                                      "X not rotated",
                                                      0.0);
                                                      
		Attribute.YRotation = GetNumberFromTable_NoHalt("Y_Rotation",
                                                      "Y not rotated",
                                                      0.0);		
                                                      
        Attribute.ZRotation = GetNumberFromTable_NoHalt("Z_Rotation",
                                                      "Z not rotated",
                                                      0.0);	
	}
	
	return Attribute;
	
}


DetectorComponent *DetectorConfigLuaInstance::WithVolumeGetDetectorComponent(SharedAttributes Attribute) {
	
	if (Attribute.VolumeType == "Cylinder")
		return MakeDetectorComponent_Cylinder(Attribute);
	else if (Attribute.VolumeType == "Box")
		return MakeDetectorComponent_Box(Attribute);
	else if (Attribute.VolumeType == "Cone")
		return MakeDetectorComponent_Cone(Attribute);
	else if (Attribute.VolumeType == "Ellipsoid")
		return MakeDetectorComponent_Ellipsoid(Attribute);
	else if (Attribute.VolumeType == "Elliptical Cone")
		return MakeDetectorComponent_EllipticalCone(Attribute);
	else if (Attribute.VolumeType == "Elliptical Tube")
		return MakeDetectorComponent_EllipticalTube(Attribute);
	else if (Attribute.VolumeType == "Hyperbolic Tube")
		return MakeDetectorComponent_HyperbolicTube(Attribute);
	else if (Attribute.VolumeType == "Parallelepiped")
		return MakeDetectorComponent_Parallelepiped(Attribute);
	else if (Attribute.VolumeType == "Solid Sphere")
		return MakeDetectorComponent_SolidSphere(Attribute);
	else if (Attribute.VolumeType == "Spherical Shell")
		return MakeDetectorComponent_SphericalShell(Attribute);
	else if (Attribute.VolumeType == "Torus")
		return MakeDetectorComponent_Torus(Attribute);
	else if (Attribute.VolumeType == "Trapezoid")
		return MakeDetectorComponent_Trapezoid(Attribute);
	else if (Attribute.VolumeType == "Twisted Box")
		return MakeDetectorComponent_TwistedBox(Attribute);
	else if (Attribute.VolumeType == "Z Twisted Trapezoid")
		return MakeDetectorComponent_ZTwistedTrapezoid(Attribute);
	
	
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
                                        
	return new DetectorComponent_Cylinder(
                                          Attribute.Name,
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
	
	return new DetectorComponent_Box(
                                     Attribute.Name, X, Y, Z, 
                                     Attribute.Position, 
                                     Attribute.Material, 
                                     Attribute.Inside);
	
}



/*
 * DetectorConfigLuaInstance::MakeDectorComponent_Cone()
 * 
 * 
 * 
 * */

DetectorComponent_Cone *DetectorConfigLuaInstance::MakeDetectorComponent_Cone(SharedAttributes Attribute) {
    
	G4double Inner_Radius_At_Bottom = GetNumberFromTable_NoHalt("Inner_Radius_At_Bottom",
							"No Inner_Radius_At_Bottom found."
							+ string(" Set to 0.0"),
							0.0);
	
	G4double Outside_Radius_At_Bottom = GetNumberFromTable_WithHalt("Outside_Radius_At_Bottom",
							"No Outside_Radius_At_Bottom found."
							+ string(" Haulting Execution"));
                                     
	G4double Inner_Radius_At_Top = GetNumberFromTable_NoHalt("Inner_Radius_At_Top",
							"No Inner_Radius_At_Top found."
							+ string(" Set to 0.0"),
							0.0);

	G4double Outside_Radius_At_Top = GetNumberFromTable_WithHalt("Outside_Radius_At_Top",
							"No Outside_Radius_At_Top found."
							+ string(" Haulting Execution"));

	G4double Half_Length = GetNumberFromTable_WithHalt("Half_Length",
							"No Half_Length found."
							+ string(" Haulting Execution"));

	G4double Start_Angle = GetNumberFromTable_NoHalt("Start_Angle",
							"No Start_Angle found."
							+ string(" Set to 0.0"),
							0.0);

	G4double Delta_Angle = GetNumberFromTable_NoHalt("Delta_Angle",
							"No Delta_Angle found."
							+ string(" Set to 360."),
							360.);
	
	return new DetectorComponent_Cone(
					Attribute.Name,
					Inner_Radius_At_Bottom,
					Outside_Radius_At_Bottom,
					Inner_Radius_At_Top,
					Outside_Radius_At_Top,
					Half_Length,
					Start_Angle,
					Delta_Angle,	 
                                     	Attribute.Position, 
                                     	Attribute.Material, 
                                     	Attribute.Inside);

}



/*
 * DetectorConfigLuaInstance::MakeDectorComponent_Ellipsoid()
 * 
 * 
 * 
 * */

DetectorComponent_Ellipsoid *DetectorConfigLuaInstance::MakeDetectorComponent_Ellipsoid(SharedAttributes Attribute) {
    
	G4double X_Semi_Axis = GetNumberFromTable_WithHalt("X_Semi_Axis",
						"No X_Semi_Axis found."
						+ string(" Haulting Execution"));
	
	G4double Y_Semi_Axis = GetNumberFromTable_WithHalt("Y_Semi_Axis",
						"No Y_Semi_Axis found."
						+ string(" Haulting Execution"));
		
	G4double Z_Semi_Axis = GetNumberFromTable_WithHalt("Z_Semi_Axis",
						"No Z_Semi_Axis found."
						+ string(" Haulting Execution"));
		
	G4double Z_Bottom = GetNumberFromTable_WithHalt("Z_Bottom",
						"No Z_Bottom found."
						+ string(" Haulting Execution"));
	
	G4double Z_Top = GetNumberFromTable_WithHalt("Z_Top",
						"No Z_Top found."
						+ string(" Haulting Execution"));
	
	return new DetectorComponent_Ellipsoid(
					Attribute.Name,
					X_Semi_Axis,
					Y_Semi_Axis,
					Z_Semi_Axis,
					Z_Bottom,
					Z_Top,
                                     	Attribute.Position, 
                                     	Attribute.Material, 
                                     	Attribute.Inside);
	
}



/*
 * DetectorConfigLuaInstance::MakeDectorComponent_EllipticalCone()
 * 
 * 
 * 
 * */

DetectorComponent_EllipticalCone *DetectorConfigLuaInstance::MakeDetectorComponent_EllipticalCone(SharedAttributes Attribute) {
    
	G4double X_Semi_Axis = GetNumberFromTable_WithHalt("X_Semi_Axis",
						"No X_Semi_Axis found."
						+ string(" Haulting Execution"));
	
	G4double Y_Semi_Axis = GetNumberFromTable_WithHalt("Y_Semi_Axis",
						"No Y_Semi_Axis found."
						+ string(" Haulting Execution"));
		
	G4double Height = GetNumberFromTable_WithHalt("Height",
						"No Height found."
						+ string(" Haulting Execution"));
	
	G4double Z_Top = GetNumberFromTable_WithHalt("Z_Top",
						"No Z_Top found."
						+ string(" Haulting Execution"));
	
	return new DetectorComponent_EllipticalCone(
					Attribute.Name,
					X_Semi_Axis,
					Y_Semi_Axis,
					Height,
					Z_Top,
                                     	Attribute.Position, 
                                     	Attribute.Material, 
                                     	Attribute.Inside);
	
}



/*
 * DetectorConfigLuaInstance::MakeDectorComponent_EllipticalTube()
 * 
 * 
 * 
 * */

DetectorComponent_EllipticalTube *DetectorConfigLuaInstance::MakeDetectorComponent_EllipticalTube(SharedAttributes Attribute) {
    
	G4double X_Half_Length = GetNumberFromTable_WithHalt("X_Half_Length",
							"No X_Half_Length found."
							+ string(" Haulting Execution"));
	
	G4double Y_Half_Length = GetNumberFromTable_WithHalt("Y_Half_Length",
							"No Y_Half_Length found."
							+ string(" Haulting Execution"));
		
	G4double Z_Half_Length = GetNumberFromTable_WithHalt("Z_Half_Length",
							"No Z_Half_Length found."
							+ string(" Haulting Execution"));
	
	return new DetectorComponent_EllipticalTube(
					Attribute.Name,
					X_Half_Length,
					Y_Half_Length,
					Z_Half_Length,
                                     	Attribute.Position, 
                                     	Attribute.Material, 
                                     	Attribute.Inside);
	
}



/*
 * DetectorConfigLuaInstance::MakeDectorComponent_HyperbolicTube()
 * 
 * 
 * 
 * */

DetectorComponent_HyperbolicTube *DetectorConfigLuaInstance::MakeDetectorComponent_HyperbolicTube(SharedAttributes Attribute) {
    
	G4double Inner_Radius = GetNumberFromTable_WithHalt("Inner_Radius",
							"No Inner_Radius found."
							+ string(" Haulting Execution"));
	
	G4double Outer_Radius = GetNumberFromTable_WithHalt("Outer_Radius",
							"No Outer_Radius found."
							+ string(" Haulting Execution"));
		
	G4double Inner_Radius_Angle = GetNumberFromTable_WithHalt("Inner_Radius_Angle",
							"Not Inner_Radius_Angle found."
							+ string(" Haulting Execution"));
	
	G4double Outer_Radius_Angle = GetNumberFromTable_WithHalt("Outer_Radius_Angle",
							"No Outer_Radius_Angle found."
							+ string(" Haulting Execution"));

	G4double Z_Half_Length = GetNumberFromTable_WithHalt("Z_Half_Length",
							"No Z_Half_Length found."
							+ string(" Haulting Execution"));
	
	return new DetectorComponent_HyperbolicTube(
					Attribute.Name,
					Inner_Radius,
					Outer_Radius,
					Inner_Radius_Angle,
					Outer_Radius_Angle,
					Z_Half_Length,
                                     	Attribute.Position, 
                                     	Attribute.Material, 
                                     	Attribute.Inside);
	
}



/*
 * DetectorConfigLuaInstance::MakeDectorComponent_Parallelepiped()
 * 
 * 
 * 
 * */

DetectorComponent_Parallelepiped *DetectorConfigLuaInstance::MakeDetectorComponent_Parallelepiped(SharedAttributes Attribute) {
    
	G4double X_Half_Length = GetNumberFromTable_WithHalt("X_Half_Length",
							"No X_Half_Length found."
							+ string(" Haulting Execution"));
	
	G4double Y_Half_Length = GetNumberFromTable_WithHalt("Y_Half_Length",
							"No Y_Half_Length found."
							+ string(" Haulting Execution"));
		
	G4double Z_Half_Length = GetNumberFromTable_WithHalt("Z_Half_Length",
							"No Z_Half_Length found."
							+ string(" Haulting Execution"));

	G4double Angle_Of_XZ_Faces = GetNumberFromTable_WithHalt("Angle_Of_XZ_Faces",
							"No Angle_Of_XZ_Faces found."
							+ string(" Haulting Execution"));
	
	G4double Polar_Angle_Of_XY_Faces = GetNumberFromTable_WithHalt("Polar_Angle_Of_XY_Faces",
							"No Polar_Angle_Of_XY_Faces found."
							+ string(" Haulting Execution"));

	G4double Azimuthal_Angle_Of_XY_Faces = GetNumberFromTable_WithHalt("Azimuthal_Angle_Of_XY_Faces",
							"No Azimuthal_Angle_Of_XY_Faces found."
							+ string(" Haulting Execution"));
	
	return new DetectorComponent_Parallelepiped(
					Attribute.Name,
					X_Half_Length,
					Y_Half_Length,
					Z_Half_Length,
					Angle_Of_XZ_Faces,
					Polar_Angle_Of_XY_Faces,
					Azimuthal_Angle_Of_XY_Faces,
                                     	Attribute.Position, 
                                     	Attribute.Material, 
                                     	Attribute.Inside);
	
}




/*
 * DetectorConfigLuaInstance::MakeDectorComponent_SolidSphere()
 * 
 * 
 * 
 * */

DetectorComponent_SolidSphere *DetectorConfigLuaInstance::MakeDetectorComponent_SolidSphere(SharedAttributes Attribute) {
    
	G4double Radius = GetNumberFromTable_WithHalt("Radius",
						"No Radius found."
						+ string(" Haulting Execution"));
	
	return new DetectorComponent_SolidSphere(
					Attribute.Name,
					Radius,
                                     	Attribute.Position, 
                                     	Attribute.Material, 
                                     	Attribute.Inside);
	
}



/*
 * DetectorConfigLuaInstance::MakeDectorComponent_SphericalShell()
 * 
 * 
 * 
 * */

DetectorComponent_SphericalShell *DetectorConfigLuaInstance::MakeDetectorComponent_SphericalShell(SharedAttributes Attribute) {
    
	G4double Inner_Radius = GetNumberFromTable_NoHalt("Inner_Radius",
						"No Inner_Radius found."
						+ string(" Set to 0.0"),
						0.0);
	
	G4double Outer_Radius = GetNumberFromTable_WithHalt("Outer_Radius",
						"No Outer_Radius found."
						+ string(" Haulting Execution"));
		
	G4double Phi_Start = GetNumberFromTable_NoHalt("Phi_Start",
						"No Phi_Start found."
						+ string(" Set to 0.0"),
						0.0);

	G4double Delta_Phi = GetNumberFromTable_NoHalt("Delta_Phi",
						"No Delta_Phi found."
						+ string(" Set to 360."),
						360.);
	
	G4double Theta_Start = GetNumberFromTable_NoHalt("Theta_Start",
						"No Theta_Start found."
						+ string(" Set to 0.0"),
						0.0);

	G4double Delta_Theta = GetNumberFromTable_NoHalt("Delta_Theta",
						"No Delta_Theta found."
						+ string(" Set to 360."),
						360.);
	
	return new DetectorComponent_SphericalShell(
					Attribute.Name,
					Inner_Radius,
					Outer_Radius,
					Phi_Start,
					Delta_Phi,
					Theta_Start,
					Delta_Theta,
                                     	Attribute.Position, 
                                     	Attribute.Material, 
                                     	Attribute.Inside);
	
}


/*
 * DetectorConfigLuaInstance::MakeDectorComponent_Torus()
 * 
 * 
 * 
 * */

DetectorComponent_Torus *DetectorConfigLuaInstance::MakeDetectorComponent_Torus(SharedAttributes Attribute) {
    
	G4double Inner_Radius = GetNumberFromTable_NoHalt("Inner_Radius",
						"No Inner_Radius found."
						+ string(" Set to 0.0"),
						0.0);

	G4double Outer_Radius = GetNumberFromTable_WithHalt("Outer_Radius",
						"No Outer_Radius found."
						+ string(" Haulting Execution"));

	G4double Sweeping_Radius = GetNumberFromTable_WithHalt("Sweeping_Radius",
						"No Sweeping_Radius found."
						+ string(" Haulting Execution"));

	G4double Phi_Start = GetNumberFromTable_NoHalt("Phi_Start",
						"No Phi_Start found."
						+ string(" Set to 0.0"),
						0.0);

	G4double Delta_Phi = GetNumberFromTable_NoHalt("Delta_Phi",
						"No Delta_Phi found."
						+ string(" Set to 360."),
						360.);
	
	return new DetectorComponent_Torus(
					Attribute.Name,
					Inner_Radius,
					Outer_Radius,
					Sweeping_Radius,
					Phi_Start,
					Delta_Phi,
                                     	Attribute.Position, 
                                     	Attribute.Material, 
                                     	Attribute.Inside);
	
}



/*
 * DetectorConfigLuaInstance::MakeDectorComponent_Trapezoid()
 * 
 * 
 * 
 * */

DetectorComponent_Trapezoid *DetectorConfigLuaInstance::MakeDetectorComponent_Trapezoid(SharedAttributes Attribute) {
    
	G4double X_Half_Length_At_Bottom = GetNumberFromTable_WithHalt("X_Half_Length_At_Bottom",
							"No X_Half_Length_At_Bottom found."
							+ string(" Haulting Execution"));

	G4double X_Half_Length_At_Top = GetNumberFromTable_WithHalt("X_Half_Length_At_Top",
							"No X_Half_Length_At_Top found."
							+ string(" Haulting Execution"));

	G4double Y_Half_Length_At_Bottom = GetNumberFromTable_WithHalt("Y_Half_Length_At_Bottom",
							"No Y_Half_Length_At_Bottom found."
							+ string(" Haulting Execution"));

	G4double Y_Half_Length_At_Top = GetNumberFromTable_WithHalt("Y_Half_Length_At_Top",
							"No Y_Half_Length_At_Top found."
							+ string(" Haulting Execution"));

	G4double Z_Half_Length = GetNumberFromTable_WithHalt("Z_Half_Length",
							"No Z_Half_Length found."
							+ string(" Haulting Execution"));
	
	return new DetectorComponent_Trapezoid(
					Attribute.Name,
					X_Half_Length_At_Bottom,
					X_Half_Length_At_Top,
					Y_Half_Length_At_Bottom,
					Y_Half_Length_At_Top,
					Z_Half_Length,
                                     	Attribute.Position, 
                                     	Attribute.Material, 
                                     	Attribute.Inside);
	
}



/*
 * DetectorConfigLuaInstance::MakeDectorComponent_TwistedBox()
 * 
 * 
 * 
 * */

DetectorComponent_TwistedBox *DetectorConfigLuaInstance::MakeDetectorComponent_TwistedBox(SharedAttributes Attribute) {
    
	G4double Twisting_Angle = GetNumberFromTable_WithHalt("Twisting_Angle",
						"No Twisting_Angle found."
						+ string(" Haulting Execution"));

	G4double X_Half_Length = GetNumberFromTable_WithHalt("X_Half_Length",
						"No X_Half_Length found."
						+ string(" Haulting Execution"));

	G4double Y_Half_Length = GetNumberFromTable_WithHalt("Y_Half_Length",
						"No Y_Half_Length found."
						+ string(" Haulting Execution"));

	G4double Z_Half_Length = GetNumberFromTable_WithHalt("Z_Half_Length",
						"No Z_Half_Length found."
						+ string(" Haulting Execution")); 
	
	return new DetectorComponent_TwistedBox(
					Attribute.Name,
					Twisting_Angle,
					X_Half_Length,
					Y_Half_Length,
					Z_Half_Length,
                                     	Attribute.Position, 
                                     	Attribute.Material, 
                                     	Attribute.Inside);
	
}



/*
 * DetectorConfigLuaInstance::MakeDectorComponent_ZTwistedTrapezoid()
 * 
 * 
 * 
 * */

DetectorComponent_ZTwistedTrapezoid *DetectorConfigLuaInstance::MakeDetectorComponent_ZTwistedTrapezoid(SharedAttributes Attribute) {
     
	G4double X_Half_Length_At_Bottom = GetNumberFromTable_WithHalt("X_Half_Length_At_Bottom",
							"No X_Half_Length_At_Bottom found."
							+ string(" Haulting Execution"));

	G4double X_Half_Length_At_Top = GetNumberFromTable_WithHalt("X_Half_Length_At_Top",
							"No X_Half_Length_At_Top found."
							+ string(" Haulting Execution"));

	G4double Y_Half_Length_At_Bottom = GetNumberFromTable_WithHalt("Y_Half_Length_At_Bottom",
							"No Y_Half_Length_At_Bottom found."
							+ string(" Haulting Execution"));

	G4double Y_Half_Length_At_Top = GetNumberFromTable_WithHalt("Y_Half_Length_At_Top",
							"No Y_Half_Length_At_Top found."
							+ string(" Haulting Execution"));

	G4double Z_Half_Length = GetNumberFromTable_WithHalt("Z_Half_Length",
							"No Z_Half_Length found."
							+ string(" Haulting Execution"));

	G4double Twisting_Angle = GetNumberFromTable_NoHalt("Twisting_Angle",
							"No Twisting_Angle found."
							+ string(" Set to 0.0"),
							0.0);
	
	return new DetectorComponent_ZTwistedTrapezoid(
					Attribute.Name,
					X_Half_Length_At_Bottom,
					X_Half_Length_At_Top,
					Y_Half_Length_At_Bottom,
					Y_Half_Length_At_Top,
					Z_Half_Length,
					Twisting_Angle,
                                     	Attribute.Position, 
                                     	Attribute.Material, 
                                     	Attribute.Inside);
	
}


void DetectorConfigLuaInstance::ApplyRotations(SharedAttributes Attribute, DetectorComponent* Component) {

	Component->RotateX(Attribute.XRotation * deg);
	Component->RotateY(Attribute.YRotation * deg);
	Component->RotateZ(Attribute.ZRotation * deg);
	
}

