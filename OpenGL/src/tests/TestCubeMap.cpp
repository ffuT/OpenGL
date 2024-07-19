#include "TestCubeMap.h"

test::TestCubeMap::TestCubeMap(const int width, const int height, Renderer* renderer)
	: m_winWidth(width), m_winHeight(height), m_render(renderer)
	, m_proj(glm::perspective(glm::radians(45.0f), (float)m_winWidth / (float)m_winHeight, 0.1f, 100.0f))
	, m_view(glm::lookAt(glm::vec3(0, 0, .5), // Camera position in world space
						 glm::vec3(0, 0, 0),  // Look at point
						 glm::vec3(0, 1, 0))) // Up vector 
{
	GLCall(glDepthMask(GL_FALSE));

	m_layout.Push<float>(3);
	m_va.AddBuffer(m_vb, m_layout);

	m_shader.Bind();
	m_skybox.Bind(0);
	m_shader.SetUniform1i("u_skybox", 0);
}

test::TestCubeMap::~TestCubeMap(){
	GLCall(glDisable(GL_DEPTH_TEST));
}

void test::TestCubeMap::OnUpdate(float deltaTime){

}

void test::TestCubeMap::OnRender(){
	GLCall(glDepthFunc(GL_LEQUAL));

	m_shader.SetUniformMat4f("u_projection", m_proj);
	m_shader.SetUniformMat4f("u_view", m_view);
	
	glDrawArrays(GL_TRIANGLES, 0, 36);

	//m_render->Draw(m_va, m_ib, m_shader);

	GLCall(glDepthMask(GL_TRUE));
}

void test::TestCubeMap::OnImGUIRender(){

}
