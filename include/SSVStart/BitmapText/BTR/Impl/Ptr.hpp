// Copyright (c) 2013-2015 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_BITMAPTEXT_BTR_IMPL_PTR
#define SSVS_BITMAPTEXT_BTR_IMPL_PTR

#include "SSVStart/Global/Typedefs.hpp"

namespace ssvs
{
	namespace BTR
	{
		template<typename T> class Ptr
		{
			private:
				T* ptr;

			public:
				#if defined(SSVU_DEBUG)
					inline Ptr() noexcept : ptr{nullptr} { }
				#else
					inline Ptr() noexcept { }
				#endif

				inline Ptr(T* mX) noexcept : ptr{mX} { }

				inline auto& operator*() noexcept				{ SSVU_ASSERT(ptr != nullptr); return *ptr; }
				inline const auto& operator*() const noexcept	{ SSVU_ASSERT(ptr != nullptr); return *ptr; }
				inline T* operator->() noexcept					{ SSVU_ASSERT(ptr != nullptr); return ptr; }
				inline T* operator->() const noexcept			{ SSVU_ASSERT(ptr != nullptr); return ptr; }

				inline operator T*() const noexcept { return ptr; }
		};
	}
}

#endif
