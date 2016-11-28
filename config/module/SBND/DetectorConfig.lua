--[[

	* Detector_Name
	
		"Anything you want" (Default value of "Detector")
		
	* Number_of_Detector_Components
	
		A *Integer* greater than 0
		
			default = nil. Will halt execution of program if not 
			defined.

]]--
DetectorConfig = { Detector_Name = "Detector",
                  Number_of_Detector_Components = 3 }


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
World = { Material = "G4_Galactic",
          Volume_Type = "Box",
          X = 5.0,
          Y = 5.0,
          Z = 1300.0,
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

-- LAr1-ND
DetectorComponent_1 = { Material = "Liquid Argon",
                        Volume_Type = "Box",
                        X = 4.0,
                        Y = 4.0,
                        Z = 5.0,
                        Position = { 0, 0, 112.5 },
                        Inside = "World" }

-- MicroBooNe
DetectorComponent_2 = { Material = "Liquid Argon",
                        Volume_Type = "Box",
                        X = 2.33,
                        Y = 2.56,
                        Z = 10.37,
                        Position = {0, 0, 475.185},
                        Inside = "World" }

-- ICARUS-T600                        
DetectorComponent_3 = { Material = "Liquid Argon",
                        Volume_Type = "Box",
                        X = 3.6,
                        Y = 3.9,
                        Z = 19.6,
                        Position = {0, 0, 609.8},
                        Inside = "World"}

                        
