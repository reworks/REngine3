///
/// UI.cpp
/// celestial
///
/// Refer to LICENSE.txt for more details.
///

#include "UI.hpp"

///
/// Core namespace.
///
namespace celestial
{
	UI::UI(protostar::ProtectedDouble* deltaTime) noexcept
		:m_isDestroyed(false), m_dt(deltaTime), m_counter(0)
	{
		m_running.set(true);
		m_mainLoop.set([&](protostar::ProtectedBool* threadPoolFinished)
		{
			while (m_running.get() && threadPoolFinished->get())
			{
				processEvents();
				update(m_dt);
			}
		});
	}

	UI::~UI() noexcept
	{
		if (!m_isDestroyed)
		{
			destroy();
		}
	}

	void UI::render(qs::Renderer& renderer, qs::Shader& shader) noexcept
	{
		// Renderer has no modifiable data, and since we are accessing
		// sequencitally, no need for mutex or syncing.
		if (m_visible.get())
		{
			std::lock_guard<std::mutex> l_lock(m_widgetMutex);
			for (auto&& widget : m_widgets)
			{
				widget->render(renderer, shader);
			}
		}
	}

	void UI::setVisibility(const bool isVisible) noexcept
	{
		m_visible.set(isVisible);
	}

	protostar::Task* UI::getTask() noexcept
	{
		return &m_mainLoop;
	}

	void UI::remove(const unsigned int id) noexcept
	{
		std::lock_guard<std::mutex> l_lock(m_widgetMutex);

		// Don't erase because that will mess up ordering.
		m_widgets[id].reset();
		m_widgets[id] = nullptr;

		m_free.push_back(id);
	}

	void UI::destroy() noexcept
	{
		m_running.set(false);
		m_mainLoop.waitUntilFinished();

		{
			std::lock_guard<std::mutex> l_lock(m_widgetMutex);

			for (auto&& widget : m_widgets)
			{
				widget.reset();
			}

			m_widgets.clear();
		}

		m_isDestroyed = true;
	}

	void UI::processEvents() noexcept
	{
		if (m_visible.get())
		{
			std::lock_guard<std::mutex> l_lock(m_eventMutex);
			m_uiEventManager.trigger();
		}
	}

	void UI::update(protostar::ProtectedDouble* deltaTime) noexcept
	{
		// Ok to pass pointer here without mutex since deltaTime value can only
		// be accessed through a mutex protected get().
		if (m_visible.get())
		{
			std::lock_guard<std::mutex> l_lock(m_widgetMutex);
			for (auto&& widget : m_widgets)
			{
				widget->update(deltaTime);
			}
		}
	}
}