--[[

	* Detector_Name
	
		"Anything you want" (Default value of "Detector")
		
	* Number_of_Detector_Components
	
		A *Integer* greater than 0
		
			default = nil. Will halt execution of program if not 
			defined.

]]--
DetectorConfig = { Detector_Name = "Detector",
                  Number_of_Detector_Components = 1 }


-- **** Please note that units of length are in metres!                  

--[[

	* Material
	
		"Liquid Argon"
		"Air"

	* Volume_Type
	
		"Cylinder"
		
			Inner_Radius (Default value of 0.0)
			Outer_Radius (No Default Value)
			Half_Length (No Default Value)
			Start_Angle (Default Value of 0.0)
			Delta_Angle   (Default Value of 360.)
		
		"Box"
		
			X (No Default Value) (Width) -> Usually
			Y (No Default Value) (Height)-> Usually
			Z (No Default Value) (Length)-> Usually

]]--
World = { Material = "G4_AIR",
          Volume_Type = "Box",
          X = 20.0,
          Y = 20.0,
          Z = 20.0,
          Inside = "None",
          Position = {0, 0, 0} }

--[[

	* Component_Name
	
		(Default value of DectorComponent_x)

	* Material
	
		"Liquid Argon"
		"Air"

	* Volume_Type
	
		"Cylinder"
		
			Inner_Radius (Default value of 0.0)
			Outer_Radius (No Default Value)
			Half_Length (No Default Value)
			Start_Angle (Default Value of 0.0)
			Delta_Angle   (Default Value of 360.)
		
		"Box"
		
			X (No Default Value) (Width) -> Usually
			Y (No Default Value) (Height)-> Usually
			Z (No Default Value) (Length)-> Usually
			
	* Inside
	
		"World"
		"DetectorComponent_x"
		
			default = nil. Will halt execution of program if not 
			defined.

]]--
--[[ DetectorComponent_1 = { Material = "Liquid Argon",
                        Volume_Type = "Box",
                        X = 1,
                        Y = 1,
                        Z = 2,
                        Position = { 0, 0, 0 },
                        Inside = "World" }
]]--

--[[ DetectorComponent_1 = { Material = "Liquid Argon",
                        Volume_Type = "Cylinder",
                        Inner_Radius = 1.0,
                        Outer_Radius = 2.0,
                        Start_Angle = 0.0,
                        Delta_Angle = 270.0,
                        Half_Length = 2.0,
                        Position = {0, 0, 2},
                        Inside = "World" }
--]]

--[[DetectorComponent_1 = { Material = "Liquid Argon",
                        Volume_Type = "Cone",
                        Inner_Radius_At_Bottom = 1.0,
			Outside_Radius_At_Bottom = 2.0,
			Inner_Radius_At_Top = 3.0,
			Outside_Radius_At_Top = 4.0,
			Half_Length = 2.0,
			Start_Angle = 270.0,
			Delta_Angle = 180.0,
                        Position = { 0, 0, 0 },
                        Inside = "World" }
]]--

--[[DetectorComponent_1 = { Material = "Liquid Argon",
                        Volume_Type = "Ellipsoid",
                        X_Semi_Axis = 6.0,
			Y_Semi_Axis = 4.0,
			Z_Semi_Axis = 2.0,
			Z_Bottom = -3.0,
			Z_Top = 3.0,
                        Position = {0, 0, 0},
                        Inside = "World" }
]]--

--[[DetectorComponent_1 = { Material = "Liquid Argon",
                        Volume_Type = "Elliptical Cone",
                        X_Semi_Axis = 0.5,
			Y_Semi_Axis = 0.5,
			Height = 0.5,
			Z_Top = 0.5,
                        Position = {0, 0, 0},
                        Inside = "World" }   
]]--

--[[DetectorComponent_1 = { Material = "Liquid Argon",
                        Volume_Type = "Elliptical Tube",
                        X_Half_Length = 2.0,
			Y_Half_Length = 4.0,
			Z_Half_Length = 6.0,			
                        Position = { 0, 0, 0 },
                        Inside = "World" }
]]--

--[[DetectorComponent_1 = { Material = "Liquid Argon",
                        Volume_Type = "Hyperbolic Tube",
                        Inner_Radius = 1.0,
			Outer_Radius = 2.0,
			Inner_Radius_Angle = .7,
			Outer_Radius_Angle = .7,
			Z_Half_Length = 4.0,			
                        Position = { 0, 0, 0 },
                        Inside = "World" }
]]--

DetectorComponent_1 = { Material = "Liquid Argon",
                        Volume_Type = "Parallelepiped",
                        X_Half_Length = 2.0,
			Y_Half_Length = 4.0,
			Z_Half_Length = 6.0,
			Angle_Of_XZ_Faces = 10,
			Polar_Angle_Of_XY_Faces = 20,
			Azimuthal_Angle_Of_XY_Faces = 5,			
                        Position = { 0, 0, 0 },
                        Inside = "World" }


--[[DetectorComponent_1 = { Material = "Liquid Argon",
                        Volume_Type = "Solid Sphere",
                        Radius = 2.0,
                        Position = { 0, 0, 0 },
                        Inside = "World" }
]]--

--[[DetectorComponent_1 = { Material = "Liquid Argon",
                        Volume_Type = "Torus",
                        Inner_Radius = 2.0,
			Outer_Radius = 3.0,
			Sweeping_Radius = 6.0,
			Phi_Start = 0.0,
			Delta_Phi = 90,
                        Position = {0, 0, 0},
                        Inside = "World" }
]]--





                 
