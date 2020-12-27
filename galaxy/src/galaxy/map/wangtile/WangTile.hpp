///
/// WangTile.hpp
/// galaxy
///
/// Refer to LICENSE.txt for more details.
///

#ifndef GALAXY_MAP_WANGTILE_WANGTILE_HPP_
#define GALAXY_MAP_WANGTILE_WANGTILE_HPP_

#include <nlohmann/json_fwd.hpp>

namespace galaxy
{
	namespace map
	{
		///
		/// Represents a Wang tile, by referring to a tile in the tileset and associating it with a certain Wang ID.
		///
		class WangTile final
		{
		public:
			///
			/// Default constructor.
			///
			WangTile();

			///
			/// Parse constructor.
			///
			/// \param json JSON structure/array containing WangTile json.
			///
			explicit WangTile(const nlohmann::json& json);

			///
			/// Destructor.
			///
			~WangTile();

			///
			/// Parses json structure to member values; etc.
			///
			/// \param json JSON structure containing WangTile json.
			///
			void parse(const nlohmann::json& json);

			///
			/// Is flipped diagonally.
			///
			/// \return True if flipped.
			///
			[[nodiscard]] const bool flipped_diagonally() const;

			///
			/// Is flipped horizontally.
			///
			/// \return True if flipped.
			///
			[[nodiscard]] const bool flipped_horizontally() const;

			///
			/// Get local tile id.
			///
			/// \return Const int.
			///
			[[nodiscard]] const int get_tile_id() const;

			///
			/// Is flipped vertically.
			///
			/// \return True if flipped.
			///
			[[nodiscard]] const bool flipped_vertically() const;

			///
			/// Get wang colour indexes.
			///
			/// \return Std::vector array.
			///
			[[nodiscard]] const auto& get_indexes() const;

		private:
			///
			/// Tile is flipped diagonally.
			///
			bool m_diagonal_flip;

			///
			/// Tile is flipped horizontally.
			///
			bool m_horizontal_flip;

			///
			/// Local ID of tile.
			///
			int m_tile_id;

			///
			/// Tile is flipped vertically.
			///
			bool m_vertical_flip;

			///
			/// Array of Wang colour indexes.
			///
			std::vector<int> m_wang_indexes;
		};
	} // namespace map
} // namespace galaxy

#endif