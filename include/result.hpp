#ifndef RESULT_HPP
#define RESULT_HPP

#include <Arduino.h>
#include <memory>
#include <type_traits>

#include "error.hpp"

namespace RumeLab::Detail
{

    template <typename PSuccessType, typename PFailureType>
    class Result
    {
        static_assert(!std::is_same<PSuccessType, PFailureType>::value, "Success value type and failure value type must not be the same.");

    public:
        using SuccessType = PSuccessType;
        using FailureType = PFailureType;

    private:
        const bool successful;
        union
        {
            SuccessType success;
            FailureType failure;
        };

    public:
        constexpr Result(SuccessType p_success)
            : successful(true), success(std::move(p_success)) {}

        constexpr Result(FailureType p_failure)
            : successful(false), failure(std::move(p_failure)) {}

        constexpr Result(Result &p_result)
            : successful(p_result.successful)
        {
            if (successful)
                success = p_result.success;
            else
                failure = p_result.failure;
        }

        constexpr Result(Result &&p_result)
            : successful(p_result.successful)
        {
            if (successful)
                success = std::move(p_result.success);
            else
                failure = std::move(p_result.failure);
        }

        ~Result()
        {
            if (successful)
            {
                if (std::is_destructible<SuccessType>::value)
                    success.~SuccessType();
            }
            else
            {
                if (std::is_destructible<FailureType>::value)
                    failure.~FailureType();
            }
        }

        operator bool() const &
        {
            return successful;
        }

        inline auto unwrap_success() -> SuccessType &&
        {
            if (!successful)
                ::error();
            return std::move(success);
        }

        inline auto unwrap_failure() -> FailureType &&
        {
            if (successful)
                ::error();
            return std::move(failure);
        }
    };

} // namespace RumeLab::Detail

template <typename PSuccessType, typename PFailureType = String>
using Result = RumeLab::Detail::Result<PSuccessType, PFailureType>;

#endif // RESULT_HPP