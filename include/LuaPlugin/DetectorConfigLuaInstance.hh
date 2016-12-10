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
#include "DetectorComponentCone.hh"
#include "DetectorComponentEllipsoid.hh"
#include "DetectorComponentEllipticalCone.hh"
#include "DetectorComponentEllipticalTube.hh"
#include "DetectorComponentHyperbolicTube.hh"
#include "DetectorComponentParallelepiped.hh"
#include "DetectorComponentSolidSphere.hh"
#include "DetectorComponentSphericalShell.hh"
#include "DetectorComponentTorus.hh"


#include "Utilities.hh"

struct SharedAttributes {

	G4String Name;
	G4String Inside;
	G4String Material;
	G4String VolumeType;
	G4ThreeVector Position;
	
	G4double XRotation;
	G4double YRotation;
	G4double ZRotation;
	
};


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
		vector<DetectorComponent_Cone> ConeComponents;
		vector<DetectorComponent_Ellipsoid> EllipsoidComponents;
		vector<DetectorComponent_EllipticalCone> EllipticalConeComponents;
		vector<DetectorComponent_EllipticalTube> EllipticalTubeComponents;
		vector<DetectorComponent_HyperbolicTube> HyperbolicTubeComponents;
		vector<DetectorComponent_Parallelepiped> ParallelepipedComponents;
		vector<DetectorComponent_SolidSphere> SolidSphereComponents;
		vector<DetectorComponent_SphericalShell> SphericalShellComponents;
		vector<DetectorComponent_Torus> TorusComponents;
		
		
		
		
	
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
		
		void ApplyRotations(SharedAttributes Attribute, DetectorComponent* Component);
		
		SharedAttributes SetSharedAttributes(string DetectorComponentIndex);
		
		DetectorComponent *WithVolumeGetDetectorComponent(SharedAttributes Attribute);
		
		DetectorComponent_Cylinder *MakeDetectorComponent_Cylinder(SharedAttributes Attribute);
		DetectorComponent_Box *MakeDetectorComponent_Box(SharedAttributes Attribute);
		DetectorComponent_Cone *MakeDetectorComponent_Cone(SharedAttributes Attribute);
		DetectorComponent_Ellipsoid *MakeDetectorComponent_Ellipsoid(SharedAttributes Attribute);
		DetectorComponent_EllipticalCone *MakeDetectorComponent_EllipticalCone(SharedAttributes Attribute);
		DetectorComponent_EllipticalTube *MakeDetectorComponent_EllipticalTube(SharedAttributes Attribute);
		DetectorComponent_HyperbolicTube *MakeDetectorComponent_HyperbolicTube(SharedAttributes Attribute);
		DetectorComponent_Parallelepiped *MakeDetectorComponent_Parallelepiped(SharedAttributes Attribute);
		DetectorComponent_SolidSphere *MakeDetectorComponent_SolidSphere(SharedAttributes Attribute);
		DetectorComponent_SphericalShell *MakeDetectorComponent_SphericalShell(SharedAttributes Attribute);
		DetectorComponent_Torus *MakeDetectorComponent_Torus(SharedAttributes Attribute);
		
		
	/*
	 * 
	 * TODO
	 * 
	 * Finish class
	 * 
	 * */
	
};

#endif

