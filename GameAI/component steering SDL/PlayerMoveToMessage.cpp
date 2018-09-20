#include "Game.h"
#include "GameMessageManager.h"
#include "PlayerMoveToMessage.h"
#include "UnitManager.h"

PlayerMoveToMessage::PlayerMoveToMessage( const Vector2D& pos )
:GameMessage(PLAYER_MOVETO_MESSAGE)
,mPos(pos)
{
}

PlayerMoveToMessage::~PlayerMoveToMessage()
{
}

void PlayerMoveToMessage::process()
{
	Unit* pPlayer = gpGame->getUnitManager()->getPlayerUnit();
<<<<<<< HEAD
	pPlayer->setSteering(Steering::ARRIVE_AND_FACE, mPos);
=======
	pPlayer->setSteering(Steering::WANDER, mPos);
>>>>>>> cb30918d63e15b62718a30e4012e92af8962e830
}

