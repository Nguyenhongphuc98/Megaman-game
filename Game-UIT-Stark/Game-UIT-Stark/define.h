#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>
#include <dsound.h>
//#include "dxaudio.h"
#include <vector>
#include <array>
#include <map>
#include <unordered_map>
#include <functional>
#include <string>
#include <algorithm>
#include "Trace.h"
//#include "utils.h"
//#include "ConfigReader.h"

#ifdef _DEBUG
#define SHOW_BOUNDINGBOX
#endif


#define SCREEN_WIDTH 512//800//640
#define SCREEN_HEIGHT 448//600//480

#define VECTOR2 D3DXVECTOR2
#define VECTOR3 D3DXVECTOR3
#define POINT VECTOR2

#define SAFE_DELETE(p) { if(p) { delete p; p = nullptr; } }