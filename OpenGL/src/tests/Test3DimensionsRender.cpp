#include "Test3DimensionsRender.h"

test::Test3DimensionsRender::Test3DimensionsRender(const int width, const int height, Renderer* renderer)
	: m_winWidth(width), m_winHeight(height), m_render(renderer)
	, m_vb(VertexBuffer(m_positions, 3 * m_spherePoints * m_spherePoints * sizeof(float)))
	, m_ib(IndexBuffer(m_indices, 6 * (m_spherePoints - 1) * (m_spherePoints - 1)))
	, m_proj(glm::perspective(glm::radians(70.0f), (float)m_winWidth / (float)m_winHeight, 0.1f, 100.0f))
	, m_view(glm::lookAt(glm::vec3(0, 0, 50), // Camera position in world space
						 glm::vec3(0, 0, 0),  // Look at point
						 glm::vec3(0, 1, 0))) // Up vector
{
	GLCall(glEnable(GL_DEPTH_TEST));

	m_layout.Push<float>(3);
	m_va.AddBuffer(m_vb, m_layout);

	m_shader.Bind();
}

test::Test3DimensionsRender::~Test3DimensionsRender(){
	GLCall(glDisable(GL_DEPTH_TEST));
	delete[] m_positions;
	delete[] m_indices;
}

void test::Test3DimensionsRender::OnUpdate(float deltaTime){

}

void test::Test3DimensionsRender::OnRender(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glm::mat4 model = glm::translate(glm::mat4(1.0), m_translation);
	m_shader.SetUniformMat4f("u_model", model);
	m_shader.SetUniformMat4f("u_view", m_view);
	m_shader.SetUniformMat4f("u_projection", m_proj);
	
	m_shader.SetUniform4f("u_sunPosition", glm::vec4(m_lightPos, 1.0));
	m_shader.SetUniform4f("u_sunCol", m_lightColor);
	m_shader.SetUniform4f("u_sphereCol", m_sphereColor);
	m_render->Draw(m_va, m_ib, m_shader);
}

void test::Test3DimensionsRender::OnImGUIRender(){
	ImGui::Text("Light Source Position");
	ImGui::SliderFloat("X", &m_lightPos.x, -100.0f, 100.0f);
	ImGui::SliderFloat("Y", &m_lightPos.y, -100.0f, 100.0f);
	ImGui::SliderFloat("Z", &m_lightPos.z, -100.0f, 100.0f);
	
	ImGui::Text("Color Options");
	ImGui::ColorEdit4("Light Albedo", m_lightColor);
	ImGui::ColorEdit4("Sphere Color", m_sphereColor);

	ImGui::Text("Camera Position");
	ImGui::SliderFloat("x", &m_translation.x, -50.0f, 50.0f);
	ImGui::SliderFloat("y", &m_translation.y, -50.0f, 50.0f);
	ImGui::SliderFloat("z", &m_translation.z, -50.0f, 50.0f);
}
