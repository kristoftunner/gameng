#pragma once

#include <memory>

#define GAMENG_BIND_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace gameng
{
  template<typename T>
  using Scope = std::unique_ptr<T>;

  template<typename T>
  using Ref = std::shared_ptr<T>;

} // namespace gameng
