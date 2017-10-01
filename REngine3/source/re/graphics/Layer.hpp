//
//  Layer.hpp
//  REngine3
//
//  Created by reworks on 11/08/2016.
//  Copyright (c) 2017 reworks. All rights reserved.
//

#ifndef RENGINE3_LAYER_HPP_
#define RENGINE3_LAYER_HPP_

#include <map>
#include <memory>
#include <vector>
#include <string>

namespace re
{
	typedef std::vector<std::pair<sf::Drawable*, sf::Transformable*>> RenderableContainer;

	class Layer
	{
	public:
		/*
		* IMPORTS: none
		* EXPORTS: none
		* PURPOSE: Clean up the entitys.
		*/
		~Group() override;

		/*
		* IMPORTS: TextComponent
		* EXPORTS: none
		* PURPOSE: Add a textocomponent to the group.
		*/
		void addDrawable(const std::string& name, sf::Drawable* drawable, sf::Transformable* transformable);
		
		/*
		* IMPORTS: RenderTarget and RenderState
		* EXPORTS: none
		* PURPOSE: Inherited function. Not called by you, called by SFML internally.
		*/
		void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

		/*
		* IMPORTS: none
		* EXPORTS: none
		* PURPOSE: Get stored drawables.
		*/
		std::map<std::string, RenderableContainer>& getDrawableMap();

	private:
		std::map<std::string, RenderableContainer> m_drawable;
	};
}

#endif