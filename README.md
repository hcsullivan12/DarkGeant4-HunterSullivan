# DarkGeant4

DarkGeant4 is a Geant4 front-end whose purpose is to provide a generic Geant4 framework that minimizes startup time by being user friendly.

## Dependencies

Geant4.9.6 and lua5.2+ is required. Please be sure to have **lua5.2-dev** packages installed on your computer, otherwise the program simply won't compile.

## Supported Platforms

RHEL 6/7, its derivatives and Ubuntu 16.04 are fully supported. Instructions on installing DarkGeant4 and Geant4.x can be found within the [wiki](https://github.com/Davenport-Physics/DarkGeant4/wiki/Compiling-and-Installing-Geant4.9.6) for the various platforms.

Platforms not officially supported may still be able to run DG4, provided that the necessary dependencies are met.

### Known working platforms

Ubuntu 14.04 (cmake3 needs a ppa)

## Building DarkGeant4

In the working directory, type the following commands to build the application. Be aware the commands may need some modifications to suit your particular environment.

```
mkdir build
cd build
cmake -DGeant4_DIR=/path/to/Geant4/dir ../
make
```
If you do not have Geant4 installed, please see the [wiki](https://github.com/Davenport-Physics/DarkGeant4/wiki/Compiling-and-Installing-Geant4.9.6) for hints.

## Basic proton run.

```
./DarkGeant4 -vis
```

A window should be rendered on your screen with a basic cylindrical volume (Presently made out of liquid argon).

To see some action happen on screen, select your terminal and press enter. The code is presently waiting for a carriage return before it executes the run phase.

## Runtime Arguments

Pass the following command if you wish to have DarkGeant4 open a Geant4 rendering window. Note, rendering will cause your simulation to run for a longer period of time. In some cases, Geant4 may not be able to render your simulation if given a large enough world volume.

`-vis`

Pass the following command if you wish to have DarkGeant4 limit the information outputted to the terminal. Note, outputting data to the terminal will cause your simulation to run for a longer period of time.

`-lim-output`

Pass the following if you wish to have DarkGeant4 load a specific module of configuration.

`-module <module name>`

To specify the amount of threads you wish DarkGeant4 to use during simulations, pass the following command

`-num-threads #threads`

where #threads must be an integer value greater than or equal to 1.

## Using Python scripts for data analysis

The python scripts are written in python3, so be sure you have a python3 interpreter installed on your system with the necessary dependencies.

As of the time of this writing, scripts are separated by directories and further split into separate files to increase maintainability. To run one a script, simply type the following

```
python3 <dir>
ex.
python3 Histogram
```

Be sure to place associated files in the top directory, ie if you path is scripts/DarkGeantHelperScripts/Histogram, be sure to place data in scripts/DarkGeantHelperScripts/

## Collaborators

Emma Davenport  (Lead Developer - UTA Graduate Student) DarkGeant4

Hunter Sullivan (Developer - UTA Graduate Student) CorsikaToDarkGeant4Converter
