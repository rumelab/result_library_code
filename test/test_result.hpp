#ifndef TEST_RESULT_HPP
#define TEST_RESULT_HPP

#include <Arduino.h>
#include <unity.h>
#include <result.hpp>

namespace RumeLab::Detail
{

    template <typename = void>
    auto test_result() -> void
    {
        using SampleResult = ::Result<uint8_t, String>;

        constexpr const uint8_t success_value = 12;
        auto success_result = SampleResult(success_value);
        TEST_ASSERT_EQUAL(true, bool(success_result));
        TEST_ASSERT_EQUAL_UINT8(success_value, success_result.unwrap_success());
        // success_result.unwrap_failure(); // Error, cannot unwrap failure value with success result.

        const auto failure_value = String("Hello world");
        auto failure_result = SampleResult(failure_value);
        TEST_ASSERT_EQUAL(false, bool(failure_result));
        TEST_ASSERT(failure_value == failure_result.unwrap_failure());

        // Make sure the result's value is movable.
        const String moved_failure_value = failure_result.unwrap_failure();
        TEST_ASSERT(failure_value != failure_result.unwrap_failure());

        // failure_result.unwrap_success(); // Error, cannot unwrap success value with failure result.
    }

} // namespace RumeLab::Detail

constexpr auto test_result = &RumeLab::Detail::test_result<>;

#endif // TEST_RESULT_HPP