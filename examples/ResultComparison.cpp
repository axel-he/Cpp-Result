// SPDX-License-Identifier: MIT

#include "Result.hpp"
using namespace Result;

#include <cassert>

static const int ERR_DIVISION_BY_ZERO = 1;
static const int ERR_NON_ZERO = 2;

static FnResult<> _CheckNonZero(int val) {
    if (val == 0) {
        return Err(ERR_NON_ZERO);
    }

    return Ok();
}

static FnResult<double> _Division(double dividend, double divisor) {
    if (divisor == 0) {
        return Err(ERR_DIVISION_BY_ZERO);
    }

    return Ok(dividend / divisor);
}

int main(int argc, char *argv[]) {
    // valued result
    {
        auto result_fail1 = _Division(2.0, 0.0);
        auto result_fail2 = _Division(2.0, 0.0);
        auto result_ok1 = _Division(2.0, 1.0);
        auto result_ok2 = _Division(2.0, 1.0);
        auto result_ok3 = _Division(4.0, 1.0);

        assert(result_fail1 !=
               result_fail2); /* error results always compare to FALSE */
        assert(result_ok1 == result_ok2); /* compare value */
        assert(result_ok1 != result_ok3); /* compare value */

        // compare by value
        assert(result_ok1 == static_cast<double>(2.0));
        assert(result_ok1 != static_cast<double>(0.5));
        assert(result_fail1 != static_cast<double>(2.0));
    }

    // non-value result
    {
        auto result_fail1 = _CheckNonZero(0);
        auto result_fail2 = _CheckNonZero(0);
        auto result_ok1 = _CheckNonZero(-1);
        auto result_ok2 = _CheckNonZero(1);

        assert(result_fail1 !=
               result_fail2); /* error results always compare to FALSE */
        assert(result_ok1 == result_ok2);   /* compare success */
        assert(result_ok1 != result_fail2); /* error compared to success */
    }

    return 0;
}
