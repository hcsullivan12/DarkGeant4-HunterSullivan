
DetectorConfig = { Detector_Name = "Detector",
                  Number_of_Detector_Components = 11 }

World = { Material = "G4_AIR",
          Volume_Type = "Box",
          half_X = 25.0,
          half_Y = 25.0,
          half_Z = 25.0,
          Inside = "None",
          Position = {0, 0, 0} }

--[[Fiberglass walls - Glass PLate Placeholder for G10]]--

DetectorComponent_1 = { Material = "G4_GLASS_PLATE",
                        Volume_Type = "Box",
                        half_X = 0.005,
                        half_Y = 5,
                        half_Z = 2.005,
                        Position = { 0, 0, 0 },
			Magnetic_Field = {0, 0, 0},
			Electric_Field = {0, 0, 0},
			color = {1.0,1.0,0.0},
                        Inside = "World" }

DetectorComponent_2 = { Material = "G4_GLASS_PLATE", 
                        Volume_Type = "Box",
                        half_X = 1,
                        half_Y = 5,
                        half_Z = 0.005,
                        Position = { 1, 0, 0 },
			Magnetic_Field = {0, 0, 0},
			Electric_Field = {0, 0, 0},
			color = {1.0,1.0,0.0},
                        Inside = "World" }

DetectorComponent_3 = { Material = "G4_GLASS_PLATE",
                        Volume_Type = "Box",
                        half_X = 1,
                        half_Y = 5,
                        half_Z = 0.005,
                        Position = { -1, 0, 0 },
			Magnetic_Field = {0, 0, 0},
			Electric_Field = {0, 0, 0},
			color = {1.0,1.0,0.0},
                        Inside = "World" }

--[[Liquid Argon Modules]]--

DetectorComponent_4 = { Material = "G4_lAr",
                        Volume_Type = "Box",
                        half_X = 0.5,
                        half_Y = 5,
                        half_Z = 1,
                        Position = { -1.505, 0, 1.005 },
			Magnetic_Field = {0, 0.5, 0},
			Electric_Field = {-1, 0, 0},
			color = {0.0,0.0,1.0},
                        Inside = "World" }

DetectorComponent_5 = { Material = "G4_lAr",
                        Volume_Type = "Box",
                        half_X = 0.5,
                        half_Y = 5,
                        half_Z = 1,
                        Position = { -0.505, 0, 1.005 },
			Magnetic_Field = {0, 0.5, 0},
			Electric_Field = {1, 0, 0},
			color = {0.0,0.0,1.0},
                        Inside = "World" }

DetectorComponent_8 = { Material = "G4_lAr",
                        Volume_Type = "Box",
                        half_X = 0.5,
                        half_Y = 5,
                        half_Z = 1,
                        Position = { -1.505, 0, -1.005 },
			Magnetic_Field = {0, 0.5, 0},
			Electric_Field = {-1, 0, 0},
			color = {1.0,0.0,0.0},
                        Inside = "World" }

DetectorComponent_9 = { Material = "G4_lAr",
                        Volume_Type = "Box",
                        half_X = 0.5,
                        half_Y = 5,
                        half_Z = 1,
                        Position = { -0.505, 0, -1.005 },
			Magnetic_Field = {0, 0.5, 0},
			Electric_Field = {1, 0, 0},
			color = {1.0,0.0,0.0},
                        Inside = "World" }

DetectorComponent_7 = { Material = "G4_lAr",
                        Volume_Type = "Box",
                        half_X = 0.5,
                        half_Y = 5,
                        half_Z = 1,
                        Position = { 1.505, 0, 1.005 },
			Magnetic_Field = {0, 0.5, 0},
			Electric_Field = {1, 0, 0},
			color = {1.0,0.0,0.0},
                        Inside = "World" }

DetectorComponent_6 = { Material = "G4_lAr",
                        Volume_Type = "Box",
                        half_X = 0.5,
                        half_Y = 5,
                        half_Z = 1,
                        Position = { 0.505, 0, 1.005 },
			Magnetic_Field = {0, 0.5, 0},
			Electric_Field = {-1, 0, 0},
			color = {1.0,0.0,0.0},
                        Inside = "World" }

DetectorComponent_11 = { Material = "G4_lAr",
                        Volume_Type = "Box",
                        half_X = 0.5,
                        half_Y = 5,
                        half_Z = 1,
                        Position = { 1.505, 0, -1.005 },
			Magnetic_Field = {0, 0.5, 0},
			Electric_Field = {1, 0, 0},
			color = {0.0,0.0,1.0},
                        Inside = "World" }

DetectorComponent_10 = { Material = "G4_lAr",
                        Volume_Type = "Box",
                        half_X = 0.5,
                        half_Y = 5,
                        half_Z = 1,
                        Position = { 0.505, 0, -1.005 },
			Magnetic_Field = {0, 0.5, 0},
			Electric_Field = {-1, 0, 0},
			color = {0.0,0.0,1.0},
                        Inside = "World" }
