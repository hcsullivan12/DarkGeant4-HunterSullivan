

--[[

	* Number_Of_Materials 
	
		Must always be defined and must be an integer

]]--
Number_Of_Materials = 2

--[[

	* Name
	
		Name of your material. Case sensitive, will be used later for
		detector components! Be consistent.
		
	* G4Database
	
		true if you want DarkGeant4 to use the Geant4 Databases to
		generate a material for you.
		
		default = false/nil and doesn't need to be defined.

		* G4Name
	
			If G4Database is set to true, please be sure to specify what
			material in the Geant4 Database your material refers to.
		
			default = nil. Will halt execution if not defined.
			
	If G4Database = false/nil
	
	* Number_Of_Protons
	
		Be sure to pass an integer! A fraction of a proton certainly
		doesn't make sense.
		
		default = nil. Will halt execution if not defined.
		
	* Atomic_Mass
	
		default = nil. Will halt execution if not defined.
		
	* Density
	
		default = nil. Will halt execution if not defined.
		
	
		
	
]]--
Material_1 = { G4Database = true,
              G4Name = "G4_AIR"  }
              
              
Material_2 = { Name = "Liquid Argon",
               Number_Of_Protons = 18,
               Atomic_Mass = 39.95,
               Density = 1.390 }
