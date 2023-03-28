#include "GameState.h"
#include "MathVector.h"

/*
==================================================
File tite:		Game State Management (create & update)
File Name:		GameState.cpp
Purpose:		Initialises & manages the game states
==================================================
*/

/*
/////////////////////////////////////////////////////////
Name:		GameState CONSTRUCTOR
Purpose:	Construct Game's gameplay & resources.
*/
GameState::GameState() :
gameWorldWindow_m(),
cameraGame_m(),
cameraHUD_m(),
cameraControl_m(),
resourceSprites_m(),
resourceFonts_m(),
resourceColour_m(),
mapEnemyTexture_m(),
mapEnemyColour_m(),
gameWorldSize_m(),
gameWorldBounds_m(),
worldLevel_m(),
worldHUD_m(),
gamePlayTime_m(),
gameLives_m(),
gameScore_m(),
gameMode_m(GamePlayMode_e::GAME_START)
{

}

/*
/////////////////////////////////////////////////////////
Name:		GameState DESTRUCTOR
Purpose:	Free Game's gameplay & resources.
*/
GameState::~GameState()
{
	this->destroy();
}

/*
/////////////////////////////////////////////////////////
Name:		Create
Purpose:	Create the game state
			i.e. Setup gameplay data, sprites, font, HUD & camera.

Arguments:	sf::Vector2f windowSize_p
			Used to determine game world size.
*/
void GameState::create(sf::Vector2f windowSize_p)
{
	//----------SETUP THE GAME DATA---------------------------------------------------------
	this->gameScore_m = 0;
	this->gamePlayTime_m = 0.0f;
	this->gameLives_m = 3;
	this->gameWorldWindow_m = windowSize_p;
	this->gameWorldSize_m = this->gameWorldWindow_m;
	this->gameWorldBounds_m = sf::fromRectDimFloat(this->gameWorldSize_m);

	//----------SETUP UP THE GAME ASSETS----------------------------------------------------
	//Load the Default Font
	this->resourceFonts_m.load(Font_e::SANSATION, "media/Fonts/Sansation.ttf");
	this->resourceFonts_m.load(Font_e::RETRO, "media/Fonts/retrofont.ttf");
	this->resourceFonts_m.load(Font_e::SPACE, "media/Fonts/SPACE COWBOYS.ttf"); 
	this->resourceFonts_m.load(Font_e::ALIEN, "media/Fonts/ALIEN5.TTF");	
	this->resourceFonts_m.load(Font_e::DIGITAL, "media/Fonts/digital-7.ttf");	

	//Load the Sprite Textures which are used in the game
	this->resourceSprites_m.load(Assets_e::ANT_ONE, "media/Textures/si_anim1.png");		
	this->resourceSprites_m.load(Assets_e::MOSQUITO_ONE, "media/Textures/si_anim2.png");
	this->resourceSprites_m.load(Assets_e::WASP_ONE, "media/Textures/si_anim3.png");
	this->resourceSprites_m.load(Assets_e::BG_ONE, "media/Textures/bg_1.png");
	this->resourceSprites_m.load(Assets_e::BG_TWO, "media/Textures/bg_2.png");
	this->resourceSprites_m.load(Assets_e::PLAYER_ANIM, "media/Textures/player_anim.png");	
	this->resourceSprites_m.load(Assets_e::BULLET, "media/Textures/bullet.png");	

	//Create our Colour Palette Map
	this->resourceColour_m[Colour_e::RED] = sf::Color(255, 0, 0);
	this->resourceColour_m[Colour_e::BLUE] = sf::Color(0, 0, 255);
	this->resourceColour_m[Colour_e::GREEN] = sf::Color(0, 255, 0);
	this->resourceColour_m[Colour_e::PURPLE] = sf::Color(255, 0, 255);
	this->resourceColour_m[Colour_e::YELLOW] = sf::Color(255, 255, 0);
	this->resourceColour_m[Colour_e::WHITE] = sf::Color(255, 255, 255);
	this->resourceColour_m[Colour_e::PINK] = sf::Color(255, 0, 220);
	this->resourceColour_m[Colour_e::CYAN] = sf::Color(0, 220, 255);
	this->resourceColour_m[Colour_e::ORANGE] = sf::Color(255, 150, 0);

	//----------SETUP THE MAPS OF ENEMY TYPES------------------------------------------------
	//Create our Dictionary of Indices to Texture Type
	this->mapEnemyTexture_m[0] = Assets_e::ANT_ONE;	
	this->mapEnemyTexture_m[1] = Assets_e::MOSQUITO_ONE;
	this->mapEnemyTexture_m[2] = Assets_e::WASP_ONE;

	//----------CREATE THE GAME LEVEL---------------------------------------------------------

	//Populate our Level Background
	this->worldLevel_m.push_back(sf::Sprite(this->resourceSprites_m.get(Assets_e::BG_ONE)));

	// Setup parallax image layer for background
	sf::Sprite buildings_t;
	buildings_t.setTexture(this->resourceSprites_m.get(Assets_e::BG_TWO));
	buildings_t.setScale(sf::Vector2f(1.0f, 1.0f));
	buildings_t.setColor(sf::Color(255, 255, 255));
	sf::Vector2f spawnPos_t(0, 0);
	sf::Vector2f dir_t(-1, 0);
	Background buildingsObj(buildings_t, dir_t, spawnPos_t, sf::seconds(0));
	this->levelBackground_m.push_back(buildingsObj);

	// Create 2nd image
	sf::Sprite buildingsTwo_t;
	buildingsTwo_t.setTexture(this->resourceSprites_m.get(Assets_e::BG_TWO));
	buildingsTwo_t.setScale(sf::Vector2f(1.0f, 1.0f));
	buildingsTwo_t.setColor(sf::Color(255, 255, 255));
	sf::Vector2f pos_t(this->levelBackground_m[0].buildings_m.getPosition());
	sf::Vector2f offset_t(buildingsTwo_t.getLocalBounds().width, 0);
	sf::Vector2f dirTwo_t(-1, 0);
	Background buildingsObjTwo(buildingsTwo_t, dirTwo_t, pos_t + offset_t, sf::seconds(0));
	this->levelBackground_m.push_back(buildingsObjTwo);

	//----------CREATE THE HUD----------------------------------------------------------------
	float gap_t = (this->gameWorldBounds_m.width / 4.0f);
	float x_t = -50;
	float y_t = 20;
	const int HUD_SCALE = 48;

	this->worldHUD_m[HUD_e::LIVES] = sf::Text("", this->resourceFonts_m.get(Font_e::DIGITAL), HUD_SCALE);
	this->worldHUD_m[HUD_e::LIVES].setString("Lives : ");
	this->worldHUD_m[HUD_e::LIVES].setPosition(x_t + gap_t, y_t);
	this->worldHUD_m[HUD_e::LIVES].setColor(this->resourceColour_m[Colour_e::CYAN]);

	this->worldHUD_m[HUD_e::SCORE] = sf::Text("", this->resourceFonts_m.get(Font_e::ALIEN), HUD_SCALE);
	this->worldHUD_m[HUD_e::SCORE].setString("Score : ");
	this->worldHUD_m[HUD_e::SCORE].setPosition(x_t + gap_t * 2, y_t);
	this->worldHUD_m[HUD_e::SCORE].setColor(this->resourceColour_m[Colour_e::PINK]);

	this->worldHUD_m[HUD_e::TIME] = sf::Text("", this->resourceFonts_m.get(Font_e::ALIEN), HUD_SCALE);
	this->worldHUD_m[HUD_e::TIME].setString("Time : ");
	this->worldHUD_m[HUD_e::TIME].setPosition(x_t + gap_t * 3, y_t);
	this->worldHUD_m[HUD_e::TIME].setColor(this->resourceColour_m[Colour_e::PINK]);

	//-----------SETUP OUR GAME CAMERA--------------------------------------------------------
	//Setup our Game Camera
	sf::Vector2f camCentre_t = this->gameWorldSize_m * 0.5f;
	this->cameraGame_m.reset(this->gameWorldBounds_m);
	this->cameraGame_m.setCenter(camCentre_t);

	//Setup our HUD Camera
	this->cameraHUD_m.reset(this->gameWorldBounds_m);
	this->cameraHUD_m.setCenter(camCentre_t);
}

/*
/////////////////////////////////////////////////////////
Name:		Update
Purpose:	Update the game state
			i.e. gameplay data, camera movement & HUD display.
Arguments:	sf::Time tpf_p
			Used for synching camera movements & game timer.
			sf::Time total_p
*/
void GameState::update(sf::Time tpf_p, sf::Time total_p)
{
	this->gamePlayTime_m += tpf_p.asSeconds();
	float tpf_t = tpf_p.asSeconds();

	// Update game camera's movement (translation, rotation & scaling)
	float zoomFactor_t = 1;
	if (this->cameraControl_m.isActive(CameraActions_e::MOVE_CAM_LEFT))
		this->cameraGame_m.move(sf::Vector2f(-200.0f* tpf_t, 0));
	if (this->cameraControl_m.isActive(CameraActions_e::MOVE_CAM_RIGHT))
		this->cameraGame_m.move(sf::Vector2f(200.0f* tpf_t, 0));
	if (this->cameraControl_m.isActive(CameraActions_e::MOVE_CAM_UP))
		this->cameraGame_m.move(sf::Vector2f(0, -200.0f* tpf_t));
	if (this->cameraControl_m.isActive(CameraActions_e::MOVE_CAM_DOWN))
		this->cameraGame_m.move(sf::Vector2f(0, 200.0f* tpf_t));
	if (this->cameraControl_m.isActive(CameraActions_e::ROT_CAM_CCW))
		this->cameraGame_m.rotate(180.0f * tpf_t);
	if (this->cameraControl_m.isActive(CameraActions_e::ROT_CAM_CW))
		this->cameraGame_m.rotate(-180.0f * tpf_t);
	if (this->cameraControl_m.isActive(CameraActions_e::ZOOM_CAM_OUT))
		zoomFactor_t -= 1.0f * tpf_t;
	if (this->cameraControl_m.isActive(CameraActions_e::ZOOM_CAM_IN))
		zoomFactor_t += 1.0f * tpf_t;
	this->cameraGame_m.zoom(zoomFactor_t);

	// Update game's HUD (gameplay, win & lose)

	// Gameplay HUD
	int displayTime_t = static_cast<int>(std::floor(this->gamePlayTime_m));
	this->worldHUD_m[HUD_e::SCORE].setString("Score : " + std::to_string(this->gameScore_m));
	this->worldHUD_m[HUD_e::LIVES].setString("Lives : " + std::to_string(this->gameLives_m));
	this->worldHUD_m[HUD_e::TIME].setString("Time:  " + std::to_string(displayTime_t));

	// Won HUD
	if (this->gameMode_m == GamePlayMode_e::GAME_WON)
	{
		this->worldHUD_m[HUD_e::SCORE].setString("");
		this->worldHUD_m[HUD_e::LIVES].setString("PLAYER WINS");
		this->worldHUD_m[HUD_e::TIME].setString("");
	}
	// Lost HUD
	else if (this->gameMode_m == GamePlayMode_e::GAME_LOST)
	{
		this->worldHUD_m[HUD_e::SCORE].setString("");
		this->worldHUD_m[HUD_e::LIVES].setString("GAME OVER");
		this->worldHUD_m[HUD_e::TIME].setString("");
	}
}

/*
/////////////////////////////////////////////////////////
Name:		Destroy
Purpose:	Destroy the game state
*/
void GameState::destroy()
{

}