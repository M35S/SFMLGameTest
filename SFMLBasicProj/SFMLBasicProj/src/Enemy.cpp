#include "Enemy.h"

/*
==================================================
File tite:		Enemy management
File Name:		Enemy.cpp
Purpose:		Constructs & updates the enemies.
==================================================
*/

/*
/////////////////////////////////////////////////////////
Name:		Enemy CONSTRUCTOR
Purpose:	Construct's the enemy object.

Argumenets:	sf::AnimSprite sprite_p
			Data structure for containing sprites.

			sf::Vector2f spawnPos_p
			Defines x & y spawn coordinates.

			sf::Time spawnTime_p
			Defines a time when an enemy is spawned.
*/
Enemy::Enemy(sf::AnimSprite sprite_p, sf::Vector2f spawnPos_p, sf::Time spawnTime_p) :
enemy_m(sprite_p),				
spawnPos_m(spawnPos_p),		
spawnTime_m(spawnTime_p),		
lifeTime_m(0.0f),				
visible_m(true),				
updatable_m(true),			
collidable_m(true),			

// Parameters for MotionTypes
parameter1_m(0.0f),	
parameter2_m(0.0f),	
parameter3_m(0.0f),	
parameter4_m(0.0f),	
motionType_m(EnemyMotion_e::LINEAR)		

{
	this->enemy_m.setPosition(spawnPos_p);		
}

/*
/////////////////////////////////////////////////////////
Name:		Enemy DESTRUCTOR
Purpose:	Free's enemy object.
*/
Enemy::~Enemy()
{

}

/*
/////////////////////////////////////////////////////////
Name:		Update
Purpose:	Update an enemy based on their current state.

Argumenets:	sf::Time tpf_p
			Used for sprite animation as well as life time for motion calculation.

			sf::Time total_p
			Helps to determine if enemy has spawned or not.
*/
void Enemy::update(sf::Time tpf_p, sf::Time total_p)
{	
	//Update the Sprite Sheet.
	this->enemy_m.update(tpf_p);

	const float ttpf = tpf_p.asSeconds();
	
	if (!this->updatable_m)	
		return;

	// If we have not spawned, return		
	if (this->spawnTime_m > total_p)
		return;								
	{
		//-----------ACCUMULATE THE FRAME TIME----------------
		this->lifeTime_m += ttpf;	

		sf::Vector2f tpos_at_t;
		
		// ---------- Linear Motion Type --------------------- //
		if (this->motionType_m == EnemyMotion_e::LINEAR)	
		{
			this->parameter3_m = -100;	
			this->parameter2_m = 10.0f;	
			this->parameter1_m = this->lifeTime_m * this->parameter2_m * this->parameter3_m;
			this->parameter4_m = 0.0f;

			tpos_at_t.x = this->spawnPos_m.x + this->parameter1_m;		
			tpos_at_t.y = this->parameter4_m * powf(tpos_at_t.x - this->parameter3_m, 2) + this->parameter2_m;
		}
		
		// ------------- Circular motion type  --------------- //
		else if (this->motionType_m == EnemyMotion_e::CIRCULAR)		
		{
			this->parameter2_m = 200.0f;
			this->parameter3_m = -0.9f;	
			this->parameter4_m = sf::Trig<float>::pi();
			this->parameter1_m = 3 * sf::Trig<float>::pi() * this->parameter3_m;
			this->parameter1_m *= this->lifeTime_m;	
			this->parameter1_m += this->parameter4_m;
			this->parameter2_m += 10 * ttpf;

			tpos_at_t.x = std::cosf(this->parameter1_m) * this->parameter2_m;
			tpos_at_t.y = std::sinf(this->parameter1_m) * this->parameter2_m;
		}
		// -------------- Sinusoidal motion type --------------- //
		else if (this->motionType_m == EnemyMotion_e::SINUSODIAL)	
		{
			this->parameter2_m = 250.0f;
			this->parameter3_m = -0.5f;	
			this->parameter4_m = -400.0f;
			this->parameter1_m = 4 * sf::Trig<float>::pi() * this->parameter3_m;
			this->parameter1_m *= this->lifeTime_m;		
			this->parameter4_m *= this->lifeTime_m;		

			tpos_at_t.x = this->parameter4_m;
			tpos_at_t.y = std::sinf(this->parameter1_m) * this->parameter2_m;
		}
		// --------------- Quadratic motion type ------------------- //
		else if (this->motionType_m == EnemyMotion_e::QUADRATIC)	
		{
			this->parameter4_m = 0.001f;
			this->parameter3_m = 700;
			this->parameter2_m = 500;
			this->parameter1_m = -this->lifeTime_m * 200.0f;	

			tpos_at_t.x = this->spawnPos_m.x + this->parameter1_m;		
			tpos_at_t.y = this->parameter4_m * powf(tpos_at_t.x - this->parameter3_m, 2) + this->parameter2_m;
			tpos_at_t += this->spawnPos_m;							
		}

		tpos_at_t += this->spawnPos_m;		
		this->enemy_m.setPosition(tpos_at_t);	
	}
}