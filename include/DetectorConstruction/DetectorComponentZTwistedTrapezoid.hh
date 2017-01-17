/*
 * DetectorComponentZTwistedTrapezoid.hh
 * 
 * Copyright 2016 Hunter Sullivan <hunter.sullivan@mavs.uta.edu>
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

#ifndef DETECTORCOMPONENTZTWISTEDTRAPEZOID_HH
#define DETECTORCOMPONENTZTWISTEDTRAPEZOID_HH

#include "DetectorComponent.hh"


class DetectorComponent_ZTwistedTrapezoid : public DetectorComponent {
	
	/*
	 * 
	 * Class member variables
	 * 
	 * */

	public:
	
		G4double xHalfLengthAtBottom;
		G4double xHalfLengthAtTop;
		G4double yHalfLengthAtBottom;
		G4double yHalfLengthAtTop;
		G4double zHalfLength;
		G4double TwistingAngle;
	
	/*
	 * 
	 * Class member functions
	 * 
	 * */

	public:
	
		DetectorComponent_ZTwistedTrapezoid(DetectorComponent_vars vars);
		~DetectorComponent_ZTwistedTrapezoid();
		
		void ConstructVolume();
	
};

#endif

