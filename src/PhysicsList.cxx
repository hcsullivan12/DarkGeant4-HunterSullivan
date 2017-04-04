/*
 * PhysicsList.cxx
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

#include "PhysicsList.hh"

#include "G4ParticleDefinition.hh"

//Particle Constructors
#include "G4LeptonConstructor.hh"
#include "G4BaryonConstructor.hh"
#include "G4MesonConstructor.hh"
#include "G4BosonConstructor.hh"

//Process Related Headers
#include "G4VProcess.hh"
#include "G4ProcessManager.hh"


PhysicsList::PhysicsList() {
	
	
	
}

PhysicsList::~PhysicsList() {
	
	
	
}

void PhysicsList::ConstructParticle() {
	
	G4BaryonConstructor::ConstructParticle();
	G4MesonConstructor::ConstructParticle();
	G4BosonConstructor::ConstructParticle();
	G4LeptonConstructor::ConstructParticle();
	
}

//Hadron Headers
#include "G4HadronElasticProcess.hh"
#include "G4HadronCaptureProcess.hh"

//Proton Headers
#include "G4ProtonInelasticProcess.hh"

//Muon Headers
#include "G4MuMultipleScattering.hh"
#include "G4MuIonisation.hh" 
#include "G4MuBremsstrahlung.hh" 
#include "G4MuPairProduction.hh" 


typedef struct {
	
	G4String Name;
	void (*Function)(G4ProcessManager *);
	
} FunctionTable;

//Function Prototypes
void Particle_Gamma(G4ProcessManager *pm);
void Particle_Electron(G4ProcessManager *pm);
void Particle_Proton(G4ProcessManager *pm);
void Particle_Muon(G4ProcessManager *pm);

static const int NumRecordsInTable = 5;

static FunctionTable Table[NumRecordsInTable] = 
{{"gamma" ,  &Particle_Gamma},
 {"e-"    ,  &Particle_Electron},
 {"proton",  &Particle_Proton},
 {"mu+"   ,  &Particle_Muon},
 {"mu-"   ,  &Particle_Muon}};

void PhysicsList::ConstructProcess() {
	
	/*
	 * Mandatory function call. Describes a particle's motion in
	 * space and time.
	 * 
	 * */
	AddTransportation();
	
	/*
	theParticleIterator->reset();
	
	while ((*theParticleIterator)()) {
	
		G4ParticleDefinition *particle = theParticleIterator->value();
		G4ProcessManager *pm = particle->GetProcessManager();
		G4String particleName = particle->GetParticleName();
		
		//A bit of indirection leads to cleaner code overall.
		for (int i = 0; i < NumRecordsInTable;i++)
			if (particleName == Table[i].Name)
				Table[i].Function(pm);
			
		
	}
	*/
	
}

void Particle_Gamma(G4ProcessManager *pm) {
	
	
	
}

void Particle_Electron(G4ProcessManager *pm) {
	
	
	
}

void Particle_Proton(G4ProcessManager *pm) {
	
	
	
}

void Particle_Muon(G4ProcessManager *pm) {

	pm->AddProcess(new G4MuMultipleScattering(), -1, 1, 1);
	pm->AddProcess(new G4MuIonisation(), -1, 2, 2);
	
}
