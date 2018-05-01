#include "stdafx.h"
#include "Crafting.h"


Crafting::Crafting()
{
}


Crafting::~Crafting()
{
}

HRESULT Crafting::init(void)
{
   for (int i = 0; i < 10; i++)
   {
      _fButton[i].isCheck = false;
      _fButton[i].isClick = false;
      _fButton[i].x = 0;
      _fButton[i].y = 146 + i * 40;
   }

   // sbutton 이닛 함수 만들것
   for (int i = 0; i < 10; i++) {
      _sButton_kind[i].isClick = false;
      _sButton_kind[i].x = 58;
   }

   _sButton_kind[0].y = 191 + 0 * 49;
   _sButton_kind[1].y = 191 + 1 * 49;
   _sButton_kind[2].y = 191 + 0 * 49;
   _sButton_kind[3].y = 191 + 1 * 49;
   _sButton_kind[4].y = 191 + 2 * 49;
   _sButton_kind[5].y = 191 + 0 * 49;
   _sButton_kind[6].y = 191 + 0 * 49;
   _sButton_kind[7].y = 191 + 0 * 49;
   _sButton_kind[8].y = 191 + 1 * 49;
   _sButton_kind[9].y = 191 + 2 * 49;

   finalItemInit();

   for (int i = 0; i < 10; ++i) {
      _CanCreate[i] = false;
   }

   for (int i = 0; i < 10; ++i) {
	   _CanCreate[i] = false;
   }

   _isPlayerClickCrafting_first = false;
   _isPlayerClickCrafting_second = false;

   return S_OK;
}

void Crafting::release(void)
{
}

void Crafting::update(void)
{
   for (int i = 0; i < 10; i++) {
      firstButtonCheck(_fButton[i].isCheck, _fButton[i].x, _fButton[i].y);
      firstButtonClick(_fButton[i].isClick, _fButton[i].x, _fButton[i].y);

      if (_fButton[i].isClick) {
         for (int j = 0; j < 10; j++) {
            if (i == j)   continue;
            _fButton[j].isClick = false;
         }
      }
   }


   for (int i = 0; i < 10; i++) {
      if (i < 2) {
         secondButtonClick(_fButton[0].isClick, _sButton_kind[i].x, _sButton_kind[i].y, _sButton_kind[i].isClick);
         if (_sButton_kind[i].isClick) {
            for (int j = 0; j < 10; j++)
            {
               if (i == j)   continue;
               _sButton_kind[j].isClick = false;
            }
         }
      }
      else if (i < 5) {
         secondButtonClick(_fButton[1].isClick, _sButton_kind[i].x, _sButton_kind[i].y, _sButton_kind[i].isClick);
         if (_sButton_kind[i].isClick) {
            for (int j = 0; j < 10; j++)
            {
               if (i == j)   continue;
               _sButton_kind[j].isClick = false;
            }
         }
      }
      else if (i == 5) {
         secondButtonClick(_fButton[2].isClick, _sButton_kind[i].x, _sButton_kind[i].y, _sButton_kind[i].isClick);
         if (_sButton_kind[i].isClick) {
            for (int j = 0; j < 10; j++)
            {
               if (i == j)   continue;
               _sButton_kind[j].isClick = false;
            }
         }
      }
      else if (i == 6) {
         secondButtonClick(_fButton[6].isClick, _sButton_kind[i].x, _sButton_kind[i].y, _sButton_kind[i].isClick);
         if (_sButton_kind[i].isClick) {
            for (int j = 0; j < 10; j++)
            {
               if (i == j)   continue;
               _sButton_kind[j].isClick = false;
            }
         }
      }
      else {
         secondButtonClick(_fButton[7].isClick, _sButton_kind[i].x, _sButton_kind[i].y, _sButton_kind[i].isClick);
         if (_sButton_kind[i].isClick) {
            for (int j = 0; j < 10; j++)
            {
               if (i == j)   continue;
               _sButton_kind[j].isClick = false;
            }
         }
      }
   }

   checkCreate();

   thirdButtonClick(206, 265 + 0 * 49);
   thirdButtonClick(206, 265 + 1 * 49);
   thirdButtonClick(206, 265 + 0 * 49);
   thirdButtonClick(206, 265 + 1 * 49);
   thirdButtonClick(206, 265 + 2 * 49);
   thirdButtonClick(206, 265 + 0 * 49);
   thirdButtonClick(206, 265 + 0 * 49);
   thirdButtonClick(206, 265 + 0 * 49);
   thirdButtonClick(206, 265 + 1 * 49);
   thirdButtonClick(206, 265 + 2 * 49);
   
   checkisPlayerClickfirst();
   checkisPlayerClicksecond();
}

void Crafting::render(void)
{
   IMAGEMANAGER->render(L"crafting", Rt, 0, 129);

   firstButtonRender();
   secondButtonRender();
   thirdButtonRender();
}

void Crafting::firstButtonCheck(bool& isCheck, int x, int y)
{
   //마우스가 렉트 안에 가있는지?
   if (IsInRect(_ptMouse, { x, y, x + 29, y + 38 })) {
      isCheck = true;
   }
   else {
      isCheck = false;
   }

}

void Crafting::firstButtonClick(bool& isClick, int x, int y)
{
   if (IsInRect(_ptMouse, { x, y, x + 29, y + 38 })) {
      if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
         for (int i = 0; i < 10; i++) {
            _sButton_kind[i].isClick = false;
         }
         isClick = !isClick;
		 SOUNDMANAGER->play("craft_open", 0.3f);
      }
   }
}

void Crafting::firstButtonRender()
{

	if (!_fButton[0].isCheck) IMAGEMANAGER->render(L"craftingKind_1", Rt, 0, 146 + 0 * 40);
	else {
		IMAGEMANAGER->render(L"craftingKind_1_on", Rt, 0, 146 + 0 * 40);
		IMAGEMANAGER->frameRender(L"cursortext_crafting", Rt, 10, 140 + 0 * 40, 0, 0);
	}
	if (!_fButton[1].isCheck) IMAGEMANAGER->render(L"craftingKind_2", Rt, 0, 146 + 1 * 40);
	else {
		IMAGEMANAGER->render(L"craftingKind_2_on", Rt, 0, 146 + 1 * 40);
		IMAGEMANAGER->frameRender(L"cursortext_crafting", Rt, 10, 140 + 1 * 40, 1, 0);
	}
	if (!_fButton[2].isCheck) IMAGEMANAGER->render(L"craftingKind_3", Rt, 0, 146 + 2 * 40);
	else {
		IMAGEMANAGER->render(L"craftingKind_3_on", Rt, 0, 146 + 2 * 40);
		IMAGEMANAGER->frameRender(L"cursortext_crafting", Rt, 10, 140 + 2 * 40, 2, 0);
	}
	if (!_fButton[3].isCheck) IMAGEMANAGER->render(L"craftingKind_4", Rt, 0, 146 + 3 * 40);
	else {
		IMAGEMANAGER->render(L"craftingKind_4_on", Rt, 0, 146 + 3 * 40);
		IMAGEMANAGER->frameRender(L"cursortext_crafting", Rt, 10, 140 + 3 * 40, 3, 0);
	}
	if (!_fButton[4].isCheck) IMAGEMANAGER->render(L"craftingKind_5", Rt, 0, 146 + 4 * 40);
	else {
		IMAGEMANAGER->render(L"craftingKind_5_on", Rt, 0, 146 + 4 * 40);
		IMAGEMANAGER->frameRender(L"cursortext_crafting", Rt, 10, 140 + 4 * 40, 4, 0);
	}
	if (!_fButton[5].isCheck) IMAGEMANAGER->render(L"craftingKind_6", Rt, 0, 146 + 5 * 40);
	else {
		IMAGEMANAGER->render(L"craftingKind_6_on", Rt, 0, 146 + 5 * 40);
		IMAGEMANAGER->frameRender(L"cursortext_crafting", Rt, 10, 140 + 5 * 40, 5, 0);
	}
	if (!_fButton[6].isCheck) IMAGEMANAGER->render(L"craftingKind_7", Rt, 0, 146 + 6 * 40);
	else {
		IMAGEMANAGER->render(L"craftingKind_7_on", Rt, 0, 146 + 6 * 40);
		IMAGEMANAGER->frameRender(L"cursortext_crafting", Rt, 10, 140 + 6 * 40, 6, 0);
	}
	if (!_fButton[7].isCheck) IMAGEMANAGER->render(L"craftingKind_8", Rt, 0, 146 + 7 * 40);
	else {
		IMAGEMANAGER->render(L"craftingKind_8_on", Rt, 0, 146 + 7 * 40);
		IMAGEMANAGER->frameRender(L"cursortext_crafting", Rt, 10, 140 + 7 * 40, 7, 0);
	}
	if (!_fButton[8].isCheck) IMAGEMANAGER->render(L"craftingKind_9", Rt, 0, 146 + 8 * 40);
	else {
		IMAGEMANAGER->render(L"craftingKind_9_on", Rt, 0, 146 + 8 * 40);
		IMAGEMANAGER->frameRender(L"cursortext_crafting", Rt, 10, 140 + 8 * 40, 8, 0);
	}
	if (!_fButton[9].isCheck) IMAGEMANAGER->render(L"craftingKind_10", Rt, 0, 146 + 9 * 40);
	else {
		IMAGEMANAGER->render(L"craftingKind_10_on", Rt, 0, 146 + 9 * 40);
		IMAGEMANAGER->frameRender(L"cursortext_crafting", Rt, 10, 140 + 9 * 40, 9, 0);
	}

}

void Crafting::secondButtonRender()
{
   if (_fButton[0].isClick) IMAGEMANAGER->render(L"craftingSecondButton_1", Rt, 36, 147);
   else if (_fButton[1].isClick) IMAGEMANAGER->render(L"craftingSecondButton_2", Rt, 36, 147);
   else if (_fButton[2].isClick) IMAGEMANAGER->render(L"craftingSecondButton_3", Rt, 36, 147);
   else if (_fButton[3].isClick) IMAGEMANAGER->render(L"craftingSecondButton_default", Rt, 36, 147);
   else if (_fButton[4].isClick) IMAGEMANAGER->render(L"craftingSecondButton_default", Rt, 36, 147);
   else if (_fButton[5].isClick) IMAGEMANAGER->render(L"craftingSecondButton_default", Rt, 36, 147);
   else if (_fButton[6].isClick) IMAGEMANAGER->render(L"craftingSecondButton_7", Rt, 36, 147);
   else if (_fButton[7].isClick) IMAGEMANAGER->render(L"craftingSecondButton_8", Rt, 36, 147);
   else if (_fButton[8].isClick) IMAGEMANAGER->render(L"craftingSecondButton_default", Rt, 36, 147);
   else if (_fButton[9].isClick) IMAGEMANAGER->render(L"craftingSecondButton_default", Rt, 36, 147);
}

void Crafting::secondButtonClick(bool firstIsClick, int x, int y, bool& secondIsClick)
{
   //isClick(첫번째 왼쪽 크래프팅 버튼 10개 중 하나..)가 열린 상태에서
   if (firstIsClick) {
      if (IsInRect(_ptMouse, { x, y, x + 54, y + 35 })) {
         if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
            secondIsClick = !secondIsClick;
			SOUNDMANAGER->play("craft_close",0.3f);
         }
      }
   }

}

void Crafting::thirdButtonRender()
{
   //도끼, 곡괭이 등.. 을 클릭했을 경우 세번째 팝업이 뜹니다
   if (_sButton_kind[0].isClick) {
      IMAGEMANAGER->render(L"craftingPopUp_axe", Rt, 112, 74 + 0 * 49);
      //도끼 재료가 다 모이지 않았으면 no버튼 렌더, 모였으면 yes렌더
      if (!_CanCreate[0]) {
         IMAGEMANAGER->render(L"craftingMakeButton_no", Rt, 206, 265 + 0 * 49);
      }
      else {
         IMAGEMANAGER->render(L"craftingMakeButton_yes", Rt, 206, 265 + 0 * 49);
      }
   }
   if (_sButton_kind[1].isClick) {
      IMAGEMANAGER->render(L"craftingPopUp_pickaxe", Rt, 112, 74 + 1 * 49);
      //곡괭이 재료가 다 모이지 않았으면 no버튼 렌더, 모였으면 yes렌더
      if (!_CanCreate[1]) {
         IMAGEMANAGER->render(L"craftingMakeButton_no", Rt, 206, 265 + 1 * 49);
      }
      else {
         IMAGEMANAGER->render(L"craftingMakeButton_yes", Rt, 206, 265 + 1 * 49);
      }
   }


   if (_sButton_kind[2].isClick) {
      IMAGEMANAGER->render(L"craftingPopUp_bonfire", Rt, 112, 74 + 0 * 49);
      //모닥불 재료가 다 모이지 않았으면 no버튼 렌더, 모였으면 yes렌더
      if (!_CanCreate[2]) {
         IMAGEMANAGER->render(L"craftingMakeButton_no", Rt, 206, 265 + 0 * 49);
      }
      else {
         IMAGEMANAGER->render(L"craftingMakeButton_yes", Rt, 206, 265 + 0 * 49);
      }
   }

   if (_sButton_kind[3].isClick) {
      IMAGEMANAGER->render(L"craftingPopUp_firepit", Rt, 112, 74 + 1 * 49);
      //화덕 재료가 다 모이지 않았으면 no버튼 렌더, 모였으면 yes렌더
      if (!_CanCreate[3]) {
         IMAGEMANAGER->render(L"craftingMakeButton_no", Rt, 206, 265 + 1 * 49);
      }
      else {
         IMAGEMANAGER->render(L"craftingMakeButton_yes", Rt, 206, 265 + 1 * 49);
      }
   }
   if (_sButton_kind[4].isClick) {
      IMAGEMANAGER->render(L"craftingPopUp_torch", Rt, 112, 74 + 2 * 49);
      //횃불 재료가 다 모이지 않았으면 no버튼 렌더, 모였으면 yes렌더
      if (!_CanCreate[4]) {
         IMAGEMANAGER->render(L"craftingMakeButton_no", Rt, 206, 265 + 2 * 49);
      }
      else {
         IMAGEMANAGER->render(L"craftingMakeButton_yes", Rt, 206, 265 + 2 * 49);
      }
   }
   if (_sButton_kind[5].isClick) {
      IMAGEMANAGER->render(L"craftingPopUp_backpack", Rt, 112, 74 + 0 * 49);
      //가방 재료가 다 모이지 않았으면 no버튼 렌더, 모였으면 yes렌더
      if (!_CanCreate[5]) {
         IMAGEMANAGER->render(L"craftingMakeButton_no", Rt, 206, 265 + 0 * 49);
      }
      else {
         IMAGEMANAGER->render(L"craftingMakeButton_yes", Rt, 206, 265 + 0 * 49);
      }
   }

   if (_sButton_kind[6].isClick) {
      IMAGEMANAGER->render(L"craftingPopUp_chest", Rt, 112, 74 + 0 * 49);
      //상자 재료가 다 모이지 않았으면 no버튼 렌더, 모였으면 yes렌더
      if (!_CanCreate[6]) {
         IMAGEMANAGER->render(L"craftingMakeButton_no", Rt, 206, 265 + 0 * 49);
      }
      else {
         IMAGEMANAGER->render(L"craftingMakeButton_yes", Rt, 206, 265 + 0 * 49);
      }
   }

   if (_sButton_kind[7].isClick) {
      IMAGEMANAGER->render(L"craftingPopUp_rope", Rt, 112, 74 + 0 * 49);
      //밧줄 재료가 다 모이지 않았으면 no버튼 렌더, 모였으면 yes렌더
      if (!_CanCreate[7]) {
         IMAGEMANAGER->render(L"craftingMakeButton_no", Rt, 206, 265 + 0 * 49);
      }
      else {
         IMAGEMANAGER->render(L"craftingMakeButton_yes", Rt, 206, 265 + 0 * 49);
      }
   }
   if (_sButton_kind[8].isClick) {
      IMAGEMANAGER->render(L"craftingPopUp_boards", Rt, 112, 74 + 1 * 49);
      //판자 재료가 다 모이지 않았으면 no버튼 렌더, 모였으면 yes렌더
      if (!_CanCreate[8]) {
         IMAGEMANAGER->render(L"craftingMakeButton_no", Rt, 206, 265 + 1 * 49);
      }
      else {
         IMAGEMANAGER->render(L"craftingMakeButton_yes", Rt, 206, 265 + 1 * 49);
      }
   }
   if (_sButton_kind[9].isClick) {
      IMAGEMANAGER->render(L"craftingPopUp_cutstone", Rt, 112, 74 + 2 * 49);
      //석재 재료가 다 모이지 않았으면 no버튼 렌더, 모였으면 yes렌더
      if (!_CanCreate[9]) {
         IMAGEMANAGER->render(L"craftingMakeButton_no", Rt, 206, 265 + 2 * 49);
      }
      else {
         IMAGEMANAGER->render(L"craftingMakeButton_yes", Rt, 206, 265 + 2 * 49);
      }
   }

}

void Crafting::finalItemInit()
{
   for (int i = 0; i < 10; ++i) {
      switch (i)
      {
      case 0: //도끼
         _finalItems[i]._final = EOBJECT_IN_INVENTORY_KIND::EII_AXE;
         _finalItems[i]._source1 = EOBJECT_IN_INVENTORY_KIND::EII_FLINT;
         _finalItems[i]._sourcenum1 = 1;
         _finalItems[i]._source2 = EOBJECT_IN_INVENTORY_KIND::EII_BRANCH;
         _finalItems[i]._sourcenum2 = 1;
         break;
      case 1: //곡괭이
         _finalItems[i]._final = EOBJECT_IN_INVENTORY_KIND::EII_PICKAX;
         _finalItems[i]._source1 = EOBJECT_IN_INVENTORY_KIND::EII_FLINT;
         _finalItems[i]._sourcenum1 = 1;
         _finalItems[i]._source2 = EOBJECT_IN_INVENTORY_KIND::EII_BRANCH;
         _finalItems[i]._sourcenum2 = 2;
         break;
      case 2: //모닥불
         _finalItems[i]._final = EOBJECT_IN_INVENTORY_KIND::EII_BONFIRE;
         _finalItems[i]._source1 = EOBJECT_IN_INVENTORY_KIND::EII_LOG;
         _finalItems[i]._sourcenum1 = 2;
         _finalItems[i]._source2 = EOBJECT_IN_INVENTORY_KIND::EII_HAY;
         _finalItems[i]._sourcenum2 = 3;
         break;
      case 3: //화덕
         _finalItems[i]._final = EOBJECT_IN_INVENTORY_KIND::EII_FIREPIT;
         _finalItems[i]._source1 = EOBJECT_IN_INVENTORY_KIND::EII_LOG;
         _finalItems[i]._sourcenum1 = 2;
         _finalItems[i]._source2 = EOBJECT_IN_INVENTORY_KIND::EII_CUTSTON;
         _finalItems[i]._sourcenum2 = 4;
         break;
      case 4: //횃불
         _finalItems[i]._final = EOBJECT_IN_INVENTORY_KIND::EII_TORCH;
         _finalItems[i]._source1 = EOBJECT_IN_INVENTORY_KIND::EII_HAY;
         _finalItems[i]._sourcenum1 = 2;
         _finalItems[i]._source2 = EOBJECT_IN_INVENTORY_KIND::EII_BRANCH;
         _finalItems[i]._sourcenum2 = 2;
         break;
      case 5: //가방
         _finalItems[i]._final = EOBJECT_IN_INVENTORY_KIND::EII_BAG;
         _finalItems[i]._source1 = EOBJECT_IN_INVENTORY_KIND::EII_HAY;
         _finalItems[i]._sourcenum1 = 4;
         _finalItems[i]._source2 = EOBJECT_IN_INVENTORY_KIND::EII_BRANCH;
         _finalItems[i]._sourcenum2 = 4;
         break;
      case 6: //상자
         _finalItems[i]._final = EOBJECT_IN_INVENTORY_KIND::EII_STORAGE;
         _finalItems[i]._source1 = EOBJECT_IN_INVENTORY_KIND::EII_BOARD;
         _finalItems[i]._sourcenum1 = 3;
         _finalItems[i]._source2 = EOBJECT_IN_INVENTORY_KIND::EII_NONE;
         _finalItems[i]._sourcenum2 = NULL;
         break;
      case 7: //밧줄
         _finalItems[i]._final = EOBJECT_IN_INVENTORY_KIND::EII_ROPE;
         _finalItems[i]._source1 = EOBJECT_IN_INVENTORY_KIND::EII_HAY;
         _finalItems[i]._sourcenum1 = 3;
         _finalItems[i]._source2 = EOBJECT_IN_INVENTORY_KIND::EII_NONE;
         _finalItems[i]._sourcenum2 = NULL;
         break;
      case 8: //판자
         _finalItems[i]._final = EOBJECT_IN_INVENTORY_KIND::EII_BOARD;
         _finalItems[i]._source1 = EOBJECT_IN_INVENTORY_KIND::EII_LOG;
         _finalItems[i]._sourcenum1 = 4;
         _finalItems[i]._source2 = EOBJECT_IN_INVENTORY_KIND::EII_NONE;
         _finalItems[i]._sourcenum2 = NULL;
         break;
      case 9: //석재
         _finalItems[i]._final = EOBJECT_IN_INVENTORY_KIND::EII_CUTSTON;
         _finalItems[i]._source1 = EOBJECT_IN_INVENTORY_KIND::EII_STONE;
         _finalItems[i]._sourcenum1 = 3;
         _finalItems[i]._source2 = EOBJECT_IN_INVENTORY_KIND::EII_NONE;
         _finalItems[i]._sourcenum2 = NULL;
         break;
      }
   }
}

void Crafting::checkCreate()
{
   OBJECT_IN_INVENTORY* tmp;
   tmp = _invClon->loadObject();

   for (int k = 0; k < 10; ++k) {
      _CanCreate[k] = false;
      if (_invClon->getIsBag()) {
         for (int i = 0; i < 21; ++i) {
            if (_finalItems[k]._source1 == tmp[i]._kind && _finalItems[k]._sourcenum1 <= tmp[i]._num) { // 첫번째 재료 확인
               for (int j = 0; j < 21; ++j) {
                  if (((_finalItems[k]._source2 == tmp[j]._kind && _finalItems[k]._sourcenum2 <= tmp[j]._num) || _finalItems[k]._source2 == EOBJECT_IN_INVENTORY_KIND::EII_NONE) && i != j) {
                     _CanCreate[k] = true;
                     break;
                  }
               }
            }
         }
      }
      else {
         for (int i = 0; i < 15; ++i) {
            if (_finalItems[k]._source1 == tmp[i]._kind && _finalItems[k]._sourcenum1 <= tmp[i]._num) { // 첫번째 재료 확인
               for (int j = 0; j < 15; ++j) {
                  if (((_finalItems[k]._source2 == tmp[j]._kind && _finalItems[k]._sourcenum2 <= tmp[j]._num) || _finalItems[k]._source2 == EOBJECT_IN_INVENTORY_KIND::EII_NONE) && i != j) {
                     _CanCreate[k] = true;
                     break;
                  }
               }
            }
         }
      }
   }
}

void Crafting::thirdButtonClick(int x, int y)
{
   for (int i = 0; i < 10; ++i) {
      if (_sButton_kind[i].isClick) {
         if (_CanCreate[i]) {
            if (IsInRect(_ptMouse, { x, y, x + 110, y + 52 })) {
               if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
				   SOUNDMANAGER->play("craft_creatItem", 0.2f);
                  _invClon->saveObject(_finalItems[i]._final);
                  _invClon->deleteObjects(_finalItems[i]._source1, _finalItems[i]._sourcenum1);
                  if (_finalItems[i]._sourcenum2 != EOBJECT_IN_INVENTORY_KIND::EII_NONE)
                     _invClon->deleteObjects(_finalItems[i]._source2, _finalItems[i]._sourcenum2);
               }
            }
         }
      }
   }
}