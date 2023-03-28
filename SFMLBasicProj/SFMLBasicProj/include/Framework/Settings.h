#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <string>

class Settings
{
public:
	/////////////////////////////////
	// Constant Members 
	static const sf::Time		DEFAULT_APP_TARGET_TPF;		
	static const std::string	DEFAULT_APP_NAME;			
	static const bool			DEFAULT_APP_FULLSCRN_MODE;	
	static const char			DEFAULT_APP_VIDEO_MODE;		

	static const unsigned int	DEFAULT_APP_CUST_WIDTH;		
	static const unsigned int	DEFAULT_APP_CUST_HEIGHT;	
	static const unsigned int	DEFAULT_APP_CUST_CDEPTH;	

	static const unsigned int   DEFAULT_OGL_DEPTH_BUFF;		
	static const unsigned int   DEFAULT_OGL_STENCIL_BUFF;	
	static const unsigned int   DEFAULT_OGL_VERSION_MAJOR;	
	static const unsigned int   DEFAULT_OGL_VERSION_MINOR;  
	static const unsigned int   DEFAULT_OGL_MSAA_MODE;		

public:
	///////////////////////////////
	// Constructor
	Settings()
	{
		this->debugColour_m = sf::Color(255, 255, 255, 255);
		this->windowColour_m = sf::Color(0, 0, 0, 255);
		this->appWinStyle_m = DEFAULT_APP_FULLSCRN_MODE ? sf::Style::Fullscreen : sf::Style::Close;
		this->appName_m = DEFAULT_APP_NAME;

		if (DEFAULT_APP_VIDEO_MODE == 'U')			// U for Custom 'User'
			this->appVidMode_m = sf::VideoMode(DEFAULT_APP_CUST_WIDTH, DEFAULT_APP_CUST_HEIGHT, DEFAULT_APP_CUST_CDEPTH);
		else if (DEFAULT_APP_VIDEO_MODE == 'B')		// B for Best
			this->appVidMode_m = sf::VideoMode::getFullscreenModes()[0];
		else
			this->appVidMode_m = sf::VideoMode::getDesktopMode();
	}

public:
	///////////////////////////////
	// Destructor
	~Settings(){};

public:
	///////////////////////////////
	// Function Members
	
	// ---------- Accessors / Mutators ------------------------ //
	sf::Color		getDebugColour(){ return this->debugColour_m; }
	sf::Color		getClearColour(){ return this->windowColour_m; }
	std::string		getAppName(){ return this->appName_m; }
	sf::VideoMode   getVideoMode(){ return this->appVidMode_m; }
	unsigned int    getAppStyle(){ return this->appWinStyle_m; }

	sf::ContextSettings getContext()
	{
		sf::ContextSettings toggleSettings(DEFAULT_OGL_DEPTH_BUFF,
			DEFAULT_OGL_STENCIL_BUFF,
			DEFAULT_OGL_MSAA_MODE,
			DEFAULT_OGL_VERSION_MAJOR,
			DEFAULT_OGL_VERSION_MINOR);
		return toggleSettings;
	}

private:
	/////////////////////////////////
	// Data Members 
	std::string			appName_m;		
	sf::Color			debugColour_m;	
	sf::Color			windowColour_m;	
	unsigned int		appWinStyle_m;	
	sf::VideoMode		appVidMode_m;	
};