#include "stdafx.h"
#include "playGround.h"


playGround::playGround()
{
}


playGround::~playGround()
{
}
//tset
//초기화 함수
HRESULT playGround::init()
{
	_backX = 2304;
	_backY = 1440;

	gameNode::init(_backX, _backY); //<-- 배경크기설정

	
	_enemy.img = IMAGEMANAGER->addFrameImage("bear", "bear.bmp", 4500, 276, 30, 2, true, RGB(255, 0, 255));
	_player.img = IMAGEMANAGER->addFrameImage("chara", "chara.bmp", 5192, 232, 44, 2, true, RGB(255, 0, 255));

	_time = 0;
	_time1 = 0;

	_rc[0] = RectMakeCenter(_backX / 2, _backY - 50, _backX, 100);
	_rc[1] = RectMakeCenter(_backX / 2 -200, _backY - 200, 100, 200);
	_rc[2] = RectMakeCenter(_backX / 2 + 100, _backY - 250, 100, 300);
	_rc[3] = RectMakeCenter(_backX / 2 , _backY - 500, 200, 50);
	_rc[4] = RectMakeCenter(_backX / 2 - 400, _backY - 600, 200, 50);
	_rc[5] = RectMakeCenter(_backX / 2 + 300, _backY - 600, 200, 50);

	

	_pRc = RectMakeCenter(_player.x + 59, _player.y + 58, 50, 50);
	
	_EAD = 0;
	_player.img->setFrameX(0);
	_player.img->setFrameY(0);

	_enemy.img->setFrameX(8);
	_enemy.img->setFrameY(0);

	_enemy.live = true;

	_player.x = 10;
	_player.y = _backY - 215;

	_map = RectMakeCenter(_player.x + 250, _player.y - 400, _backX / 6, _backY / 6);

	_enemy.x = 1700;
	_enemy.y = _backY - 238;
	_EM = _EI = _EA = false;
	_enemyDr = RectMakeCenter(_enemy.x + 75, _enemy.y + 99, 800, 50);

	_PIR = true;
	_PIL = _PM = _PW = _PA = _PJ = _RT = _LT = false;

	_index = 0;
	_enemyIndex = 0;

	_JP = 0;
	_gravity = 0.1;

	_mapOn = false;

	back = IMAGEMANAGER->addImage("back", "back.bmp", 2304, 1440, false, RGB(0, 0, 0));
	return S_OK;
}

//메모리 해제
void playGround::release()
{
	
}

//연산
void playGround::update()
{
	gameNode::update();


	_time++;
	_time1++;

	_pRc = RectMakeCenter(_player.x + 53, _player.y + 58, 15, 116);

	enemyMove();

	//바닥 초기화
	if (_pRc.bottom > _rc[0].top)
		_player.y = _backY - 216;
		
	//점프 중력
	if (_PJ == true)
	{
		_player.y -= _JP;
		_JP -= _gravity;
		
		if (_pRc.bottom > _rc[0].top)
		{
			_player.y = _backY - 216;
			_PJ = false;
		}	
	}

	
	
	for (int i = 1; i < 6; i++)
	{
		//블럭1
		if (_rc[i].top < _pRc.bottom && _rc[i].left < _pRc.left && _rc[i].right > _pRc.right  && _pRc.bottom < _rc[i].bottom && _pRc.bottom < _rc[i].top +10)
		{
			_PJ = false;
		}
		

		if (_rc[i].left <= _pRc.right && _pRc.bottom > _rc[i].top && _pRc.left + 0.1f < _rc[i].left && _pRc.bottom <= _rc[i].bottom + 70)
		{
			
			
			
			if (_PJ == true && _pRc.top + 50 > _rc[i].top)
			{
				_PW = true;
				_PJ = false;
				_player.img->setFrameX(24);
				_player.img->setFrameY(0);
			}
			_player.x = _rc[i].left - 61;

			
			break;
		}
		else if (_rc[i].right >= _pRc.left && _pRc.bottom > _rc[i].top && _pRc.right > _rc[i].right - 0.1f  && _pRc.bottom <= _rc[i].bottom + 70)
		{
			
			
			if (_PJ == true && _pRc.top + 50 > _rc[i].top)
			{
				_PW = true;
				_PJ = false;
				_player.img->setFrameX(7);
				_player.img->setFrameY(1);
			}
			_player.x = _rc[i].right - 45;

			
			break;
		}
		else if (_rc[i].top <= _pRc.bottom && _rc[i].left < _pRc.right && _rc[i].right > _pRc.left && _PJ == false && _JP < 0 && _pRc.bottom <= _rc[i].top +10)
		{
			_player.y = _rc[i].top - 116;
			_PB = true;
			_JP = 0;
			//_PJ = false;
			break;
		}
	}
	
	//중력
	if (_player.y < _backY - 216 && _PW == false && _PB == false && _PJ == false)
	{
		_player.y -= _JP;
		_JP -= _gravity * 3;		
	}
	
	
	

	if (_player.x < -33)
		_player.x = -33;
	if (_player.x + 116 - 33 > _backX)
		_player.x = _backX - 116 +33;
			
	
	playerKEY();
	

	if (_PA == true)
	{
		if (_PIR == true)
		{
			if (_pRc.left <= _enemy.x && _pRc.right + 10 > _enemy.x)
			{
				_enemy.live = false;
				_enemy.x = -500;
				_enemy.y = -500;
				_EAD = 0;
			}
		}
		else if (_PIL == true)
		{
			if (_pRc.right - 90 >= _enemy.x && _pRc.left - 120 < _enemy.x)
			{
				_enemy.live = false;
				_enemy.x = -500;
				_enemy.y = -500;
				_EAD = 0;
			}
		}
	}

	if (_enemy.live == false && _EAD > 140)
	{
		_enemy.x = 1700;
		_enemy.y = _backY - 238;
		_enemy.live = true;
	}
	
	if (_EA == true)
	{
		if (_EM == true)  //오
		{
			if (_enemy.x + 70 <= _pRc.left && _enemy.x + 170 > _pRc.left && _player.y > _enemy.y)
			{
				_player.x += 40;
			}			
		}
		else if (_EM == false)
		{
			if (_enemy.x +60 >= _pRc.right && _enemy.x - 40 < _pRc.right && _player.y > _enemy.y)
			{
				_player.x -= 40;
			}
		}
	}

	
	if (_player.x > WINSIZEX/2 && _player.y < _backY - WINSIZEY/2 && _player.x < _backX - WINSIZEX/2)
		_map = RectMakeCenter(_player.x - 260, _player.y - 200, _backX / 6, _backY / 6);
	else if(_player.x > WINSIZEX / 2 && _player.y > _backY - WINSIZEY / 2 && _player.x < _backX - WINSIZEX / 2)
		_map = RectMakeCenter(_player.x - 260, _backY - 600, _backX / 6, _backY / 6);
	else if (_player.y >= _backY - WINSIZEY / 2 && _player.x >= _backX - WINSIZEX / 2)
		_map = RectMakeCenter(_backX - 770, _backY - 600, _backX / 6, _backY / 6);
	else 
		_map = RectMakeCenter(250, _backY - 600, _backX / 6, _backY / 6);
	
	_mapP = RectMakeCenter(_map.left + _player.x / 6 + 10, _map.bottom - (_backY - _player.y) / 6, 80 / 6, 116 / 6);
	_mapE = RectMakeCenter(_map.left + _enemy.x / 6 + 10, _map.bottom - (_backY - _enemy.y) / 6 +4, 80 / 6, 116 / 6);
}

//그리기 전용
void playGround::render(HDC hdc)
{
	//백버퍼의 DC영역을 가지고 온다 
	HDC backDC = this->getBackBuffer()->getMemDC();
	PatBlt(backDC, 0, 0, WINSIZEX , WINSIZEY , WHITENESS);
	//=================================================
	back->render(backDC, 0, 0);

	
	for (int i = 0; i < 6; i++)
	{
		Rectangle(backDC, _rc[i]);
	}

	//Rectangle(backDC, _enemyDr);

	if (_enemy.live == true)
	_enemy.img->frameRender(backDC, _enemy.x, _enemy.y, _enemy.img->getFrameX(), _enemy.img->getFrameY());
	_player.img->frameRender(backDC, _player.x, _player.y, _player.img->getFrameX(), _player.img->getFrameY());
	
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		Rectangle(backDC, _map);
		Rectangle(backDC, _mapP);
		Rectangle(backDC, _mapE);

		HBRUSH brush = CreateSolidBrush(RGB(0, 255, 0));
		FillRect(backDC, &_mapP, brush);
		DeleteObject(brush);
		HBRUSH brush1 = CreateSolidBrush(RGB(255, 0, 0));
		FillRect(backDC, &_mapE, brush1);
		DeleteObject(brush1);
	}

	


	//Rectangle(backDC, _pRc);

	//=============================================
	this->getBackBuffer()->render(hdc, _player.x , _player.y , _backX, _backY);  //<--- 캠좌표, 배경크기 설정
}

void playGround::playerKEY()
{
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && _PA == false && _PW == false)
	{
		if ((_PM == false || _PIL == true) && _PJ == false)
		{
			_player.img->setFrameX(12);
			_player.img->setFrameY(0);
			_index = 12;
		}

		_LT = false;
		_PB = false;
		_player.x += 3;

		if (_PJ == false)
		{
			_PIR = true;
			_PIL = false;
			_PM = true;
		}

	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && _PA == false && _PW == false)
	{
		if ((_PM == false || _PIR == true) && _PJ == false)
		{
			_player.img->setFrameX(19);
			_player.img->setFrameY(1);
			_index = 19;
		}

		_RT = false;
		_PB = false;
		_player.x -= 3;
		if (_PJ == false)
		{
			_PIR = false;
			_PIL = true;
			_PM = true;
		}
	}
	if (KEYMANAGER->isOnceKeyUp(VK_RIGHT) && _PA == false && _PW == false)
	{
		if (_PJ == false)
		{
			_PM = false;
			_player.img->setFrameX(0);
			_player.img->setFrameY(0);
			_index = 0;
		}
	}
	if (KEYMANAGER->isOnceKeyUp(VK_LEFT) && _PA == false && _PW == false)
	{
		if (_PJ == false)
		{
			_PM = false;
			_player.img->setFrameX(31);
			_player.img->setFrameY(1);
			_index = 31;
		}
	}

	if (KEYMANAGER->isStayKeyDown(VK_DOWN) && KEYMANAGER->isOnceKeyDown(VK_SPACE) && _PJ == false && _PA == false)
	{
		_player.y += 11;
		_PB = false;
		_JP = 0;
		_PJ = true;
		if (_PIR == true)
		{
			_index = 32;
		}
		else if (_PIL == true)
		{
			_index = 43;
		}
	}
	else if (KEYMANAGER->isOnceKeyDown(VK_SPACE) && _PJ == false && _PA == false)
	{
		_PW = false;
		_PJ = true;
		_PM = false;
		_PB = false;
		_JP = 5;
		if (_PIR == true)
		{
			_index = 32;
		}
		else if (_PIL == true)
		{
			_index = 43;
		}
	}

	if (KEYMANAGER->isOnceKeyDown('A') && _PJ == false && _PA == false && _PW == false)
	{
		_PA = true;
		_PM = false;
		if (_PIR == true)
		{
			_index = 25;
		}
		else if (_PIL == true)
		{
			_index = 6;
		}
	}

	


	//대기
	if (_PIR == true && _time >= 5 && _PM == false && _PJ == false && _PA == false && _PW == false)
	{
		_player.img->setFrameX(_index);
		_player.img->setFrameY(0);
		_index++;
		if (_index >= 12)
			_index = 0;
		_time = 0;
	}
	else if (_PIL == true && _time >= 5 && _PM == false && _PJ == false && _PA == false && _PW == false)
	{
		_player.img->setFrameX(_index);
		_player.img->setFrameY(1);
		_index--;
		if (_index <= 19)
			_index = 31;
		_time = 0;
	}
	//이동
	else if (_PIR == true && _time >= 5 && _PM == true && _PJ == false && _PA == false)
	{
		_player.img->setFrameX(_index);
		_player.img->setFrameY(0);
		_index++;
		if (_index >= 24)
			_index = 12;
		_time = 0;
	}
	else if (_PIL == true && _time >= 5 && _PM == true && _PJ == false && _PA == false)
	{
		_player.img->setFrameX(_index);
		_player.img->setFrameY(1);
		_index--;
		if (_index <= 7)
			_index = 19;
		_time = 0;
	}
	//점프
	else if (_PIR == true && _time >= 5 && _PJ == true && _PA == false)
	{
		_player.img->setFrameX(_index);
		_player.img->setFrameY(0);
		_index++;
		if (_index >= 44)
			_index = 43;
		_time = 0;
	}
	else if (_PIL == true && _time >= 5 && _PJ == true && _PA == false)
	{
		_player.img->setFrameX(_index);
		_player.img->setFrameY(1);
		_index--;
		if (_index <= 31)
			_index = 32;
		_time = 0;
	}
	//공격
	else if (_PIR == true && _time >= 5 && _PA == true)
	{
		_player.img->setFrameX(_index);
		_player.img->setFrameY(0);
		_index++;
		if (_index >= 32)
		{
			_PA = false;
			_index = 0;
		}
		_time = 0;
	}
	else if (_PIL == true && _time >= 5 && _PA == true)
	{
		_player.img->setFrameX(_index);
		_player.img->setFrameY(1);
		_index--;
		if (_index < 0)
		{
			_index = 31;
			_PA = false;
		}

		_time = 0;
	}
}

void playGround::enemyMove()
{
	_EAD++;

	if (_player.x > _enemyDr.left && _player.x < _enemyDr.right - 70 && _EA == false && _EAD >= 148)
	{
		if (_player.x <= _enemy.x)
		{
			_EM = false;
			_EI = false;
			_enemyIndex = 20; 
			_enemy.img->setFrameX(20);
			_enemy.img->setFrameY(0);

			_EA = true;
		}
		else if (_player.x > _enemy.x)
		{
			_EM = true;
			_EI = false;
			_enemyIndex = 9;
			_enemy.img->setFrameX(9);
			_enemy.img->setFrameY(1);

			_EA = true;
		}
		_EAD = 0;
	}


	if (_EM == false && _EI == false && _EA == false)
	{
		_enemy.x -= 3;

		if (_time1 >= 5)
		{
			_enemy.img->setFrameX(_enemyIndex);
			_enemyIndex++;
			if (_enemyIndex >= 20)
				_enemyIndex = 8;
			_time1 = 0;

		}

		if (_enemy.x <= _enemyDr.left)
		{
			_EM = true;
			_EI = true;
			_enemyIndex = 0;
		}
	}
	else if (_EM == true && _EI == false && _EA == false)
	{
		_enemy.x += 3;

		if (_time1 >= 5)
		{
			_enemy.img->setFrameX(_enemyIndex);
			_enemyIndex--;
			if (_enemyIndex <= 9)
				_enemyIndex = 21;
			_time1 = 0;

		}

		if (_enemy.x >= _enemyDr.right - 150)
		{
			_EM = false;
			_EI = true;
			_enemyIndex = 29;
		}
	}
	else if (_EM == false && _EI == true && _EA == false)
	{
		if (_time1 >= 5)
		{
			_enemy.img->setFrameX(_enemyIndex);
			_enemyIndex--;
			if (_enemyIndex <= 21)
			{
				_enemyIndex = 8;
				_enemy.img->setFrameX(8);
				_enemy.img->setFrameY(0);
				_EI = false;
			}

			_time1 = 0;
		}		
	}
	else if (_EM == true && _EI == true && _EA == false)
	{	
		if (_time1 >= 5)
		{
			_enemy.img->setFrameX(_enemyIndex);
			_enemyIndex++;
			if (_enemyIndex >= 8)
			{
				_enemyIndex = 21;
				_enemy.img->setFrameX(21);
				_enemy.img->setFrameY(1);
				_EI = false;
			}
			_time1 = 0;
		}
	}
	else if (_EM == false && _EA == true)
	{
		if (_time1 >= 5)
		{
			_enemy.img->setFrameX(_enemyIndex);
			_enemyIndex++;
			if (_enemyIndex >= 30)
			{ 
				_enemyIndex = 8;
				_enemy.img->setFrameX(8);
				_EA = false;
			}
			_time1 = 0;

		}
	}
	else if (_EM == true && _EA == true)
	{

		if (_time1 >= 5)
		{
			_enemy.img->setFrameX(_enemyIndex);
			_enemyIndex--;
			if (_enemyIndex <= -1)
			{
				_enemyIndex = 21;
				_enemy.img->setFrameX(21);
				_EA = false;
			}
			_time1 = 0;

		}
	}
}
