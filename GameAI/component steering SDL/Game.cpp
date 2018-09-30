#include <stdio.h>
#include <assert.h>

#include <sstream>
#include <SDL.h>

#include "Game.h"
#include "GraphicsSystem.h"
#include "GraphicsBuffer.h"
#include "Font.h"
#include "GraphicsBufferManager.h"
#include "GameMessageManager.h"
#include "Sprite.h"
#include "SpriteManager.h"
#include "Timer.h"
#include "PlayerMoveToMessage.h"
#include "ComponentManager.h"
#include "UnitManager.h"
#include "EventSystem.h"
#include "Event.h"
#include "MousePosition.h"
#include "AEvent.h"
#include "Save.h"

#include <sstream>
#include <fstream>
#include <string>

Game* gpGame = NULL;

const int WIDTH = 1024;
const int HEIGHT = 768;
const Uint32 MAX_UNITS = 100;

Game::Game()
	:mpGraphicsSystem(NULL)
	,mpGraphicsBufferManager(NULL)
	,mpSpriteManager(NULL)
	,mpLoopTimer(NULL)
	,mpMasterTimer(NULL)
	,mpFont(NULL)
	,mShouldExit(false)
	,mBackgroundBufferID("")
	,mpMessageManager(NULL)
	,mpComponentManager(NULL)
	,mpUnitManager(NULL)
{
}

Game::~Game()
{
	cleanup();
}

bool Game::init()
{
	string number;
	string toOpen = "Data.txt";

	mFin.open(toOpen);
	if (mFin.good())
	{
		getline(mFin, number);
		mAlignmentWeight = atoi(number.c_str());

		getline(mFin, number);
		mCohesionWeight = atoi(number.c_str());

		getline(mFin, number);
		mSeparationWeight = atoi(number.c_str());

		getline(mFin, number);
		mWanderWeight = atoi(number.c_str());

		mFin.close();
	}
	else
	{
		cout << "Cant Open File" << endl;
	}
	mFin.close();

	mShouldCreateRandomUnit = false;
	mShouldExit = false;
	EventSystem::initInstance();
	EventSystem::getInstance()->addListener(ESCAPE_EVENT, this);
	EventSystem::getInstance()->addListener(MOUSE_POSITION_EVENT, this);
	EventSystem::getInstance()->addListener(D_EVENT, this);
	EventSystem::getInstance()->addListener(ENTER_EVENT, this);
	EventSystem::getInstance()->addListener(A_EVENT, this);
	EventSystem::getInstance()->addListener(SAVE, this);
	mSystem.init();


	//create Timers
	mpLoopTimer = new Timer;
	mpMasterTimer = new Timer;

	//create and init GraphicsSystem
	mpGraphicsSystem = new GraphicsSystem();
	bool goodGraphics = mpGraphicsSystem->init( WIDTH, HEIGHT );
	if(!goodGraphics) 
	{
		fprintf(stderr, "failed to initialize GraphicsSystem object!\n");
		return false;
	}

	mpGraphicsBufferManager = new GraphicsBufferManager(mpGraphicsSystem);
	mpSpriteManager = new SpriteManager();


	mpMessageManager = new GameMessageManager();
	mpComponentManager = new ComponentManager(MAX_UNITS);
	mpUnitManager = new UnitManager(MAX_UNITS);

	//load buffers
	mpGraphicsBufferManager->loadBuffer(mBackgroundBufferID,"wallpaper.bmp");
	mpGraphicsBufferManager->loadBuffer(mPlayerIconBufferID,"arrow.png");
	mpGraphicsBufferManager->loadBuffer(mEnemyIconBufferID,"enemy-arrow.png");
	mpGraphicsBufferManager->loadBuffer(mTargetBufferID,"target.png");

	//load Font
	mpFont = new Font("cour.ttf", 24);
	
	//setup sprites
	GraphicsBuffer* pBackGroundBuffer = mpGraphicsBufferManager->getBuffer( mBackgroundBufferID );
	if( pBackGroundBuffer != NULL )
	{
		mpSpriteManager->createAndManageSprite( BACKGROUND_SPRITE_ID, pBackGroundBuffer, 0, 0, (float)pBackGroundBuffer->getWidth(), (float)pBackGroundBuffer->getHeight() );
	}
	GraphicsBuffer* pPlayerBuffer = mpGraphicsBufferManager->getBuffer( mPlayerIconBufferID );
	Sprite* pArrowSprite = NULL;
	if( pPlayerBuffer != NULL )
	{
		pArrowSprite = mpSpriteManager->createAndManageSprite( PLAYER_ICON_SPRITE_ID, pPlayerBuffer, 0, 0, (float)pPlayerBuffer->getWidth(), (float)pPlayerBuffer->getHeight() );
	}
	GraphicsBuffer* pAIBuffer = mpGraphicsBufferManager->getBuffer(mEnemyIconBufferID);
	Sprite* pEnemyArrow = NULL;
	if (pAIBuffer != NULL)
	{
		pEnemyArrow = mpSpriteManager->createAndManageSprite(AI_ICON_SPRITE_ID, pAIBuffer, 0, 0, (float)pAIBuffer->getWidth(), (float)pAIBuffer->getHeight());
	}

	GraphicsBuffer* pTargetBuffer = mpGraphicsBufferManager->getBuffer(mTargetBufferID);
	if (pTargetBuffer != NULL)
	{
		mpSpriteManager->createAndManageSprite(TARGET_SPRITE_ID, pTargetBuffer, 0, 0, (float)pTargetBuffer->getWidth(), (float)pTargetBuffer->getHeight());
	}

	//setup units
	//Unit* pUnit = mpUnitManager->createPlayerUnit(*pArrowSprite);
	//pUnit->setShowTarget(true);
	////NEEED TO CHANGE THIS TO ARRIVE AND MESS WITH THINGS IN SEEKSTEERING!
	//pUnit->setSteering(Steering::SEEK, ZERO_VECTOR2D);

	////create 2 enemies
	//pUnit = mpUnitManager->createUnit(*pEnemyArrow, true, PositionData(Vector2D((float)gpGame->getGraphicsSystem()->getWidth()-1, 0.0f), 0.0f));
	//pUnit->setShowTarget(true);
	////CHANGE (Changed in UnitManager, SteeringComponent)
	//pUnit->setSteering(Steering::WANDER, ZERO_VECTOR2D, PLAYER_UNIT_ID);

	//pUnit = mpUnitManager->createUnit(*pEnemyArrow, true, PositionData(Vector2D(0.0f, (float)gpGame->getGraphicsSystem()->getHeight()-1), 0.0f));
	//pUnit->setShowTarget(false);
	//pUnit->setSteering(Steering::FLEE, ZERO_VECTOR2D, PLAYER_UNIT_ID);
	


	return true;
}

void Game::cleanup()
{
	//delete the timers
	delete mpLoopTimer;
	mpLoopTimer = NULL;
	delete mpMasterTimer;
	mpMasterTimer = NULL;

	delete mpFont;
	mpFont = NULL;

	//delete the graphics system
	delete mpGraphicsSystem;
	mpGraphicsSystem = NULL;

	delete mpGraphicsBufferManager;
	mpGraphicsBufferManager = NULL;
	delete mpSpriteManager;
	mpSpriteManager = NULL;
	delete mpMessageManager;
	mpMessageManager = NULL;
	delete mpUnitManager;
	mpUnitManager = NULL;
	delete mpComponentManager;
	mpComponentManager = NULL;

}

void Game::beginLoop()
{
	mpLoopTimer->start();
}

const float TARGET_ELAPSED_MS = LOOP_TARGET_TIME / 1000.0f;
	
void Game::processLoop()
{
	mSystem.updateKeyboard();
	mpUnitManager->updateAll(TARGET_ELAPSED_MS);
	mpComponentManager->update(TARGET_ELAPSED_MS);
	
	//draw background
	Sprite* pBackgroundSprite = mpSpriteManager->getSprite( BACKGROUND_SPRITE_ID );
	GraphicsBuffer* pDest = mpGraphicsSystem->getBackBuffer();
	mpGraphicsSystem->draw(*pDest, *pBackgroundSprite, 0.0f, 0.0f);

	//draw units
	mpUnitManager->drawAll();

	//create mouse text
	std::stringstream mousePos;
	mousePos << mSystem.getMousePosition().getX() << ":" << mSystem.getMousePosition().getY();

	//write text at mouse position
	mpGraphicsSystem->writeText(*mpFont, (float)mSystem.getMousePosition().getX(), (float)mSystem.getMousePosition().getY(), mousePos.str(), BLACK_COLOR);

	//test of fill region
	//mpGraphicsSystem->fillRegion(*pDest, Vector2D(300, 300), Vector2D(500, 500), RED_COLOR);
	mpGraphicsSystem->swap();

	mpMessageManager->processMessagesForThisframe();

	/*Unit* pUnit = mpUnitManager->createRandomUnit(*mpSpriteManager->getSprite(AI_ICON_SPRITE_ID));
	if (pUnit == NULL)
	{
		mpUnitManager->deleteRandomUnit();
	}*/

}

bool Game::endLoop()
{
	//mpMasterTimer->start();
	mpLoopTimer->sleepUntilElapsed( LOOP_TARGET_TIME );
	return mShouldExit;
}

void Game::handleEvent(const Event & theEvent)
{
	if (theEvent.getType() == ESCAPE_EVENT)
	{
		mShouldExit = true;
	}

	if (theEvent.getType() == MOUSE_POSITION_EVENT)
	{
		Vector2D pos(mSystem.getMousePosition().getX(), mSystem.getMousePosition().getY());
		GameMessage* pMessage = new PlayerMoveToMessage(pos);
		MESSAGE_MANAGER->addMessage(pMessage, 0);
	}

	if (theEvent.getType() == ENTER_EVENT && !mShouldExit)
	{
		//ADD RANDOM UNIT
		Unit* pUnit = mpUnitManager->createRandomUnit(*mpSpriteManager->getSprite(AI_ICON_SPRITE_ID));
		if (pUnit == NULL)
		{
			mpUnitManager->deleteRandomUnit();
		}
		cout << "Add random unit" << endl;
	}

	if (theEvent.getType() == D_EVENT)
	{
		//DELETE RANDOM UNIT
		mpUnitManager->deleteRandomUnit();
		cout << "delete random unit" << endl;
	}

	if (theEvent.getType() == A_EVENT)
	{
		//ADD 10 RANDOM UNIT
		Unit* pUnit = mpUnitManager->createRandomUnit(*mpSpriteManager->getSprite(AI_ICON_SPRITE_ID));
		if (pUnit == NULL)
		{
			mpUnitManager->deleteRandomUnit();
		}

		Unit* pUnit1 = mpUnitManager->createRandomUnit(*mpSpriteManager->getSprite(AI_ICON_SPRITE_ID));
		if (pUnit1 == NULL)
		{
			mpUnitManager->deleteRandomUnit();
		}

		Unit* pUnit2 = mpUnitManager->createRandomUnit(*mpSpriteManager->getSprite(AI_ICON_SPRITE_ID));
		if (pUnit2 == NULL)
		{
			mpUnitManager->deleteRandomUnit();
		}

		Unit* pUnit3 = mpUnitManager->createRandomUnit(*mpSpriteManager->getSprite(AI_ICON_SPRITE_ID));
		if (pUnit3 == NULL)
		{
			mpUnitManager->deleteRandomUnit();
		}

		Unit* pUnit4 = mpUnitManager->createRandomUnit(*mpSpriteManager->getSprite(AI_ICON_SPRITE_ID));
		if (pUnit4 == NULL)
		{
			mpUnitManager->deleteRandomUnit();
		}

		Unit* pUnit5 = mpUnitManager->createRandomUnit(*mpSpriteManager->getSprite(AI_ICON_SPRITE_ID));
		if (pUnit5 == NULL)
		{
			mpUnitManager->deleteRandomUnit();
		}

		Unit* pUnit6 = mpUnitManager->createRandomUnit(*mpSpriteManager->getSprite(AI_ICON_SPRITE_ID));
		if (pUnit6 == NULL)
		{
			mpUnitManager->deleteRandomUnit();
		}

		Unit* pUnit7 = mpUnitManager->createRandomUnit(*mpSpriteManager->getSprite(AI_ICON_SPRITE_ID));
		if (pUnit7 == NULL)
		{
			mpUnitManager->deleteRandomUnit();
		}

		Unit* pUnit8 = mpUnitManager->createRandomUnit(*mpSpriteManager->getSprite(AI_ICON_SPRITE_ID));
		if (pUnit8 == NULL)
		{
			mpUnitManager->deleteRandomUnit();
		}

		Unit* pUnit9 = mpUnitManager->createRandomUnit(*mpSpriteManager->getSprite(AI_ICON_SPRITE_ID));
		if (pUnit9 == NULL)
		{
			mpUnitManager->deleteRandomUnit();
		}
		
		
	}

	if (theEvent.getType() == SAVE)
	{
		//SAVE CERTAIN THINGS
		string toOpen = "Data.txt";
		mFout.open(toOpen);

		mFout << mAlignmentWeight << endl << mCohesionWeight << endl << mSeparationWeight << endl << mWanderWeight << endl;
		
		mFout.close();
	}
}

float genRandomBinomial()
{
	return genRandomFloat() - genRandomFloat();
}

float genRandomFloat()
{
	float r = (float)rand()/(float)RAND_MAX;
	return r;
}

