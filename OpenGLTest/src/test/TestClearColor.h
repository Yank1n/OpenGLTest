#pragma once

#include "Test.h"

namespace test
{

	class TestClearColor : public Test
	{
	public:
		TestClearColor();
		~TestClearColor();

		void OnUpdate(float deltatime) override;
		void OnRender() override;
		void OnImGUIRender() override;
	private:
		float m_clearColor[4];
	};

}