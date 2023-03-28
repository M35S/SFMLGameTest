#pragma once

#include <AnimSprite.h>
#include <SFML/Graphics/Transform.hpp>
#include <SFML/System/Clock.hpp>
#include "MathTrigonometry.h"

enum class EnemyMotion_e	
{
	LINEAR,
	CIRCULAR,	
	SINUSODIAL,
	QUADRATIC
};	


class Enemy
{
public:
	/////////////////////////
	// Constructor
	Enemy(sf::AnimSprite sprite_p, sf::Vector2f spawnPos_p, sf::Time spawnTime_p);

	/////////////////////////
	// Destructor
	~Enemy();

public:
	/////////////////////////
	// Function members
	void update(sf::Time tpf_p, sf::Time total_p);

public:
	/////////////////////////
	// Data members
	sf::Vector2f		spawnPos_m;
	sf::AnimSprite		enemy_m;			
	sf::Time			spawnTime_m;	
	float				lifeTime_m;	
	bool				visible_m;		
	bool				updatable_m;	
	bool				collidable_m;	

	float				parameter1_m;		
	float				parameter2_m;		
	float				parameter3_m;		
	float				parameter4_m;		
	EnemyMotion_e		motionType_m;	
};