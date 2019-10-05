//File: image_util.h
#ifndef IMAGE_UTIL_H
#define IMAGE_UTIL_H

#include <cmath>
#include <fstream>
#include <sstream>
#include <vector>

#include <glm/vec4.hpp>

float clamp(const float &lo, const float &hi, const float &v);
void save_image(std::vector<std::vector<glm::vec4>> &image, int width, int height);
std::vector<std::vector<glm::vec4>> read_image(const char * filename);

#endif
