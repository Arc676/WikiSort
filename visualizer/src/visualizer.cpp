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

#include "visualizer.h"

void renderVisualizer() {
	if (!shadersCompiled) {
		return;
	}

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

int compileShaders() {
	std::ifstream file;
	std::stringstream stream;
	std::string src;

	// Set up vertex shader
	unsigned int vShader = glCreateShader(GL_VERTEX_SHADER);
	file.open(vertexShader);
	if (!file.is_open()) {
		shadersCompiled = false;
		return SHADER_NOT_FOUND;
	}
	stream << file.rdbuf();
	file.close();
	src = stream.str();
	const char* vertexSrc = src.c_str();
	glShaderSource(vShader, 1, &vertexSrc, NULL);
	glCompileShader(vShader);

	stream.str(std::string());

	// Set up fragment shader
	unsigned int fShader = glCreateShader(GL_FRAGMENT_SHADER);
	file.open(fragmentShader);
	if (!file.is_open()) {
		shadersCompiled = false;
		return SHADER_NOT_FOUND;
	}
	stream << file.rdbuf();
	file.close();
	src = stream.str();
	const char* fragmentSrc = src.c_str();
	glShaderSource(fShader, 1, &fragmentSrc, NULL);
	glCompileShader(fShader);

	// Set up shader program
	shaderProg = glCreateProgram();
	glAttachShader(shaderProg, vShader);
	glAttachShader(shaderProg, fShader);
	glLinkProgram(shaderProg);

	glDeleteShader(vShader);
	glDeleteShader(fShader);

	shadersCompiled = true;
	return EXIT_SUCCESS;
}

int initGL() {
	// Generate VAO, EBO
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
		std::cerr << "Framebuffer incomplete" << std::endl;
		return EXIT_OPENGL_ERROR;
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	return compileShaders();
}

void rebuildEBO(int newSize) {
	const size_t INDEX_LIST_SIZE = newSize * 6 * sizeof(float);
	vis_indices = (unsigned int*)realloc(vis_indices, INDEX_LIST_SIZE);
	for (int i = arraySize; i < newSize; i++) {
		int idx = i * 6;
		int vShift = i * 4;
		vis_indices[idx] = vShift;
		vis_indices[1 + idx] = vis_indices[3 + idx] = 1 + vShift;
		vis_indices[2 + idx] = vis_indices[5 + idx] = 3 + vShift;
		vis_indices[4 + idx] = 2 + vShift;
	}
	glBindVertexArray(vis_vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vis_ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, INDEX_LIST_SIZE, vis_indices, GL_DYNAMIC_DRAW);
	glBindVertexArray(0);
}

void swapped(void** a, void** b) {
	renderVisualizer();
}

void ptrAdvanced(void** ptr, int dst) {
	renderVisualizer();
}

void glfwErrorCallback(int error, const char* description) {
	std::cerr << "GLFW error " << error << ": " << description << std::endl;
}

int main(int argc, char* argv[]) {
	// Default shader programs
	sprintf(fragmentShader, "fragment.glsl");
	sprintf(vertexShader, "vertex.glsl");

	int opt;
	while ((opt = getopt(argc, argv, "f:v:")) != -1) {
		switch (opt) {
		case 'f':
			snprintf(fragmentShader, FNAME_SIZE, "%s", optarg);
			break;
		case 'v':
			snprintf(vertexShader, FNAME_SIZE, "%s", optarg);
			break;
		default:
			std::cerr << "Invalid argument " << opt << std::endl;
			return EXIT_BAD_ARGS;
		}
	}

	glfwSetErrorCallback(glfwErrorCallback);
	if (!glfwInit()) {
		return EXIT_OPENGL_ERROR;
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
		return EXIT_OPENGL_ERROR;
	}
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	if (glewInit() != GLEW_OK) {
		std::cerr << "Failed to initialize OpenGL loader" << std::endl;
		return EXIT_OPENGL_ERROR;
	}

	srand(time(NULL));

	visualizer_itemsSwapped = swapped;
	visualizer_pointerAdvanced = ptrAdvanced;

	int gl = initGL();
	if (gl > 0) {
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
		ImGui::SetNextWindowSize(ImVec2(600, 500), ImGuiCond_FirstUseEver);

		if (ImGui::Begin("Control Panel")) {
			if (ImGui::CollapsingHeader("Data")) {
				static int newSize = 100;
				ImGui::InputInt("Array size", &newSize);
				if (ImGui::Button("Allocate")) {
					array = (int*)realloc(array, newSize * sizeof(int));
					vis_vertices = (float*)realloc(vis_vertices, newSize * 12 * sizeof(float));
					if (newSize > arraySize) {
						rebuildEBO(newSize);
					}
					arraySize = newSize;
					renderVisualizer();
				}
				ImGui::InputInt("Maximum element value", &dataMax);
				if (ImGui::Button("Fill with random numbers")) {
					for (int i = 0; i < arraySize; i++) {
						array[i] = rand() % (dataMax + 1);
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
				if (ImGui::Button("Radix Sort (LSD)")) {
					radixSortLSD((void**)array, arraySize, sizeof(int), cmp_int, 10, int_base_cmp_LSD, int_base_dig_LSD);
				}
				if (ImGui::Button("Counting Sort")) {
					countingSort((void**)array, arraySize, sizeof(int), key_int, dataMax + 1);
				}
				if (ImGui::Button("Bucket Sort")) {
					bucketSort((void**)array, arraySize, sizeof(int), cmp_int, key_intranges);
				}
				if (ImGui::Button("Pigeonhole Sort")) {
					pigeonholeSort((void**)array, arraySize, sizeof(int), key_int, dataMax + 1);
				}
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

		ImGui::SetNextWindowPos(ImVec2(0, 500), ImGuiCond_FirstUseEver);
		ImGui::SetNextWindowSize(ImVec2(600, 200), ImGuiCond_FirstUseEver);

		if (ImGui::Begin("Settings")) {
			ImGui::InputText("Vertex Shader", vertexShader, FNAME_SIZE);
			ImGui::InputText("Fragment Shader", fragmentShader, FNAME_SIZE);
			if (ImGui::Button("Compile Shaders")) {
				compileShaders();
			}
			if (ImGui::Button("Refresh Visualizer")) {
				renderVisualizer();
			}
		}
		ImGui::End();

		ImGui::SetNextWindowPos(ImVec2(600, 0), ImGuiCond_FirstUseEver);
		ImGui::SetNextWindowSize(ImVec2(700, 700), ImGuiCond_FirstUseEver);

		if (ImGui::Begin("Visualizer")) {
			if (shadersCompiled) {
				ImGui::BeginChild("ArrayRender");
				ImVec2 size = ImGui::GetWindowSize();

				ImGui::Image((ImTextureID)(intptr_t)vis_tex, size, ImVec2(0, 1), ImVec2(1, 0));
				ImGui::EndChild();
			} else {
				ImGui::Text("Please choose and compile shaders to enable visualizer.");
			}
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

	return EXIT_SUCCESS;
}
