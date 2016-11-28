/*
 * DetectorComponent.cxx
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

#include "DetectorComponent.hh"

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
	
	this->RotationMatrix = G4RotationMatrix();
	this->Transform = G4Transform3D(this->RotationMatrix, Position);
	
}

void DetectorComponent::RotateX(double delta) {
	
	this->RotationMatrix.rotateX(delta);
	this->Transform = G4Transform3D(this->RotationMatrix, Position);
	
}

void DetectorComponent::RotateY(double delta) {
	
	this->RotationMatrix.rotateY(delta);
	this->Transform = G4Transform3D(this->RotationMatrix, Position);
	
}

void DetectorComponent::RotateZ(double delta) {
	
	this->RotationMatrix.rotateZ(delta);
	this->Transform = G4Transform3D(this->RotationMatrix, Position);
	
}

DetectorComponent::~DetectorComponent() {

	
	
}

