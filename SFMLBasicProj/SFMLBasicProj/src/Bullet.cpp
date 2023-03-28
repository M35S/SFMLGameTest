#include "Bullet.h"

/*
==================================================
File tite:		Bullet management
File Name:		Bullet.cpp
Purpose:		Setup and manage bullets.
==================================================
*/

/*
/////////////////////////////////////////////////////////
Name:		Bullet CONSTRUCTOR
Purpose:	Construct the bullet object.
Arguments:	sf::AnimSprite sprite_p
			Sprite container.

			sf::Vector2f dir_p
			Direction the bullet travels in.

			sf::Vector2f spawnPos_p
			x & y coordinates for spawn position.

			sf::Time spawnTime_p
			Specified time the enemies spawn in.
*/
Bullet::Bullet(sf::Sprite sprite_p, sf::Vector2f dir_p, sf::Vector2f spawnPos_p, sf::Time spawnTime_p) :
bullet_m(sprite_p),
direction_m(dir_p),
spawnPos_m(spawnPos_p),
spawnTime_m(spawnTime_p),
speed_m(static_cast<float>(DEF_SPEED)),
lifeTime_m(0.0f),
alpha_m(DEF_ALPHA),
visible_m(true),
updatable_m(true),
collidable_m(true)
{
	this->bullet_m.setPosition(spawnPos_p);
	sf::Color colour_t = this->bullet_m.getColor();
	colour_t.a = alpha_m;
	this->bullet_m.setColor(colour_t);
}

/*
/////////////////////////////////////////////////////////
Name:		Bullet DESTRUCTOR
Purpose:	Free's bullet object.
*/
Bullet::~Bullet()
{

}

/*
/////////////////////////////////////////////////////////
Name:		Update
Purpose:	Update the position of the bullet.

Argumenets:	sf::Time tpf_p
			Used to calculate bullet's motion.

			sf::Time total_p
			
*/
void Bullet::update(sf::Time tpf_p, sf::Time total_p)
{	
	float tpf_t = tpf_p.asSeconds();
	this->lifeTime_m += tpf_t;

	if (this->updatable_m)
		this->bullet_m.move(this->direction_m * this->speed_m * tpf_t);
}