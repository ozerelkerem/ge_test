#pragma once
#define GLM_ENABLE_EXPERIMENTAL
#define _HAS_STD_BYTE 0
#include <iostream>
#include <stdlib.h>
#include <stdarg.h>
#include <stdint.h>
#include <limits>

#include <vector>
#include <list>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>

#include <algorithm>
#include <functional>

#include <assert.h>
#include <memory>

#include <string>
#include <math.h>

#include <chrono>
#include <util/Handle.h>

#include<physx/PxPhysicsAPI.h>

#define PROJECTDIRECTORY "C:\\Users\\KeremPC\\Documents\\GitHub\\ge_test"

#define ACTOR_LUT_GROW 1024
#define COMPONENT_LUT_GROW 1024
#define ACTOR_CHUNK_SIZE 512
#define COMPONENT_CHUNK_SIZE 512

#define GLOBAL_MEMORY_CAPACITY 134217728 // 128 MB



using TypeID = uint16_t;
using TextureID = uint16_t;
using ActorID = GameEngine::Util::Handle64;

#define SKINNED_MESH_MAX_WEIGHT_PER_VERTICES 4

class Shader;
extern Shader *normalShader;
extern Shader *colorShader;
extern Shader *spriteShader;

class  MemoryManager;
extern MemoryManager*				ECSMemoryManager;

class GlobalMemoryUser
{
private:

	MemoryManager* ECS_MEMORY_MANAGER;

public:

	GlobalMemoryUser();
	virtual ~GlobalMemoryUser();

	 const void* Allocate(size_t memSize);
	 void Free(void* pMem);
};


class Engine;

extern Engine*		GE_Engine;

void	Initialize();
void	Terminate();