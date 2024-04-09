#pragma once

#include <string>

namespace lib {
using U8String = std::u8string;
using U8StringView = std::u8string_view;
using U16String = std::u16string;
using U16StringView = std::u16string_view;
using U32String = std::u32string;
using U32StringView = std::u32string_view;

using String = U8String;
using StringView = U8StringView;
}
