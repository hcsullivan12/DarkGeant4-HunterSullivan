
DetectorConfig = { Detector_Name = "Detector",
                  Number_of_Detector_Components = 1 }

World = { Material = "G4_AIR",
          Volume_Type = "Box",
          half_X = 20.0,
          half_Y = 20.0,
          half_Z = 70.0,
          Inside = "None",
          Position = {0, 0, 0} }

DetectorComponent_1 = { Material = "Liquid Argon",
                        Volume_Type = "Box",
                        half_X = 19,
                        half_Y = 18,
                        half_Z = 66.0,
                        Position = { 0, 0, 0 },
                        Inside = "World" }
