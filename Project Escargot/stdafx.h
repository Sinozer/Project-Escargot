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

#include "json.hpp"
/* ################# STANDART ################# */

/* #################  SNAIL   ################# */
#include "Game/Math/Math.h"
#include "Game/Asset/AssetManager.h"
#include "Game/State/State.h"
/* #################  SNAIL   ################# */

/* ###############################  INCLUDES   ############################### */

/* ############################### DEFINITIONS ############################### */

/* ################## DEBUG  ################## */
#define DEBUG false
/* ################## DEBUG  ################## */

/* ################## PHYSIC ################## */
#define GRAVITY 9.81f
#define PHYSIC_SCALE 100.0f
#define GAME_GRAVITY GRAVITY * PHYSIC_SCALE
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

/* ########## JOIN ########## */
#define STATE_JOIN_BACKGROUND_FILEPATH "Resources/Textures/Backgrounds/Join.jpg"
/* ########## JOIN ########## */

/* ########## MAIN ########## */
#define STATE_MAIN_BACKGROUND_FILEPATH "Resources/Textures/Backgrounds/Canyon.jpg"
#define STATE_MAIN_ENTITY_TEST_FILEPATH "Resources/Textures/Entities/Test.png"
#define STATE_MAIN_DUMMY_ENTITY_TEST_FILEPATH "Resources/Textures/Entities/Box.png"
/* ########## MAIN ########## */

/* ################## STATES ################## */

/* ############################### DEFINITIONS ############################### */