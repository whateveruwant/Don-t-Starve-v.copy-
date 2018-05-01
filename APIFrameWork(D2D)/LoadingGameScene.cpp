#include "stdafx.h"
#include "LoadingGameScene.h"


LoadingGameScene::LoadingGameScene()
{
}


LoadingGameScene::~LoadingGameScene()
{
}

HRESULT LoadingGameScene::init(void)
{
	_loading = new loading;
	_loading->init();

	//IMAGEMANAGER->deleteAll();

	if (loading_game_first == false)
	{
		loading_game_first = true;
		this->totalLoading();
	}

	return S_OK;
}

void LoadingGameScene::release(void)
{
}

void LoadingGameScene::update(void)
{
	_loading->update();
	if (_loading->loadingDone()) {
		SCENEMANAGER->changeScene("gameScene");
	}
}

void LoadingGameScene::render(void)
{
	_loading->render();
}

void LoadingGameScene::totalLoading()
{
	//===================================
	// UI 
	//===================================
	// 장비창 이미지 init 
	_loading->loadFrameImage(L"health", L"image/ui_health.png", 2400, 50, 50, 1);
	_loading->loadFrameImage(L"hunger", L"image/ui_hunger.png", 2400, 50, 50, 1);
	_loading->loadFrameImage(L"mental", L"image/ui_mental.png", 2400, 50, 50, 1);
	_loading->loadFrameImage(L"number", L"image/ui_number.png", 150, 40, 10, 1);

	// 인벤토리 박스 이미지
	_loading->loadImage(L"invenMenu", L"image/ui_4.png", 761, 47);
	_loading->loadImage(L"invenBox", L"image/ui_inventorybox.png", 32, 32);
	_loading->loadImage(L"invenHandBox", L"image/ui_inventoryhandbox.png", 32, 32);
	_loading->loadImage(L"invenArmorBox", L"image/ui_inventoryarmorbox.png", 32, 32);
	_loading->loadImage(L"invenHelmetBox", L"image/ui_inventoryhelmetbox.png", 32, 32);

	_loading->loadImage(L"backpack_on", L"image/inventory/ui_bag.png", 91, 120);
	_loading->loadImage(L"chest_on", L"image/inventory/ui_box.png", 154, 170);

	_loading->loadFrameImage(L"cursortext_invnetory", L"image/inventory/ui_cursortext_inventory.png", 400, 20, 10, 1);
	_loading->loadFrameImage(L"inventory_number", L"image/inventory/ui_inventorynumber.png", 115, 18, 10, 1);


	// 크래프팅 창 이미지
	_loading->loadImage(L"crafting", L"image/ui_1.png", 43, 462);
	_loading->loadImage(L"craftingKind_1", L"image/ui_1_1.png", 29, 38);
	_loading->loadImage(L"craftingKind_2", L"image/ui_1_2.png", 29, 38);
	_loading->loadImage(L"craftingKind_3", L"image/ui_1_3.png", 29, 38);
	_loading->loadImage(L"craftingKind_4", L"image/ui_1_4.png", 29, 38);
	_loading->loadImage(L"craftingKind_5", L"image/ui_1_5.png", 29, 38);
	_loading->loadImage(L"craftingKind_6", L"image/ui_1_6.png", 29, 38);
	_loading->loadImage(L"craftingKind_7", L"image/ui_1_7.png", 29, 38);
	_loading->loadImage(L"craftingKind_8", L"image/ui_1_8.png", 29, 38);
	_loading->loadImage(L"craftingKind_9", L"image/ui_1_9.png", 29, 38);
	_loading->loadImage(L"craftingKind_10", L"image/ui_1_10.png", 29, 38);
	_loading->loadImage(L"craftingKind_1_on", L"image/ui_1_1_on.png", 29, 38);
	_loading->loadImage(L"craftingKind_2_on", L"image/ui_1_2_on.png", 29, 38);
	_loading->loadImage(L"craftingKind_3_on", L"image/ui_1_3_on.png", 29, 38);
	_loading->loadImage(L"craftingKind_4_on", L"image/ui_1_4_on.png", 29, 38);
	_loading->loadImage(L"craftingKind_5_on", L"image/ui_1_5_on.png", 29, 38);
	_loading->loadImage(L"craftingKind_6_on", L"image/ui_1_6_on.png", 29, 38);
	_loading->loadImage(L"craftingKind_7_on", L"image/ui_1_7_on.png", 29, 38);
	_loading->loadImage(L"craftingKind_8_on", L"image/ui_1_8_on.png", 29, 38);
	_loading->loadImage(L"craftingKind_9_on", L"image/ui_1_9_on.png", 29, 38);
	_loading->loadImage(L"craftingKind_10_on", L"image/ui_1_10_on.png", 29, 38);
	_loading->loadImage(L"craftingSecondButton_1", L"image/ui_crafting/ui_2_1.png", 93, 423);
	_loading->loadImage(L"craftingSecondButton_2", L"image/ui_crafting/ui_2_2.png", 93, 423);
	_loading->loadImage(L"craftingSecondButton_3", L"image/ui_crafting/ui_2_3.png", 93, 423);
	_loading->loadImage(L"craftingSecondButton_7", L"image/ui_crafting/ui_2_7.png", 93, 423);
	_loading->loadImage(L"craftingSecondButton_8", L"image/ui_crafting/ui_2_8.png", 93, 423);
	_loading->loadImage(L"craftingSecondButton_default", L"image/ui_crafting/ui_2_456910.png", 93, 423);
	_loading->loadImage(L"craftingPopUp_axe", L"image/ui_crafting/ui_3_axe.png", 251, 279);
	_loading->loadImage(L"craftingPopUp_backpack", L"image/ui_crafting/ui_3_backpack.png", 251, 279);
	_loading->loadImage(L"craftingPopUp_boards", L"image/ui_crafting/ui_3_boards.png", 251, 279);
	_loading->loadImage(L"craftingPopUp_bonfire", L"image/ui_crafting/ui_3_bonfire.png", 251, 279);
	_loading->loadImage(L"craftingPopUp_chest", L"image/ui_crafting/ui_3_chest.png", 251, 279);
	_loading->loadImage(L"craftingPopUp_cutstone", L"image/ui_crafting/ui_3_cutstone.png", 251, 279);
	_loading->loadImage(L"craftingPopUp_firepit", L"image/ui_crafting/ui_3_firepit.png", 251, 279);
	_loading->loadImage(L"craftingPopUp_pickaxe", L"image/ui_crafting/ui_3_pickaxe.png", 251, 279);
	_loading->loadImage(L"craftingPopUp_rope", L"image/ui_crafting/ui_3_rope.png", 251, 279);
	_loading->loadImage(L"craftingPopUp_torch", L"image/ui_crafting/ui_3_torch.png", 251, 279);
	_loading->loadImage(L"craftingMakeButton_no", L"image/ui_crafting/ui_3_makebutton_no.png", 110, 52);
	_loading->loadImage(L"craftingMakeButton_yes", L"image/ui_crafting/ui_3_makebutton_yes.png", 110, 52);
	_loading->loadFrameImage(L"cursortext_crafting", L"image/ui_crafting/ui_cursortext_crafting.png", 375, 25, 10, 1);

	_loading->loadImage(L"stopMenu", L"image/ui_stopMenu.png", 398, 450);
	_loading->loadImage(L"stopMenuButton_yes", L"image/ui_stopmenubutton_yes.png", 165, 53);
	_loading->loadImage(L"stopMenuButton_no", L"image/ui_stopmenubutton_no.png", 165, 53);
	
	// 시계 이미지 
	_loading->loadImage(L"clock", L"image/ui_clock.png", 71, 71);
	_loading->loadImage(L"clockNeedle", L"image/ui_clockneedle.png", 16, 53);
	_loading->loadFrameImage(L"clockRoundAfternoon", L"image/ui_clockroundafternoon.png", 1260, 94, 14, 1);
	_loading->loadFrameImage(L"clockRoundNight", L"image/ui_clockroundnight.png", 1260, 94, 14, 1);
	_loading->loadImage(L"clockdaytxt", L"image/ui_worlddatetext.png", 70, 47);
	_loading->loadFrameImage(L"clockNumber", L"image/ui_clocknumber.png", 150, 40, 10, 1);

	//죽었을 때 팝업 이미지
	_loading->loadImage(L"dead_popup", L"image/ui_dead.png", 673, 396);
	_loading->loadImage(L"dead_quit_button", L"image/ui_dead_quit.png", 195, 61);
	_loading->loadImage(L"dead_quit_button_on", L"image/ui_dead_quit_on.png", 195, 61);
	_loading->loadFrameImage(L"day_number", L"image/inventory/ui_inventorynumber.png", 224, 35, 10, 1);

	//피격 당했을때 필터
	_loading->loadImage(L"playerdamage", L"image/playerdamage.png", WINSIZEX_NUM, WINSIZEY_NUM);

	//게임 메인 씬 메뉴 버튼 이미지 추가
	_loading->loadImage(L"stopMenu", L"image/ui_stopMenu.png", 398, 450);
	_loading->loadImage(L"stopMenuButton_yes", L"image/ui_stopmenubutton_yes.png", 165, 53);
	_loading->loadImage(L"stopMenuButton_no", L"image/ui_stopmenubutton_no.png", 165, 53);
	_loading->loadImage(L"stopMenuButton", L"image/ui_stopmenubutton.png", 23, 22);

	//======================================
	// character 
	//======================================
	// action
	_loading->loadFrameImage(L"player_wakeup_none", L"image/player/action/player_action_wakeup20.png", 3000, 110, 20, 1);
	_loading->loadFrameImage(L"player_eat_none", L"image/player/action/player_action_eat45.png", 5151, 100, 45, 1);
	_loading->loadFrameImage(L"player_hungry_none", L"image/player/action/player_action_hungry45.png", 4276, 100, 45, 1);
	_loading->loadFrameImage(L"player_death_none", L"image/player/action/player_action_death45.png", 5273, 100, 45, 1);
	_loading->loadFrameImage(L"player_item_in_none", L"image/player/action/player_action_item_in.png", 724, 100, 10, 1);
	_loading->loadFrameImage(L"player_item_out_none", L"image/player/action/player_action_item_out.png", 775, 100, 10, 1);
	_loading->loadFrameImage(L"player_build_pre_down", L"image/player/action/player_action_build_pre_down.png", 904, 100, 14, 1);
	_loading->loadFrameImage(L"player_build_pre_left", L"image/player/action/player_action_build_pre_left.png", 977, 100, 14, 1);
	_loading->loadFrameImage(L"player_build_pre_right", L"image/player/action/player_action_build_pre_right.png", 977, 100, 14, 1);
	_loading->loadFrameImage(L"player_build_pre_up", L"image/player/action/player_action_build_pre_up.png", 856, 100, 14, 1);
	_loading->loadFrameImage(L"player_build_loop_down", L"image/player/action/player_action_build_loop_down.png", 825, 100, 10, 1);
	_loading->loadFrameImage(L"player_build_loop_right", L"image/player/action/player_action_build_loop_right.png", 825, 100, 10, 1);
	_loading->loadFrameImage(L"player_build_loop_left", L"image/player/action/player_action_build_loop_left.png", 1055, 100, 10, 1);
	_loading->loadFrameImage(L"player_build_loop_up", L"image/player/action/player_action_build_loop_up.png", 1199, 100, 10, 1);
	_loading->loadFrameImage(L"player_build_pst_down", L"image/player/action/player_action_build_pst_down.png", 653, 100, 8, 1);
	_loading->loadFrameImage(L"player_build_pst_left", L"image/player/action/player_action_build_pst_left.png", 618, 100, 8, 1);
	_loading->loadFrameImage(L"player_build_pst_right", L"image/player/action/player_action_build_pst_right.png", 618, 100, 8, 1);
	_loading->loadFrameImage(L"player_build_pst_up", L"image/player/action/player_action_build_pst_up.png", 655, 100, 8, 1);
	_loading->loadFrameImage(L"player_actionFX_down", L"image/player/action/player_actionFX_down.png", 1060, 100, 10, 1);
	_loading->loadFrameImage(L"player_actionFX_left", L"image/player/action/player_actionFX_left.png", 994, 100, 10, 1);
	_loading->loadFrameImage(L"player_actionFX_right", L"image/player/action/player_actionFX_right.png", 994, 100, 10, 1);
	_loading->loadFrameImage(L"player_actionFX_up", L"image/player/action/player_actionFX_up.png", 1060, 100, 10, 1);
	_loading->loadFrameImage(L"player_pickup_down", L"image/player/action/player_action_pickup_down.png", 662, 100, 10, 1);
	_loading->loadFrameImage(L"player_pickup_left", L"image/player/action/player_action_pickup_left.png", 963, 100, 10, 1);
	_loading->loadFrameImage(L"player_pickup_right", L"image/player/action/player_action_pickup_right.png", 963, 100, 10, 1);
	_loading->loadFrameImage(L"player_pickup_up", L"image/player/action/player_action_pickup_up.png", 718, 100, 10, 1);
	// idle
	_loading->loadFrameImage(L"player_idle_down", L"image/player/idle/player_idle_down.png", 620, 100, 10, 1);
	_loading->loadFrameImage(L"player_idle_up", L"image/player/idle/player_idle_up.png", 620, 100, 10, 1);
	_loading->loadFrameImage(L"player_idle_left", L"image/player/idle/player_idle_left.png", 620, 100, 10, 1);
	_loading->loadFrameImage(L"player_idle_right", L"image/player/idle/player_idle_right.png", 620, 100, 10, 1);
	_loading->loadFrameImage(L"player_idle_sanity_pre_down", L"image/player/idle/player_idle_sanity_pre_down.png", 642, 100, 10, 1);
	_loading->loadFrameImage(L"player_idle_sanity_pre_up", L"image/player/idle/player_idle_sanity_pre_up.png", 661, 100, 10, 1);
	_loading->loadFrameImage(L"player_idle_sanity_pre_right", L"image/player/idle/player_idle_sanity_pre_right.png", 675, 100, 10, 1);
	_loading->loadFrameImage(L"player_idle_sanity_pre_left", L"image/player/idle/player_idle_sanity_pre_left.png", 675, 100, 10, 1);
	_loading->loadFrameImage(L"player_idle_sanity_loop_down", L"image/player/idle/player_idle_sanity_loop_down.png", 763, 100, 10, 1);
	_loading->loadFrameImage(L"player_idle_sanity_loop_up", L"image/player/idle/player_idle_sanity_loop_up.png", 805, 100, 10, 1);
	_loading->loadFrameImage(L"player_idle_sanity_loop_right", L"image/player/idle/player_idle_sanity_loop_right.png", 778, 100, 10, 1);
	_loading->loadFrameImage(L"player_idle_sanity_loop_left", L"image/player/idle/player_idle_sanity_loop_left.png", 778, 100, 10, 1);
	_loading->loadFrameImage(L"player_idle_torch_down", L"image/player/idle/player_idle_torch_down.png", 665, 100, 10, 1);
	_loading->loadFrameImage(L"player_idle_torch_up", L"image/player/idle/player_idle_torch_up.png", 776, 100, 10, 1);
	_loading->loadFrameImage(L"player_idle_torch_right", L"image/player/idle/player_idle_torch_right.png", 681, 100, 10, 1);
	_loading->loadFrameImage(L"player_idle_torch_left", L"image/player/idle/player_idle_torch_left.png", 681, 100, 10, 1);
	// run
	_loading->loadFrameImage(L"player_run_pre_down", L"image/player/run/player_run_pre_down.png", 620, 100, 10, 1);
	_loading->loadFrameImage(L"player_run_pre_left", L"image/player/run/player_run_pre_left.png", 680, 100, 10, 1);
	_loading->loadFrameImage(L"player_run_pre_right", L"image/player/run/player_run_pre_right.png", 680, 100, 10, 1);
	_loading->loadFrameImage(L"player_run_pre_up", L"image/player/run/player_run_pre_up.png", 620, 100, 10, 1);
	_loading->loadFrameImage(L"player_run_loop_down", L"image/player/run/player_run_loop_down.png", 620, 110, 10, 1);
	_loading->loadFrameImage(L"player_run_loop_right", L"image/player/run/player_run_loop_right.png", 760, 106, 10, 1);
	_loading->loadFrameImage(L"player_run_loop_left", L"image/player/run/player_run_loop_left.png", 760, 102, 10, 1);
	_loading->loadFrameImage(L"player_run_loop_up", L"image/player/run/player_run_loop_up.png", 620, 120, 10, 1);
	_loading->loadFrameImage(L"player_run_pst_down", L"image/player/run/player_run_pst_down.png", 620, 100, 10, 1);
	_loading->loadFrameImage(L"player_run_pst_left", L"image/player/run/player_run_pst_left.png", 700, 100, 10, 1);
	_loading->loadFrameImage(L"player_run_pst_right", L"image/player/run/player_run_pst_right.png", 720, 100, 10, 1);
	_loading->loadFrameImage(L"player_run_pst_up", L"image/player/run/player_run_pst_up.png", 620, 100, 10, 1);
	_loading->loadFrameImage(L"player_run_torch_loop_down", L"image/player/run/player_run_torch_loop_down.png", 700, 110, 10, 1);
	_loading->loadFrameImage(L"player_run_torch_loop_right", L"image/player/run/player_run_torch_loop_right.png", 700, 110, 10, 1);
	_loading->loadFrameImage(L"player_run_torch_loop_left", L"image/player/run/player_run_torch_loop_left.png", 700, 110, 10, 1);
	_loading->loadFrameImage(L"player_run_torch_loop_up", L"image/player/run/player_run_torch_loop_up.png", 700, 110, 10, 1);
	// run
	_loading->loadFrameImage(L"player_run_pre_down", L"image/player/run/player_run_pre_down.png", 594, 100, 10, 1);
	_loading->loadFrameImage(L"player_run_pre_left", L"image/player/run/player_run_pre_left.png", 595, 100, 10, 1);
	_loading->loadFrameImage(L"player_run_pre_right", L"image/player/run/player_run_pre_right.png", 595, 100, 10, 1);
	_loading->loadFrameImage(L"player_run_pre_up", L"image/player/run/player_run_pre_up.png", 632, 100, 10, 1);
	_loading->loadFrameImage(L"player_run_loop_down", L"image/player/run/player_run_loop_down.png", 542, 100, 10, 1);
	_loading->loadFrameImage(L"player_run_loop_right", L"image/player/run/player_run_loop_right.png", 619, 100, 10, 1);
	_loading->loadFrameImage(L"player_run_loop_left", L"image/player/run/player_run_loop_left.png", 619, 100, 10, 1);
	_loading->loadFrameImage(L"player_run_loop_up", L"image/player/run/player_run_loop_up.png", 564, 100, 10, 1);
	_loading->loadFrameImage(L"player_run_pst_down", L"image/player/run/player_run_pst_down.png", 652, 100, 10, 1);
	_loading->loadFrameImage(L"player_run_pst_left", L"image/player/run/player_run_pst_left.png", 658, 100, 10, 1);
	_loading->loadFrameImage(L"player_run_pst_right", L"image/player/run/player_run_pst_right.png", 658, 100, 10, 1);
	_loading->loadFrameImage(L"player_run_pst_up", L"image/player/run/player_run_pst_up.png", 669, 100, 10, 1);
	_loading->loadFrameImage(L"player_run_torch_loop_down", L"image/player/run/player_run_torch_loop_down.png", 800, 150, 10, 1);
	_loading->loadFrameImage(L"player_run_torch_loop_right", L"image/player/run/player_run_torch_loop_right.png", 800, 150, 10, 1);
	_loading->loadFrameImage(L"player_run_torch_loop_left", L"image/player/run/player_run_torch_loop_left.png", 800, 150, 10, 1);
	_loading->loadFrameImage(L"player_run_torch_loop_up", L"image/player/run/player_run_torch_loop_up.png", 800, 150, 10, 1);

	// use item ( axe, pickaxe)
	_loading->loadFrameImage(L"player_axe_pre_down", L"image/player/use_item/player_axe_pre_down.png", 1226, 100, 10, 1);
	_loading->loadFrameImage(L"player_axe_pre_left", L"image/player/use_item/player_axe_pre_left.png", 1500, 120, 10, 1);
	_loading->loadFrameImage(L"player_axe_pre_right", L"image/player/use_item/player_axe_pre_right.png", 1328, 100, 10, 1);
	_loading->loadFrameImage(L"player_axe_pre_up", L"image/player/use_item/player_axe_pre_up.png", 1500, 120, 10, 1);
	_loading->loadFrameImage(L"player_axe_loop_down", L"image/player/use_item/player_axe_loop_down.png", 1281, 100, 10, 1);
	_loading->loadFrameImage(L"player_axe_loop_right", L"image/player/use_item/player_axe_loop_right.png", 1600, 120, 10, 1);
	_loading->loadFrameImage(L"player_axe_loop_left", L"image/player/use_item/player_axe_loop_left.png", 1600, 120, 10, 1);
	_loading->loadFrameImage(L"player_axe_loop_up", L"image/player/use_item/player_axe_loop_up.png", 1199, 100, 10, 1);
	_loading->loadFrameImage(L"player_axe_pst_down", L"image/player/use_item/player_axe_pst_down.png", 1283, 100, 10, 1);
	_loading->loadFrameImage(L"player_axe_pst_left", L"image/player/use_item/player_axe_pst_left.png", 2000, 120, 10, 1);
	_loading->loadFrameImage(L"player_axe_pst_right", L"image/player/use_item/player_axe_pst_right.png", 2000, 120, 10, 1);
	_loading->loadFrameImage(L"player_axe_pst_up", L"image/player/use_item/player_axe_pst_up.png", 1182, 100, 10, 1); 
	_loading->loadFrameImage(L"player_pickaxe_pre_down", L"image/player/use_item/player_pickaxe_pre_down.png", 1324, 100, 10, 1);
	_loading->loadFrameImage(L"player_pickaxe_pre_left", L"image/player/use_item/player_pickaxe_pre_left.png", 1800, 130, 10, 1);
	_loading->loadFrameImage(L"player_pickaxe_pre_right", L"image/player/use_item/player_pickaxe_pre_right.png", 1800, 130, 10, 1);
	_loading->loadFrameImage(L"player_pickaxe_pre_up", L"image/player/use_item/player_pickaxe_pre_up.png", 879, 100, 10, 1);
	_loading->loadFrameImage(L"player_pickaxe_loop_down", L"image/player/use_item/player_pickaxe_loop_down.png", 980, 100, 10, 1);
	_loading->loadFrameImage(L"player_pickaxe_loop_right", L"image/player/use_item/player_pickaxe_loop_right.png", 1800, 130, 10, 1);
	_loading->loadFrameImage(L"player_pickaxe_loop_left", L"image/player/use_item/player_pickaxe_loop_left.png", 1800, 130, 10, 1);
	_loading->loadFrameImage(L"player_pickaxe_loop_up", L"image/player/use_item/player_pickaxe_loop_up.png", 788, 100, 10, 1);
	_loading->loadFrameImage(L"player_pickaxe_pst_down", L"image/player/use_item/player_pickaxe_pst_down.png", 1498, 100, 10, 1);
	_loading->loadFrameImage(L"player_pickaxe_pst_left", L"image/player/use_item/player_pickaxe_pst_left.png", 1800, 130, 10, 1);
	_loading->loadFrameImage(L"player_pickaxe_pst_right", L"image/player/use_item/player_pickaxe_pst_right.png", 1800, 130, 10, 1);
	_loading->loadFrameImage(L"player_pickaxe_pst_up", L"image/player/use_item/player_pickaxe_pst_up.png", 884, 100, 10, 1);

	//타일 이미지 추가
	_loading->loadFrameImage(L"grassTile", L"image/grass_tile.png", TILESIZEX * 3, TILESIZEY * 9, 3, 9);   //408 1224
	_loading->loadFrameImage(L"forestTile", L"image/forest_tile.png", TILESIZEX * 13, TILESIZEY * 9, 13, 9);  //1768 1224
	_loading->loadFrameImage(L"stoneTile", L"image/stone_tile.png", TILESIZEX * 13, TILESIZEY * 9, 13, 9);
	_loading->loadImage(L"map_wave", L"image/wave.png", 1400, 256);

	//인벤토리 아이템 이미지
	_loading->loadFrameImage(L"ui_items", L"image/inventory/ui_atlas.png", 612, 34, 18, 1);

	// 오브젝트 이미지들
	// object_enviornment
	_loading->loadImage		(L"object_berrybush_idle",		L"image/o_environment/berriesbush/berriesbush_idle1.png", 130, 140);
	_loading->loadImage		(L"object_berrybush_die",		L"image/o_environment/berriesbush/berriesbush_die1.png", 130, 140);
	_loading->loadImage		(L"object_flower",				L"image/o_environment/flower1.png", 43, 40);
	_loading->loadImage		(L"object_planted_carrot",		L"image/o_environment/planted_carrot.png", 36, 40);
	_loading->loadFrameImage(L"object_hay_idle",			L"image/o_environment/hay/hay28.png", 1525, 140, 28, 1);
	_loading->loadImage		(L"object_hay_pick",			L"image/o_environment/hay/haypick.png", 50, 38);
	_loading->loadImage		(L"object_rock1",				L"image/o_environment/rock1.png", 204, 140);
	_loading->loadImage		(L"object_rock2",				L"image/o_environment/rock2.png", 190, 100);
	_loading->loadImage		(L"object_rock3",				L"image/o_environment/rock3.png", 150, 50);
	_loading->loadFrameImage(L"object_tree1_idle",			L"image/o_environment/tree1/tree1_idle21.png", 4024, 280, 21, 1);
	_loading->loadFrameImage(L"object_tree1_chop",			L"image/o_environment/tree1/tree1_chop4.png", 773, 280, 4, 1);
	_loading->loadFrameImage(L"object_tree1_dyingRight",	L"image/o_environment/tree1/tree1_dyingRight12.png", 3996, 350, 12, 1);
	_loading->loadFrameImage(L"object_tree1_dyingLeft",		L"image/o_environment/tree1/tree1_dyingLeft12.png", 3993, 350, 12, 1);
	_loading->loadImage		(L"object_tree1_die",			L"image/o_environment/tree1/tree1_die1.png", 70, 40);
	_loading->loadFrameImage(L"object_tree2_idle",			L"image/o_environment/tree2/tree2_idle21.png", 4024, 280, 21, 1);
	_loading->loadFrameImage(L"object_tree2_chop",			L"image/o_environment/tree2/tree2_chop4.png", 773, 280, 4, 1);
	_loading->loadFrameImage(L"object_tree2_dyingRight",	L"image/o_environment/tree2/tree2_dyingRight12.png", 3996, 350, 12, 1);
	_loading->loadFrameImage(L"object_tree2_dyingLeft",		L"image/o_environment/tree2/tree2_dyingLeft12.png", 3993, 350, 12, 1);
	_loading->loadImage		(L"object_tree2_die",			L"image/o_environment/tree2/tree2_die1.png", 70, 40);

	// object_meterial
	_loading->loadImage(L"object_flint", L"image/o_material/flint.png", 70, 40);
	_loading->loadImage(L"object_stone", L"image/o_material/stone.png", 64, 40);
	_loading->loadImage(L"object_twigs", L"image/o_material/twigs.png", 69, 40);
	_loading->loadImage(L"object_cutgrass", L"image/o_material/cutgrass.png", 46, 40);
	_loading->loadImage(L"object_log", L"image/o_material/log_drop.png", 70, 40);
	_loading->loadImage(L"object_board", L"image/o_material/board_drop.png", 77, 40);


	// object_usable
	_loading->loadFrameImage(L"object_camfire_place",		L"image/o_material/campfire/camfire_place.png", 700, 100, 7, 1);
	_loading->loadImage		(L"object_campfire",			L"image/o_material/campfire/campfire.png", 100, 40);
	_loading->loadImage		(L"object_campfire_dead",		L"image/o_material/campfire/campfire_dead.png", 100, 40);
	_loading->loadImage		(L"object_campfire_preview",	L"image/o_material/campfire/campfire_preview.png", 773, 280);
	_loading->loadFrameImage(L"object_campfire_fire_1",		L"image/o_material/campfire/campfire_fire_1.png", 250, 100, 5, 1);
	_loading->loadFrameImage(L"object_campfire_fire_2",		L"image/o_material/campfire/campfire_fire_2.png", 3993, 350, 5, 1);
	_loading->loadFrameImage(L"object_campfire_fire_3",		L"image/o_material/campfire/campfire_fire_3.png", 3993, 350, 5, 1);
	_loading->loadFrameImage(L"object_campfire_fire_4",		L"image/o_material/campfire/campfire_fire_4.png", 3993, 350, 5, 1);
	_loading->loadImage		(L"object_chest_idle",			L"image/o_material/chest/chest_idle.png", 70, 40);
	_loading->loadFrameImage(L"object_chest_open",			L"image/o_material/chest/chest_open.png", 4024, 280, 8, 1);
	_loading->loadFrameImage(L"object_chest_close",			L"image/o_material/chest/chest_close.png", 800, 80, 8, 1);
	_loading->loadImage		(L"object_firepit",				L"image/o_material/firepit/firepit.png", 100, 40);
	_loading->loadImage		(L"object_firepit_preview",		L"image/o_material/firepit/firepit_preview.png", 70, 40);
	_loading->loadFrameImage(L"object_firepit_place",		L"image/o_material/firepit/firepit_place.png", 700, 100, 7, 1);
}