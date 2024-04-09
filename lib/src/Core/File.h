#pragma once

#include "Core/IntrusiveRefCounter.h"

namespace lib {
class File : public IntrusiveRefCounter<File> {
public:
    File() = default;

};
}
