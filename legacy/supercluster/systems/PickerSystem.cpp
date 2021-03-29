///
/// PickerSystem.cpp
/// supercluster
///
/// Refer to LICENSE.txt for more details.
///

#include <galaxy/core/World.hpp>

#include "../components/Picker.hpp"

#include "PickerSystem.hpp"

using namespace galaxy;

namespace sc
{
	void PickerSystem::update(core::World& world, const double dt)
	{
		world.each([&](const ecs::Entity entity) {
			if (!world.get<Picker>())
			{
			}
		});

		// clang-format off
		


			world.operate<components::Renderable, components::Transform>([&](const ecs::Entity entity, components::Renderable* renderable, components::Transform* transform) -> void
				{
					RenderData data
					{
						.m_entity = entity,
						.m_type = renderable->m_type,
						.m_z_level = renderable->m_z_level,
						.m_transform = transform
					};

					if (renderable->m_type == graphics::Renderables::BATCHED)
					{
						graphics::Renderer::m_batch->add(world.get<components::BatchedSprite>(entity), transform, renderable->m_z_level);
					}
					else
					{
						m_sorted.emplace_back(data);
					}
				});
		// clang-format on

		if (!graphics::Renderer::m_batch->empty())
		{
			graphics::Renderer::m_batch->calculate();
			graphics::Renderer::submit_batched_sprite(camera);
		}

		std::sort(std::execution::par, m_sorted.begin(), m_sorted.end(), [&](const auto& left, const auto& right) {
			return left.m_z_level < right.m_z_level;
		});

		for (const auto& data : m_sorted)
		{
			auto* shader = SL_HANDLE.shaderbook()->get(world.get<components::ShaderID>(data.m_entity)->m_shader_id);
			shader->bind();
			shader->set_uniform("u_cameraProj", camera.get_proj());
			shader->set_uniform("u_cameraView", camera.get_transform());

			switch (data.m_type)
			{
				case graphics::Renderables::POINT:
					graphics::Renderer::submit_point(world.get<components::Point>(data.m_entity), data.m_transform, shader);
					break;

				case graphics::Renderables::LINE:
					graphics::Renderer::submit_line(world.get<components::Line>(data.m_entity), data.m_transform, shader);
					break;

				case graphics::Renderables::CIRCLE:
					graphics::Renderer::submit_circle(world.get<components::Circle>(data.m_entity), data.m_transform, shader);
					break;

				case graphics::Renderables::SPRITE:
					graphics::Renderer::submit_sprite(world.get<components::Sprite>(data.m_entity), data.m_transform, shader);
					break;

				case graphics::Renderables::TEXT:
					graphics::Renderer::submit_text(world.get<components::Text>(data.m_entity), data.m_transform, shader);
					break;

				case graphics::Renderables::POLYGON:
					graphics::Renderer::submit_polygon(world.get<components::Polygon>(data.m_entity), data.m_transform, shader);
					break;

				case graphics::Renderables::ELLIPSE:
					graphics::Renderer::submit_ellipse(world.get<components::Ellipse>(data.m_entity), data.m_transform, shader);
					break;
			}
		}

		m_sorted.clear();
		graphics::Renderer::m_batch->clear_sprites();
	}
} // namespace sc