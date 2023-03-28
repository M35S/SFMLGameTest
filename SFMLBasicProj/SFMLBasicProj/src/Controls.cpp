#include "Controls.h"
#include <algorithm>

/*
==================================================
File tite:		Player & Camera Controls
File Name:		Controls.cpp
Purpose:		Setup and manage controls.
==================================================
*/

/*
/////////////////////////////////////////////////////////
Name:		Player Controls CONSTRUCTOR
Purpose:	Construct mappings of player's input controls.
*/
PlayerControls::PlayerControls()
{
	//Populate our Mappings of Key Controls
	this->actions_m.insert(std::make_pair(sf::Keyboard::Key::Left, PlayerActions_e::MOVE_LEFT));
	this->actions_m.insert(std::make_pair(sf::Keyboard::Key::Down, PlayerActions_e::MOVE_DOWN));
	this->actions_m.insert(std::make_pair(sf::Keyboard::Key::Right, PlayerActions_e::MOVE_RIGHT));
	this->actions_m.insert(std::make_pair(sf::Keyboard::Key::Up, PlayerActions_e::MOVE_UP));
	this->actions_m.insert(std::make_pair(sf::Keyboard::Key::M, PlayerActions_e::ANIM_DEC_FRAME));
	this->actions_m.insert(std::make_pair(sf::Keyboard::Key::N, PlayerActions_e::ANIM_INC_FRAME));
	this->actions_m.insert(std::make_pair(sf::Keyboard::Key::Space, PlayerActions_e::FIRE_BULLET));

	//Populate our Mappings of Flags for Actions
	this->flags_m.insert(std::make_pair(PlayerActions_e::MOVE_LEFT, false));
	this->flags_m.insert(std::make_pair(PlayerActions_e::MOVE_DOWN, false));
	this->flags_m.insert(std::make_pair(PlayerActions_e::MOVE_RIGHT, false));
	this->flags_m.insert(std::make_pair(PlayerActions_e::MOVE_UP, false));
	this->flags_m.insert(std::make_pair(PlayerActions_e::ANIM_DEC_FRAME, false));
	this->flags_m.insert(std::make_pair(PlayerActions_e::ANIM_INC_FRAME, false));
	this->flags_m.insert(std::make_pair(PlayerActions_e::FIRE_BULLET, false));
}

/*
/////////////////////////////////////////////////////////
Name:		Player Controls DESTRUCTOR
Purpose:	Free any redundant actions & flags mappings.
*/
PlayerControls::~PlayerControls()
{
	this->actions_m.erase(this->actions_m.begin(), this->actions_m.end());
	this->flags_m.erase(this->flags_m.begin(), this->flags_m.end());
}

/*
/////////////////////////////////////////////////////////
Name:		Set Action Mapping
Purpose:	Create mapping between an action and a Keyboard key.

Arguments:	PlayerActions_e action_p
			Provides the action type that was performed.

			sf::Keyboard::Key key_p
			Index's the map container via key.
*/
void PlayerControls::setActionMapping(PlayerActions_e action_p, sf::Keyboard::Key key_p)
{
	this->actions_m[key_p] = action_p;
	this->setFlag(action_p, false);
}

/*
/////////////////////////////////////////////////////////
Name:		Clear Defaults
Purpose:	Remove the default mappings.
*/
void PlayerControls::clearDefaults()
{
	this->actions_m.erase(this->actions_m.begin(), this->actions_m.end());
}

/*
/////////////////////////////////////////////////////////
Name:		Get Action
Purpose:	Get the action for a given key. If the key
			can't be found, then return the unknown
			action enumeration.

Arguments:	sf::Keyboard::Key key_p
			Used to determine which key to get.
*/
PlayerActions_e PlayerControls::getAction(sf::Keyboard::Key key_p)
{
	if (this->actions_m.find(key_p) != this->actions_m.end())
		return this->actions_m[key_p];
	else
		return PlayerActions_e::ACTION_UNKNOWN;
}

/*
/////////////////////////////////////////////////////////
Name:		Get Key
Purpose:	Get the first keyboard key mapping for an action.
			If it can't be found, then return the unknown key.

Arguments:	PlayerActions_e action_p
			Determines map's value type.
*/
sf::Keyboard::Key PlayerControls::getKey(PlayerActions_e action_p)
{
	auto position_t = std::find_if(std::begin(this->actions_m), std::end(this->actions_m),
		[&](const std::pair<sf::Keyboard::Key, PlayerActions_e> &pair)
	{
		return action_p == pair.second;
	});
	if (position_t != this->actions_m.end())
		return position_t->first;
	else
		return sf::Keyboard::Key::Unknown;
}

/*
/////////////////////////////////////////////////////////
Name:		Set Flag
Purpose:	Set the flag state for a given action.

Arguments:	PlayerActions_e action_p
			Index's the map's flag container.

			bool flag_p
			Used to set a key's flag value.
*/
void PlayerControls::setFlag(PlayerActions_e action_p, bool flag_p)
{
	this->flags_m[action_p] = flag_p;
}

/*
/////////////////////////////////////////////////////////
Name:		Is Active
Purpose:	Get the flag state for a given action.

Arguments:	PlayerActions_e action_p
			Determines a player's action type.
*/
bool PlayerControls::isActive(PlayerActions_e action_p)
{
	return this->flags_m[action_p];
}

/*
/////////////////////////////////////////////////////////
Name:		Set Flag
Purpose:	Set the flag state for a given key. If the key
			is not mapped to an action then nothing will happen.

Arguments:	sf::Keyboard::Key key_p
			Determines which key was pressed.

			bool flag_p
			Used to set a key's flag value.
*/
void PlayerControls::setFlag(sf::Keyboard::Key key_p, bool flag_p)
{
	if (this->actions_m.find(key_p) != this->actions_m.end())
		this->flags_m[this->actions_m[key_p]] = flag_p;
}

/*
/////////////////////////////////////////////////////////
Name:		Is Active
Purpose:	Get the flag state for a given key. If the key
			is not mappped to an action then the function 
			will return false.

Arguments:	sf::Keyboard::Key key_p
			Determine's map container's key.
*/
bool PlayerControls::isActive(sf::Keyboard::Key key_p)
{
	if (this->actions_m.find(key_p) != this->actions_m.end())
		return this->flags_m[this->actions_m[key_p]];
	return false;
}



/*
/////////////////////////////////////////////////////////
Name:		Camera Controls CONSTRUCTOR
Purpose:	Construct mappings of camera's input controls.
			(i.e. creates the default control scheme for the camera)
*/
CamControls::CamControls()
{
	//Populate our Mappings of Key Controls
	this->actions_m.insert(std::make_pair(sf::Keyboard::Key::A, CameraActions_e::MOVE_CAM_LEFT));
	this->actions_m.insert(std::make_pair(sf::Keyboard::Key::S, CameraActions_e::MOVE_CAM_DOWN));
	this->actions_m.insert(std::make_pair(sf::Keyboard::Key::D, CameraActions_e::MOVE_CAM_RIGHT));
	this->actions_m.insert(std::make_pair(sf::Keyboard::Key::W, CameraActions_e::MOVE_CAM_UP));
	this->actions_m.insert(std::make_pair(sf::Keyboard::Key::R, CameraActions_e::ROT_CAM_CCW));
	this->actions_m.insert(std::make_pair(sf::Keyboard::Key::T, CameraActions_e::ROT_CAM_CW));
	this->actions_m.insert(std::make_pair(sf::Keyboard::Key::Q, CameraActions_e::ZOOM_CAM_IN));
	this->actions_m.insert(std::make_pair(sf::Keyboard::Key::E, CameraActions_e::ZOOM_CAM_OUT));

	//Populate our Mappings of Flags for Actions
	this->flags_m.insert(std::make_pair(CameraActions_e::MOVE_CAM_LEFT, false));
	this->flags_m.insert(std::make_pair(CameraActions_e::MOVE_CAM_DOWN, false));
	this->flags_m.insert(std::make_pair(CameraActions_e::MOVE_CAM_RIGHT, false));
	this->flags_m.insert(std::make_pair(CameraActions_e::MOVE_CAM_UP, false));
	this->flags_m.insert(std::make_pair(CameraActions_e::ROT_CAM_CCW, false));
	this->flags_m.insert(std::make_pair(CameraActions_e::ROT_CAM_CW, false));
	this->flags_m.insert(std::make_pair(CameraActions_e::ZOOM_CAM_IN, false));
	this->flags_m.insert(std::make_pair(CameraActions_e::ZOOM_CAM_OUT, false));
}

/*
/////////////////////////////////////////////////////////
Name:		Camera Controls DESTRUCTOR
Purpose:	Free any redundant actions & flags mappings.
*/
CamControls::~CamControls()
{
	this->actions_m.erase(this->actions_m.begin(), this->actions_m.end());
	this->flags_m.erase(this->flags_m.begin(), this->flags_m.end());
}

/*
/////////////////////////////////////////////////////////
Name:		Set Action Mapping
Purpose:	Add a mapping between a given action and a Keyboard key.

Arguments:	CameraActions_e action_p
			Determines action value type.

			sf::Keyboard::Key key_p
			Key to indicate the action type.
*/
void CamControls::setActionMapping(CameraActions_e action_p, sf::Keyboard::Key key_p)
{
	this->actions_m[key_p] = action_p;
	this->setFlag(action_p, false);
}

/*
/////////////////////////////////////////////////////////
Name:		Clear Defaults
Purpose:	Remove the default mappings.
*/
void CamControls::clearDefaults()
{
	this->actions_m.erase(this->actions_m.begin(), this->actions_m.end());
}

/*
/////////////////////////////////////////////////////////
Name:		Get Action
Purpose:	Get the action that is mapped to a given key. 
			If no key can be found, then the unknown
			action is returned.

Arguments:	sf::Keyboard::Key key_p
			Determines which key to get.
*/
CameraActions_e CamControls::getAction(sf::Keyboard::Key key_p)
{
	if (this->actions_m.find(key_p) != this->actions_m.end())
		return this->actions_m[key_p];
	else
		return CameraActions_e::ACTION_UNKNOWN;
}

/*
/////////////////////////////////////////////////////////
Name:		Get Key
Purpose:	Get the first keyboard key found that is mapped to
			a given action. If no key can be found then the
			unknown key is return.

Arguments:	CameraActions_e action_p
			Determines which action value type to get.
*/
sf::Keyboard::Key CamControls::getKey(CameraActions_e action_p)
{
	auto position_t = std::find_if(std::begin(this->actions_m), std::end(this->actions_m),
		[&](const std::pair<sf::Keyboard::Key, CameraActions_e> &pair)
	{
		return action_p == pair.second;
	});
	if (position_t != this->actions_m.end())
		return position_t->first;
	else
		return sf::Keyboard::Key::Unknown;
}

/*
/////////////////////////////////////////////////////////
Name:		Set Flag
Purpose:	Set the flag state of the given action.

Arguments:	CameraActions_e action_p
			Determine's action type.

			bool flag_p
			Sets the key's flag value.
*/
void CamControls::setFlag(CameraActions_e action_p, bool flag_p)
{
	this->flags_m[action_p] = flag_p;
}

/*
/////////////////////////////////////////////////////////
Name:		Is Active
Purpose:	Return the flag state of the given action.

Arguments:	CameraActions_e action_p
			Determine's the action type to index.
*/
bool CamControls::isActive(CameraActions_e action_p)
{
	return this->flags_m[action_p];
}

/*
/////////////////////////////////////////////////////////
Name:		Set Flag
Purpose:	Set the flag state for the action that is mapped
			to the given key. If there is no key found then
			this function does nothing.

Arguments:	sf::Keyboard::Key key_p
			Used to find the key.

			bool flag_p
			Determines the key's flag value.
*/
void CamControls::setFlag(sf::Keyboard::Key key_p, bool flag_p)
{
	if (this->actions_m.find(key_p) != this->actions_m.end())
		this->flags_m[this->actions_m[key_p]] = flag_p;
}

/*
/////////////////////////////////////////////////////////
Name:		Is Active
Purpose:	Return the flag state of the action mapped to
			the given key. If there is no action mapped to
			the given key then this function will return false.

Arguments:	sf::Keyboard::Key key_p
			Determines the which action the key matches.
*/
bool CamControls::isActive(sf::Keyboard::Key key_p)
{
	if (this->actions_m.find(key_p) != this->actions_m.end())
		return this->flags_m[this->actions_m[key_p]];
	return false;
}