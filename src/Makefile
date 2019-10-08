# Makefile for Writing Make Files Example

# *****************************************************
# Variables to control Makefile operation

CXX = g++
CXXFLAGS = -Wall -g -std=c++17 -fopenmp -Iglm-0.9.7.1/

# ****************************************************
# Targets needed to bring the executable up to date

all: main_path_tracing

main_path_tracing: main_path_tracing.o \
	complex_geometry.o \
	geometry/sphere.o \
	geometry/triangle.o \
	lib_scene.o \
	light.o \
	material.o \
	model/bounding_box.o \
	model/camera.o \
	model/cartesian_system.o \
	model/grid/cell.o \
	model/grid/grid.o \
	model/scene.o \
	ray.o \
	render/pathtracing.o \
	util/geom_util.o \
	util/image_util.o \
	util/vector_util.o
	$(CXX) $(CXXFLAGS) -o main_path_tracing \
	main_path_tracing.o \
	complex_geometry.o \
	geometry/sphere.o \
	geometry/triangle.o \
	lib_scene.o \
	light.o \
	material.o \
	model/bounding_box.o \
	model/camera.o \
	model/cartesian_system.o \
	model/grid/cell.o \
	model/grid/grid.o \
	model/scene.o \
	ray.o \
	render/pathtracing.o \
	util/geom_util.o \
	util/image_util.o \
	util/vector_util.o

main_path_tracing.o: main_path_tracing.cpp
	$(CXX) $(CXXFLAGS) -c main_path_tracing.cpp

complex_geometry.o: complex_geometry.h

#geometry/primitive.o: geometry/primitive.h
geometry/sphere.o: geometry/sphere.h
geometry/triangle.o: geometry/triangle.h

lib_scene.o: lib_scene.h
light.o: light.h

material.o: material.h

model/bounding_box.o: model/bounding_box.h
model/camera.o: model/camera.h
model/cartesian_system.o: model/cartesian_system.h
model/scene.o: model/scene.h

model/grid/cell.o: model/grid/cell.h
model/grid/grid.o: model/grid/grid.h

ray.o: ray.h

render/pathtracing.o: render/pathtracing.h

util/geom_util.o: util/geom_util.h
util/image_util.o: util/image_util.h
util/vector_util.o: util/vector_util.h
