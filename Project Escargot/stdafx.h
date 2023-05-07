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

#include "json.hpp"
/* ################# STANDART ################# */

/* ###############################  INCLUDES   ############################### */

/* ############################### DEFINITIONS ############################### */

/* ################## DEBUG  ################## */
#define DEBUG false
#define DEBUG_CONTROL true
/* ################## DEBUG  ################## */

/* ################## PHYSIC ################## */
#define GRAVITY 9.81f
#define PHYSIC_SCALE 100.0f
#define GAME_GRAVITY GRAVITY * PHYSIC_SCALE

#define PI 3.14159265358979323846

/* ########## MASKS ######### */
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