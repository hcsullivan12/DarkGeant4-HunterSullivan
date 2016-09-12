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

//Geant4 Headers
#include "G4RunManager.hh"
#include "G4ThreeVector.hh"
#include "G4VUserDetectorConstruction.hh"

#ifdef G4VIS_USE

	#include "G4VisExecutive.hh"
	void InitializeVisManager(G4VisManager *vis);
	
#endif
#ifdef G4UI_USE

	#include "G4UImanager.hh"
	void InitializeUIManager(G4UImanager *ui);
	
#endif

//User Headers
#include "DetectorConstruction.hh"
#include "PhysicsList.hh"
#include "PrimaryGeneratorAction.hh"

// C & C++ Headers
#include <cstring>
#include <string>
#include <vector>

using std::string;
using std::vector;
using std::cout;

static vector<G4String> ExecutionVector;

//Function Prototypes
void HandleArguments(int argc, char *argv[]);
void InitializeRunManager(G4RunManager *runManager);

int main(int argc, char *argv[]) {
	
	if (argc > 1)
		HandleArguments(argc, argv);
	
	G4RunManager *runManager = new G4RunManager();
	InitializeRunManager(runManager);
	
#ifdef G4VIS_USE
	G4VisManager *vis = new G4VisExecutive();
	InitializeVisManager(vis);
#endif
#ifdef G4UI_USE
	G4UImanager  *ui = G4UImanager::GetUIpointer();
	InitializeUIManager(ui);
#endif

	std::cin.get();
	runManager->BeamOn(30);
	std::cin.get();

#ifdef G4UI_USE
	delete ui;
#endif
#ifdef G4VIS_USE
	delete vis;
#endif	
	
	return 0;
}

void InitializeRunManager(G4RunManager *runManager) {

	runManager->SetUserInitialization(new DetectorConstruction());
	runManager->SetUserInitialization(new PhysicsList());
	runManager->SetUserAction(new PrimaryGeneratorAction());
	
	runManager->Initialize();
	
}
#ifdef G4UI_USE
void InitializeUIManager(G4UImanager *ui) {

	ui->ApplyCommand("/run/verbose 1");
	ui->ApplyCommand("/event/verbose 1");
	ui->ApplyCommand("/tracking/verbose 1");
	
	ui->ApplyCommand("/control/execute vis.mac");
	
	for (size_t i = 0; i < ExecutionVector.size();i++)
		ui->ApplyCommand(ExecutionVector[i]);
}
#endif

#ifdef G4VIS_USE
void InitializeVisManager(G4VisManager *vis) {

	vis->Initialize();
	
}
#endif

// String-Function structure
typedef struct {
	
	string name;
	void (*Function)(int argc, char *argv[], int index);
	
} ArgumentTable;


//Argument Function Prototypes
void Execute_Argument(int argc, char *argv[], int index);


//Argument Function table
static const int numHandledArguments = 1;
static const ArgumentTable Table[numHandledArguments] =
{{"-execute", &Execute_Argument}};

/*
 * 
 * Checks each provided runtime argument provided by the user
 * against known runtime arguments and acts accordingly.
 * 
 * */
void HandleArguments(int argc, char *argv[]) {
	
	for (int y = 1;y < argc;y++)
		for (int x = 0;x < numHandledArguments;x++)
			if (strcasecmp(argv[y], Table[x].name.c_str()) == 0)
				Table[x].Function(argc, argv, y);		
		
}

void Execute_Argument(int argc, char *argv[], int index) {

	if ( (index+1) == argc) {
	
		cout << "Did not give a good execution argument";
		return;
		
	}
	
	G4String CharLiteralToString(argv[index + 1]);
	ExecutionVector.push_back("/control/execute " + CharLiteralToString);
	
}

