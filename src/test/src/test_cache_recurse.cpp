#include <functional>
#include <source_location>
#include <iostream>
#include <map>
#include <memory>
#include <format>
#include <tuple>
#include <string>
using namespace std;


template<class R, class ...Args>
std::function<R(Args...)> CacheFunc(std::function<R(Args...)> func, const std::source_location& loc = std::source_location::current())
{
    using Func = std::function<R(Args...)>;
    using namespace std;
    static map<string, Func> cache_map;
    string flag = format("file:{},function:{},line:{}", loc.file_name(), loc.function_name(), loc.line());
    if (cache_map.count(flag) == 0)
    {
        using KeyType = tuple<Args...>;
        using MapType = map<KeyType, R>;
        auto data_cache = std::make_shared<MapType>();
        cache_map[flag] = [=](Args... args)->R {
            KeyType arg{ args... };
            auto show_data = [](const auto& val)->const auto& {cout << " ";
            return val; };
            if (data_cache->count(arg) == 0)
            {
                cout << "正在计算：";
                (cout << ... << show_data(args)) << endl;
                data_cache->emplace(arg, func(args...));
            }
            else
            {
                cout << "正在查询：";
                (cout << ... << show_data(args)) << endl;
            }

            return data_cache->at(arg);
            };
    }
    return cache_map[flag];
}


template<class R, class ...Args>
std::function<R(Args...)> CacheFunc(R(*func)(Args...), const std::source_location& loc = std::source_location::current())
{
    return CacheFunc(std::function<R(Args...)>{func}, loc);
}

template<class R, class ...Args, std::invocable<Args...> F>
std::function<R(Args...)> CacheFunc(F func, const std::source_location& loc = std::source_location::current())
{
    return CacheFunc(std::function<R(Args...)>{func}, loc);
}



size_t fibonacci(size_t n)
{
    if (n < 3)
        return 1;
    static auto&& func = CacheFunc(fibonacci);
    cout << format("当前：n={}", n) << endl;
    return func(n - 1) + func(n - 2) + func(n - 3);
}

void test_cache_recurse()
{
    using namespace std;
    cout << "fibonacci(10)=\n" << fibonacci(10) << endl;
}
