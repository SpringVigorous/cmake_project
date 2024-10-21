#pragma once

#include <string>

#include "tools/tools.h"

class TOOLS_API CodeConvert
{
public:
    //! 将gbk格式的字符串转换为utf8格式
    static std::string gbk_to_utf8(const std::string &gbk_str);

    //! 将utf8格式的字符串转换为gbk格式
    static std::string utf8_to_gbk(const std::string &utf_str);

    //! 将unicode格式的字符串转换为utf8格式
    static std::string unicode_to_utf8(const std::wstring &uicode_str);

    //! 将utf8格式的字符串转换为unicode格式
    static std::wstring utf8_to_unicode(const std::string &utf_str);

    //! 将gbk格式的字符串转换为unicode格式
    static std::wstring gbk_to_unicode(const std::string &gbk_str);

    //! 将unicode格式的字符串转换为gbk格式
    static std::string unicode_to_gbk(const std::wstring &uicode_str);

    static std::u16string utf8_to_utf16(const std::string &utf32_str);

    static std::string utf16_to_utf8(const std::u16string &utf16_str);

    static std::u32string utf8_to_utf32(const std::string &utf8_str);

    static std::string utf32_to_utf8(const std::u32string &utf32_str);

    static std::u32string utf16_to_utf32(const std::u16string &utf16_str);

    static std::u16string utf32_to_utf16(const std::u32string &utf32_str);

    static std::u16string utf8_to_utf16(const std::u8string &utf32_str);
    static std::u32string utf8_to_utf32(const std::u8string &utf8_str);
    static std::u8string utf8_to_utf8(const std::string &utf8_str);
    static std::string utf8_to_utf8(const std::u8string &utf8_str);
};