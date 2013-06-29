// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_ASSETS_INTERNAL_COMMON
#define SSVS_ASSETS_INTERNAL_COMMON

#include <memory>

namespace ssvs
{
	namespace Internal
	{
		template<typename T> using Uptr = std::unique_ptr<T>;
		enum class Mode{Load, Open, Image, Samples, Shader};

		template<bool> struct ShaderDisambiguationTag {};
		typedef ShaderDisambiguationTag<true> ShaderFromMemory;
		typedef ShaderDisambiguationTag<false> ShaderFromPath;
	}
}

#endif
