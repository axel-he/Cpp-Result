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
        auto result = _Division(1.0, 0.0)
                          .on_success([](auto &value) {
                              assert(false); /* should not be called */
                          })
                          .on_error([](auto &err) {
                              assert(err.value() == ERR_DIVISION_BY_ZERO);
                          });
    }

    // success result
    {
        auto result = _Division(1.0, 2.0)
                          .on_success([](auto &value) { assert(value == 0.5); })
                          .on_error([](auto &err) {
                              assert(false); /* should not be called */
                          });
    }

    return 0;
}
