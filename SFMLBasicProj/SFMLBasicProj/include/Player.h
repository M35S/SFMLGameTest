#pragma once

#include "Controls.h"
#include <AnimSprite.h>
#include <SFML/Graphics/Transform.hpp>
#include <SFML/System/Clock.hpp>
#include "MathTrigonometry.h"

class Player
{
public:
	/////////////////////////////////
	// Constant data members
	static const int DEF_SPEED = 200;
	static const int DEF_LIVES = 5;

public:
	/////////////////////////////////
	// Constructor
	Player(sf::AnimSprite sprite_p, PlayerControls controls_p, sf::Vector2f spawnPos_p);

	////////////////////////////////
	// Destructor
	~Player();

	
public:
	/////////////////////////////////
	// Function members
	void update(sf::Time tpf_p, sf::Time total_p);

public:
	////////////////////////////////
	// Data members
	sf::AnimSprite	player_m;	
	PlayerControls	controls_m;				
	sf::Vector2f	direction_m;	
	sf::Vector2f	spawnPos_m;		
	float			speed_m;		
	int				lives_m;		
	bool			visible_m;		
	bool			updatable_m;	
	bool			collidable_m;	
	sf::Time		lastChange_m;		
	int				idleFrame_m;
};