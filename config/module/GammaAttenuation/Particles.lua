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

math.randomseed(os.time())
glob_distribution_modifier = 0
function PseudoRandomDistribution()

	local randnum = math.random()

	--Forces a higher proportion of particles to be closer to the origin
	if glob_distribution_modifier < 5 then

		glob_distribution_modifier = glob_distribution_modifier + 1
		
		if randnum <= .5 then
		
			return (-randnum) * 2.0
		
		else
		
			return randnum * 1.0
		
		end
	
	else 
	
		glob_distribution_modifier = 0
		
		if randnum <= .5 then
		
			return (-randnum) * 10.0
		
		else
		
			return randnum * 5.0
		
		end
	
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
Particle_Table = { Particle_Name = "gamma",
                   Particles_Position = {0, 0, -0.1},
                   Momentum_Direction = {0.0, 0.0, 1.0},
                   Energy = 0.0004,
                   Number_Of_Events = 10000 }

