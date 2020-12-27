///
/// SourceManipulator.hpp
/// galaxy
///
/// Refer to LICENSE.txt for more details.
///

#ifndef GALAXY_AUDIO_SOURCE_SOURCEMANIPULATOR_HPP_
#define GALAXY_AUDIO_SOURCE_SOURCEMANIPULATOR_HPP_

#include <AL/al.h>
#include <AL/alc.h>

#include "galaxy/meta/Concepts.hpp"

namespace galaxy
{
	namespace audio
	{
		///
		/// Origin of the audio sound.
		///
		class SourceManipulator
		{
		public:
			///
			/// Virtual destructor.
			///
			virtual ~SourceManipulator();

			///
			/// \brief Play source.
			///
			/// Plays source from beginning or pause point.
			///
			void play();

			///
			/// Pause source.
			///
			void pause();

			///
			/// \brief Stop source.
			///
			/// Starts again from beginning when play() or resume() are called.
			///
			void stop();

			///
			/// Rewind source to beginning.
			///
			void rewind();

			///
			/// Audio pitch.
			///
			/// \param pitch Multiplier value. I.e. 0.5f is a *0.5 multiplier.
			///
			void set_pitch(const float pitch);

			///
			/// Audio gain.
			///
			/// \param gain Multiplier value. I.e. 0.5f is a *0.5 multiplier.
			///
			void set_gain(const float gain);

			///
			/// \brief Set RollOff factor for source.
			///
			/// \param factor Floating point factor value.
			///
			void set_rolloff_factor(const float factor);

			///
			/// \brief Set maximum distance from which there is no attenuation afterwards.
			///
			/// \param distance Floating point distance value.
			///
			void set_max_distance(const float distance);

			///
			/// \brief Configure audio cone.
			///
			/// \param outerGain The gain when outside the oriented cone.
			/// \param innerAngle The gain when inside the oriented cone.
			/// \param outerAngle Outer angle of the sound cone, in degrees. Default is 360.
			///
			void set_cone(const float outer_gain, const float inner_angle, const float outer_angle = 360.0f);

			///
			/// \brief Specifies the current location of the object in the world coordinate system.
			///
			/// \param x position in world.
			/// \param y position in world.
			/// \param z position in world.
			///
			void set_position(const float x, const float y, const float z);

			///
			/// \brief Specifies the current velocity (speed and direction) of the object, in theworld coordinate system
			///
			/// \param x X velocity.
			/// \param y Y velocity.
			/// \param z Z velocity.
			///
			void set_velocity(const float x, const float y, const float z);

			///
			/// \brief Source is directional. The sound emission is presumed to be symmetric around the direction vector.
			///
			/// \param x position in world.
			/// \param y position in world.
			/// \param z position in world.
			///
			void set_direction(const float x, const float y, const float z);

			///
			/// \brief Should the source repeat upon reaching the end.
			///
			/// \param True to repeat.
			///
			void set_looping(bool looping);

		protected:
			///
			/// Default constructor.
			///
			SourceManipulator();

			///
			/// Copy constructor.
			///
			SourceManipulator(const SourceManipulator&) = delete;

			///
			/// Move constructor.
			///
			SourceManipulator(SourceManipulator&&);

			///
			/// Copy assignment operator.
			///
			SourceManipulator& operator=(const SourceManipulator&) = delete;

			///
			/// Move assignment operator.
			///
			SourceManipulator& operator=(SourceManipulator&&);

			///
			/// Set source to manipulate.
			///
			/// \param source Pointer to source handle in OpenAL.
			///
			void set_source_to_manipulate(const ALuint source);

			///
			/// Retrieve OpenAL source state.
			///
			/// \return Integer of enum AL_SOURCE_STATE.
			///
			ALint get_state();

			///
			/// Pointer to source being used internally.
			///
			ALuint m_source;
		};
	} // namespace audio

} // namespace galaxy

#endif