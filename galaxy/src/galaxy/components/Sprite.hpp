///
/// Sprite.hpp
/// galaxy
///
/// Refer to LICENSE.txt for more details.
///

#ifndef GALAXY_COMPONENTS_SPRITE_HPP_
#define GALAXY_COMPONENTS_SPRITE_HPP_

#include <nlohmann/json_fwd.hpp>

#include "galaxy/graphics/texture/Texture.hpp"
#include "galaxy/graphics/vertex/VertexData.hpp"

namespace galaxy
{
	namespace components
	{
		///
		/// Everything you need to draw a sprite.
		///
		class Sprite final : public graphics::VertexData, public graphics::Texture
		{
		public:
			///
			/// Constructor.
			///
			Sprite() noexcept;

			///
			/// JSON constructor.
			///
			/// \param json JSON defining object.
			///
			Sprite(const nlohmann::json& json);

			///
			/// Move constructor.
			///
			Sprite(Sprite&&) noexcept;

			///
			/// Move assignment operator.
			///
			Sprite& operator=(Sprite&&) noexcept;

			///
			/// Destructor.
			///
			~Sprite() noexcept = default;

			///
			/// \brief Creates the internal vertex array.
			///
			/// BufferType Fixed or dynamic buffer.
			///
			/// \param tex_x Optional texture x pos.
			/// \param tex_y Optional texture y pos.
			///
			void create(const float tex_x = 0.0f, const float tex_y = 0.0f);

			///
			/// Activate sprite context.
			///
			void bind() noexcept override;

			///
			/// Deactivate sprite context.
			///
			void unbind() noexcept override;

		private:
			///
			/// Copy constructor.
			///
			Sprite(const Sprite&) = delete;

			///
			/// Copy assignment operator.
			///
			Sprite& operator=(const Sprite&) = delete;
		};
	} // namespace components
} // namespace galaxy

#endif