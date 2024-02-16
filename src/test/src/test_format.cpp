#include "kernel_serialize/serialize_obj.h"
#include <iostream>
#include "tools/string_convert.h"
#include <iostream>
#include <bit>
#include <format>
#include <string_view>
#include "test/test.h"

using namespace std;

auto operator ""_f(const char* format_str, size_t n)
{
    std::string fstr(format_str);
    return[=]<class ...Args>(Args&&...args)
    {
        return vformat(fstr, make_format_args(std::forward<Args>(args)...));
        //return format(string_view(fstr.begin(), fstr.end()), std::forward<Args>(args)...);
    };
};

unsigned long long operator""_f(unsigned long long val){
    return val * 2;
};

void test_format()

{
 cout << "fs{}:{}"_f(35,2345.9) << endl;

    cout << 5_f << endl;

    if (std::endian::native == std::endian::big) {
        std::cout << "大端" << std::endl;
    } else if (std::endian::native == std::endian::little) {
        std::cout << "小端" << std::endl;
    } else {
        std::cout << "中端" << std::endl;
    }
    int a = 0x11223344;
    char* p = (char*)(&a);
    int i = 0;
    while(i<sizeof(int))
    {
        cout << hex << p[i++] << endl;

    }

    using namespace std;
    using namespace  KERNEL_SERIALIZE;
    serialize_person obj;
    cout<< "(测试：)"<< 15<<endl;

    cout << "sizeof (char):" << sizeof(char) << endl;
    cout << "sizeof (wchar):" << sizeof(wchar_t) << endl;

    string org_gbk_str("中A国b人C民d欢E迎f您G");
    wstring org_unicode_str(L"中A国b人C民d欢E迎f您G");
    u8string org_utf8_str1(u8"中A国b人C民d欢E迎f您G");
    string org_utf8_str(org_utf8_str1.begin(), org_utf8_str1.end());

    auto dest_gbk_to_unicode = CodeConvert::gbk_to_unicode(org_gbk_str);
    auto dest_gbk_to_utf8 = CodeConvert::gbk_to_utf8(org_gbk_str);

    auto dest_utf8_to_gbk = CodeConvert::utf8_to_gbk(org_utf8_str);
    auto dest_utf8_to_unicode = CodeConvert::utf8_to_unicode(org_utf8_str);


    auto dest_unicode_to_gbk = CodeConvert::unicode_to_gbk(org_unicode_str);
    auto dest_unicode_to_utf8 = CodeConvert::unicode_to_utf8(org_unicode_str);
}