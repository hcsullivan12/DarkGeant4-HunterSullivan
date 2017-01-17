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
	local x = 0
	local y = 0
	for i = 1, AmountOfPositionsToGenerate 
	do
	
		local z = GetSign() * math.random()
		
		PositionTable[i] = {x, y, z}
	
	end
	
	return PositionTable

end

function GetSign()

	rand = math.random()
	
	if rand < 0.5 then
		return -1
	else
		return 1
	end

end


--[[

	Particle_File
	
	A string value, naming the file located in the present module
	directory that you want DarkGeant4 to load.
	
	Default value is nil and will not halt execution if other
	variables are satisfied.

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
		
			Specifies the number of events to generate. Must be an
			integer.
			
			default = nil. Will half execution if Particle_File is nil
			
		Energy
		
			Specifies the energy of each particle in units of GeV
			
			default = nil. Will halt execution if Particle_File is nil

--]]
Particle_Table = { Particle_Name = "mu+",
                   Particles_Position = Particle_Position_Function,
                   Momentum_Direction = {0.0, 0.0, 0.0},
                   Energy = 3.0,
                   Number_Of_Events = 20 }

