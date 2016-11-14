
--[[

	If Particle_Position is equal to a function named
	Particle_Position_function, the C++ code will call the lua
	function and allow the script to generate a unique set of
	positions.
	
	The return value expected is a 2D array, where the number of
	rows is equal to AmountOfPositionsToGenerate and the number of
	columns is exactly 3.

--]]
--Sort of a very wonky algorithm
function Particle_Position_Function(AmountOfPositionsToGenerate)
	
	local distribution = GetDistributionTable(AmountOfPositionsToGenerate)
	
	local PositionTable = {}
	local x = 0
	local y = 0
	for i = 1, #distribution
	do
	
		local z = 0.0
		if i <= #distribution/2 then
		
			z = (-(.4 - distribution[i]) * 33.0) + 13.2
		
		else
		
			z = ((.4 - distribution[i]) * 33.0) - 13.2
		
		end
		
		PositionTable[i] = {x, y, z}
	
	end
	
	return PositionTable

end


function GetDistributionTable(AmountOfPositionsToGenerate)

	local dz = 66.0/AmountOfPositionsToGenerate
	
	local i = 1
	local distribution = {}
	--Small bug right here that was "fixed" by starting at -33.0 +dz
	for z = (-33.0 + dz), 33.0, dz
	do
	
		distribution[i] = GuassianDistribution(z)
		i = i + 1
	
	end
	
	return distribution

end

function GuassianDistribution(z)

	return math.exp((-.5)*(z^2))/math.sqrt(2.0 * math.pi)

end



--[[

--]]
Particle_File = "output.dat"

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
Particle_Table = { Particle_Name = "proton",
                   Particles_Position = Particle_Position_Function }

