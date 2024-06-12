#include "TestClearColor.h"
#include <GL/glew.h>
#include "macros.h"
#include "imgui/imgui.h"

namespace test{

	TestClearColor::TestClearColor() {
	}

	TestClearColor::~TestClearColor() {
	}

	void TestClearColor::OnUpdate(float deltaTime) {
	}

	void TestClearColor::OnRender() {
		GLCall(glClearColor(m_Color[0], m_Color[1], m_Color[2], m_Color[3]));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));
	}

	void TestClearColor::OnImGUIRender() {
		ImGui::ColorEdit4("clear color", m_Color);
	}
}