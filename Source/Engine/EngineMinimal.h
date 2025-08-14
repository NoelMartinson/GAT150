#pragma once

// core
#include "Core/File.h"
#include "Core/Logger.h"
#include "Core/Random.h"
#include "Core/Time.h"
#include "Core/Singleton.h"
#include "Core/StringHelper.h"
#include "Core/Json.h"

// framework
#include "Framework/Object.h"
#include "Framework/Actor.h"
#include "Framework/Game.h"
#include "Framework/Scene.h"

// math
#include "Math/Math.h"
#include "Math/Vector2.h"
#include "Math/Vector3.h"
#include "Math/Transform.h"

// resources
#include "Resource/Resource.h"
#include "Resource/ResourceManager.h"

// third-party library
#include <fmod.hpp>
#include <fmod_errors.h>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>

// standard library
#include <string>
#include <iostream>
#include <fstream>
#include <memory>
#include <vector>
#include <random>
#include <map>
#include <algorithm>
#include <list>
#include <cstdlib>
#include <filesystem>

#include "EngineMinimal.h"

#include "Engine.h"

//Components
#include "Components/SpriteRenderer.h"
#include "Components/RigidBody.h"
#include "Components/CircleCollider2D.h"
#include "Components/MeshRenderer.h"


//audio
#include "Audio/AudioSystem.h"
#include "Audio/AudioClip.h"

//input
#include "Input/InputSystem.h"

//renderer
#include "Renderer/Font.h"
#include "Renderer/Renderer.h"
#include "Renderer/Texture.h"
#include "Renderer/Mesh.h"
#include "Renderer/Text.h"
#include "Renderer/ParticleSystem.h"