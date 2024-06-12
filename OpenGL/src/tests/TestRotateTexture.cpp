#include "TestRotateTexture.h"

test::TestRotateTexture::TestRotateTexture(const int width, const int height, Renderer* renderer)
    : winWidth(width), winHeight(height), m_render(renderer), m_time(0) {

	m_layout.Push<float>(2);
	m_layout.Push<float>(2);
	m_va.AddBuffer(m_vb, m_layout);

	m_shader.Bind();
	m_texture.Bind(0);
	m_shader.SetUniform1i("u_Texture", 0);
}

test::TestRotateTexture::~TestRotateTexture(){
    
}

void test::TestRotateTexture::OnUpdate(float deltaTime){
    m_time += deltaTime;
}

void test::TestRotateTexture::OnRender(){
    glm::mat4 model = glm::translate(glm::mat4(1.0), translation);
    glm::mat4 mvp = proj * view * model;
    m_shader.SetUniformMat4f("u_MVP", mvp);
    m_render->Draw(m_va, m_ib, m_shader);
}

void test::TestRotateTexture::OnImGUIRender(){
    ImGui::Text("Fade Color");
    ImGui::SliderFloat("R", &r, 0.0f, 1.0f);
    ImGui::SliderFloat("G", &g, 0.0f, 1.0f);
    ImGui::SliderFloat("B", &b, 0.0f, 1.0f);

    ImGui::SliderInt("Rotation speed", &rotationSpeed, -50, 50);

    ImGui::Text("translation");
    ImGui::SliderFloat("x", &translation.x, 0.0f, (float) winWidth);
    ImGui::SliderFloat("y", &translation.y, 0.0f, (float) winHeight);

    m_shader.SetUniform4f("u_Color", r, g, b, 1.0f);
    m_shader.SetUniform1f("u_Time", m_time);
    m_shader.SetUniform1i("u_RotSpeed", rotationSpeed);
}
