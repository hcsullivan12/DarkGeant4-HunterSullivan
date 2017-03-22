/*
 * MagneticField.cxx
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

#include "MagneticField.hh"

#include "G4FieldManager.hh"
#include "G4TransportationManager.hh"


MagneticField::MagneticField()
  : G4UniformMagField(G4ThreeVector())
{
  GetGlobalFieldManager()->SetDetectorField(NULL);
}


MagneticField::MagneticField(G4ThreeVector fieldVector)
  : G4UniformMagField(fieldVector)
{
  GetGlobalFieldManager()->SetDetectorField(this);    
  GetGlobalFieldManager()->CreateChordFinder(this);
}


MagneticField::~MagneticField()
{}


// Set the value of the Global Field to fieldValue along X

void MagneticField::SetMagFieldValue(G4double fieldValue)
{
   SetMagFieldValue(G4ThreeVector(fieldValue,0,0));
}


// Set the value of the Global Field

void MagneticField::SetMagFieldValue(G4ThreeVector fieldVector)
{
  if( fieldVector != G4ThreeVector(0.,0.,0.) )
  {
    SetFieldValue(fieldVector);
    GetGlobalFieldManager()->SetDetectorField(this);
    GetGlobalFieldManager()->CreateChordFinder(this);
  } else
    GetGlobalFieldManager()->SetDetectorField(NULL);
}


G4FieldManager*  MagneticField::GetGlobalFieldManager()
{
  return G4TransportationManager::GetTransportationManager()->GetFieldManager();
}


