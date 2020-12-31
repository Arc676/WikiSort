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

#include <thread>
#include <chrono>
#include <mutex>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "allsorts.h"

// Exit and return codes
#define EXIT_BAD_ARGS 1
#define EXIT_OPENGL_ERROR 2

#define SHADER_NOT_FOUND -1

enum SortAlgo {
	BUBBLE, QUICK, ODD_EVEN, COMB, COCKTAIL, GNOME, STOOGE, SLOW, BOGO_R, BOGO_D,
	SELECTION, CYCLE, HEAP, CARTESIAN_TREE,
	INSERTION, SHELL, PATIENCE, TREE, SPLAY,
	MERGE,
	RADIX, COUNTING, BUCKET, PIGEONHOLE,
	INTRO, TIM,
	PANCAKE
};

// Visualizer update calls
VISUALIZER_SWAP* visualizer_itemsSwapped;
VISUALIZER_ADV* visualizer_pointerAdvanced;

VISUALIZER_UPDATE* visualizer_updateArray;
VISUALIZER_ABORT_REQ* visualizer_abortRequested;

// Concurrency
using Lock = std::lock_guard<std::mutex>;
std::mutex mutex;
std::thread sortingThread;
int* renderArray = nullptr;
bool arrayChanged = false;
bool abortRequested = false;

// Array parameters
int arraySize = 0;
int* array = nullptr;
int dataMax = 100;

// OpenGL
bool shadersCompiled = false;
unsigned int shaderProg, vis_tex, vis_vao, vis_ebo, vis_fbo;
float* vis_vertices;
unsigned int* vis_indices;

#define FNAME_SIZE 200
char fragmentShader[FNAME_SIZE], vertexShader[FNAME_SIZE];

// Render settings
int sleepTime = 500, lastSleepTime;

// UI text
const char* sequences_s[] = {
	"Shell 1959", "Frank & Lazarus 1960",
	"A168604", "A083318", "A003586", "A003462", "A036569", "A036562", "A033622",
	"Gonnet & Baeza-Yates 1991",
	"A108870", "A102549"
};

#endif
