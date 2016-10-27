
--[[

--]]
Particle_File = "Output.dat"

--[[

	Particle_File_Type
	
	* Values
	
		"Four Vector"
		
			Standard format of a four vector file
			<E/c, P_x, P_y, P_z> where each component is in units of
			GeV/c
		
		"Four Vector, with name"
		
			Name, <E/c, P_x, P_y, P_z> 
			where Name is the name of the particle being described
		
		"Four Vector, with name, with position"
			
			Name, <E/c, P_x, P_y, P_z>, <X, Y, Z>
			where <X, Y, Z> define the position of the particle with
			respect to the origin of the world box, with units of
			metres.
		
		"Four Vector, with position, with name"
		
			Same as the previous version
		
		"Four Vector, with position"
		
			<E/c, P_x, P_y, P_z>, <X, Y, Z>
	
		default value = nil.

--]]
Particle_File_Type = "Four Vector"

--[[

	Four_Vector_Table
	
	* Values
	
		Particle_Name
		
			May be defined as any known particle
			
			default value = nil. Will halt execution if "with name" was
			not a component of Particle_File_Type
			
		Particles_Position
		
			Must be defined as a table with three numerical quantities
			<X, Y, Z>
			
			default = nil. Will halt execution if "with position" was
			not a component of Particle_File_Type

--]]
Four_Vector_Table = {Particle_Name = "proton",
                     Particles_Position = {0., 0., 0.}}


--[[

	If Particle_Position
	
		...

--]]
function Particle_Positions()

	print("STUB")

end
