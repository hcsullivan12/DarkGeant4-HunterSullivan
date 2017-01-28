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
	
	math.randomseed(os.time())
	for i = 1, AmountOfPositionsToGenerate 
	do
	
		local x = UniformRandomDistribution(-2.5, 2.5)
		local y = UniformRandomDistribution(-2.5, 2.5)
		local z = UniformRandomDistribution(-650.0, 650.0)
		
		PositionTable[i] = {x, y, z}
	
	end
	
	return PositionTable

end

function UniformRandomDistribution(lower, upper)

	local randnum = math.random()
	
	if randnum < .5 then
		return -(lower * 2) * randnum
	else
		return upper * randnum
	end

end



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
Particle_Table = { Primary_Particles = "proton",
                   Particles_Position = Particle_Position_Function,
                   Momentum_Direction = {0.0, 0.0, 1.0},
                   Energy = 2.0,
                   Number_Of_Events = 1000 }

