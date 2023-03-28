#include "Background.h"

/*
==================================================
File tite:		Background management
File Name:		Background.cpp
Purpose:		Setup and manage the background images.
==================================================
*/

/*
/////////////////////////////////////////////////////////
Name:		Background CONSTRUCTOR
Purpose:	Construct the background object.
Arguments:	sf::AnimSprite sprite_p
			Sprite container.

			sf::Vector2f dir_p
			Direction the parallax images travel in.

			sf::Vector2f spawnPos_p
			x & y coordinates for spawning.

			sf::Time spawnTime_p
			Specified time for sprites to spawn.
*/
Background::Background(sf::Sprite sprite_p, sf::Vector2f dir_p, sf::Vector2f spawnPos_p, sf::Time spawnTime_p) :
direction_m(dir_p),
spawnPos_m(spawnPos_p),
speed_m(static_cast<float>(DEF_SPEED)),
alpha_m(DEF_ALPHA),
buildings_m(sprite_p),
spawnTime_m(spawnTime_p),
lifeTime_m(0.0f),
visible_m(true),
updatable_m(true)
{
	this->buildings_m.setPosition(spawnPos_p);
	sf::Color colour_t = this->buildings_m.getColor();
	colour_t.a = alpha_m;
	this->buildings_m.setColor(colour_t);
}

/*
/////////////////////////////////////////////////////////
Name:		Background DESTRUCTOR
Purpose:	Free the background object.
*/
Background::~Background()
{

}

/*
/////////////////////////////////////////////////////////
Name:		Update
Purpose:	Update the map object represented by this class.

Argumenets:	sf::Time tpf_p
			Used to calculate the motion path.

			sf::Time total_p
			
*/
void Background::update(sf::Time tpf_p, sf::Time total_p)
{	
	float tpf_t = tpf_p.asSeconds();
	this->lifeTime_m += tpf_t;
	if (this->updatable_m)
		this->buildings_m.move(this->direction_m * this->speed_m * tpf_t);
}