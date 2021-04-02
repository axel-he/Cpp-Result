// SPDX-License-Identifier: MIT

#include "Result.hpp"
using namespace Result;

#include <cassert>
#include <cmath>

static const int ERR_DIVISION_BY_ZERO = 1;

static FnResult<double> _Division(double dividend, double divisor) {
    if (divisor == 0) {
        return Err(ERR_DIVISION_BY_ZERO);
    }

    return Ok(dividend / divisor);
}

static FnResult<double> _DivisionRounded(double dividend, double divisor) {
    return _Division(dividend, divisor).touch_value([](auto &value) {
        value = round(value);
    });
}

int main(int argc, char *argv[]) {
    // failed result
    {
        auto result = _DivisionRounded(2.0, 0.0);

        assert(result.success() == false);
        // assert(result.value() == 0.5); /* would throw */
        assert(result.has_error() == true);
        assert(result.error().value() == ERR_DIVISION_BY_ZERO);
        // assert(result.get_value_or_throw() == 0.5); /* would throw */
    }

    // success result
    {
        auto result = _DivisionRounded(10.0, 4.0); // 2.5 = 3.0 rounded

        assert(result.success() == true);
        assert(result.value() == 3.0);
        assert(result.has_error() == false);
        // assert(result.error()); /* would throw */
    }

    return 0;
}
