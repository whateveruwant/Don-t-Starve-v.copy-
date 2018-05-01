#include "stdafx.h"
#include "Tiles.h"

Tiles::Tiles()
{
}

Tiles::~Tiles()
{
}

HRESULT Tiles::init(void)
{
	count = 0;

	for (int i = 0; i < 10; i++)
	{
		_wave[i].x = RND->getInt(100);
		_wave[i].y = i * 80 - 100;
		_wave[i].wave_count = RND->getInt(500);
	}

	return S_OK;
}

void Tiles::release(void)
{
}

void Tiles::update(void)
{
	calulateStandard();
	for (int i = 0; i < 10; i++)
	{
		waveMotion(i);
	}
}

void Tiles::render(void)
{

	for (int i = 0; i < 10; i++)
	{
		IMAGEMANAGER->render(L"map_wave", Rt, _wave[i].x - 150, _wave[i].y);
	}

	for (int i = _standard.x - 6; i < _standard.x + 6; ++i) {
		for (int j = _standard.y - 4; j < _standard.y + 4; ++j) {
			if (i < 0 || j <0) continue;
			if (i >= TILEX || j >= TILEY) continue;
			POINT _ttmp = CAMERAMANAGER->getAbsPosition({ i*TILESIZEX, j*TILESIZEY });
			IMAGEMANAGER->frameRender(L"grassTile", Rt, _ttmp.x, _ttmp.y, _tile[i][j].backTileFrameX, _tile[i][j].backTileFrameY);
			if (_tile[i][j].forestExist == true)
				IMAGEMANAGER->frameRender(L"forestTile", Rt, _ttmp.x, _ttmp.y, _tile[i][j].forestTileFrameX, _tile[i][j].forestTileFrameY);
			if (_tile[i][j].stoneExist == true)
				IMAGEMANAGER->frameRender(L"stoneTile", Rt, _ttmp.x, _ttmp.y, _tile[i][j].stoneTileFrameX, _tile[i][j].stoneTileFrameY);
		}
	}
}


//�߰�
void Tiles::objFrontRender(void)
{
	for (int i = _standard.y - 10; i < _standard.y + 10; ++i) {
		for (int j = _standard.x - 8; j < _standard.x + 8; ++j) {
			if (i < 0 || j < 0) continue;
			if (i >= TILEX || j >= TILEY) continue;
			vObjEnvi[j][i].render();
		}
	}
}


void Tiles::objMateRender(void)
{
	//for (int i = _standard.y - 8; i < _standard.y + 8; ++i) {
	//	for (int j = _standard.x - 8; j < _standard.x + 8; ++j) {
	//		if (i < 0 || j < 0) continue;
	//		if (i >= TILEX || j >= TILEY) continue;
	//		if (!vObjMate[i][j].empty())
	//			vObjMate[i][j].at(0).render();
	//	}
	//}
}



void Tiles::calulateStandard()
{
	long i = CAMERAMANAGER->getStandardPoint().x / TILESIZEX;
	long j = CAMERAMANAGER->getStandardPoint().y / TILESIZEY;

	_standard.x = i;
	_standard.y = j;
}

bool Tiles::generatorDone()
{
	count = 0;

	if (tile_init_select == true)
	{
		mapLoad();
		objInit();
		maptool_objEnviInit();
		return true;
	}
	objInit();
	if (backTileInit()) count++;

	if (forestTileInit()) count++;

	if (stoneTileInit())count++;

	if (objEnviInit())count++;

	//�߰�
	if (objMateInit())count++;

	if (count >= 5) return true;

	else return false;
}

bool Tiles::backTileInit()
{
	//�⺻ ����
	for (int i = 0; i < TILEX; i++)
	{
		for (int j = 0; j < TILEY; ++j)
		{
			//�»��
			if (i == 0 && j == 0)
			{
				_tile[i][j]._x = i * TILESIZEX;
				_tile[i][j]._y = j * TILESIZEY;
				_tile[i][j].backTileFrameX = 0;
				_tile[i][j].backTileFrameY = 8;
				_tile[i][j]._state = GRASSTILE;
			}

			//����
			else if (j == 0 && i == TILEX - 1)
			{
				_tile[i][j]._x = i * TILESIZEX;
				_tile[i][j]._y = j * TILESIZEY;
				_tile[i][j].backTileFrameX = 0;
				_tile[i][j].backTileFrameY = 7;
				_tile[i][j]._state = GRASSTILE;
			}

			//���ϴ�
			else if (j == TILEY - 1 && i == 0)
			{
				_tile[i][j]._x = i * TILESIZEX;
				_tile[i][j]._y = j * TILESIZEY;
				_tile[i][j].backTileFrameX = 0;
				_tile[i][j].backTileFrameY = 5;
				_tile[i][j]._state = GRASSTILE;
			}

			//���ϴ�
			else if (j == TILEY - 1 && i == TILEX - 1)
			{
				_tile[i][j]._x = i * TILESIZEX;
				_tile[i][j]._y = j * TILESIZEY;
				_tile[i][j].backTileFrameX = 0;
				_tile[i][j].backTileFrameY = 6;
				_tile[i][j]._state = GRASSTILE;
			}

			//���
			else if (j == 0)
			{
				_tile[i][j]._x = i * TILESIZEX;
				_tile[i][j]._y = j * TILESIZEY;
				_tile[i][j].backTileFrameX = RND->getInt(3);
				_tile[i][j].backTileFrameY = 4;
				_tile[i][j]._state = GRASSTILE;
			}

			//�ϴ�
			else if (j == TILEY - 1)
			{
				_tile[i][j]._x = i * TILESIZEX;
				_tile[i][j]._y = j * TILESIZEY;
				_tile[i][j].backTileFrameX = RND->getInt(3);
				_tile[i][j].backTileFrameY = 3;
				_tile[i][j]._state = GRASSTILE;
			}

			//����
			else if (i == 0)
			{
				_tile[i][j]._x = i * TILESIZEX;
				_tile[i][j]._y = j * TILESIZEY;
				_tile[i][j].backTileFrameX = RND->getInt(3);
				_tile[i][j].backTileFrameY = 1;
				_tile[i][j]._state = GRASSTILE;
			}

			//����
			else if (i == TILEX - 1)
			{
				_tile[i][j]._x = i * TILESIZEX;
				_tile[i][j]._y = j * TILESIZEY;
				_tile[i][j].backTileFrameX = RND->getInt(3);
				_tile[i][j].backTileFrameY = 2;
				_tile[i][j]._state = GRASSTILE;
			}

			//�߾Ӻκ�
			else
			{
				_tile[i][j]._x = i * TILESIZEX;
				_tile[i][j]._y = j * TILESIZEY;
				_tile[i][j].backTileFrameX = RND->getInt(3);
				_tile[i][j].backTileFrameY = 0;
				_tile[i][j]._state = GRASSTILE;

				int rnd_obj = RND->getInt(3);

				if (rnd_obj == 0) _tile[i][j]._objstate = FLOWER;
				else if (rnd_obj == 1) _tile[i][j]._objstate = TREE1;
				else if (rnd_obj == 2) _tile[i][j]._objstate = RASPBERRYSTACK;


			}
			_tile[i][j].forestTileFrameX = 14;
			_tile[i][j].forestTileFrameY = 14;

			_tile[i][j].stoneTileFrameX = 14;
			_tile[i][j].stoneTileFrameY = 14;

			_tile[i][j].forestExist = false;
			_tile[i][j].stoneExist = false;
		}
	}

	if (_tile == nullptr) return false;
	return true;
}

bool Tiles::forestTileInit()
{
	//��Ÿ�� ���� ����
	int RNDCNT = RND->getFromIntTo(600, 1000);

	for (int i = 0; i <RNDCNT; i++)
	{
		int x = RND->getInt(TILEX);
		int y = RND->getInt(TILEY);

		int _xEnd = RND->getFromIntTo(5, 20);
		int _yEnd = RND->getFromIntTo(5, 20);

		for (int p = x; p < x + _xEnd; p++)
		{
			for (int k = y; k < y + _yEnd; k++)
			{
				if (_tile[p][k]._state == TILESTATE::FORESTTILE && _tile[p][k].forestTileFrameY == 0) continue;


				//�»��(ok)
				if (p == x && k == y)
				{
					//����� �̹� ����ִٸ�
					if (_tile[p][k].forestTileFrameY == 4) continue;
					//������ �̹� ����ִٸ�
					if (_tile[p][k].forestTileFrameY == 1) continue;
					//�»���� �̹� ��ȴٸ�
					if (_tile[p][k].forestTileFrameY == 8) continue;


					//������ �������
					if (_tile[p][k].forestTileFrameY == 7)
					{
						//���ܸ� ������
						if (_tile[p][k].forestTileFrameX == 0)
						{
							_tile[p][k].forestTileFrameX = 1;
							_tile[p][k].forestTileFrameY = 8;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}

						//���ܰ� ���ϴ��� ������
						else if (_tile[p][k].forestTileFrameX == 4)
						{
							_tile[p][k].forestTileFrameX = 5;
							_tile[p][k].forestTileFrameY = 8;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}

						//���ܰ� ���ϴ��� ������
						else if (_tile[p][k].forestTileFrameX == 2)
						{
							_tile[p][k].forestTileFrameX = 6;
							_tile[p][k].forestTileFrameY = 8;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}

						//���ܰ� �ϴܱ��� ������
						else if (_tile[p][k].forestTileFrameX == 9) //8, �ٲ�
						{
							_tile[p][k].forestTileFrameX = 11;
							_tile[p][k].forestTileFrameY = 8;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}

						//��� �������� ������
						else if (_tile[p][k].forestTileFrameX == 7) //6, �ٲ�
						{
							_tile[p][k].forestTileFrameX = 8;
							_tile[p][k].forestTileFrameY = 8;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}

					}

					//���ϴ��� �������
					if (_tile[p][k].forestTileFrameY == 6)
					{
						//���ϴܸ� ������
						if (_tile[p][k].forestTileFrameX == 0)
						{
							_tile[p][k].forestTileFrameX = 4;
							_tile[p][k].forestTileFrameY = 8;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}
						//���ϴܰ� ���ϴ��� ������
						else if (_tile[p][k].forestTileFrameX == 1)
						{
							_tile[p][k].forestTileFrameX = 3;
							_tile[p][k].forestTileFrameY = 8;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}
						//���ϴܰ� ������ ������
						else if (_tile[p][k].forestTileFrameX == 2)
						{
							_tile[p][k].forestTileFrameX = 6;
							_tile[p][k].forestTileFrameY = 8;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}

						//��� �������� ������
						else if (_tile[p][k].forestTileFrameX == 6)
						{
							_tile[p][k].forestTileFrameX = 8;
							_tile[p][k].forestTileFrameY = 8;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}
					}

					//���ϴ��� �������
					if (_tile[p][k].forestTileFrameY == 5)
					{
						//���ϴܸ� ������

						//���ϴܰ� ���ϴ��� ������
						if (_tile[p][k].forestTileFrameX == 1)
						{
							_tile[p][k].forestTileFrameX = 3;
							_tile[p][k].forestTileFrameY = 8;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}
						//���ϴܰ� ������ ������
						else if (_tile[p][k].forestTileFrameX == 4)
						{
							_tile[p][k].forestTileFrameX = 5;
							_tile[p][k].forestTileFrameY = 8;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}
						//���ϴܰ� ������ ������
						else if (_tile[p][k].forestTileFrameX == 8)
						{
							_tile[p][k].forestTileFrameX = 10;
							_tile[p][k].forestTileFrameY = 8;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}

						//��� �������� ������
						else if (_tile[p][k].forestTileFrameX == 6)
						{
							_tile[p][k].forestTileFrameX = 8;
							_tile[p][k].forestTileFrameY = 8;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}
						else
						{
							_tile[p][k].forestTileFrameX = 2;
							_tile[p][k].forestTileFrameY = 8;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}

					}

					//������ ����ִ�
					if (_tile[p][k].forestTileFrameY == 2)
					{
						//�ϴܵ� ����ִ�
						if (_tile[p][k].forestTileFrameX == 1)
						{
							_tile[p][k].forestTileFrameX = 13;
							_tile[p][k].forestTileFrameY = 8;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}
						//���ϴܵ� ����ִ�
						else if (_tile[p][k].forestTileFrameX == 4)
						{
							_tile[p][k].forestTileFrameX = 10;
							_tile[p][k].forestTileFrameY = 8;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}
						//������ ��ȴ�
						else
						{
							_tile[p][k].forestTileFrameX = 8;
							_tile[p][k].forestTileFrameY = 8;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}
					}

					//�ϴ��� �������
					if (_tile[p][k].forestTileFrameY == 3)
					{
						//������ ��ȴ�
						if (_tile[p][k].forestTileFrameX == 1)
						{
							_tile[p][k].forestTileFrameX = 12;
							_tile[p][k].forestTileFrameY = 8;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}
						//���ܵ� ��ȴ�
						else if (_tile[p][k].forestTileFrameX == 5)
						{
							_tile[p][k].forestTileFrameX = 11;
							_tile[p][k].forestTileFrameY = 8;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}
						//�ϴܸ� �ִ�
						else
						{
							_tile[p][k].forestTileFrameX = 9;
							_tile[p][k].forestTileFrameY = 8;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}
					}

					else
					{
						_tile[p][k].forestTileFrameX = 0;
						_tile[p][k].forestTileFrameY = 8;
						_tile[p][k]._state = FORESTTILE;
						_tile[p][k].forestExist = true;
					}
				}

				//���� p == x && k == y + _yEnd - 1
				else if (p == x + _xEnd - 1 && k == y)
				{
					//����� �̹� ����ִٸ�
					if (_tile[p][k].forestTileFrameY == 4) continue;
					//������ �̹� ����ִٸ�
					if (_tile[p][k].forestTileFrameY == 2) continue;
					//������ �̹� ��ȴٸ�
					if (_tile[p][k].forestTileFrameY == 7) continue;


					//�»���� ������
					if (_tile[p][k].forestTileFrameY == 8)
					{
						//���ϴܵ� ������
						if (_tile[p][k].forestTileFrameX == 4)
						{
							_tile[p][k].forestTileFrameX = 3;
							_tile[p][k].forestTileFrameY = 7;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}

						//���ϴܵ� ������
						else if (_tile[p][k].forestTileFrameX == 2)
						{
							_tile[p][k].forestTileFrameX = 5;
							_tile[p][k].forestTileFrameY = 7;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}
						//��� ������
						else if (_tile[p][k].forestTileFrameX == 3)
						{
							_tile[p][k].forestTileFrameX = 7;
							_tile[p][k].forestTileFrameY = 7;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}
						//�»�� �� ������
						else if (_tile[p][k].forestTileFrameX == 0)
						{
							_tile[p][k].forestTileFrameX = 1;
							_tile[p][k].forestTileFrameY = 7;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}
					}

					//���ϴ��� ������
					else if (_tile[p][k].forestTileFrameY == 6)
					{
						//�»�ܵ� ������
						if (_tile[p][k].forestTileFrameX == 4)
						{
							_tile[p][k].forestTileFrameX = 3;
							_tile[p][k].forestTileFrameY = 7;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}
						//���ϴܵ� ������
						else if (_tile[p][k].forestTileFrameX == 1)
						{
							_tile[p][k].forestTileFrameX = 6;
							_tile[p][k].forestTileFrameY = 7;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}
						//��� ������
						else if (_tile[p][k].forestTileFrameX == 3)
						{
							_tile[p][k].forestTileFrameX = 7;
							_tile[p][k].forestTileFrameY = 7;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}

						//���ϴܸ� ������
						else if (_tile[p][k].forestTileFrameX == 0)
						{
							_tile[p][k].forestTileFrameX = 2;
							_tile[p][k].forestTileFrameY = 7;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}
					}

					//���ϴ��� ������
					else if (_tile[p][k].forestTileFrameY == 5)
					{
						//���ϴܵ� ������
						if (_tile[p][k].forestTileFrameX == 1)
						{
							_tile[p][k].forestTileFrameX = 6;
							_tile[p][k].forestTileFrameY = 7;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}
						//�»�ܵ� ������
						else 	if (_tile[p][k].forestTileFrameX == 2)
						{
							_tile[p][k].forestTileFrameX = 5;
							_tile[p][k].forestTileFrameY = 7;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}
						//��� ������
						else 	if (_tile[p][k].forestTileFrameX == 3)
						{
							_tile[p][k].forestTileFrameX = 7;
							_tile[p][k].forestTileFrameY = 7;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}
						//���ϴܸ� ������
						else 	if (_tile[p][k].forestTileFrameX == 0)
						{
							_tile[p][k].forestTileFrameX = 4;
							_tile[p][k].forestTileFrameY = 7;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}
					}

					//������ ������
					else if (_tile[p][k].forestTileFrameY == 1)
					{
						//�ϴܵ� ������
						if (_tile[p][k].forestTileFrameX == 1)
						{
							_tile[p][k].forestTileFrameX = 12;
							_tile[p][k].forestTileFrameY = 7;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}

						//���ϴܵ� ������
						else if (_tile[p][k].forestTileFrameX == 4)
						{
							_tile[p][k].forestTileFrameX = 10;
							_tile[p][k].forestTileFrameY = 7;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}
						//������ ������
						else if (_tile[p][k].forestTileFrameX == 0)
						{
							_tile[p][k].forestTileFrameX = 8;
							_tile[p][k].forestTileFrameY = 7;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}
					}

					//�ϴ��� ������
					else if (_tile[p][k].forestTileFrameY == 3)
					{
						//������ ������
						if (_tile[p][k].forestTileFrameX == 2)
						{
							_tile[p][k].forestTileFrameX = 12;
							_tile[p][k].forestTileFrameY = 7;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}
						//�»� ������
						else if (_tile[p][k].forestTileFrameX == 4)
						{
							_tile[p][k].forestTileFrameX = 11;
							_tile[p][k].forestTileFrameY = 7;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}
						//�ϴܸ� ������
						else if (_tile[p][k].forestTileFrameX == 0)
						{
							_tile[p][k].forestTileFrameX = 9;
							_tile[p][k].forestTileFrameY = 7;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}
					}
					else
					{
						_tile[p][k].forestTileFrameX = 0;
						_tile[p][k].forestTileFrameY = 7;
						_tile[p][k]._state = FORESTTILE;
						_tile[p][k].forestExist = true;
					}
				}

				//���ϴ� p == x + _xEnd - 1 && k == y
				else if (p == x && k == y + _yEnd - 1)
				{
					//�ϴ��� �̹� ����ִٸ�
					if (_tile[p][k].forestTileFrameY == 3) continue;
					//������ �̹� ����ִٸ�
					if (_tile[p][k].forestTileFrameY == 1) continue;
					//���ϴ��� �̹� ��ȴٸ�
					if (_tile[p][k].forestTileFrameY == 5) continue;



					//�»���� ������
					if (_tile[p][k].forestTileFrameY == 8)
					{
						//���ϴܵ� ������
						if (_tile[p][k].forestTileFrameX == 4)
						{
							_tile[p][k].forestTileFrameX = 3;
							_tile[p][k].forestTileFrameY = 5;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}

						//���ܵ� ������
						else if (_tile[p][k].forestTileFrameX == 1)
						{
							_tile[p][k].forestTileFrameX = 5;
							_tile[p][k].forestTileFrameY = 5;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}
						//��� ������
						else if (_tile[p][k].forestTileFrameX == 6)
						{
							_tile[p][k].forestTileFrameX = 7;
							_tile[p][k].forestTileFrameY = 5;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}
						//�»�� �� ������
						else if (_tile[p][k].forestTileFrameX == 0)
						{
							_tile[p][k].forestTileFrameX = 2;
							_tile[p][k].forestTileFrameY = 5;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}
					}

					//���ϴ��� ������
					else if (_tile[p][k].forestTileFrameY == 6)
					{
						//�»�ܵ� ������
						if (_tile[p][k].forestTileFrameX == 4)
						{
							_tile[p][k].forestTileFrameX = 3;
							_tile[p][k].forestTileFrameY = 5;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}
						//���ܵ� ������
						else if (_tile[p][k].forestTileFrameX == 2)
						{
							_tile[p][k].forestTileFrameX = 6;
							_tile[p][k].forestTileFrameY = 5;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}
						//��� ������
						else if (_tile[p][k].forestTileFrameX == 5)
						{
							_tile[p][k].forestTileFrameX = 7;
							_tile[p][k].forestTileFrameY = 5;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}

						//���ϴܸ� ������
						else if (_tile[p][k].forestTileFrameX == 0)
						{
							_tile[p][k].forestTileFrameX = 1;
							_tile[p][k].forestTileFrameY = 5;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}
					}

					//������ ������
					else if (_tile[p][k].forestTileFrameY == 7)
					{
						//���ϴܵ� ������
						if (_tile[p][k].forestTileFrameX == 2)
						{
							_tile[p][k].forestTileFrameX = 6;
							_tile[p][k].forestTileFrameY = 5;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}
						//�»�ܵ� ������
						else 	if (_tile[p][k].forestTileFrameX == 1)
						{
							_tile[p][k].forestTileFrameX = 5;
							_tile[p][k].forestTileFrameY = 5;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}
						//��� ������
						else 	if (_tile[p][k].forestTileFrameX == 3)
						{
							_tile[p][k].forestTileFrameX = 7;
							_tile[p][k].forestTileFrameY = 5;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}
						//���ܸ� ������
						else 	if (_tile[p][k].forestTileFrameX == 0)
						{
							_tile[p][k].forestTileFrameX = 4;
							_tile[p][k].forestTileFrameY = 5;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}
					}

					//������ ������
					else if (_tile[p][k].forestTileFrameY == 2)
					{
						//��ܵ� ������
						if (_tile[p][k].forestTileFrameX == 2)
						{
							_tile[p][k].forestTileFrameX = 12;
							_tile[p][k].forestTileFrameY = 5;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}

						//�»�ܵ� ������
						else if (_tile[p][k].forestTileFrameX == 5)
						{
							_tile[p][k].forestTileFrameX = 10;
							_tile[p][k].forestTileFrameY = 5;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}
						//������ ������
						else if (_tile[p][k].forestTileFrameX == 0)
						{
							_tile[p][k].forestTileFrameX = 8;
							_tile[p][k].forestTileFrameY = 5;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}
					}

					//����� ������
					else if (_tile[p][k].forestTileFrameY == 4)
					{
						//������ ������
						if (_tile[p][k].forestTileFrameX == 1)
						{
							_tile[p][k].forestTileFrameX = 12;
							_tile[p][k].forestTileFrameY = 5;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}
						//���ϴܵ� ������
						else if (_tile[p][k].forestTileFrameX == 4)
						{
							_tile[p][k].forestTileFrameX = 11;
							_tile[p][k].forestTileFrameY = 5;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}
						//��ܸ� ������
						else if (_tile[p][k].forestTileFrameX == 0)
						{
							_tile[p][k].forestTileFrameX = 9;
							_tile[p][k].forestTileFrameY = 5;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}

					}

					else {
						_tile[p][k].forestTileFrameX = 0;
						_tile[p][k].forestTileFrameY = 5;
						_tile[p][k]._state = FORESTTILE;
						_tile[p][k].forestExist = true;
					}
				}

				//���ϴ�(ok)
				else if (p == x + _xEnd - 1 && k == y + _yEnd - 1)
				{
					//�ϴ��� �̹� ����ִٸ�
					if (_tile[p][k].forestTileFrameY == 3) continue;
					//������ �̹� ����ִٸ�
					if (_tile[p][k].forestTileFrameY == 2) continue;
					//���ϴ��� �̹� ��ȴٸ� 
					if (_tile[p][k].forestTileFrameY == 6) continue;


					//�»���� ������
					if (_tile[p][k].forestTileFrameY == 8)
					{
						//���ϴܵ� ������
						if (_tile[p][k].forestTileFrameX == 2)
						{
							_tile[p][k].forestTileFrameX = 3;
							_tile[p][k].forestTileFrameY = 6;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}

						//���ܵ� ������
						else if (_tile[p][k].forestTileFrameX == 1)
						{
							_tile[p][k].forestTileFrameX = 5;
							_tile[p][k].forestTileFrameY = 6;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}
						//��� ������
						else if (_tile[p][k].forestTileFrameX == 6)
						{
							_tile[p][k].forestTileFrameX = 7;
							_tile[p][k].forestTileFrameY = 6;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}
						//�»�� �� ������
						else if (_tile[p][k].forestTileFrameX == 0)
						{
							_tile[p][k].forestTileFrameX = 4;
							_tile[p][k].forestTileFrameY = 6;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}
					}

					//���ϴ��� ������
					else if (_tile[p][k].forestTileFrameY == 5)
					{
						//���ܵ� ������
						if (_tile[p][k].forestTileFrameX == 4)
						{
							_tile[p][k].forestTileFrameX = 6;
							_tile[p][k].forestTileFrameY = 6;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}
						//�»�ܵ� ������
						else 	if (_tile[p][k].forestTileFrameX == 2)
						{
							_tile[p][k].forestTileFrameX = 3;
							_tile[p][k].forestTileFrameY = 6;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}
						//��� ������
						else 	if (_tile[p][k].forestTileFrameX == 5)
						{
							_tile[p][k].forestTileFrameX = 7;
							_tile[p][k].forestTileFrameY = 6;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}
						//���ϴܸ� ������
						else 	if (_tile[p][k].forestTileFrameX == 0)
						{
							_tile[p][k].forestTileFrameX = 1;
							_tile[p][k].forestTileFrameY = 6;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}
					}


					//������ ������
					else if (_tile[p][k].forestTileFrameY == 7)
					{
						//���ϴܵ� ������
						if (_tile[p][k].forestTileFrameX == 4)
						{
							_tile[p][k].forestTileFrameX = 6;
							_tile[p][k].forestTileFrameY = 6;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}
						//�»�ܵ� ������
						else 	if (_tile[p][k].forestTileFrameX == 1)
						{
							_tile[p][k].forestTileFrameX = 5;
							_tile[p][k].forestTileFrameY = 6;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}
						//��� ������
						else 	if (_tile[p][k].forestTileFrameX == 5)
						{
							_tile[p][k].forestTileFrameX = 7;
							_tile[p][k].forestTileFrameY = 6;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}
						//���ܸ� ������
						else 	if (_tile[p][k].forestTileFrameX == 0)
						{
							_tile[p][k].forestTileFrameX = 2;
							_tile[p][k].forestTileFrameY = 6;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}
					}

					//������ ������
					else if (_tile[p][k].forestTileFrameY == 1)
					{
						//��ܵ� ������
						if (_tile[p][k].forestTileFrameX == 2)
						{
							_tile[p][k].forestTileFrameX = 12;
							_tile[p][k].forestTileFrameY = 6;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}

						//���ϴܵ� ������
						else if (_tile[p][k].forestTileFrameX == 5)
						{
							_tile[p][k].forestTileFrameX = 10;
							_tile[p][k].forestTileFrameY = 6;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}
						//������ ������
						else if (_tile[p][k].forestTileFrameX == 0)
						{
							_tile[p][k].forestTileFrameX = 8;
							_tile[p][k].forestTileFrameY = 6;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}
					}

					//����� ������
					else if (_tile[p][k].forestTileFrameY == 4)
					{
						//������ ������
						if (_tile[p][k].forestTileFrameX == 2)
						{
							_tile[p][k].forestTileFrameX = 12;
							_tile[p][k].forestTileFrameY = 6;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}
						//���ϴܵ� ������
						else if (_tile[p][k].forestTileFrameX == 5)
						{
							_tile[p][k].forestTileFrameX = 11;
							_tile[p][k].forestTileFrameY = 6;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}
						//�ϴܸ� ������
						else if (_tile[p][k].forestTileFrameX == 0)
						{
							_tile[p][k].forestTileFrameX = 9;
							_tile[p][k].forestTileFrameY = 6;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}
					}

					else
					{
						_tile[p][k].forestTileFrameX = 0;
						_tile[p][k].forestTileFrameY = 6;
						_tile[p][k]._state = FORESTTILE;
						_tile[p][k].forestExist = true;
					}
				}

				//��� p == x
				else if (k == y)
				{
					//����� �̹� ����ִٸ�
					if (_tile[p][k].forestTileFrameY == 4) continue;


					//������ ������
					if (_tile[p][k].forestTileFrameY == 1)
					{
						//������ ������
						if (_tile[p][k].forestTileFrameX == 3)
						{
							_tile[p][k].forestTileFrameX = 9;
							_tile[p][k].forestTileFrameY = 4;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}
						//�ϴܵ� ������
						else if (_tile[p][k].forestTileFrameX == 1)
						{
							_tile[p][k].forestTileFrameX = 10;
							_tile[p][k].forestTileFrameY = 4;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}
						//���ϴܵ� ������
						else if (_tile[p][k].forestTileFrameX == 4)
						{
							_tile[p][k].forestTileFrameX = 8;
							_tile[p][k].forestTileFrameY = 4;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}

						//������ ������
						else if (_tile[p][k].forestTileFrameX == 0)
						{
							_tile[p][k].forestTileFrameX = 2;
							_tile[p][k].forestTileFrameY = 4;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}
					}
					//������ ������
					else if (_tile[p][k].forestTileFrameY == 2)
					{
						//������ ������
						if (_tile[p][k].forestTileFrameX == 3)
						{
							_tile[p][k].forestTileFrameX = 9;
							_tile[p][k].forestTileFrameY = 4;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}
						//�ϴܵ� ������
						else if (_tile[p][k].forestTileFrameX == 1)
						{
							_tile[p][k].forestTileFrameX = 11;
							_tile[p][k].forestTileFrameY = 4;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}
						//���ϴܵ� ������
						else if (_tile[p][k].forestTileFrameX == 4)
						{
							_tile[p][k].forestTileFrameX = 7;
							_tile[p][k].forestTileFrameY = 4;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}

						else if (_tile[p][k].forestTileFrameX == 0)
						{
							_tile[p][k].forestTileFrameX = 1;
							_tile[p][k].forestTileFrameY = 4;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}
					}

					//�ϴ��� ������
					else if (_tile[p][k].forestTileFrameY == 3)
					{
						//������ ������
						if (_tile[p][k].forestTileFrameX == 2)
						{
							_tile[p][k].forestTileFrameX = 10;
							_tile[p][k].forestTileFrameY = 4;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}
						//������ ������
						else if (_tile[p][k].forestTileFrameX == 1)
						{
							_tile[p][k].forestTileFrameX = 11;
							_tile[p][k].forestTileFrameY = 4;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}
						//�ϴܸ� ������
						else if (_tile[p][k].forestTileFrameX == 0)
						{
							_tile[p][k].forestTileFrameX = 3;
							_tile[p][k].forestTileFrameY = 4;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}
					}

					//���ϴ��� ������
					else if (_tile[p][k].forestTileFrameY == 5)
					{
						//������ ������
						if (_tile[p][k].forestTileFrameX == 8)
						{
							_tile[p][k].forestTileFrameX = 8;
							_tile[p][k].forestTileFrameY = 4;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}
						//���ϴܵ� ������
						else if (_tile[p][k].forestTileFrameX == 1)
						{
							_tile[p][k].forestTileFrameX = 6;
							_tile[p][k].forestTileFrameY = 4;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}
						//���ϴܸ� ������
						else if (_tile[p][k].forestTileFrameX == 0)
						{
							_tile[p][k].forestTileFrameX = 5;
							_tile[p][k].forestTileFrameY = 4;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}
					}

					//���ϴ��� ������
					else if (_tile[p][k].forestTileFrameY == 6)
					{
						//������ ������
						if (_tile[p][k].forestTileFrameX == 8)
						{
							_tile[p][k].forestTileFrameX = 8;
							_tile[p][k].forestTileFrameY = 4;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}
						//���ϴܵ� ������
						else if (_tile[p][k].forestTileFrameX == 1)
						{
							_tile[p][k].forestTileFrameX = 6;
							_tile[p][k].forestTileFrameY = 4;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}
						//���ϴܸ� ������
						else if (_tile[p][k].forestTileFrameX == 0)
						{
							_tile[p][k].forestTileFrameX = 4;
							_tile[p][k].forestTileFrameY = 4;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}
					}

					else
					{
						_tile[p][k].forestTileFrameX = 0;
						_tile[p][k].forestTileFrameY = 4;
						_tile[p][k]._state = FORESTTILE;
						_tile[p][k].forestExist = true;
					}
				}

				//�ϴ� p == x + _xEnd - 1
				else if (k == y + _yEnd - 1)
				{
					//�ϴ��� �̹� ����ִٸ�
					if (_tile[p][k].forestTileFrameY == 3) continue;

					//������ ������
					if (_tile[p][k].forestTileFrameY == 1)
					{
						//������ ������
						if (_tile[p][k].forestTileFrameX == 3)
						{
							_tile[p][k].forestTileFrameX = 9;
							_tile[p][k].forestTileFrameY = 3;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}
						//��ܵ� ������
						else if (_tile[p][k].forestTileFrameX == 2)
						{
							_tile[p][k].forestTileFrameX = 10;
							_tile[p][k].forestTileFrameY = 3;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}
						//���ܵ� ������
						else if (_tile[p][k].forestTileFrameX == 5)
						{
							_tile[p][k].forestTileFrameX = 8;
							_tile[p][k].forestTileFrameY = 3;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}

						//������ ������ (Ŀ��� ����)
						else if (_tile[p][k].forestTileFrameX == 0)
						{
							_tile[p][k].forestTileFrameX = 2;
							_tile[p][k].forestTileFrameY = 3;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}
					}

					//������ ������
					else if (_tile[p][k].forestTileFrameY == 2)
					{
						//������ ������
						if (_tile[p][k].forestTileFrameX == 3)
						{
							_tile[p][k].forestTileFrameX = 9;
							_tile[p][k].forestTileFrameY = 3;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}
						//��ܵ� ������
						else if (_tile[p][k].forestTileFrameX == 2)
						{
							_tile[p][k].forestTileFrameX = 11;
							_tile[p][k].forestTileFrameY = 3;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}
						//�»�ܵ� ������
						else if (_tile[p][k].forestTileFrameX == 5)
						{
							_tile[p][k].forestTileFrameX = 7;
							_tile[p][k].forestTileFrameY = 3;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}
						//������ ������
						else if (_tile[p][k].forestTileFrameX == 0)
						{
							_tile[p][k].forestTileFrameX = 1;
							_tile[p][k].forestTileFrameY = 3;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}
					}

					//����� ������
					else if (_tile[p][k].forestTileFrameY == 4)
					{
						//������ ������
						if (_tile[p][k].forestTileFrameX == 2)
						{
							_tile[p][k].forestTileFrameX = 10;
							_tile[p][k].forestTileFrameY = 3;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}
						//������ ������
						else if (_tile[p][k].forestTileFrameX == 1)
						{
							_tile[p][k].forestTileFrameX = 11;
							_tile[p][k].forestTileFrameY = 3;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}
						//��ܸ� ������
						else if (_tile[p][k].forestTileFrameX == 0)
						{
							_tile[p][k].forestTileFrameX = 3;
							_tile[p][k].forestTileFrameY = 3;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}
					}

					//�»���� ������
					else if (_tile[p][k].forestTileFrameY == 8)
					{
						//������ ������
						if (_tile[p][k].forestTileFrameX == 8)
						{
							_tile[p][k].forestTileFrameX = 7;
							_tile[p][k].forestTileFrameY = 3;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}
						//���ܵ� ������
						else if (_tile[p][k].forestTileFrameX == 1)
						{
							_tile[p][k].forestTileFrameX = 6;
							_tile[p][k].forestTileFrameY = 3;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}
						//���ϴܸ� ������
						else if (_tile[p][k].forestTileFrameX == 0)
						{
							_tile[p][k].forestTileFrameX = 4;
							_tile[p][k].forestTileFrameY = 3;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}
					}

					//������ ������
					else if (_tile[p][k].forestTileFrameY == 7)
					{
						//������ ������
						if (_tile[p][k].forestTileFrameX == 8)
						{
							_tile[p][k].forestTileFrameX = 8;
							_tile[p][k].forestTileFrameY = 3;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}
						//�»�ܵ� ������
						else if (_tile[p][k].forestTileFrameX == 1)
						{
							_tile[p][k].forestTileFrameX = 6;
							_tile[p][k].forestTileFrameY = 3;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}
						//���ܸ� ������
						else if (_tile[p][k].forestTileFrameX == 0)
						{
							_tile[p][k].forestTileFrameX = 5;
							_tile[p][k].forestTileFrameY = 3;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}
					}

					else
					{
						_tile[p][k].forestTileFrameX = 0;
						_tile[p][k].forestTileFrameY = 3;
						_tile[p][k]._state = FORESTTILE;
						_tile[p][k].forestExist = true;
					}
				}

				//���� k == y
				else if (p == x)
				{
					//������ �̹� ��ȴٸ�
					if (_tile[p][k].forestTileFrameY == 1) continue;

					//����� ������
					if (_tile[p][k].forestTileFrameY == 4)
					{
						//������ ������
						if (_tile[p][k].forestTileFrameX == 1) // ������
						{
							_tile[p][k].forestTileFrameX = 11;
							_tile[p][k].forestTileFrameY = 1;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}
						//���ϴܵ� ������
						else if (_tile[p][k].forestTileFrameX == 4)
						{
							_tile[p][k].forestTileFrameX = 8;
							_tile[p][k].forestTileFrameY = 1;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}

						//��ܸ� ������
						else if (_tile[p][k].forestTileFrameX == 0)
						{
							_tile[p][k].forestTileFrameX = 2;
							_tile[p][k].forestTileFrameY = 1;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}
					}

					//�ϴ��� ������
					else if (_tile[p][k].forestTileFrameY == 3)
					{
						//������ ������
						if (_tile[p][k].forestTileFrameX == 1)
						{
							_tile[p][k].forestTileFrameX = 10;
							_tile[p][k].forestTileFrameY = 1;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}

						//���ܵ� ������
						else if (_tile[p][k].forestTileFrameX == 5)
						{
							_tile[p][k].forestTileFrameX = 7;
							_tile[p][k].forestTileFrameY = 1;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}


						//�ϴܸ� ������
						else if (_tile[p][k].forestTileFrameX == 0)
						{
							_tile[p][k].forestTileFrameX = 1;
							_tile[p][k].forestTileFrameY = 1;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}
					}

					//���ϴ��� ������
					else if (_tile[p][k].forestTileFrameY == 6)
					{
						//��ܵ� ������
						if (_tile[p][k].forestTileFrameX == 9)
						{
							_tile[p][k].forestTileFrameX = 8;
							_tile[p][k].forestTileFrameY = 1;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}

						//���ܵ� ������
						else 	if (_tile[p][k].forestTileFrameX == 2)
						{
							_tile[p][k].forestTileFrameX = 6;
							_tile[p][k].forestTileFrameY = 1;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}



						//���ϴܸ� ������
						else if (_tile[p][k].forestTileFrameX == 0)
						{
							_tile[p][k].forestTileFrameX = 4;
							_tile[p][k].forestTileFrameY = 1;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}
					}

					//������ ������
					else if (_tile[p][k].forestTileFrameY == 7)
					{
						//�ϴܵ� ������
						if (_tile[p][k].forestTileFrameX == 9)
						{
							_tile[p][k].forestTileFrameX = 7;
							_tile[p][k].forestTileFrameY = 1;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}

						//���ϴܵ� ������
						else 	if (_tile[p][k].forestTileFrameX == 2)
						{
							_tile[p][k].forestTileFrameX = 6;
							_tile[p][k].forestTileFrameY = 1;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}

						//���ܸ� ������
						else if (_tile[p][k].forestTileFrameX == 0)
						{
							_tile[p][k].forestTileFrameX = 5;
							_tile[p][k].forestTileFrameY = 1;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}

					}

					//������ ������
					else if (_tile[p][k].forestTileFrameY == 2)
					{
						if (_tile[p][k].forestTileFrameX == 0)
						{
							_tile[p][k].forestTileFrameX = 3;
							_tile[p][k].forestTileFrameY = 1;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;

						}
						else if (_tile[p][k].forestTileFrameX == 2)
						{
							_tile[p][k].forestTileFrameX = 11;
							_tile[p][k].forestTileFrameY = 1;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}
						else if (_tile[p][k].forestTileFrameX == 1)
						{
							_tile[p][k].forestTileFrameX = 10;
							_tile[p][k].forestTileFrameY = 1;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}
					}

					else
					{
						_tile[p][k].forestTileFrameX = 0;
						_tile[p][k].forestTileFrameY = 1;
						_tile[p][k]._state = FORESTTILE;
						_tile[p][k].forestExist = true;
					}
				}

				//���� k == y + _yEnd - 1
				else if (p == x + _xEnd - 1)
				{
					//������ �̹� ��ȴٸ�
					if (_tile[p][k].forestTileFrameY == 2) continue;

					//����� ������
					if (_tile[p][k].forestTileFrameY == 4)
					{
						//������ ������
						if (_tile[p][k].forestTileFrameX == 2)
						{
							_tile[p][k].forestTileFrameX = 11;
							_tile[p][k].forestTileFrameY = 2;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}
						//���ϴܵ� ������
						else if (_tile[p][k].forestTileFrameX == 5)
						{
							_tile[p][k].forestTileFrameX = 8;
							_tile[p][k].forestTileFrameY = 2;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}

						//��ܸ� ������
						else if (_tile[p][k].forestTileFrameX == 0)
						{
							_tile[p][k].forestTileFrameX = 2;
							_tile[p][k].forestTileFrameY = 2;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}
					}

					//�ϴ��� ������
					else if (_tile[p][k].forestTileFrameY == 3)
					{
						//������ ������
						if (_tile[p][k].forestTileFrameX == 2)
						{
							_tile[p][k].forestTileFrameX = 10;
							_tile[p][k].forestTileFrameY = 2;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}

						//�»�ܵ� ������
						else if (_tile[p][k].forestTileFrameX == 5)
						{
							_tile[p][k].forestTileFrameX = 7;
							_tile[p][k].forestTileFrameY = 2;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}


						//�ϴܸ� ������
						else if (_tile[p][k].forestTileFrameX == 0)
						{
							_tile[p][k].forestTileFrameX = 1;
							_tile[p][k].forestTileFrameY = 2;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}
					}

					//���ϴ��� ������
					else if (_tile[p][k].forestTileFrameY == 5)
					{
						//��ܵ� ������
						if (_tile[p][k].forestTileFrameX == 9)
						{
							_tile[p][k].forestTileFrameX = 8;
							_tile[p][k].forestTileFrameY = 2;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}

						//�»�ܵ� ������
						else 	if (_tile[p][k].forestTileFrameX == 2)
						{
							_tile[p][k].forestTileFrameX = 6;
							_tile[p][k].forestTileFrameY = 2;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}

						//���ϴܸ� ������
						else if (_tile[p][k].forestTileFrameX == 0)
						{
							_tile[p][k].forestTileFrameX = 4;
							_tile[p][k].forestTileFrameY = 2;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}
					}

					//�»���� ������
					else if (_tile[p][k].forestTileFrameY == 8)
					{
						//�ϴܵ� ������5
						if (_tile[p][k].forestTileFrameX == 9)
						{
							_tile[p][k].forestTileFrameX = 7;
							_tile[p][k].forestTileFrameY = 2;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}

						//���ϴܵ� ������
						else 	if (_tile[p][k].forestTileFrameX == 2)
						{
							_tile[p][k].forestTileFrameX = 6;
							_tile[p][k].forestTileFrameY = 2;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}

						//�»�ܸ� ������
						else if (_tile[p][k].forestTileFrameX == 0)
						{
							_tile[p][k].forestTileFrameX = 5;
							_tile[p][k].forestTileFrameY = 2;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}

					}

					//������ ������
					else if (_tile[p][k].forestTileFrameY == 1)
					{
						if (_tile[p][k].forestTileFrameX == 0)
						{
							_tile[p][k].forestTileFrameX = 3;
							_tile[p][k].forestTileFrameY = 2;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;


						}
						else if (_tile[p][k].forestTileFrameX == 2)
						{
							_tile[p][k].forestTileFrameX = 11;
							_tile[p][k].forestTileFrameY = 2;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}
						else if (_tile[p][k].forestTileFrameX == 1)
						{
							_tile[p][k].forestTileFrameX = 10;
							_tile[p][k].forestTileFrameY = 2;
							_tile[p][k]._state = FORESTTILE;
							_tile[p][k].forestExist = true;
						}
					}
					else
					{
						_tile[p][k].forestTileFrameX = 0;
						_tile[p][k].forestTileFrameY = 2;
						_tile[p][k]._state = FORESTTILE;
						_tile[p][k].forestExist = true;
					}
				}

				//�߾Ӻκ�
				else
				{
					_tile[p][k].forestTileFrameX = RND->getInt(5);
					_tile[p][k].forestTileFrameY = 0;
					_tile[p][k]._state = FORESTTILE;
					_tile[p][k].forestExist = true;

					int rnd_obj = RND->getInt(3);

					if (rnd_obj == 0) _tile[p][k]._objstate = PLANTCARROT;
					else if (rnd_obj == 1) _tile[p][k]._objstate = TREE2;
					else if (rnd_obj == 2) _tile[p][k]._objstate = RASPBERRYSTACK;

				}

			}
		}
	}
	if (_tile == nullptr) return false;
	return true;
}

bool Tiles::stoneTileInit()
{

	//��Ÿ�� ���� ����
	int RNDCNT = RND->getFromIntTo(100, 250);

	for (int i = 0; i <RNDCNT; i++)
	{
		int x = RND->getInt(TILEX);
		int y = RND->getInt(TILEY);

		int _xEnd = RND->getFromIntTo(5, 20);
		int _yEnd = RND->getFromIntTo(5, 20);

		for (int p = x; p < x + _xEnd; p++)
		{
			for (int k = y; k < y + _yEnd; k++)
			{
				if (_tile[p][k]._state == TILESTATE::STONETILE && _tile[p][k].stoneTileFrameY == 0) continue;


				//�»��(ok)
				if (p == x && k == y)
				{
					//����� �̹� ����ִٸ�
					if (_tile[p][k].stoneTileFrameY == 4) continue;
					//������ �̹� ����ִٸ�
					if (_tile[p][k].stoneTileFrameY == 1) continue;
					//�»���� �̹� ��ȴٸ�
					if (_tile[p][k].stoneTileFrameY == 8) continue;


					//������ �������
					if (_tile[p][k].stoneTileFrameY == 7)
					{
						//���ܸ� ������
						if (_tile[p][k].stoneTileFrameX == 0)
						{
							_tile[p][k].stoneTileFrameX = 1;
							_tile[p][k].stoneTileFrameY = 8;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}

						//���ܰ� ���ϴ��� ������
						else if (_tile[p][k].stoneTileFrameX == 4)
						{
							_tile[p][k].stoneTileFrameX = 5;
							_tile[p][k].stoneTileFrameY = 8;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}

						//���ܰ� ���ϴ��� ������
						else if (_tile[p][k].stoneTileFrameX == 2)
						{
							_tile[p][k].stoneTileFrameX = 6;
							_tile[p][k].stoneTileFrameY = 8;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}

						//���ܰ� �ϴܱ��� ������
						else if (_tile[p][k].stoneTileFrameX == 9) //8, �ٲ�
						{
							_tile[p][k].stoneTileFrameX = 11;
							_tile[p][k].stoneTileFrameY = 8;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}

						//��� �������� ������
						else if (_tile[p][k].stoneTileFrameX == 7) //6, �ٲ�
						{
							_tile[p][k].stoneTileFrameX = 8;
							_tile[p][k].stoneTileFrameY = 8;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}

					}

					//���ϴ��� �������
					if (_tile[p][k].stoneTileFrameY == 6)
					{
						//���ϴܸ� ������
						if (_tile[p][k].stoneTileFrameX == 0)
						{
							_tile[p][k].stoneTileFrameX = 4;
							_tile[p][k].stoneTileFrameY = 8;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}
						//���ϴܰ� ���ϴ��� ������
						else if (_tile[p][k].stoneTileFrameX == 1)
						{
							_tile[p][k].stoneTileFrameX = 3;
							_tile[p][k].stoneTileFrameY = 8;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}
						//���ϴܰ� ������ ������
						else if (_tile[p][k].stoneTileFrameX == 2)
						{
							_tile[p][k].stoneTileFrameX = 6;
							_tile[p][k].stoneTileFrameY = 8;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}

						//��� �������� ������
						else if (_tile[p][k].stoneTileFrameX == 6)
						{
							_tile[p][k].stoneTileFrameX = 8;
							_tile[p][k].stoneTileFrameY = 8;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}
					}

					//���ϴ��� �������
					if (_tile[p][k].stoneTileFrameY == 5)
					{
						//���ϴܸ� ������

						//���ϴܰ� ���ϴ��� ������
						if (_tile[p][k].stoneTileFrameX == 1)
						{
							_tile[p][k].stoneTileFrameX = 3;
							_tile[p][k].stoneTileFrameY = 8;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}
						//���ϴܰ� ������ ������
						else if (_tile[p][k].stoneTileFrameX == 4)
						{
							_tile[p][k].stoneTileFrameX = 5;
							_tile[p][k].stoneTileFrameY = 8;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}
						//���ϴܰ� ������ ������
						else if (_tile[p][k].stoneTileFrameX == 8)
						{
							_tile[p][k].stoneTileFrameX = 10;
							_tile[p][k].stoneTileFrameY = 8;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}

						//��� �������� ������
						else if (_tile[p][k].stoneTileFrameX == 6)
						{
							_tile[p][k].stoneTileFrameX = 8;
							_tile[p][k].stoneTileFrameY = 8;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}
						else
						{
							_tile[p][k].stoneTileFrameX = 2;
							_tile[p][k].stoneTileFrameY = 8;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}

					}

					//������ ����ִ�
					if (_tile[p][k].stoneTileFrameY == 2)
					{
						//�ϴܵ� ����ִ�
						if (_tile[p][k].stoneTileFrameX == 1)
						{
							_tile[p][k].stoneTileFrameX = 13;
							_tile[p][k].stoneTileFrameY = 8;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}
						//���ϴܵ� ����ִ�
						else if (_tile[p][k].stoneTileFrameX == 4)
						{
							_tile[p][k].stoneTileFrameX = 10;
							_tile[p][k].stoneTileFrameY = 8;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}
						//������ ��ȴ�
						else
						{
							_tile[p][k].stoneTileFrameX = 8;
							_tile[p][k].stoneTileFrameY = 8;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}
					}

					//�ϴ��� �������
					if (_tile[p][k].stoneTileFrameY == 3)
					{
						//������ ��ȴ�
						if (_tile[p][k].stoneTileFrameX == 1)
						{
							_tile[p][k].stoneTileFrameX = 12;
							_tile[p][k].stoneTileFrameY = 8;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}
						//���ܵ� ��ȴ�
						else if (_tile[p][k].stoneTileFrameX == 5)
						{
							_tile[p][k].stoneTileFrameX = 11;
							_tile[p][k].stoneTileFrameY = 8;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}
						//�ϴܸ� �ִ�
						else
						{
							_tile[p][k].stoneTileFrameX = 9;
							_tile[p][k].stoneTileFrameY = 8;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}
					}

					else
					{
						_tile[p][k].stoneTileFrameX = 0;
						_tile[p][k].stoneTileFrameY = 8;
						_tile[p][k]._state = STONETILE;
						_tile[p][k].stoneExist = true;
					}
				}

				//���� p == x && k == y + _yEnd - 1
				else if (p == x + _xEnd - 1 && k == y)
				{
					//����� �̹� ����ִٸ�
					if (_tile[p][k].stoneTileFrameY == 4) continue;
					//������ �̹� ����ִٸ�
					if (_tile[p][k].stoneTileFrameY == 2) continue;
					//������ �̹� ��ȴٸ�
					if (_tile[p][k].stoneTileFrameY == 7) continue;


					//�»���� ������
					if (_tile[p][k].stoneTileFrameY == 8)
					{
						//���ϴܵ� ������
						if (_tile[p][k].stoneTileFrameX == 4)
						{
							_tile[p][k].stoneTileFrameX = 3;
							_tile[p][k].stoneTileFrameY = 7;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}

						//���ϴܵ� ������
						else if (_tile[p][k].stoneTileFrameX == 2)
						{
							_tile[p][k].stoneTileFrameX = 5;
							_tile[p][k].stoneTileFrameY = 7;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}
						//��� ������
						else if (_tile[p][k].stoneTileFrameX == 3)
						{
							_tile[p][k].stoneTileFrameX = 7;
							_tile[p][k].stoneTileFrameY = 7;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}
						//�»�� �� ������
						else if (_tile[p][k].stoneTileFrameX == 0)
						{
							_tile[p][k].stoneTileFrameX = 1;
							_tile[p][k].stoneTileFrameY = 7;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}
					}

					//���ϴ��� ������
					else if (_tile[p][k].stoneTileFrameY == 6)
					{
						//�»�ܵ� ������
						if (_tile[p][k].stoneTileFrameX == 4)
						{
							_tile[p][k].stoneTileFrameX = 3;
							_tile[p][k].stoneTileFrameY = 7;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}
						//���ϴܵ� ������
						else if (_tile[p][k].stoneTileFrameX == 1)
						{
							_tile[p][k].stoneTileFrameX = 6;
							_tile[p][k].stoneTileFrameY = 7;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}
						//��� ������
						else if (_tile[p][k].stoneTileFrameX == 3)
						{
							_tile[p][k].stoneTileFrameX = 7;
							_tile[p][k].stoneTileFrameY = 7;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}

						//���ϴܸ� ������
						else if (_tile[p][k].stoneTileFrameX == 0)
						{
							_tile[p][k].stoneTileFrameX = 2;
							_tile[p][k].stoneTileFrameY = 7;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}
					}

					//���ϴ��� ������
					else if (_tile[p][k].stoneTileFrameY == 5)
					{
						//���ϴܵ� ������
						if (_tile[p][k].stoneTileFrameX == 1)
						{
							_tile[p][k].stoneTileFrameX = 6;
							_tile[p][k].stoneTileFrameY = 7;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}
						//�»�ܵ� ������
						else 	if (_tile[p][k].stoneTileFrameX == 2)
						{
							_tile[p][k].stoneTileFrameX = 5;
							_tile[p][k].stoneTileFrameY = 7;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}
						//��� ������
						else 	if (_tile[p][k].stoneTileFrameX == 3)
						{
							_tile[p][k].stoneTileFrameX = 7;
							_tile[p][k].stoneTileFrameY = 7;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}
						//���ϴܸ� ������
						else 	if (_tile[p][k].stoneTileFrameX == 0)
						{
							_tile[p][k].stoneTileFrameX = 4;
							_tile[p][k].stoneTileFrameY = 7;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}
					}

					//������ ������
					else if (_tile[p][k].stoneTileFrameY == 1)
					{
						//�ϴܵ� ������
						if (_tile[p][k].stoneTileFrameX == 1)
						{
							_tile[p][k].stoneTileFrameX = 12;
							_tile[p][k].stoneTileFrameY = 7;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}

						//���ϴܵ� ������
						else if (_tile[p][k].stoneTileFrameX == 4)
						{
							_tile[p][k].stoneTileFrameX = 10;
							_tile[p][k].stoneTileFrameY = 7;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}
						//������ ������
						else if (_tile[p][k].stoneTileFrameX == 0)
						{
							_tile[p][k].stoneTileFrameX = 8;
							_tile[p][k].stoneTileFrameY = 7;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}
					}

					//�ϴ��� ������
					else if (_tile[p][k].stoneTileFrameY == 3)
					{
						//������ ������
						if (_tile[p][k].stoneTileFrameX == 2)
						{
							_tile[p][k].stoneTileFrameX = 12;
							_tile[p][k].stoneTileFrameY = 7;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}
						//�»� ������
						else if (_tile[p][k].stoneTileFrameX == 4)
						{
							_tile[p][k].stoneTileFrameX = 11;
							_tile[p][k].stoneTileFrameY = 7;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}
						//�ϴܸ� ������
						else if (_tile[p][k].stoneTileFrameX == 0)
						{
							_tile[p][k].stoneTileFrameX = 9;
							_tile[p][k].stoneTileFrameY = 7;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}
					}
					else
					{
						_tile[p][k].stoneTileFrameX = 0;
						_tile[p][k].stoneTileFrameY = 7;
						_tile[p][k]._state = STONETILE;
						_tile[p][k].stoneExist = true;
					}
				}

				//���ϴ� p == x + _xEnd - 1 && k == y
				else if (p == x && k == y + _yEnd - 1)
				{
					//�ϴ��� �̹� ����ִٸ�
					if (_tile[p][k].stoneTileFrameY == 3) continue;
					//������ �̹� ����ִٸ�
					if (_tile[p][k].stoneTileFrameY == 1) continue;
					//���ϴ��� �̹� ��ȴٸ�
					if (_tile[p][k].stoneTileFrameY == 5) continue;



					//�»���� ������
					if (_tile[p][k].stoneTileFrameY == 8)
					{
						//���ϴܵ� ������
						if (_tile[p][k].stoneTileFrameX == 4)
						{
							_tile[p][k].stoneTileFrameX = 3;
							_tile[p][k].stoneTileFrameY = 5;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}

						//���ܵ� ������
						else if (_tile[p][k].stoneTileFrameX == 1)
						{
							_tile[p][k].stoneTileFrameX = 5;
							_tile[p][k].stoneTileFrameY = 5;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}
						//��� ������
						else if (_tile[p][k].stoneTileFrameX == 6)
						{
							_tile[p][k].stoneTileFrameX = 7;
							_tile[p][k].stoneTileFrameY = 5;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}
						//�»�� �� ������
						else if (_tile[p][k].stoneTileFrameX == 0)
						{
							_tile[p][k].stoneTileFrameX = 2;
							_tile[p][k].stoneTileFrameY = 5;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}
					}

					//���ϴ��� ������
					else if (_tile[p][k].stoneTileFrameY == 6)
					{
						//�»�ܵ� ������
						if (_tile[p][k].stoneTileFrameX == 4)
						{
							_tile[p][k].stoneTileFrameX = 3;
							_tile[p][k].stoneTileFrameY = 5;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}
						//���ܵ� ������
						else if (_tile[p][k].stoneTileFrameX == 2)
						{
							_tile[p][k].stoneTileFrameX = 6;
							_tile[p][k].stoneTileFrameY = 5;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}
						//��� ������
						else if (_tile[p][k].stoneTileFrameX == 5)
						{
							_tile[p][k].stoneTileFrameX = 7;
							_tile[p][k].stoneTileFrameY = 5;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}

						//���ϴܸ� ������
						else if (_tile[p][k].stoneTileFrameX == 0)
						{
							_tile[p][k].stoneTileFrameX = 1;
							_tile[p][k].stoneTileFrameY = 5;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}
					}

					//������ ������
					else if (_tile[p][k].stoneTileFrameY == 7)
					{
						//���ϴܵ� ������
						if (_tile[p][k].stoneTileFrameX == 2)
						{
							_tile[p][k].stoneTileFrameX = 6;
							_tile[p][k].stoneTileFrameY = 5;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}
						//�»�ܵ� ������
						else 	if (_tile[p][k].stoneTileFrameX == 1)
						{
							_tile[p][k].stoneTileFrameX = 5;
							_tile[p][k].stoneTileFrameY = 5;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}
						//��� ������
						else 	if (_tile[p][k].stoneTileFrameX == 3)
						{
							_tile[p][k].stoneTileFrameX = 7;
							_tile[p][k].stoneTileFrameY = 5;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}
						//���ܸ� ������
						else 	if (_tile[p][k].stoneTileFrameX == 0)
						{
							_tile[p][k].stoneTileFrameX = 4;
							_tile[p][k].stoneTileFrameY = 5;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}
					}

					//������ ������
					else if (_tile[p][k].stoneTileFrameY == 2)
					{
						//��ܵ� ������
						if (_tile[p][k].stoneTileFrameX == 2)
						{
							_tile[p][k].stoneTileFrameX = 12;
							_tile[p][k].stoneTileFrameY = 5;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}

						//�»�ܵ� ������
						else if (_tile[p][k].stoneTileFrameX == 5)
						{
							_tile[p][k].stoneTileFrameX = 10;
							_tile[p][k].stoneTileFrameY = 5;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}
						//������ ������
						else if (_tile[p][k].stoneTileFrameX == 0)
						{
							_tile[p][k].stoneTileFrameX = 8;
							_tile[p][k].stoneTileFrameY = 5;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}
					}

					//����� ������
					else if (_tile[p][k].stoneTileFrameY == 4)
					{
						//������ ������
						if (_tile[p][k].stoneTileFrameX == 1)
						{
							_tile[p][k].stoneTileFrameX = 12;
							_tile[p][k].stoneTileFrameY = 5;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}
						//���ϴܵ� ������
						else if (_tile[p][k].stoneTileFrameX == 4)
						{
							_tile[p][k].stoneTileFrameX = 11;
							_tile[p][k].stoneTileFrameY = 5;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}
						//��ܸ� ������
						else if (_tile[p][k].stoneTileFrameX == 0)
						{
							_tile[p][k].stoneTileFrameX = 9;
							_tile[p][k].stoneTileFrameY = 5;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}

					}

					else {
						_tile[p][k].stoneTileFrameX = 0;
						_tile[p][k].stoneTileFrameY = 5;
						_tile[p][k]._state = STONETILE;
						_tile[p][k].stoneExist = true;
					}
				}

				//���ϴ�(ok)
				else if (p == x + _xEnd - 1 && k == y + _yEnd - 1)
				{
					//�ϴ��� �̹� ����ִٸ�
					if (_tile[p][k].stoneTileFrameY == 3) continue;
					//������ �̹� ����ִٸ�
					if (_tile[p][k].stoneTileFrameY == 2) continue;
					//���ϴ��� �̹� ��ȴٸ� 
					if (_tile[p][k].stoneTileFrameY == 6) continue;


					//�»���� ������
					if (_tile[p][k].stoneTileFrameY == 8)
					{
						//���ϴܵ� ������
						if (_tile[p][k].stoneTileFrameX == 2)
						{
							_tile[p][k].stoneTileFrameX = 3;
							_tile[p][k].stoneTileFrameY = 6;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}

						//���ܵ� ������
						else if (_tile[p][k].stoneTileFrameX == 1)
						{
							_tile[p][k].stoneTileFrameX = 5;
							_tile[p][k].stoneTileFrameY = 6;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}
						//��� ������
						else if (_tile[p][k].stoneTileFrameX == 6)
						{
							_tile[p][k].stoneTileFrameX = 7;
							_tile[p][k].stoneTileFrameY = 6;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}
						//�»�� �� ������
						else if (_tile[p][k].stoneTileFrameX == 0)
						{
							_tile[p][k].stoneTileFrameX = 4;
							_tile[p][k].stoneTileFrameY = 6;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}
					}

					//���ϴ��� ������
					else if (_tile[p][k].stoneTileFrameY == 5)
					{
						//���ܵ� ������
						if (_tile[p][k].stoneTileFrameX == 4)
						{
							_tile[p][k].stoneTileFrameX = 6;
							_tile[p][k].stoneTileFrameY = 6;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}
						//�»�ܵ� ������
						else 	if (_tile[p][k].stoneTileFrameX == 2)
						{
							_tile[p][k].stoneTileFrameX = 3;
							_tile[p][k].stoneTileFrameY = 6;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}
						//��� ������
						else 	if (_tile[p][k].stoneTileFrameX == 5)
						{
							_tile[p][k].stoneTileFrameX = 7;
							_tile[p][k].stoneTileFrameY = 6;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}
						//���ϴܸ� ������
						else 	if (_tile[p][k].stoneTileFrameX == 0)
						{
							_tile[p][k].stoneTileFrameX = 1;
							_tile[p][k].stoneTileFrameY = 6;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}
					}


					//������ ������
					else if (_tile[p][k].stoneTileFrameY == 7)
					{
						//���ϴܵ� ������
						if (_tile[p][k].stoneTileFrameX == 4)
						{
							_tile[p][k].stoneTileFrameX = 6;
							_tile[p][k].stoneTileFrameY = 6;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}
						//�»�ܵ� ������
						else 	if (_tile[p][k].stoneTileFrameX == 1)
						{
							_tile[p][k].stoneTileFrameX = 5;
							_tile[p][k].stoneTileFrameY = 6;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}
						//��� ������
						else 	if (_tile[p][k].stoneTileFrameX == 5)
						{
							_tile[p][k].stoneTileFrameX = 7;
							_tile[p][k].stoneTileFrameY = 6;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}
						//���ܸ� ������
						else 	if (_tile[p][k].stoneTileFrameX == 0)
						{
							_tile[p][k].stoneTileFrameX = 2;
							_tile[p][k].stoneTileFrameY = 6;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}
					}

					//������ ������
					else if (_tile[p][k].stoneTileFrameY == 1)
					{
						//��ܵ� ������
						if (_tile[p][k].stoneTileFrameX == 2)
						{
							_tile[p][k].stoneTileFrameX = 12;
							_tile[p][k].stoneTileFrameY = 6;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}

						//���ϴܵ� ������
						else if (_tile[p][k].stoneTileFrameX == 5)
						{
							_tile[p][k].stoneTileFrameX = 10;
							_tile[p][k].stoneTileFrameY = 6;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}
						//������ ������
						else if (_tile[p][k].stoneTileFrameX == 0)
						{
							_tile[p][k].stoneTileFrameX = 8;
							_tile[p][k].stoneTileFrameY = 6;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}
					}

					//����� ������
					else if (_tile[p][k].stoneTileFrameY == 4)
					{
						//������ ������
						if (_tile[p][k].stoneTileFrameX == 2)
						{
							_tile[p][k].stoneTileFrameX = 12;
							_tile[p][k].stoneTileFrameY = 6;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}
						//���ϴܵ� ������
						else if (_tile[p][k].stoneTileFrameX == 5)
						{
							_tile[p][k].stoneTileFrameX = 11;
							_tile[p][k].stoneTileFrameY = 6;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}
						//�ϴܸ� ������
						else if (_tile[p][k].stoneTileFrameX == 0)
						{
							_tile[p][k].stoneTileFrameX = 9;
							_tile[p][k].stoneTileFrameY = 6;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}
					}

					else
					{
						_tile[p][k].stoneTileFrameX = 0;
						_tile[p][k].stoneTileFrameY = 6;
						_tile[p][k]._state = STONETILE;
						_tile[p][k].stoneExist = true;
					}
				}

				//��� p == x
				else if (k == y)
				{
					//����� �̹� ����ִٸ�
					if (_tile[p][k].stoneTileFrameY == 4) continue;


					//������ ������
					if (_tile[p][k].stoneTileFrameY == 1)
					{
						//������ ������
						if (_tile[p][k].stoneTileFrameX == 3)
						{
							_tile[p][k].stoneTileFrameX = 9;
							_tile[p][k].stoneTileFrameY = 4;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}
						//�ϴܵ� ������
						else if (_tile[p][k].stoneTileFrameX == 1)
						{
							_tile[p][k].stoneTileFrameX = 10;
							_tile[p][k].stoneTileFrameY = 4;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}
						//���ϴܵ� ������
						else if (_tile[p][k].stoneTileFrameX == 4)
						{
							_tile[p][k].stoneTileFrameX = 8;
							_tile[p][k].stoneTileFrameY = 4;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}

						//������ ������
						else if (_tile[p][k].stoneTileFrameX == 0)
						{
							_tile[p][k].stoneTileFrameX = 2;
							_tile[p][k].stoneTileFrameY = 4;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}
					}
					//������ ������
					else if (_tile[p][k].stoneTileFrameY == 2)
					{
						//������ ������
						if (_tile[p][k].stoneTileFrameX == 3)
						{
							_tile[p][k].stoneTileFrameX = 9;
							_tile[p][k].stoneTileFrameY = 4;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}
						//�ϴܵ� ������
						else if (_tile[p][k].stoneTileFrameX == 1)
						{
							_tile[p][k].stoneTileFrameX = 11;
							_tile[p][k].stoneTileFrameY = 4;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}
						//���ϴܵ� ������
						else if (_tile[p][k].stoneTileFrameX == 4)
						{
							_tile[p][k].stoneTileFrameX = 7;
							_tile[p][k].stoneTileFrameY = 4;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}

						else if (_tile[p][k].stoneTileFrameX == 0)
						{
							_tile[p][k].stoneTileFrameX = 1;
							_tile[p][k].stoneTileFrameY = 4;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}
					}

					//�ϴ��� ������
					else if (_tile[p][k].stoneTileFrameY == 3)
					{
						//������ ������
						if (_tile[p][k].stoneTileFrameX == 2)
						{
							_tile[p][k].stoneTileFrameX = 10;
							_tile[p][k].stoneTileFrameY = 4;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}
						//������ ������
						else if (_tile[p][k].stoneTileFrameX == 1)
						{
							_tile[p][k].stoneTileFrameX = 11;
							_tile[p][k].stoneTileFrameY = 4;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}
						//�ϴܸ� ������
						else if (_tile[p][k].stoneTileFrameX == 0)
						{
							_tile[p][k].stoneTileFrameX = 3;
							_tile[p][k].stoneTileFrameY = 4;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}
					}

					//���ϴ��� ������
					else if (_tile[p][k].stoneTileFrameY == 5)
					{
						//������ ������
						if (_tile[p][k].stoneTileFrameX == 8)
						{
							_tile[p][k].stoneTileFrameX = 8;
							_tile[p][k].stoneTileFrameY = 4;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}
						//���ϴܵ� ������
						else if (_tile[p][k].stoneTileFrameX == 1)
						{
							_tile[p][k].stoneTileFrameX = 6;
							_tile[p][k].stoneTileFrameY = 4;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}
						//���ϴܸ� ������
						else if (_tile[p][k].stoneTileFrameX == 0)
						{
							_tile[p][k].stoneTileFrameX = 5;
							_tile[p][k].stoneTileFrameY = 4;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}
					}

					//���ϴ��� ������
					else if (_tile[p][k].stoneTileFrameX == 6)
					{
						//������ ������
						if (_tile[p][k].stoneTileFrameX == 8)
						{
							_tile[p][k].stoneTileFrameX = 8;
							_tile[p][k].stoneTileFrameY = 4;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}
						//���ϴܵ� ������
						else if (_tile[p][k].stoneTileFrameX == 1)
						{
							_tile[p][k].stoneTileFrameX = 6;
							_tile[p][k].stoneTileFrameY = 4;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}
						//���ϴܸ� ������
						else if (_tile[p][k].stoneTileFrameX == 0)
						{
							_tile[p][k].stoneTileFrameX = 4;
							_tile[p][k].stoneTileFrameY = 4;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}
					}

					else
					{
						_tile[p][k].stoneTileFrameX = 0;
						_tile[p][k].stoneTileFrameY = 4;
						_tile[p][k]._state = STONETILE;
						_tile[p][k].stoneExist = true;
					}
				}

				//�ϴ� p == x + _xEnd - 1
				else if (k == y + _yEnd - 1)
				{
					//�ϴ��� �̹� ����ִٸ�
					if (_tile[p][k].stoneTileFrameY == 3) continue;

					//������ ������
					if (_tile[p][k].stoneTileFrameY == 1)
					{
						//������ ������
						if (_tile[p][k].stoneTileFrameX == 3)
						{
							_tile[p][k].stoneTileFrameX = 9;
							_tile[p][k].stoneTileFrameY = 3;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}
						//��ܵ� ������
						else if (_tile[p][k].stoneTileFrameX == 2)
						{
							_tile[p][k].stoneTileFrameX = 10;
							_tile[p][k].stoneTileFrameY = 3;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}
						//���ܵ� ������
						else if (_tile[p][k].stoneTileFrameX == 5)
						{
							_tile[p][k].stoneTileFrameX = 8;
							_tile[p][k].stoneTileFrameY = 3;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}

						//������ ������ (Ŀ��� ����)
						else if (_tile[p][k].stoneTileFrameX == 0)
						{
							_tile[p][k].stoneTileFrameX = 2;
							_tile[p][k].stoneTileFrameY = 3;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}
					}

					//������ ������
					else if (_tile[p][k].stoneTileFrameY == 2)
					{
						//������ ������
						if (_tile[p][k].stoneTileFrameX == 3)
						{
							_tile[p][k].stoneTileFrameX = 9;
							_tile[p][k].stoneTileFrameY = 3;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}
						//��ܵ� ������
						else if (_tile[p][k].stoneTileFrameX == 2)
						{
							_tile[p][k].stoneTileFrameX = 11;
							_tile[p][k].stoneTileFrameY = 3;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}
						//�»�ܵ� ������
						else if (_tile[p][k].stoneTileFrameX == 5)
						{
							_tile[p][k].stoneTileFrameX = 7;
							_tile[p][k].stoneTileFrameY = 3;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}
						//������ ������
						else if (_tile[p][k].stoneTileFrameX == 0)
						{
							_tile[p][k].stoneTileFrameX = 1;
							_tile[p][k].stoneTileFrameY = 3;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}
					}

					//����� ������
					else if (_tile[p][k].stoneTileFrameY == 4)
					{
						//������ ������
						if (_tile[p][k].stoneTileFrameX == 2)
						{
							_tile[p][k].stoneTileFrameX = 10;
							_tile[p][k].stoneTileFrameY = 3;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}
						//������ ������
						else if (_tile[p][k].stoneTileFrameX == 1)
						{
							_tile[p][k].stoneTileFrameX = 11;
							_tile[p][k].stoneTileFrameY = 3;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}
						//��ܸ� ������
						else if (_tile[p][k].stoneTileFrameX == 0)
						{
							_tile[p][k].stoneTileFrameX = 3;
							_tile[p][k].stoneTileFrameY = 3;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}
					}

					//�»���� ������
					else if (_tile[p][k].stoneTileFrameY == 8)
					{
						//������ ������
						if (_tile[p][k].stoneTileFrameX == 8)
						{
							_tile[p][k].stoneTileFrameX = 7;
							_tile[p][k].stoneTileFrameY = 3;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}
						//���ܵ� ������
						else if (_tile[p][k].stoneTileFrameX == 1)
						{
							_tile[p][k].stoneTileFrameX = 6;
							_tile[p][k].stoneTileFrameY = 3;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}
						//���ϴܸ� ������
						else if (_tile[p][k].stoneTileFrameX == 0)
						{
							_tile[p][k].stoneTileFrameX = 4;
							_tile[p][k].stoneTileFrameY = 3;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}
					}

					//������ ������
					else if (_tile[p][k].stoneTileFrameY == 7)
					{
						//������ ������
						if (_tile[p][k].stoneTileFrameX == 8)
						{
							_tile[p][k].stoneTileFrameX = 8;
							_tile[p][k].stoneTileFrameY = 3;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}
						//�»�ܵ� ������
						else if (_tile[p][k].stoneTileFrameX == 1)
						{
							_tile[p][k].stoneTileFrameX = 6;
							_tile[p][k].stoneTileFrameY = 3;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}
						//���ܸ� ������
						else if (_tile[p][k].stoneTileFrameX == 0)
						{
							_tile[p][k].stoneTileFrameX = 5;
							_tile[p][k].stoneTileFrameY = 3;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}
					}

					else
					{
						_tile[p][k].stoneTileFrameX = 0;
						_tile[p][k].stoneTileFrameY = 3;
						_tile[p][k]._state = STONETILE;
						_tile[p][k].stoneExist = true;
					}
				}

				//���� k == y
				else if (p == x)
				{
					//������ �̹� ��ȴٸ�
					if (_tile[p][k].stoneTileFrameY == 1) continue;

					//����� ������
					if (_tile[p][k].stoneTileFrameY == 4)
					{
						//������ ������
						if (_tile[p][k].stoneTileFrameX == 1) // ������
						{
							_tile[p][k].stoneTileFrameX = 11;
							_tile[p][k].stoneTileFrameY = 1;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}
						//���ϴܵ� ������
						else if (_tile[p][k].stoneTileFrameX == 4)
						{
							_tile[p][k].stoneTileFrameX = 8;
							_tile[p][k].stoneTileFrameY = 1;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}

						//��ܸ� ������
						else if (_tile[p][k].stoneTileFrameX == 0)
						{
							_tile[p][k].stoneTileFrameX = 2;
							_tile[p][k].stoneTileFrameY = 1;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}
					}

					//�ϴ��� ������
					else if (_tile[p][k].stoneTileFrameY == 3)
					{
						//������ ������
						if (_tile[p][k].stoneTileFrameX == 1)
						{
							_tile[p][k].stoneTileFrameX = 10;
							_tile[p][k].stoneTileFrameY = 1;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}

						//���ܵ� ������
						else if (_tile[p][k].stoneTileFrameX == 5)
						{
							_tile[p][k].stoneTileFrameX = 7;
							_tile[p][k].stoneTileFrameY = 1;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}


						//�ϴܸ� ������
						else if (_tile[p][k].stoneTileFrameX == 0)
						{
							_tile[p][k].stoneTileFrameX = 1;
							_tile[p][k].stoneTileFrameY = 1;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}
					}

					//���ϴ��� ������
					else if (_tile[p][k].stoneTileFrameY == 6)
					{
						//��ܵ� ������
						if (_tile[p][k].stoneTileFrameX == 9)
						{
							_tile[p][k].stoneTileFrameX = 8;
							_tile[p][k].stoneTileFrameY = 1;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}

						//���ܵ� ������
						else 	if (_tile[p][k].stoneTileFrameX == 2)
						{
							_tile[p][k].stoneTileFrameX = 6;
							_tile[p][k].stoneTileFrameY = 1;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}



						//���ϴܸ� ������
						else if (_tile[p][k].stoneTileFrameX == 0)
						{
							_tile[p][k].stoneTileFrameX = 4;
							_tile[p][k].stoneTileFrameY = 1;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}
					}

					//������ ������
					else if (_tile[p][k].stoneTileFrameY == 7)
					{
						//�ϴܵ� ������
						if (_tile[p][k].stoneTileFrameX == 9)
						{
							_tile[p][k].stoneTileFrameX = 7;
							_tile[p][k].stoneTileFrameY = 1;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}

						//���ϴܵ� ������
						else 	if (_tile[p][k].stoneTileFrameX == 2)
						{
							_tile[p][k].stoneTileFrameX = 6;
							_tile[p][k].stoneTileFrameY = 1;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}

						//���ܸ� ������
						else if (_tile[p][k].stoneTileFrameX == 0)
						{
							_tile[p][k].stoneTileFrameX = 5;
							_tile[p][k].stoneTileFrameY = 1;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}

					}

					//������ ������
					else if (_tile[p][k].stoneTileFrameY == 2)
					{
						if (_tile[p][k].stoneTileFrameX == 0)
						{
							_tile[p][k].stoneTileFrameX = 3;
							_tile[p][k].stoneTileFrameY = 1;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}
						else if (_tile[p][k].stoneTileFrameX == 2)
						{
							_tile[p][k].stoneTileFrameX = 11;
							_tile[p][k].stoneTileFrameY = 1;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}
						else if (_tile[p][k].stoneTileFrameX == 1)
						{
							_tile[p][k].stoneTileFrameX = 10;
							_tile[p][k].stoneTileFrameY = 1;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}
					}

					else
					{
						_tile[p][k].stoneTileFrameX = 0;
						_tile[p][k].stoneTileFrameY = 1;
						_tile[p][k]._state = STONETILE;
						_tile[p][k].stoneExist = true;
					}
				}

				//���� k == y + _yEnd - 1
				else if (p == x + _xEnd - 1)
				{
					//������ �̹� ��ȴٸ�
					if (_tile[p][k].stoneTileFrameY == 2) continue;

					//����� ������
					if (_tile[p][k].stoneTileFrameY == 4)
					{
						//������ ������
						if (_tile[p][k].stoneTileFrameX == 2)
						{
							_tile[p][k].stoneTileFrameX = 11;
							_tile[p][k].stoneTileFrameY = 2;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}
						//���ϴܵ� ������
						else if (_tile[p][k].stoneTileFrameX == 5)
						{
							_tile[p][k].stoneTileFrameX = 8;
							_tile[p][k].stoneTileFrameY = 2;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}

						//��ܸ� ������
						else if (_tile[p][k].stoneTileFrameX == 0)
						{
							_tile[p][k].stoneTileFrameX = 2;
							_tile[p][k].stoneTileFrameY = 2;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}
					}

					//�ϴ��� ������
					else if (_tile[p][k].stoneTileFrameY == 3)
					{
						//������ ������
						if (_tile[p][k].stoneTileFrameX == 2)
						{
							_tile[p][k].stoneTileFrameX = 10;
							_tile[p][k].stoneTileFrameY = 2;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}

						//�»�ܵ� ������
						else if (_tile[p][k].stoneTileFrameX == 5)
						{
							_tile[p][k].stoneTileFrameX = 7;
							_tile[p][k].stoneTileFrameY = 2;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}


						//�ϴܸ� ������
						else if (_tile[p][k].stoneTileFrameX == 0)
						{
							_tile[p][k].stoneTileFrameX = 1;
							_tile[p][k].stoneTileFrameY = 2;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}
					}

					//���ϴ��� ������
					else if (_tile[p][k].stoneTileFrameY == 5)
					{
						//��ܵ� ������
						if (_tile[p][k].stoneTileFrameX == 9)
						{
							_tile[p][k].stoneTileFrameX = 8;
							_tile[p][k].stoneTileFrameY = 2;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}

						//�»�ܵ� ������
						else 	if (_tile[p][k].stoneTileFrameX == 2)
						{
							_tile[p][k].stoneTileFrameX = 6;
							_tile[p][k].stoneTileFrameY = 2;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}

						//���ϴܸ� ������
						else if (_tile[p][k].stoneTileFrameX == 0)
						{
							_tile[p][k].stoneTileFrameX = 4;
							_tile[p][k].stoneTileFrameY = 2;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}
					}

					//�»���� ������
					else if (_tile[p][k].stoneTileFrameY == 8)
					{
						//�ϴܵ� ������5
						if (_tile[p][k].stoneTileFrameX == 9)
						{
							_tile[p][k].stoneTileFrameX = 7;
							_tile[p][k].stoneTileFrameY = 2;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}

						//���ϴܵ� ������
						else 	if (_tile[p][k].stoneTileFrameX == 2)
						{
							_tile[p][k].stoneTileFrameX = 6;
							_tile[p][k].stoneTileFrameY = 2;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}

						//�»�ܸ� ������
						else if (_tile[p][k].stoneTileFrameX == 0)
						{
							_tile[p][k].stoneTileFrameX = 5;
							_tile[p][k].stoneTileFrameY = 2;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}

					}

					//������ ������
					else if (_tile[p][k].stoneTileFrameY == 1)
					{
						if (_tile[p][k].stoneTileFrameX == 0)
						{
							_tile[p][k].stoneTileFrameX = 3;
							_tile[p][k].stoneTileFrameY = 2;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;

						}
						else if (_tile[p][k].stoneTileFrameX == 2)
						{
							_tile[p][k].stoneTileFrameX = 11;
							_tile[p][k].stoneTileFrameY = 2;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}
						else if (_tile[p][k].stoneTileFrameX == 1)
						{
							_tile[p][k].stoneTileFrameX = 10;
							_tile[p][k].stoneTileFrameY = 2;
							_tile[p][k]._state = STONETILE;
							_tile[p][k].stoneExist = true;
						}
					}
					else
					{
						_tile[p][k].stoneTileFrameX = 0;
						_tile[p][k].stoneTileFrameY = 2;
						_tile[p][k]._state = STONETILE;
						_tile[p][k].stoneExist = true;
					}
				}

				//�߾Ӻκ�
				else
				{
					_tile[p][k].stoneTileFrameX = 0;
					_tile[p][k].stoneTileFrameY = 0;
					_tile[p][k]._state = STONETILE;
					_tile[p][k].stoneExist = true;

					int rnd_obj = RND->getInt(2);

					if (rnd_obj == 0) _tile[p][k]._objstate = ROCK;
					else if (rnd_obj == 1) _tile[p][k]._objstate = HAYSTACK;

				}

			}
		}
	}
	if (_tile == nullptr) return false;
	return true;
}

bool Tiles::objEnviInit()
{
	for (int i = 1; i < TILEX - 1; i += 3)
	{
		for (int j = 1; j < TILEY - 1; j += 3)
		{
			int rnd_x = RND->getInt(120);
			int rnd_y = RND->getInt(120);

			switch (_tile[i][j]._objstate)
			{
			case NONE_ENVIRONMENT:
				break;
			case FLOWER:
				vObjEnvi[i][j].init(FLOWER, { i*TILESIZEX + rnd_x, j*TILESIZEY + rnd_y });
				break;
			case PLANTCARROT:
				vObjEnvi[i][j].init(PLANTCARROT, { i*TILESIZEX + rnd_x, j*TILESIZEY + rnd_y });

				break;
			case TREE1:
				vObjEnvi[i][j].init(TREE1, { i*TILESIZEX + rnd_x, j*TILESIZEY + rnd_y });

				break;
			case TREE2:
				vObjEnvi[i][j].init(TREE2, { i*TILESIZEX + rnd_x, j*TILESIZEY + rnd_y });

				break;
			case RASPBERRYSTACK:
				vObjEnvi[i][j].init(RASPBERRYSTACK, { i*TILESIZEX + rnd_x, j*TILESIZEY + rnd_y });

				break;
			case ROCK:
				vObjEnvi[i][j].init(ROCK, { i*TILESIZEX + rnd_x, j*TILESIZEY + rnd_y });

				break;
			case HAYSTACK:
				vObjEnvi[i][j].init(HAYSTACK, { i*TILESIZEX + rnd_x, j*TILESIZEY + rnd_y });

				break;
			default:
				break;
			}

		}
	}
	return true;
}


//�߰�
bool Tiles::objMateInit()
{
	OBJECT_MATERIAL tmp;

	for (int i = 1; i < TILEX - 1; i += 4)
	{
		for (int j = 1; j < TILEY - 1; j += 4)
		{
			int rnd_kind = (EOBJKIND_MATERIAL)RND->getInt(6);

			int rnd_x = RND->getInt(100);
			int rnd_y = RND->getInt(100);

			switch (rnd_kind)
			{
			case FLINT:
				tmp.init(FLINT, { i * TILESIZEX + rnd_x, j * TILESIZEY + rnd_y });
				vObjMate[j][i].push_back(tmp);
				break;
			case STONE:
				tmp.init(STONE, { i * TILESIZEX + rnd_x , j * TILESIZEY + rnd_y });
				vObjMate[j][i].push_back(tmp);
				break;
			case BRANCH:
				tmp.init(BRANCH, { i * TILESIZEX + rnd_x, j * TILESIZEY + rnd_y });
				vObjMate[j][i].push_back(tmp);
				break;
			case BOARD:
				tmp.init(BOARD, { i * TILESIZEX + rnd_x, j * TILESIZEY + rnd_y });
				vObjMate[j][i].push_back(tmp);
				break;
			default:
				break;
			}
		}
	}
	return true;
}

void Tiles::waveMotion(int i)
{
	if (_wave[i].wave_count < 200)
	{
		_wave[i].x -= 0.4;
		_wave[i].y -= 0.4;
	}
	else if (_wave[i].wave_count < 300)
	{
		_wave[i].x -= 0.2;
		_wave[i].y -= 0.2;
	}

	else if (_wave[i].wave_count < 400)
	{
		_wave[i].x += 0.2;
		_wave[i].y += 0.2;

	}

	else if (_wave[i].wave_count < 600)
	{
		_wave[i].x += 0.4;
		_wave[i].y += 0.4;
	}

	_wave[i].wave_count++;

	if (_wave[i].wave_count == 601) _wave[i].wave_count = 0;
}

bool Tiles::maptool_objEnviInit()
{
	for (int i = 1; i < TILEX - 1; i++)
	{
		for (int j = 1; j < TILEY - 1; j++)
		{
			int rnd_x = RND->getInt(200);
			int rnd_y = RND->getInt(200);

			switch (_tile[i][j]._objstate)
			{
			case NONE_ENVIRONMENT:
				break;
			case FLOWER:
				vObjEnvi[i][j].init(FLOWER, { i*TILESIZEX + rnd_x, j*TILESIZEY + rnd_y });
				break;
			case PLANTCARROT:
				vObjEnvi[i][j].init(PLANTCARROT, { i*TILESIZEX + rnd_x, j*TILESIZEY + rnd_y });

				break;
			case TREE1:
				vObjEnvi[i][j].init(TREE1, { i*TILESIZEX + rnd_x, j*TILESIZEY + rnd_y });

				break;
			case TREE2:
				vObjEnvi[i][j].init(TREE2, { i*TILESIZEX + rnd_x, j*TILESIZEY + rnd_y });

				break;
			case RASPBERRYSTACK:
				vObjEnvi[i][j].init(RASPBERRYSTACK, { i*TILESIZEX + rnd_x, j*TILESIZEY + rnd_y });

				break;
			case ROCK:
				vObjEnvi[i][j].init(ROCK, { i*TILESIZEX + rnd_x, j*TILESIZEY + rnd_y });

				break;
			case HAYSTACK:
				vObjEnvi[i][j].init(HAYSTACK, { i*TILESIZEX + rnd_x, j*TILESIZEY + rnd_y });

				break;
			default:
				break;
			}

		}
	}
	return true;
}

void Tiles::miniTileInit()
{
	for (int i = 0; i < TILEX; i++)
	{
		for (int k = 0; k < TILEY; k++)
		{
			_minitile[i][k]._x = i * MINITILESIZEX;
			_minitile[i][k]._y = k * MINITILESIZEY;
			_minitile[i][k]._state = _tile[i][k]._state;
		}
	}
}

void Tiles::showMinimap()
{
	POINT _tmpPoint = { 250,250 };
	for (int i = _standard.x - 7; i < _standard.x + 7; ++i) {
		for (int j = _standard.y - 7; j < _standard.y + 7; ++j) {
			if (i < 0 || j < 0) continue;
			if (i >= TILEX || j >= TILEY) continue;
			POINT _ttmp = CAMERAMANAGER->getAbsPosition({ i*MINITILESIZEX, j*MINITILESIZEY });
			POINT _tttmp = CAMERAMANAGER->getStandardPoint();
			//if (_minitile[i][j]._state == GRASSTILE)
			//IMAGEMANAGER->render(L"minigrass", Rt, _ttmp.x + _tttmp.x , _ttmp.y + _tttmp.y);
			//if (_minitile[i][j]._state == FORESTTILE)
			//	IMAGEMANAGER->render(L"miniforest", Rt, _ttmp.x + _tttmp.x, _ttmp.y + _tttmp.y);
			//if (_minitile[i][j]._state == STONETILE)
			//	IMAGEMANAGER->render(L"ministone", Rt, _ttmp.x + _tttmp.x, _ttmp.y + _tttmp.y);
			if (_minitile[i][j]._state == GRASSTILE)
				IMAGEMANAGER->render(L"minigrass", Rt, (i - _standard.x - 7)*MINITILESIZEX + WINSIZEX_NUM / 2, (j - _standard.y - 7)*MINITILESIZEY + WINSIZEY_NUM / 2);
			if (_minitile[i][j]._state == FORESTTILE)
				IMAGEMANAGER->render(L"miniforest", Rt, (i - _standard.x - 7)*MINITILESIZEX + WINSIZEX_NUM / 2, (j - _standard.y - 7)*MINITILESIZEY + WINSIZEY_NUM / 2);
			if (_minitile[i][j]._state == STONETILE)
				IMAGEMANAGER->render(L"ministone", Rt, (i - _standard.x - 7)*MINITILESIZEX + WINSIZEX_NUM / 2, (j - _standard.y - 7)*MINITILESIZEY + WINSIZEY_NUM / 2);
		}
	}
}

void Tiles::mapLoad()
{
	HANDLE file;
	DWORD read;
	file = CreateFile(L"tileMap.map",
		GENERIC_READ,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	ReadFile(file, _tile, sizeof(S_TILE) * TILEX * TILEY, &read, NULL);
	CloseHandle(file);
}

void Tiles::objInit()
{

	for (int i = 0; i < TILEX; i++)
	{
		for (int j = 0; j < TILEY; j++)
		{
			vObjEnvi[i][j].init(NONE_ENVIRONMENT, { 0, 0 });
		}
	}

}