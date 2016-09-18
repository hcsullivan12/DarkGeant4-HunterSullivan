/*
 * PrimaryGeneratorAction.hh
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


#ifndef PRIMARYGENERATORACTION_H
#define PRIMARYGENERATORACTION_H

#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ThreeVector.hh"


class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction {
	
	public:
	
		PrimaryGeneratorAction();
		PrimaryGeneratorAction(G4int NumParticles,
                               G4String ParticleName,
                               G4double Energy,
                               G4ThreeVector Position,
                               G4ThreeVector MomentumDirection);
		~PrimaryGeneratorAction();
		
		void GeneratePrimaries(G4Event *event);
		
	private:
	
		G4ParticleGun *ParticleGun;
	
};

#endif

