/*
 * PrimaryGeneratorAction.cxx
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


#include "PrimaryGeneratorAction.hh"

#include "G4SystemOfUnits.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction(vector<FourVector> FourVectors, string DarkGeantOutputPath) 

 : G4VUserPrimaryGeneratorAction()

{
	
	this->Stepping = new SteppingAction(DarkGeantOutputPath);
	
	this->ParticleGun = new G4ParticleGun(1);
	ParticleTable = G4ParticleTable::GetParticleTable();
	
	this->PresentIndex = 0;
	this->FourVectors = FourVectors;
	
}

PrimaryGeneratorAction::~PrimaryGeneratorAction() {
	
	delete this->ParticleGun;
	
}

/*
 * GeneratePrimaries(G4Event *event)
 * 
 * * Description
 * 
 * 		...
 * 
 * */

void PrimaryGeneratorAction::GeneratePrimaries(G4Event *event) {
	
	if (this->PresentIndex == (int)this->FourVectors.size())
		return;
	
	this->Stepping->SaveEvent();
	
	int i = this->PresentIndex;
	this->ParticleGun->SetParticleDefinition(
	                   ParticleTable->FindParticle(
	                   this->FourVectors[i].ParticleName));
	                     
	this->ParticleGun->SetParticleEnergy(this->FourVectors[i].T * GeV);
	
	this->ParticleGun->SetParticlePosition(G4ThreeVector(
                                           this->FourVectors[i].X * m,
                                           this->FourVectors[i].Y * m,
                                           this->FourVectors[i].Z * m));
                                               
	this->ParticleGun->SetParticleMomentumDirection(G4ThreeVector(
                                             this->FourVectors[i].P_x,
                                             this->FourVectors[i].P_y,
                                             this->FourVectors[i].P_z));
	
	this->PresentIndex++;
	this->ParticleGun->GeneratePrimaryVertex(event);
	
}


/*
 * GetSteppingAction()
 * 
 * * Comment
 * 
 * 		This code is very ad hoc at the moment. It's
 * 		literally the only way I can think of introducing
 * 		"Event = %d" lines in the outputted DarkGeantOutput.dat file
 * 
 * */
 
SteppingAction *PrimaryGeneratorAction::GetSteppingAction() {
	
	return this->Stepping;
	
}
