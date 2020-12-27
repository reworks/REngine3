///
/// Image.hpp
/// galaxy
///
/// Refer to LICENSE.txt for more details.
///

#ifndef GALAXY_UI_WIDGETS_IMAGE_HPP_
#define GALAXY_UI_WIDGETS_IMAGE_HPP_

#include "galaxy/events/MouseMoved.hpp"
#include "galaxy/graphics/sprite/BatchedSprite.hpp"
#include "galaxy/ui/Widget.hpp"

namespace galaxy
{
	namespace ui
	{
		///
		/// \brief Simple image widget.
		///
		/// ANY FUNCTIONS YOU BIND TO AN EVENT ARE NOT CALLED ON THE MAIN THREAD.
		/// DO NOT CALL GL CODE IN EVENT FUNCTIONS.
		///
		class Image final : public Widget, public graphics::BatchedSprite
		{
		public:
			///
			/// Constructor.
			///
			Image() = default;

			///
			/// Copy constructor.
			///
			Image(const Image&) = delete;

			///
			/// Copy assignment operator.
			///
			Image& operator=(const Image&) = delete;

			///
			/// Destructor.
			///
			virtual ~Image() = default;

			///
			/// Use theme texture from atlas.
			///
			/// \param name Name of the texture to use.
			///
			using graphics::BatchedSprite::create;
			void create(std::string_view name);

			///
			/// Sets position without moving the object.
			///
			/// \param x X position to set object to.
			/// \param y Y position to set object to.
			///
			void set_pos(const float x, const float y) override;

			///
			/// Triggered when mouse moves.
			///
			/// \param mme Mouse Moved Event.
			///
			void on_event(const events::MouseMoved& mme);

			///
			/// \brief Update widget logic.
			///
			/// YOU MUST NOT CALL ANY GL CODE FROM THIS FUNCTION. THIS FUNCTION IS CALLED FROM A SEPERATE THREAD.
			///
			/// \param dt Delta Time from gameloop.
			///
			void update(const double dt) override;

			///
			/// \brief Render the widget.
			///
			/// THIS FUNCTION IS CALLED ON THE MAIN THREAD. PUT YOUR GL CODE HERE.
			///
			/// \param camera View camera to use when rendering.
			///
			void render(graphics::Camera& camera) override;
		};
	} // namespace ui
} // namespace galaxy

#endif