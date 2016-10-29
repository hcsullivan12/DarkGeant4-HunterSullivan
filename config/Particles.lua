
--[[

--]]
Particle_File = nil

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
Particle_File_Type = nil

--[[

	Particle_Table
	
	* Values
	
		Particle_Name
		
			May be defined as any known particle
			
			default value = nil. Will halt execution if "with name" was
			not a component of Particle_File_Type
			
		Particles_Position
		
			Must be defined as a table with three numerical quantities
			<X, Y, Z> or a function that generates a 2D list
			
			default = nil. Will halt execution if "with position" was
			not a component of Particle_File_Type
			
		Number_Of_Events
		
			...

--]]
Particle_Table = { Particle_Name = "mu+",
                   Particles_Position = {0.0, 0.0, 0.0},
                   Momentum_Direction = {0.0, 0.0, 1.0},
                   Energy = 100.0,
                   Number_Of_Events = 20 }


--[[

	If Particle_Position is equal to a function named
	Particle_Position_function, the C++ code will call the lua
	function and allow the script to generate a unique set of
	positions.
	
	The return value expected is a 2D array, where the number of
	rows is equal to AmountOfPositionsToGenerate and the number of
	columns is exactly 3.

--]]
function Particle_Position_Function(AmountOfPositionsToGenerate)

	local PositionTable = {}
	
	for i = 1, AmountOfPositionsToGenerate 
	do
	
		local x = 0
		local y = 0
		local z = PseudoRandomDistribution()
		
		PositionTable[i] = {x, y, z}
	
	end
	
	return PositionTable

end

--[[



--]]
glob_distribution_modifier = 0
function PseudoRandomDistribution()

	--Forces a higher proportion of particles to be closer to the origin
	if glob_distribution_modifier < 5 then

		glob_distribution_modifier = glob_distribution_modifier + 1
		return math.random() * 1.0
	
	else 
	
		glob_distribution_modifier = 0
		return math.random() * 5.0
	
	end

end
