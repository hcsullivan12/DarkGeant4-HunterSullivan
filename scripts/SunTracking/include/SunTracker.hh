/*
 * SunTracker.hh
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

#ifndef SUNTRACKER_HH 
#define SUNTRACKER_HH

class SunTracker {
	
	 /*
     * 
     * Class member variables
     * 
     * */
     
     private:
		int year;
		int month;
		int day;
		int NumberOfDays;
		double latitude;
		double longitude;
		double beta; /// angle between +z-axis of detector and North
		double JD;
		double T;
		double epsilon;
		double omega_bar;
		double e;
		double Mdot;
		double E;
		double tanv;
		double v;
		double lambda;
		double RA;
		double DEC;
		double H;
		double UT;
		double GST;
		double LST;
     
     /*
     * 
     * Class member functions
     * 
     * */
     
     public:
     
		SunTracker();
		~SunTracker();
		
		void Track();
		void UserInput();
		void Calculations(FILE* File);
		void CheckRange(double* );
		void CalculateRA();
		void PrintDayTrack(int , FILE* );
		void ConvertToGST();
	
};

#endif 

