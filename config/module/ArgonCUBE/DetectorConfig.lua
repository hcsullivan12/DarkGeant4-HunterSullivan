
DetectorConfig = { Detector_Name = "Detector",
                  Number_of_Detector_Components = 2 }

World = { Material = "Liquid Argon",
          Volume_Type = "Box",
          half_X = 10.0,
          half_Y = 10.0,
          half_Z = 10.0,
          Inside = "None",
          Position = {0, 0, 0} }

DetectorComponent_1 = { Material = "Liquid Argon",
                        Volume_Type = "Box",
                        half_X = 5,
                        half_Y = 1,
                        half_Z = 1,
                        Position = { 0, 0, 0 },
                        Inside = "World" }

DetectorComponent_2 = { Material = "G4_GLASS_PLATE", --[[Placeholder for G10 for the moment]]--
                        Volume_Type = "Box",
                        half_X = 5.005,
                        half_Y = 1.005,
                        half_Z = 1.005,
                        Position = { 0, 0, 0 },
                        Inside = "World" }
