///
/// Renderer3D.hpp
/// galaxy
///
/// Refer to LICENSE.txt for more details.
///

#ifndef GALAXY_GRAPHICS_RENDERER3D_HPP_
#define GALAXY_GRAPHICS_RENDERER3D_HPP_

#include <span>

#include <glad/glad.h>

#include "galaxy/graphics/camera/Camera3D.hpp"
#include "galaxy/graphics/GeomBuffer.hpp"

#define RENDERER_3D galaxy::graphics::Renderer3D::inst

namespace galaxy
{
	namespace components
	{
		class Model;
	} // namespace components

	namespace light
	{
		class Material;
		struct Directional;
		struct Point;
		struct Spot;
		class Object;
	} // namespace light

	namespace systems
	{
		class RenderSystem3D;
	} // namespace systems

	namespace graphics
	{
		class Mesh;
		class Shader;
		class Skybox;

		///
		/// OpenGL 3D renderer.
		///
		class Renderer3D final
		{
			friend class systems::RenderSystem3D;

		public:
			///
			/// Destructor.
			///
			~Renderer3D() noexcept;

			///
			/// Retrieve Renderer instance.
			///
			/// \return Reference to renderer.
			///
			[[nodiscard]] static Renderer3D& inst() noexcept;

			///
			/// Init renderer.
			///
			/// \param width Usually screen width.
			/// \param height Usually screen height.
			///
			void init(const int width, const int height);

			///
			/// Prepare framebuffer to recieve render commands.
			///
			void prepare() noexcept;

			///
			/// Bind to take render commands.
			///
			void bind() noexcept;

			///
			/// Unbind and finish rendering.
			///
			void unbind() noexcept;

			///
			/// Render contents to active framebuffer.
			///
			void render();

			///
			/// Add post processing shader.
			///
			/// \param vs Vertex shader source.
			/// \param fs Fragment shader source.
			///
			void add_renderpass(const std::string& vs, const std::string& fs);

			///
			/// Resize framebuffer.
			///
			/// \param width New framebuffer width. Usually screen width.
			/// \param height New framebuffer height. Usually screen height.
			///
			void resize(const int width, const int height);

			///
			/// Forward render an object.
			///
			/// \param renderable Renderable object corresponding to a RENDERER_3D draw call.
			/// \param shader Shader to draw renderable with.
			///
			template<meta::is_class Renderable>
			void forward_render(Renderable* renderable, Shader* shader);

			///
			/// Execute forward render draw calls.
			///
			void do_forward_render();

			///
			/// Reserve GPU memory for Uniform Buffer.
			///
			/// \param index Index binding assigned to this UBO in shader(s).
			/// \param size Size (in bytes) to reserve.
			///
			void reserve_ubo(const std::size_t index, const unsigned int size);

			///
			/// Reserve GPU memory for Uniform Buffer.
			///
			/// \param index Index binding assigned to this UBO in shader(s).
			/// \param size Size (in bytes) to reserve.
			///
			void reserve_ssbo(const std::size_t index, const unsigned int size);

			///
			/// Bind Uniform Buffer Object as active.
			///
			/// \param index Index binding assigned to this UBO in shader(s).
			///
			void bind_ubo(const std::size_t index);

			///
			/// Unbind UBO.
			///
			void unbind_ubo();

			///
			/// Bind Shader Storage Buffer Object as active.
			///
			/// \param index Index binding assigned to this SSBO in shader(s).
			///
			void bind_ssbo(const std::size_t index);

			///
			/// Unbind SSBO.
			///
			void unbind_ssbo();

			///
			/// Copy data into existing UBO buffer.
			///
			/// \param index Index binding assigned to this UBO in shader(s).
			/// \param offset Offset in UBO memory to buffer this data at.
			/// \param size Count of data elements.
			/// \param data Data buffer to copy.
			///
			template<typename Type>
			void sub_buffer_ubo(const std::size_t index, const unsigned int offset, const unsigned int size, Type* data);

			///
			/// Copy data into existing SSBO buffer.
			///
			/// \param index Index binding assigned to this SSBO in shader(s).
			/// \param offset Offset in SSBO memory to buffer this data at.
			/// \param size Count of data elements.
			/// \param data Data buffer to copy.
			///
			template<typename Type>
			void sub_buffer_ssbo(const std::size_t index, const unsigned int offset, const unsigned int size, Type* data);

			///
			/// Recreate SSBO buffer and copy new data into it.
			///
			/// \param index Index binding assigned to this SSBO in shader(s).
			/// \param data Data buffer to assign.
			///
			template<typename Type>
			void buffer_ssbo(const std::size_t index, std::span<Type> data);

			///
			/// Draw a mesh.
			///
			/// \param mesh Mesh to draw.
			/// \param material Material to draw mesh with.
			///
			void draw_mesh_deferred(Mesh* mesh, light::Material* material);

			///
			/// Draw skybox.
			///
			/// \param skybox Skybox to draw.
			/// \param shader Shader to draw skybox with.
			///
			void draw(Skybox* skybox, Shader* shader);

			///
			/// Draw a light cube for visualization purposes.
			///
			/// \param light Object data to draw.
			/// \param shader Shader to draw cube with.
			///
			void draw(light::Object* light, Shader* shader);

			///
			/// \brief Clean up renderer gl buffers.
			///
			/// Includes SSBOs and UBOs.
			///
			void clean_up();

			///
			/// Get G-Buffer.
			///
			/// \return Reference to the g-buffer.
			///
			[[nodiscard]] GeomBuffer& get_gbuffer() noexcept;

		private:
			///
			/// Constructor.
			///
			Renderer3D() noexcept;

		private:
			///
			/// "G-Buffer" object.
			///
			GeomBuffer m_gbuffer;

			///
			/// OpenGL ubo/ssbo ids.
			///
			std::vector<unsigned int> m_buffers;

			///
			/// Render pass screen quad verter buffer object.
			///
			unsigned int m_screen_vbo;

			///
			/// Render pass screen quad vertex array object.
			///
			unsigned int m_screen_vao;

			///
			/// Currently bound framebuffer.
			///
			int m_bound_fb;

			///
			/// List of shaders to do render pass over.
			///
			std::vector<Shader> m_render_passes;

			///
			/// Forward render calls.
			///
			std::vector<std::function<void(void)>> m_forward_calls;
		};

		template<meta::is_class Renderable>
		inline void Renderer3D::forward_render(Renderable* renderable, Shader* shader)
		{
			m_forward_calls.emplace_back([this, renderable, shader]() {
				draw(renderable, shader);
			});
		}

		template<typename Type>
		inline void Renderer3D::sub_buffer_ubo(const std::size_t index, const unsigned int offset, const unsigned int size, Type* data)
		{
			bind_ubo(index);
			glBufferSubData(GL_UNIFORM_BUFFER, offset, size * sizeof(Type), data);
			unbind_ubo();
		}

		template<typename Type>
		inline void Renderer3D::sub_buffer_ssbo(const std::size_t index, const unsigned int offset, const unsigned int size, Type* data)
		{
			bind_ssbo(index);
			glBufferSubData(GL_SHADER_STORAGE_BUFFER, offset, size * sizeof(Type), data);
			unbind_ssbo();
		}

		template<typename Type>
		inline void Renderer3D::buffer_ssbo(const std::size_t index, std::span<Type> data)
		{
			bind_ssbo(index);

			GLint64 size = 0;
			glGetBufferParameteri64v(GL_SHADER_STORAGE_BUFFER, GL_BUFFER_SIZE, &size);

			if (size != data.size_bytes())
			{
				glInvalidateBufferData(m_buffers[index]);
				glBufferData(GL_SHADER_STORAGE_BUFFER, data.size_bytes(), data.data(), GL_DYNAMIC_DRAW);
			}
			else
			{
				glBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, data.size_bytes(), data.data());
			}

			unbind_ssbo();
		}
	} // namespace graphics
} // namespace galaxy

#endif