///
/// VertexArrary.hpp
/// quasar
///
/// Apache 2.0 LICENSE.
/// Refer to LICENSE.txt for more details.
///

#ifndef QUASAR_VERTEXARRAY_HPP_
#define QUASAR_VERTEXARRAY_HPP_

#include "qs/vertex/IndexBuffer.hpp"
#include "qs/vertex/VertexBuffer.hpp"
#include "qs/vertex/VertexLayout.hpp"

///
/// Core namespace.
///
namespace qs
{
	///
	/// Abstraction for OpenGL vertex array objects.
	///
	class VertexArray final
	{
	public:
		///
		/// Default constructor.
		///
		VertexArray() noexcept;

		///
		/// Creation constructor (without indexbuffer).
		///
		/// \param vb VertexBufferObject to bind to VertexArrayObject.
		/// \param layout VertexLayout to specify for this VertexArrayObject.
		///
		explicit VertexArray(const qs::VertexBuffer& vb, const qs::VertexLayout& layout) noexcept;

		///
		/// Creation constructor (with indexbuffer).
		///
		/// \param vb VertexBufferObject to bind to VertexArrayObject.
		/// \param ib IndexBufferObject to bind to VertexArrayObject.
		/// \param layout VertexLayout to specify for this VertexArrayObject.
		///
		explicit VertexArray(const qs::VertexBuffer& vb, const qs::IndexBuffer& ib, const qs::VertexLayout& layout) noexcept;

		///
		/// Destroys buffer.
		///
		~VertexArray() noexcept;

		///
		/// Create vertex array.
		///
		/// \param vb VertexBufferObject to bind to VertexArrayObject.
		/// \param layout VertexLayout to specify for this VertexArrayObject.
		///
		void create(const qs::VertexBuffer& vb, const qs::VertexLayout& layout) noexcept;

		///
		/// Add an index buffer to the vertex array layout.
		///
		/// \param ib IndexBufferObject to bind to VertexArrayObject.
		///
		void addIndexBuffer(const qs::IndexBuffer& ib);

		///
		/// Bind the current vertex array to current GL context.
		///
		void bind() const noexcept;

		///
		/// Unbind the current vertex array to current GL context.
		///
		void unbind() const noexcept;

	private:
		///
		/// ID returned by OpenGL when generating vertex array.
		///
		unsigned int m_id;
	};
}

#endif