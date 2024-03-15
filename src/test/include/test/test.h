#pragma once
#include <iostream>
#include <memory>
#include <format>

void test_code_convet();

void test_queens_n_n();
void test_queens_n();
void test_format();

void test_package_0_1();
void test_package_0_1_2();
void test_package_whole_1();
void test_quick_sort();

void test_merge_sort();
void test_shell_sort();
void test_insert_sort();
void test_heap_sort();

void test_bfs();
void  test_recursive();

void test_slice_paper();
void test_key_route();
void test_maze();
void test_create_maze();

template<class T, class K>
void print(const std::pair<T, K>& item) {
    using namespace std;
    cout << std::format("({},{})\n", item.first, item.second);
}

template<class T>
void print(const T& val) {
    using namespace std;
    cout << val << ",";
}

template<class T,template<typename U,typename =std::allocator<U>> class Container>
void print(const Container<T>& vec) {
    using namespace std;
    for (const auto& val : vec)
        print(val);
    cout << "\n";
}


template<class T, template<typename U, typename = std::allocator<U>> class Container>
void print(const Container<Container<T>>& vec) {
    using namespace std;
    for (const auto& val : vec)
        print(val) ;
    cout << "\n";
}

template<class T, template<typename U, typename = std::allocator<U>> class Container,class Func>
void print(const Container<T>& vec,Func func) {
    using namespace std;
    for (const auto& val : vec)
        cout << func(val) << ",";
    cout << "\n";
}
template<class T, template<typename U, typename = std::allocator<U>> class Container, class Func>
void print(const Container<Container<T>>& vec, Func func) {
    using namespace std;
    for (const auto& val : vec)
        print(val,func);
    cout << "\n";
}