#pragma once
#include "raylib-cpp.hpp"



struct timer{
	float elapsedTime = 0.0f;

	float getDelta() {
		float dt = GetFrameTime();

		// prevents larges jumps of elapsed time in-between frames //
		if (dt > 0.05f) {
			dt = 0.05f; 
		}

		return elapsedTime += dt;

	}
};