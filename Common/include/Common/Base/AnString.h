#ifndef AN_STRING_H
#define AN_STRING_H

#include <Common/Base/ShareContextBase.h>

namespace Common
{
    class COMMON_API AnString : public Common::ShareContextBase<std::string>
    {
    public:
        AnString() = default;
        explicit AnString(const std::string& value) : Common::ShareContextBase<std::string>(value) {}
        explicit AnString(std::string&& value) : Common::ShareContextBase<std::string>(std::move(value)) {}
    };
}

#endif // AN_STRING_H