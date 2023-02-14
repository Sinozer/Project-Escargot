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

#include "Game/Game.h"
#include "Game/State/StateManager.h"
#include "Game/View/ViewManager.h"
#include "Game/Input/InputManager.h"
#include "Game/Asset/AssetManager.h"
#include "Game/State/State.h"
#include "Game/State/List/JoinState.h"
#include "Game/State/List/MainState.h"
#include "Game/View/View.h"
#include "Game/Physic/PhysicBodyManager.h"
#include "Game/Physic/PhysicBody.h"
#include "Game/Entity/Entity.h"
#include "Game/Entity/EntityManager.h"
#include "Game/Entity/Weapon/WeaponManager.h"
#include "Game/Entity/Weapon/Weapon.h"
#include "Game/Entity/Weapon/Range.h"
#include "Game/Entity/Weapon/Melee.h"
#include "Game/Entity/Projectile/Projectile.h"
#include "Game/Entity/Weapon/RangeWeapon/Bow.h"
#include "Game/Entity/LivingEntity/Player/Player.h"
#include "Game/Entity/LivingEntity/Enemy/Enemy.h"
#include "Game/Entity/LivingEntity/LivingEntity.h"
#include "Game/Map/Map.h"
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