#include "stdafx.h"
#include "gameNode.h"


void gameNode::setBackBuffer()
{
	_backBuffer = new image;
	_backBuffer->init(WINSIZEX, WINSIZEY);
}

void gameNode::setBackBuffer(int _destX, int _destY)
{
	_backBuffer = new image;
	_backBuffer->init(_destX, _destY);
}

gameNode::gameNode()
{
}


gameNode::~gameNode()
{
}

HRESULT gameNode::init()
{
	SetTimer(_hWnd, 1, 10, NULL);
	KEYMANAGER->init();
	IMAGEMANAGER->init();
	
	setBackBuffer();

	return S_OK;
}


HRESULT gameNode::init(int _destX, int _destY)
{
	SetTimer(_hWnd, 1, 10, NULL);
	KEYMANAGER->init();
	IMAGEMANAGER->init();

	setBackBuffer(_destX, _destY);

	return S_OK;
}

void gameNode::release()
{
	KillTimer(_hWnd, 1);

	KEYMANAGER->release();
	KEYMANAGER->releaseSingleton();

	IMAGEMANAGER->release();
	IMAGEMANAGER->releaseSingleton();
}

void gameNode::update()
{
	InvalidateRect(_hWnd, NULL, false);
}

void gameNode::render(HDC hdc)
{
}


LRESULT gameNode::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	//HWND - 핸들메시지
	//UINT - 메시지 발생 번호
	//WPARAM - 키보드 입력 및 마우스 클릭 메시지 전달
	//LPARAM - 마우스 좌표 전달

	PAINTSTRUCT ps;
	HDC			hdc;

	switch (iMessage)
	{
		case WM_TIMER:
			this->update();
		break;
		case WM_PAINT:
		{
			hdc = BeginPaint(hWnd, &ps);

			this->render(hdc);

			EndPaint(hWnd, &ps);
		}
		break;
		case WM_MOUSEMOVE:
			_ptMouse.x = static_cast<float>(LOWORD(lParam));
			_ptMouse.y = static_cast<float>(HIWORD(lParam));
		break;

		case WM_KEYDOWN:
		{
			switch (wParam)
			{
				case VK_ESCAPE:
					PostQuitMessage(0);
				break;

			}
		}
		break;

		case WM_DESTROY:
			PostQuitMessage(0);
		break;
	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}
