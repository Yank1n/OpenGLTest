#include "TestTexture2D.h"
#include "Renderer.h"

namespace test
{
	TestTexture2D::TestTexture2D()
		: m_translationA(200, 200, 0), m_translationB(400, 200, 0),
		m_proj(glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f)),
		m_view(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f)))
	{
		float positions[] =
		{
			-50.0f, -50.0f,  0.0f, 0.0f,
			 50.0f, -50.0f,  1.0f, 0.0f,
			 50.0f,  50.0f,  1.0f, 1.0f,
			-50.0f,  50.0f,  0.0f, 1.0f,
		};

		unsigned int indices[] =
		{
			0, 1, 2,
			2, 3, 0,
		};

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		m_VAO = std::make_unique<VertexArray>();

		m_vertexBuffer = std::make_unique<VertexBuffer>(positions, sizeof(positions));

		VertexBufferLayout layout;
		layout.Push<float>(2);
		layout.Push<float>(2);

		m_VAO->AddBuffer(*m_vertexBuffer, layout);
		m_indexBuffer = std::make_unique<IndexBuffer>(indices, sizeof(indices) / sizeof(unsigned int));

		m_shader = std::make_unique<Shader>("res\\shaders\\Basic.shader");
		m_shader->Bind();
		m_shader->SetUniform4f("u_Color", 1.0f, 0.8f, 0.8f, 1.0f);

		m_texture = std::make_unique<Texture>("res\\textures\\images.png");
		m_shader->SetUniform1i("u_Texture", 0);
	}

	TestTexture2D::~TestTexture2D()
	{
	}

	void TestTexture2D::OnUpdate(float deltatime)
	{
	}

	void TestTexture2D::OnRender()
	{
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		Renderer renderer;

		m_texture->Bind();

		{
			glm::mat4 model = glm::translate(glm::mat4(1.0f), m_translationA);
			glm::mat4 mvp = m_proj * m_view * model;

			m_shader->Bind();

			m_shader->SetUniformMat4("u_MVP", mvp);
			renderer.Draw(*m_VAO, *m_indexBuffer, *m_shader);
		}

		{
			glm::mat4 model = glm::translate(glm::mat4(1.0f), m_translationB);
			glm::mat4 mvp = m_proj * m_view * model;

			m_shader->Bind();

			m_shader->SetUniformMat4("u_MVP", mvp);
			renderer.Draw(*m_VAO, *m_indexBuffer, *m_shader);
		}
	}

	void TestTexture2D::OnImGUIRender()
	{
		{
			ImGui::SliderFloat3("Translation A", &m_translationA.x, 0.0f, 960.0f);
			ImGui::SliderFloat3("Translation B", &m_translationB.x, 0.0f, 960.0f);
			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		}
	}
}
