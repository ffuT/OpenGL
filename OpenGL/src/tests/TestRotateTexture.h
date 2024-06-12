#pragma once
#include "Test.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "macros.h"
#include "Renderer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "VertexArray.h"
#include "Texture.h"

namespace test {

	class TestRotateTexture : public Test {
	public:
		TestRotateTexture(const int width, const int height, Renderer* renderer);
		~TestRotateTexture();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGUIRender() override;
	private:
		Renderer* m_render;
		const int winWidth; 
		const int winHeight;
		float m_time;
		float r = 0.069f, g = 0.069f, b = 0.069f;
		int rotationSpeed = 0;

		float m_positions[16] = {   //simple square
			-50, -50, 0.0, 0.0, // 0
			 50, -50, 1.0, 0.0, // 1
			 50,  50, 1.0, 1.0, // 2
			-50,  50, 0.0, 1.0, // 3
		};

		unsigned int m_indices[6] = { // vertex index
			0, 1, 2,
			2, 3, 0
		};

		VertexArray m_va;
		VertexBuffer m_vb = VertexBuffer(m_positions, 4 * 4 * sizeof(float));
		VertexBufferLayout m_layout;
		IndexBuffer m_ib = IndexBuffer(m_indices, 3 * 2);
		Shader m_shader = Shader("res/shaders/Basic.shader");
		Texture m_texture = Texture("res/texture/catrizz.jpg");
		//matricies projection and view
		glm::mat4 proj = glm::ortho(0.0, (double)winWidth, 0.0, (double)winHeight, -1.0, 1.0);
		glm::mat4 view = glm::translate(glm::mat4(1.0), glm::vec3(1, 1, 0));
		glm::vec3 translation = glm::vec3(winWidth / 2, winHeight / 2, 0);
	};
}

