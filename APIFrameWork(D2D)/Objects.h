#pragma once
#include "gameNode.h"

class OBJECT_ENVIRONMENT : public gameNode { //ȯ����(ex. ����, ��������� ��)
private:
	//������� ��ȣ����
	EOBJKIND_ENVIRONMENT _kind;				// ����
	EOBJ_ENVIRONMENT_STATE _state;			// �������
	float _inactivateTime;					// ��Ȱ��ȭ�� �ð�
	float _regenerateTime;					// ����ð�
	int _hp;
	int _count;
	int _frame;
	POINT _pt;								// ������ǥ
	EOBJKIND_MATERIAL aDropItem[3];		// ��Ȱ��ȭ�� ����ϴ� �����۵�

public:
	OBJECT_ENVIRONMENT() {}
	~OBJECT_ENVIRONMENT() {}

	HRESULT init(EOBJKIND_ENVIRONMENT kind, POINT pt);
	void release();
	void update();
	void render();

	void changeState(EOBJ_ENVIRONMENT_STATE state) { _state = state; }
	void Regenerate();
	void ifZeroHP();
	inline void damage() { _hp -= 1; }
	inline EOBJKIND_ENVIRONMENT getKind() { return _kind; }
	inline EOBJKIND_MATERIAL* getDropItem() { return aDropItem; }

	inline int getHP() { return _hp; }
	inline POINT getPosition() { return _pt; }
	inline EOBJ_ENVIRONMENT_STATE getState() { return _state; }
};

class OBJECT_MATERIAL : public gameNode { //���������ѿ��(ex. �ν˵�, �������� ��)
private:
	EOBJKIND_MATERIAL _kind;
	EOBJ_ENVIRONMENT_STATE _state;			// �������
	POINT _pt;								// ������ǥ
	RECT _rc;								// ���� ��Ʈ

public:
	OBJECT_MATERIAL() {}
	~OBJECT_MATERIAL() {}

	HRESULT init(EOBJKIND_MATERIAL kind, POINT pt);
	void release();
	void update();
	void render();

	void changeState(EOBJ_ENVIRONMENT_STATE state) { _state = state; }
	inline EOBJ_ENVIRONMENT_STATE getState() { return _state; }
	inline EOBJKIND_MATERIAL getKind() { return _kind; }
	inline POINT getPosition() { return _pt; }
};

// ȭ�� , ��ں�, ���� ������Ʈ
enum EOBJECT_FIRE_STATE{EFS_PLACE, EFS_IDLE, EFS_DEAD};
class OBJECT_FIRE : public gameNode {
private:
	bool _kind;						// false�� ��ں�, true�� ȭ��
	float firePowerX, firePowerY;	// ���� ����
	POINT _pt;
	EOBJECT_FIRE_STATE _state;
	int frame, count;
	int lightDownTime;

public:
	OBJECT_FIRE() {}
	~OBJECT_FIRE() {}

	HRESULT init(bool kind, POINT pt);
	void release();
	void update();
	void render();

	void lightDown();
	POINT getPosition() { return _pt; }
	EOBJECT_FIRE_STATE getState() { return _state; }
};

enum EOBJECT_STORAGE_STATE {ESS_IDLE, ESS_OPEN, ESS_CLOSE};
class OBJECT_STORAGE : public gameNode {
private:
	OBJECT_IN_INVENTORY _Items[9];
	POINT _pt;
	bool _isOpen;
	int frame, count;

public:
	OBJECT_STORAGE() {}
	~OBJECT_STORAGE() {}

	HRESULT init(POINT pt);
	void release();
	void update();
	void render();

	void checkOpenRange();
	bool getisOpen() { return _isOpen; }

	void deleteByindex(int index) {
		_Items[index]._kind = EII_NONE;
		_Items[index]._num = NULL;
	}
	OBJECT_IN_INVENTORY* loadItem() { return _Items; }
	void reduceByindexandNum(int index, int num) {
		_Items[index]._num -= num;
		if (_Items[index]._num <= 0) {
			_Items[index]._kind = EII_NONE;
			_Items[index]._num = NULL;
		}
	}
	void saveByindex(int index, OBJECT_IN_INVENTORY obj) {
		_Items[index]._kind = obj._kind;
		_Items[index]._num = obj._num;
	}
};