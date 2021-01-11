#pragma once

#include "imgui/imgui.h"

#include <functional>
#include <vector>

namespace test
{
	
	class Test
	{
	public:
		Test() {}
		virtual ~Test() {}

		virtual void OnUpdate(float deltatime) {}
		virtual void OnRender() {}
		virtual void OnImGUIRender() {}
	};

	class TestMenu : public Test
	{
	public:
		TestMenu(Test*& currentTestPointer);

		void OnImGUIRender() override;

		template<typename T>
		void RegisterTest(const std::string& name)
		{
			m_tests.push_back(std::make_pair(name, []() { return new T(); }));
		}
	private:
		Test*& m_currentTest;
		std::vector<std::pair<std::string, std::function<Test*()>>> m_tests;
	};

}