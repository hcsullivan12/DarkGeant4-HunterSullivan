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
		
	* Atomic_Mass (g/mole)
	
		default = nil. Will halt execution if not defined.
		
	* Density (g/cm^3)
	
		default = nil. Will halt execution if not defined.
		
	
		
	
]]--

Material_1 = { G4Name = "G4_Galactic" }
            
              
Material_2 = { G4Name = "G4_Pb" }               
               

Number_Of_Composite_Materials = 0

--[[

	TODO
	
	It might be imperative to calculate the density in DarkGeant4,
	affording the user to avoid having to do that calculation themselves.
	
	With that being said, maybe they want to provide a different density,
	so maybe the option ought to stay but be optional?
	
	*Component_x
	
		First value is a known material, second value is the fractional
		mass.

--]]
