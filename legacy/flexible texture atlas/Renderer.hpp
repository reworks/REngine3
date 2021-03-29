///
/// Renderer.hpp
/// galaxy
///
/// Refer to LICENSE.txt for more details.
///

#ifndef GALAXY_GRAPHICS_RENDERER_HPP_
#define GALAXY_GRAPHICS_RENDERER_HPP_

#include <string>
#include <vector>

#include "galaxy/components/Sprite.hpp"
#include "galaxy/components/Transform.hpp"
#include "galaxy/ecs/Entity.hpp"
#include "galaxy/graphics/Camera.hpp"
#include "galaxy/graphics/SpriteBatch.hpp"

namespace galaxy
{
	namespace components
	{
		class Point;
		class Line;
		class Circle;
		class Sprite;
		class Text;
	} // namespace components

	namespace graphics
	{
		class ParticleGenerator;
		class Shader;
		class RenderTexture;

		///
		/// OpenGL 2D renderer for drawing VA with transforms, shaders and textures.
		///
		class Renderer final
		{
		public:
			static void init(const unsigned int max_quads, std::string_view batch_shader);

			static void draw_point(components::Point* point, components::Transform* transform, Shader* shader);
			static void draw_line(components::Line* line, components::Transform* transform, Shader* shader);
			static void draw_circle(components::Circle* circle, components::Transform* transform, Shader* shader);
			static void draw_sprite(components::Sprite* sprite, components::Transform* transform, Shader* shader);
			static void draw_text(components::Text* text, components::Transform* transform, Shader* shader);

			static void submit_to_batch(components::BatchedSprite* sprite, components::Transform* transform, const int z_level);
			static void draw_batches(Camera& camera);

			static void draw_sprite_to_texture(components::Sprite* sprite, components::Transform* transform, Shader* shader, RenderTexture* target);
			static void draw_particles(graphics::ParticleGenerator* gen, Camera& camera);

			inline static std::vector<Shader*> m_post_shaders;

		private:
			inline static unsigned int m_maxquads;
			inline static res::TextureAtlas* m_atlas;
			inline static robin_hood::unordered_flat_map<std::size_t, SpriteBatch> m_batchmap;
			inline static Shader* m_batch_shader;
		};
	} // namespace graphics
} // namespace galaxy

#endif