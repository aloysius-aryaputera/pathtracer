//File: lib_scene.h
#ifndef LIB_SCENE_H
#define LIB_SCENE_H

#include <iostream>
#include <tuple>
#include <vector>

#include <glm/vec3.hpp>

#include "complex_geometry.h"
#include "geometry/primitive.h"
#include "geometry/sphere.h"
#include "geometry/triangle.h"
#include "light.h"
#include "material.h"
#include "model/camera.h"
#include "model/scene.h"
#include "util/geom_util.h"
#include "util/image_util.h"

using namespace std;

Scene* create_scene_1();
Scene* create_scene_2();

#endif
