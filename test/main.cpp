#include <Arduino.h>
#include <unity.h>

#include "test_result.hpp"

REDIRECT_STDOUT_TO(Serial);

void test_unity(void)
{
    TEST_ASSERT_EQUAL(33, 33);
}

void setup()
{
    delay(2000);
    Serial.begin(9600);
    while (!Serial)
    {
    }

    UNITY_BEGIN();
    RUN_TEST(test_unity);
    RUN_TEST(test_result);
    UNITY_END();
}

void loop()
{
    delay(1000);
}