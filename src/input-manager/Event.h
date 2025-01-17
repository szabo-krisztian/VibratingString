#pragma once

#include <vector>
#include <memory>
#include <algorithm>

#include "Callback.h"

namespace tlr
{

template<typename... Args>
class Event
{
public:
    using MethodPtr = void (*)(Args...);

    void RegisterCallback(MethodPtr pMethod)
    {
        _pCallbacks.push_back(std::make_unique<Callback<MethodPtr>>(pMethod));
    }

    void UnregisterCallback(MethodPtr pMethod)
    {
        Callback<MethodPtr> pCallback(pMethod);
        EraseCallback(&pCallback);
    }
    
    template<typename C>
    using MemberMethodPtr = void (C::*)(Args...);

    template<typename C>
    void RegisterCallback(C *object, MemberMethodPtr<C> pMemberMethod)
    {
        _pCallbacks.push_back(std::make_unique<Callback<MemberMethodPtr<C>>>(object, pMemberMethod));
    }

    template<typename C>
    void UnregisterCallback(C *object, MemberMethodPtr<C> pMemberMethod)
    {
        Callback<MemberMethodPtr<C>> pCallback(object, pMemberMethod);
        EraseCallback(&pCallback);
    }

    void Raise(Args... args) const
    {
        for (auto const& pCallback : _pCallbacks)
        {
            pCallback->Call(std::forward<Args>(args)...);
        }
    }

private:
    std::vector<std::unique_ptr<ICallback<Args...>>> _pCallbacks;

    void EraseCallback(ICallback<Args...> const* pCallbackToDelete)
    {
        auto it = std::find_if(_pCallbacks.cbegin(), _pCallbacks.cend(),
        [&pCallbackToDelete](auto const& pCallback)
        {
            return pCallback->Equals(*pCallbackToDelete);
        });
        if (it != _pCallbacks.cend())
        {
            _pCallbacks.erase(it);
        }
    }
};

} // namespace tlr