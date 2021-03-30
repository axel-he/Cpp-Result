# Cpp-Result

Implementation for a *Result* type. It can be used to return values or error output for functions. The type contains a value type and an error type. The value type and error type can be specified with template parameters. By default the error type is a `std::error_code`.

Requires C++17 or higher.

## Use it in your own *C++* project ##

You can use the header file `src/Result.hpp` inside your project. The *Result* type is implemented as C++ class: `Result::FnResult<...>`.

```c++
#include "Result.hpp"
using namespace Result;

FnResult<> result;
```

## Basic usage ##

Implement function with *Result* type:

```c++
#include "Result.hpp"
using namespace Result;

FnResult<> _SomeFunction() {
  if(/*error*/) {
    return Err(/* error code */);
  }
  
  if(/* success */) {
    return Ok();
  }
}
```

Use returned result:

```c++
auto result = _ResultingFunction();

// has succeeded?
result.success();

// has failed?
result.has_error();

// get resulting value (throw on error)
val = result.value();

// get resulting value or fallback value on error
val = result.value_or(/* fallback-value */);

// get error code or throw if succeeded
result.error();

// throw error if resulting in error
result.throw_on_error();
```

