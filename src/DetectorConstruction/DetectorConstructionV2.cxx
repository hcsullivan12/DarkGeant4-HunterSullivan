/*
 * DetectorConstructionV2.cxx
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

//User Headers
#include "DetectorConstructionV2.hh"

// Geant4 Headers
#include "G4PVPlacement.hh"

using namespace std;

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

/*
 * Construct()
 * 
 * * Description
 * 
 * 		...
 * 
 * */

G4VPhysicalVolume* DetectorConstructionV2::Construct() {
	
	InitializeWorld();
	InitializeDetectorComponents();
	InitializePhysicalVolume();
	
	return this->WorldPhysicalVolume;
	
}

/*
 * InitializeWorld
 * 
 * * Description
 * 
 * 		...
 * 
 * */

void DetectorConstructionV2::InitializeWorld() {
	
	FindMaterial(this->World);
	this->World->ConstructVolume();	
	
	this->World->SetEMField("World");
                                    
}

/*
 * InitializeDetectorComponents()
 * 
 * * Description
 * 
 * 		...
 * 
 * */

void DetectorConstructionV2::InitializeDetectorComponents() {
	
	for (size_t i = 0; i < this->Components.size();i++) {
		
		FindMaterial(this->Components[i]);
		this->Components[i]->ConstructVolume();
		std::cout << this->Components[i]->Name << std::endl;
		this->Components[i]->SetEMField(this->Components[i]->Name);
		this->Components[i]->ApplyVisEffects();
		
	}
	
}

/*
 * InitializePhysicalVolume()
 * 
 * * Description
 * 
 * 		...
 * 
 * */

void DetectorConstructionV2::InitializePhysicalVolume() {

	this->WorldPhysicalVolume = new G4PVPlacement(0, 
                                    G4ThreeVector(0, 0, 0),
                                    this->World->LogicalVolume,
                                    this->World->Name,
                                    0, false, 0);
	
	for (size_t i = 0; i < this->Components.size();i++) {
	
		new G4PVPlacement(this->Components[i]->Transform,
                          this->Components[i]->LogicalVolume,
                          this->Components[i]->Name,
                          this->World->LogicalVolume,
                          false,
                          0);
			
	}
	
}

/*
 * FindMaterial(DetectorComponent *Component)
 * 
 * * Description
 * 
 * 		...
 * 
 * */

void DetectorConstructionV2::FindMaterial(DetectorComponent *Component) {

	G4String ComponentString = Component->MaterialString;
	for (size_t i = 0;i < this->Materials.size();i++) {
	
		G4String MaterialString = Materials[i]->GetMaterialName();
		if (ComponentString == MaterialString) {
			
			Component->DetectorComponentMaterial = Materials[i];
			return;
			
		}
		
	}
	cout << "Was not able to find material for ";
	cout << Component->Name;
	cout << ". Please be sure that you have no spelling mistakes and ";
	cout << "be aware that this code is case sensitive.\n";
	cout << "Halting execution.\n";
	
	exit(0);
	
}

