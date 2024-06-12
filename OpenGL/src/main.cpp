/*
    My first OpenGL Program,
    using GLFW, glew, glm , and ImGUI
    largely inspired by the Cherno's c++ opengl playlist -> https://www.youtube.com/playlist?list=PLlrATfBNZ98foTJPJ_Ev03o2oq3-GGOS2
*/
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <stb_image/stb_image.h>

#include <string>
#include <fstream>
#include <iostream>
#include <chrono>
#include <thread>
#include <sstream>
#include <math.h>
#include <windows.h>

#include "macros.h"
#include "Renderer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "VertexArray.h"
#include "Texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "tests/test.h"
#include "tests/testClearColor.h"
#include "tests/testRotateTexture.h"
#include "tests/Test3DimensionsRender.h"

constexpr int WIDTH = 1280, HEIGHT = 720;
constexpr bool UseVsync = false;
const std::string iconImgPath = "res/texture/catrizz.jpg";

float appRunTime = 0.0;

void LoadIcon(GLFWwindow* win);

int main(void){
    GLFWwindow* window;

    if (!glfwInit())
        return -1;

    window = glfwCreateWindow(WIDTH, HEIGHT, "OpenGL", NULL, NULL);
    if (!window){
        glfwTerminate();
        return -1;
    }

    LoadIcon(window);

    glfwMakeContextCurrent(window);
    if (glewInit() != GLEW_OK)
        std::cout << "Error!" << std::endl;
    glfwSwapInterval(UseVsync);

    glfwWindowHint(GLFW_DEPTH_BITS, 24);

    std::cout << glGetString(GL_VERSION) << std::endl;

    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    
    Renderer renderer;

    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330 core");

    test::Test* currentTest = nullptr;
    test::TestMenu* menu = new test::TestMenu(currentTest);
    currentTest = menu;

    menu->RegisterTest<test::TestClearColor>("Clear Color");
    menu->RegisterTest<test::TestRotateTexture>("Rotating cat color shit wow", WIDTH, HEIGHT, &renderer);
    menu->RegisterTest<test::Test3DimensionsRender>("Sphere test iguess", WIDTH, HEIGHT, &renderer);

    auto now = std::chrono::system_clock::now();
    auto last = std::chrono::system_clock::now();
    auto second = now + std::chrono::seconds(1);
    float delta = 0.0f;
    while (!glfwWindowShouldClose(window)){
        last = now;
        now = std::chrono::system_clock::now();
        delta = (float)(now - last).count() / 10000000;

        renderer.Clear();
         
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        if (currentTest) {
            currentTest->OnUpdate(delta);
            currentTest->OnRender();
            ImGui::Begin("Test");
            if (currentTest != menu && ImGui::Button("<-")) {
                delete currentTest;
                currentTest = menu;
            }
            currentTest->OnImGUIRender();
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::End();
        }


        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
        glfwPollEvents();
        appRunTime += delta;
    }
    delete currentTest;
    if (currentTest != menu)
        delete menu;

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
}

void LoadIcon(GLFWwindow* win) {
    // Load the icon image
    int width, height, channels;
    unsigned char* pixels = stbi_load(iconImgPath.c_str(), &width, &height, &channels, 4);
    if (!pixels)
    {
        glfwTerminate();
        exit(-1);
    }
    // Create GLFWimage and set its properties
    GLFWimage images[1];
    images[0].width = width;
    images[0].height = height;
    images[0].pixels = pixels;
    // Set the window icon
    glfwSetWindowIcon(win, 1, images);
    // Free the image memory
    stbi_image_free(pixels);
}