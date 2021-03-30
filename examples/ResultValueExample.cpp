// SPDX-License-Identifier: MIT

#include "Result.hpp"
using namespace Result;

#include <cassert>

static const int ERR_DIVISION_BY_ZERO = 1;

static FnResult<double> _Division(double dividend, double divisor) {
    if (divisor == 0) {
        return Err(ERR_DIVISION_BY_ZERO);
    }

    return Ok(dividend / divisor);
}

int main(int argc, char *argv[]) {
    // failed result
    {
        auto result = _Division(2.0, 0.0);

        assert(result.success() == false);
        // assert(result.value() == 0.5); /* would throw */
        assert(result.has_error() == true);
        assert(result.error().value() == ERR_DIVISION_BY_ZERO);
    }

    // success result
    {
        auto result = _Division(1.0, 2.0);

        assert(result.success() == true);
        assert(result.value() == 0.5);
        assert(result.has_error() == false);
        // assert(result.error()); /* would throw */
    }

    return 0;
}
