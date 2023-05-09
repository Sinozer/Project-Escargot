#pragma once

/* ###############################  INCLUDES   ############################### */

/* ##################  SFML  ################## */
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
/* ##################  SFML  ################## */

/* ################# STANDART ################# */
#include <fstream>
#include <iostream>
#include <memory>
#include <stack>
#include <map>
#include <string>
#include <algorithm>
#include <cstdint>
#include <chrono>
#include <random>

#include "json.hpp"
/* ################# STANDART ################# */

/* ###############################  INCLUDES   ############################### */

/* ############################### DEFINITIONS ############################### */

/* ################## DEBUG  ################## */
#define DEBUG false
#define DEBUG_LEAKS false
#define DEBUG_CONTROL false
/* ################## DEBUG  ################## */

/* ################## PHYSIC ################## */
#define GRAVITY 9.81f
#define PHYSIC_SCALE 100.0f
#define GAME_GRAVITY GRAVITY * PHYSIC_SCALE

#define PI 3.14159265358979323846

/* ########## MASKS ######### */
constexpr std::uint16_t MASK_COLLECTABLE	{ 0b0000'0001'0000'0000 };

constexpr std::uint16_t MASK_PLAYER			{ 0b0000'0000'1000'0000 };
constexpr std::uint16_t MASK_ENEMY			{ 0b0000'0000'0100'0000 };

constexpr std::uint16_t MASK_BULLET_PLAYER	{ 0b0000'0000'0000'1000 };
constexpr std::uint16_t MASK_BULLET_ENEMY	{ 0b0000'0000'0000'0100 };

constexpr std::uint16_t MASK_MAP_OBJECT		{ 0b0000'0000'0000'0010 };
constexpr std::uint16_t MASK_MAP			{ 0b0000'0000'0000'0001 };

constexpr std::uint16_t MASK_EMPTY			{ 0b1000'0000'0000'0000 };
/* ########## MASKS ######### */

/* ################## PHYSIC ################## */

/* ################## WINDOW ################## */

/* ######### SCREEN ######### */
#define WINDOW_SCREEN_WIDTH 1200
#define WINDOW_SCREEN_HEIGHT 800
#define WINDOW_SCREEN_FRAMERATE_LOW 30
#define WINDOW_SCREEN_FRAMERATE_MED 60
#define WINDOW_SCREEN_FRAMERATE_HIGH 120
/* ######### SCREEN ######### */

/* ################## WINDOW ################## */

/* ################## STATES ################## */

#define STATE_COUNT_MAX 5

/* ####### BACKGROUNDS ###### */
#define BACKGROUND_CANYON_FILEPATH "Resources/Textures/Backgrounds/Canyon.jpg"
#define BACKGROUND_DAYMOUNTAIN_FILEPATH "Resources/Textures/Backgrounds/DayMountain.jpg"
#define BACKGROUND_DESERT_FILEPATH "Resources/Textures/Backgrounds/Desert.jpg"
#define BACKGROUND_FOREST_FILEPATH "Resources/Textures/Backgrounds/Forest.jpg"
#define BACKGROUND_PINKDESERT_FILEPATH "Resources/Textures/Backgrounds/PinkDesert.jpg"
#define BACKGROUND_DAWNMOUNTAIN_FILEPATH "Resources/Textures/Backgrounds/DawnMountain.jpg"
/* ####### BACKGROUNDS ###### */

/* ######### AUDIOS ######### */
#define AUDIO_MUSIC_MENU_FILEPATH "Resources/Audio/Music/Menu.wav"
#define AUDIO_MUSIC_GAME_IDLE_FILEPATH "Resources/Audio/Music/GameIdle.wav"
#define AUDIO_MUSIC_GAME_PLAY_FILEPATH "Resources/Audio/Music/GamePlay.wav"

#define AUDIO_UI_BACK_FILEPATH "Resources/Audio/UI/back.wav"
#define AUDIO_UI_BACK_ECHO_FILEPATH "Resources/Audio/UI/back_echo.wav"
#define AUDIO_UI_CONFIRM_FILEPATH "Resources/Audio/UI/confirm.wav"
#define AUDIO_UI_CONFIRM_ECHO_FILEPATH "Resources/Audio/UI/confirm_echo.wav"
#define AUDIO_UI_CURSOR_FILEPATH "Resources/Audio/UI/cursor.wav"
#define AUDIO_UI_ERROR_FILEPATH "Resources/Audio/UI/error.wav"
#define AUDIO_UI_ERROR_ECHO_FILEPATH "Resources/Audio/UI/error_echo.wav"

#define	AUDIO_SFX_BOW_SHOOT_FILEPATH "Resources/Audio/SFX/BowShoot.wav"
#define	AUDIO_SFX_ENEMY_DAMAGED_FILEPATH "Resources/Audio/SFX/EnemyDamaged.wav"
#define	AUDIO_SFX_ENEMY_JUMP_FILEPATH "Resources/Audio/SFX/EnemyJump.wav" //Maybe trop relou, ils sautent plus que des lapins
#define	AUDIO_SFX_LOOT_AMMO_FILEPATH "Resources/Audio/SFX/LootAmmo.wav"
#define	AUDIO_SFX_LOOT_LIFE_FILEPATH "Resources/Audio/SFX/LootLife.wav"
#define	AUDIO_SFX_PLAYER_DAMAGED "Resources/Audio/SFX/PlayerDamaged.wav"
#define AUDIO_SFX_PLAYER_JUMP_FILEPATH "Resources/Audio/SFX/PlayerJump.wav"
/* ######### AUDIOS ######### */

/* ########## JOIN ########## */
#define STATE_JOIN_BACKGROUND_FILEPATH "Resources/Textures/Backgrounds/Join.jpg"
/* ########## JOIN ########## */

/* ########## MAIN ########## */
#define STATE_MAIN_BACKGROUND_FILEPATH "Resources/Textures/Backgrounds/Canyon.jpg"
/* ########## MAIN ########## */

/* ########## MAIN ########## */
#define STATE_GAME_BACKGROUND_FILEPATH "Resources/Textures/Backgrounds/DawnMountain.jpg"
/* ########## MAIN ########## */

/* ########## GAME ########## */
#define STATE_GAME_PLAYER_FILEPATH "Resources/Textures/Entities/Player.png"
#define STATE_GAME_DUMMY_ENTITY_FILEPATH "Resources/Textures/Entities/Test.png"

#define STATE_GAME_BASE_ENEMIES_AMOUNT 6
#define STATE_GAME_BASE_ENEMIES_DAMAGES 10
#define STATE_GAME_BASE_ENEMIES_DAMAGES_PER_WAVE 3

#define STATE_GAME_COLLECTABLE_LIFE_FILEPATH "Resources/Textures/Entities/Objects/heart.png"
#define STATE_GAME_COLLECTABLE_AMMO_FILEPATH "Resources/Textures/Entities/Objects/treasure_chest.png"

#define STATE_GAME_WEAPON_CROSSHAIR_FILEPATH "Resources/Textures/Crosshairs/White Retina/crosshair182.png"

#define STATE_GAME_PROJECTILE_ARROW_FILEPATH "Resources/Textures/Entities/Bullets/bullet11.png"
/* ########## GAME ########## */

/* ################## STATES ################## */

/* ############################### DEFINITIONS ############################### */

/* ###############################  INCLUDES   ############################### */

/* #################  SNAIL   ################# */
#include "Game/Game.h"
#include "Game/Math/Math.h"
#include "Game/Asset/AssetManager.h"
#include "Game/State/State.h"
/* #################  SNAIL   ################# */

/* ###############################  INCLUDES   ############################### */