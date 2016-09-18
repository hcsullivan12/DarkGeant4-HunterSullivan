# DarkGeant4

DarkGeant4 is a Geant4 application whose purpose is to provide a generic runtime framework for testing the various Dark Matter models. This software is presently being built and features may vary over time.

## Building DarkGeant4

In the working directory, type the following commands to build the application. Be aware the commands may need some modifications to suit your particular environment.

```
mkdir build
cd build
cmake -DGeant4_DIR=/path/to/Geant4/dir ../
make
```

## Basic muon run.

The following command is subject to change with time

```
./DarkGeant4 -execute basicrun.mac
```
