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

PrimaryGeneratorAction::PrimaryGeneratorAction(vector<FourVector> *FourVectors,
                                               string DarkGeantOutputPath,
                                               int NumberOfEvents,
                                               DetectorComponent *World) 

 : G4VUserPrimaryGeneratorAction()

{
	
	this->Stepping = new SteppingAction(DarkGeantOutputPath);
	
	this->ParticleGun = new G4ParticleGun(1);
	this->ParticleTable = G4ParticleTable::GetParticleTable();
	
	this->PresentIndex = 0;
	this->FourVectors = FourVectors;
	this->World = World;
	
	this->NumberOfEvents = NumberOfEvents;
	
}

PrimaryGeneratorAction::~PrimaryGeneratorAction() {
	
	delete this->Stepping;
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
	
	if (this->PresentIndex == this->NumberOfEvents)
		return;
	
	this->Stepping->SaveEvent();
	
	int i = this->PresentIndex;
	
	for (size_t prtcle = 0; prtcle < this->FourVectors[i].size(); prtcle++) {

		if (!this->World->WithinVolume(this->FourVectors[i][prtcle].X,
                                     this->FourVectors[i][prtcle].Y,
                                     this->FourVectors[i][prtcle].Z))
        {
		
			continue;
			
		}

		G4ParticleDefinition *Def = GetParticleDefinition(this->FourVectors[i][prtcle]);
		this->FourVectors[i][prtcle].T = this->FourVectors[i][prtcle].E * GeV - Def->GetPDGMass();
		
		this->ParticleGun->SetParticleDefinition(Def);
		this->ParticleGun->SetParticleEnergy(this->FourVectors[i][prtcle].T);
		this->ParticleGun->SetParticlePosition(G4ThreeVector(
                                           this->FourVectors[i][prtcle].X * m,
                                           this->FourVectors[i][prtcle].Y * m,
                                           this->FourVectors[i][prtcle].Z * m));
                                               
		this->ParticleGun->SetParticleMomentumDirection(G4ThreeVector(
                                             this->FourVectors[i][prtcle].P_x,
                                             this->FourVectors[i][prtcle].P_y,
                                             this->FourVectors[i][prtcle].P_z));

		this->ParticleGun->GeneratePrimaryVertex(event);
		
	}
	
	this->PresentIndex++;
	
}

G4ParticleDefinition *PrimaryGeneratorAction::GetParticleDefinition(FourVector vec) {

	//std::cout << vec.ParticleName << "\n";
	G4ParticleDefinition* Def;
	if (vec.ParticleName == "0") {
	
		//Geantino or Optical Photon
		Def = ParticleTable->FindParticle(0);
		
	} else if (atoi(vec.ParticleName.c_str()) != 0) {
		
		Def = ParticleTable->FindParticle(atoi(vec.ParticleName.c_str()));
		
	} else {
	
		Def = ParticleTable->FindParticle(vec.ParticleName);
		
	}
	
	return Def;
	
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
