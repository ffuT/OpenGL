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
#include "CubeMap.h"

namespace test{

	class TestCubeMap : public Test {
	public:
		TestCubeMap(const int width, const int height, Renderer* renderer);
		~TestCubeMap();
		
		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGUIRender() override;

	private:
		Renderer* m_render;
		const int m_winWidth;
		const int m_winHeight;

		VertexArray m_va;
		VertexBuffer m_vb = VertexBuffer(positions, 8 * 3 * sizeof(float));
		IndexBuffer m_ib = IndexBuffer(indices, 3 * 12);
		VertexBufferLayout m_layout;
		CubeMap m_skybox = CubeMap("res/texture/skybox");
		Shader m_shader = Shader("res/shaders/skybox.shader");
		glm::mat4 m_proj;
		glm::mat4 m_view;
        
		float positions[8 * 3] = {
		   -1.0f, -1.0f,  1.0f,
		    1.0f, -1.0f,  1.0f,
			1.0f, -1.0f, -1.0f,
		   -1.0f, -1.0f, -1.0f,
		   -1.0f,  1.0f,  1.0f,
		    1.0f,  1.0f,  1.0f,
			1.0f,  1.0f, -1.0f,
		   -1.0f,  1.0f, -1.0f
		};
		unsigned int indices[3 * 12] = {
			1, 2, 6,
			6, 5, 1,
			0, 4, 7,
			7, 3, 0,
			4, 5, 6,
			6, 7, 4,
			0, 3, 2,
			2, 1, 0,
			0, 1, 5,
			5, 4, 0,
			3, 7, 6,
			6, 2, 3
		};
	};

}