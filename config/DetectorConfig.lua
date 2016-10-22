--[[

	* Detector_Name
	
		"Anything you want" (Default value of "Detector")
		
	* Number_of_Detector_Components
	
		A *Integer* greater than 0

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
World = { Material = "Air",
          Volume_Type = "Box",
          X = 20.0,
          Y = 20.0,
          Z = 20.0 }

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

]]--
DetectorComponent_1 = { Material = "Liquid Argon",
                        Volume_Type = "Cylinder",
                        Inner_Radius = 0.0,
                        Outer_Radius = .6,
                        Half_Length = .5,
                        Position = { 0, 0, 0 } }
                        
DetectorComponent_2 = { Material = "Air",
                        Volume_Type = "Box",
                        X = 1.0,
                        Y = 1.0,
                        Z = 1.0,
                        Position = { 0, 1, 0 } }
