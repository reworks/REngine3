///
/// Meta.hpp
/// quasar
///
/// Apache 2.0 LICENSE.
/// Refer to LICENSE.txt for more details.
///

#ifndef QUASAR_META_HPP_
#define QUASAR_META_HPP_

///
/// Core namespace.
///
namespace qs
{
	///
	/// \brief Specifies a static buffer at compile time.
	///
	/// Cannot be instansiated.
	///
	struct DynamicBufferType
	{
		DynamicBufferType() = delete;
	};

	///
	/// \brief Specifies a dynamic buffer at compile time.
	///
	/// Cannot be instansiated.
	///
	struct StaticBufferType
	{
		StaticBufferType() = delete;
	};

	///
	/// \brief Specifies "position" vertex attribute type at compile time.
	///
	/// Cannot be instansiated.
	///
	struct PositionVAType
	{
		PositionVAType() = delete;
	};

	///
	/// \brief Specifies "colour" vertex attribute type at compile time.
	///
	/// Cannot be instansiated.
	///
	struct ColourVAType
	{
		ColourVAType() = delete;
	};

	///
	/// \brief Specifies "texel" vertex attribute type at compile time.
	///
	/// Cannot be instansiated.
	///
	struct TexelVAType
	{
		TexelVAType() = delete;
	};
}

#endif