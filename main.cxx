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
	void InitializeVisManager();
	static G4VisManager *vis = new G4VisExecutive();
	
#endif
#ifdef G4UI_USE

	#include "G4UImanager.hh"
	void InitializeUIManager();
	static G4UImanager  *ui = G4UImanager::GetUIpointer();
	
#endif

//User Headers
#include "DetectorConstruction.hh"
#include "PhysicsList.hh"
#include "PrimaryGeneratorAction.hh"
#include "Utilities.hh"

// C & C++ Headers
#include <cstring>
#include <string>
#include <vector>

using std::string;
using std::vector;
using std::cout;
using std::cin;

static vector<G4String> ExecutionVector;
static FourVectorStruct<G4double> *JBStruct = NULL;

//Function Prototypes
void Clean();
void HandleArguments(int argc, char *argv[]);
void InitializeRunManager(G4RunManager *runManager);
void InitializeState();

int main(int argc, char *argv[]) {
	
	if (argc > 1)
		HandleArguments(argc, argv);
	
	InitializeState();
	std::cin.get();
	Clean();
	
	return 0;
}

/*
 * InitializeState
 * 
 * Initializes important runtime variables, calls several important
 * functions that initialize the UI and VIS functions (if compiled in),
 * and changes runtime state depending on user input
 * 
 * 
 * */

void InitializeState() {
	
	G4RunManager *runManager = new G4RunManager();
	InitializeRunManager(runManager);
	
#ifdef G4VIS_USE

	InitializeVisManager();
	
#endif
#ifdef G4UI_USE

	InitializeUIManager();
	if (ExecutionVector.size() != 0)
		cin.get();
	for (size_t i = 0; i < ExecutionVector.size();i++)
		ui->ApplyCommand(ExecutionVector[i]);
		
#endif
	
	if (JBStruct != NULL) {
	
		/*
		 * TODO
		 * 
		 * Implement Functionality
		 * 
		 * */
		
	}
	
}

void Clean() {
	
#ifdef G4UI_USE
	delete ui;
#endif
#ifdef G4VIS_USE
	delete vis;
#endif	

	if (JBStruct != NULL)
		delete JBStruct->array;
	delete JBStruct;
	
}

void InitializeRunManager(G4RunManager *runManager) {

	runManager->SetUserInitialization(new DetectorConstruction());
	runManager->SetUserInitialization(new PhysicsList());
	runManager->SetUserAction(new PrimaryGeneratorAction());
	
	runManager->Initialize();
	
}
#ifdef G4UI_USE
void InitializeUIManager() {

	ui->ApplyCommand("/run/verbose 1");
	ui->ApplyCommand("/event/verbose 1");
	ui->ApplyCommand("/tracking/verbose 1");
	
	ui->ApplyCommand("/control/execute vis.mac");
	
}
#endif

#ifdef G4VIS_USE
void InitializeVisManager() {

	vis->Initialize();
	
}
#endif





struct ArgumentTable {
	
	string name;
	void (*Function)(int argc, char *argv[], int index);
	
};



//Argument Function Prototypes
void Execute_Argument(int argc, char *argv[], int index);
void JBInput_Argument(int argc, char *argv[], int index);



static const int numHandledArguments = 2;
static const ArgumentTable Table[numHandledArguments] =
{{"-execute", &Execute_Argument},
 {"-JBInput", &JBInput_Argument}};



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

void JBInput_Argument(int argc, char *argv[], int index) {

	/*
	 * Output.dat is not a permanent filename in Josh's code, however
	 * I don't see much reason to change it to something else so
	 * I'm going to pretend it's just output.dat always.
	 * 
	 * Subject to change.
	 * 
	 * */
	string filename("output.dat");
	JBStruct = Get_VectorStruct_FromFile<G4double>(filename);
	
}

