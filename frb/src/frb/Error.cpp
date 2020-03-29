///
/// Error.cpp
/// context
///
/// Refer to LICENSE.txt for more details.
///

#include <iostream>

#include <AL/al.h>
#include <AL/alc.h>

#include "Error.hpp"

namespace frb
{
	std::string parseError(const std::string& message) noexcept
	{
		std::string msg = "OpenAL Error: " + message + " | " + alGetString(alGetError());
		return std::move(msg);
	}

	std::string errorCodeAsString(const int err) noexcept
	{
		std::string out = "";
		switch (err)
		{
		case AL_NO_ERROR:
			out = "AL_NO_ERROR";
			break;

		case AL_INVALID_NAME:
			out = "AL_INVALID_NAME";
			break;

		case AL_INVALID_ENUM:
			out = "AL_INVALID_ENUM";
			break;

		case AL_INVALID_VALUE:
			out = "AL_INVALID_VALUE";
			break;

		case AL_INVALID_OPERATION:
			out = "AL_INVALID_OPERATION";
			break;

		case AL_OUT_OF_MEMORY:
			out = "AL_OUT_OF_MEMORY";
			break;

		default:
			out = "AL_NO_ERROR";
			break;
		}

		return std::move(out);
	}
}