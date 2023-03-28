#pragma once

#include <SFML/Graphics/Transform.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Clock.hpp>
#include "MathTrigonometry.h"

class Bullet
{
public:
	///////////////////////////
	// Constant data members 
	static const int DEF_SPEED = 1000;	
	static const int DEF_ALPHA = 255;

public:
	///////////////////////////
	// Constructor
	Bullet(sf::Sprite sprite_p, sf::Vector2f dir_p, sf::Vector2f spawnPos_p, sf::Time spawnTime_p);
	
	//////////////////////////
	// Destructor
	~Bullet();

public:
	/////////////////////////
	// Function members
	void update(sf::Time tpf_p, sf::Time total_p);

public:
	/////////////////////////
	// Data members
	sf::Vector2f	direction_m;
	sf::Vector2f	spawnPos_m;
	float			speed_m;
	int				alpha_m;
	sf::Sprite		bullet_m;
	sf::Time		spawnTime_m;
	float			lifeTime_m;
	bool			visible_m;
	bool			updatable_m;
	bool			collidable_m;
};