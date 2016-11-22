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

ConfigTable = { Module_Name = "Default",
                PhysicsList = "QGSP_BERT" }

--[[

	DarkGeantOutputFile
	
	* Name
	
		Not Required. By default will be "DarkGeantOutput.dat"
		
	* Location
	
		Not Required. Default will be the <present module path>/log

--]]
DarkGeantOutputFile = { Name = "DarkGeantOutput.dat",
                        Location = nil }
