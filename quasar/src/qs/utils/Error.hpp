///
/// Error.hpp
/// quasar
///
/// Apache 2.0 LICENSE.
/// Refer to LICENSE.txt for more details.
///

#ifndef QUASAR_ERROR_HPP_
#define QUASAR_ERROR_HPP_

#include <string>
#include <vector>
#include <functional>
#include <string_view>

#include <glad/glad.h>

///
/// Core namespace.
///
namespace qs
{
	///
	/// Allows for Quasar to manage error in a way that allows for other libraries to interact easily.
	///
	class Error final
	{
	public:
		///
		/// Resets current error message and clears history. 
		///
		~Error() noexcept;

		///
		/// Static handle to error class.
		///
		static qs::Error& handle() noexcept;

		///
		/// \brief Set the OpenGL debug information callback.
		///
		/// \param callback Function pointer to set. See: http://docs.gl/gl4/glDebugMessageCallback.
		///
		void setGLCallback(void(*callback)(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)) noexcept;

		///
		/// \brief Set the callback function for errors in Quasar. Adds error message to history.
		///
		/// Callback function has params: file (std::string_view), line (unsigned int), message (std::string_view).
		/// 
		/// \param callback Function pointer to callback function.
		///
		void setQSCallback(std::function<void(std::string_view, unsigned int, std::string_view)> callback) noexcept;

		///
		/// Execute callback function. Adds error message to history. Make sure a callback is set or this does nothing.
		///
		/// \param File File error is happening in.
		/// \param line Line the error is happening on.
		/// \param message What is the error.
		///
		void callback(std::string_view file, unsigned int line, std::string_view message) noexcept;

		///
		/// Retrieve all error messages.
		///
		/// \return Returns const reference of history as a std::vector<std::string>.
		///
		const std::vector<std::string>& getHistory() const noexcept;

		///
		/// Resets history. Does not reset callback.
		///
		void clear() noexcept;

	private:
		///
		/// Private Default Constructor.
		/// Ensures class can't be constructed.
		///
		Error() noexcept;

		///
		/// Private copy constructor.
		/// Ensures class can't be copied.
		///
		Error(const Error &) = default;

		///
		/// Private move constructor.
		/// Ensures class can't be moved.
		///
		Error(Error &&) = default;

	private:
		///
		/// Contains a history of all error messages.
		///
		std::vector<std::string> m_history;

		///
		/// Callback method for error handling.
		///
		std::function<void(std::string_view, unsigned int, std::string_view)> m_callback;		
	};
}

#endif