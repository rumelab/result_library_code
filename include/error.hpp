#ifndef ERROR_HPP
#define ERROR_HPP

#include <Arduino.h>

namespace RumeLab::Detail
{

    /// Halt execution and blink builtin LED to signal unrecoverable error.
    template <typename = void>
    [[noreturn]] auto error() -> void
    {
        pinMode(LED_BUILTIN, OUTPUT);
        while (true)
        {
            digitalWrite(LED_BUILTIN, HIGH);
            delay(500);
            digitalWrite(LED_BUILTIN, LOW);
            delay(500);
        }
    }

} // namespace RumeLab::Detail

constexpr auto error = &RumeLab::Detail::error<>;

#endif // ERROR_HPP