///
/// Renderer.cpp
/// quasar
///
/// Apache 2.0 LICENSE.
/// Refer to LICENSE.txt for more details.
///

#include <glm/mat4x4.hpp>

#include "qs/text/Text.hpp"
#include "qs/graphics/Line.hpp"
#include "qs/graphics/Sprite.hpp"
#include "qs/graphics/Circle.hpp"
#include "qs/graphics/Point.hpp"
#include "qs/graphics/Camera.hpp"
#include "qs/core/RenderTexture.hpp"
#include "qs/renderer/LightSource.hpp"
#include "qs/graphics/SpriteBatch.hpp"

#include "Renderer.hpp"

///
/// Core namespace.
///
namespace qs
{
	void Renderer::drawPoint(qs::Point& point, qs::Shader& shader) noexcept
	{
		point.bind();
		shader.setUniform("u_point_size", point.getSize());

		glDrawArrays(GL_POINTS, 0, 1);
	}

	void Renderer::drawLine(qs::Line& line) noexcept
	{
		line.bind();

		glDrawArrays(GL_LINES, 0, 2);
	}

	void Renderer::drawCircle(qs::Circle& circle) noexcept
	{
		circle.bind();

		glDrawArrays(GL_LINE_LOOP, 0, circle.getCount());
	}

	void Renderer::drawVAToTexture(qs::VertexArray& va, qs::IndexBuffer& ib, qs::RenderTexture& rt, qs::Shader& shader) noexcept
	{
		shader.bind();
		shader.setUniform("u_projection", rt.getProjection());
		va.bind();

		glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, nullptr);
	}

	void Renderer::drawSprite(qs::Sprite& sprite, qs::Shader& shader) noexcept
	{
		sprite.update();

		shader.setUniform("u_transform", sprite.getTransformation());
		shader.setUniform<float>("u_width", static_cast<float>(sprite.getWidth()));
		shader.setUniform<float>("u_height", static_cast<float>(sprite.getHeight()));

		sprite.bind();
		
		glDrawElements(GL_TRIANGLES, sprite.getCount(), GL_UNSIGNED_INT, nullptr);
	}

	void Renderer::drawSpriteBatch(qs::SpriteBatch& spritebatch, qs::Shader& shader) noexcept
	{
		spritebatch.applyTransforms();

		shader.setUniform<float>("u_width", static_cast<float>(spritebatch.getWidth()));
		shader.setUniform<float>("u_height", static_cast<float>(spritebatch.getHeight()));

		spritebatch.bind();

		glDrawElements(GL_TRIANGLES, spritebatch.getCount(), GL_UNSIGNED_INT, nullptr);
	}

	void Renderer::drawSpriteToTexture(qs::Sprite& sprite, qs::RenderTexture& rt, qs::Shader& shader) noexcept
	{
		shader.bind();

		shader.setUniform("u_projection", rt.getProjection());
		shader.setUniform("u_transform", sprite.getTransformation());
		shader.setUniform<float>("u_width", static_cast<float>(sprite.getWidth()));
		shader.setUniform<float>("u_height", static_cast<float>(sprite.getHeight()));

		sprite.bind();

		glDrawElements(GL_TRIANGLES, sprite.getCount(), GL_UNSIGNED_INT, nullptr);
	}

	void Renderer::drawText(qs::Text& text, qs::Shader& shader) noexcept
	{
		drawSprite(text.asSprite(), shader);
	}

	void Renderer::drawScene(qs::Sprite& sprite, qs::Camera& camera, qs::LightSource& ls) noexcept
	{
		ls.m_shader.bind();

		ls.m_shader.setUniform("u_light_pos", glm::vec3(ls.m_pos.x, camera.getHeight() - ls.m_pos.y, ls.m_zLevel));
		ls.m_shader.setUniform("u_light_colour", ls.m_lightColour);
		ls.m_shader.setUniform("u_ambient_colour", ls.m_ambientColour);
		ls.m_shader.setUniform("u_falloff", ls.m_falloff);
		ls.m_shader.setUniform("u_width", static_cast<float>(sprite.getWidth()));
		ls.m_shader.setUniform("u_height", static_cast<float>(sprite.getHeight()));
		ls.m_shader.setUniform<glm::mat4>("u_cameraProj", camera.getProj());
		ls.m_shader.setUniform<glm::mat4>("u_cameraView", camera.getTransformation());
		ls.m_shader.setUniform("u_window_resolution", camera.getWidth(), camera.getHeight());

		sprite.bind();

		glDrawElements(GL_TRIANGLES, sprite.getCount(), GL_UNSIGNED_INT, nullptr);
	}
}