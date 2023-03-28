#pragma once

#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Clock.hpp>
#include <map>

enum class PlayerActions_e
{
	ACTION_UNKNOWN,
	MOVE_LEFT,
	MOVE_RIGHT,
	MOVE_UP,
	MOVE_DOWN,
	ANIM_INC_FRAME,
	ANIM_DEC_FRAME,
	FIRE_BULLET
};

class PlayerControls
{
public:
	//////////////////////////
	// Constructor
	PlayerControls();

	//////////////////////////
	// Destructor
	~PlayerControls();

public:
	///////////////////////////
	// Function members
	void setActionMapping(PlayerActions_e action_p, sf::Keyboard::Key key_p);
	void clearDefaults();

	PlayerActions_e getAction(sf::Keyboard::Key key_p);
	sf::Keyboard::Key getKey(PlayerActions_e action_p);

	void setFlag(PlayerActions_e action_p, bool flag_p);
	void setFlag(sf::Keyboard::Key key_p, bool flag_p);

	bool isActive(PlayerActions_e action_p);
	bool isActive(sf::Keyboard::Key key_p);

protected:
	//////////////////////////
	// Data members
	std::map<sf::Keyboard::Key, PlayerActions_e>	actions_m;
	std::map<PlayerActions_e, bool>					flags_m;
};


enum class CameraActions_e
{
	ACTION_UNKNOWN,
	MOVE_CAM_LEFT,
	MOVE_CAM_RIGHT,
	MOVE_CAM_UP,
	MOVE_CAM_DOWN,
	ROT_CAM_CW,
	ROT_CAM_CCW,
	ZOOM_CAM_IN,
	ZOOM_CAM_OUT
};

class CamControls
{
public:
	///////////////////////////
	// Constructor
	CamControls();

	//////////////////////////
	// Destructor
	~CamControls();

public:
	//////////////////////////
	// Function members
	void setActionMapping(CameraActions_e action, sf::Keyboard::Key key_p);
	void clearDefaults();

	CameraActions_e getAction(sf::Keyboard::Key key_p);
	sf::Keyboard::Key getKey(CameraActions_e action_p);

	void setFlag(CameraActions_e action_p, bool flag_p);
	void setFlag(sf::Keyboard::Key key_p, bool flag_p);

	bool isActive(CameraActions_e action_p);
	bool isActive(sf::Keyboard::Key key_p);

protected:
	////////////////////////////
	// Data members
	std::map<sf::Keyboard::Key, CameraActions_e>	actions_m;
	std::map<CameraActions_e, bool>					flags_m;
};