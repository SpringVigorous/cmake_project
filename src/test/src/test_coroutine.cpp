#include <iostream>
#include <vector>
#include <algorithm>
#include "test/test.h"
#include <coroutine>
#include <format>
struct Generator {
    class ExhaustedException : std::exception {};
    struct Awaiter;
    struct promise_type {
        int value;
        std::suspend_never initial_suspend() { return {}; };
        std::suspend_always final_suspend() noexcept { return {}; }
        Awaiter yield_value(int value) {
            this->value = value;
            return { *this };
        }
        void unhandled_exception() {
        }
        Generator get_return_object() {
            return Generator{ std::coroutine_handle<promise_type>::from_promise(*this) };
        }
        void return_value(int value) {
            this->value = value;
        }
    };
    std::coroutine_handle<promise_type> handle;
    struct Awaiter
    {
        constexpr bool await_ready() const noexcept {
            return false;
        }
        void await_suspend(std::coroutine_handle<> handle) noexcept {

        }
        auto await_resume() noexcept {
            return promise.value;
        }
        promise_type& promise;
    };
    bool has_next() {
        if (handle.done()) {
            return false;
        }
        else {
            return true;
        }
    }
    int next() {
        if (has_next()) {
            return handle.promise().value;
        }
        throw ExhaustedException();
    }
    int next(int val)
    {
        handle.promise().value = val;
        handle.resume();
        return handle.promise().value;
    }
    Awaiter operator co_await() noexcept {
        return Awaiter{ handle.promise() };
    }
    explicit Generator(std::coroutine_handle<promise_type> handle) noexcept
        : handle(handle) {}
    Generator(Generator&& generator) noexcept
        : handle(std::exchange(generator.handle, {})) {}
    Generator(Generator&) = delete;
    Generator& operator=(Generator&) = delete;
    ~Generator() {
        if (handle) handle.destroy();
    }
};
Generator sequence() {
    int i = 100;
    while (true) {
        int j = co_yield i++;
        i = j+5;
    }
    co_return 0;
}
void test_coroutine()
{
    
    auto generator = sequence();
    for (int i = 0; i < 10; ++i) {
        std::cout << std::format("第{}次：",i+1).c_str()<<  generator.next(i * 10) << std::endl;
    }
}
