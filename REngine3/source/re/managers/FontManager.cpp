//
//  FontManager.cpp
//  REngine3
//
//  Created by reworks on 22/09/2017.
//  Copyright (c) 2017 reworks. All rights reserved.
//

#include <allegro5/allegro_ttf.h>

#include "re/services/VFS.hpp"
#include "re/services/ServiceLocator.hpp"

#include "FontManager.hpp"

namespace re
{
	FontManager::~FontManager()
	{
		for (auto& it : m_fontMap)
		{
			al_destroy_font(it.second);
		}

		m_fontMap.clear();
	}

	void FontManager::add(const std::string& font, const std::string& id, int size)
	{
		m_fontMap.emplace(id, al_load_ttf_font_f(Locator::get<VFS>()->open(font, "r"), nullptr, size, NULL));
	}

	ALLEGRO_FONT* FontManager::get(const std::string& id)
	{
		return m_fontMap[id];
	}
}