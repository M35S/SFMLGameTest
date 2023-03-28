#include "Player.h"
#include "MathVector.h"

/*
==================================================
File tite:		Player management
File Name:		Player.cpp
Purpose:		Constructs & updates the Players.
==================================================
*/

/*
/////////////////////////////////////////////////////////
Name:		Player CONSTRUCTOR
Purpose:	Construct's the player object.

Argumenets:	sf::AnimSprite sprite_p
			Data structure for containing sprites.

			PlayerControls controls_p
			Map containers for action controls.

			sf::Vector2f spawnPos_p
			Defines x & y spawn coordinates. 
*/
Player::Player(sf::AnimSprite sprite_p, PlayerControls controls_p, sf::Vector2f spawnPos_p)
:
player_m(sprite_p),				
controls_m(controls_p),				
spawnPos_m(spawnPos_p),				
direction_m(0.0f, 0.0f),					
speed_m(static_cast<float>(DEF_SPEED)),		
lives_m(DEF_LIVES),							
visible_m(true),							
updatable_m(true),							
collidable_m(true),							

idleFrame_m(0),						
lastChange_m(sf::seconds(0))				
{
	this->player_m.setPosition(spawnPos_p);	
}

/*
/////////////////////////////////////////////////////////
Name:		Player DESTRUCTOR
Purpose:	Free's player object.
*/
Player::~Player()
{

}

/*
/////////////////////////////////////////////////////////
Name:		Update
Purpose:	Update player's position & animation.

Argumenets:	sf::Time tpf_p
			Used for calculating linear motion & last animation change.

			sf::Time total_p
			Used for calculating the next animation frame.
*/
void Player::update(sf::Time ptpf,sf::Time ptotal)
{
	// Move player UP, DOWN, LEFT or RIGHT
	sf::Vector2f tvel(0, 0);
	if (this->controls_m.isActive(PlayerActions_e::MOVE_UP))	
		tvel.y -= 1.0f;
	if (this->controls_m.isActive(PlayerActions_e::MOVE_RIGHT))	
		tvel.x += 1.0f;
	if (this->controls_m.isActive(PlayerActions_e::MOVE_LEFT))	
		tvel.x -= 1.0f;
	if (this->controls_m.isActive(PlayerActions_e::MOVE_DOWN))	
		tvel.y += 1.0f;

	this->direction_m = tvel;									
	if (sf::squaredVectLength(this->direction_m) > 0)			
	{
		this->direction_m = sf::unitVector(this->direction_m);	
	}

	this->player_m.move(this->direction_m * this->speed_m * ptpf.asSeconds());	

	// Animation for player movement
	this->lastChange_m += ptpf;										
	if (this->lastChange_m > sf::seconds(0.05f))					
	{
		if (this->controls_m.isActive(PlayerActions_e::MOVE_UP))		
		{
			this->player_m.incrementFrame(ptotal, false);				
			this->lastChange_m = sf::seconds(0);						
		}
		else if (this->controls_m.isActive(PlayerActions_e::MOVE_DOWN))	
		{
			this->player_m.decrementFrame(ptotal, false);	
			this->lastChange_m = sf::seconds(0);		
		}
		else
		{
			int tdiff = this->player_m.getFrameNo() - this->idleFrame_m;
			if (tdiff > 0)
			{
				this->player_m.decrementFrame(ptotal, false);		
				this->lastChange_m = sf::seconds(0);				
			}
			else if (tdiff < 0)
			{
				this->player_m.incrementFrame(ptotal, false);			
				this->lastChange_m = sf::seconds(0);				
			}
		}
	}	
}