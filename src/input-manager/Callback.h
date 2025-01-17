#pragma once

#include <memory>

#include "ICallback.h"

namespace tlr
{

template<typename T>
class Callback;

template<typename... Args>
class Callback<void(*)(Args...)> final : public ICallback<Args...>
{
public:
    using MethodPtr = void(*)(Args...);

    Callback(MethodPtr pMethod) : _pMethod(pMethod) {}

    void Call(Args... args) override
    {
        _pMethod(std::forward<Args>(args)...);
    }

    bool Equals(ICallback<Args...> const& other) const override
    {
        if (auto otherObj = dynamic_cast<Callback const*>(&other))
        {
            return otherObj->_pMethod == _pMethod;
        }
        return false;
    }

private:
    MethodPtr _pMethod;
};

template<typename C, typename... Args>
class Callback<void (C::*)(Args...)> final : public ICallback<Args...>
{
public:
    using MemberMethodPtr = void (C::*)(Args...);

    Callback(C *object, MemberMethodPtr pMemberMethod) : _object(object), _pMemberMethod(pMemberMethod) {}

    void Call(Args... args) override
    {
        (_object->*_pMemberMethod)(std::forward<Args>(args)...);
    }

    bool Equals(ICallback<Args...> const& other) const override
    {
        if (auto otherObj = dynamic_cast<Callback const*>(&other))
        {
            return otherObj->_object == _object && otherObj->_pMemberMethod == _pMemberMethod;
        }
        return false;
    }

private:
    C *_object;
    MemberMethodPtr _pMemberMethod;
};

} // namespace tlr