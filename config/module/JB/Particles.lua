
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
	
	math.randomseed(os.time())
	
	local PositionTable = {}
	local x = 0
	local y = 0
	for i = 1, AmountOfPositionsToGenerate
	do
	
		PositionTable[i] = {x, y, BoxMullerTransform()}
	
	end
	
	return PositionTable

end

--[[

	Box-Muller Transform allows for a uniform random distribution from
	[0,1] to be transformed to a random guassian distribution
	
	U_1 = e^(-(R^2)/2)

--]]
function BoxMullerTransform()

	local U_1 = 0.0
	local U_2 = 0.0
	
	U_2 = math.random()

	--[[
	
		This condition is set to force a radius of 33.0 or less.
	
	--]]
	repeat
		U_1 = math.random()
	until U_1 >= 3.726653-6

	return math.sqrt(-2 * math.log(U_1)) * math.cos(2 * math.pi * U_2)

end

Particle_File = "output.dat"
Particle_File_Type = "Four Vector"
Particle_Table = { Particle_Name = "proton",
                   Particles_Position = Particle_Position_Function }

