//
//  Window.hpp
//  REngine3
//
//  Created by reworks on 19/09/2016.
//  Copyright (c) 2017 reworks. All rights reserved.
//

#ifndef RENGINE3_WINDOW_HPP_
#define RENGINE3_WINDOW_HPP_

#include <allegro5/events.h>
#include <allegro5/bitmap.h>
#include <allegro5/display.h>

namespace re
{
	class Window
	{
	public:
		///
		/// \brief Sets up window.
		/// 
		/// Sets up all the data for the allegro window such as rendering.
		///
		/// \param width Window width.
		/// \param height Window height.
		/// \param fullscreen Should the window be fullscreen on startup, true or false.
		/// \param msaa Enable or disable MultiSample AntiAliasing. 1 is true, 0 is false.
		/// \param msaaValue Strength of MSAA. 2, 4, 8, 16 are valid values. Set to 0 if msaa is disabled.
		/// \param title Window title. Must be smaller than 255 characters.
		/// \param icon Path to window icon. Must be 512x512.
		///
		Window(int width, int height, bool fullscreen, int msaa, int msaaValue, const std::string& title, const std::string& icon);

		///
		/// Cleans up the window.
		///
		~Window();

		///
		/// Toggle window between fullscreen and windowed.
		///
		/// \param onoff Boolean. True or False.
		///
		void toggleFullscreen(bool onoff);

		///
		/// Sets m_running to false, to close application.
		///
		void close();

		///
		/// See if the window is still running.
		///
		/// \return Const boolean.
		///
		bool isOpen() const;

		///
		/// Retrieves the internal display.
		///
		/// \return Returns pointer to ALLEGRO_DISPLAY.
		///
		ALLEGRO_DISPLAY* getDisplay();

		///
		/// Retrieves the internal event queue.
		///
		/// \return Returns pointer to ALLEGRO_EVENT_QUEUE.
		///
		ALLEGRO_EVENT_QUEUE* getEvents();

	private:
		bool m_running;
		ALLEGRO_BITMAP* m_icon;
		ALLEGRO_DISPLAY* m_display;
		ALLEGRO_EVENT_QUEUE* m_events;
	};
}

#endif
