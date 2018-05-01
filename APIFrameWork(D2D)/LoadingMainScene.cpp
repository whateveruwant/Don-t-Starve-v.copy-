#include "stdafx.h"
#include "LoadingMainScene.h"


LoadingMainScene::LoadingMainScene()
{
}


LoadingMainScene::~LoadingMainScene()
{
}

HRESULT LoadingMainScene::init(void)
{
	_loading = new loading;
	_loading->init();

	//IMAGEMANAGER->deleteAll();

	this->totalLoading();
	return S_OK;
}

void LoadingMainScene::release(void)
{
}

void LoadingMainScene::update(void)
{
	_loading->update();
	if (_loading->loadingDone()) {
		SCENEMANAGER->changeScene("menuScene");
	}
}

void LoadingMainScene::render(void)
{
	_loading->render();
}

void LoadingMainScene::totalLoading()
{
	//메뉴씬, 캐릭터 셀렉트씬 이미지 추가(이미지가 그대로 있는것들만 로딩에 추가)
	_loading->loadImage(L"mainMenu", L"image/ui_mainmenu.png", WINSIZEX_NUM, WINSIZEY_NUM);
	_loading->loadImage(L"mainMenuButton_start", L"image/ui_mainbutton_start.png", 195, 61);
	_loading->loadImage(L"mainMenuButton_start_on", L"image/ui_mainbutton_start_on.png", 195, 61);
	_loading->loadImage(L"mainMenuButton_quit", L"image/ui_mainbutton_quit.png", 195, 61);
	_loading->loadImage(L"mainMenuButton_quit_on", L"image/ui_mainbutton_quit_on.png", 195, 61);
	_loading->loadImage(L"characterSelect", L"image/ui_characterselect.png", WINSIZEX_NUM, WINSIZEY_NUM);
	_loading->loadImage(L"characterSelect_on", L"image/ui_characterselect_on.png", WINSIZEX_NUM, WINSIZEY_NUM);
	_loading->loadImage(L"selectButton_no", L"image/ui_selectbutton_no.png", 195, 61);
	_loading->loadImage(L"selectButton_no_on", L"image/ui_selectbutton_no_on.png", 195, 61);
	_loading->loadImage(L"selectButton_yes", L"image/ui_selectbutton_yes.png", 195, 61);
	_loading->loadImage(L"selectButton_yes_on", L"image/ui_selectbutton_yes_on.png", 195, 61);
	_loading->loadImage(L"mainMenuButton_maptool", L"image/ui_mainbutton_maptool.png", 195, 61);
	_loading->loadImage(L"mainMenuButton_maptool_on", L"image/ui_mainbutton_maptool_on.png", 195, 61);


	//맵툴 이미지 추가
	_loading->loadImage(L"forest_tilemap", L"image/maptool/forest_tile.png", 884, 612, 13, 9);  // 442, 306
	_loading->loadImage(L"stone_tilemap", L"image/maptool/stone_tile.png", 884, 612, 13, 9);  // 442, 306
	_loading->loadImage(L"grass_tilemap", L"image/maptool/grass_tile.png", 204, 612, 3, 9);   // 102, 306
	_loading->loadFrameImage(L"minimap_forest_tilemap", L"image/maptool/forest_tile.png", MINIMAPTILESIZE * 13, MINIMAPTILESIZE * 9, 13, 9);  // 442, 306
	_loading->loadFrameImage(L"minimap_stone_tilemap", L"image/maptool/stone_tile.png", MINIMAPTILESIZE * 13, MINIMAPTILESIZE * 9, 13, 9);  // 442, 306
	_loading->loadFrameImage(L"minimap_grass_tilemap", L"image/maptool/grass_tile.png", MINIMAPTILESIZE * 3, MINIMAPTILESIZE * 9, 3, 9);   // 102, 306
	_loading->loadFrameImage(L"mini_tileset", L"image/maptool/maptool_tileset.png", 102, 306, SAMPLETILEX, SAMPLETILEY);   //408 , 1224  = 136
	
	_loading->loadImage(L"backgound", L"image/maptool/maptool_background2.png", WINSIZEX_NUM, WINSIZEY_NUM);
	_loading->loadImage(L"backboard", L"image/maptool/maptool_back1.png", 565, 565);
	_loading->loadImage(L"tileset_bg", L"image/maptool/tileset_bg1.png", 200, 475);
	_loading->loadImage(L"erese_bt", L"image/maptool/maptool_erese.png", 100, 100);
	_loading->loadImage(L"reset_bt", L"image/maptool/maptool_reset.png", 100, 100);
	_loading->loadImage(L"save_bt", L"image/maptool/maptool_save.png", 100, 100);
	_loading->loadImage(L"load_bt", L"image/maptool/maptool_load.png", 100, 100);
	_loading->loadImage(L"minimap_bt", L"image/maptool/maptool_minimap.png", 100, 100);
	_loading->loadImage(L"exit_bt", L"image/maptool/maptool_exit.png", 100, 100);


	//맵툴용 오브젝트 이미지 
	_loading->loadImage(L"m_object_berrybush_idle", L"image/o_environment/berriesbush/berriesbush_idle1.png", 65, 70);
	_loading->loadImage(L"m_object_flower", L"image/o_environment/flower1.png", 21, 20);
	_loading->loadImage(L"m_object_planted_carrot", L"image/o_environment/planted_carrot.png", 18, 20);
	_loading->loadFrameImage(L"m_object_hay_idle", L"image/o_environment/hay/hay28.png", 700, 70, 28, 1);
	_loading->loadFrameImage(L"m_object_tree1_idle", L"image/o_environment/tree1/tree1_idle21.png", 1365, 70, 21, 1);
	_loading->loadFrameImage(L"m_object_tree2_idle", L"image/o_environment/tree2/tree2_idle21.png", 1365, 70, 21, 1);
	_loading->loadImage(L"m_object_rock1", L"image/o_environment/rock1.png", 65, 60);

	//=======================================================
	// SOUND
	//=======================================================
	//사운드 추가

	_loading->loadSound("mainBGM", "sounds/DST_Theme_FINAL_CNY.wav", false, true);
	_loading->loadSound("click", "sounds/click_move.mp3", false, false);
	_loading->loadSound("craft_creatItem", "sounds/getNewItem.mp3", false, false);
	_loading->loadSound("craft_close", "sounds/HUD_craft_close.mp3", false, false);
	_loading->loadSound("craft_open", "sounds/HUD_craft_open.mp3", false, false);
	_loading->loadSound("getItem", "sounds/collectResource.mp3", false, false);
	_loading->loadSound("MorningSound", "sounds/Dawn_150bpm_3.4time.mp3", false, false);
	_loading->loadSound("NightSound", "sounds/AMB_graveyard.mp3", false, true);
	_loading->loadSound("eatsound", "sounds/eat_2.mp3", false, false);
	_loading->loadSound("maptoolsound", "sounds/StartScreen_130bpm_3.4time_vinyl.mp3", false, true);
	_loading->loadSound("deadSound", "sounds/Dusk_150bpm_3.4time.mp3", false, false);

	_loading->loadSound("toolbreak", "sounds/Tool_Break.mp3", false, false);
	_loading->loadSound("chestopen", "sounds/Chest_open.mp3", false, false);
	_loading->loadSound("chestclose", "sounds/Chest_close.mp3", false, false);

	
	_loading->loadSound("hpUp", "sounds/HUD_health_up.mp3", false, false);
	_loading->loadSound("hpDown", "sounds/HUD_health_down.mp3", false, false);
	_loading->loadSound("hungerUp", "sounds/HUD_hunger_up.mp3", false, false);
	_loading->loadSound("hungerDown", "sounds/HUD_hunger_down.mp3", false, false);
	_loading->loadSound("mentalUp", "sounds/HUD_sanity_up.mp3", false, false);
	_loading->loadSound("mentalDown", "sounds/HUD_sanity_down.mp3", false, false);

	_loading->loadSound("walkSound", "sounds/footstep_grass_4.mp3", false, false);
	_loading->loadSound("hitStone", "sounds/hit_stone_3.mp3", false, false);
	_loading->loadSound("hitTree", "sounds/hit_wood_3.mp3", false, false);

}