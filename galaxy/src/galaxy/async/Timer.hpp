///
/// Timer.hpp
/// galaxy
///
/// Refer to LICENSE.txt for more details.
///

#ifndef GALAXY_ASYNC_TIMER_HPP_
#define GALAXY_ASYNC_TIMER_HPP_

#include <functional>

namespace galaxy
{
	namespace async
	{
		///
		/// Simple timer class.
		///
		class Timer final
		{
		public:
			///
			/// Constructor.
			///
			Timer() noexcept;

			///
			/// Destructor.
			///
			~Timer();

			///
			/// Make function repeat itself instead of running once.
			///
			/// \param repeat True to repeat.
			///
			void set_repeating(const bool repeat) noexcept;

			///
			/// \brief Run a function on a precision timer.
			///
			/// The function runs on a thread so do not run any thread dependent code.
			///
			/// \param func Function to call on thread.
			/// \param delay Delay until function is called. In milliseconds.
			///
			template<typename Lambda>
			void set(Lambda&& func, const std::uint32_t delay) noexcept;

			///
			/// Call to update timer count.
			///
			/// \param dt Total time to accumulate every time update() is called.
			///
			void update(const double dt);

			///
			/// Start timer.
			///
			void start();

			///
			/// Stop timer.
			///
			void stop();

		private:
			///
			/// Copy constructor.
			///
			Timer(const Timer&) = delete;

			///
			/// Copy assignment operator.
			///
			Timer& operator=(const Timer&) = delete;

		private:
			///
			/// Is function repeating on thread.
			///
			bool m_repeat;

			///
			/// Is timer stopped.
			///
			bool m_stopped;

			///
			/// Time passed.
			///
			double m_time_passed;

			///
			/// Current delay on timer.
			///
			std::uint32_t m_delay;

			///
			/// Callback function.
			///
			std::function<void(void)> m_callback;
		};

		template<typename Lambda>
		inline void Timer::set(Lambda&& func, const std::uint32_t delay) noexcept
		{
			m_callback = func;
			m_delay    = delay;
		}
	} // namespace async
} // namespace galaxy

#endif