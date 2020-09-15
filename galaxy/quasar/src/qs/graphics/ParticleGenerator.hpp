///
/// ParticleGenerator.hpp
/// quasar
///
/// Refer to LICENSE.txt for more details.
///

#ifndef QUASAR_PARTICLEGENERATOR_HPP_
#define QUASAR_PARTICLEGENERATOR_HPP_

#include <protostar/graphics/Rect.hpp>
#include <protostar/math/Random.hpp>

#include "qs/core/Shader.hpp"
#include "qs/texture/Texture.hpp"

///
/// Core namespace.
///
namespace qs
{
	struct DirectionalGen
	{
		DirectionalGen() = delete;
	};

	struct CircularGen
	{
		CircularGen() = delete;
	};

	struct RandomDirectionalGen
	{
		RandomDirectionalGen() = delete;
	};

	struct RandomCircularGen
	{
		RandomCircularGen() = delete;
	};

	template<typename Type>
	concept particle_type = (std::is_same<Type, DirectionalGen>::value ||
				 std::is_same<Type, CircularGen>::value ||
				 std::is_same<Type, RandomDirectionalGen>::value ||
				 std::is_same<Type, RandomCircularGen>::value);

	///
	///
	///
	template<particle_type ParticleGenType>
	class ParticleGenerator final
	{
	public:
		ParticleGenerator(std::string_view particle_sheet, qs::Shader* shader);

		ParticleGenerator(const ParticleGenerator&) = delete;

		ParticleGenerator(ParticleGenerator&&);

		ParticleGenerator& operator=(const ParticleGenerator&) = delete;

		ParticleGenerator& operator=(ParticleGenerator&&);

		~ParticleGenerator();

		void configure(std::string_view particle_type, const unsigned int amount);
		void define(std::string_view particle_type, pr::Rect<int>& region);

	private:
		ParticleGenerator() = default;
		void bind();
		void unbind();

		qs::Texture m_texture;
		qs::Shader* m_shader;

		std::unordered_map<std::string, pr::Rect<int>> m_texture_regions;
	};

	template<particle_type ParticleGenType>
	ParticleGenerator<ParticleGenType>::ParticleGenerator(std::string_view particle_sheet, qs::Shader* shader)
	    : m_shader {shader}
	{
		m_texture.load(particle_sheet);
	}

	template<particle_type ParticleGenType>
	inline ParticleGenerator<ParticleGenType>::ParticleGenerator(ParticleGenerator&& pg)
	{
		this->m_texture         = std::move(pg.m_texture);
		this->m_shader          = pg.m_shader;
		this->m_texture_regions = std::move(pg.m_texture_regions);

		pg.m_shader = nullptr;
	}

	template<particle_type ParticleGenType>
	inline ParticleGenerator<ParticleGenType>& ParticleGenerator<ParticleGenType>::operator=(ParticleGenerator&& pg)
	{
		if (this != &pg)
		{
			this->m_texture         = std::move(pg.m_texture);
			this->m_shader          = pg.m_shader;
			this->m_texture_regions = std::move(pg.m_texture_regions);

			pg.m_shader = nullptr;
		}

		return *this;
	}

	template<particle_type ParticleGenType>
	inline ParticleGenerator<ParticleGenType>::~ParticleGenerator()
	{
		pg.m_shader = nullptr;
		m_texture_regions.clear();
	}

	template<particle_type ParticleGenType>
	void ParticleGenerator<ParticleGenType>::configure(std::string_view particle_type, const unsigned int amount)
	{
		if constexpr (std::is_same<ParticleGenType, DirectionalGen>::value)
		{
			for (unsigned int count = 0; count < amount; count++)
			{
				auto val = protostar::random<unsigned int>(0, 25);
				?
			}
		}
		else if constexpr (std::is_same<ParticleGenType, CircularGen>::value)
		{
		}
		else if constexpr (std::is_same<ParticleGenType, RandomDirectionalGen>::value)
		{
		}
		else if constexpr (std::is_same<ParticleGenType, RandomCircularGen>::value)
		{
		}
	}

	template<particle_type ParticleGenType>
	void ParticleGenerator<ParticleGenType>::define(std::string_view particle_type, pr::Rect<int>& region)
	{
		m_texture_regions.emplace(static_cast<std::string>(particle_type), std::move(region));
	}

	template<particle_type ParticleGenType>
	void ParticleGenerator<ParticleGenType>::bind()
	{
	}

	template<particle_type ParticleGenType>
	void ParticleGenerator<ParticleGenType>::unbind()
	{
	}
} // namespace qs

#endif