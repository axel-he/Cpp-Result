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

    inline const _ValueType &get_value_or_throw() const {
        this->throw_on_error();
        return _BaseType::value();
    }

    inline _ErrorType const &error() const { return _error.value(); }

    inline bool has_error() const noexcept { return _error.has_value(); }

    inline bool success() const noexcept { return !has_error(); }

    inline const FnResult &throw_on_error() const {
        if (has_error()) {
            throw std::system_error(this->error());
        }
        return *this;
    }

    inline const FnResult &
    on_success(std::function<void(const _ValueType &)> fn) const noexcept {
        if (success()) {
            fn(value());
        }
        return *this;
    }

    inline const FnResult &
    on_success(std::function<void(void)> fn) const noexcept {
        if (success()) {
            fn();
        }
        return *this;
    }

    inline const FnResult &
    on_error(std::function<void(const _ErrorType &err)> fn) const noexcept {
        if (!success()) {
            fn(error());
        }
        return *this;
    }

    inline bool operator==(const _ValueType &value) {
        return this->success() && (this->value() == value);
    }

    inline bool operator!=(const _ValueType &value) {
        return !(*this == value);
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

template <typename _LeftErrorType, typename _RightErrorType>
static bool
operator==(const FnResult<std::monostate, _LeftErrorType> &left,
           const FnResult<std::monostate, _RightErrorType> &right) noexcept {
    const bool success = left.success() && right.success();
    return success;
}

template <typename _ValueType, typename _LeftErrorType,
          typename _RightErrorType>
static bool
operator==(const FnResult<_ValueType, _LeftErrorType> &left,
           const FnResult<_ValueType, _RightErrorType> &right) noexcept {
    const bool success = left.success() && right.success();
    return success && (left.value() == right.value());
}

template <typename _ValueType, typename _LeftErrorType,
          typename _RightErrorType>
static bool
operator!=(const FnResult<_ValueType, _LeftErrorType> &left,
           const FnResult<_ValueType, _RightErrorType> &right) noexcept {
    return !(left == right);
}

} // namespace Result
