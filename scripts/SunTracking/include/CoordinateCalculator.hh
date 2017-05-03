/*
 * CoordinateCalculator.hh
 * 
 * Copyright 2017 Hunter Sullivan <hunter.sullivan@mavs.uta.edu>
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

#ifndef COORDINATECALCULATOR_HH
#define COORDINATECALCULATOR_HH

class CoordinateCalculator {


    /*
     * 
     * Class member functions
     * 
     * */
     
     public:
     
       CoordinateCalculator(double Altitude, double Azimuth, double beta);
       ~CoordinateCalculator();
       void Calculate();
       double GetXComponent();
       double GetYComponent();
       double GetZComponent();
       
    /*
     * 
     * Class member variables
     * 
     * */
     
     private:
        double Altitude;
        double Azimuth;
        double theta;
        double phi;
        double X;
        double Y;
        double Z;
        double beta; ///angle between North and beam line direction (z axis)
     
};

#endif

