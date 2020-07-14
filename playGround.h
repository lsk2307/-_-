#pragma once
#include "gameNode.h"

struct object
{
	image* img;
	float x, y;
	bool live;
};


class playGround : public gameNode
{
private:
	object _player;
	int _time, _time1;
	RECT _rc[6];
	RECT _pRc;

	RECT _enemyDr;

	object _enemy;

	image* back;

	RECT _map, _mapP, _mapE;
	bool _mapOn;

	int _backX, _backY;
	int _EAD;
	bool _EM, _EI, _EA;
	bool _PIL, _PIR, _PM, _PW, _PA, _PJ , _PB , _RT, _LT;
	int _index;
	int _enemyIndex;
	float _JP, _gravity;

public:
	playGround();
	~playGround();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);


	void playerKEY();
	void enemyMove();
};

