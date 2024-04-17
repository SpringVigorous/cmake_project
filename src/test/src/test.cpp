//#pragma execution_character_set("utf-8")
#include <test/test.h>
#include <iostream>
#include <cstdlib>
#include <filesystem>
#include <string>

int main(int count, const char* args[])
{
    using namespace std;
    string temp_str("临时文件目录");

    cout << "临时文件目录:" << filesystem::temp_directory_path() << endl;
    std::filesystem::path cmake_file = std::filesystem::path("CMakeLists.txt");
    std::cout << "CMakeLists.txt 的路径: " << cmake_file << std::endl;

    // 设置当前工作目录为指定路径
    cout << "原始工作目录为：\n" << std::filesystem::current_path() << endl;
    auto work_dir = std::filesystem::path(args[0]).parent_path();
     std::filesystem::current_path(work_dir);
    cout << "修改后工作目录为：\n" << std::filesystem::current_path() << endl;


    //test_cache_recurse();
    //test_code_convet();
    // test_queens_n_n();
    // test_queens_n();
    // test_format();

     //test_package_0_1();
    // test_package_0_1_2();
    // test_package_whole_1();
    // test_quick_sort();
    // test_merge_sort();
    // test_insert_sort();
    //  test_shell_sort();
    // test_heap_sort();
     //test_bfs();
    // test_recursive();
    // test_slice_paper();
    //test_key_route();
    //test_create_maze();
    //  test_maze();
    test_coroutine();
    system("pause");

    return 0;
}