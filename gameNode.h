#pragma once
#include "image.h"

class gameNode
{
private:
	image* _backBuffer;
	void setBackBuffer();
	void setBackBuffer(int _destX, int _destY);

public:
	gameNode();
	virtual ~gameNode();

	//HRESULT�� ����ũ�μ���Ʈ ���� ����� ��ȯ�� �ε�
	//S_OK, E_FAIL, SUCCDED ������ ���â�� 
	//����� �ʱ�ȭ�� �ߵƴ��� �ƴ����� �����ش�
	virtual HRESULT init();			//�ʱ�ȭ ���� �Լ�
	virtual void release();			//�޸� ���� ����
	virtual void update();			//���� ����
	virtual void render(HDC hdc);	//�׸��� ����

	//���ũ��X, ���ũ��Y
	virtual HRESULT init(int _destX, int _destY);

	//����� ������
	image* getBackBuffer() { return _backBuffer; }

	LRESULT MainProc(HWND, UINT, WPARAM, LPARAM);
};

