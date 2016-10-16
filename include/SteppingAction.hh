/*
 * SteppingAction.hh
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


#ifndef STEPPINGACTION_H
#define STEPPINGACTION_H


// Geant4 Headers
#include "G4Step.hh"
#include "G4UserSteppingAction.hh"

// C/C++ Headers
#include <cstdio>

class SteppingAction : public G4UserSteppingAction {
	
	
	/*
	 * Class Member Variables
	 * 
	 * */
	 
	private:
		
		FILE *fp;
		int CurrentEvent;
	
	/*
	 * Class Member Functions
	 * 
	 * */
	 
	public:
	
		SteppingAction();
		~SteppingAction();
		
		void UserSteppingAction(const G4Step *Step);
		void SaveEvent();
		
	private:
	
		void SaveBanner(const G4Step *Step, G4Track *Track);
		void SaveFormat();
		void Save0StepData(const G4Step *Step);
		void SaveStepData(const G4Step *Step, G4Track *Track);
	
};

#endif

