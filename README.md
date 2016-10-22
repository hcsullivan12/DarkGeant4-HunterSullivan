# DarkGeant4

DarkGeant4 is a Geant4 application whose purpose is to provide a generic runtime framework for testing the various Dark Matter models. This software is presently being built and features may vary over time.

## Dependencies

Geant4 and lua5.2+ is required. Please be sure to have lua5.2-dev packages installed on your computer, otherwise the program simply won't compile.

## Building DarkGeant4

In the working directory, type the following commands to build the application. Be aware the commands may need some modifications to suit your particular environment.

```
mkdir build
cd build
cmake -DGeant4_DIR=/path/to/Geant4/dir ../
make
```

## Basic muon run.

The following command is subject to change with time.

```
./DarkGeant4 -execute basicrun.mac
```

A window should be rendered on your screen with a basic cylindrical volume (Presently made out of liquid argon).

To see some action happen on screen, select your terminal and press enter. The code is presently waiting for a carriage return before it executes the run phase.

## Using Python scripts for data analyse

The python scripts are written in python3, so be sure you have a python3 interpreter installed on your system with the necessary dependencies.

As of the time of this writing, scripts are separated by directories and further split into separate files to increase maintainability. To run one a script, simply type the following

```
python3 <dir>
ex.
python3 Histogram
```

Be sure to place associated files in the top directory, ie if you path is scripts/DarkGeantHelperScripts/Histogram, be sure to place data in scripts/DarkGeantHelperScripts/
