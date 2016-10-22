/*
 * DetectorConstruction.cxx
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

#include "DetectorConstruction.hh"

// Geant4 Headers
#include "G4Material.hh"
#include "G4PVPlacement.hh"
#include "G4ThreeVector.hh"

using std::cout;


static Material *Air;
static Material *LiquidArgon;

void InitializeMaterials() {
	
	Air         = new Material("G4_AIR");
	LiquidArgon = new Material("Liquid Argon", 18., 39.95 * g/mole,
                                                         1.390 * g/cm3);
	
}

DetectorConstruction::DetectorConstruction() {
	
	this->Air         = new Material("G4_AIR");
    this->LiquidArgon = new Material("LiquidArgon", 18., 39.95 * g/mole,
                                                         1.390 * g/cm3);
	
}

DetectorConstruction::~DetectorConstruction() {



}

G4VPhysicalVolume* DetectorConstruction::Construct() {


	InitializeWorld();
	InitializeDetector();
	InitializePhysicalVolume();
	
	return this->WorldPhysicalVolume;
}

void DetectorConstruction::InitializeWorld() {

	G4double world_hx = 3.0*m;
	G4double world_hy = 1.0*m;
	G4double world_hz = 1.0*m;
	
	this->worldBox = new G4Box("World", world_hx, world_hy, world_hz);
	
	/*
	 * With the defined object, you can create an object with made
	 * out of a material or element. The following code is called a
	 * Logical Volume.
	 * 
	 * Need to specify what Ar and Al are!
	 * 
	 * */
	 
	this->worldLog = new G4LogicalVolume(this->worldBox, 
                                         this->Air->GetMaterialPointer(), 
                                         "World");
	
}

void DetectorConstruction::InitializeDetector() {
	
	/*
	 * Creates a cylinder of radius 60cm, with length (in the z direction)
	 * 50 cm. hz defines a half length.
	 * 
	 * */
	G4double innerRadius = 0.*cm;
	G4double outerRadius = 60.*cm;
	G4double hz = 25.*cm;
	G4double startAngle = 0.*deg;
	G4double spanningAngle = 360.*deg;
	
	this->trackerTube = new G4Tubs("Tracker",
                                    innerRadius,
                                    outerRadius,
                                    hz,
                                    startAngle,
                                    spanningAngle);
									
	/*
	 * With the defined object, you can create an object with made
	 * out of a material or element. The following code is called a
	 * Logical Volume.
	 * 
	 * Need to specify what Ar and Al are!
	 * 
	 * */									
	this->trackerLog = new G4LogicalVolume(this->trackerTube, 
                                           this->LiquidArgon->GetMaterialPointer(),
                                           "Tracker");
	
}

void DetectorConstruction::InitializePhysicalVolume() {
	
	this->WorldPhysicalVolume = new G4PVPlacement(0, G4ThreeVector(), 
                                             this->worldLog, "World",
                                             0, false, 0);
									
	G4VPhysicalVolume *TrackerPhysical = new G4PVPlacement(0, 
                                             G4ThreeVector(0, 0, 0), 
                                             this->trackerLog,
                                             "Detector",
                                             this->worldLog,
                                             false,
                                             0);
	
	if (TrackerPhysical == NULL)
		cout << "Tracker physical volume could not be initialized\n";
	
}

/*
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Class DetectorComponent member functions
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * 
 * */
 
 
 
 
 
 
DetectorComponent::DetectorComponent(G4String Name,
                                     VolumeType Type, 
                                     G4ThreeVector Position,
                                     G4String MaterialString,
                                     G4String Inside) 
{
	
	this->Name = Name;
	this->Type = Type;
	this->Position = Position;
	this->MaterialString = MaterialString;
	this->Inside = Inside;
	// TODO design of Materials must change to accomodate lua config.
	//this->MaterialString
	
}

DetectorComponent::~DetectorComponent() {

	
	
}

/*
 * 
 * TODO
 * 
 * 		It might be fruitful to introduce an array of Material object 
 * 		pointers so that this function can just loop over the objects
 * 
 * */
void DetectorComponent::SetMaterialPointer(G4String MaterialString) {
	
	
	
}


/*
 * 
 * Class DetectorComponent_Cylinder member functions
 * 
 * */
 
DetectorComponent_Cylinder::DetectorComponent_Cylinder(
                                   G4String Name,
                                   G4double InnerRadius,
                                   G4double OuterRadius,
                                   G4double StartAngle,
                                   G4double EndAngle,
                                   G4double HalfLength,
                                   G4ThreeVector Position,
                                   G4String MaterialString,
                                   G4String Inside)
 : DetectorComponent(Name, CYLINDER, Position, MaterialString, Inside)
{
	
	this->InnerRadius = InnerRadius;
	this->OuterRadius = OuterRadius;
	this->StartAngle = StartAngle;
	this->EndAngle = EndAngle;
	
}

DetectorComponent_Cylinder::~DetectorComponent_Cylinder() {
	
	
}


void DetectorComponent_Cylinder::ConstructVolume() {
	
	G4Tubs *VirtualVolume = new G4Tubs(this->Name,
                                       this->InnerRadius * m,
                                       this->OuterRadius * m,
                                       this->HalfLength * m,
                                       this->StartAngle * deg,
                                       this->EndAngle * deg);
	
	this->LogicalVolume = new G4LogicalVolume(VirtualVolume,
                 this->DetectorComponentMaterial->GetMaterialPointer(),
                 this->Name);

}



/*
 * 
 * Class DetectorComponent_Box member functions
 * 
 * */
 
 
 

DetectorComponent_Box::DetectorComponent_Box(
                              G4String Name,
                              G4double x,
                              G4double y,
                              G4double z,
                              G4ThreeVector Position,
                              G4String MaterialString,
                              G4String Inside)
 : DetectorComponent(Name, BOX, Position, MaterialString, Inside) 
{
	
	this->x = x;
	this->y = y;
	this->z = z;
	
}


DetectorComponent_Box::~DetectorComponent_Box() {
	

	
	
}

void DetectorComponent_Box::ConstructVolume() {
	
	G4Box *VirtualVolume = new G4Box(this->Name,
                                     this->x * m,
                                     this->y * m,
                                     this->z * m);
                                     
	this->LogicalVolume = new G4LogicalVolume(VirtualVolume,
                 this->DetectorComponentMaterial->GetMaterialPointer(),
                 this->Name);
	
}





/*
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * class DetectorConstructionV2 member functions
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * 
 * */






DetectorConstructionV2::DetectorConstructionV2(DetectorComponent *World,
                               vector<DetectorComponent *> Components,
                               vector<Material *> Materials)
{

	this->World = World;
	this->Components = Components;
	this->Materials = Materials;
	
}

DetectorConstructionV2::~DetectorConstructionV2() {
	
	
}

G4VPhysicalVolume* DetectorConstructionV2::Construct() {
	
	InitializeWorld();
	InitializeDetectorComponents();
	InitializePhysicalVolume();
	
	return this->WorldPhysicalVolume;
	
}

void DetectorConstructionV2::InitializeWorld() {
	
	FindMaterial(this->World);
	this->World->ConstructVolume();	
                                    
}

void DetectorConstructionV2::InitializeDetectorComponents() {
	
	for (size_t i = 0; i < this->Components.size();i++)
		FindMaterial(this->Components[i]);
	
	for (size_t i = 0; i < this->Components.size();i++)
		this->Components[i]->ConstructVolume();
	
}

void DetectorConstructionV2::InitializePhysicalVolume() {
	
	this->WorldPhysicalVolume = new G4PVPlacement(0, 
                                    G4ThreeVector(0, 0, 0),
                                    this->World->LogicalVolume,
                                    this->World->Name,
                                    0, false, 0);
	
	for (size_t i = 0; i < this->Components.size();i++) {
	
		G4VPhysicalVolume *ComponentPhysical = new G4PVPlacement(0,
                                     this->Components[i]->Position,
                                     this->Components[i]->LogicalVolume,
                                     this->Components[i]->Name,
                                     this->World->LogicalVolume,
                                     false,
                                     0);     
		
		if (ComponentPhysical == NULL)
			cout << "ComponentPhysical STUB\n";
			
		delete ComponentPhysical;
	}
	/*	G4VPhysicalVolume *TrackerPhysical = new G4PVPlacement(0, 
                                             G4ThreeVector(0, 0, 0), 
                                             this->trackerLog,
                                             "Detector",
                                             this->worldLog,
                                             false,
                                             0);*/
	
}

void DetectorConstructionV2::FindMaterial(DetectorComponent *Component) {

	G4String ComponentString = Component->MaterialString;
	for (size_t i = 0;i < this->Materials.size();i++) {
	
		G4String MaterialString = Materials[i]->GetMaterialName();
		if (strcmp(ComponentString.c_str(), MaterialString.c_str()) == 0) {
			
			Component->DetectorComponentMaterial = Materials[i];
			break;
			
		}
		
	}
	cout << "Was not able to find material for ";
	cout << Component->Name;
	cout << ". Please be sure that you have no spelling mistakes and ";
	cout << "be aware that this code is case sensitive.\n";
	cout << "Halting execution.\n";
	
	exit(0);
	
}
