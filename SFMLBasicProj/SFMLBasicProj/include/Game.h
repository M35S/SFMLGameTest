#pragma once

// Include Game Classes
#include "Settings.h"
#include "GameState.h"
#include "Bullet.h"
#include "Player.h"
#include "Enemy.h"
#include "Background.h"

// Include C++ Libraries
#include <string>
#include <chrono> // Time
#include <vector> 
#include <array>
#include <map> 
#include <algorithm>
#include <memory>
#include <stdexcept>
#include <tuple>
#include <utility>
#include <thread>
#include <mutex>
#include <future>

class Game : private sf::NonCopyable		
{
public:
	/////////////////////////////
	// Constant data members
	static const unsigned int HUD_SCALE = 48;

public:
	////////////////////////////
	// Constructor
	Game(void);

	///////////////////////////
	// Destructor
	~Game(void);

public:
	///////////////////////////
	// Function members
	void runGameLoop();		// Controls the entire game loop of the application.

private:
	///////////////////////////
	// Function members
	void    initialise();		
	void    loadContent();      
	void	handleEvents();     
	void	update(sf::Time tpf_p);
	void	render();				
	void    cleanup();				
	void	handleInput(sf::Keyboard::Key key_p, bool pressed_p);

#ifdef _DEBUG
	void setupDebugText();
#endif

	//-----------Game Specific Functions----------------- //
	void setupPlayer();
	void setupAliens();
	void fireBullet(int index_p, sf::Vector2f dir_p);
	void fireEnemyBullet(int index_p, sf::Vector2f dir_p);
	void moveBackground(int index_p, sf::Vector2f dir_p);

private:
	/////////////////////////////////
	// Data members
	sf::Time				timeTPF_m;	
	sf::Time				timeTotal_m;	
	sf::Time				timeNPCFire_m;	
	sf::RenderWindow		window_m;		
	Settings				settings_m;		
	
	//-----------Game Objects------------------- //
	std::vector<Player>		playersList_m;
	std::vector<Enemy>		aliensList_m;
	std::vector<Bullet>		bulletsList_m;
	std::vector<Bullet>		enemyBulletsList_m;
	GameState				gameWorld_m;

#ifdef _DEBUG
	sf::Text				textFPS_m;		
	sf::Font				debugFont_m;
#endif
};