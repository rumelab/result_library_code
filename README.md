# Result Library Code

Result library is a header-only Platform IO library with Arduino framework
that provides a simple error handling methodology similar to `Result` from the Rust programming language,
with complete unit testing (on Raspberry Pi Pico) which also could be use as example.
Below is a sample code snippet to demonstrate the usage of this library.

```cpp

// It is invalid for the success value type to be the same as error value type.

Result<uint8_t, String> compute_number_failure() {
    return Result<uint8_t, String>("Fail to compute number."); // Create failure result.
}

Result<uint8_t, String> compute_number_success() {
    return Result<uint8_t, String>(42); // Create successful result.
}

void handle_result() {
    // Handle failure.
    Result<uint8_t, String> result_a = compute_number_failure();
    if(result_a) {
        // Success
        uint8_t success_value = result_a.unwrap_success(); // This would be a move assignment for movable objects.
        // Do something about the success.
    } else {
        // Failure
        String failure_message = result_a.unwrap_failure(); // This would be a move assignment for movable objects.
        // Do something about the failure.

        // result_a.unwrap_success(); // It would be an error to unwrap success value during a failure, it will halt and blink the builtin LED.
    }
}

void raise_error() {
    error(); // To raise an unrecoverable error, it will halt and blink the builtin LED.
}

```

## Installation

In your `platform.io` library, append the URL of this github repository to the `lib_deps` attribute.

```ini
lib_deps=https://github.com/rumelab/result_library_code
```
