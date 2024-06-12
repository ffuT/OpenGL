#pragma once

#include "Test.h"

namespace test{

	class TestClearColor : public Test{
	public:
		TestClearColor();
		~TestClearColor();
		
		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGUIRender() override;
	private:
		float m_Color[4] = { 1.0f, 0.2f, 1.0f, 1.0f };

	
	};

}

