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

//function declaration for helper functions
inline float* CreateSphere(const float radius, const int PointAmount);
inline unsigned int* CreateSphereIndices(const int PointAmount);

namespace test {
	
	class Test3DimensionsRender : public Test {
	public:
		Test3DimensionsRender(const int width, const int height, Renderer* renderer);
		~Test3DimensionsRender();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGUIRender() override;

	private:
		Renderer* m_render;
		const int m_spherePoints = 48; //gets squared for grid
		const int m_winWidth;
		const int m_winHeight;

		float* m_positions = CreateSphere(10, m_spherePoints);
		unsigned int* m_indices = CreateSphereIndices(m_spherePoints);

		float m_lightColor[4] = { 1.0, 1.0, 1.0, 1.0 };	//default white
		float m_sphereColor[4] = { 1.0, 0.0, 0.0, 1.0 }; //default red

		glm::vec3 m_lightPos = glm::vec3(-25.0, 25.0, 25.0);

		VertexArray m_va;
		VertexBuffer m_vb;
		IndexBuffer m_ib;
		VertexBufferLayout m_layout;
		Shader m_shader = Shader("res/shaders/Basic3d.shader");
		glm::mat4 m_proj;
		glm::mat4 m_view;
		glm::vec3 m_translation = glm::vec3(1.0);
	};
}

// helper functions
inline float* CreateSphere(const float radius, const int PointAmount) {
	int totalelements = 3 * PointAmount * PointAmount; // Adjusted for more points

	float* points = new float[totalelements];

	int index = 0;
	for (size_t i = 0; i < PointAmount; i++) {
		float phi = PI * i / (PointAmount - 1); // Ranges from 0 to PI

		for (size_t j = 0; j < PointAmount; j++) {
			float theta = 2 * PI * j / (PointAmount - 1); // Ranges from 0 to 2*PI

			points[index++] = radius * sin(phi) * cos(theta);
			points[index++] = radius * sin(phi) * sin(theta);
			points[index++] = radius * cos(phi);
		}
	}
	return points;
} //thanks gpt

inline unsigned int* CreateSphereIndices(const int PointAmount) {
	int totalIndices = 6 * (PointAmount - 1) * (PointAmount - 1);
	unsigned int* indices = new unsigned int[totalIndices];

	int index = 0;
	for (int i = 0; i < PointAmount - 1; i++) {
		for (int j = 0; j < PointAmount - 1; j++) {
			int current = i * PointAmount + j;
			int next = current + PointAmount;

			indices[index++] = current;
			indices[index++] = next;
			indices[index++] = current + 1;

			indices[index++] = current + 1;
			indices[index++] = next;
			indices[index++] = next + 1;
		}
	}
	return indices;
} //thanks gpt