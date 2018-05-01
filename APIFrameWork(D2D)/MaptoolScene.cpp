#include "stdafx.h"
#include "MaptoolScene.h"

MaptoolScene::MaptoolScene()
{
}


MaptoolScene::~MaptoolScene()
{
}

HRESULT MaptoolScene::init(void)
{
	SOUNDMANAGER->stop("mainBGM");
	if (!SOUNDMANAGER->isPlaySound("maptoolsound")) SOUNDMANAGER->bgmPlay("maptoolsound", 0.3f);

	erese_button = { 680, 420, 780, 520 };
	reset_button = { 680, 570, 780, 670 };
	save_button = { 820, 420, 920, 520 };
	load_button = { 820, 570, 920, 670 };
	minimap_button = { 960, 420, 1060, 520 };
	exit_button = { 960, 570, 1060, 670 };


	maptoolSetup();

	_currentTile.x = 2;
	_currentTile.y = 0;

	_x = _y = 0;

	show_minimap = false;

	mouse_state = 0;

	_index = 0;
	return S_OK;
}

void MaptoolScene::release(void)
{

}

void MaptoolScene::update(void)
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		for (int i = 0; i < SAMPLETILEX * SAMPLETILEY; i++)
		{
			if (PtInRect(&_sampleTiles[i].rcTile, _ptMouse))
			{
				mouse_state = SELECTTILE;
			}
		}
		this->setMap();


		if (PtInRect(&exit_button, _ptMouse))
		{
			SOUNDMANAGER->stop("maptoolsound");
			SCENEMANAGER->changeScene("menuScene");
		}


		if (PtInRect(&minimap_button, _ptMouse))
		{
			//save();
			SOUNDMANAGER->stop("maptoolsound");
			SCENEMANAGER->changeScene("selectScene");

		}

		if (PtInRect(&erese_button, _ptMouse))
		{
			if (mouse_state == SELECTTILE)
			{
				mouse_state = ERESETILE;
			}
		}

		if (PtInRect(&reset_button, _ptMouse))
		{
			resetTile();
		}

		if (PtInRect(&save_button, _ptMouse))
		{
			save();
		}

		if (PtInRect(&load_button, _ptMouse))
		{
			load();
		}
	}

	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		_x--;
		if (_x < 0)
		{
			_x = 0;
		}
		else
		{
			for (int i = 0; i < TILEX * TILEY; i++)
			{
				_tiles[i].rc.top += M_TILESIZE;
				_tiles[i].rc.bottom += M_TILESIZE;
			}
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		_x++;
		if (_x > TILEX - 8)
		{
			_x = TILEX - 8;
		}
		else
		{
			for (int i = 0; i < TILEX * TILEY; i++)
			{
				_tiles[i].rc.top -= M_TILESIZE;
				_tiles[i].rc.bottom -= M_TILESIZE;
			}
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_y--;
		if (_y < 0)
		{
			_y = 0;
		}
		else
		{
			for (int i = 0; i < TILEX * TILEY; i++)
			{
				_tiles[i].rc.left += M_TILESIZE;
				_tiles[i].rc.right += M_TILESIZE;
			}
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_y++;
		if (_y > TILEY - 8)
		{
			_y = TILEY - 8;
		}
		else
		{
			for (int i = 0; i < TILEX * TILEY; i++)
			{
				_tiles[i].rc.left -= M_TILESIZE;
				_tiles[i].rc.right -= M_TILESIZE;
			}
		}
	}
	if (KEYMANAGER->isOnceKeyDown('P'))
	{
		int a = 0;
	}
	minimapUpdate();
}

void MaptoolScene::render(void)
{
	IMAGEMANAGER->render(L"backgound", Rt);
	IMAGEMANAGER->render(L"tileset_bg", Rt, WINSIZEX_NUM - 200, 0);
	IMAGEMANAGER->render(L"mini_tileset", Rt, WINSIZEX_NUM - 165, 90);

	int k = (_y)* (TILEY)+_x;

	int _count = 0;

	for (int i = k; i < 8 * TILEY + k; ++i)
	{
		_count++;

		if (_count == 9)
		{
			i += TILEX - 9;
			_count = 0;
		}

		if (_tiles[i].rc.left < 50 || _tiles[i].rc.top < 50) continue;
		IMAGEMANAGER->frameRender(L"grass_tilemap", Rt, _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].backTileFrameX, _tiles[i].backTileFrameY);
		if (_tiles[i].forestExist == true)
			IMAGEMANAGER->frameRender(L"forest_tilemap", Rt, _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].forestTileFrameX, _tiles[i].forestTileFrameY);
		if (_tiles[i].stoneExist == true)
			IMAGEMANAGER->frameRender(L"stone_tilemap", Rt, _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].stoneTileFrameX, _tiles[i].stoneTileFrameY);

		if (_tiles[i]._objstate == FLOWER)
			IMAGEMANAGER->render(L"m_object_flower", Rt, _tiles[i].rc.left + 20, _tiles[i].rc.top + 20);
		if (_tiles[i]._objstate == PLANTCARROT)
			IMAGEMANAGER->render(L"m_object_planted_carrot", Rt, _tiles[i].rc.left, _tiles[i].rc.top);
		if (_tiles[i]._objstate == TREE1)
			IMAGEMANAGER->frameRender(L"m_object_tree1_idle", Rt, _tiles[i].rc.left, _tiles[i].rc.top, 0, 0);
		if (_tiles[i]._objstate == TREE2)
			IMAGEMANAGER->frameRender(L"m_object_tree2_idle", Rt, _tiles[i].rc.left, _tiles[i].rc.top, 0, 0);
		if (_tiles[i]._objstate == RASPBERRYSTACK)
			IMAGEMANAGER->render(L"m_object_berrybush_idle", Rt, _tiles[i].rc.left, _tiles[i].rc.top);
		if (_tiles[i]._objstate == ROCK)
			IMAGEMANAGER->render(L"m_object_rock1", Rt, _tiles[i].rc.left, _tiles[i].rc.top);
		if (_tiles[i]._objstate == HAYSTACK)
			IMAGEMANAGER->frameRender(L"m_object_hay_idle", Rt, _tiles[i].rc.left, _tiles[i].rc.top, 0, 0);
		if (PtInRect(&_tiles[i].rc, _ptMouse))
		{
			Rt->FillRectangle(D2D1::RectF(_tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].rc.right, _tiles[i].rc.bottom), WhiteBrush);
		}
	}

	IMAGEMANAGER->render(L"backboard", Rt, 40, 40);


	for (int i = 0; i < SAMPLETILEX * SAMPLETILEY; i++)
	{
		if (PtInRect(&_sampleTiles[i].rcTile, _ptMouse))
		{
			Rt->FillRectangle(D2D1::RectF(_sampleTiles[i].rcTile.left, _sampleTiles[i].rcTile.top, _sampleTiles[i].rcTile.right, _sampleTiles[i].rcTile.bottom), WhiteBrush);
			break;
		}
	}



	//if (show_minimap == true)
	//{
	//	for (int i = 0; i < TILEX * TILEY; i++)
	//	{
	//		IMAGEMANAGER->frameRender(L"minimap_grass_tilemap", Rt, _minimaptiles[i].rc.left, _minimaptiles[i].rc.top, _minimaptiles[i].backTileFrameX, _minimaptiles[i].backTileFrameY);
	//		if (_minimaptiles[i].forestExist == true)
	//			IMAGEMANAGER->frameRender(L"minimap_forest_tilemap", Rt, _minimaptiles[i].rc.left, _minimaptiles[i].rc.top, _minimaptiles[i].forestTileFrameX, _minimaptiles[i].forestTileFrameY);
	//		if (_minimaptiles[i].stoneExist == true)
	//			IMAGEMANAGER->frameRender(L"minimap_stone_tilemap", Rt, _minimaptiles[i].rc.left, _minimaptiles[i].rc.top, _minimaptiles[i].stoneTileFrameX, _minimaptiles[i].stoneTileFrameY);

	//	}
	//}

	IMAGEMANAGER->render(L"erese_bt", Rt, 680, 420);
	IMAGEMANAGER->render(L"reset_bt", Rt, 680, 570);
	IMAGEMANAGER->render(L"save_bt", Rt, 820, 420);
	IMAGEMANAGER->render(L"load_bt", Rt, 820, 570);
	IMAGEMANAGER->render(L"minimap_bt", Rt, 960, 420);
	IMAGEMANAGER->render(L"exit_bt", Rt, 960, 570);


	TCHAR text[20];
	wsprintf(text, L"index : %d", _index);
	D2TextOut(Rt, text, TextFormat, D2D1::Rect(650, 100, 900, 120), Brush);

	wsprintf(text, L"x : %d", _index / TILEX);
	D2TextOut(Rt, text, TextFormat, D2D1::Rect(650, 125, 900, 150), Brush);
	wsprintf(text, L"y : %d", _index % TILEY);
	D2TextOut(Rt, text, TextFormat, D2D1::Rect(650, 150, 900, 180), Brush);
}



void MaptoolScene::maptoolSetup()
{

	for (int i = 0; i < SAMPLETILEY; i++)
	{
		for (int j = 0; j < SAMPLETILEX; j++)
		{
			_sampleTiles[i * SAMPLETILEX + j].terrainFrameX = j;
			_sampleTiles[i * SAMPLETILEX + j].terrainFrameY = i;

			SetRect(&_sampleTiles[i * SAMPLETILEX + j].rcTile,
				(WINSIZEX_NUM - 165) + j * MINITILESIZE,
				i * MINITILESIZE + 90,
				(WINSIZEX_NUM - 165) + j * MINITILESIZE + MINITILESIZE,
				i * MINITILESIZE + MINITILESIZE + 90);
		}
	}



	for (int i = 0; i < TILEY; i++)
	{
		for (int j = 0; j < TILEX; j++)
		{
			SetRect(&_tiles[i * TILEX + j].rc,
				i * M_TILESIZE + 50,
				j * M_TILESIZE + 50,
				i * M_TILESIZE + M_TILESIZE + 50,
				j * M_TILESIZE + M_TILESIZE + 50);
		}
	}

	for (int i = 0; i < TILEY; i++)
	{
		for (int j = 0; j < TILEX; j++)
		{
			SetRect(&_minimaptiles[i * TILEX + j].rc,
				j * MINIMAPTILESIZE + 680,
				i * MINIMAPTILESIZE + 40,
				j * MINIMAPTILESIZE + MINIMAPTILESIZE + 680,
				i * MINIMAPTILESIZE + MINIMAPTILESIZE + 40);
		}
	}


	for (int i = 0; i < TILEX * TILEY; i++)
	{
		_tiles[i].backTileFrameX = 0;
		_tiles[i].backTileFrameY = 0;

		_tiles[i].forestTileFrameX = 0;
		_tiles[i].forestTileFrameY = 0;

		_tiles[i].stoneTileFrameX = 0;
		_tiles[i].stoneTileFrameY = 0;

		_tiles[i].forestExist = false;
		_tiles[i].stoneExist = false;

		_tiles[i]._state = GRASSTILE;
		_tiles[i]._objstate = NONE_ENVIRONMENT;
	}


	for (int i = 0; i < TILEX * TILEY; i++)
	{
		_minimaptiles[i].backTileFrameX = 0;
		_minimaptiles[i].backTileFrameY = 0;

		_minimaptiles[i].forestTileFrameX = 0;
		_minimaptiles[i].forestTileFrameY = 0;

		_minimaptiles[i].stoneTileFrameX = 0;
		_minimaptiles[i].stoneTileFrameY = 0;

		_minimaptiles[i].forestExist = false;
		_minimaptiles[i].stoneExist = false;
		_minimaptiles[i]._state = GRASSTILE;
	}
}

void MaptoolScene::setMap()
{
	for (int i = 0; i < SAMPLETILEX * SAMPLETILEY; i++)
	{
		if (PtInRect(&_sampleTiles[i].rcTile, _ptMouse))
		{
			_currentTile.x = _sampleTiles[i].terrainFrameX;
			_currentTile.y = _sampleTiles[i].terrainFrameY;
			break;
		}
	}

	for (int i = 0; i < TILEX * TILEY; i++)
	{
		RECT _rc;
		_rc = { 50, 50, M_TILESIZE * 8 + 50, M_TILESIZE * 8 + 50 };
		if (!PtInRect(&_rc, _ptMouse)) continue;
		if (PtInRect(&_tiles[i].rc, _ptMouse))
		{
			if (mouse_state == SELECTTILE)
			{
				if (!forestCheck(i))
				{
					_tiles[i].forestTileFrameX = 0;
					_tiles[i].forestTileFrameY = _currentTile.y;

					_tiles[i].forestExist = true;
					_tiles[i]._state = FORESTTILE;
				}
				else if (!stoneCheck(i))
				{
					_tiles[i].stoneTileFrameX = 0;
					_tiles[i].stoneTileFrameY = _currentTile.y;

					_tiles[i].stoneExist = true;
					_tiles[i]._state = STONETILE;
				}
				else
				{
					objCheck(i);
				}

				_index = i;
			}

			else if (mouse_state == ERESETILE)
			{
				_tiles[i].backTileFrameX = 0;
				_tiles[i].backTileFrameY = 0;

				_tiles[i].forestTileFrameX = 0;
				_tiles[i].forestTileFrameY = 0;

				_tiles[i].stoneTileFrameX = 0;
				_tiles[i].stoneTileFrameY = 0;

				_tiles[i].forestExist = false;
				_tiles[i].stoneExist = false;

				_tiles[i]._state = GRASSTILE;
				_tiles[i]._objstate = NONE_ENVIRONMENT;
			}

		}
	}
}

void MaptoolScene::save()
{
	HANDLE file;
	DWORD write;
	file = CreateFile(L"tileMap.map",
		GENERIC_WRITE,
		0,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL);


	WriteFile(file, _tiles, sizeof(S_TILE) * TILEX * TILEY, &write, NULL);
	CloseHandle(file);
}

void MaptoolScene::load()
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

	ReadFile(file, _tiles, sizeof(S_TILE) * TILEX * TILEY, &read, NULL);
	CloseHandle(file);
}

bool MaptoolScene::forestCheck(int i)
{

	{

		if (_currentTile.x != 0) return true;

		//�»��(ok)
		if (_currentTile.y == 8)
		{
			//����� �̹� ����ִٸ�
			if (_tiles[i].forestTileFrameY == 4) return true;
			//������ �̹� ����ִٸ�
			if (_tiles[i].forestTileFrameY == 1) return true;
			//�»���� �̹� ��ȴٸ�
			if (_tiles[i].forestTileFrameY == 8) return true;


			//������ �������
			if (_tiles[i].forestTileFrameY == 7)
			{
				//���ܸ� ������
				if (_tiles[i].forestTileFrameX == 0)
				{
					_tiles[i].forestTileFrameX = 1;
					_tiles[i].forestTileFrameY = 8;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}

				//���ܰ� ���ϴ��� ������
				else if (_tiles[i].forestTileFrameX == 4)
				{
					_tiles[i].forestTileFrameX = 5;
					_tiles[i].forestTileFrameY = 8;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}

				//���ܰ� ���ϴ��� ������
				else if (_tiles[i].forestTileFrameX == 2)
				{
					_tiles[i].forestTileFrameX = 6;
					_tiles[i].forestTileFrameY = 8;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}

				//���ܰ� �ϴܱ��� ������
				else if (_tiles[i].forestTileFrameX == 9) //8, �ٲ�
				{
					_tiles[i].forestTileFrameX = 11;
					_tiles[i].forestTileFrameY = 8;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}

				//��� �������� ������
				else if (_tiles[i].forestTileFrameX == 7) //6, �ٲ�
				{
					_tiles[i].forestTileFrameX = 8;
					_tiles[i].forestTileFrameY = 8;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}

			}

			//���ϴ��� �������
			if (_tiles[i].forestTileFrameY == 6)
			{
				//���ϴܸ� ������
				if (_tiles[i].forestTileFrameX == 0)
				{
					_tiles[i].forestTileFrameX = 4;
					_tiles[i].forestTileFrameY = 8;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}
				//���ϴܰ� ���ϴ��� ������
				else if (_tiles[i].forestTileFrameX == 1)
				{
					_tiles[i].forestTileFrameX = 3;
					_tiles[i].forestTileFrameY = 8;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}
				//���ϴܰ� ������ ������
				else if (_tiles[i].forestTileFrameX == 2)
				{
					_tiles[i].forestTileFrameX = 6;
					_tiles[i].forestTileFrameY = 8;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}

				//��� �������� ������
				else if (_tiles[i].forestTileFrameX == 6)
				{
					_tiles[i].forestTileFrameX = 8;
					_tiles[i].forestTileFrameY = 8;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}
			}

			//���ϴ��� �������
			if (_tiles[i].forestTileFrameY == 5)
			{
				//���ϴܸ� ������

				//���ϴܰ� ���ϴ��� ������
				if (_tiles[i].forestTileFrameX == 1)
				{
					_tiles[i].forestTileFrameX = 3;
					_tiles[i].forestTileFrameY = 8;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}
				//���ϴܰ� ������ ������
				else if (_tiles[i].forestTileFrameX == 4)
				{
					_tiles[i].forestTileFrameX = 5;
					_tiles[i].forestTileFrameY = 8;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}
				//���ϴܰ� ������ ������
				else if (_tiles[i].forestTileFrameX == 8)
				{
					_tiles[i].forestTileFrameX = 10;
					_tiles[i].forestTileFrameY = 8;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}

				//��� �������� ������
				else if (_tiles[i].forestTileFrameX == 6)
				{
					_tiles[i].forestTileFrameX = 8;
					_tiles[i].forestTileFrameY = 8;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}
				else
				{
					_tiles[i].forestTileFrameX = 2;
					_tiles[i].forestTileFrameY = 8;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}

			}

			//������ ����ִ�
			if (_tiles[i].forestTileFrameY == 2)
			{
				//�ϴܵ� ����ִ�
				if (_tiles[i].forestTileFrameX == 1)
				{
					_tiles[i].forestTileFrameX = 13;
					_tiles[i].forestTileFrameY = 8;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}
				//���ϴܵ� ����ִ�
				else if (_tiles[i].forestTileFrameX == 4)
				{
					_tiles[i].forestTileFrameX = 10;
					_tiles[i].forestTileFrameY = 8;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}
				//������ ��ȴ�
				else
				{
					_tiles[i].forestTileFrameX = 8;
					_tiles[i].forestTileFrameY = 8;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}
			}

			//�ϴ��� �������
			if (_tiles[i].forestTileFrameY == 3)
			{
				//������ ��ȴ�
				if (_tiles[i].forestTileFrameX == 1)
				{
					_tiles[i].forestTileFrameX = 12;
					_tiles[i].forestTileFrameY = 8;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}
				//���ܵ� ��ȴ�
				else if (_tiles[i].forestTileFrameX == 5)
				{
					_tiles[i].forestTileFrameX = 11;
					_tiles[i].forestTileFrameY = 8;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}
				//�ϴܸ� �ִ�
				else
				{
					_tiles[i].forestTileFrameX = 9;
					_tiles[i].forestTileFrameY = 8;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}
			}

			else
			{
				_tiles[i].forestTileFrameX = 0;
				_tiles[i].forestTileFrameY = 8;
				_tiles[i]._state = FORESTTILE;
				_tiles[i].forestExist = true;
			}
		}

		//���� p == x && k == y + _yEnd - 1
		else if (_currentTile.y == 7)
		{
			//����� �̹� ����ִٸ�
			if (_tiles[i].forestTileFrameY == 4) return true;
			//������ �̹� ����ִٸ�
			if (_tiles[i].forestTileFrameY == 2) return true;
			//������ �̹� ��ȴٸ�
			if (_tiles[i].forestTileFrameY == 7) return true;


			//�»���� ������
			if (_tiles[i].forestTileFrameY == 8)
			{
				//���ϴܵ� ������
				if (_tiles[i].forestTileFrameX == 4)
				{
					_tiles[i].forestTileFrameX = 3;
					_tiles[i].forestTileFrameY = 7;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}

				//���ϴܵ� ������
				else if (_tiles[i].forestTileFrameX == 2)
				{
					_tiles[i].forestTileFrameX = 5;
					_tiles[i].forestTileFrameY = 7;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}
				//��� ������
				else if (_tiles[i].forestTileFrameX == 3)
				{
					_tiles[i].forestTileFrameX = 7;
					_tiles[i].forestTileFrameY = 7;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}
				//�»�� �� ������
				else if (_tiles[i].forestTileFrameX == 0)
				{
					_tiles[i].forestTileFrameX = 1;
					_tiles[i].forestTileFrameY = 7;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}
			}

			//���ϴ��� ������
			else if (_tiles[i].forestTileFrameY == 6)
			{
				//�»�ܵ� ������
				if (_tiles[i].forestTileFrameX == 4)
				{
					_tiles[i].forestTileFrameX = 3;
					_tiles[i].forestTileFrameY = 7;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}
				//���ϴܵ� ������
				else if (_tiles[i].forestTileFrameX == 1)
				{
					_tiles[i].forestTileFrameX = 6;
					_tiles[i].forestTileFrameY = 7;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}
				//��� ������
				else if (_tiles[i].forestTileFrameX == 3)
				{
					_tiles[i].forestTileFrameX = 7;
					_tiles[i].forestTileFrameY = 7;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}

				//���ϴܸ� ������
				else if (_tiles[i].forestTileFrameX == 0)
				{
					_tiles[i].forestTileFrameX = 2;
					_tiles[i].forestTileFrameY = 7;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}
			}

			//���ϴ��� ������
			else if (_tiles[i].forestTileFrameY == 5)
			{
				//���ϴܵ� ������
				if (_tiles[i].forestTileFrameX == 1)
				{
					_tiles[i].forestTileFrameX = 6;
					_tiles[i].forestTileFrameY = 7;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}
				//�»�ܵ� ������
				else 	if (_tiles[i].forestTileFrameX == 2)
				{
					_tiles[i].forestTileFrameX = 5;
					_tiles[i].forestTileFrameY = 7;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}
				//��� ������
				else 	if (_tiles[i].forestTileFrameX == 3)
				{
					_tiles[i].forestTileFrameX = 7;
					_tiles[i].forestTileFrameY = 7;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}
				//���ϴܸ� ������
				else 	if (_tiles[i].forestTileFrameX == 0)
				{
					_tiles[i].forestTileFrameX = 4;
					_tiles[i].forestTileFrameY = 7;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}
			}

			//������ ������
			else if (_tiles[i].forestTileFrameY == 1)
			{
				//�ϴܵ� ������
				if (_tiles[i].forestTileFrameX == 1)
				{
					_tiles[i].forestTileFrameX = 12;
					_tiles[i].forestTileFrameY = 7;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}

				//���ϴܵ� ������
				else if (_tiles[i].forestTileFrameX == 4)
				{
					_tiles[i].forestTileFrameX = 10;
					_tiles[i].forestTileFrameY = 7;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}
				//������ ������
				else if (_tiles[i].forestTileFrameX == 0)
				{
					_tiles[i].forestTileFrameX = 8;
					_tiles[i].forestTileFrameY = 7;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}
			}

			//�ϴ��� ������
			else if (_tiles[i].forestTileFrameY == 3)
			{
				//������ ������
				if (_tiles[i].forestTileFrameX == 2)
				{
					_tiles[i].forestTileFrameX = 12;
					_tiles[i].forestTileFrameY = 7;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}
				//�»� ������
				else if (_tiles[i].forestTileFrameX == 4)
				{
					_tiles[i].forestTileFrameX = 11;
					_tiles[i].forestTileFrameY = 7;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}
				//�ϴܸ� ������
				else if (_tiles[i].forestTileFrameX == 0)
				{
					_tiles[i].forestTileFrameX = 9;
					_tiles[i].forestTileFrameY = 7;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}
			}
			else
			{
				_tiles[i].forestTileFrameX = 0;
				_tiles[i].forestTileFrameY = 7;
				_tiles[i]._state = FORESTTILE;
				_tiles[i].forestExist = true;
			}
		}

		//���ϴ� p == x + _xEnd - 1 && k == y
		else if (_currentTile.y == 5)
		{
			//�ϴ��� �̹� ����ִٸ�
			if (_tiles[i].forestTileFrameY == 3) return true;
			//������ �̹� ����ִٸ�
			if (_tiles[i].forestTileFrameY == 1) return true;
			//���ϴ��� �̹� ��ȴٸ�
			if (_tiles[i].forestTileFrameY == 5) return true;



			//�»���� ������
			if (_tiles[i].forestTileFrameY == 8)
			{
				//���ϴܵ� ������
				if (_tiles[i].forestTileFrameX == 4)
				{
					_tiles[i].forestTileFrameX = 3;
					_tiles[i].forestTileFrameY = 5;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}

				//���ܵ� ������
				else if (_tiles[i].forestTileFrameX == 1)
				{
					_tiles[i].forestTileFrameX = 5;
					_tiles[i].forestTileFrameY = 5;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}
				//��� ������
				else if (_tiles[i].forestTileFrameX == 6)
				{
					_tiles[i].forestTileFrameX = 7;
					_tiles[i].forestTileFrameY = 5;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}
				//�»�� �� ������
				else if (_tiles[i].forestTileFrameX == 0)
				{
					_tiles[i].forestTileFrameX = 2;
					_tiles[i].forestTileFrameY = 5;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}
			}

			//���ϴ��� ������
			else if (_tiles[i].forestTileFrameY == 6)
			{
				//�»�ܵ� ������
				if (_tiles[i].forestTileFrameX == 4)
				{
					_tiles[i].forestTileFrameX = 3;
					_tiles[i].forestTileFrameY = 5;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}
				//���ܵ� ������
				else if (_tiles[i].forestTileFrameX == 2)
				{
					_tiles[i].forestTileFrameX = 6;
					_tiles[i].forestTileFrameY = 5;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}
				//��� ������
				else if (_tiles[i].forestTileFrameX == 5)
				{
					_tiles[i].forestTileFrameX = 7;
					_tiles[i].forestTileFrameY = 5;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}

				//���ϴܸ� ������
				else if (_tiles[i].forestTileFrameX == 0)
				{
					_tiles[i].forestTileFrameX = 1;
					_tiles[i].forestTileFrameY = 5;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}
			}

			//������ ������
			else if (_tiles[i].forestTileFrameY == 7)
			{
				//���ϴܵ� ������
				if (_tiles[i].forestTileFrameX == 2)
				{
					_tiles[i].forestTileFrameX = 6;
					_tiles[i].forestTileFrameY = 5;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}
				//�»�ܵ� ������
				else 	if (_tiles[i].forestTileFrameX == 1)
				{
					_tiles[i].forestTileFrameX = 5;
					_tiles[i].forestTileFrameY = 5;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}
				//��� ������
				else 	if (_tiles[i].forestTileFrameX == 3)
				{
					_tiles[i].forestTileFrameX = 7;
					_tiles[i].forestTileFrameY = 5;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}
				//���ܸ� ������
				else 	if (_tiles[i].forestTileFrameX == 0)
				{
					_tiles[i].forestTileFrameX = 4;
					_tiles[i].forestTileFrameY = 5;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}
			}

			//������ ������
			else if (_tiles[i].forestTileFrameY == 2)
			{
				//��ܵ� ������
				if (_tiles[i].forestTileFrameX == 2)
				{
					_tiles[i].forestTileFrameX = 12;
					_tiles[i].forestTileFrameY = 5;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}

				//�»�ܵ� ������
				else if (_tiles[i].forestTileFrameX == 5)
				{
					_tiles[i].forestTileFrameX = 10;
					_tiles[i].forestTileFrameY = 5;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}
				//������ ������
				else if (_tiles[i].forestTileFrameX == 0)
				{
					_tiles[i].forestTileFrameX = 8;
					_tiles[i].forestTileFrameY = 5;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}
			}

			//����� ������
			else if (_tiles[i].forestTileFrameY == 4)
			{
				//������ ������
				if (_tiles[i].forestTileFrameX == 1)
				{
					_tiles[i].forestTileFrameX = 12;
					_tiles[i].forestTileFrameY = 5;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}
				//���ϴܵ� ������
				else if (_tiles[i].forestTileFrameX == 4)
				{
					_tiles[i].forestTileFrameX = 11;
					_tiles[i].forestTileFrameY = 5;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}
				//��ܸ� ������
				else if (_tiles[i].forestTileFrameX == 0)
				{
					_tiles[i].forestTileFrameX = 9;
					_tiles[i].forestTileFrameY = 5;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}

			}

			else {
				_tiles[i].forestTileFrameX = 0;
				_tiles[i].forestTileFrameY = 5;
				_tiles[i]._state = FORESTTILE;
				_tiles[i].forestExist = true;
			}
		}

		//���ϴ�(ok)
		else if (_currentTile.y == 6)
		{
			//�ϴ��� �̹� ����ִٸ�
			if (_tiles[i].forestTileFrameY == 3) return true;
			//������ �̹� ����ִٸ�
			if (_tiles[i].forestTileFrameY == 2) return true;
			//���ϴ��� �̹� ��ȴٸ� 
			if (_tiles[i].forestTileFrameY == 6) return true;


			//�»���� ������
			if (_tiles[i].forestTileFrameY == 8)
			{
				//���ϴܵ� ������
				if (_tiles[i].forestTileFrameX == 2)
				{
					_tiles[i].forestTileFrameX = 3;
					_tiles[i].forestTileFrameY = 6;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}

				//���ܵ� ������
				else if (_tiles[i].forestTileFrameX == 1)
				{
					_tiles[i].forestTileFrameX = 5;
					_tiles[i].forestTileFrameY = 6;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}
				//��� ������
				else if (_tiles[i].forestTileFrameX == 6)
				{
					_tiles[i].forestTileFrameX = 7;
					_tiles[i].forestTileFrameY = 6;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}
				//�»�� �� ������
				else if (_tiles[i].forestTileFrameX == 0)
				{
					_tiles[i].forestTileFrameX = 4;
					_tiles[i].forestTileFrameY = 6;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}
			}

			//���ϴ��� ������
			else if (_tiles[i].forestTileFrameY == 5)
			{
				//���ܵ� ������
				if (_tiles[i].forestTileFrameX == 4)
				{
					_tiles[i].forestTileFrameX = 6;
					_tiles[i].forestTileFrameY = 6;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}
				//�»�ܵ� ������
				else 	if (_tiles[i].forestTileFrameX == 2)
				{
					_tiles[i].forestTileFrameX = 3;
					_tiles[i].forestTileFrameY = 6;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}
				//��� ������
				else 	if (_tiles[i].forestTileFrameX == 5)
				{
					_tiles[i].forestTileFrameX = 7;
					_tiles[i].forestTileFrameY = 6;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}
				//���ϴܸ� ������
				else 	if (_tiles[i].forestTileFrameX == 0)
				{
					_tiles[i].forestTileFrameX = 1;
					_tiles[i].forestTileFrameY = 6;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}
			}


			//������ ������
			else if (_tiles[i].forestTileFrameY == 7)
			{
				//���ϴܵ� ������
				if (_tiles[i].forestTileFrameX == 4)
				{
					_tiles[i].forestTileFrameX = 6;
					_tiles[i].forestTileFrameY = 6;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}
				//�»�ܵ� ������
				else 	if (_tiles[i].forestTileFrameX == 1)
				{
					_tiles[i].forestTileFrameX = 5;
					_tiles[i].forestTileFrameY = 6;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}
				//��� ������
				else 	if (_tiles[i].forestTileFrameX == 5)
				{
					_tiles[i].forestTileFrameX = 7;
					_tiles[i].forestTileFrameY = 6;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}
				//���ܸ� ������
				else 	if (_tiles[i].forestTileFrameX == 0)
				{
					_tiles[i].forestTileFrameX = 2;
					_tiles[i].forestTileFrameY = 6;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}
			}

			//������ ������
			else if (_tiles[i].forestTileFrameY == 1)
			{
				//��ܵ� ������
				if (_tiles[i].forestTileFrameX == 2)
				{
					_tiles[i].forestTileFrameX = 12;
					_tiles[i].forestTileFrameY = 6;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}

				//���ϴܵ� ������
				else if (_tiles[i].forestTileFrameX == 5)
				{
					_tiles[i].forestTileFrameX = 10;
					_tiles[i].forestTileFrameY = 6;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}
				//������ ������
				else if (_tiles[i].forestTileFrameX == 0)
				{
					_tiles[i].forestTileFrameX = 8;
					_tiles[i].forestTileFrameY = 6;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}
			}

			//����� ������
			else if (_tiles[i].forestTileFrameY == 4)
			{
				//������ ������
				if (_tiles[i].forestTileFrameX == 2)
				{
					_tiles[i].forestTileFrameX = 12;
					_tiles[i].forestTileFrameY = 6;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}
				//���ϴܵ� ������
				else if (_tiles[i].forestTileFrameX == 5)
				{
					_tiles[i].forestTileFrameX = 11;
					_tiles[i].forestTileFrameY = 6;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}
				//�ϴܸ� ������
				else if (_tiles[i].forestTileFrameX == 0)
				{
					_tiles[i].forestTileFrameX = 9;
					_tiles[i].forestTileFrameY = 6;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}
			}

			else
			{
				_tiles[i].forestTileFrameX = 0;
				_tiles[i].forestTileFrameY = 6;
				_tiles[i]._state = FORESTTILE;
				_tiles[i].forestExist = true;
			}
		}

		//��� p == x
		else if (_currentTile.y == 4)
		{
			//����� �̹� ����ִٸ�
			if (_tiles[i].forestTileFrameY == 4) return true;


			//������ ������
			if (_tiles[i].forestTileFrameY == 1)
			{
				//������ ������
				if (_tiles[i].forestTileFrameX == 3)
				{
					_tiles[i].forestTileFrameX = 9;
					_tiles[i].forestTileFrameY = 4;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}
				//�ϴܵ� ������
				else if (_tiles[i].forestTileFrameX == 1)
				{
					_tiles[i].forestTileFrameX = 10;
					_tiles[i].forestTileFrameY = 4;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}
				//���ϴܵ� ������
				else if (_tiles[i].forestTileFrameX == 4)
				{
					_tiles[i].forestTileFrameX = 8;
					_tiles[i].forestTileFrameY = 4;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}

				//������ ������
				else if (_tiles[i].forestTileFrameX == 0)
				{
					_tiles[i].forestTileFrameX = 2;
					_tiles[i].forestTileFrameY = 4;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}
			}
			//������ ������
			else if (_tiles[i].forestTileFrameY == 2)
			{
				//������ ������
				if (_tiles[i].forestTileFrameX == 3)
				{
					_tiles[i].forestTileFrameX = 9;
					_tiles[i].forestTileFrameY = 4;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}
				//�ϴܵ� ������
				else if (_tiles[i].forestTileFrameX == 1)
				{
					_tiles[i].forestTileFrameX = 11;
					_tiles[i].forestTileFrameY = 4;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}
				//���ϴܵ� ������
				else if (_tiles[i].forestTileFrameX == 4)
				{
					_tiles[i].forestTileFrameX = 7;
					_tiles[i].forestTileFrameY = 4;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}

				else if (_tiles[i].forestTileFrameX == 0)
				{
					_tiles[i].forestTileFrameX = 1;
					_tiles[i].forestTileFrameY = 4;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}
			}

			//�ϴ��� ������
			else if (_tiles[i].forestTileFrameY == 3)
			{
				//������ ������
				if (_tiles[i].forestTileFrameX == 2)
				{
					_tiles[i].forestTileFrameX = 10;
					_tiles[i].forestTileFrameY = 4;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}
				//������ ������
				else if (_tiles[i].forestTileFrameX == 1)
				{
					_tiles[i].forestTileFrameX = 11;
					_tiles[i].forestTileFrameY = 4;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}
				//�ϴܸ� ������
				else if (_tiles[i].forestTileFrameX == 0)
				{
					_tiles[i].forestTileFrameX = 3;
					_tiles[i].forestTileFrameY = 4;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}
			}

			//���ϴ��� ������
			else if (_tiles[i].forestTileFrameY == 5)
			{
				//������ ������
				if (_tiles[i].forestTileFrameX == 8)
				{
					_tiles[i].forestTileFrameX = 8;
					_tiles[i].forestTileFrameY = 4;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}
				//���ϴܵ� ������
				else if (_tiles[i].forestTileFrameX == 1)
				{
					_tiles[i].forestTileFrameX = 6;
					_tiles[i].forestTileFrameY = 4;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}
				//���ϴܸ� ������
				else if (_tiles[i].forestTileFrameX == 0)
				{
					_tiles[i].forestTileFrameX = 5;
					_tiles[i].forestTileFrameY = 4;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}
			}

			//���ϴ��� ������
			else if (_tiles[i].forestTileFrameY == 6)
			{
				//������ ������
				if (_tiles[i].forestTileFrameX == 8)
				{
					_tiles[i].forestTileFrameX = 8;
					_tiles[i].forestTileFrameY = 4;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}
				//���ϴܵ� ������
				else if (_tiles[i].forestTileFrameX == 1)
				{
					_tiles[i].forestTileFrameX = 6;
					_tiles[i].forestTileFrameY = 4;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}
				//���ϴܸ� ������
				else if (_tiles[i].forestTileFrameX == 0)
				{
					_tiles[i].forestTileFrameX = 4;
					_tiles[i].forestTileFrameY = 4;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}
			}

			else
			{
				_tiles[i].forestTileFrameX = 0;
				_tiles[i].forestTileFrameY = 4;
				_tiles[i]._state = FORESTTILE;
				_tiles[i].forestExist = true;
			}
		}

		//�ϴ� p == x + _xEnd - 1
		else if (_currentTile.y == 3)
		{
			//�ϴ��� �̹� ����ִٸ�
			if (_tiles[i].forestTileFrameY == 3) return true;

			//������ ������
			if (_tiles[i].forestTileFrameY == 1)
			{
				//������ ������
				if (_tiles[i].forestTileFrameX == 3)
				{
					_tiles[i].forestTileFrameX = 9;
					_tiles[i].forestTileFrameY = 3;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}
				//��ܵ� ������
				else if (_tiles[i].forestTileFrameX == 2)
				{
					_tiles[i].forestTileFrameX = 10;
					_tiles[i].forestTileFrameY = 3;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}
				//���ܵ� ������
				else if (_tiles[i].forestTileFrameX == 5)
				{
					_tiles[i].forestTileFrameX = 8;
					_tiles[i].forestTileFrameY = 3;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}

				//������ ������ (Ŀ��� ����)
				else if (_tiles[i].forestTileFrameX == 0)
				{
					_tiles[i].forestTileFrameX = 2;
					_tiles[i].forestTileFrameY = 3;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}
			}

			//������ ������
			else if (_tiles[i].forestTileFrameY == 2)
			{
				//������ ������
				if (_tiles[i].forestTileFrameX == 3)
				{
					_tiles[i].forestTileFrameX = 9;
					_tiles[i].forestTileFrameY = 3;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}
				//��ܵ� ������
				else if (_tiles[i].forestTileFrameX == 2)
				{
					_tiles[i].forestTileFrameX = 11;
					_tiles[i].forestTileFrameY = 3;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}
				//�»�ܵ� ������
				else if (_tiles[i].forestTileFrameX == 5)
				{
					_tiles[i].forestTileFrameX = 7;
					_tiles[i].forestTileFrameY = 3;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}
				//������ ������
				else if (_tiles[i].forestTileFrameX == 0)
				{
					_tiles[i].forestTileFrameX = 1;
					_tiles[i].forestTileFrameY = 3;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}
			}

			//����� ������
			else if (_tiles[i].forestTileFrameY == 4)
			{
				//������ ������
				if (_tiles[i].forestTileFrameX == 2)
				{
					_tiles[i].forestTileFrameX = 10;
					_tiles[i].forestTileFrameY = 3;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}
				//������ ������
				else if (_tiles[i].forestTileFrameX == 1)
				{
					_tiles[i].forestTileFrameX = 11;
					_tiles[i].forestTileFrameY = 3;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}
				//��ܸ� ������
				else if (_tiles[i].forestTileFrameX == 0)
				{
					_tiles[i].forestTileFrameX = 3;
					_tiles[i].forestTileFrameY = 3;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}
			}

			//�»���� ������
			else if (_tiles[i].forestTileFrameY == 8)
			{
				//������ ������
				if (_tiles[i].forestTileFrameX == 8)
				{
					_tiles[i].forestTileFrameX = 7;
					_tiles[i].forestTileFrameY = 3;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}
				//���ܵ� ������
				else if (_tiles[i].forestTileFrameX == 1)
				{
					_tiles[i].forestTileFrameX = 6;
					_tiles[i].forestTileFrameY = 3;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}
				//���ϴܸ� ������
				else if (_tiles[i].forestTileFrameX == 0)
				{
					_tiles[i].forestTileFrameX = 4;
					_tiles[i].forestTileFrameY = 3;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}
			}

			//������ ������
			else if (_tiles[i].forestTileFrameY == 7)
			{
				//������ ������
				if (_tiles[i].forestTileFrameX == 8)
				{
					_tiles[i].forestTileFrameX = 8;
					_tiles[i].forestTileFrameY = 3;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}
				//�»�ܵ� ������
				else if (_tiles[i].forestTileFrameX == 1)
				{
					_tiles[i].forestTileFrameX = 6;
					_tiles[i].forestTileFrameY = 3;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}
				//���ܸ� ������
				else if (_tiles[i].forestTileFrameX == 0)
				{
					_tiles[i].forestTileFrameX = 5;
					_tiles[i].forestTileFrameY = 3;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}
			}

			else
			{
				_tiles[i].forestTileFrameX = 0;
				_tiles[i].forestTileFrameY = 3;
				_tiles[i]._state = FORESTTILE;
				_tiles[i].forestExist = true;
			}
		}

		//���� k == y
		else if (_currentTile.y == 1)
		{
			//������ �̹� ��ȴٸ�
			if (_tiles[i].forestTileFrameY == 1) return true;

			//����� ������
			if (_tiles[i].forestTileFrameY == 4)
			{
				//������ ������
				if (_tiles[i].forestTileFrameX == 1) // ������
				{
					_tiles[i].forestTileFrameX = 11;
					_tiles[i].forestTileFrameY = 1;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}
				//���ϴܵ� ������
				else if (_tiles[i].forestTileFrameX == 4)
				{
					_tiles[i].forestTileFrameX = 8;
					_tiles[i].forestTileFrameY = 1;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}

				//��ܸ� ������
				else if (_tiles[i].forestTileFrameX == 0)
				{
					_tiles[i].forestTileFrameX = 2;
					_tiles[i].forestTileFrameY = 1;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}
			}

			//�ϴ��� ������
			else if (_tiles[i].forestTileFrameY == 3)
			{
				//������ ������
				if (_tiles[i].forestTileFrameX == 1)
				{
					_tiles[i].forestTileFrameX = 10;
					_tiles[i].forestTileFrameY = 1;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}

				//���ܵ� ������
				else if (_tiles[i].forestTileFrameX == 5)
				{
					_tiles[i].forestTileFrameX = 7;
					_tiles[i].forestTileFrameY = 1;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}


				//�ϴܸ� ������
				else if (_tiles[i].forestTileFrameX == 0)
				{
					_tiles[i].forestTileFrameX = 1;
					_tiles[i].forestTileFrameY = 1;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}
			}

			//���ϴ��� ������
			else if (_tiles[i].forestTileFrameY == 6)
			{
				//��ܵ� ������
				if (_tiles[i].forestTileFrameX == 9)
				{
					_tiles[i].forestTileFrameX = 8;
					_tiles[i].forestTileFrameY = 1;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}

				//���ܵ� ������
				else 	if (_tiles[i].forestTileFrameX == 2)
				{
					_tiles[i].forestTileFrameX = 6;
					_tiles[i].forestTileFrameY = 1;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}



				//���ϴܸ� ������
				else if (_tiles[i].forestTileFrameX == 0)
				{
					_tiles[i].forestTileFrameX = 4;
					_tiles[i].forestTileFrameY = 1;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}
			}

			//������ ������
			else if (_tiles[i].forestTileFrameY == 7)
			{
				//�ϴܵ� ������
				if (_tiles[i].forestTileFrameX == 9)
				{
					_tiles[i].forestTileFrameX = 7;
					_tiles[i].forestTileFrameY = 1;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}

				//���ϴܵ� ������
				else 	if (_tiles[i].forestTileFrameX == 2)
				{
					_tiles[i].forestTileFrameX = 6;
					_tiles[i].forestTileFrameY = 1;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}

				//���ܸ� ������
				else if (_tiles[i].forestTileFrameX == 0)
				{
					_tiles[i].forestTileFrameX = 5;
					_tiles[i].forestTileFrameY = 1;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}

			}

			//������ ������
			else if (_tiles[i].forestTileFrameY == 2)
			{
				if (_tiles[i].forestTileFrameX == 0)
				{
					_tiles[i].forestTileFrameX = 3;
					_tiles[i].forestTileFrameY = 1;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;

				}
				else if (_tiles[i].forestTileFrameX == 2)
				{
					_tiles[i].forestTileFrameX = 11;
					_tiles[i].forestTileFrameY = 1;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}
				else if (_tiles[i].forestTileFrameX == 1)
				{
					_tiles[i].forestTileFrameX = 10;
					_tiles[i].forestTileFrameY = 1;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}
			}

			else
			{
				_tiles[i].forestTileFrameX = 0;
				_tiles[i].forestTileFrameY = 1;
				_tiles[i]._state = FORESTTILE;
				_tiles[i].forestExist = true;
			}
		}

		//���� k == y + _yEnd - 1
		else if (_currentTile.y == 2)
		{
			//������ �̹� ��ȴٸ�
			if (_tiles[i].forestTileFrameY == 2) return true;

			//����� ������
			if (_tiles[i].forestTileFrameY == 4)
			{
				//������ ������
				if (_tiles[i].forestTileFrameX == 2)
				{
					_tiles[i].forestTileFrameX = 11;
					_tiles[i].forestTileFrameY = 2;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}
				//���ϴܵ� ������
				else if (_tiles[i].forestTileFrameX == 5)
				{
					_tiles[i].forestTileFrameX = 8;
					_tiles[i].forestTileFrameY = 2;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}

				//��ܸ� ������
				else if (_tiles[i].forestTileFrameX == 0)
				{
					_tiles[i].forestTileFrameX = 2;
					_tiles[i].forestTileFrameY = 2;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}
			}

			//�ϴ��� ������
			else if (_tiles[i].forestTileFrameY == 3)
			{
				//������ ������
				if (_tiles[i].forestTileFrameX == 2)
				{
					_tiles[i].forestTileFrameX = 10;
					_tiles[i].forestTileFrameY = 2;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}

				//�»�ܵ� ������
				else if (_tiles[i].forestTileFrameX == 5)
				{
					_tiles[i].forestTileFrameX = 7;
					_tiles[i].forestTileFrameY = 2;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}


				//�ϴܸ� ������
				else if (_tiles[i].forestTileFrameX == 0)
				{
					_tiles[i].forestTileFrameX = 1;
					_tiles[i].forestTileFrameY = 2;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}
			}

			//���ϴ��� ������
			else if (_tiles[i].forestTileFrameY == 5)
			{
				//��ܵ� ������
				if (_tiles[i].forestTileFrameX == 9)
				{
					_tiles[i].forestTileFrameX = 8;
					_tiles[i].forestTileFrameY = 2;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}

				//�»�ܵ� ������
				else 	if (_tiles[i].forestTileFrameX == 2)
				{
					_tiles[i].forestTileFrameX = 6;
					_tiles[i].forestTileFrameY = 2;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}

				//���ϴܸ� ������
				else if (_tiles[i].forestTileFrameX == 0)
				{
					_tiles[i].forestTileFrameX = 4;
					_tiles[i].forestTileFrameY = 2;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}
			}

			//�»���� ������
			else if (_tiles[i].forestTileFrameY == 8)
			{
				//�ϴܵ� ������5
				if (_tiles[i].forestTileFrameX == 9)
				{
					_tiles[i].forestTileFrameX = 7;
					_tiles[i].forestTileFrameY = 2;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}

				//���ϴܵ� ������
				else 	if (_tiles[i].forestTileFrameX == 2)
				{
					_tiles[i].forestTileFrameX = 6;
					_tiles[i].forestTileFrameY = 2;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}

				//�»�ܸ� ������
				else if (_tiles[i].forestTileFrameX == 0)
				{
					_tiles[i].forestTileFrameX = 5;
					_tiles[i].forestTileFrameY = 2;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}

			}

			//������ ������
			else if (_tiles[i].forestTileFrameY == 1)
			{
				if (_tiles[i].forestTileFrameX == 0)
				{
					_tiles[i].forestTileFrameX = 3;
					_tiles[i].forestTileFrameY = 2;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;


				}
				else if (_tiles[i].forestTileFrameX == 2)
				{
					_tiles[i].forestTileFrameX = 11;
					_tiles[i].forestTileFrameY = 2;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}
				else if (_tiles[i].forestTileFrameX == 1)
				{
					_tiles[i].forestTileFrameX = 10;
					_tiles[i].forestTileFrameY = 2;
					_tiles[i]._state = FORESTTILE;
					_tiles[i].forestExist = true;
				}
			}
			else
			{
				_tiles[i].forestTileFrameX = 0;
				_tiles[i].forestTileFrameY = 2;
				_tiles[i]._state = FORESTTILE;
				_tiles[i].forestExist = true;
			}
		}

		else if (_currentTile.y == 0)
		{
			_tiles[i].forestTileFrameX = 0;
			_tiles[i].forestTileFrameY = 0;
			_tiles[i]._state = FORESTTILE;
			_tiles[i].forestExist = true;
		}
	}
}

bool MaptoolScene::stoneCheck(int i)
{

	{

		if (_currentTile.x != 1) return true;

		//�»��(ok)
		if (_currentTile.y == 8)
		{
			//����� �̹� ����ִٸ�
			if (_tiles[i].stoneTileFrameY == 4) return true;
			//������ �̹� ����ִٸ�
			if (_tiles[i].stoneTileFrameY == 1) return true;
			//�»���� �̹� ��ȴٸ�
			if (_tiles[i].stoneTileFrameY == 8) return true;


			//������ �������
			if (_tiles[i].stoneTileFrameY == 7)
			{
				//���ܸ� ������
				if (_tiles[i].stoneTileFrameX == 0)
				{
					_tiles[i].stoneTileFrameX = 1;
					_tiles[i].stoneTileFrameY = 8;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}

				//���ܰ� ���ϴ��� ������
				else if (_tiles[i].stoneTileFrameX == 4)
				{
					_tiles[i].stoneTileFrameX = 5;
					_tiles[i].stoneTileFrameY = 8;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}

				//���ܰ� ���ϴ��� ������
				else if (_tiles[i].stoneTileFrameX == 2)
				{
					_tiles[i].stoneTileFrameX = 6;
					_tiles[i].stoneTileFrameY = 8;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}

				//���ܰ� �ϴܱ��� ������
				else if (_tiles[i].stoneTileFrameX == 9) //8, �ٲ�
				{
					_tiles[i].stoneTileFrameX = 11;
					_tiles[i].stoneTileFrameY = 8;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}

				//��� �������� ������
				else if (_tiles[i].stoneTileFrameX == 7) //6, �ٲ�
				{
					_tiles[i].stoneTileFrameX = 8;
					_tiles[i].stoneTileFrameY = 8;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}

			}

			//���ϴ��� �������
			if (_tiles[i].stoneTileFrameY == 6)
			{
				//���ϴܸ� ������
				if (_tiles[i].stoneTileFrameX == 0)
				{
					_tiles[i].stoneTileFrameX = 4;
					_tiles[i].stoneTileFrameY = 8;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}
				//���ϴܰ� ���ϴ��� ������
				else if (_tiles[i].stoneTileFrameX == 1)
				{
					_tiles[i].stoneTileFrameX = 3;
					_tiles[i].stoneTileFrameY = 8;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}
				//���ϴܰ� ������ ������
				else if (_tiles[i].stoneTileFrameX == 2)
				{
					_tiles[i].stoneTileFrameX = 6;
					_tiles[i].stoneTileFrameY = 8;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}

				//��� �������� ������
				else if (_tiles[i].stoneTileFrameX == 6)
				{
					_tiles[i].stoneTileFrameX = 8;
					_tiles[i].stoneTileFrameY = 8;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}
			}

			//���ϴ��� �������
			if (_tiles[i].stoneTileFrameY == 5)
			{
				//���ϴܸ� ������

				//���ϴܰ� ���ϴ��� ������
				if (_tiles[i].stoneTileFrameX == 1)
				{
					_tiles[i].stoneTileFrameX = 3;
					_tiles[i].stoneTileFrameY = 8;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}
				//���ϴܰ� ������ ������
				else if (_tiles[i].stoneTileFrameX == 4)
				{
					_tiles[i].stoneTileFrameX = 5;
					_tiles[i].stoneTileFrameY = 8;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}
				//���ϴܰ� ������ ������
				else if (_tiles[i].stoneTileFrameX == 8)
				{
					_tiles[i].stoneTileFrameX = 10;
					_tiles[i].stoneTileFrameY = 8;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}

				//��� �������� ������
				else if (_tiles[i].stoneTileFrameX == 6)
				{
					_tiles[i].stoneTileFrameX = 8;
					_tiles[i].stoneTileFrameY = 8;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}
				else
				{
					_tiles[i].stoneTileFrameX = 2;
					_tiles[i].stoneTileFrameY = 8;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}

			}

			//������ ����ִ�
			if (_tiles[i].stoneTileFrameY == 2)
			{
				//�ϴܵ� ����ִ�
				if (_tiles[i].stoneTileFrameX == 1)
				{
					_tiles[i].stoneTileFrameX = 13;
					_tiles[i].stoneTileFrameY = 8;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}
				//���ϴܵ� ����ִ�
				else if (_tiles[i].stoneTileFrameX == 4)
				{
					_tiles[i].stoneTileFrameX = 10;
					_tiles[i].stoneTileFrameY = 8;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}
				//������ ��ȴ�
				else
				{
					_tiles[i].stoneTileFrameX = 8;
					_tiles[i].stoneTileFrameY = 8;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}
			}

			//�ϴ��� �������
			if (_tiles[i].stoneTileFrameY == 3)
			{
				//������ ��ȴ�
				if (_tiles[i].stoneTileFrameX == 1)
				{
					_tiles[i].stoneTileFrameX = 12;
					_tiles[i].stoneTileFrameY = 8;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}
				//���ܵ� ��ȴ�
				else if (_tiles[i].stoneTileFrameX == 5)
				{
					_tiles[i].stoneTileFrameX = 11;
					_tiles[i].stoneTileFrameY = 8;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}
				//�ϴܸ� �ִ�
				else
				{
					_tiles[i].stoneTileFrameX = 9;
					_tiles[i].stoneTileFrameY = 8;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}
			}

			else
			{
				_tiles[i].stoneTileFrameX = 0;
				_tiles[i].stoneTileFrameY = 8;
				_tiles[i]._state = STONETILE;
				_tiles[i].stoneExist = true;
			}
		}

		//���� p == x && k == y + _yEnd - 1
		else if (_currentTile.y == 7)
		{
			//����� �̹� ����ִٸ�
			if (_tiles[i].stoneTileFrameY == 4) return true;
			//������ �̹� ����ִٸ�
			if (_tiles[i].stoneTileFrameY == 2) return true;
			//������ �̹� ��ȴٸ�
			if (_tiles[i].stoneTileFrameY == 7) return true;


			//�»���� ������
			if (_tiles[i].stoneTileFrameY == 8)
			{
				//���ϴܵ� ������
				if (_tiles[i].stoneTileFrameX == 4)
				{
					_tiles[i].stoneTileFrameX = 3;
					_tiles[i].stoneTileFrameY = 7;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}

				//���ϴܵ� ������
				else if (_tiles[i].stoneTileFrameX == 2)
				{
					_tiles[i].stoneTileFrameX = 5;
					_tiles[i].stoneTileFrameY = 7;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}
				//��� ������
				else if (_tiles[i].stoneTileFrameX == 3)
				{
					_tiles[i].stoneTileFrameX = 7;
					_tiles[i].stoneTileFrameY = 7;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}
				//�»�� �� ������
				else if (_tiles[i].stoneTileFrameX == 0)
				{
					_tiles[i].stoneTileFrameX = 1;
					_tiles[i].stoneTileFrameY = 7;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}
			}

			//���ϴ��� ������
			else if (_tiles[i].stoneTileFrameY == 6)
			{
				//�»�ܵ� ������
				if (_tiles[i].stoneTileFrameX == 4)
				{
					_tiles[i].stoneTileFrameX = 3;
					_tiles[i].stoneTileFrameY = 7;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}
				//���ϴܵ� ������
				else if (_tiles[i].stoneTileFrameX == 1)
				{
					_tiles[i].stoneTileFrameX = 6;
					_tiles[i].stoneTileFrameY = 7;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}
				//��� ������
				else if (_tiles[i].stoneTileFrameX == 3)
				{
					_tiles[i].stoneTileFrameX = 7;
					_tiles[i].stoneTileFrameY = 7;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}

				//���ϴܸ� ������
				else if (_tiles[i].stoneTileFrameX == 0)
				{
					_tiles[i].stoneTileFrameX = 2;
					_tiles[i].stoneTileFrameY = 7;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}
			}

			//���ϴ��� ������
			else if (_tiles[i].stoneTileFrameY == 5)
			{
				//���ϴܵ� ������
				if (_tiles[i].stoneTileFrameX == 1)
				{
					_tiles[i].stoneTileFrameX = 6;
					_tiles[i].stoneTileFrameY = 7;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}
				//�»�ܵ� ������
				else 	if (_tiles[i].stoneTileFrameX == 2)
				{
					_tiles[i].stoneTileFrameX = 5;
					_tiles[i].stoneTileFrameY = 7;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}
				//��� ������
				else 	if (_tiles[i].stoneTileFrameX == 3)
				{
					_tiles[i].stoneTileFrameX = 7;
					_tiles[i].stoneTileFrameY = 7;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}
				//���ϴܸ� ������
				else 	if (_tiles[i].stoneTileFrameX == 0)
				{
					_tiles[i].stoneTileFrameX = 4;
					_tiles[i].stoneTileFrameY = 7;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}
			}

			//������ ������
			else if (_tiles[i].stoneTileFrameY == 1)
			{
				//�ϴܵ� ������
				if (_tiles[i].stoneTileFrameX == 1)
				{
					_tiles[i].stoneTileFrameX = 12;
					_tiles[i].stoneTileFrameY = 7;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}

				//���ϴܵ� ������
				else if (_tiles[i].stoneTileFrameX == 4)
				{
					_tiles[i].stoneTileFrameX = 10;
					_tiles[i].stoneTileFrameY = 7;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}
				//������ ������
				else if (_tiles[i].stoneTileFrameX == 0)
				{
					_tiles[i].stoneTileFrameX = 8;
					_tiles[i].stoneTileFrameY = 7;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}
			}

			//�ϴ��� ������
			else if (_tiles[i].stoneTileFrameY == 3)
			{
				//������ ������
				if (_tiles[i].stoneTileFrameX == 2)
				{
					_tiles[i].stoneTileFrameX = 12;
					_tiles[i].stoneTileFrameY = 7;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}
				//�»� ������
				else if (_tiles[i].stoneTileFrameX == 4)
				{
					_tiles[i].stoneTileFrameX = 11;
					_tiles[i].stoneTileFrameY = 7;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}
				//�ϴܸ� ������
				else if (_tiles[i].stoneTileFrameX == 0)
				{
					_tiles[i].stoneTileFrameX = 9;
					_tiles[i].stoneTileFrameY = 7;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}
			}
			else
			{
				_tiles[i].stoneTileFrameX = 0;
				_tiles[i].stoneTileFrameY = 7;
				_tiles[i]._state = STONETILE;
				_tiles[i].stoneExist = true;
			}
		}

		//���ϴ� p == x + _xEnd - 1 && k == y
		else if (_currentTile.y == 5)
		{
			//�ϴ��� �̹� ����ִٸ�
			if (_tiles[i].stoneTileFrameY == 3) return true;
			//������ �̹� ����ִٸ�
			if (_tiles[i].stoneTileFrameY == 1) return true;
			//���ϴ��� �̹� ��ȴٸ�
			if (_tiles[i].stoneTileFrameY == 5) return true;



			//�»���� ������
			if (_tiles[i].stoneTileFrameY == 8)
			{
				//���ϴܵ� ������
				if (_tiles[i].stoneTileFrameX == 4)
				{
					_tiles[i].stoneTileFrameX = 3;
					_tiles[i].stoneTileFrameY = 5;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}

				//���ܵ� ������
				else if (_tiles[i].stoneTileFrameX == 1)
				{
					_tiles[i].stoneTileFrameX = 5;
					_tiles[i].stoneTileFrameY = 5;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}
				//��� ������
				else if (_tiles[i].stoneTileFrameX == 6)
				{
					_tiles[i].stoneTileFrameX = 7;
					_tiles[i].stoneTileFrameY = 5;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}
				//�»�� �� ������
				else if (_tiles[i].stoneTileFrameX == 0)
				{
					_tiles[i].stoneTileFrameX = 2;
					_tiles[i].stoneTileFrameY = 5;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}
			}

			//���ϴ��� ������
			else if (_tiles[i].stoneTileFrameY == 6)
			{
				//�»�ܵ� ������
				if (_tiles[i].stoneTileFrameX == 4)
				{
					_tiles[i].stoneTileFrameX = 3;
					_tiles[i].stoneTileFrameY = 5;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}
				//���ܵ� ������
				else if (_tiles[i].stoneTileFrameX == 2)
				{
					_tiles[i].stoneTileFrameX = 6;
					_tiles[i].stoneTileFrameY = 5;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}
				//��� ������
				else if (_tiles[i].stoneTileFrameX == 5)
				{
					_tiles[i].stoneTileFrameX = 7;
					_tiles[i].stoneTileFrameY = 5;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}

				//���ϴܸ� ������
				else if (_tiles[i].stoneTileFrameX == 0)
				{
					_tiles[i].stoneTileFrameX = 1;
					_tiles[i].stoneTileFrameY = 5;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}
			}

			//������ ������
			else if (_tiles[i].stoneTileFrameY == 7)
			{
				//���ϴܵ� ������
				if (_tiles[i].stoneTileFrameX == 2)
				{
					_tiles[i].stoneTileFrameX = 6;
					_tiles[i].stoneTileFrameY = 5;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}
				//�»�ܵ� ������
				else 	if (_tiles[i].stoneTileFrameX == 1)
				{
					_tiles[i].stoneTileFrameX = 5;
					_tiles[i].stoneTileFrameY = 5;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}
				//��� ������
				else 	if (_tiles[i].stoneTileFrameX == 3)
				{
					_tiles[i].stoneTileFrameX = 7;
					_tiles[i].stoneTileFrameY = 5;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}
				//���ܸ� ������
				else 	if (_tiles[i].stoneTileFrameX == 0)
				{
					_tiles[i].stoneTileFrameX = 4;
					_tiles[i].stoneTileFrameY = 5;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}
			}

			//������ ������
			else if (_tiles[i].stoneTileFrameY == 2)
			{
				//��ܵ� ������
				if (_tiles[i].stoneTileFrameX == 2)
				{
					_tiles[i].stoneTileFrameX = 12;
					_tiles[i].stoneTileFrameY = 5;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}

				//�»�ܵ� ������
				else if (_tiles[i].stoneTileFrameX == 5)
				{
					_tiles[i].stoneTileFrameX = 10;
					_tiles[i].stoneTileFrameY = 5;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}
				//������ ������
				else if (_tiles[i].stoneTileFrameX == 0)
				{
					_tiles[i].stoneTileFrameX = 8;
					_tiles[i].stoneTileFrameY = 5;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}
			}

			//����� ������
			else if (_tiles[i].stoneTileFrameY == 4)
			{
				//������ ������
				if (_tiles[i].stoneTileFrameX == 1)
				{
					_tiles[i].stoneTileFrameX = 12;
					_tiles[i].stoneTileFrameY = 5;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}
				//���ϴܵ� ������
				else if (_tiles[i].stoneTileFrameX == 4)
				{
					_tiles[i].stoneTileFrameX = 11;
					_tiles[i].stoneTileFrameY = 5;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}
				//��ܸ� ������
				else if (_tiles[i].stoneTileFrameX == 0)
				{
					_tiles[i].stoneTileFrameX = 9;
					_tiles[i].stoneTileFrameY = 5;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}

			}

			else {
				_tiles[i].stoneTileFrameX = 0;
				_tiles[i].stoneTileFrameY = 5;
				_tiles[i]._state = STONETILE;
				_tiles[i].stoneExist = true;
			}
		}

		//���ϴ�(ok)
		else if (_currentTile.y == 6)
		{
			//�ϴ��� �̹� ����ִٸ�
			if (_tiles[i].stoneTileFrameY == 3) return true;
			//������ �̹� ����ִٸ�
			if (_tiles[i].stoneTileFrameY == 2) return true;
			//���ϴ��� �̹� ��ȴٸ� 
			if (_tiles[i].stoneTileFrameY == 6) return true;


			//�»���� ������
			if (_tiles[i].stoneTileFrameY == 8)
			{
				//���ϴܵ� ������
				if (_tiles[i].stoneTileFrameX == 2)
				{
					_tiles[i].stoneTileFrameX = 3;
					_tiles[i].stoneTileFrameY = 6;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}

				//���ܵ� ������
				else if (_tiles[i].stoneTileFrameX == 1)
				{
					_tiles[i].stoneTileFrameX = 5;
					_tiles[i].stoneTileFrameY = 6;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}
				//��� ������
				else if (_tiles[i].stoneTileFrameX == 6)
				{
					_tiles[i].stoneTileFrameX = 7;
					_tiles[i].stoneTileFrameY = 6;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}
				//�»�� �� ������
				else if (_tiles[i].stoneTileFrameX == 0)
				{
					_tiles[i].stoneTileFrameX = 4;
					_tiles[i].stoneTileFrameY = 6;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}
			}

			//���ϴ��� ������
			else if (_tiles[i].stoneTileFrameY == 5)
			{
				//���ܵ� ������
				if (_tiles[i].stoneTileFrameX == 4)
				{
					_tiles[i].stoneTileFrameX = 6;
					_tiles[i].stoneTileFrameY = 6;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}
				//�»�ܵ� ������
				else 	if (_tiles[i].stoneTileFrameX == 2)
				{
					_tiles[i].stoneTileFrameX = 3;
					_tiles[i].stoneTileFrameY = 6;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}
				//��� ������
				else 	if (_tiles[i].stoneTileFrameX == 5)
				{
					_tiles[i].stoneTileFrameX = 7;
					_tiles[i].stoneTileFrameY = 6;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}
				//���ϴܸ� ������
				else 	if (_tiles[i].stoneTileFrameX == 0)
				{
					_tiles[i].stoneTileFrameX = 1;
					_tiles[i].stoneTileFrameY = 6;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}
			}


			//������ ������
			else if (_tiles[i].stoneTileFrameY == 7)
			{
				//���ϴܵ� ������
				if (_tiles[i].stoneTileFrameX == 4)
				{
					_tiles[i].stoneTileFrameX = 6;
					_tiles[i].stoneTileFrameY = 6;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}
				//�»�ܵ� ������
				else 	if (_tiles[i].stoneTileFrameX == 1)
				{
					_tiles[i].stoneTileFrameX = 5;
					_tiles[i].stoneTileFrameY = 6;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}
				//��� ������
				else 	if (_tiles[i].stoneTileFrameX == 5)
				{
					_tiles[i].stoneTileFrameX = 7;
					_tiles[i].stoneTileFrameY = 6;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}
				//���ܸ� ������
				else 	if (_tiles[i].stoneTileFrameX == 0)
				{
					_tiles[i].stoneTileFrameX = 2;
					_tiles[i].stoneTileFrameY = 6;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}
			}

			//������ ������
			else if (_tiles[i].stoneTileFrameY == 1)
			{
				//��ܵ� ������
				if (_tiles[i].stoneTileFrameX == 2)
				{
					_tiles[i].stoneTileFrameX = 12;
					_tiles[i].stoneTileFrameY = 6;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}

				//���ϴܵ� ������
				else if (_tiles[i].stoneTileFrameX == 5)
				{
					_tiles[i].stoneTileFrameX = 10;
					_tiles[i].stoneTileFrameY = 6;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}
				//������ ������
				else if (_tiles[i].stoneTileFrameX == 0)
				{
					_tiles[i].stoneTileFrameX = 8;
					_tiles[i].stoneTileFrameY = 6;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}
			}

			//����� ������
			else if (_tiles[i].stoneTileFrameY == 4)
			{
				//������ ������
				if (_tiles[i].stoneTileFrameX == 2)
				{
					_tiles[i].stoneTileFrameX = 12;
					_tiles[i].stoneTileFrameY = 6;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}
				//���ϴܵ� ������
				else if (_tiles[i].stoneTileFrameX == 5)
				{
					_tiles[i].stoneTileFrameX = 11;
					_tiles[i].stoneTileFrameY = 6;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}
				//�ϴܸ� ������
				else if (_tiles[i].stoneTileFrameX == 0)
				{
					_tiles[i].stoneTileFrameX = 9;
					_tiles[i].stoneTileFrameY = 6;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}
			}

			else
			{
				_tiles[i].stoneTileFrameX = 0;
				_tiles[i].stoneTileFrameY = 6;
				_tiles[i]._state = STONETILE;
				_tiles[i].stoneExist = true;
			}
		}

		//��� p == x
		else if (_currentTile.y == 4)
		{
			//����� �̹� ����ִٸ�
			if (_tiles[i].stoneTileFrameY == 4) return true;


			//������ ������
			if (_tiles[i].stoneTileFrameY == 1)
			{
				//������ ������
				if (_tiles[i].stoneTileFrameX == 3)
				{
					_tiles[i].stoneTileFrameX = 9;
					_tiles[i].stoneTileFrameY = 4;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}
				//�ϴܵ� ������
				else if (_tiles[i].stoneTileFrameX == 1)
				{
					_tiles[i].stoneTileFrameX = 10;
					_tiles[i].stoneTileFrameY = 4;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}
				//���ϴܵ� ������
				else if (_tiles[i].stoneTileFrameX == 4)
				{
					_tiles[i].stoneTileFrameX = 8;
					_tiles[i].stoneTileFrameY = 4;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}

				//������ ������
				else if (_tiles[i].stoneTileFrameX == 0)
				{
					_tiles[i].stoneTileFrameX = 2;
					_tiles[i].stoneTileFrameY = 4;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}
			}
			//������ ������
			else if (_tiles[i].stoneTileFrameY == 2)
			{
				//������ ������
				if (_tiles[i].stoneTileFrameX == 3)
				{
					_tiles[i].stoneTileFrameX = 9;
					_tiles[i].stoneTileFrameY = 4;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}
				//�ϴܵ� ������
				else if (_tiles[i].stoneTileFrameX == 1)
				{
					_tiles[i].stoneTileFrameX = 11;
					_tiles[i].stoneTileFrameY = 4;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}
				//���ϴܵ� ������
				else if (_tiles[i].stoneTileFrameX == 4)
				{
					_tiles[i].stoneTileFrameX = 7;
					_tiles[i].stoneTileFrameY = 4;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}

				else if (_tiles[i].stoneTileFrameX == 0)
				{
					_tiles[i].stoneTileFrameX = 1;
					_tiles[i].stoneTileFrameY = 4;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}
			}

			//�ϴ��� ������
			else if (_tiles[i].stoneTileFrameY == 3)
			{
				//������ ������
				if (_tiles[i].stoneTileFrameX == 2)
				{
					_tiles[i].stoneTileFrameX = 10;
					_tiles[i].stoneTileFrameY = 4;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}
				//������ ������
				else if (_tiles[i].stoneTileFrameX == 1)
				{
					_tiles[i].stoneTileFrameX = 11;
					_tiles[i].stoneTileFrameY = 4;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}
				//�ϴܸ� ������
				else if (_tiles[i].stoneTileFrameX == 0)
				{
					_tiles[i].stoneTileFrameX = 3;
					_tiles[i].stoneTileFrameY = 4;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}
			}

			//���ϴ��� ������
			else if (_tiles[i].stoneTileFrameY == 5)
			{
				//������ ������
				if (_tiles[i].stoneTileFrameX == 8)
				{
					_tiles[i].stoneTileFrameX = 8;
					_tiles[i].stoneTileFrameY = 4;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}
				//���ϴܵ� ������
				else if (_tiles[i].stoneTileFrameX == 1)
				{
					_tiles[i].stoneTileFrameX = 6;
					_tiles[i].stoneTileFrameY = 4;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}
				//���ϴܸ� ������
				else if (_tiles[i].stoneTileFrameX == 0)
				{
					_tiles[i].stoneTileFrameX = 5;
					_tiles[i].stoneTileFrameY = 4;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}
			}

			//���ϴ��� ������
			else if (_tiles[i].stoneTileFrameY == 6)
			{
				//������ ������
				if (_tiles[i].stoneTileFrameX == 8)
				{
					_tiles[i].stoneTileFrameX = 8;
					_tiles[i].stoneTileFrameY = 4;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}
				//���ϴܵ� ������
				else if (_tiles[i].stoneTileFrameX == 1)
				{
					_tiles[i].stoneTileFrameX = 6;
					_tiles[i].stoneTileFrameY = 4;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}
				//���ϴܸ� ������
				else if (_tiles[i].stoneTileFrameX == 0)
				{
					_tiles[i].stoneTileFrameX = 4;
					_tiles[i].stoneTileFrameY = 4;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}
			}

			else
			{
				_tiles[i].stoneTileFrameX = 0;
				_tiles[i].stoneTileFrameY = 4;
				_tiles[i]._state = STONETILE;
				_tiles[i].stoneExist = true;
			}
		}

		//�ϴ� p == x + _xEnd - 1
		else if (_currentTile.y == 3)
		{
			//�ϴ��� �̹� ����ִٸ�
			if (_tiles[i].stoneTileFrameY == 3) return true;

			//������ ������
			if (_tiles[i].stoneTileFrameY == 1)
			{
				//������ ������
				if (_tiles[i].stoneTileFrameX == 3)
				{
					_tiles[i].stoneTileFrameX = 9;
					_tiles[i].stoneTileFrameY = 3;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}
				//��ܵ� ������
				else if (_tiles[i].stoneTileFrameX == 2)
				{
					_tiles[i].stoneTileFrameX = 10;
					_tiles[i].stoneTileFrameY = 3;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}
				//���ܵ� ������
				else if (_tiles[i].stoneTileFrameX == 5)
				{
					_tiles[i].stoneTileFrameX = 8;
					_tiles[i].stoneTileFrameY = 3;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}

				//������ ������ (Ŀ��� ����)
				else if (_tiles[i].stoneTileFrameX == 0)
				{
					_tiles[i].stoneTileFrameX = 2;
					_tiles[i].stoneTileFrameY = 3;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}
			}

			//������ ������
			else if (_tiles[i].stoneTileFrameY == 2)
			{
				//������ ������
				if (_tiles[i].stoneTileFrameX == 3)
				{
					_tiles[i].stoneTileFrameX = 9;
					_tiles[i].stoneTileFrameY = 3;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}
				//��ܵ� ������
				else if (_tiles[i].stoneTileFrameX == 2)
				{
					_tiles[i].stoneTileFrameX = 11;
					_tiles[i].stoneTileFrameY = 3;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}
				//�»�ܵ� ������
				else if (_tiles[i].stoneTileFrameX == 5)
				{
					_tiles[i].stoneTileFrameX = 7;
					_tiles[i].stoneTileFrameY = 3;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}
				//������ ������
				else if (_tiles[i].stoneTileFrameX == 0)
				{
					_tiles[i].stoneTileFrameX = 1;
					_tiles[i].stoneTileFrameY = 3;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}
			}

			//����� ������
			else if (_tiles[i].stoneTileFrameY == 4)
			{
				//������ ������
				if (_tiles[i].stoneTileFrameX == 2)
				{
					_tiles[i].stoneTileFrameX = 10;
					_tiles[i].stoneTileFrameY = 3;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}
				//������ ������
				else if (_tiles[i].stoneTileFrameX == 1)
				{
					_tiles[i].stoneTileFrameX = 11;
					_tiles[i].stoneTileFrameY = 3;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}
				//��ܸ� ������
				else if (_tiles[i].stoneTileFrameX == 0)
				{
					_tiles[i].stoneTileFrameX = 3;
					_tiles[i].stoneTileFrameY = 3;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}
			}

			//�»���� ������
			else if (_tiles[i].stoneTileFrameY == 8)
			{
				//������ ������
				if (_tiles[i].stoneTileFrameX == 8)
				{
					_tiles[i].stoneTileFrameX = 7;
					_tiles[i].stoneTileFrameY = 3;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}
				//���ܵ� ������
				else if (_tiles[i].stoneTileFrameX == 1)
				{
					_tiles[i].stoneTileFrameX = 6;
					_tiles[i].stoneTileFrameY = 3;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}
				//���ϴܸ� ������
				else if (_tiles[i].stoneTileFrameX == 0)
				{
					_tiles[i].stoneTileFrameX = 4;
					_tiles[i].stoneTileFrameY = 3;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}
			}

			//������ ������
			else if (_tiles[i].stoneTileFrameY == 7)
			{
				//������ ������
				if (_tiles[i].stoneTileFrameX == 8)
				{
					_tiles[i].stoneTileFrameX = 8;
					_tiles[i].stoneTileFrameY = 3;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}
				//�»�ܵ� ������
				else if (_tiles[i].stoneTileFrameX == 1)
				{
					_tiles[i].stoneTileFrameX = 6;
					_tiles[i].stoneTileFrameY = 3;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}
				//���ܸ� ������
				else if (_tiles[i].stoneTileFrameX == 0)
				{
					_tiles[i].stoneTileFrameX = 5;
					_tiles[i].stoneTileFrameY = 3;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}
			}

			else
			{
				_tiles[i].stoneTileFrameX = 0;
				_tiles[i].stoneTileFrameY = 3;
				_tiles[i]._state = STONETILE;
				_tiles[i].stoneExist = true;
			}
		}

		//���� k == y
		else if (_currentTile.y == 1)
		{
			//������ �̹� ��ȴٸ�
			if (_tiles[i].stoneTileFrameY == 1) return true;

			//����� ������
			if (_tiles[i].stoneTileFrameY == 4)
			{
				//������ ������
				if (_tiles[i].stoneTileFrameX == 1) // ������
				{
					_tiles[i].stoneTileFrameX = 11;
					_tiles[i].stoneTileFrameY = 1;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}
				//���ϴܵ� ������
				else if (_tiles[i].stoneTileFrameX == 4)
				{
					_tiles[i].stoneTileFrameX = 8;
					_tiles[i].stoneTileFrameY = 1;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}

				//��ܸ� ������
				else if (_tiles[i].stoneTileFrameX == 0)
				{
					_tiles[i].stoneTileFrameX = 2;
					_tiles[i].stoneTileFrameY = 1;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}
			}

			//�ϴ��� ������
			else if (_tiles[i].stoneTileFrameY == 3)
			{
				//������ ������
				if (_tiles[i].stoneTileFrameX == 1)
				{
					_tiles[i].stoneTileFrameX = 10;
					_tiles[i].stoneTileFrameY = 1;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}

				//���ܵ� ������
				else if (_tiles[i].stoneTileFrameX == 5)
				{
					_tiles[i].stoneTileFrameX = 7;
					_tiles[i].stoneTileFrameY = 1;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}


				//�ϴܸ� ������
				else if (_tiles[i].stoneTileFrameX == 0)
				{
					_tiles[i].stoneTileFrameX = 1;
					_tiles[i].stoneTileFrameY = 1;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}
			}

			//���ϴ��� ������
			else if (_tiles[i].stoneTileFrameY == 6)
			{
				//��ܵ� ������
				if (_tiles[i].stoneTileFrameX == 9)
				{
					_tiles[i].stoneTileFrameX = 8;
					_tiles[i].stoneTileFrameY = 1;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}

				//���ܵ� ������
				else 	if (_tiles[i].stoneTileFrameX == 2)
				{
					_tiles[i].stoneTileFrameX = 6;
					_tiles[i].stoneTileFrameY = 1;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}



				//���ϴܸ� ������
				else if (_tiles[i].stoneTileFrameX == 0)
				{
					_tiles[i].stoneTileFrameX = 4;
					_tiles[i].stoneTileFrameY = 1;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}
			}

			//������ ������
			else if (_tiles[i].stoneTileFrameY == 7)
			{
				//�ϴܵ� ������
				if (_tiles[i].stoneTileFrameX == 9)
				{
					_tiles[i].stoneTileFrameX = 7;
					_tiles[i].stoneTileFrameY = 1;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}

				//���ϴܵ� ������
				else 	if (_tiles[i].stoneTileFrameX == 2)
				{
					_tiles[i].stoneTileFrameX = 6;
					_tiles[i].stoneTileFrameY = 1;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}

				//���ܸ� ������
				else if (_tiles[i].stoneTileFrameX == 0)
				{
					_tiles[i].stoneTileFrameX = 5;
					_tiles[i].stoneTileFrameY = 1;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}

			}

			//������ ������
			else if (_tiles[i].stoneTileFrameY == 2)
			{
				if (_tiles[i].stoneTileFrameX == 0)
				{
					_tiles[i].stoneTileFrameX = 3;
					_tiles[i].stoneTileFrameY = 1;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;

				}
				else if (_tiles[i].stoneTileFrameX == 2)
				{
					_tiles[i].stoneTileFrameX = 11;
					_tiles[i].stoneTileFrameY = 1;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}
				else if (_tiles[i].stoneTileFrameX == 1)
				{
					_tiles[i].stoneTileFrameX = 10;
					_tiles[i].stoneTileFrameY = 1;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}
			}

			else
			{
				_tiles[i].stoneTileFrameX = 0;
				_tiles[i].stoneTileFrameY = 1;
				_tiles[i]._state = STONETILE;
				_tiles[i].stoneExist = true;
			}
		}

		//���� k == y + _yEnd - 1
		else if (_currentTile.y == 2)
		{
			//������ �̹� ��ȴٸ�
			if (_tiles[i].stoneTileFrameY == 2) return true;

			//����� ������
			if (_tiles[i].stoneTileFrameY == 4)
			{
				//������ ������
				if (_tiles[i].stoneTileFrameX == 2)
				{
					_tiles[i].stoneTileFrameX = 11;
					_tiles[i].stoneTileFrameY = 2;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}
				//���ϴܵ� ������
				else if (_tiles[i].stoneTileFrameX == 5)
				{
					_tiles[i].stoneTileFrameX = 8;
					_tiles[i].stoneTileFrameY = 2;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}

				//��ܸ� ������
				else if (_tiles[i].stoneTileFrameX == 0)
				{
					_tiles[i].stoneTileFrameX = 2;
					_tiles[i].stoneTileFrameY = 2;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}
			}

			//�ϴ��� ������
			else if (_tiles[i].stoneTileFrameY == 3)
			{
				//������ ������
				if (_tiles[i].stoneTileFrameX == 2)
				{
					_tiles[i].stoneTileFrameX = 10;
					_tiles[i].stoneTileFrameY = 2;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}

				//�»�ܵ� ������
				else if (_tiles[i].stoneTileFrameX == 5)
				{
					_tiles[i].stoneTileFrameX = 7;
					_tiles[i].stoneTileFrameY = 2;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}


				//�ϴܸ� ������
				else if (_tiles[i].stoneTileFrameX == 0)
				{
					_tiles[i].stoneTileFrameX = 1;
					_tiles[i].stoneTileFrameY = 2;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}
			}

			//���ϴ��� ������
			else if (_tiles[i].stoneTileFrameY == 5)
			{
				//��ܵ� ������
				if (_tiles[i].stoneTileFrameX == 9)
				{
					_tiles[i].stoneTileFrameX = 8;
					_tiles[i].stoneTileFrameY = 2;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}

				//�»�ܵ� ������
				else 	if (_tiles[i].stoneTileFrameX == 2)
				{
					_tiles[i].stoneTileFrameX = 6;
					_tiles[i].stoneTileFrameY = 2;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}

				//���ϴܸ� ������
				else if (_tiles[i].stoneTileFrameX == 0)
				{
					_tiles[i].stoneTileFrameX = 4;
					_tiles[i].stoneTileFrameY = 2;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}
			}

			//�»���� ������
			else if (_tiles[i].stoneTileFrameY == 8)
			{
				//�ϴܵ� ������5
				if (_tiles[i].stoneTileFrameX == 9)
				{
					_tiles[i].stoneTileFrameX = 7;
					_tiles[i].stoneTileFrameY = 2;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}

				//���ϴܵ� ������
				else 	if (_tiles[i].stoneTileFrameX == 2)
				{
					_tiles[i].stoneTileFrameX = 6;
					_tiles[i].stoneTileFrameY = 2;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}

				//�»�ܸ� ������
				else if (_tiles[i].stoneTileFrameX == 0)
				{
					_tiles[i].stoneTileFrameX = 5;
					_tiles[i].stoneTileFrameY = 2;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}

			}

			//������ ������
			else if (_tiles[i].stoneTileFrameY == 1)
			{
				if (_tiles[i].stoneTileFrameX == 0)
				{
					_tiles[i].stoneTileFrameX = 3;
					_tiles[i].stoneTileFrameY = 2;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;


				}
				else if (_tiles[i].stoneTileFrameX == 2)
				{
					_tiles[i].stoneTileFrameX = 11;
					_tiles[i].stoneTileFrameY = 2;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}
				else if (_tiles[i].stoneTileFrameX == 1)
				{
					_tiles[i].stoneTileFrameX = 10;
					_tiles[i].stoneTileFrameY = 2;
					_tiles[i]._state = STONETILE;
					_tiles[i].stoneExist = true;
				}
			}
			else
			{
				_tiles[i].stoneTileFrameX = 0;
				_tiles[i].stoneTileFrameY = 2;
				_tiles[i]._state = STONETILE;
				_tiles[i].stoneExist = true;
			}
		}

		else if (_currentTile.y == 0)
		{
			_tiles[i].stoneTileFrameX = 0;
			_tiles[i].stoneTileFrameY = 0;
			_tiles[i]._state = STONETILE;
			_tiles[i].stoneExist = true;
		}
	}
}

void MaptoolScene::objCheck(int i)
{
	if (_currentTile.x != 2) return;

	//�»��(ok)
	if (_currentTile.y == 0)
		_tiles[i]._objstate = FLOWER;
	if (_currentTile.y == 1)
		_tiles[i]._objstate = PLANTCARROT;
	if (_currentTile.y == 2)
		_tiles[i]._objstate = TREE1;
	if (_currentTile.y == 3)
		_tiles[i]._objstate = TREE2;
	if (_currentTile.y == 4)
		_tiles[i]._objstate = RASPBERRYSTACK;
	if (_currentTile.y == 5)
		_tiles[i]._objstate = ROCK;
	if (_currentTile.y == 6)
		_tiles[i]._objstate = HAYSTACK;
};


void MaptoolScene::ereseTile()
{
}

void MaptoolScene::resetTile()
{
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		_tiles[i].backTileFrameX = 0;
		_tiles[i].backTileFrameY = 0;

		_tiles[i].forestTileFrameX = 0;
		_tiles[i].forestTileFrameY = 0;

		_tiles[i].stoneTileFrameX = 0;
		_tiles[i].stoneTileFrameY = 0;

		_tiles[i].forestExist = false;
		_tiles[i].stoneExist = false;

		_tiles[i]._state = GRASSTILE;
		_tiles[i]._objstate = NONE_ENVIRONMENT;
	}
}

void MaptoolScene::minimapUpdate()
{
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		_minimaptiles[i].backTileFrameX = _tiles[i].backTileFrameX;
		_minimaptiles[i].backTileFrameY = _tiles[i].backTileFrameY;

		_minimaptiles[i].forestTileFrameX = _tiles[i].forestTileFrameX;
		_minimaptiles[i].forestTileFrameY = _tiles[i].forestTileFrameY;

		_minimaptiles[i].stoneTileFrameX = _tiles[i].stoneTileFrameX;
		_minimaptiles[i].stoneTileFrameY = _tiles[i].stoneTileFrameY;

		_minimaptiles[i].forestExist = _tiles[i].forestExist;
		_minimaptiles[i].stoneExist = _tiles[i].stoneExist;
		_minimaptiles[i]._state = _tiles[i]._state;
	}
}
