/*
 * DetectorConstruction.hh
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

#ifndef DETECTORCONSTRUCTION_H
#define DETECTORCONSTRUCTION_H

class G4VSolid;
class G4LogicalVolume;
class G4VPhysicalVolume;
class G4Material;

//Geant4 Headers
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"

#include "G4ThreeVector.hh"
#include "G4VUserDetectorConstruction.hh"

//User Headers
#include "Material.hh"

class DetectorConstruction : public G4VUserDetectorConstruction 
{

	public:
	
		DetectorConstruction();
		~DetectorConstruction();
		
		G4VPhysicalVolume* Construct();
		
	private:
	
		G4Box *worldBox;
		G4Tubs *trackerTube;
		
		G4LogicalVolume *worldLog;
		G4LogicalVolume *trackerLog;
		
		Material *Air;
		Material *LiquidArgon;
	
		void InitializeWorld();
		void InitializeDetector();
		void InitializePhysicalSpace();
		
};

#endif
