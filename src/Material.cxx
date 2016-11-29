/*
 * Material.cxx
 * 
 * Copyright 2016 Emma Davenport <Davenport.physics@gmail.com>
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

#include "Material.hh"

//Geant4 Headers
#include "G4NistManager.hh"


static G4NistManager *NistManager = NULL;

/*
 *
 * Should be used for Materials that are defined by Geant4 already. 
 * 
 * */
 
Material::Material(G4String name) {
	
	/*
	 * 
	 * Fixes SEGFAULT if NistManager is set during runtime and not
	 * at compile time.
	 * 
	 * */
	if (NistManager == NULL) {
		NistManager = G4NistManager::Instance();
	}
	
	this->name = name;
	this->DefinedMaterial = NistManager->FindOrBuildMaterial(name);
	
}

Material::Material(G4String name, G4double z, G4double a, G4double density) {
	
	this->name    = name;
	this->z       = z;
	this->a       = a;
	this->density = density;
	
	this->DefinedMaterial = new G4Material(name = this->name, 
										   z = this->z, 
								           this->a, 
								           this->density);
}

Material::~Material() {
	
	/*
	 * 
	 * Documentation states that nothing should ever be deleted by
	 * the user's code. So the destructor should remain empty until
	 * the end of eternity.
	 * 
	 * */
	
}

G4Material *Material::GetMaterialPointer() {
	
	return this->DefinedMaterial;	
	
}

G4String Material::GetMaterialName() {

	return this->name;
	
}

void Material::SetAdditionalNames() {
	
	/*
	 * 
	 * Since users might want the option to use different names,
	 * it might be fruitful to add this functionality.
	 * 
	 * TODO
	 * 
	 * 		Finish this function and create another function that
	 * 		can compare arbitrary strings against the set name and
	 * 		these alternative names
	 * 
	 * */
	
}


Composite_Material::Composite_Material(G4String name, vector<Material *> Composite_Materials) {
	
	this->Composite_Materials = Composite_Materials;
	
}

void Composite_Material::BuildCompositeMaterial() {

	
	
}
