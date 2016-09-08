/*
 * main.cxx
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

#include "G4UImanager.hh"
#include "G4RunManager.hh"
#include "G4ThreeVector.hh"
#include "G4VisExecutive.hh"
#include "G4VUserDetectorConstruction.hh"

#include "DetectorConstruction.hh"
#include "PhysicsList.hh"
#include "ActionInitialization.hh"

void InitializeRunManager(G4RunManager *runManager);
void InitializeUIManager(G4UImanager *ui);
void InitializeVisManager(G4VisManager *vis);

int main(void) {
	
	G4RunManager *runManager = new G4RunManager();
	G4UImanager  *ui         = G4UImanager::GetUIpointer();
	G4VisManager *vis        = new G4VisExecutive();
	
	InitializeRunManager(runManager);
	InitializeUIManager(ui);
	InitializeVisManager(vis);
	
	/*
	 * 
	 * I will presently not delete anything unless I know it can be
	 * destroyed.
	 * 
	 * */
	
	return 0;
}

void InitializeRunManager(G4RunManager *runManager) {

	runManager->SetUserInitialization(new DetectorConstruction());
	//runManager->SetUserInitialization(new PhysicsList());
	//runManager->SetUserAction(new PrimaryGeneratorAction(""));
	
	runManager->Initialize();
	
}

void InitializeUIManager(G4UImanager *ui) {

	ui->ApplyCommand("/run/verbose 1");
	ui->ApplyCommand("/event/verbose 1");
	ui->ApplyCommand("/tracking/verbose 1");
	
}

void InitializeVisManager(G4VisManager *vis) {

	vis->Initialize();
	
}

