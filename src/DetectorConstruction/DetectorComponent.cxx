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

DetectorComponent::DetectorComponent(DetectorComponent_vars vars) 
{
	
	this->Name           = vars.Name;
	this->Type           = vars.Type;
	this->Position       = vars.Position;
	this->MaterialString = vars.MaterialString;
	this->Inside         = vars.Inside;
	this->colour         = vars.colour;
	
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

void DetectorComponent::ApplyColor() {
	
	this->attributes = new G4VisAttributes(this->colour);
	LogicalVolume->SetVisAttributes(attributes);
	
}

DetectorComponent::~DetectorComponent() {

	delete this->attributes;
	
}

