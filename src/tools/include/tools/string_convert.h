#pragma once

#include <string>

#include "tools/tools.h"


class TOOLS_API CodeConvert
{
public:
    //! 将gbk格式的字符串转换为utf8格式
    static std::string gbk_to_utf8(const std::string& gbk_str);

    //! 将utf8格式的字符串转换为gbk格式
    static std::string utf8_to_gbk(const std::string& utf_str);

    //! 将unicode格式的字符串转换为utf8格式
    static std::string unicode_to_utf8(const std::wstring& uicode_str);

    //! 将utf8格式的字符串转换为unicode格式
    static std::wstring utf8_to_unicode(const std::string& utf_str);

    //! 将gbk格式的字符串转换为unicode格式
    static std::wstring gbk_to_unicode(const std::string& gbk_str);

    //! 将unicode格式的字符串转换为gbk格式
    static std::string unicode_to_gbk(const std::wstring& uicode_str);

};