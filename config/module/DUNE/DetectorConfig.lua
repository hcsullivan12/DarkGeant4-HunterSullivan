
DetectorConfig = { Detector_Name = "Detector",
                  Number_of_Detector_Components = 1 }

World = { Material = "G4_AIR",
          Volume_Type = "Box",
          X = 20.0,
          Y = 20.0,
          Z = 70.0,
          Inside = "None",
          Position = {0, 0, 0} }

DetectorComponent_1 = { Material = "Liquid Argon",
                        Volume_Type = "Box",
                        X = 19,
                        Y = 18,
                        Z = 66.0,
                        Position = { 0, 0, 0 },
                        Inside = "World" }
