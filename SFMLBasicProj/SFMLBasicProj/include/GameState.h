#pragma once

#include "Controls.h"
#include "Assets.h"
#include "SFMLUtility.h"
#include <SFML/Graphics.hpp>
#include "Background.h"

enum class HUD_e
{
	SCORE,
	LIVES,
	TIME
};

enum class Colour_e
{
	RED,
	BLUE,
	GREEN,
	PURPLE,
	YELLOW,
	WHITE,
	PINK,
	CYAN,
	ORANGE
};

enum class GamePlayMode_e
{
	GAME_START,
	GAME_PLAYING,
	GAME_WON,
	GAME_LOST
};

class GameState
{
public:
	//////////////////////////////
	// Constructor
	GameState();

	/////////////////////////////
	// Destructor
	~GameState();

public:
	////////////////////////////
	// Function members
	void create(sf::Vector2f windowSize_p);
	void update(sf::Time tpf_p, sf::Time total_p);
	void destroy();

public:
	/////////////////////////////
	// Data members
	sf::View									cameraGame_m;
	sf::View									cameraHUD_m;
	CamControls									cameraControl_m;
	sf::ResourceHelper<sf::Texture, Assets_e>	resourceSprites_m;
	sf::ResourceHelper<sf::Font, Font_e>   	    resourceFonts_m;
	std::map<Colour_e, sf::Color>				resourceColour_m;
	std::map<int, Assets_e>						mapEnemyTexture_m;
	std::map<int, Colour_e>						mapEnemyColour_m;

	int											gameLives_m;
	int											gameScore_m;
	sf::Vector2f								gameWorldSize_m;
	sf::Vector2f								gameWorldWindow_m;
	sf::FloatRect								gameWorldBounds_m;
	GamePlayMode_e								gameMode_m;
	float                                       gamePlayTime_m;

	std::vector<sf::Sprite>						worldLevel_m;
	std::vector<Background>						levelBackground_m;
	std::map<HUD_e, sf::Text>					worldHUD_m;
};