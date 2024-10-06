#pragma once

namespace lib {

class Reflectable {
public:
    virtual const char* GetClassName() const = 0;
};

}  // namespace lib