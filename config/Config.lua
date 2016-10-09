--[[

Config
~~~~~~~~~~~~~~~~~~

*ModuleName specifies the name of this module

*PhysicsList specifies which PhysicsList ought to be loaded at 
runtime. Options include the following

1."Default" (Uses the prepackaged physics list that comes with DarkGeant4)
2."QGSP_BERT"
3. ... 

*<Other parameters>

]]--

ConfigTable = { Module_Name = "Default",
                PhysicsList = "Default" }

--[[

File
~~~~~~~~~~~~~~~~~~

*File specifies a file to be loaded. It must give the entire path from the
executable's standpoint

*Type specifies the type of data stored in the file given.

1. Fourvector ( E, P_x, P_y, P_z)
2. ...

]]--

FileTable = { File = nil,
              Type = nil }
