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


Particle_File = nil
Particle_File_Type = nil
Particle_Table = { Primary_Particles = "mu+",
                   Particles_Position = Particle_Position_Function,
                   Momentum_Direction = {0.0, 0.0, 1.0},
                   Energy = 1000.0,
                   Number_Of_Events = 20 }

