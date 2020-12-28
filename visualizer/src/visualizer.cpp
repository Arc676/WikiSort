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

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <string>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "allsorts.h"

VISUALIZER_SWAP* visualizer_itemsSwapped;
VISUALIZER_ADV* visualizer_pointerAdvanced;

int arraySize = 0;
int* array = nullptr;

int dataMax = 100;
unsigned int shaderProg, vis_tex, vis_vao, vis_ebo, vis_fbo;
float* vis_vertices;
unsigned int* vis_indices;

const char* sequences_s[] = {
	"Shell 1959", "Frank & Lazarus 1960",
	"A168604", "A083318", "A003586", "A003462", "A036569", "A036562", "A033622",
	"Gonnet & Baeza-Yates 1991",
	"A108870", "A102549"
};

void renderVisualizer() {
	float vertices[12];
	memset(vertices, 0, sizeof(vertices));
	vertices[4] = vertices[7] = -1;
	float w = 2.f / arraySize;
	for (int i = 0; i < arraySize; i++) {
		float x = w * i - 1;
		float h = (float)array[i] * 2 / dataMax;
		vertices[0] = vertices[3] = x + w;
		vertices[6] = vertices[9] = x;
		vertices[1] = vertices[10] = h - 1;
		memcpy(vis_vertices + i * 12, vertices, sizeof(vertices));
	}

	glBindFramebuffer(GL_FRAMEBUFFER, vis_fbo);
	glViewport(0, 0, 1200, 700);
	glClearColor(0.f, 0.f, 0.f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(shaderProg);

	glBindVertexArray(vis_vao);
	unsigned int vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 12 * arraySize * sizeof(float), vis_vertices, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glDrawElements(GL_TRIANGLES, 6 * arraySize, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glDeleteBuffers(1, &vbo);
}

int initGL() {
	// Set up vertex shader
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	const char *vertexSrc = "#version 330 core\n"
	    "layout (location = 0) in vec3 aPos;\n"
	        "void main()\n"
		    "{\n"
		        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
			    "}\0";
	glShaderSource(vertexShader, 1, &vertexSrc, NULL);
	glCompileShader(vertexShader);

	// Set up fragment shader
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	const char* fragmentSrc = "#version 330 core\n"
	"out vec4 FragColor;\n"
	"void main(){\n"
	    "FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);\n"
	    "}\0";
	glShaderSource(fragmentShader, 1, &fragmentSrc, NULL);
	glCompileShader(fragmentShader);

	// Set up shader program
	shaderProg = glCreateProgram();
	glAttachShader(shaderProg, vertexShader);
	glAttachShader(shaderProg, fragmentShader);
	glLinkProgram(shaderProg);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// Set up VAO, EBO
	glGenVertexArrays(1, &vis_vao);
	glGenBuffers(1, &vis_ebo);

	// Set up framebuffer
	glGenFramebuffers(1, &vis_fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, vis_fbo);

	glGenTextures(1, &vis_tex);
	glBindTexture(GL_TEXTURE_2D, vis_tex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1200, 700, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, vis_tex, 0);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		fprintf(stderr, "Framebuffer incomplete\n");
		return 1;
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	return 0;
}

void swapped(void** a, void** b) {
	renderVisualizer();
}

void ptrAdvanced(void** ptr, int dst) {
	renderVisualizer();
}

void glfwErrorCallback(int error, const char* description) {
	fprintf(stderr, "GLFW error %d: %s\n", error, description);
}

int main() {
	glfwSetErrorCallback(glfwErrorCallback);
	if (!glfwInit()) {
		return 1;
	}
	#ifdef __APPLE__
	const char* glslVersion = "#version 150";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	#else
	const char* glslVersion = "#version 130";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

	#endif

	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	GLFWwindow* window = glfwCreateWindow(1200, 700, "WikiSort Visualizer", NULL, NULL);
	if (!window) {
		return 1;
	}
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize OpenGL loader\n");
		return 1;
	}

	srand(time(NULL));

	visualizer_itemsSwapped = swapped;
	visualizer_pointerAdvanced = ptrAdvanced;

	int gl = initGL();
	if (gl != 0) {
		return gl;
	}

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(glslVersion);
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_FirstUseEver);
		ImGui::SetNextWindowSize(ImVec2(600, 700), ImGuiCond_FirstUseEver);

		if (ImGui::Begin("Control Panel")) {
			if (ImGui::CollapsingHeader("Data")) {
				static int newSize = 100;
				ImGui::InputInt("Array size", &newSize);
				if (ImGui::Button("Allocate")) {
					array = (int*)realloc(array, newSize * sizeof(int));
					vis_vertices = (float*)realloc(vis_vertices, newSize * 12 * sizeof(float));
					if (newSize > arraySize) {
						vis_indices = (unsigned int*)realloc(vis_indices, newSize * 6 * sizeof(float));
						for (int i = arraySize; i < newSize; i++) {
							int idx = i * 6;
							int vShift = i * 4;
							vis_indices[idx] = vShift;
							vis_indices[1 + idx] = vis_indices[3 + idx] = 1 + vShift;
							vis_indices[2 + idx] = vis_indices[5 + idx] = 3 + vShift;
							vis_indices[4 + idx] = 2 + vShift;
						}
						// reload EBO
						glBindVertexArray(vis_vao);
						glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vis_ebo);
						glBufferData(GL_ELEMENT_ARRAY_BUFFER, newSize * 6 * sizeof(float), vis_indices, GL_DYNAMIC_DRAW);
						glBindVertexArray(0);
					}
					arraySize = newSize;
					renderVisualizer();
				}
				ImGui::InputInt("Maximum element value", &dataMax);
				if (ImGui::Button("Fill with random numbers")) {
					for (int i = 0; i < arraySize; i++) {
						array[i] = rand() % dataMax;
					}
					renderVisualizer();
				}
			}
			if (ImGui::CollapsingHeader("Exchange Sorts")) {
				if (ImGui::Button("Bubble Sort")) {
					bubbleSort((void**)array, arraySize, sizeof(int), cmp_int);
				}
				if (ImGui::Button("Quicksort")) {
					quickSort((void**)array, arraySize, sizeof(int), cmp_int);
				}
				if (ImGui::Button("Odd-Even Sort")) {
					oddEvenSort((void**)array, arraySize, sizeof(int), cmp_int);
				}

				static float combShrink = 1.3f;
				if (ImGui::Button("Comb Sort")) {
					combSort((void**)array, arraySize, sizeof(int), cmp_int, combShrink);
				}
				ImGui::SameLine();
				ImGui::InputFloat("Shrink Factor", &combShrink);

				if (ImGui::Button("Cocktail Sort")) {
					cocktailSort((void**)array, arraySize, sizeof(int), cmp_int);
				}
				if (ImGui::Button("Gnome Sort")) {
					gnomeSort((void**)array, arraySize, sizeof(int), cmp_int);
				}
				if (ImGui::Button("Stooge Sort")) {
					stoogeSort((void**)array, arraySize, sizeof(int), cmp_int);
				}
				if (ImGui::Button("Slowsort")) {
					slowSort((void**)array, arraySize, sizeof(int), cmp_int);
				}

				static bool deterministic = true;
				if (ImGui::Button("Bogosort")) {
					if (deterministic) {
						bogoSort_det((void**)array, arraySize, sizeof(int), cmp_int);
					} else {
						bogoSort_rand((void**)array, arraySize, sizeof(int), cmp_int);
					}
				}
				ImGui::SameLine();
				ImGui::Checkbox("Deterministic Sort", &deterministic);
			}
			if (ImGui::CollapsingHeader("Selection Sorts")) {
				if (ImGui::Button("Selection Sort")) {
					selectionSort((void**)array, arraySize, sizeof(int), cmp_int);
				}
				if (ImGui::Button("Cycle Sort")) {
					cycleSort((void**)array, arraySize, sizeof(int), cmp_int);
				}
				if (ImGui::Button("Heapsort")) {
					heapSort((void**)array, arraySize, sizeof(int), cmp_int);
				}
				if (ImGui::Button("Cartesian Tree Sort")) {
					cartesianTreeSort((void**)array, arraySize, sizeof(int), cmp_int, binTree_cmp_int);
				}
			}
			if (ImGui::CollapsingHeader("Insertion Sorts")) {
				if (ImGui::Button("Insertion Sort")) {
					insertionSort((void**)array, arraySize, sizeof(int), cmp_int);
				}

				static int seq = 0;
				if (ImGui::Button("Shellsort")) {
					shellSort((void**)array, arraySize, sizeof(int), cmp_int, (GapSequence)seq, nullptr, nullptr);
				}
				ImGui::SameLine();
				ImGui::Combo("Gap Sequence", &seq, sequences_s, GAP_COUNT);

				if (ImGui::Button("Patience Sort")) {
					patienceSort((void**)array, arraySize, sizeof(int), cmp_int, geq_int);
				}
				if (ImGui::Button("Tree Sort")) {
					treeSort((void**)array, arraySize, sizeof(int), cmp_int);
				}
				if (ImGui::Button("Splay Sort")) {
					splaySort((void**)array, arraySize, sizeof(int), cmp_int);
				}
			}
			if (ImGui::CollapsingHeader("Merge Sorts")) {
				if (ImGui::Button("Merge Sort")) {
					mergeSort((void**)array, arraySize, sizeof(int), cmp_int);
				}
			}
			if (ImGui::CollapsingHeader("Distribution Sorts")) {
			}
			if (ImGui::CollapsingHeader("Concurrent Sorts")) {
				ImGui::Text("(None yet implemented)");
			}
			if (ImGui::CollapsingHeader("Hybrid Sorts")) {
				if (ImGui::Button("Introsort")) {
					introSort((void**)array, arraySize, sizeof(int), cmp_int);
				}
				if (ImGui::Button("Timsort")) {
					timSort((void**)array, arraySize, sizeof(int), cmp_int);
				}
			}
			if (ImGui::CollapsingHeader("Other Sorts")) {
				if (ImGui::Button("Pancake Sort")) {
					pancakeSort((void**)array, arraySize, sizeof(int), cmp_int);
				}
			}
			if (ImGui::Button("Exit")) {
				break;
			}
		}
		ImGui::End();

		ImGui::SetNextWindowPos(ImVec2(600, 0), ImGuiCond_FirstUseEver);
		ImGui::SetNextWindowSize(ImVec2(700, 700), ImGuiCond_FirstUseEver);

		if (ImGui::Begin("Visualizer")) {
			ImGui::BeginChild("ArrayRender");
			ImVec2 size = ImGui::GetWindowSize();

			ImGui::Image((ImTextureID)(intptr_t)vis_tex, size, ImVec2(0, 1), ImVec2(1, 0));
			ImGui::EndChild();
		}
		ImGui::End();

		ImGui::Render();
		int displayW, displayH;
		glfwGetFramebufferSize(window, &displayW, &displayH);
		glViewport(0, 0, displayW, displayH);
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		glfwSwapBuffers(window);
	}

	glDeleteFramebuffers(1, &vis_fbo);
	glDeleteVertexArrays(1, &vis_vao);
	glDeleteBuffers(1, &vis_ebo);
	glDeleteProgram(shaderProg);

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	glfwDestroyWindow(window);
	glfwTerminate();

	if (array) {
		free(array);
		free(vis_vertices);
		free(vis_indices);
	}

	return 0;
}
