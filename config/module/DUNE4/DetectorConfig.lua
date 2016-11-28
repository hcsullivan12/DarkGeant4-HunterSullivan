--[[

	* Detector_Name
	
		"Anything you want" (Default value of "Detector")
		
	* Number_of_Detector_Components
	
		A *Integer* greater than 0
		
			default = nil. Will halt execution of program if not 
			defined.

]]--
DetectorConfig = { Detector_Name = "Detector",
                  Number_of_Detector_Components = 2 }


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
			End_Angle   (Default Value of 360.)
		
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
			End_Angle   (Default Value of 360.)
		
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
DetectorComponent_1 = { Material = "Liquid Argon",
                        Volume_Type = "Box",
                        X = 1,
                        Y = 1,
                        Z = 2,
                        Position = { 0, 0, 0 },
                        Inside = "World" }

DetectorComponent_2 = { Material = "Liquid Argon",
                        Volume_Type = "Cylinder",
                        Inner_Radius = 1.0,
                        Outer_Radius = 2.0,
                        Start_Angle = 0.0,
                        End_Angle = 270.0,
                        Half_Length = 2.0,
                        Position = {0, 0, 2},
                        Inside = "World" }

                        