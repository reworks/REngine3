///
/// ParallaxSystem.hpp
/// starlight
///
/// Created by reworks on 04/02/2018.
/// MIT License.
/// Refer to LICENSE.txt for more details.
///

#ifndef STARLIGHT_PARALLAXSYSTEM_HPP_
#define STARLIGHT_PARALLAXSYSTEM_HPP_

#include "sl/types/System.hpp"

namespace sl
{
	///
	/// Process's parallax entities, that have a ParallaxComponent.
	///
	class ParallaxSystem final : public System
	{
	public:
		///
		/// Default Constructor.
		///
		ParallaxSystem() = default;

		///
		/// Destructor.
		///
		~ParallaxSystem() noexcept override = default;

	private:
		///
		/// \brief Update the system.
		///
		/// Dont actually call this, this is called by the world automatically.
		///
		/// \param dt Delta Time from update loop.
		/// \param registry Default entity registry.
		///
		void update(const double dt, entt::DefaultRegistry& registry) override;
	};
}

#endif