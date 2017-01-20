DetectorConfig = { Detector_Name = "Detector",
                  Number_of_Detector_Components = 11 }
                  
World = { Material = "G4_AIR",
          Volume_Type = "Box",
          half_X = 60.0,
          half_Y = 60.0,
          half_Z = 60.0,
          Inside = "None",
          Position = {0, 0, 0} }

--TPC
DetectorComponent_1 = { Material = "Liquid Argon",
                        Volume_Type = "Box",
                        half_X = 1.25,
                        half_Y = 1.15,
                        half_Z = 5.15,
                        X_Rotation = 90.0,
                        Position = { 0, 0, -15 },
                        colour = {1.0, 0.0, 0.0},
                        Inside = "World" }
     
--Steel Cylinder surrounding TPC                   
DetectorComponent_2 = { Material     = "Steel",
                        Volume_Type  = "Cylinder",
                        Inner_Radius = 1.7,
                        Outer_Radius = 2.0,
                        Half_Length  = 5.25,
                        X_Rotation = 90.0,
                        Inside = "World",
                        Position = { 0 , 0 , -15 }}
                      
--Basic Exterior  
DetectorComponent_5 = { Material = "Steel",
                        Volume_Type = "Box",
                        half_X = 0.1,
                        half_Y = 10.0,
                        half_Z = 7.5,
                        X_Rotation = 90.0,
                        Inside = "World",
                        --Wireframe = true,
                        Position = {5, 0, -10}}
                        
DetectorComponent_4 = { Material = "Steel",
                        Volume_Type = "Box",
                        half_X = 0.1,
                        half_Y = 10.0,
                        half_Z = 7.5,
                        X_Rotation = 90.0,
                        Inside = "World",
                        --Wireframe = true,
                        Position = {-5, 0, -10}}
                        
DetectorComponent_3 = { Material = "Steel",
                        Volume_Type = "Box",
                        half_X = 0.1,
                        half_Y = 5.0,
                        half_Z = 7.5,
                        X_Rotation = 90.0,
                        Y_Rotation = 90.0,
                        Inside = "World",
                        --Wireframe = true,
                        Position = {0, 0, 0}}
                   
    
DetectorComponent_6 = { Material = "Steel",
                        Volume_Type = "Box",
                        half_X = 0.1,
                        half_Y = 5.0,
                        half_Z = 10.0,
                        Z_Rotation = 90.0,
                        Inside = "World",
                        --Wireframe = true,
                        Position = {-4.2, 10, -8.3}}
                        


--Dirt...Silica actually
DetectorComponent_7 = { Material = "SiO2",
                         Volume_Type = "Box",
                         half_X = 60.0,
                         half_Y = 30.0,
                         half_Z = 20.0,
                         Inside = "World",
                         --Wireframe = true,
                         colour = {0.0, 1.0, 0.0},
                         Position = {0, 37.50, -30}}
                         
DetectorComponent_8 = { Material = "SiO2",
                         Volume_Type = "Box",
                         half_X = 60.0,
                         half_Y = 30.0,
                         half_Z = 20.0,
                         Inside = "World",
                         --Wireframe = true,
                         colour = {0.0, 1.0, 0.0},
                         Position = {0, -37.50, -30}}
                         
DetectorComponent_9 = { Material = "SiO2",
                         Volume_Type = "Box",
                         half_X = 60.0,
                         half_Y = 7.5,
                         half_Z = 15,
                         Inside = "World",
                         --Wireframe = true,
                         colour = {0.0, 1.0, 0.0},
                         Position = {0, 0, -35}}
                         
DetectorComponent_10 = { Material = "SiO2",
                         Volume_Type = "Box",
                         half_X = 27.5,
                         half_Y = 7.5,
                         half_Z = 5.0,
                         Inside = "World",
                         colour = {0.0, 1.0, 0.0},
                         --Wireframe = true,
                         Position = {32.5, 0, -15.0}}
                         
DetectorComponent_11 = { Material = "SiO2",
                         Volume_Type = "Box",
                         half_X = 27.5,
                         half_Y = 7.5,
                         half_Z = 5.0,
                         Inside = "World",
                         colour = {0.0, 1.0, 0.0},
                         --Wireframe = true,
                         Position = {-32.5, 0, -15.0}}
                         
