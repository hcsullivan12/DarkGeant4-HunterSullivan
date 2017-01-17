/*
 * DetectorComponent.hh
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

#ifndef DETECTORCOMPONENT_HH
#define DETECTORCOMPONENT_HH

class G4VSolid;
class G4LogicalVolume;
class G4VPhysicalVolume;
class G4Material;

//Geant4 Headers
#include "G4LogicalVolume.hh"
#include "G4VisAttributes.hh"
#include "G4RotationMatrix.hh"
#include "G4Transform3D.hh"
#include "G4ThreeVector.hh"

// C/C++ headers
#include <vector>

//User Headers
#include "Material.hh"

enum VolumeType {

	BOX = 0,
	CYLINDER,
	CONE,
	ELLIPSOID,
	ELLIPTICAL_CONE,
	ELLIPTICAL_TUBE,
	HYPERBOLIC_TUBE,
	PARALLELEPIPED,
	SOLID_SPHERE,
	SPHERICAL_SHELL,
	TETRAHEDRA,
	TORUS,
	TRAPEZOID,
	TWISTED_BOX,
	Z_TWISTED_TRAPEZOID
	
};

struct DetectorComponent_Box_vars {
	
	G4double half_x;
	G4double half_y;
	G4double half_z;
	
};

struct DetectorComponent_Cone_vars {
	
	G4double InnerRadiusAtBottom;
	G4double OutsideRadiusAtBottom;
	G4double InnerRadiusAtTop;
	G4double OutsideRadiusAtTop;
	G4double HalfLength;
	G4double StartAngle;
	G4double DeltaAngle;
	
};

struct DetectorComponent_Cylinder_vars {
	
	G4double InnerRadius;
	G4double OuterRadius;
	G4double StartAngle;
	G4double HalfLength;
	G4double DeltaAngle;
	
};

struct DetectorComponent_Ellipsoid_vars {
	
	G4double xSemiAxis;
	G4double ySemiAxis;
	G4double zSemiAxis;
	G4double zBottom;
	G4double zTop;
	
};

struct DetectorComponent_EllipticalCone_vars {

	G4double xSemiAxis;
	G4double ySemiAxis;
	G4double Height;
	G4double zTop;	
	
};

struct DetectorComponent_EllipticalTube_vars {

	G4double xHalfLength;
	G4double yHalfLength;
	G4double zHalfLength;
	
};

struct DetectorComponent_HyperbolicTube_vars {
	
	G4double InnerRadius;
	G4double OuterRadius;
	G4double InnerRadiusAngle;
	G4double OuterRadiusAngle;
	G4double zHalfLength;
	
};

struct DetectorComponent_Parallelepiped_vars {

	G4double xHalfLength;
	G4double yHalfLength;
	G4double zHalfLength;
	G4double AngleOfXZFaces;
	G4double PolarAngleOfXYFaces;
	G4double AzimuthalAngleOfXYFaces;
	
};

struct DetectorComponent_SolidSphere_vars {

	G4double Radius;
	
};

struct DetectorComponent_SphericalShell_vars {

	G4double InnerRadius;
	G4double OuterRadius;
	G4double PhiStart;
	G4double DeltaPhi;
	G4double ThetaStart;
	G4double DeltaTheta;
	
};
struct DetectorComponent_Tetrahedra_vars {
	
	G4ThreeVector Point1;
	G4ThreeVector Point2;
	G4ThreeVector Point3;
	G4ThreeVector Point4;
	
};

struct DetectorComponent_Torus_vars {

	G4double InnerRadius;
	G4double OuterRadius;
	G4double SweepingRadius;
	G4double PhiStart;
	G4double DeltaPhi;
	
};

struct DetectorComponent_Trapezoid_vars {

	G4double xHalfLengthAtBottom;
	G4double xHalfLengthAtTop;
	G4double yHalfLengthAtBottom;
	G4double yHalfLengthAtTop;
	G4double zHalfLength;
	
};

struct DetectorComponent_TwistedBox_vars {

	G4double TwistingAngle;
	G4double xHalfLength;
	G4double yHalfLength;
	G4double zHalfLength;
	
};

struct DetectorComponent_ZTwistedTrapezoid_vars {

	G4double xHalfLengthAtBottom;
	G4double xHalfLengthAtTop;
	G4double yHalfLengthAtBottom;
	G4double yHalfLengthAtTop;
	G4double zHalfLength;
	G4double TwistingAngle;	
	
};

struct DetectorComponent_vars {
	
	G4String Name;
	G4String VolumeType_str;
	G4String MaterialString;
	G4String Inside;
	
	VolumeType Type;
	
	G4ThreeVector Position;
	G4Colour colour;
	G4LogicalVolume *LogicalVolume;
	Material *DetectorComponentMaterial;
	
	G4double XRotation;
	G4double YRotation;
	G4double ZRotation;
	
	//G4Color
	
	DetectorComponent_Box_vars *box;
	DetectorComponent_Cone_vars *cone;
	DetectorComponent_Cylinder_vars *cylinder;
	DetectorComponent_Ellipsoid_vars *ellipsoid;
	DetectorComponent_EllipticalCone_vars *elliptical_cone;
	DetectorComponent_EllipticalTube_vars *elliptical_tube;
	DetectorComponent_HyperbolicTube_vars *hyperbolic_tube;
	DetectorComponent_Parallelepiped_vars *parallelepiped;
	DetectorComponent_SolidSphere_vars *solid_sphere;
	DetectorComponent_SphericalShell_vars *spherical_shell;
	DetectorComponent_Tetrahedra_vars *tetrahedra;
	DetectorComponent_Torus_vars *torus;
	DetectorComponent_Trapezoid_vars *trapezoid;
	DetectorComponent_TwistedBox_vars *twisted_box;
	DetectorComponent_ZTwistedTrapezoid_vars *z_twisted_trapezoid;
	
};

class DetectorComponent {
	
	/*
	 * 
	 * Class member variables
	 * 
	 * */
	public:
	
		G4String Name;
		G4String Inside;
		G4String MaterialString;
		
		VolumeType Type;
		
		G4Colour colour;
		G4ThreeVector Position;
		G4LogicalVolume *LogicalVolume;
		G4VisAttributes *attributes;
		
		G4RotationMatrix RotationMatrix;
		G4Transform3D Transform;
		
		Material *DetectorComponentMaterial;
	
	/*
	 * 
	 * Class member functions
	 * 
	 * */
	public:
	
		DetectorComponent(DetectorComponent_vars vars);
		~DetectorComponent();
		
		virtual void ConstructVolume() {;}
		
		void ApplyColor();
		
		void RotateX(double delta);
		void RotateY(double delta);
		void RotateZ(double delta);
	
};

#endif
