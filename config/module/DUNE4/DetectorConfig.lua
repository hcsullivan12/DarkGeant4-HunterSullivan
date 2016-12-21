
DetectorConfig = { Detector_Name = "Detector",
                  Number_of_Detector_Components = 2 }

World = { Material = "G4_AIR",
          Volume_Type = "Box",
          X = 20.0,
          Y = 20.0,
          Z = 20.0,
          Inside = "None",
          Position = {0, 0, 0} }

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

                        
