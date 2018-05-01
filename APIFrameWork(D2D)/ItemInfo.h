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
	HAYSTACK/*���ʴ���*/};

enum EOBJKIND_MATERIAL {
	FLINT/*�ν˵�*/,	// �ٴڿ� ���� �� �ִ�
	STONE,			// �ٴڿ� ���� �� �ִ�
	BRANCH,			// �������� twigs
	HAY,
	LOG,			// �볪��
	BOARD,			/*����*/
};

enum EOBJKIND_USABLE{
	BONFIRE,	/*��ں�*/
	FIREPIT,	// ȭ��
	STORAGE,	/*�����*/
	//CARROT,		// 
	//RASPBERRY,	// 
	//AXE, 
	//PICKAX,		/*���*/
	//TORCH,		/*ȶ��*/
	//BAG,
};

enum EOBJECT_IN_INVENTORY_KIND { 
	EII_NONE,
	EII_FLINT/*�ν˵�*/, 
	EII_BRANCH, 
	EII_HAY, 
	EII_LOG, 
	EII_STONE,
	EII_CARROT, 
	EII_RASPBERRY, 
	EII_BOARD, 
	EII_AXE,
	EII_PICKAX/*���*/, 
	EII_TORCH/*ȶ��*/,
	EII_BAG, 
	EII_CUTSTON,
	EII_LEAF,
	EII_ROPE, 
	EII_BONFIRE/*��ں�*/, 
	EII_FIREPIT/*ȭ��*/, 
	EII_STORAGE/*�����*/ };

struct OBJECT_IN_INVENTORY {
	EOBJECT_IN_INVENTORY_KIND _kind;
	int _num; // ���� �Ǵ� ������
};

enum EOBJ_ENVIRONMENT_STATE {
	EES_IDLE,
	EES_DEAD,
	EES_LEFTDYING,
	EES_RIGHTDYING,
	EES_CHOPPED,
	EES_DELETE
};