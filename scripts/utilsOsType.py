""" Utility module to determine the OS Python running on

	--------------------------------------------------------------------------
	File: 			utilsOsType.py

	Overview: 		Python module to supply functions and an enumeration to 
					help determine the platform type, bit size and OS currently
					being used.
									
	Environment:	OS:			Windows/LINUX/OSX
					IDE: 	    Visual Studio 2013 Plugin Python Tools (PTVS)
					Script:		Python 2.6 x64 

	Gotchas:		None.

	Copyright:		None.
	--------------------------------------------------------------------------
	
"""

# Python modules:
import sys		# Provide system information

# Third party modules:

# In-house modules:

# Instantiations:

# Enumerations:
#-----------------------------------------------------------------------------
# Details:	Class to implement a 'C' style enumeration type.
# Gotchas:	None.
# Authors:	Illya Rudkin 28/11/2013.
# Changes:	None.
#--
class EnumOsType( object ):
	values = [	"Unknown",
				"Windows", 
				"Linux", 
				"Darwin" ]; # OSX
	class __metaclass__( type ):
#++---------------------------------------------------------------------------
# Details:	Fn acts as an enumeration.
# Args:		vName - (R) Enumeration to match.
# Returns:	Int - Matching enumeration/index.
# Throws:	None.
#--
		def __getattr__( self, vName ):
			return self.values.index( vName );

#++---------------------------------------------------------------------------
# Details:	Reverse fast lookup of the values list.
# Args:		vI - (R) Index / enumeration.
# Returns:	Str - text description matching enumeration.
# Throws:	None.
#--
		def name_of( self, vI ):
			return EnumOsType.values[ vI ];

#-----------------------------------------------------------------------------
#-----------------------------------------------------------------------------
#-----------------------------------------------------------------------------

#++---------------------------------------------------------------------------
# Details:	Determine what operating system is currently running on.
# Args:		None.
# Returns:	EnumOsType - The OS type being used ATM.
# Throws:	None.
#--
def determine_os_type():
	eOSType = EnumOsType.Unknown;
	
	strOS = sys.platform
	if strOS == "win32":
		eOSType = EnumOsType.Windows;
	elif (strOS == "linux") or (strOS == "linux2"):
		eOSType = EnumOsType.Linux;
	elif strOS == "darwin":
		eOSType == EnumOsType.Darwin;
		
	return eOSType;
