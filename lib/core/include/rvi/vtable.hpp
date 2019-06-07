#pragma once

#include <functional>

namespace rvi
{
    template<typename T>
    struct vtable
    {
        template<typename... TArgs>
        using VT_ENTRY = std::function<void(T&, TArgs...)>;

        template<typename TRet, typename ...TArgs>
        using VT_ENTRY_RET = std::function<TRet(T&, TArgs...)>;

        bool initialized = false;
    };
}