///
/// RenderableComponent.hpp
/// starlight
///
///  Created by reworks on 12/01/2018.
///  Copyright (c) 2018+ reworks.
///  Refer to LICENSE.txt for more details.
///

#include "imgui/imgui.h"

#include "RenderableComponent.hpp"

namespace sl
{
	void RenderableComponent::debug()
	{
		ImGui::Text("Flag component.");
	}
}