#pragma once
#include "raylib-cpp.hpp"
#include <cstring>
#include <string>
#include <unordered_map>

enum spriteType {
	BACKGROUND = 0,
	ENTITY = 1,
	ANIMATION = 2,
	UI = 3
};

struct virtualResolutions{
	static const int VIRTUAL_WIDTH = 1920;
	static const int VIRTUAL_HEIGHT = 1080;
};

struct spriteHandler {

	std::unordered_map<const char*, Texture2D> textures;

	 Texture2D& loadSprite(const char* name, int spriteType) {
		const char* prefix = "media/textures/";

		switch (spriteType) {
		case BACKGROUND:
			prefix = "media/textures/background/";
		break;

		case ENTITY:
			prefix = "media/textures/entity/";
		break;

		case ANIMATION:
			prefix = "media/textures/anim/";
		break;

		case UI:
			prefix = "media/textures/UI/";
		break;

		default:
			prefix = "media/textures/";
		break;
		}

		std::string result(std::string(prefix) + name);

		if (!textures.contains(name)) {
			textures[name] = LoadTexture(result.c_str());
		}

		return textures.at(name);
	};
};

// file for helper functions that don't exist in raylib and would clutter Warblade.cpp
