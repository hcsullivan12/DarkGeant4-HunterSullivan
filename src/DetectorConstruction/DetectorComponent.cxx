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

//User Headers
#include "DetectorComponent.hh"
#include "UniformEMField.hh"

//Geant4 Headers
#include "G4FieldManager.hh"
#include "G4TransportationManager.hh"
#include "G4EqEMFieldWithSpin.hh"
#include "G4ClassicalRK4.hh"
#include "G4MagIntegratorStepper.hh"
#include "G4ChordFinder.hh"
#include "G4PropagatorInField.hh"
#include "G4SystemOfUnits.hh"

DetectorComponent::DetectorComponent(DetectorComponent_vars vars) 
{
	
	this->Name           = vars.Name;
	this->Type           = vars.Type;
	this->Position       = vars.Position;
	this->MagneticField  = vars.MagneticField;
	this->ElectricField  = vars.ElectricField;
	this->MaterialString = vars.MaterialString;
	this->Inside         = vars.Inside;
	this->colour         = vars.colour;
	this->Wireframe      = vars.Wireframe;
	
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

void DetectorComponent::ApplyVisEffects() {
	
	this->attributes = new G4VisAttributes(this->colour);
	this->attributes->SetForceWireframe(this->Wireframe);
	LogicalVolume->SetVisAttributes(this->attributes);
	
}

void DetectorComponent::SetEMField(string Name) {
	
	UniformEMField* Field = new UniformEMField(this->MagneticField, this->ElectricField);
	G4FieldManager* FieldMgr;

	if (Name == "World") {
		std::cout << "DOING WORLD!\n";
		std::cout <<this->Name << std::endl;
		FieldMgr = G4TransportationManager::GetTransportationManager()->GetFieldManager();
	}
	else {
		std::cout << "Doing the ELSE!\n";
		FieldMgr = new G4FieldManager(Field);
	}
		
	if (this->ElectricField.x() != 0 || this->ElectricField.y() != 0 || this->ElectricField.z() != 0) {
			FieldMgr->SetFieldChangesEnergy(true);
	}
		
	//Set Field (allLocal pushes field to daughter volumes)
	G4bool allLocal = true;
	this->LogicalVolume->SetFieldManager(FieldMgr, allLocal);
	FieldMgr->SetDetectorField(Field);
	G4double FieldValue[6];
	G4double Point[4];
	Point[0] = 0.0;
	Point[2] = 0.0;
	Point[3] = 0.0;		
	this->LogicalVolume->GetFieldManager()->GetDetectorField()->GetFieldValue(Point, FieldValue);
		
	//Parameter setting for accuracy
	G4EqEMFieldWithSpin* Equation = new G4EqEMFieldWithSpin(Field);
	G4double minStep = 0.01*mm;
	G4MagIntegratorStepper* Stepper = new G4ClassicalRK4(Equation,12);
	G4ChordFinder* ChordFinder = new G4ChordFinder((G4MagneticField*)Field,minStep,Stepper);
	G4double deltaChord        = 3.0*mm;
	ChordFinder->SetDeltaChord( deltaChord );
	G4double deltaOneStep      = 0.01*mm;
	FieldMgr->SetAccuraciesWithDeltaOneStep(deltaOneStep);
	G4double deltaIntersection = 0.1*mm;
	FieldMgr->SetDeltaIntersection(deltaIntersection);
	G4TransportationManager* TransportManager = G4TransportationManager::GetTransportationManager();
	TransportManager->SetFieldManager(FieldMgr);
	G4PropagatorInField* FieldPropagator = TransportManager->GetPropagatorInField();
	G4double epsMin            = 2.5e-7*mm;
	G4double epsMax            = 0.05*mm;
	FieldPropagator->SetMinimumEpsilonStep(epsMin);
	FieldPropagator->SetMaximumEpsilonStep(epsMax);
	FieldMgr->SetChordFinder(ChordFinder);	

}

DetectorComponent::~DetectorComponent() {

	delete this->attributes;
	
}

