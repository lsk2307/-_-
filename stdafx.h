#pragma once
#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>

// C 런타임 헤더 파일입니다.
#include <iostream>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

using namespace std;

#include "commonMacroFunction.h"
#include "randomFunction.h"
#include "keyManager.h"
#include "utils.h"
#include "collision.h"
#include "imageManager.h"

using namespace TTYONE_UTIL;

// 여기서 프로그램에 필요한 추가 헤더를 참조합니다.
#define WINNAME (LPCTSTR)(TEXT("뜨웨니 원~"))
#define WINSTARTX	50
#define WINSTARTY	50
#define WINSIZEX	1020		
#define WINSIZEY	800
#define WINSTYLE	WS_CAPTION | WS_SYSMENU

#define RND randomFunction::getSingleton()
#define KEYMANAGER keyManager::getSingleton()
#define IMAGEMANAGER imageManager::getSingleton()

#define SAFE_DELETE(p) {if(p) {delete(p); (p) = NULL;}}

//====================================
// ## 20.05.29 ## Extern ##
//====================================

extern HINSTANCE	_hInstance;
extern HWND			_hWnd;
extern POINT		_ptMouse;