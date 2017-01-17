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

using std::exception;
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
        DetectorComponent_vars LocalAttributes = SetSharedAttributes(
                                           DetectorComponentIndex);
                                           
		this->Components.push_back(WithVolumeGetDetectorComponent(
                                   LocalAttributes));
		
		ApplyRotations(LocalAttributes,
		this->Components[this->Components.size()-1]);
		
		
	}
	cout << "\n";
	
}

DetectorComponent_vars DetectorConfigLuaInstance::SetSharedAttributes(string DetectorComponentIndex) {

	DetectorComponent_vars vars;
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


	vars.VolumeType_str = GetStringFromTable_WithHalt("Volume_Type",
		                  "You didn't define an appropriate volume for "
		                  + OutputVolumeName);
		                     
	vars.Name = GetStringFromTable_NoHalt("Component_Name",
                                          "Default Component_Name Used",
                                          OutputVolumeName);
                         
	vars.MaterialString = GetStringFromTable_WithHalt("Material",
                                        "No Material found."
                                        + string(" Halting Execution"));
                         
	vars.Inside = GetStringFromTable_WithHalt("Inside",
                                        "Please define Inside."
                                        + string(" Halting Execution"));
                             
	vars.Position = GetG4ThreeVector("Position");
	
	
	try {
		
		vars.colour = GetG4ThreeVector("colour");
		
	} catch (string e) {
		
		cout << "Default colour used\n";
		vars.colour = G4Colour(.5, .5, .5);
		lua_pop(this->L, 1);
	}
	
	if (DetectorComponentIndex != "0") {
	
		vars.XRotation = GetNumberFromTable_NoHalt("X_Rotation",
                                                      "X not rotated",
                                                      0.0);
                                                      
		vars.YRotation = GetNumberFromTable_NoHalt("Y_Rotation",
                                                      "Y not rotated",
                                                      0.0);		
                                                      
        vars.ZRotation = GetNumberFromTable_NoHalt("Z_Rotation",
                                                      "Z not rotated",
                                                      0.0);	
	}
	
	return vars;
	
}


DetectorComponent *DetectorConfigLuaInstance::WithVolumeGetDetectorComponent(DetectorComponent_vars vars) {
	
	if (vars.VolumeType_str == "Cylinder")
		return MakeDetectorComponent_Cylinder(vars);
	else if (vars.VolumeType_str == "Box")
		return MakeDetectorComponent_Box(vars);
	else if (vars.VolumeType_str == "Cone")
		return MakeDetectorComponent_Cone(vars);
	else if (vars.VolumeType_str == "Ellipsoid")
		return MakeDetectorComponent_Ellipsoid(vars);
	else if (vars.VolumeType_str == "Elliptical Cone")
		return MakeDetectorComponent_EllipticalCone(vars);
	else if (vars.VolumeType_str == "Elliptical Tube")
		return MakeDetectorComponent_EllipticalTube(vars);
	else if (vars.VolumeType_str == "Hyperbolic Tube")
		return MakeDetectorComponent_HyperbolicTube(vars);
	else if (vars.VolumeType_str == "Parallelepiped")
		return MakeDetectorComponent_Parallelepiped(vars);
	else if (vars.VolumeType_str == "Solid Sphere")
		return MakeDetectorComponent_SolidSphere(vars);
	else if (vars.VolumeType_str == "Spherical Shell")
		return MakeDetectorComponent_SphericalShell(vars);
	else if (vars.VolumeType_str == "Torus")
		return MakeDetectorComponent_Torus(vars);
	else if (vars.VolumeType_str == "Trapezoid")
		return MakeDetectorComponent_Trapezoid(vars);
	else if (vars.VolumeType_str == "Twisted Box")
		return MakeDetectorComponent_TwistedBox(vars);
	else if (vars.VolumeType_str == "Z Twisted Trapezoid")
		return MakeDetectorComponent_ZTwistedTrapezoid(vars);
	
	
	return NULL;
	
}


/*
 * DetectorConfigLuaInstance::MakeDetectorComponent_Cylinder()
 * 
 * 
 * 
 * 
 * */
 
DetectorComponent_Cylinder *DetectorConfigLuaInstance::MakeDetectorComponent_Cylinder(DetectorComponent_vars vars) {     
	
	vars.cylinder = new DetectorComponent_Cylinder_vars;
	vars.cylinder->InnerRadius = GetNumberFromTable_NoHalt("Inner_Radius",
                                             "No Inner_Radius found."
                                             + string(" Set to 0.0"),
                                             0.0);
                                                                               
	vars.cylinder->OuterRadius = GetNumberFromTable_WithHalt("Outer_Radius",
                                             "No Outer_Radius found."
                                        + string(" Halting Execution"));
                                      
	vars.cylinder->StartAngle = GetNumberFromTable_NoHalt("Start_Angle",
                                             "No Start_Angle found."
                                             + string(" Set to 0.0"),
                                             0.0);
                                               
	vars.cylinder->DeltaAngle = GetNumberFromTable_NoHalt("Delta_Angle",
                                             "No Delta_Angle found."
                                             + string(" Set to 360."),
                                             360.);
                                            
	vars.cylinder->HalfLength = GetNumberFromTable_WithHalt("Half_Length",
                                             "No Half_Length found."
                                        + string(" Halting Execution"));
                                        
	
                                        
	return new DetectorComponent_Cylinder(vars);
                                    
   
}




/*
 * DetectorConfigLuaInstance::MakeDectorComponent_Box()
 * 
 * 
 * 
 * */

DetectorComponent_Box *DetectorConfigLuaInstance::MakeDetectorComponent_Box(DetectorComponent_vars vars) {
    
    vars.box = new DetectorComponent_Box_vars;
	vars.box->half_x = GetNumberFromTable_WithHalt("half_X", "Did not provide half_X "+
                                    string("value. Halting Execution"));
	
	vars.box->half_y = GetNumberFromTable_WithHalt("half_Y", "Did not provide half_Y "+
                                    string("value. Halting Execution"));
                                     
	vars.box->half_z = GetNumberFromTable_WithHalt("half_Z", "Did not provide half_Z "+
                                    string("value. Halting Execution"));
	
	return new DetectorComponent_Box(vars);
	
}



/*
 * DetectorConfigLuaInstance::MakeDectorComponent_Cone()
 * 
 * 
 * 
 * */

DetectorComponent_Cone *DetectorConfigLuaInstance::MakeDetectorComponent_Cone(DetectorComponent_vars vars) {
    
    vars.cone = new DetectorComponent_Cone_vars;
	vars.cone->InnerRadiusAtBottom = GetNumberFromTable_NoHalt("Inner_Radius_At_Bottom",
							"No Inner_Radius_At_Bottom found."
							+ string(" Set to 0.0"),
							0.0);
	
	vars.cone->OutsideRadiusAtBottom = GetNumberFromTable_WithHalt("Outside_Radius_At_Bottom",
							"No Outside_Radius_At_Bottom found."
							+ string(" Haulting Execution"));
                                     
	vars.cone->InnerRadiusAtTop = GetNumberFromTable_NoHalt("Inner_Radius_At_Top",
							"No Inner_Radius_At_Top found."
							+ string(" Set to 0.0"),
							0.0);

	vars.cone->OutsideRadiusAtTop = GetNumberFromTable_WithHalt("Outside_Radius_At_Top",
							"No Outside_Radius_At_Top found."
							+ string(" Haulting Execution"));

	vars.cone->HalfLength = GetNumberFromTable_WithHalt("Half_Length",
							"No Half_Length found."
							+ string(" Haulting Execution"));

	vars.cone->StartAngle = GetNumberFromTable_NoHalt("Start_Angle",
							"No Start_Angle found."
							+ string(" Set to 0.0"),
							0.0);

	vars.cone->DeltaAngle = GetNumberFromTable_NoHalt("Delta_Angle",
							"No Delta_Angle found."
							+ string(" Set to 360."),
							360.);
	
	return new DetectorComponent_Cone(vars);

}



/*
 * DetectorConfigLuaInstance::MakeDectorComponent_Ellipsoid()
 * 
 * 
 * 
 * */

DetectorComponent_Ellipsoid *DetectorConfigLuaInstance::MakeDetectorComponent_Ellipsoid(DetectorComponent_vars vars) {
    
    vars.ellipsoid = new DetectorComponent_Ellipsoid_vars;
	vars.ellipsoid->xSemiAxis = GetNumberFromTable_WithHalt("X_Semi_Axis",
						"No X_Semi_Axis found."
						+ string(" Haulting Execution"));

	vars.ellipsoid->ySemiAxis = GetNumberFromTable_WithHalt("Y_Semi_Axis",
						"No Y_Semi_Axis found."
						+ string(" Haulting Execution"));
		
	vars.ellipsoid->zSemiAxis = GetNumberFromTable_WithHalt("Z_Semi_Axis",
						"No Z_Semi_Axis found."
						+ string(" Haulting Execution"));
		
	vars.ellipsoid->zBottom = GetNumberFromTable_WithHalt("Z_Bottom",
						"No Z_Bottom found."
						+ string(" Haulting Execution"));
	
	vars.ellipsoid->zTop = GetNumberFromTable_WithHalt("Z_Top",
						"No Z_Top found."
						+ string(" Haulting Execution"));
	
	return new DetectorComponent_Ellipsoid(vars);
	
}



/*
 * DetectorConfigLuaInstance::MakeDectorComponent_EllipticalCone()
 * 
 * 
 * 
 * */

DetectorComponent_EllipticalCone *DetectorConfigLuaInstance::MakeDetectorComponent_EllipticalCone(DetectorComponent_vars vars) {
    
    vars.elliptical_cone = new DetectorComponent_EllipticalCone_vars;
	vars.elliptical_cone->xSemiAxis = GetNumberFromTable_WithHalt("X_Semi_Axis",
						"No X_Semi_Axis found."
						+ string(" Haulting Execution"));
	
	vars.elliptical_cone->ySemiAxis = GetNumberFromTable_WithHalt("Y_Semi_Axis",
						"No Y_Semi_Axis found."
						+ string(" Haulting Execution"));
		
	vars.elliptical_cone->Height = GetNumberFromTable_WithHalt("Height",
						"No Height found."
						+ string(" Haulting Execution"));
	
	vars.elliptical_cone->zTop = GetNumberFromTable_WithHalt("Z_Top",
						"No Z_Top found."
						+ string(" Haulting Execution"));
	
	return new DetectorComponent_EllipticalCone(vars);
	
}



/*
 * DetectorConfigLuaInstance::MakeDectorComponent_EllipticalTube()
 * 
 * 
 * 
 * */

DetectorComponent_EllipticalTube *DetectorConfigLuaInstance::MakeDetectorComponent_EllipticalTube(DetectorComponent_vars vars) {
    
    vars.elliptical_tube = new DetectorComponent_EllipticalTube_vars;
	vars.elliptical_tube->xHalfLength = GetNumberFromTable_WithHalt("X_Half_Length",
							"No X_Half_Length found."
							+ string(" Haulting Execution"));
	
	vars.elliptical_tube->yHalfLength = GetNumberFromTable_WithHalt("Y_Half_Length",
							"No Y_Half_Length found."
							+ string(" Haulting Execution"));
		
	vars.elliptical_tube->zHalfLength = GetNumberFromTable_WithHalt("Z_Half_Length",
							"No Z_Half_Length found."
							+ string(" Haulting Execution"));
	
	return new DetectorComponent_EllipticalTube(vars);
	
}



/*
 * DetectorConfigLuaInstance::MakeDectorComponent_HyperbolicTube()
 * 
 * 
 * 
 * */

DetectorComponent_HyperbolicTube *DetectorConfigLuaInstance::MakeDetectorComponent_HyperbolicTube(DetectorComponent_vars vars) {
    
    vars.hyperbolic_tube = new DetectorComponent_HyperbolicTube_vars;
	vars.hyperbolic_tube->InnerRadius = GetNumberFromTable_WithHalt("Inner_Radius",
							"No Inner_Radius found."
							+ string(" Haulting Execution"));
	
	vars.hyperbolic_tube->OuterRadius = GetNumberFromTable_WithHalt("Outer_Radius",
							"No Outer_Radius found."
							+ string(" Haulting Execution"));
		
	vars.hyperbolic_tube->InnerRadiusAngle = GetNumberFromTable_WithHalt("Inner_Radius_Angle",
							"Not Inner_Radius_Angle found."
							+ string(" Haulting Execution"));
	
	vars.hyperbolic_tube->OuterRadiusAngle = GetNumberFromTable_WithHalt("Outer_Radius_Angle",
							"No Outer_Radius_Angle found."
							+ string(" Haulting Execution"));

	vars.hyperbolic_tube->zHalfLength = GetNumberFromTable_WithHalt("Z_Half_Length",
							"No Z_Half_Length found."
							+ string(" Haulting Execution"));
	
	return new DetectorComponent_HyperbolicTube(vars);
	
}



/*
 * DetectorConfigLuaInstance::MakeDectorComponent_Parallelepiped()
 * 
 * 
 * 
 * */

DetectorComponent_Parallelepiped *DetectorConfigLuaInstance::MakeDetectorComponent_Parallelepiped(DetectorComponent_vars vars) {
    
    vars.parallelepiped = new DetectorComponent_Parallelepiped_vars;
	vars.parallelepiped->xHalfLength = GetNumberFromTable_WithHalt("X_Half_Length",
							"No X_Half_Length found."
							+ string(" Haulting Execution"));
	
	vars.parallelepiped->yHalfLength = GetNumberFromTable_WithHalt("Y_Half_Length",
							"No Y_Half_Length found."
							+ string(" Haulting Execution"));
		
	vars.parallelepiped->zHalfLength = GetNumberFromTable_WithHalt("Z_Half_Length",
							"No Z_Half_Length found."
							+ string(" Haulting Execution"));

	vars.parallelepiped->AngleOfXZFaces = GetNumberFromTable_WithHalt("Angle_Of_XZ_Faces",
							"No Angle_Of_XZ_Faces found."
							+ string(" Haulting Execution"));
	
	vars.parallelepiped->PolarAngleOfXYFaces = GetNumberFromTable_WithHalt("Polar_Angle_Of_XY_Faces",
							"No Polar_Angle_Of_XY_Faces found."
							+ string(" Haulting Execution"));

	vars.parallelepiped->AzimuthalAngleOfXYFaces = GetNumberFromTable_WithHalt("Azimuthal_Angle_Of_XY_Faces",
							"No Azimuthal_Angle_Of_XY_Faces found."
							+ string(" Haulting Execution"));
	
	return new DetectorComponent_Parallelepiped(vars);
	
}




/*
 * DetectorConfigLuaInstance::MakeDectorComponent_SolidSphere()
 * 
 * 
 * 
 * */

DetectorComponent_SolidSphere *DetectorConfigLuaInstance::MakeDetectorComponent_SolidSphere(DetectorComponent_vars vars) {
    
    vars.solid_sphere = new DetectorComponent_SolidSphere_vars;
	vars.solid_sphere->Radius = GetNumberFromTable_WithHalt("Radius",
						"No Radius found."
						+ string(" Haulting Execution"));
	
	return new DetectorComponent_SolidSphere(vars);
	
}



/*
 * DetectorConfigLuaInstance::MakeDectorComponent_SphericalShell()
 * 
 * 
 * 
 * */

DetectorComponent_SphericalShell *DetectorConfigLuaInstance::MakeDetectorComponent_SphericalShell(DetectorComponent_vars vars) {
    
    vars.spherical_shell = new DetectorComponent_SphericalShell_vars;
	vars.spherical_shell->InnerRadius = GetNumberFromTable_NoHalt("Inner_Radius",
						"No Inner_Radius found."
						+ string(" Set to 0.0"),
						0.0);
	
	vars.spherical_shell->OuterRadius = GetNumberFromTable_WithHalt("Outer_Radius",
						"No Outer_Radius found."
						+ string(" Haulting Execution"));
		
	vars.spherical_shell->PhiStart = GetNumberFromTable_NoHalt("Phi_Start",
						"No Phi_Start found."
						+ string(" Set to 0.0"),
						0.0);

	vars.spherical_shell->DeltaPhi = GetNumberFromTable_NoHalt("Delta_Phi",
						"No Delta_Phi found."
						+ string(" Set to 360."),
						360.);
	
	vars.spherical_shell->ThetaStart = GetNumberFromTable_NoHalt("Theta_Start",
						"No Theta_Start found."
						+ string(" Set to 0.0"),
						0.0);

	vars.spherical_shell->DeltaTheta = GetNumberFromTable_NoHalt("Delta_Theta",
						"No Delta_Theta found."
						+ string(" Set to 360."),
						360.);
	
	return new DetectorComponent_SphericalShell(vars);
	
}


/*
 * DetectorConfigLuaInstance::MakeDectorComponent_Torus()
 * 
 * 
 * 
 * */

DetectorComponent_Torus *DetectorConfigLuaInstance::MakeDetectorComponent_Torus(DetectorComponent_vars vars) {
    
    vars.torus = new DetectorComponent_Torus_vars;
	vars.torus->InnerRadius = GetNumberFromTable_NoHalt("Inner_Radius",
						"No Inner_Radius found."
						+ string(" Set to 0.0"),
						0.0);

	vars.torus->OuterRadius = GetNumberFromTable_WithHalt("Outer_Radius",
						"No Outer_Radius found."
						+ string(" Haulting Execution"));

	vars.torus->SweepingRadius = GetNumberFromTable_WithHalt("Sweeping_Radius",
						"No Sweeping_Radius found."
						+ string(" Haulting Execution"));

	vars.torus->PhiStart = GetNumberFromTable_NoHalt("Phi_Start",
						"No Phi_Start found."
						+ string(" Set to 0.0"),
						0.0);

	vars.torus->DeltaPhi = GetNumberFromTable_NoHalt("Delta_Phi",
						"No Delta_Phi found."
						+ string(" Set to 360."),
						360.);
	
	return new DetectorComponent_Torus(vars);
	
}



/*
 * DetectorConfigLuaInstance::MakeDectorComponent_Trapezoid()
 * 
 * 
 * 
 * */

DetectorComponent_Trapezoid *DetectorConfigLuaInstance::MakeDetectorComponent_Trapezoid(DetectorComponent_vars vars) {
    
    vars.trapezoid = new DetectorComponent_Trapezoid_vars;
	vars.trapezoid->xHalfLengthAtBottom = GetNumberFromTable_WithHalt("X_Half_Length_At_Bottom",
							"No X_Half_Length_At_Bottom found."
							+ string(" Haulting Execution"));

	vars.trapezoid->xHalfLengthAtTop = GetNumberFromTable_WithHalt("X_Half_Length_At_Top",
							"No X_Half_Length_At_Top found."
							+ string(" Haulting Execution"));

	vars.trapezoid->yHalfLengthAtBottom = GetNumberFromTable_WithHalt("Y_Half_Length_At_Bottom",
							"No Y_Half_Length_At_Bottom found."
							+ string(" Haulting Execution"));

	vars.trapezoid->yHalfLengthAtTop = GetNumberFromTable_WithHalt("Y_Half_Length_At_Top",
							"No Y_Half_Length_At_Top found."
							+ string(" Haulting Execution"));

	vars.trapezoid->zHalfLength = GetNumberFromTable_WithHalt("Z_Half_Length",
							"No Z_Half_Length found."
							+ string(" Haulting Execution"));
	
	return new DetectorComponent_Trapezoid(vars);
	
}



/*
 * DetectorConfigLuaInstance::MakeDectorComponent_TwistedBox()
 * 
 * 
 * 
 * */

DetectorComponent_TwistedBox *DetectorConfigLuaInstance::MakeDetectorComponent_TwistedBox(DetectorComponent_vars vars) {
    
    vars.twisted_box = new DetectorComponent_TwistedBox_vars;
	vars.twisted_box->TwistingAngle = GetNumberFromTable_WithHalt("Twisting_Angle",
						"No Twisting_Angle found."
						+ string(" Haulting Execution"));

	vars.twisted_box->xHalfLength = GetNumberFromTable_WithHalt("X_Half_Length",
						"No X_Half_Length found."
						+ string(" Haulting Execution"));

	vars.twisted_box->yHalfLength = GetNumberFromTable_WithHalt("Y_Half_Length",
						"No Y_Half_Length found."
						+ string(" Haulting Execution"));

	vars.twisted_box->zHalfLength = GetNumberFromTable_WithHalt("Z_Half_Length",
						"No Z_Half_Length found."
						+ string(" Haulting Execution")); 
	
	return new DetectorComponent_TwistedBox(vars);
	
}



/*
 * DetectorConfigLuaInstance::MakeDectorComponent_ZTwistedTrapezoid()
 * 
 * 
 * 
 * */

DetectorComponent_ZTwistedTrapezoid *DetectorConfigLuaInstance::MakeDetectorComponent_ZTwistedTrapezoid(DetectorComponent_vars vars) {
     
	vars.z_twisted_trapezoid = new DetectorComponent_ZTwistedTrapezoid_vars;
	vars.z_twisted_trapezoid->xHalfLengthAtBottom = GetNumberFromTable_WithHalt("X_Half_Length_At_Bottom",
							"No X_Half_Length_At_Bottom found."
							+ string(" Haulting Execution"));

	vars.z_twisted_trapezoid->xHalfLengthAtTop = GetNumberFromTable_WithHalt("X_Half_Length_At_Top",
							"No X_Half_Length_At_Top found."
							+ string(" Haulting Execution"));

	vars.z_twisted_trapezoid->yHalfLengthAtBottom = GetNumberFromTable_WithHalt("Y_Half_Length_At_Bottom",
							"No Y_Half_Length_At_Bottom found."
							+ string(" Haulting Execution"));

	vars.z_twisted_trapezoid->yHalfLengthAtTop = GetNumberFromTable_WithHalt("Y_Half_Length_At_Top",
							"No Y_Half_Length_At_Top found."
							+ string(" Haulting Execution"));

	vars.z_twisted_trapezoid->zHalfLength = GetNumberFromTable_WithHalt("Z_Half_Length",
							"No Z_Half_Length found."
							+ string(" Haulting Execution"));

	vars.z_twisted_trapezoid->TwistingAngle = GetNumberFromTable_NoHalt("Twisting_Angle",
							"No Twisting_Angle found."
							+ string(" Set to 0.0"),
							0.0);
	
	return new DetectorComponent_ZTwistedTrapezoid(vars);
	
}


void DetectorConfigLuaInstance::ApplyRotations(DetectorComponent_vars vars, DetectorComponent* Component) {

	Component->RotateX(vars.XRotation * deg);
	Component->RotateY(vars.YRotation * deg);
	Component->RotateZ(vars.ZRotation * deg);
	
}

