#pragma once

enum EOBJCLASS { ENVIRONMENT , MATERIAL, EQUIPMENT, ERECTION };
enum EOBJKIND_ENVIRONMENT {
	NONE_ENVIRONMENT,
	FLOWER, 
	PLANTCARROT, 
	TREE1, 
	TREE2, 
	RASPBERRYSTACK, 
	ROCK, 
	HAYSTACK/*°ÇÃÊ´õ¹Ì*/};

enum EOBJKIND_MATERIAL {
	FLINT/*ºÎ½Ëµ¹*/,	// ¹Ù´Ú¿¡ ¶³±¼ ¼ö ÀÖ´Ù
	STONE,			// ¹Ù´Ú¿¡ ¶³±¼ ¼ö ÀÖ´Ù
	BRANCH,			// ³ª¹µ°¡Áö twigs
	HAY,
	LOG,			// Åë³ª¹«
	BOARD,			/*ÆÇÀÚ*/
};

enum EOBJKIND_USABLE{
	BONFIRE,	/*¸ð´ÚºÒ*/
	FIREPIT,	// È­´ö
	STORAGE,	/*ÀúÀå¼Ò*/
	//CARROT,		// 
	//RASPBERRY,	// 
	//AXE, 
	//PICKAX,		/*°î±ªÀÌ*/
	//TORCH,		/*È¶ºÒ*/
	//BAG,
};

enum EOBJECT_IN_INVENTORY_KIND { 
	EII_NONE,
	EII_FLINT/*ºÎ½Ëµ¹*/, 
	EII_BRANCH, 
	EII_HAY, 
	EII_LOG, 
	EII_STONE,
	EII_CARROT, 
	EII_RASPBERRY, 
	EII_BOARD, 
	EII_AXE,
	EII_PICKAX/*°î±ªÀÌ*/, 
	EII_TORCH/*È¶ºÒ*/,
	EII_BAG, 
	EII_CUTSTON,
	EII_LEAF,
	EII_ROPE, 
	EII_BONFIRE/*¸ð´ÚºÒ*/, 
	EII_FIREPIT/*È­´ö*/, 
	EII_STORAGE/*ÀúÀå¼Ò*/ };

struct OBJECT_IN_INVENTORY {
	EOBJECT_IN_INVENTORY_KIND _kind;
	int _num; // °¹¼ö ¶Ç´Â ³»±¸µµ
};

enum EOBJ_ENVIRONMENT_STATE {
	EES_IDLE,
	EES_DEAD,
	EES_LEFTDYING,
	EES_RIGHTDYING,
	EES_CHOPPED,
	EES_DELETE
};