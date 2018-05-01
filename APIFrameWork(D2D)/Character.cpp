#include "stdafx.h"
#include "Character.h"


Character::Character()
{}

Character::~Character()
{}

HRESULT Character::init(void)
{
	_dir = DOWN;
	isWalk = false;

	// 이미지 키값 인덱스
	// action
	character_action[WAKEUP] = L"player_wakeup";
	character_action[EAT] = L"player_eat";
	character_action[HUNGRY] = L"player_hungry";
	character_action[DEATH] = L"player_death";
	character_action[ACTION_BUILD] = L"player_build";
	character_action[ACTION_PICKUP] = L"player_pickup";
	character_action[ITEM_IN] = L"player_item_in";
	character_action[ITEM_OUT] = L"player_item_out";
	character_action[ACTION_FX] = L"player_actionFX";
	// run
	character_action[RUN] = L"player_run";
	character_action[RUN_TORCH] = L"player_run_torch";
	character_action[ACTION_AXE] = L"player_axe";
	character_action[ACTION_PICKAXE] = L"player_pickaxe";
	character_action[IDLE] = L"player_idle";
	character_action[IDLE_TORCH] = L"player_idle_torch";
	character_action[IDLE_SANITY] = L"player_idle_sanity";

	// item_in, item_out, wakeup
	character_order[NONE_ORDER] = L"_none";
	// idle, idle_torch, pickup, actionFX,
	character_order[NONE_DOWN] = L"_down";
	character_order[NONE_RIGHT] = L"_right";
	character_order[NONE_LEFT] = L"_left";
	character_order[NONE_UP] = L"_up";
	// idle_sanity, build, run, run_torch, axe, pickaxe
	character_order[PRE_DOWN] = L"_pre_down";
	character_order[PRE_RIGHT] = L"_pre_right";
	character_order[PRE_LEFT] = L"_pre_left";
	character_order[PRE_UP] = L"_pre_up";
	character_order[LOOP_DOWN] = L"_loop_down";
	character_order[LOOP_RIGHT] = L"_loop_right";
	character_order[LOOP_LEFT] = L"_loop_left";
	character_order[LOOP_UP] = L"_loop_up";
	character_order[PST_DOWN] = L"_pst_down";
	character_order[PST_RIGHT] = L"_pst_right";
	character_order[PST_LEFT] = L"_pst_left";
	character_order[PST_UP] = L"_pst_up";

	eAction = WAKEUP;
	eOrder = NONE_ORDER;
	isOpening = true;
	isKeyUp = false;
	isKeyDown = false;
	isKeyRight = false;
	isKeyLeft = false;
	isActionWork = false;
	isTorch = false;

	triCount = 0;

	_position.x = MAPMAX_X / 2 - 500;
	_position.y = MAPMAX_X / 2 - 500;
	mousePt = _position;
	frameX = 0;
	frameY = 0;
	count = 1;

	CAMERAMANAGER->setPositionMemotyRick(&_position);
	return S_OK;
}

void Character::release(void)
{
}

void Character::update(CHARACTER_ACTION mCharcterAction) {
	eAction = mCharcterAction;

	if (!isActionWork) {
		switch (eAction)
		{
		case ACTION_FX:
		case ACTION_PICKUP:
		case IDLE_TORCH:
		case IDLE:
			switch (_dir)
			{
			case DOWN:
				eOrder = NONE_DOWN;
				count = 0;
				isActionWork = true;
				break;
			case UP:
				eOrder = NONE_UP;
				count = 0;
				isActionWork = true;
				break;
			case LEFT:
				eOrder = NONE_LEFT;
				count = 0;
				isActionWork = true;
				break;
			case RIGHT:
				eOrder = NONE_RIGHT;
				count = 0;
				isActionWork = true;
				break;
			}
			break;
		case ACTION_BUILD:
		case IDLE_SANITY:
		case RUN:
		case RUN_TORCH:
		case ACTION_AXE:
		case ACTION_PICKAXE:
			switch (_dir)
			{
			case DOWN:
				eOrder = PRE_DOWN;
				count = 0;
				isActionWork = true;
				break;
			case UP:
				eOrder = PRE_UP;
				count = 0;
				isActionWork = true;
				break;
			case LEFT:
				eOrder = PRE_LEFT;
				count = 0;
				isActionWork = true;
				break;
			case RIGHT:
				eOrder = PRE_RIGHT;
				count = 0;
				isActionWork = true;
				break;
			}
			break;
		}
	}

	selectAction();
}
void Character::update()
{
	keyInput();
	move();
	selectAction();
	if (isWalk) {
		if (!SOUNDMANAGER->isPlaySound("walkSound")) {
			SOUNDMANAGER->bgmPlay("walkSound");
		}
	}
}

void Character::render(void)
{
	tmp = character_action[eAction] + character_order[eOrder];
	float height = WINSIZEY_NUM / 2;  // - 0.5 * (IMAGEMANAGER->findImage(tmp)->getHeight() / 10)
	float width = WINSIZEX_NUM / 2;// -0.15 * (IMAGEMANAGER->findImage(tmp)->getWidth() / 10);
	IMAGEMANAGER->frameBottomRender(tmp, Rt, width, height, frameX, 0);
}

void Character::move()
{
	if (isWalk && (eOrder == LOOP_DOWN || eOrder == LOOP_UP || eOrder == LOOP_LEFT || eOrder == LOOP_RIGHT)) {
		if (isKeyDown && !isKeyLeft && !isKeyRight) {
			if (_position.y + SPEED <= MAPMAX_X - 350) {
				_position.y += SPEED;
				eOrder = LOOP_DOWN;
			}
		}
		else if (isKeyDown && isKeyLeft && !isKeyRight) {
			if (_position.x - SPEED * 0.707 >= 350 && _position.y + SPEED * 0.707 <= MAPMAX_X - 350) {
				_position.x -= SPEED * 0.707;
				_position.y += SPEED * 0.707;
				eOrder = LOOP_LEFT;
			}
		}
		else if (isKeyDown && !isKeyLeft && isKeyRight) {
			if (_position.x + SPEED * 0.707 <= MAPMAX_X - 350 && _position.y + SPEED * 0.707 <= MAPMAX_X - 350) {
				_position.x += SPEED * 0.707;
				_position.y += SPEED * 0.707;
				eOrder = LOOP_RIGHT;
			}
		}
		if (isKeyUp && !isKeyLeft && !isKeyRight) {
			if (_position.y - SPEED >= 350) {
				_position.y -= SPEED;
				eOrder = LOOP_UP;
			}
		}
		else if (isKeyUp && isKeyLeft && !isKeyRight) {
			if (_position.x - SPEED * 0.707 >= 350 && _position.y - SPEED * 0.707 >= 350) {
				_position.x -= SPEED * 0.707;
				_position.y -= SPEED * 0.707;
				eOrder = LOOP_LEFT;
			}
		}
		else if (isKeyUp && !isKeyLeft && isKeyRight) {
			if (_position.x + SPEED * 0.707 <= MAPMAX_X - 350 && _position.y - SPEED * 0.707 >= 350) {
				_position.x += SPEED * 0.707;
				_position.y -= SPEED * 0.707;
				eOrder = LOOP_RIGHT;
			}
		}
		if (isKeyLeft && !isKeyDown && !isKeyUp) {
			if (_position.x - SPEED >= 350) {
				_position.x -= SPEED;
				eOrder = LOOP_LEFT;
			}
		}
		if (isKeyRight && !isKeyDown && !isKeyUp) {
			if (_position.x + SPEED <= MAPMAX_X - 350) {
				_position.x += SPEED;
				eOrder = LOOP_RIGHT;
			}
		}
		if (isKeyLeft && isKeyRight) {
			isWalk = false;
		}
	}
}

void Character::keyInput() {
	// up remove
	if (KEYMANAGER->isOnceKeyUp('W')) {
		isWalk = false;
		isKeyUp = false;
		if (!isKeyUp && !isKeyLeft && !isKeyRight && !isKeyDown)
			eOrder = PST_UP;
	}
	//down remove
	if (KEYMANAGER->isOnceKeyUp('S')) {
		isWalk = false;
		isKeyDown = false;
		if (!isKeyUp && !isKeyLeft && !isKeyRight && !isKeyDown)
			eOrder = PST_DOWN;
	}
	//left remove
	if (KEYMANAGER->isOnceKeyUp('A')) {
		isWalk = false;
		isKeyLeft = false;
		if (!isKeyUp && !isKeyLeft && !isKeyRight && !isKeyDown)
			eOrder = PST_LEFT;
	}
	//right remove
	if (KEYMANAGER->isOnceKeyUp('D')) {
		isWalk = false;
		isKeyRight = false;
		if (isTorch)	eAction = RUN_TORCH;
		else eAction = RUN;
		if (!isKeyUp && !isKeyLeft && !isKeyRight && !isKeyDown)
			eOrder = PST_RIGHT;
	}

	// up
	if ((!isKeyUp && !isKeyDown && !isKeyLeft && !isKeyRight) && KEYMANAGER->isOnceKeyDown('W')) {
		eOrder = PRE_UP;
	}
	if (KEYMANAGER->isStayKeyDown('W')) {
		isWalk = true;
		isKeyUp = true;
		if (isTorch)	eAction = RUN_TORCH;
		else eAction = RUN;
		if (!isKeyLeft && !isKeyRight)
			_dir = UP;
		if (isKeyUp) _dir = UP;
	}
	// down
	if ((!isKeyUp && !isKeyDown && !isKeyLeft && !isKeyRight) && KEYMANAGER->isOnceKeyDown('S')) {
		eOrder = PRE_DOWN;
	}
	if (KEYMANAGER->isStayKeyDown('S')) {
		isWalk = true;
		isKeyDown = true;
		if (isTorch)	eAction = RUN_TORCH;
		else eAction = RUN;
		if (!isKeyLeft && !isKeyRight)
			_dir = DOWN;
		if (isKeyDown) _dir = DOWN;
	}
	//left	
	if ((!isKeyUp && !isKeyDown && !isKeyLeft && !isKeyRight) && KEYMANAGER->isOnceKeyDown('A')) {
		eOrder = PRE_LEFT;
	}
	if (KEYMANAGER->isStayKeyDown('A')) {
		isWalk = true;
		isKeyLeft = true;
		if (isTorch)	eAction = RUN_TORCH;
		else eAction = RUN;
		if (!isKeyUp && !isKeyDown)
			_dir = LEFT;
		if (isKeyLeft) _dir = LEFT;
	}
	//right
	if ((!isKeyUp && !isKeyDown && !isKeyLeft && !isKeyRight) && KEYMANAGER->isOnceKeyDown('D')) {
		eOrder = PRE_RIGHT;
	}
	if (KEYMANAGER->isStayKeyDown('D')) {
		isWalk = true;
		isKeyRight = true;
		if (isTorch)	eAction = RUN_TORCH;
		else eAction = RUN;
		if (!isKeyUp && !isKeyDown)
			_dir = RIGHT;
		if (isKeyRight) _dir = RIGHT;
	}

}

void Character::selectAction()
{
	switch (eAction)
	{
	case WAKEUP:
		switch (eOrder)
		{
		case NONE_ORDER:
			count++;
			frameX = count / CHARACTER_SPEED % 20;
			if (frameX == 19) {
				frameX = 0;
				count = 0;
				if (isTorch)	eAction = IDLE_TORCH;
				else eAction = IDLE;
				isActionWork = false;
			}
			break;
		}
		break;
	case EAT:
		switch (eOrder)
		{
		case NONE_ORDER:
			count++;
			frameX = count / CHARACTER_SPEED % 20;
			if (frameX == 19) {
				frameX = 0;
				count = 0;
				if (isTorch)	eAction = IDLE_TORCH;
				else eAction = IDLE;
				isActionWork = false;
			}
			break;
		}
		break;
	case HUNGRY:
		switch (eOrder)
		{
		case NONE_ORDER:
			count++;
			frameX = count / CHARACTER_SPEED % 20;
			if (frameX == 19) {
				frameX = 0;
				count = 0;
				if (isTorch)	eAction = IDLE_TORCH;
				else eAction = IDLE;
				isActionWork = false;
			}
			break;
		}
		break;
	case DEATH:
		switch (eOrder)
		{
		case NONE_ORDER:
			count++;
			frameX = count / CHARACTER_SPEED % 20;
			if (frameX == 19) {
				frameX = 0;
				count = 0;
				if (isTorch)	eAction = IDLE_TORCH;
				else eAction = IDLE;
				isActionWork = false;
			}
			break;
		}
		break;
	case ITEM_IN:
		switch (eOrder)
		{
		case NONE_ORDER:
			count++;
			frameX = count / CHARACTER_SPEED % 20;
			if (frameX == 19) {
				frameX = 0;
				count = 0;
				if (isTorch)	eAction = IDLE_TORCH;
				else eAction = IDLE;
				isActionWork = false;
			}
			break;
		}
		break;
	case ITEM_OUT:
		switch (eOrder)
		{
		case NONE_ORDER:
			count++;
			frameX = count / CHARACTER_SPEED % 20;
			if (frameX == 19) {
				frameX = 0;
				count = 0;
				if (isTorch)	eAction = IDLE_TORCH;
				else eAction = IDLE;
				isActionWork = false;
			}
			break;
		}
		break;
	case ACTION_BUILD:
		switch (_dir)
		{
		case DOWN:
			switch (eOrder)
			{
			case PRE_DOWN:
				count++;
				frameX = (count / CHARACTER_SPEED) % 14;
				if (frameX == 13) {
					frameX = 0;
					count = 0;
					eOrder = LOOP_DOWN;
				}
				break;
			case LOOP_DOWN:
				count++;
				frameX = (count / CHARACTER_SPEED) % 10;
				if (frameX == 9) {
					frameX = 0;
					count = 0;
					eOrder = PST_DOWN;
				}
				break;
			case PST_DOWN:
				count++;
				frameX = (count / CHARACTER_SPEED) % 10;
				if (frameX == 9) {
					frameX = 0;
					count = 0;
					if (isTorch)	eAction = IDLE_TORCH;
					else eAction = IDLE;
					eOrder = NONE_DOWN;
					isActionWork = false;
				}
				break;
			}
			break;
		case UP:
			switch (eOrder)
			{
			case PRE_UP:
				count++;
				frameX = (count / CHARACTER_SPEED) % 14;
				if (frameX == 13) {
					frameX = 0;
					count = 0;
					eOrder = LOOP_UP;
				}
				break;
			case LOOP_UP:
				count++;
				frameX = (count / CHARACTER_SPEED) % 10;
				if (frameX == 9) {
					frameX = 0;
					count = 0;
					eOrder = PST_UP;
				}
				break;
			case PST_UP:
				count++;
				frameX = (count / CHARACTER_SPEED) % 10;
				if (frameX == 9) {
					frameX = 0;
					count = 0;
					if (isTorch)	eAction = IDLE_TORCH;
					else eAction = IDLE;
					eOrder = NONE_UP;
					isActionWork = false;
				}
				break;
			}
			break;
		case LEFT:
			switch (eOrder)
			{
			case PRE_LEFT:
				count++;
				frameX = (count / CHARACTER_SPEED) % 14;
				if (frameX == 13) {
					frameX = 0;
					count = 0;
					eOrder = LOOP_LEFT;
				}
				break;
			case LOOP_LEFT:
				count++;
				frameX = (count / CHARACTER_SPEED) % 10;
				if (frameX == 9) {
					frameX = 0;
					count = 0;
					eOrder = PST_LEFT;
				}
				break;
			case PST_LEFT:
				count++;
				frameX = (count / CHARACTER_SPEED) % 10;
				if (frameX == 9) {
					frameX = 0;
					count = 0;
					if (isTorch)	eAction = IDLE_TORCH;
					else eAction = IDLE;
					eOrder = NONE_LEFT;
					isActionWork = false;
				}
				break;
			}
			break;
		case RIGHT:
			switch (eOrder)
			{
			case PRE_RIGHT:
				count++;
				frameX = (count / CHARACTER_SPEED) % 14;
				if (frameX == 13) {
					frameX = 0;
					count = 0;
					eOrder = LOOP_RIGHT;
				}
				break;
			case LOOP_RIGHT:
				count++;
				frameX = (count / CHARACTER_SPEED) % 10;
				if (frameX == 9) {
					frameX = 0;
					count = 0;
					eOrder = PST_RIGHT;
				}
				break;
			case PST_RIGHT:
				count++;
				frameX = (count / CHARACTER_SPEED) % 10;
				if (frameX == 9) {
					frameX = 0;
					count = 0;
					if (isTorch)	eAction = IDLE_TORCH;
					else eAction = IDLE;
					eOrder = NONE_RIGHT;
					isActionWork = false;
				}
				break;
			}
			break;
		}
		break;
	case ACTION_FX:
		switch (_dir)
		{
		case DOWN:
			eOrder = NONE_DOWN;
			count++;
			frameX = count / CHARACTER_SPEED % 10;
			if (frameX == 9) {
				frameX = 0;
				count = 0;
			}
			break;
		case UP:
			eOrder = NONE_UP;
			count++;
			frameX = count / CHARACTER_SPEED % 10;
			if (frameX == 9) {
				frameX = 0;
				count = 0;
			}
			break;
		case LEFT:
			eOrder = NONE_LEFT;
			count++;
			frameX = count / CHARACTER_SPEED % 10;
			if (frameX == 9) {
				frameX = 0;
				count = 0;
			}
			break;
		case RIGHT:
			eOrder = NONE_RIGHT;
			count++;
			frameX = count / CHARACTER_SPEED % 10;
			if (frameX == 9) {
				frameX = 0;
				count = 0;
			}
			break;
		default:
			break;
		}
		break;
	case ACTION_PICKUP:
		switch (_dir)
		{
		case DOWN:
			eOrder = NONE_DOWN;
			count++;
			frameX = count / CHARACTER_SPEED % 10;
			if (frameX == 9) {
				frameX = 0;
				count = 0;
				if (isTorch)	eAction = IDLE_TORCH;
				else eAction = IDLE;
				isActionWork = false;
			}
			break;
		case UP:
			eOrder = NONE_UP;
			count++;
			frameX = count / CHARACTER_SPEED % 10;
			if (frameX == 9) {
				frameX = 0;
				count = 0;
				if (isTorch)	eAction = IDLE_TORCH;
				else eAction = IDLE;
				isActionWork = false;
			}
			break;
		case LEFT:
			eOrder = NONE_LEFT;
			count++;
			frameX = count / CHARACTER_SPEED % 10;
			if (frameX == 9) {
				frameX = 0;
				count = 0;
				if (isTorch)	eAction = IDLE_TORCH;
				else eAction = IDLE;
				isActionWork = false;
			}
			break;
		case RIGHT:
			eOrder = NONE_RIGHT;
			count++;
			frameX = count / CHARACTER_SPEED % 10;
			if (frameX == 9) {
				frameX = 0;
				count = 0;
				if (isTorch)	eAction = IDLE_TORCH;
				else eAction = IDLE;
				isActionWork = false;
			}
			break;
		default:
			break;
		}
		break;
	case IDLE:
		if (isTorch) eAction = IDLE_TORCH;
		switch (_dir)
		{
		case DOWN:
			eOrder = NONE_DOWN;
			count++;
			frameX = count / CHARACTER_SPEED % 10;
			if (frameX == 9) {
				frameX = 0;
				count = 0;
			}
			break;
		case UP:
			eOrder = NONE_UP;
			count++;
			frameX = count / CHARACTER_SPEED % 10;
			if (frameX == 9) {
				frameX = 0;
				count = 0;
			}
			break;
		case LEFT:
			eOrder = NONE_LEFT;
			count++;
			frameX = count / CHARACTER_SPEED % 10;
			if (frameX == 9) {
				frameX = 0;
				count = 0;
			}
			break;
		case RIGHT:
			eOrder = NONE_RIGHT;
			count++;
			frameX = count / CHARACTER_SPEED % 10;
			if (frameX == 9) {
				frameX = 0;
				count = 0;
			}
			break;
		default:
			break;
		}
		break;
	case IDLE_SANITY:
		switch (_dir)
		{
		case DOWN:
			switch (eOrder)
			{
			case PRE_DOWN:
				count++;
				frameX = (count / CHARACTER_SPEED) % 10;
				if (frameX == 9) {
					frameX = 0;
					count = 0;
					eOrder = LOOP_DOWN;
				}
				break;
			case LOOP_DOWN:
				count++;
				frameX = (count / CHARACTER_SPEED) % 10;
				if (frameX == 9) {
					frameX = 0;
					count = 0;
					if (isTorch)	eAction = IDLE_TORCH;
					else eAction = IDLE;
					eOrder = NONE_DOWN;
					isActionWork = false;
				}
				break;
			}
			break;
		case UP:
			switch (eOrder)
			{
			case PRE_UP:
				count++;
				frameX = (count / CHARACTER_SPEED) % 10;
				if (frameX == 9) {
					frameX = 0;
					count = 0;
					eOrder = LOOP_UP;
				}
				break;
			case LOOP_UP:
				count++;
				frameX = (count / CHARACTER_SPEED) % 10;
				if (frameX == 9) {
					frameX = 0;
					count = 0;
					if (isTorch)	eAction = IDLE_TORCH;
					else eAction = IDLE;
					eOrder = NONE_UP;
					isActionWork = false;
				}
				break;
			}
			break;
		case LEFT:
			switch (eOrder)
			{
			case PRE_LEFT:
				count++;
				frameX = (count / CHARACTER_SPEED) % 10;
				if (frameX == 9) {
					frameX = 0;
					count = 0;
					eOrder = LOOP_LEFT;
				}
				break;
			case LOOP_LEFT:
				count++;
				frameX = (count / CHARACTER_SPEED) % 10;
				if (frameX == 9) {
					frameX = 0;
					count = 0;
					if (isTorch)	eAction = IDLE_TORCH;
					else eAction = IDLE;
					eOrder = NONE_LEFT;
					isActionWork = false;
				}
				break;
			}
			break;
		case RIGHT:
			switch (eOrder)
			{
			case PRE_RIGHT:
				count++;
				frameX = (count / CHARACTER_SPEED) % 10;
				if (frameX == 9) {
					frameX = 0;
					count = 0;
					eOrder = LOOP_RIGHT;
				}
				break;
			case LOOP_RIGHT:
				count++;
				frameX = (count / CHARACTER_SPEED) % 10;
				if (frameX == 9) {
					frameX = 0;
					count = 0;
					if (isTorch)	eAction = IDLE_TORCH;
					else eAction = IDLE;
					eOrder = NONE_RIGHT;
					isActionWork = false;
				}
				break;
			}
			break;
		}
		break;
	case IDLE_TORCH:
		switch (_dir)
		{
		case DOWN:
			eOrder = NONE_DOWN;
			count++;
			frameX = count / CHARACTER_SPEED % 10;
			if (frameX == 9) {
				frameX = 0;
				count = 0;
			}
			break;
		case UP:
			eOrder = NONE_UP;
			count++;
			frameX = count / CHARACTER_SPEED % 10;
			if (frameX == 9) {
				frameX = 0;
				count = 0;
			}
			break;
		case LEFT:
			eOrder = NONE_LEFT;
			count++;
			frameX = count / CHARACTER_SPEED % 10;
			if (frameX == 9) {
				frameX = 0;
				count = 0;
			}
			break;
		case RIGHT:
			eOrder = NONE_RIGHT;
			count++;
			frameX = count / CHARACTER_SPEED % 10;
			if (frameX == 9) {
				frameX = 0;
				count = 0;
			}
			break;
		default:
			break;
		}
		break;
	case RUN:
		switch (_dir)
		{
		case DOWN:
			switch (eOrder)
			{
			case PRE_DOWN:
				count++;
				frameX = (count) % 10;
				if (frameX == 9) {
					frameX = 0;
					count = 0;
					eOrder = LOOP_DOWN;
				}
				break;
			case LOOP_DOWN:
				count++;
				frameX = (count / CHARACTER_SPEED) % 10;
				if (frameX == 9) {
					frameX = 0;
					count = 0;
				}
				break;
			case PST_DOWN:
				count++;
				frameX = (count) % 10;
				if (frameX == 9) {
					frameX = 0;
					count = 0;
					if (isTorch)	eAction = IDLE_TORCH;
					else eAction = IDLE;
					eOrder = NONE_DOWN;
				}
				break;
			}
			break;
		case UP:
			switch (eOrder)
			{
			case PRE_UP:
				count++;
				frameX = (count) % 10;
				if (frameX == 9) {
					frameX = 0;
					count = 0;
					eOrder = LOOP_UP;
				}
				break;
			case LOOP_UP:
				count++;
				frameX = (count / CHARACTER_SPEED) % 10;
				if (frameX == 9) {
					frameX = 0;
					count = 0;
				}
				break;
			case PST_UP:
				count++;
				frameX = (count) % 10;
				if (frameX == 9) {
					frameX = 0;
					count = 0;
					if (isTorch)	eAction = IDLE_TORCH;
					else eAction = IDLE;
					eOrder = NONE_UP;
				}
				break;
			}
			break;
		case LEFT:
			switch (eOrder)
			{
			case PRE_LEFT:
				count++;
				frameX = (count) % 10;
				if (frameX == 9) {
					frameX = 0;
					count = 0;
					eOrder = LOOP_LEFT;
				}
				break;
			case LOOP_LEFT:
				count++;
				frameX = (count / CHARACTER_SPEED) % 10;
				if (frameX == 9) {
					frameX = 0;
					count = 0;
				}
				break;
			case PST_LEFT:
				count++;
				frameX = (count) % 10;
				if (frameX == 9) {
					frameX = 0;
					count = 0;
					if (isTorch)	eAction = IDLE_TORCH;
					else eAction = IDLE;
					eOrder = NONE_LEFT;
				}
				break;
			}
			break;
		case RIGHT:
			switch (eOrder)
			{
			case PRE_RIGHT:
				count++;
				frameX = (count) % 10;
				if (frameX == 9) {
					frameX = 0;
					count = 0;
					eOrder = LOOP_RIGHT;
				}
				break;
			case LOOP_RIGHT:
				count++;
				frameX = (count / CHARACTER_SPEED) % 10;
				if (frameX == 9) {
					frameX = 0;
					count = 0;
				}
				break;
			case PST_RIGHT:
				count++;
				frameX = (count) % 10;
				if (frameX == 9) {
					frameX = 0;
					count = 0;
					if (isTorch)	eAction = IDLE_TORCH;
					else eAction = IDLE;
					eOrder = NONE_RIGHT;
				}
				break;
			}
			break;
		}
		break;
	case RUN_TORCH:
		switch (_dir)
		{
		case DOWN:
			switch (eOrder)
			{
			case PRE_DOWN:
				count++;
				frameX = (count) % 10;
				if (frameX == 9) {
					frameX = 0;
					count = 0;
					eOrder = LOOP_DOWN;
				}
				break;
			case LOOP_DOWN:
				count++;
				frameX = (count / CHARACTER_SPEED) % 10;
				if (frameX == 9) {
					frameX = 0;
					count = 0;
				}
				break;
			case PST_DOWN:
				count++;
				frameX = (count) % 10;
				if (frameX == 9) {
					frameX = 0;
					count = 0;
					eAction = IDLE;
					eOrder = NONE_DOWN;
				}
				break;
			}
			break;
		case UP:
			switch (eOrder)
			{
			case PRE_UP:
				count++;
				frameX = (count) % 10;
				if (frameX == 9) {
					frameX = 0;
					count = 0;
					eOrder = LOOP_UP;
				}
				break;
			case LOOP_UP:
				count++;
				frameX = (count / CHARACTER_SPEED) % 10;
				if (frameX == 9) {
					frameX = 0;
					count = 0;
				}
				break;
			case PST_UP:
				count++;
				frameX = (count) % 10;
				if (frameX == 9) {
					frameX = 0;
					count = 0;
					eAction = IDLE;
					eOrder = NONE_UP;
				}
				break;
			}
			break;
		case LEFT:
			switch (eOrder)
			{
			case PRE_LEFT:
				count++;
				frameX = (count) % 10;
				if (frameX == 9) {
					frameX = 0;
					count = 0;
					eOrder = LOOP_LEFT;
				}
				break;
			case LOOP_LEFT:
				count++;
				frameX = (count / CHARACTER_SPEED) % 10;
				if (frameX == 9) {
					frameX = 0;
					count = 0;
				}
				break;
			case PST_LEFT:
				count++;
				frameX = (count) % 10;
				if (frameX == 9) {
					frameX = 0;
					count = 0;
					eAction = IDLE;
					eOrder = NONE_LEFT;
				}
				break;
			}
			break;
		case RIGHT:
			switch (eOrder)
			{
			case PRE_RIGHT:
				count++;
				frameX = (count) % 10;
				if (frameX == 9) {
					frameX = 0;
					count = 0;
					eOrder = LOOP_RIGHT;
				}
				break;
			case LOOP_RIGHT:
				count++;
				frameX = (count / CHARACTER_SPEED) % 10;
				if (frameX == 9) {
					frameX = 0;
					count = 0;
				}
				break;
			case PST_RIGHT:
				count++;
				frameX = (count) % 10;
				if (frameX == 9) {
					frameX = 0;
					count = 0;
					eAction = IDLE;
					eOrder = NONE_RIGHT;
				}
				break;
			}
			break;
		}
		break;
	case ACTION_AXE:
		switch (_dir)
		{
		case DOWN:
			switch (eOrder)
			{
			case PRE_DOWN:
				count++;
				frameX = (count / CHARACTER_SPEED) % 10;
				if (frameX == 9) {
					frameX = 0;
					count = 0;
					eOrder = LOOP_DOWN;
				}
				break;
			case LOOP_DOWN:
				count++;
				frameX = (count / CHARACTER_SPEED) % 10;
				if (frameX == 9) {
					frameX = 0;
					count = 0;
					eOrder = PST_DOWN;
				}
				break;
			case PST_DOWN:
				count++;
				frameX = (count / CHARACTER_SPEED) % 10;
				if (frameX == 9) {
					frameX = 0;
					count = 0;
					if (isTorch)	eAction = IDLE_TORCH;
					else eAction = IDLE;
					eOrder = NONE_DOWN;
					isActionWork = false;
				}
				break;
			}
			break;
		case UP:
			switch (eOrder)
			{
			case PRE_UP:
				count++;
				frameX = (count / CHARACTER_SPEED) % 10;
				if (frameX == 9) {
					frameX = 0;
					count = 0;
					eOrder = LOOP_UP;
				}
				break;
			case LOOP_UP:
				count++;
				frameX = (count / CHARACTER_SPEED) % 10;
				if (frameX == 9) {
					frameX = 0;
					count = 0;
					eOrder = PST_UP;
				}
				break;
			case PST_UP:
				count++;
				frameX = (count / CHARACTER_SPEED) % 10;
				if (frameX == 9) {
					frameX = 0;
					count = 0;
					if (isTorch)	eAction = IDLE_TORCH;
					else eAction = IDLE;
					eOrder = NONE_UP;
					isActionWork = false;
				}
				break;
			}
			break;
		case LEFT:
			switch (eOrder)
			{
			case PRE_LEFT:
				count++;
				frameX = (count / CHARACTER_SPEED) % 10;
				if (frameX == 9) {
					frameX = 0;
					count = 0;
					eOrder = LOOP_LEFT;
				}
				break;
			case LOOP_LEFT:
				count++;
				frameX = (count / CHARACTER_SPEED) % 10;
				if (frameX == 9) {
					frameX = 0;
					count = 0;
					eOrder = PST_LEFT;
				}
				break;
			case PST_LEFT:
				count++;
				frameX = (count / CHARACTER_SPEED) % 10;
				if (frameX == 9) {
					frameX = 0;
					count = 0;
					if (isTorch)	eAction = IDLE_TORCH;
					else eAction = IDLE;
					eOrder = NONE_LEFT;
					isActionWork = false;
				}
				break;
			}
			break;
		case RIGHT:
			switch (eOrder)
			{
			case PRE_RIGHT:
				count++;
				frameX = (count / CHARACTER_SPEED) % 10;
				if (frameX == 9) {
					frameX = 0;
					count = 0;
					eOrder = LOOP_RIGHT;
				}
				break;
			case LOOP_RIGHT:
				count++;
				frameX = (count / CHARACTER_SPEED) % 10;
				if (frameX == 9) {
					frameX = 0;
					count = 0;
					eOrder = PST_RIGHT;
				}
				break;
			case PST_RIGHT:
				count++;
				frameX = (count / CHARACTER_SPEED) % 10;
				if (frameX == 9) {
					frameX = 0;
					count = 0;
					if (isTorch)	eAction = IDLE_TORCH;
					else eAction = IDLE;
					eOrder = NONE_RIGHT;
					isActionWork = false;
				}
				break;
			}
			break;
		}
		break;
	case ACTION_PICKAXE:
		switch (_dir)
		{
		case DOWN:
			switch (eOrder)
			{
			case PRE_DOWN:
				count++;
				frameX = (count / CHARACTER_SPEED) % 10;
				if (frameX == 9) {
					frameX = 0;
					count = 0;
					eOrder = LOOP_DOWN;
				}
				break;
			case LOOP_DOWN:
				count++;
				frameX = (count / CHARACTER_SPEED) % 10;
				if (frameX == 9) {
					frameX = 0;
					count = 0;
					eOrder = PST_DOWN;
				}
				break;
			case PST_DOWN:
				count++;
				frameX = (count / CHARACTER_SPEED) % 10;
				if (frameX == 9) {
					frameX = 0;
					count = 0;
					if (isTorch)	eAction = IDLE_TORCH;
					else eAction = IDLE;
					eOrder = NONE_DOWN;
					isActionWork = false;
				}
				break;
			}
			break;
		case UP:
			switch (eOrder)
			{
			case PRE_UP:
				count++;
				frameX = (count / CHARACTER_SPEED) % 10;
				if (frameX == 9) {
					frameX = 0;
					count = 0;
					eOrder = LOOP_UP;
				}
				break;
			case LOOP_UP:
				count++;
				frameX = (count / CHARACTER_SPEED) % 10;
				if (frameX == 9) {
					frameX = 0;
					count = 0;
					eOrder = PST_UP;
				}
				break;
			case PST_UP:
				count++;
				frameX = (count / CHARACTER_SPEED) % 10;
				if (frameX == 9) {
					frameX = 0;
					count = 0;
					if (isTorch)	eAction = IDLE_TORCH;
					else eAction = IDLE;
					eOrder = NONE_UP;
					isActionWork = false;
				}
				break;
			}
			break;
		case LEFT:
			switch (eOrder)
			{
			case PRE_LEFT:
				count++;
				frameX = (count / CHARACTER_SPEED) % 10;
				if (frameX == 9) {
					frameX = 0;
					count = 0;
					eOrder = LOOP_LEFT;
				}
				break;
			case LOOP_LEFT:
				count++;
				frameX = (count / CHARACTER_SPEED) % 10;
				if (frameX == 9) {
					frameX = 0;
					count = 0;
					eOrder = PST_LEFT;
				}
				break;
			case PST_LEFT:
				count++;
				frameX = (count / CHARACTER_SPEED) % 10;
				if (frameX == 9) {
					frameX = 0;
					count = 0;
					if (isTorch)	eAction = IDLE_TORCH;
					else eAction = IDLE;
					eOrder = NONE_LEFT;
					isActionWork = false;
				}
				break;
			}
			break;
		case RIGHT:
			switch (eOrder)
			{
			case PRE_RIGHT:
				count++;
				frameX = (count / CHARACTER_SPEED) % 10;
				if (frameX == 9) {
					frameX = 0;
					count = 0;
					eOrder = LOOP_RIGHT;
				}
				break;
			case LOOP_RIGHT:
				count++;
				frameX = (count / CHARACTER_SPEED) % 10;
				if (frameX == 9) {
					frameX = 0;
					count = 0;
					eOrder = PST_RIGHT;
				}
				break;
			case PST_RIGHT:
				count++;
				frameX = (count / CHARACTER_SPEED) % 10;
				if (frameX == 9) {
					frameX = 0;
					count = 0;
					if (isTorch)	eAction = IDLE_TORCH;
					else eAction = IDLE;
					eOrder = NONE_RIGHT;
					isActionWork = false;
				}
				break;
			}
			break;
		}
		break;
	}
}
