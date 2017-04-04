
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
	
	math.randomseed(os.time())
	
	local PositionTable = {}
	local x = 0
	local y = 0
	for i = 1, AmountOfPositionsToGenerate
	do
	
		local z = BoxMullerTransform()
		
		PositionTable[i] = {x, y, z}
	
	end
	
	return PositionTable

end

--[[

	Box-Muller Transform allows for a uniform random distribution from
	[0,1] to be transformed to a random guassian distribution

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
	until U_1 > 3.36244e-237

	return math.sqrt(-2 * math.log(U_1)) * math.cos(2 * math.pi * U_2)

end

Particle_Table = { Primary_Particles = "proton",
                   Particles_Position = {0,0,0},
	           Momentum_Direction = {0.0, 0.0, 1.0},
                   Energy = 4,
                   Number_Of_Events = 20 } }

