#include "Settings.h"

//--------GAME CONSTANTS------------------------------------------------------
const sf::Time		  Settings::DEFAULT_APP_TARGET_TPF = sf::seconds(1.0f / 60.0f);	//Set the Target Frame Rate

//--------WINDOW SETTING CONSTANTS--------------------------------------------
const std::string	  Settings::DEFAULT_APP_NAME = "SFML Game Test";	//Set the Default Application Name
const unsigned int	  Settings::DEFAULT_APP_CUST_WIDTH = 1024U;		//Set the Default Screen Width
const unsigned int	  Settings::DEFAULT_APP_CUST_HEIGHT = 768U;		//Set the Default Screen Height
const unsigned int	  Settings::DEFAULT_APP_CUST_CDEPTH = 32U;		//Set the Default Colour Depth
const bool			  Settings::DEFAULT_APP_FULLSCRN_MODE = false;	//Set FullScreen Mode (True if FS, False otherwise)
const char			  Settings::DEFAULT_APP_VIDEO_MODE = 'U';		//Set the Video Mode 'U', 'B', 'D'

//--------OPEN GL CONSTANTS----------------------------------------------------
const unsigned int    Settings::DEFAULT_OGL_DEPTH_BUFF = 24U;	    //Set the OpenGL Depth Buffer
const unsigned int    Settings::DEFAULT_OGL_STENCIL_BUFF = 0U;		//Set the OpenGL Stencil Buffer
const unsigned int    Settings::DEFAULT_OGL_VERSION_MAJOR = 4U;		//Set the OpenGL Major Version
const unsigned int    Settings::DEFAULT_OGL_VERSION_MINOR = 4U;		//Set the OpenGL Minor Version
const unsigned int    Settings::DEFAULT_OGL_MSAA_MODE = 0U;		//Set the OpenGL Anti-Aliasing Mode