// Copyright (C) 2020 Arc676/Alessandro Vinciguerra <alesvinciguerra@gmail.com>

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation (version 3)

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.
// See README and LICENSE for more details.

#ifndef VISUALIZER_H
#define VISUALIZER_H

#include <cstdlib>
#include <ctime>
#include <unistd.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "allsorts.h"

// Visualizer update calls
VISUALIZER_SWAP* visualizer_itemsSwapped;
VISUALIZER_ADV* visualizer_pointerAdvanced;

// Array parameters
int arraySize = 0;
int* array = nullptr;
int dataMax = 100;

// OpenGL
unsigned int shaderProg, vis_tex, vis_vao, vis_ebo, vis_fbo;
float* vis_vertices;
unsigned int* vis_indices;

#define FNAME_SIZE 200
char fragmentShader[FNAME_SIZE], vertexShader[FNAME_SIZE];

// UI text
const char* sequences_s[] = {
	"Shell 1959", "Frank & Lazarus 1960",
	"A168604", "A083318", "A003586", "A003462", "A036569", "A036562", "A033622",
	"Gonnet & Baeza-Yates 1991",
	"A108870", "A102549"
};

#endif
