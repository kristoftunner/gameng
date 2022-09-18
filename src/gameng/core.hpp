#pragma once

#include "log.hpp"

#define GAMENG_BIND_FN(fn) std::bind(&fn, this, std::placeholders::_1)

