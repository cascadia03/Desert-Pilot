#pragma once

#include <iostream>
#include <algorithm>
#include <vector>
#include <list>
#include <map>
#include <string>
#include <random>
#include <time.h>
#include "SDKsound.h"
#include "SDKwavefile.h"

#pragma comment(lib, "dsound.lib")

using namespace std;

#define g_device DXUTGetD3D9Device()
#define WINSIZEX 1280
#define WINSIZEY 720

typedef D3DXVECTOR2 VECTOR2;
typedef D3DXVECTOR3 VECTOR3;

#include "image_manager.h"
#include "render_manager.h"
#include "scene_manager.h"
#include "object_manager.h"
#include "input_manager.h"
#include "sound_manager.h"