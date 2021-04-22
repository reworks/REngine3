///
/// DefaultFramebuffer.hpp
/// galaxy
///
/// Refer to LICENSE.txt for more details.
///

#ifndef GALAXY_GRAPHICS_SHADER_DEFAULTFRAMEBUFFER_HPP_
#define GALAXY_GRAPHICS_SHADER_DEFAULTFRAMEBUFFER_HPP_

#include <string>

namespace galaxy
{
	namespace shaders
	{
		///
		/// Default Framebuffer vertex shader.
		///
		inline const std::string default_framebuffer_vert = R"(
			#version 450 core
			layout(location = 0) in vec2 l_pos;
			layout(location = 1) in vec2 l_texels;

			out vec2 io_texels;
			out float io_opacity;

			uniform mat4 u_projection;
			uniform mat4 u_transform;
			uniform float u_width;
			uniform float u_height;
			uniform float u_opacity;

			void main()
			{
				gl_Position =  u_projection * u_transform * vec4(l_pos, 0.0, 1.0);

				io_texels = vec2(l_texels.x / u_width, 1.0 - (l_texels.y / u_height));
				io_opacity = u_opacity;
			}
		)";

		///
		/// Default Framebuffer fragment shader.
		///
		inline const std::string default_framebuffer_frag = R"(
			#version 450 core
			
			#define GAMMA_CORRECTION 2.2
			
			in vec2 io_texels;
			in float io_opacity;

			out vec4 io_frag_colour;

			uniform sampler2D u_texture;

			void main()
			{
				vec4 tex = texture(u_texture, io_texels);
                vec3 corrected = pow(tex.rgb, vec3(GAMMA_CORRECTION));

				float opacity = tex.a * io_opacity;
				io_frag_colour = vec4(corrected, opacity);
			}
		)";
	} // namespace shaders
} // namespace galaxy

#endif