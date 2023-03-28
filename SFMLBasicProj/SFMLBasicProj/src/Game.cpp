#include "Game.h"
#include <iostream>

#include "MathVector.h"
#include <algorithm>

/*
==================================================
File tite:		Game Management 
				(create, load, handle, update & render)
File Name:		Game.cpp
Purpose:		Initialises & manages game
==================================================
*/

/*
/////////////////////////////////////////////////////////
Name:		Game CONSTRUCTOR
Purpose:	Construct Game's window settings and Game's
			time based members for managing time.
*/
Game::Game(void) :
timeTPF_m(), 
timeTotal_m()
{

}

/*
/////////////////////////////////////////////////////////
Name:		Game DESTRUCTOR
Purpose:	Free Game's resources.
*/
Game::~Game(void)
{

}

/*
/////////////////////////////////////////////////////////
Name:		Initialise 
Purpose:	Setup & create SFML window's settings.
*/
void Game::initialise()
{
	//Create the Window. 
	this->window_m.create(this->settings_m.getVideoMode(),
						this->settings_m.getAppName(),
						this->settings_m.getAppStyle(),
						this->settings_m.getContext());
	this->window_m.setKeyRepeatEnabled(false);

#ifdef _DEBUG
	//Output our OpenGL Settings
	sf::err() << sf::getContextInfo(this->window_m);
#endif
}


/*
/////////////////////////////////////////////////////////
Name:		Load Content
Purpose:	Setup main game objects & assets.
			(world, players & enemies) 
*/
void Game::loadContent()
{
	//-------------Create our Game World-----------------------------------------
	this->gameWorld_m.create(sf::toFloat(this->window_m.getSize()));

	//-------------Create our Player Sprites-------------------------------------
	this->setupPlayer();

	//-------------Create the Alien Sprites--------------------------------------
	this->setupAliens();

	//-------------Create the Debug Elements-------------------------------------
#ifdef _DEBUG
	this->setupDebugText();
#endif 		
}

/*
/////////////////////////////////////////////////////////
Name:		Update
Purpose:	Update states of all game objects and cleanup redundant objects.
			(Enemies, Players, Bullets & Background) 
Argumenets:	sf::Time tpf_p
			Keep all game objects synchronized.
*/
void Game::update(sf::Time tpf_p)
{
	//-------GET THE UPDATE TIMES------------------------------------
	const float tpf_t = this->timeTPF_m.asSeconds();
	const float total_t = this->timeTotal_m.asSeconds();

	// -------UPDATE THE ALIENS---------------------------------------
	
	bool win_t = true;
	for (auto& enemy_t : this->aliensList_m)
	{
		if (enemy_t.updatable_m)		
		{	
			enemy_t.update(this->timeTPF_m, this->timeTotal_m);
			win_t = false;
		}
	}

	//-------UPDATE THE PLAYER---------------------------------------
	
	for (auto& player_t : this->playersList_m)
	{
		if (player_t.updatable_m)									
			player_t.update(this->timeTPF_m, this->timeTotal_m);

		if (player_t.lives_m < this->gameWorld_m.gameLives_m)		
			this->gameWorld_m.gameLives_m = player_t.lives_m;		
	}
	//-------UPDATE THE BULLETS--------------------------------------
	
	for (auto& playerBullet_t : this->bulletsList_m)
	{
		if (playerBullet_t.updatable_m)
			playerBullet_t.update(this->timeTPF_m, this->timeTotal_m);
	}

	//Fire a bullet every 0.8 seconds
	bool isAliens_t = this->aliensList_m.size() > 0;				
	if (this->timeTotal_m - this->timeNPCFire_m > sf::seconds(0.8f) && isAliens_t)
	{
		srand(this->timeTotal_m.asMilliseconds());

		bool validAlien_t = false;
		int enemyIndex_t = 0;
		while (!validAlien_t)
		{
			enemyIndex_t = rand() % this->aliensList_m.size();
			if (this->aliensList_m[enemyIndex_t].updatable_m)		
				validAlien_t = true;
		}
		this->fireEnemyBullet(enemyIndex_t, sf::Vector2f(-1, 0));
		this->timeNPCFire_m = this->timeTotal_m;
	}

	//Update the Enemies' Bullets
	for (auto& enemyBullet_t : this->enemyBulletsList_m)
	{
		if (enemyBullet_t.updatable_m)
			enemyBullet_t.update(this->timeTPF_m, this->timeTotal_m);
	}

	//--------------------COLLISION DETECTION AND RESPONSE-----------------------------
	for (auto& player_t : this->playersList_m)
	{
		for (auto& enemy_t : this->aliensList_m)
		{
			bool collisionCondition_t = player_t.collidable_m && enemy_t.collidable_m;										
			if (collisionCondition_t && player_t.player_m.getGlobalBounds().intersects(enemy_t.enemy_m.getGlobalBounds()))
			{
				//Set the State of the Enemy
				enemy_t.collidable_m = false;		
				enemy_t.visible_m = false;			
				enemy_t.updatable_m = false;		
				player_t.lives_m--;
			}
		}

		for (auto& enemyBullet_t : this->enemyBulletsList_m)
		{
			bool collisionCondition_t = player_t.collidable_m && enemyBullet_t.collidable_m;
			if (collisionCondition_t && player_t.player_m.getGlobalBounds().intersects(enemyBullet_t.bullet_m.getGlobalBounds()))
			{
				//Set the State of the Enemy
				enemyBullet_t.collidable_m = false;
				enemyBullet_t.visible_m = false;
				enemyBullet_t.updatable_m = false;
			}
		}
	}

	for (auto& enemy_t : this->aliensList_m)
	{
		for (auto& playerBullet_t : this->bulletsList_m)
		{
			bool collisionCondition_t = enemy_t.collidable_m && playerBullet_t.collidable_m;
			if (collisionCondition_t && enemy_t.enemy_m.getGlobalBounds().intersects(playerBullet_t.bullet_m.getGlobalBounds()))
			{
				//Set the State of the Enemy
				playerBullet_t.collidable_m = false;
				playerBullet_t.visible_m = false;
				playerBullet_t.updatable_m = false;

				enemy_t.collidable_m = false;		
				enemy_t.updatable_m = false;		
				enemy_t.visible_m = false;			

				this->gameWorld_m.gameScore_m += 100;
			}
		}
	}

	bool loss_t = this->gameWorld_m.gameLives_m <= 0;

	if (win_t)
	{
		this->gameWorld_m.gameMode_m = GamePlayMode_e::GAME_WON;
	}
	else if (loss_t)
	{
		this->gameWorld_m.gameMode_m = GamePlayMode_e::GAME_LOST;
	}

	// ------------------- Update Background ----------------------------------- //
	for (auto& bg_t : this->gameWorld_m.levelBackground_m)
	{
		if (bg_t.updatable_m)
		{
			float tpf_t = this->timeTPF_m.asSeconds();
			bg_t.lifeTime_m += tpf_t;
			bg_t.buildings_m.move(bg_t.direction_m * bg_t.speed_m * tpf_t);
		}
	}

	//---------------------UPDATE THE GAME WORLD---------------------------------------
	this->gameWorld_m.update(this->timeTPF_m, this->timeTotal_m);

	// --------------------- Game Object cleanup ------------------------------------
	// Clean up Alien enemies
	auto enemyItr_t = std::remove_if(this->aliensList_m.begin(), this->aliensList_m.end(), [&](Enemy& enemy_p)
	{
		bool dead_t = !enemy_p.collidable_m && !enemy_p.updatable_m && !enemy_p.visible_m;
		bool farLeft_t = enemy_p.enemy_m.getPosition().x < -100;
		return dead_t || farLeft_t;
	}
	);
	if (enemyItr_t != this->aliensList_m.end())
		this->aliensList_m.erase(enemyItr_t, this->aliensList_m.end());


	// Clean up the Redundant Player Bullets
	auto playerBulletItr_t = std::remove_if(this->bulletsList_m.begin(), this->bulletsList_m.end(), [&](Bullet& bullet_p)
	{
		bool dead_t = !bullet_p.collidable_m && !bullet_p.updatable_m && !bullet_p.visible_m;
		bool farRight_t = bullet_p.bullet_m.getPosition().x > 2000;
		return dead_t || farRight_t;
	}
	);
	if (playerBulletItr_t != this->bulletsList_m.end())
		this->bulletsList_m.erase(playerBulletItr_t, this->bulletsList_m.end());

	// Clean up the Redundant Enemy Bullets
	auto enemyBulletItr_t = std::remove_if(this->enemyBulletsList_m.begin(), this->enemyBulletsList_m.end(), [&](Bullet& enemy_p)
	{
		bool dead_t = !enemy_p.collidable_m && !enemy_p.updatable_m && !enemy_p.visible_m;
		bool farLeft_t = enemy_p.bullet_m.getPosition().x < -100;
		return dead_t || farLeft_t;
	}
	);
	if (enemyBulletItr_t != this->enemyBulletsList_m.end())
		this->enemyBulletsList_m.erase(enemyBulletItr_t, this->enemyBulletsList_m.end());

	// Clean up redundent parallax image
	auto bgItr_t = std::remove_if(this->gameWorld_m.levelBackground_m.begin(), this->gameWorld_m.levelBackground_m.end(), [&](Background& bg_p)
	{
		bool farLeft_t = bg_p.buildings_m.getPosition().x < -2500;
		return farLeft_t;
	}
	);
	if (bgItr_t != this->gameWorld_m.levelBackground_m.end())
	{
		this->gameWorld_m.levelBackground_m.erase(bgItr_t, this->gameWorld_m.levelBackground_m.end());

		// Create 2nd image
		sf::Sprite buildingsTwo_t;
		buildingsTwo_t.setTexture(this->gameWorld_m.resourceSprites_m.get(Assets_e::BG_TWO));
		buildingsTwo_t.setScale(sf::Vector2f(1.0f, 1.0f));
		buildingsTwo_t.setColor(sf::Color(255, 255, 255));
		sf::Vector2f pos_t(this->gameWorld_m.levelBackground_m[0].buildings_m.getPosition());
		sf::Vector2f offset_t(buildingsTwo_t.getLocalBounds().width, 0);
		sf::Vector2f dirTwo_t(-1, 0);
		Background buildingsObjTwo(buildingsTwo_t, dirTwo_t, pos_t + offset_t, sf::seconds(0));
		this->gameWorld_m.levelBackground_m.push_back(buildingsObjTwo);
	}
}

/*
/////////////////////////////////////////////////////////
Name:		Handle Events
Purpose:	Process any input events generated.
*/
void Game::handleEvents()
{
	//Create an Event Object
	sf::Event event_t;

	//Poll the Window for All Input Events (May be multiple in one frame)
	while (this->window_m.pollEvent(event_t))
	{
		//Switch Statement to decide between the different Event Types
		switch (event_t.type)
		{
		case sf::Event::KeyPressed:
			this->handleInput(event_t.key.code, true);
			break;
		case sf::Event::KeyReleased:
			this->handleInput(event_t.key.code, false);
			break;

			//If we have the Close request, close the window.
		case sf::Event::Closed:
			this->window_m.close();
			break;
		}
	}
}

/*
/////////////////////////////////////////////////////////
Name:		Handle Input
Purpose:	Process any key presses and releases.
Argumenets:	sf::Keyboard::Key key_p
			Used to determine which was key pressed.
			bool isPressed_p
			Used to determine key's flag state.
*/
void Game::handleInput(sf::Keyboard::Key key_p, bool isPressed_p)
{
	// Player fire controls update
	int index = 0;
	for (auto& player_t : this->playersList_m)
	{
		player_t.controls_m.setFlag(key_p, isPressed_p);											// "Controls" class member from class "LJMUPlayer" in "LJMUPlayer.h"
		if (player_t.controls_m.getKey(PlayerActions_e::FIRE_BULLET) == key_p && isPressed_p)		// "Controls" class member from class "LJMUPlayer" in "LJMUPlayer.h"
		{
			this->fireBullet(index, sf::Vector2f(1, 0));
			this->fireBullet(index, sf::Vector2f(1, -0.5f));
			this->fireBullet(index, sf::Vector2f(1, 0.5f));
		}
		index++;
	}
	
	// Game's camera controls update
	this->gameWorld_m.cameraControl_m.setFlag(key_p, isPressed_p);
}

/*
/////////////////////////////////////////////////////////
Name:		Render
Purpose:	Display sprites within the 2D game world.
*/
void Game::render()
{
	// Clear current buffer
	static sf::Color clear_t = this->settings_m.getClearColour();
	this->window_m.clear(clear_t);

	// Setup game's camera view
	this->window_m.setView(this->gameWorld_m.cameraGame_m);

	// Render  static background
	for (auto& bg_t : this->gameWorld_m.worldLevel_m)
		this->window_m.draw(bg_t);

	// Render background's parallax images
	for (auto& bg_t : this->gameWorld_m.levelBackground_m)
		this->window_m.draw(bg_t.buildings_m);

	// Render all visible enemies
	for (auto& alien_t : this->aliensList_m)
	{
		if (alien_t.visible_m)				
			this->window_m.draw(alien_t.enemy_m);	
	}

	// Render all visible players
	for (auto& player_t : this->playersList_m)
	{
		if (player_t.visible_m)						
			this->window_m.draw(player_t.player_m);	
	}

	// Render all player's bullets
	for (auto& plyrBullet_t : this->bulletsList_m)
	{
		if (plyrBullet_t.visible_m)
			this->window_m.draw(plyrBullet_t.bullet_m);
	}

	// Render all enemy bullets
	for (auto& enemyBullet_t : this->enemyBulletsList_m)
	{
		if (enemyBullet_t.visible_m)
			this->window_m.draw(enemyBullet_t.bullet_m);
	}
	
	// Setup game's HUD view
	this->window_m.setView(this->gameWorld_m.cameraHUD_m);

	// Render game's HUD
	for (auto& HUD_t : this->gameWorld_m.worldHUD_m)
		this->window_m.draw(HUD_t.second);

#if _DEBUG
	//Draw the FPS Text
	this->window_m.draw(this->textFPS_m);
#endif

	//Flip the Back Buffer with the Front Buffer
	this->window_m.display();
}

/*
/////////////////////////////////////////////////////////
Name:		Cleanup
Purpose:	Clean up any dynamically allocated resources.
*/
void Game::cleanup()
{

}

/*
/////////////////////////////////////////////////////////
Name:		Setup Player
Purpose:	Setup the Player's position, scale & sprites.
*/
void Game::setupPlayer()
{
	sf::Vector2f position_t(100, this->gameWorld_m.gameWorldBounds_m.height / 2.0f);
	sf::AnimSprite playerSprite_t;
	sf::AnimSeq spriteAnim_t;
	spriteAnim_t.setSpriteSheet(this->gameWorld_m.resourceSprites_m.get(Assets_e::PLAYER_ANIM));

	// ( int i = width; i < total frames width; i += width
	for (int i = 329; i < 3290; i += 329)
	{
		spriteAnim_t.addFrame(sf::IntRect(i, 0, 329, 255));		// (i, 0, width, height)
	}

	playerSprite_t.setScale(sf::Vector2f(0.5f, 0.5f));
	playerSprite_t.setAnimation(spriteAnim_t);
	sf::setOriginCentre(playerSprite_t);

	PlayerControls tplyrctrl;
	Player player_t(playerSprite_t, tplyrctrl, position_t);

	// new code bellow
	player_t.idleFrame_m = 3;			
	player_t.player_m.setFrame(3);		
	// end of new code
	this->playersList_m.push_back(player_t);
}

/*
/////////////////////////////////////////////////////////
Name:		Setup Aliens
Purpose:	Setup Alien's starting states 
			(numbers, positions, scales, sprites & motion types).
*/
void Game::setupAliens()
{
	int tstartx = this->window_m.getSize().x - 100;
	int tstarty = 100;
	const int NUM_OF_ENEMIES = 150;	

	// ----------- LOOP 1 -----------------------//
	for (int i = 0; i < NUM_OF_ENEMIES; i++)
	{
		sf::AnimSprite alienSprite_t;
		int columnIndex_t = i % 1;
		int rowIndex_t = (i - columnIndex_t);

		Assets_e texture_t = this->gameWorld_m.mapEnemyTexture_m[rowIndex_t % 3];	// "trowindex" uses enemy types from row 1 to 3 (ant, mosquito and wasp).
		// you can also use numbers e.g. 1 for enemy type such as mosquito.

		//Create the Animation sequence and add to the list
		sf::AnimSeq spriteAnim_t;
		spriteAnim_t.setSpriteSheet(this->gameWorld_m.resourceSprites_m.get(texture_t));	
		spriteAnim_t.addFrame(sf::IntRect(0, 0, 128, 128));
		spriteAnim_t.addFrame(sf::IntRect(128, 0, 128, 128));

		alienSprite_t.setAnimation(spriteAnim_t);
		alienSprite_t.setLooping(true);
		alienSprite_t.setFrameTime(sf::seconds(1));

		alienSprite_t.setScale(sf::Vector2f(0.4f, 0.4f));

		alienSprite_t.play(); 

		sf::setOriginCentre(alienSprite_t);

		alienSprite_t.setPosition(sf::Vector2f(1000000, 1000000));

		Enemy te(alienSprite_t, sf::Vector2f(-100, 0), sf::seconds(0));	// (X, Y) Enemy waiting outside game screen
		this->aliensList_m.push_back(te);
	}


	// ------ LOOP TECHNIQUE 2 ------------------
	// Enemies have regular timings and regular spacing.
	float startTime_t = 2.0f;
	int i = 0;
	for (auto& alien_t : this->aliensList_m)
	{
		alien_t.spawnPos_m = sf::Vector2f(1000, 500);	
		alien_t.spawnTime_m = sf::seconds(startTime_t);	
		if (i < 10)
			alien_t.motionType_m = EnemyMotion_e::LINEAR;
		else if (i < 20)
			alien_t.motionType_m = EnemyMotion_e::SINUSODIAL;
		else if (i < 30)
			alien_t.motionType_m = EnemyMotion_e::CIRCULAR;
		else if (i < 40)
			alien_t.motionType_m = EnemyMotion_e::SINUSODIAL;
		else if (i < 40)
			alien_t.motionType_m = EnemyMotion_e::QUADRATIC;
		else
			alien_t.motionType_m = EnemyMotion_e::SINUSODIAL;
		if (i == 9)
			startTime_t += 3.6f;
		else
			startTime_t += 0.6f;
		i++;
	}
}

/*
/////////////////////////////////////////////////////////
Name:		Move Background
Purpose:	Move the background's parallax sprites.
Argumenets:	int index_p
			Was initially used for array indexing.
			sf::Vector2f dir_p
			Determines which direction object is moving.
*/
void Game::moveBackground(int index_p, sf::Vector2f dir_p)
{
	sf::Sprite bg_t;
	bg_t.setTexture(this->gameWorld_m.resourceSprites_m.get(Assets_e::BG_TWO));
	bg_t.setScale(sf::Vector2f(1.0f, 1.0f));
	bg_t.setColor(sf::Color(255, 255, 255));

	sf::Vector2f offset_t(bg_t.getLocalBounds().width, 0);
	sf::Vector2f dir_t = dir_p;
}

/*
/////////////////////////////////////////////////////////
Name:		Fire Bullet
Purpose:	Fire the Player's bullet.
Argumenets:	int index_p
			Used for indexing player container.
			sf::Vector2f dir_p
			Used to determine bullet's movement direction.
*/
void Game::fireBullet(int index_p, sf::Vector2f dir_p)
{
	sf::Sprite tbullet;
	tbullet.setTexture(this->gameWorld_m.resourceSprites_m.get(Assets_e::BULLET));
	tbullet.setScale(sf::Vector2f(1.0f, 1.0f));
	tbullet.setColor(sf::Color(255, 255, 255));
	sf::setOriginCentre(tbullet);

	sf::Vector2f tpos(this->playersList_m[index_p].player_m.getPosition());		
	sf::Vector2f toffset(tbullet.getLocalBounds().width, 0);
	sf::Vector2f tdir = dir_p;

	Bullet tbulletobj(tbullet, tdir, tpos + toffset, this->timeTotal_m);
	this->bulletsList_m.push_back(tbulletobj);
}

/*
/////////////////////////////////////////////////////////
Name:		Fire Enemy Bullet
Purpose:	Fire the Enemy's bullet.
Argumenets:	int index_p
			Used to index the container of enemies.
			sf::Vector2f dir_p
			Determines an enemy's bullet's movement direction.
*/
void Game::fireEnemyBullet(int index_p, sf::Vector2f dir_p)
{
	sf::Sprite bulletSprite_t;
	bulletSprite_t.setTexture(this->gameWorld_m.resourceSprites_m.get(Assets_e::BULLET));
	bulletSprite_t.setScale(sf::Vector2f(1.0f, 1.0f));
	bulletSprite_t.setColor(sf::Color(0, 255, 0));
	sf::setOriginCentre(bulletSprite_t);

	sf::Vector2f position_t(this->aliensList_m[index_p].enemy_m.getPosition());
	sf::Vector2f offset_t(bulletSprite_t.getLocalBounds().width, 0);
	sf::Vector2f direction_t = dir_p;

	Bullet bullet_t(bulletSprite_t, direction_t, position_t - offset_t, this->timeTotal_m);
	this->enemyBulletsList_m.push_back(bullet_t);
}

// ---------------------- MAIN GAME LOOP -------------------------------- //

/*
/////////////////////////////////////////////////////////
Name:		Run Game Loop
Purpose:	Creates and handles the game's main sub-processes.
*/
void Game::runGameLoop()
{
	sf::Clock clock_t;
	sf::Time prevTime_t = clock_t.restart();

	//Initialise the Game Window
	this->initialise();
	this->loadContent();

	//Start the game loop - while the window is open, run. 
	while (this->window_m.isOpen())
	{
		this->timeTotal_m = clock_t.getElapsedTime();
		this->timeTPF_m = clock_t.getElapsedTime() - prevTime_t;
		prevTime_t = clock_t.getElapsedTime();

		this->handleEvents();
		this->update(this->timeTPF_m);
		this->render();
#ifdef _DEBUG
		this->textFPS_m.setString("Current FPS: " + sf::getFPS(this->timeTPF_m));
#endif
	}
	this->cleanup();
}

//-----------------------DEBUG ONLY METHODS----------------------- //

#ifdef _DEBUG

/*
/////////////////////////////////////////////////////////
Name:		Setup Debug Text
Purpose:	Setup the debugging text.
*/
void Game::setupDebugText()
{
	this->debugFont_m.loadFromFile("media/Fonts/Sansation.ttf");

	//Create a Text Object and Set the Font, Position and Character Size
	this->textFPS_m.setFont(this->debugFont_m);
	this->textFPS_m.setPosition(5.0f, this->window_m.getSize().y - 25.0f);
	this->textFPS_m.setColor(this->settings_m.getDebugColour());
	this->textFPS_m.setCharacterSize(18);
}

#endif