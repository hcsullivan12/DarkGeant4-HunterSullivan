# SunTracking

SunTracking is a program designed to generate positions of the sun in the sky for a geographical location. These positions are converted into unit momentum direction three-vectors for input in DarkGeant4. This program was built to simulate high energy particles originating from the sun. 

## Building SunTracking

In the working directory, type the following commands to buil the application.

```
mkdir build
cd build
cmake ../
make

This creates an executable that the user can run to generate data file, SunTracking.dat, which contains unit momentum direction three-vectors over a selected time period at a selected geographical location.
