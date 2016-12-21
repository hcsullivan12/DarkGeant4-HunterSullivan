DetectorConfig = { Detector_Name = "Detector",
                  Number_of_Detector_Components = 1 }
                  
World = { Material = "G4_AIR",
          Volume_Type = "Box",
          X = 20.0,
          Y = 20.0,
          Z = 20.0,
          Inside = "None",
          Position = {0, 0, 0} }

DetectorComponent_1 = { Material = "Liquid Argon",
                        Volume_Type = "Box",
                        X = 1.25,
                        Y = 1.15,
                        Z = 5.0,
                        Position = { 0, 0, 0 },
                        Inside = "World" }
