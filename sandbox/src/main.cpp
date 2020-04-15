///
/// main.cpp
/// Sandbox
///
/// Apache 2.0 LICENSE.
/// Refer to LICENSE.txt for more details.
///

#include <iostream>

#include <protostar/system/Keys.hpp>
#include <qs/utils/Error.hpp>
#include <qs/core/WindowSettings.hpp>
#include <qs/core/Texture.hpp>
#include <qs/core/Window.hpp>
#include <qs/renderer/Renderer.hpp>
#include <qs/graphics/Camera.hpp>
#include <qs/graphics/Sprite.hpp>
#include <qs/core/Shader.hpp>
#include <qs/core/RenderTexture.hpp>
#include <qs/graphics/TextureAtlas.hpp>

int main(int argsc, char* argsv[])
{
	qs::Error::handle().setQSCallback([](std::string_view file, unsigned int line, std::string_view message) -> void
		{
			std::cout << "[Quasar Error] File: " << file << " Line: " << line << " Message: " << message << std::endl;
		});

	qs::WindowSettings::s_msaa = 4;
	qs::WindowSettings::s_vsync = false;
	qs::WindowSettings::s_srgb = false;
	qs::WindowSettings::s_aspectRatioX = -1;
	qs::WindowSettings::s_aspectRatioY = -1;
	qs::WindowSettings::s_rawMouseInput = true;

	qs::Window window;

	if (!window.create("TestBed", 1024, 768))
	{
		std::cout << "Window creation failed!" << std::endl;
	}

	qs::Error::handle().setGLCallback([](GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) -> void
		{
			std::cout << "[GL_MSG]: Severity: " << severity << " Message: " << message << std::endl;
		});

	qs::Renderer renderer;

	// Shaders
	qs::Shader shader(std::filesystem::path("bin/sprite.vert"), std::filesystem::path("bin/sprite.frag"));
	qs::Shader rttshader(std::filesystem::path("bin/rtt.vert"), std::filesystem::path("bin/rtt.frag"));

	// Texture atlas is allowed to bind/unbind shaders - the only one allowed.
	qs::TextureAtlas atlas;
	atlas.add("bin/wall_2.png");
	atlas.create(window, renderer, rttshader);
	atlas.save("bin/atlas");

	qs::Sprite wall;
	wall.load("bin/wall.png");
	wall.create(qs::BufferType::DYNAMIC);
	wall.move(0.0f, 0.0f);

	auto atlasSpr = atlas.getSprite();

	qs::Camera camera; //left, right, bottom, top
	camera.create(0.0f, window.getWidth(), window.getHeight(), 0.0f);
	camera.setSpeed(0.2f);

	shader.bind();

	// Loop
	while (window.isOpen())
	{
		glfwPollEvents();

		int esc = glfwGetKey(window.getWindow(), GLFW_KEY_ESCAPE);
		if (esc == GLFW_PRESS)
		{
			window.close();
		}

		int w = glfwGetKey(window.getWindow(), GLFW_KEY_W);
		if (w == GLFW_PRESS)
		{
			camera.onKeyDown({ protostar::Keys::W });
		}

		int s = glfwGetKey(window.getWindow(), GLFW_KEY_S);
		if (s == GLFW_PRESS)
		{
			camera.onKeyDown({ protostar::Keys::S });
		}

		int a = glfwGetKey(window.getWindow(), GLFW_KEY_A);
		if (a == GLFW_PRESS)
		{
			camera.onKeyDown({ protostar::Keys::A });
		}

		int d = glfwGetKey(window.getWindow(), GLFW_KEY_D);
		if (d == GLFW_PRESS)
		{
			camera.onKeyDown({ protostar::Keys::D });
		}

		int q = glfwGetKey(window.getWindow(), GLFW_KEY_Q);
		if (q == GLFW_PRESS)
		{
			camera.onKeyDown({ protostar::Keys::Q });
		}

		int e = glfwGetKey(window.getWindow(), GLFW_KEY_E);
		if (e == GLFW_PRESS)
		{
			camera.onKeyDown({ protostar::Keys::E });
		}

		camera.update(1.0);
		shader.setUniform<glm::mat4>("u_cameraProj", camera.getProj());
		shader.setUniform<glm::mat4>("u_cameraView", camera.getTransformation());

		// Render.
		window.begin(qs::Colours::White);

		renderer.drawSprite(atlasSpr, shader);
		//renderer.drawSprite(wall, shader);

		window.end();
	}

	// Exit.
	window.destroy();

	return 0;
}