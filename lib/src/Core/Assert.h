#pragma once

#include "Logger/Logger.h"
#include "Logger/LogLevel.h"

#define PB_ASSERT(expr) do { if (!(expr)) { __debugbreak(); } } while (0)
//#define PB_ASSERT_MSG(expr, msg) do { if (!(expr)) { LOG_ERROR("assert", msg); __debugbreak(); } } while (0)
#define PB_ASSERT_MSG(expr, category, msg) do { if (!(expr)) { LOG_ERROR(category, msg); __debugbreak(); } } while (0)