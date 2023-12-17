#include "RandomGenerator.h"

std::random_device random_device;
std::mt19937 generator(random_device());

float genRandomPosition(float min, float max) {
    std::uniform_real_distribution<float> dist(min, max);
    float randomValue = dist(generator);
    return randomValue;
}