--[[

Config
~~~~~~~~~~~~~~~~~~

	* Module_Name

	* PhysicsList

		1."Default"
		2."QGSP_BERT"
		3. ... 

	* <Other parameters>

]]--

ConfigTable = { Module_Name = "DUNE",
                PhysicsList = "QGSP_BERT" }

--[[

File
~~~~~~~~~~~~~~~~~~

	* File specifies a file to be loaded. It must give the entire path from the
	executable's standpoint

	* Type specifies the type of data stored in the file given.

		1. Fourvector ( E, P_x, P_y, P_z)
		2. ...

]]--

FileTable = { File = nil,
              Type = nil }
