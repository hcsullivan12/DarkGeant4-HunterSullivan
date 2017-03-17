/*
 * SteppingAction.cxx
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


// User Headers
#include "SteppingAction.hh"

// Geant4 Headers
#include "G4Track.hh"
#include "G4VProcess.hh"

SteppingAction::SteppingAction(string DarkGeantOutputLocation)
: G4UserSteppingAction()
{
	
	this->fp = fopen(DarkGeantOutputLocation.c_str(), "w");
	
	if (this->fp == NULL) {
	
		printf("Was not able to open DarkGeantOutputLocation\n");
		printf("File received = %s\n", DarkGeantOutputLocation.c_str());
		exit(1);
		
	}
	
	this->CurrentEvent = 1;
	
}

SteppingAction::~SteppingAction() {
	
	fclose(this->fp);
	
}

/*
 * UserSteppingAction(const G4Step* Step)
 * 
 * * Description
 * 
 * 		This function is automatically called by Geant4 during
 * 		each step taken in a simulation. This function is used to
 * 		save step data.
 * 
 * */

void SteppingAction::UserSteppingAction(const G4Step* Step) {
	
	G4Track *Track = Step->GetTrack();
	
	if (Track->GetCurrentStepNumber() == 1) {
	
		SaveBanner(Step, Track);
		SaveFormat();
		Save0StepData(Step);
		
	}
	SaveStepData(Step, Track);
	
}

/*
 * SaveEvent()
 * 
 * * Description
 * 
 * 		Saves "\nEvent = <event_number>\n" to DarkGeantOutput.dat and
 * 		increments the this->CurrentEvent variable by one.
 * 
 * */

void SteppingAction::SaveEvent() {
	
	fprintf(this->fp,"\nEvent = %d\n", this->CurrentEvent);
	this->CurrentEvent++;
	
}

/*
 * SaveBanner(const G4Step *Step, G4Track *Track)
 * 
 * * Description
 * 
 * 		Saves a banner not unlike the Geant4 banner at the start
 * 		of each event.
 * 
 * 
 * */

void SteppingAction::SaveBanner(const G4Step *Step, G4Track *Track) {
	
	fprintf(this->fp, "*********************************************\n");
	fprintf(this->fp, "* G4Track Information: Particle = %s,", 
	Track->GetDefinition()->GetParticleName().c_str());
	
	fprintf(this->fp, " Track ID = %d,", Track->GetTrackID());
	fprintf(this->fp, " Parent ID = %d\n", Track->GetParentID());
	fprintf(this->fp, "*********************************************\n");
	
}

/*
 * SaveFormat()
 * 
 * * Description
 * 
 * 		Another portion of the banner that specifies which columns are
 *		which.
 * 
 * * Comment
 * 
 * 		Technically this should be part of the banner, however to
 * 		break the code up into digestible chunks, it felt appropriate
 * 		to place this portion here.
 * 
 * */

void SteppingAction::SaveFormat() {
	
	fprintf(this->fp,"%-5s","Step#");
	fprintf(this->fp,"%25s","X(mm)");
	fprintf(this->fp,"%25s","Y(mm)");
	fprintf(this->fp,"%25s","Z(mm)");
	fprintf(this->fp,"%25s","KinE(MeV)");
	fprintf(this->fp,"%25s","dE(MeV)");
	fprintf(this->fp,"%25s","StepLeng");
	fprintf(this->fp,"%25s","TrackLeng");
	fprintf(this->fp,"%20s","NextVolume");
	fprintf(this->fp,"%20s","ProcName\n");
	
}

/*
 * Save0StepData(const G4Step *Step)
 * 
 * * Description
 * 
 * 		Saves the step data for the very first step taking by a particle
 * 		in DarkGeantOutput.dat
 * 
 * * Comment
 * 
 * 		The reason why this function and SaveStepData are split is
 * 		because by default Geant4 starts with step #1 instead of step
 * 		zero. So in order to get the step #0 data, I have to use
 * 		a complete different set of functions i.e GetPreStepPoint();
 * 
 * 		Unfortunately PreStepPoint does not have all the variables
 * 		as a normal StepPoint, but since track length/steplength etc.
 * 		should be zero, it's not necessary for those variables to exist.
 * 
 * */

void SteppingAction::Save0StepData(const G4Step *Step) {
	
	G4StepPoint *PreStepPoint = Step->GetPreStepPoint();
	
	fprintf(this->fp,"%-5s","0");
	fprintf(this->fp,"%25.15f", PreStepPoint->GetPosition().x());
	fprintf(this->fp,"%25.15f", PreStepPoint->GetPosition().y());
	fprintf(this->fp,"%25.15f", PreStepPoint->GetPosition().z());
	fprintf(this->fp,"%25.15f", PreStepPoint->GetKineticEnergy());
	fprintf(this->fp,"%25s","0.000000000000000");
	fprintf(this->fp,"%25s","0.000000000000000");
	fprintf(this->fp,"%25s","0.000000000000000");
	fprintf(this->fp,"%20s","Detector");      
	fprintf(this->fp,"%20s","InitStep\n");
}

/*
 * SaveStepData(const G4Step *Step, G4Track *Track)
 * 
 * * Description
 * 
 * 		Saves the step data for step #'s > 0.
 * 
 * 
 * */

void SteppingAction::SaveStepData(const G4Step *Step, G4Track *Track) {
	
	fprintf(this->fp,"%-5d", Track->GetCurrentStepNumber());
	fprintf(this->fp, "%25.15f", Track->GetPosition().x());
	fprintf(this->fp, "%25.15f", Track->GetPosition().y());
	fprintf(this->fp, "%25.15f", Track->GetPosition().z());
	fprintf(this->fp, "%25.15f", Track->GetKineticEnergy());
	fprintf(this->fp, "%25.15f", Step->GetTotalEnergyDeposit());
	fprintf(this->fp, "%25.15f", Step->GetStepLength());
	fprintf(this->fp, "%25.15f", Track->GetTrackLength());
	
	/*
	 * If the volume exists, save which volume the particle is presently
	 * traversing through, otherwise it's OutOfWorld.
	 * 
	 * */
	
	if (Track->GetNextVolume())
		fprintf(this->fp,"%20s", Track->GetNextVolume()->GetName().c_str());
	else
		fprintf(this->fp,"%20s","OutOfWorld");
	
	/*
	 * If the process is defined, i.e GetPorcessDefinedStep != 0,
	 * then it writes out what process is it.
	 * 
	 * Otherwise the program writes out "User Limit" as some default
	 * process. This was taken from Geant4
	 * 
	 * */
	
	G4StepPoint *PostStepPoint = Step->GetPostStepPoint();
	if (PostStepPoint->GetProcessDefinedStep() != 0) {
		
		fprintf(this->fp,"%19s\n",
		PostStepPoint->GetProcessDefinedStep()->GetProcessName().c_str());
		
	} else {
	
		fprintf(this->fp,"%19s","UserLimit\n");
		
	}
}
