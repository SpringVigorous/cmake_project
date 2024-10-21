#include "test/test.h"
#include "tools/string_convert.h"

void test_code_convet()
{
    using namespace std;
    string gbk_str{ "中国" };
    auto unicode_str = CodeConvert::gbk_to_unicode(gbk_str);
    auto utf_str= CodeConvert::gbk_to_utf8(gbk_str);

    gbk_str = CodeConvert::unicode_to_gbk(unicode_str);
    utf_str = CodeConvert::unicode_to_utf8(unicode_str);

    gbk_str = CodeConvert::utf8_to_gbk(utf_str);
    unicode_str = CodeConvert::utf8_to_unicode(utf_str);


    auto u16_str = CodeConvert::utf8_to_utf16(utf_str);
    auto u32_str = CodeConvert::utf8_to_utf32(utf_str);
    utf_str = CodeConvert::utf16_to_utf8(u16_str);
    u32_str = CodeConvert::utf16_to_utf32(u16_str);
    utf_str = CodeConvert::utf32_to_utf8(u32_str);
    u16_str = CodeConvert::utf32_to_utf16(u32_str);
    auto u8_str = CodeConvert::utf8_to_utf8(utf_str);
    utf_str= CodeConvert::utf8_to_utf8(u8_str);
    u16_str = CodeConvert::utf8_to_utf16(u8_str);
    u32_str = CodeConvert::utf8_to_utf32(u8_str);

}