// SPDX-License-Identifier: MIT

#include "Result.hpp"
using namespace Result;

#include <cassert>

static const int ERR_NON_ZERO = 1;

static FnResult<> _CheckNonZero(int val) {
    if (val == 0) {
        return Err(ERR_NON_ZERO);
    }

    return Ok();
}

int main(int argc, char *argv[]) {
    // failed result
    {
        auto result = _CheckNonZero(0);

        assert(result.success() == false);
        assert(result.has_error() == true);
        assert(result.error().value() == ERR_NON_ZERO);
    }

    // success result
    {
        auto result = _CheckNonZero(1);

        assert(result.success() == true);
        assert(result.has_error() == false);
        // assert(result.error()); /* would throw */
    }

    return 0;
}
