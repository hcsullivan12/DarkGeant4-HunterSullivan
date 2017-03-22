/*
 * MagneticField.hh
 * 
 * Copyright 2017 Hunter Sullivan <hunter@laptop>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */


#ifndef MagneticField_HH
#define MagneticField_HH

#include "G4UniformMagField.hh"

class G4FieldManager;

///  A class for control of the Magnetic Field of the detector.
///  The field is assumed to be uniform.
 
class MagneticField : public G4UniformMagField
{
  public:
    MagneticField();              //  A zero field
    MagneticField(G4ThreeVector); //  The value of the field
    virtual ~MagneticField();  
      
    //Set the field (fieldValue,0,0)
    void SetMagFieldValue(G4double fieldValue);
    void SetMagFieldValue(G4ThreeVector fieldVector);
      
  protected:
    // Find the global Field Manager
    G4FieldManager* GetGlobalFieldManager(); // static 
};

#endif
