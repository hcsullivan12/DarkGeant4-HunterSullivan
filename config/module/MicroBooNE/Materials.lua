Number_Of_Materials = 6
Material_1 = { G4Name = "G4_AIR"  }             
Material_2 = { Name = "Liquid Argon",
               Number_Of_Protons = 18,
               Atomic_Mass = 39.95,
               Density = 1.390 }
-- Used for Steel
Material_3 = { G4Name = "G4_Fe" }
Material_4 = { G4Name = "G4_C" }

-- Used for Silica
Material_5 = { G4Name = "G4_Si" }
Material_6 = { G4Name = "G4_O" }


Number_Of_Composite_Materials = 2
Composite_Material_1 = { Name = "Steel",
                         Density = 7.86, -- Arbitrary number
                         Number_Of_Components = 2,
                         Component_1 = {Material = "G4_Fe", Fractional_Mass = .979},
                         Component_2 = {Material = "G4_C" , Fractional_Mass = .021}}
                         
Composite_Material_2 = { Name = "SiO2",
                         Density = 2.196,
                         Number_Of_Components = 2,
                         Component_1 = {Material = "G4_Si", Fractional_Mass = .33},
                         Component_2 = {Material = "G4_O" , Fractional_Mass = .67}}
