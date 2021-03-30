// SPDX-License-Identifier: MIT
/**
 * This file contains a header-only class `Result` class.
 * Requires C++17 or higher.
 */
#pragma once

#include <functional>
#include <optional>
#include <system_error>
#include <variant>

namespace Result {

template <typename _ValueType = std::monostate,
          typename _ErrorType = std::error_code>
class FnResult : public std::optional<_ValueType> {
  public:
    typedef std::optional<_ValueType> _BaseType;

  protected:
    std::optional<_ErrorType> _error;

  public:
    using _BaseType::_BaseType;
    FnResult(const _ErrorType &err) noexcept : _error(err) {}
    FnResult(const FnResult<std::monostate, _ErrorType> &obj)
        : _error(obj.error()) {}

    inline _ValueType &get_value_or_throw() const {
        if (_ResultType::has_error()) {
            throw_error();
        }
        return _BaseType::value();
    }

    inline _ErrorType const &error() const { return _error.value(); }

    inline bool has_error() const noexcept { return _error.has_value(); }

    inline bool success() const noexcept { return !has_error(); }

    inline FnResult &throw_on_error() const {
        if (has_error()) {
            throw std::system_error(_error);
        }
    }

    inline FnResult &on_success(std::function<void(const _ValueType &)> fn) {
        if (success()) {
            fn(value());
        }
        return *this;
    }

    inline FnResult &on_success(std::function<void(void)> fn) {
        if (success()) {
            fn();
        }
        return *this;
    }

    inline FnResult &on_error(std::function<void(const _ErrorType &err)> fn) {
        if (!success()) {
            fn(error());
        }
        return *this;
    }
};

static inline FnResult<> Ok() { return FnResult<>(); }

template <typename _ValueType>
static inline FnResult<_ValueType> Ok(const _ValueType &value) {
    return FnResult<_ValueType>(value);
}

static inline FnResult<>
Err(int errorCode, const std::error_category &cat = std::generic_category()) {
    return FnResult<>(std::error_code(errorCode, cat));
}

template <typename _ErrorType>
static inline FnResult<std::monostate, _ErrorType> Err(const _ErrorType &err) {
    return FnResult<std::monostate, _ErrorType>(err);
}

} // namespace Result
