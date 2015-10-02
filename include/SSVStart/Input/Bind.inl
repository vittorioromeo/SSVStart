// Copyright (c) 2013-2015 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_INPUT_BIND_INL
#define SSVS_INPUT_BIND_INL

namespace ssvs
{
namespace Input
{
    inline void Bind::setPriorityUser(SizeT mValue) noexcept
    {
        priorityUser = mValue;
        manager.mustSort = true;
    }
}
}

#endif
