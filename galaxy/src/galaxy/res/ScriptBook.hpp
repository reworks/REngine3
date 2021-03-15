///
/// ScriptBook.hpp
/// galaxy
///
/// Refer to LICENSE.txt for more details.
///

#ifndef GALAXY_RES_SCRIPTBOOK_HPP_
#define GALAXY_RES_SCRIPTBOOK_HPP_

#include "galaxy/res/ResourceCache.hpp"

namespace galaxy
{
	namespace res
	{
		///
		/// Resource manager for lua scripts.
		///
		class ScriptBook final : public ResourceCache<std::string>
		{
		public:
			///
			/// Constructor.
			///
			ScriptBook() noexcept = default;

			///
			/// JSON constructor.
			///
			/// \param file JSON file to load.
			///
			ScriptBook(std::string_view file);

			///
			/// Destructor.
			///
			virtual ~ScriptBook() noexcept;

			///
			/// Create ScriptBook from JSON.
			///
			/// \param file JSON file to load.
			///
			void create_from_json(std::string_view file);

			///
			/// Run a script.
			///
			/// \param script_id ID of the script to run.
			///
			void run(std::string_view script_id);

			///
			/// Clean up.
			///
			void clear() noexcept override;

		private:
			///
			/// Copy constructor.
			///
			ScriptBook(const ScriptBook&) = delete;

			///
			/// Move constructor.
			///
			ScriptBook(ScriptBook&&) = delete;

			///
			/// Copy assignment operator.
			///
			ScriptBook& operator=(const ScriptBook&) = delete;

			///
			/// Move assignment operator.
			///
			ScriptBook& operator=(ScriptBook&&) = delete;
		};
	} // namespace res
} // namespace galaxy

#endif