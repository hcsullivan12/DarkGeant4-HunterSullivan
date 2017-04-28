DetectorConfig = { Detector_Name = "Detector",
                  Number_of_Detector_Components = 3 }

World = { Material = "G4_Galactic",
          Volume_Type = "Box",
          half_X = 5.0,
          half_Y = 5.0,
          half_Z = 1300.0,
          Inside = "None",
          Position = {0, 0, 0} }

-- LAr1-ND
DetectorComponent_1 = { Material = "Liquid Argon",
                        Volume_Type = "Box",
                        half_X = 4.0,
                        half_Y = 4.0,
                        half_Z = 5.0,
                        Position = { 0, 0, 112.5 },
                        Inside = "World" }

-- MicroBooNe
DetectorComponent_2 = { Material = "Liquid Argon",
                        Volume_Type = "Box",
                        half_X = 2.33,
                        half_Y = 2.56,
                        half_Z = 10.37,
                        Position = {0, 0, 475.185},
                        Inside = "World" }

-- ICARUS-T600                        
DetectorComponent_3 = { Material = "Liquid Argon",
                        Volume_Type = "Box",
                        half_X = 3.6,
                        half_Y = 3.9,
                        half_Z = 19.6,
                        Position = {0, 0, 609.8},
                        Inside = "World"}

                        
