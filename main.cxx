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

#ifdef G4VIS_USE

	#include "G4VisExecutive.hh"
	void InitializeVisManager();
	static G4VisManager *vis;
	
#endif
#ifdef G4UI_USE

	#include "G4UImanager.hh"
	void InitializeUIManager();
	static G4UImanager  *ui;
	
#endif

//User Headers
#include "DetectorConstructionV2.hh"
#include "PhysicsList.hh"
#include "PrimaryGeneratorAction.hh"
#include "Utilities.hh"

#include "LuaInstance.hh"
#include "ConfigLuaInstance.hh"
#include "DetectorConfigLuaInstance.hh"
#include "MaterialConfigLuaInstance.hh"
#include "ParticlesConfigLuaInstance.hh"

#include "SteppingAction.hh"

// C & C++ Headers
#include <cstring>
#include <ctime>
#include <string>
#include <vector>

/* 
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * namespaces
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * 
 * */
using std::string;
using std::vector;
using std::cout;
using std::cin;
using std::endl;

/*
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Static variables
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * 
 * */

// Runtime Argument variables
static const string VersionString = "0.4 \"Fermi\"";
static bool TerminalOutput = true;
static bool ShowVis = false;

static int NumberOfThreads = 1;

static string           Module = "config";
static vector<G4String> ExecutionVector;

// Misc variables
static ConfigLuaInstance         *ConfigFileInstance = NULL;
static DetectorConfigLuaInstance *DetectorConfigFileInstance = NULL;
static MaterialConfigLua         *MaterialConfigFileInstance = NULL;
static ParticlesConfigLua        *ParticleConfigFileInstance = NULL;
static DetectorConstructionV2 *Detector = NULL;
static G4RunManager *runManager;

/*
 *  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *  Function Prototypes
 *  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * 
 * */

void HandleArguments(int argc, char *argv[]);
void InitializeState();
void InitializeLuaInstances();
void InitializeRunManager(G4RunManager *runManager);

// Relies on DetectorConfigLua instance
void InitializeDetectorGeometry();
void Clean();

int main(int argc, char *argv[]) {
	
	cout << "DarkGeant4 version " << VersionString << "\n";
	cout << "Written by Emma Davenport (UT Arlington)\n";
	
	HandleArguments(argc, argv);
	InitializeState();
	
	cout << "Done! Press enter to exit\n";
	std::cin.get();
	Clean();
	
	return 0;
}

/*
 * InitializeState
 * 
 * * Description
 * 
 * 		Initializes important runtime variables, calls several important
 * 		functions that initialize the UI and VIS functions 
 * 		(if compiled in), and changes runtime state depending on user 
 * 		input.
 * 
 * 
 * */

void InitializeState() {
	
	runManager = new G4RunManager();
	
	InitializeLuaInstances();
	InitializeDetectorGeometry();
	InitializeRunManager(runManager);
#ifdef G4VIS_USE
	if (ShowVis == true)
		InitializeVisManager();
#endif
#ifdef G4UI_USE
	InitializeUIManager();
	if (ExecutionVector.size() != 0)
		cin.get();
	for (size_t i = 0; i < ExecutionVector.size();i++)
		ui->ApplyCommand(ExecutionVector[i]);		
#endif
	
	std::cout << endl;
	std::cout << "Press enter to start simulation" << endl;
	std::cin.get();
	clock_t start_time = time(NULL);
	cout << "BeamOn!\n";
	runManager->BeamOn(ParticleConfigFileInstance->NumberOfEvents);
	
	double time_elapsed = difftime(time(NULL), start_time);
	
	cout << "Elapsed time = " << time_elapsed << "s\n";
	cout << "Elapsed time = " << time_elapsed/60.0 << "min\n";
	
}

/*
 * Clean()
 * 
 * * Description
 * 
 * 		...
 * 
 * */

void Clean() {
	
#ifdef G4UI_USE
	delete ui;
#endif
#ifdef G4VIS_USE
	delete vis;
#endif	

	/*
	 * 
	 * There might be a memory leak upon exiting, but it's nothing
	 * to worry about too much. Any modern operating system should
	 * just reclaim that memory.
	 * 
	 * TODO
	 * 
	 * 		FIX memory leak and possibly the segmentation fault.
	 * 
	 * */
	//delete runManager;
	
	delete ConfigFileInstance;
	delete DetectorConfigFileInstance;
	delete MaterialConfigFileInstance;
	delete ParticleConfigFileInstance;
}

/*
 * InitializeLuaInstances()
 * 
 * * Description
 * 
 * 		Uses openmp to introduce parallelization for the lua state
 * 		config files.
 * 
 * * Comment
 * 
 * 		Be sure to define the build type as release!
 * 
 * 		cmake -DCMAKE_BUILD_TYPE=Release -DGeant4_DIR=/path/to/G4 ../
 * 
 * */

void InitializeLuaInstances() {

	/*
	 * 
	 * uses openmp to introduce parallelization for the lua state
	 * config files
	 * 
	 * */
	#pragma omp parallel sections
	{
		#pragma omp section
		{
	
			ConfigFileInstance = new ConfigLuaInstance(Module);
			ConfigFileInstance->CloseLuaState();
		
		}
		#pragma omp section
		{
		
			DetectorConfigFileInstance = new DetectorConfigLuaInstance(Module);
			DetectorConfigFileInstance->CloseLuaState();
		
		}
		#pragma omp section
		{
		
			MaterialConfigFileInstance = new MaterialConfigLua(Module);
			MaterialConfigFileInstance->CloseLuaState();
			
		}
		#pragma omp section
		{
			
			ParticleConfigFileInstance = new ParticlesConfigLua(Module);
			ParticleConfigFileInstance->CloseLuaState();
			
		}
	}	
	
}

/*
 * InitializeRunManager(G4RunManager *runManager)
 * 
 * * Description
 * 
 * 		...
 * 
 * * Comment
 * 
 * 		You might notice something a bit odd with 

 * 		PrimaryGeneratorAction and SteppingAction. I wasn't able to
 * 		find a good solution for delimiting events in the
 * 		DarkGeantOutput.dat file without having 
 * 		PrimaryGeneratorAction::GeneratePrimaries increment a variable
 * 		in the SteppingAction instance.
 * 
 * 		This seems a bit hackish and I certainly don't like how
 * 		interconnected this code is, so a better solution would be
 *		ideal.
 * 
 * */

void InitializeRunManager(G4RunManager *runManager) {

	runManager->SetUserInitialization(Detector);
	runManager->SetUserInitialization(ConfigFileInstance->physicslist);
	
	
	PrimaryGeneratorAction *Generator = new PrimaryGeneratorAction(
                           ParticleConfigFileInstance->FourVectors,
                           ConfigFileInstance->DarkGeantOutputLocation,
                           ParticleConfigFileInstance->NumberOfEvents,
                           DetectorConfigFileInstance->World);
	runManager->SetUserAction(Generator);
	runManager->SetUserAction(Generator->GetSteppingAction());
	
	
	runManager->Initialize();
	
}
#ifdef G4UI_USE
void InitializeUIManager() {

	ui = G4UImanager::GetUIpointer();
	if (TerminalOutput) {
		
		ui->ApplyCommand("/run/verbose 1");
		ui->ApplyCommand("/event/verbose 1");
		ui->ApplyCommand("/tracking/verbose 1");
		
	}
	ui->ApplyCommand("/control/execute " + Module +"/vis.mac");
	
}
#endif

#ifdef G4VIS_USE
void InitializeVisManager() {

	vis = new G4VisExecutive();
	vis->Initialize();
	
}
#endif

void InitializeDetectorGeometry() {

	Detector = new DetectorConstructionV2(
	               DetectorConfigFileInstance->World,
	               DetectorConfigFileInstance->Components,
	               MaterialConfigFileInstance->Materials);
	
}



struct ArgumentTable {
	
	string name;
	void (*Function)(int argc, char *argv[], int index);
	
};

//Argument Function Prototypes
void Execute_Argument(int argc, char *argv[], int index);
void Module_Argument (int argc, char *argv[], int index);
void Limit_T_Argument(int argc, char *argv[], int index);
void Show_Vis_Argument(int argc, char *argv[], int index);
void Num_Threads_Argument(int argc, char *argv[], int index);



static const int numHandledArguments = 5;
static const ArgumentTable Table[numHandledArguments] =
{{"-execute"     , &Execute_Argument},
 {"-module"      , &Module_Argument},
 {"-lim-output"  , &Limit_T_Argument},
 {"-vis"         , &Show_Vis_Argument},
 {"-num-threads" , &Num_Threads_Argument}};



/*
 * HandleArguments(int argc, char *argv[])
 * 
 * * Description
 * 
 * 		Checks each provided runtime argument provided by the user
 * 		against known runtime arguments and acts accordingly.
 * 
 * */
 
void HandleArguments(int argc, char *argv[]) {
	
	for (int y = 1;y < argc;y++)
		for (int x = 0;x < numHandledArguments;x++)
			if (strcasecmp(argv[y], Table[x].name.c_str()) == 0)
				Table[x].Function(argc, argv, y);		
		
}

/*
 * Execute_Argument(int argc, char *argv[], int index)
 * 
 * * Description
 * 
 * 		...
 * 
 * */
 
void Execute_Argument(int argc, char *argv[], int index) {

	if ((index + 1) == argc) {
	
		cout << "Did not give a good execution argument\n";
		return;
		
	}
	
	G4String CharLiteralToString(argv[index + 1]);
	ExecutionVector.push_back("/control/execute " + CharLiteralToString);
	
}

void Module_Argument (int argc, char *argv[], int index) {

	if ((index+1) == argc) {
	
		cout << "Need to specify a module!\n";
		return;
		
	}
	Module = "config/module/" + string(argv[index+1]);
	
}

void Limit_T_Argument(int argc, char *argv[], int index) {

	TerminalOutput = false;
	
}

void Show_Vis_Argument(int argc, char *argv[], int index) {
	
	ShowVis = true;
	
}

void Num_Threads_Argument(int argc, char *argv[], int index) {
	
	if ((index+1) == argc) {
	
		cout << "Need to specify number of threads!\n";
		return;
		
	}
	if (atoi(argv[index+1]) >= 1) {
		
		NumberOfThreads = atoi(argv[index+1]);
		
	} else {
		
		cout << "Invalid number of threads. Be sure to provide a number\n";
		cout << "greater than or equal to 1\n";
		return;
		
	}
	
	
}

