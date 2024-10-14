#pragma once

#include "Logger/LogLevel.h"
#include "Logger/Logger.h"

#define PB_ASSERT(expr)                \
    do {                               \
        if (!(expr)) {                 \
            LOG_ERROR("asert", #expr); \
            __debugbreak();            \
        }                              \
    } while (0)

#define PB_ASSERT_MSG(expr, category, msg) \
    do {                                   \
        if (!(expr)) {                     \
            LOG_ERROR(category, msg);      \
            __debugbreak();                \
        }                                  \
    } while (0)

#define PB_WARNING(expr)              \
    do {                              \
        if (!expr) {                  \
            LOG_WARN("waring", #expr) \
        }                             \
    }

#define PB_WARNING_MSG(expr, category, msg) \
    do {                                    \
        if (!(expr)) {                      \
            LOG_WARN(category, msg);        \
            __debugbreak();                 \
        }                                   \
    } while (0)
