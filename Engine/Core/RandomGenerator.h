#pragma once

#include <random>

extern std::mt19937 generator;  // Declare the generator in the header file

float genRandom(float min = -100.0f, float max = 100.0f);