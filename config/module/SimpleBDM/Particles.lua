
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
		local z = GetSign() * math.random() * 5.15
		PositionTable[i] = {x, y, z}
	
	end
	
	return PositionTable

end

function GetSign()

	local rand = math.random()
	if rand < 0.5 then
		return -1
	else
		return 1
	end

end

Particle_File = "output.dat"
Particle_File_Type = "Four Vector"
Particle_Table = { Particle_Name = "proton",
                   Particles_Position = Particle_Position_Function }

