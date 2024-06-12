#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <functional>

namespace test {

	class Test {
	public:
		Test() {};
		virtual ~Test() {};

		virtual void OnUpdate(float deltaTime) {}
		virtual void OnRender() {}
		virtual void OnImGUIRender() {}
	};

	class TestMenu : public Test {
	public:
		TestMenu(Test*& currentTestPointer);
		~TestMenu();

		void OnImGUIRender() override;

		template<typename T, typename... Args>
		void RegisterTest(const std::string& name, Args&&... args) {
			std::cout << "registering test " << name << std::endl;

			m_Tests.push_back(std::make_pair(name, [&args...]() { return new T(args...); }));
		}

	private:
		Test*& m_currentTest;
		std::vector<std::pair<std::string, std::function<Test* ()>>> m_Tests;
	};

}