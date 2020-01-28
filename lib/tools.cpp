#include "tools.h"

#include <sstream>

namespace ts {

int BigEndianHexStringToInt(const unsigned char *str, const int &str_len) {
    int ret = 0;
    for (int i = 0; i < str_len; ++i) {
        ret <<= 8;
        ret += static_cast<unsigned short>(str[i]);
    }
    return ret;
}

int LittleEndianHexStringToInt(const unsigned char *str, const int str_len) {
    int ret = 0;
    for (int i = str_len - 1; i >= 0; --i) {
        ret <<= 8;
        ret += static_cast<unsigned short>(str[i]);
    }
    return ret;
}

std::string CharPointerToString(const char *str, const int &str_len) {
    std::ostringstream outss;
    for (int i = 0; i < str_len; ++i) {
        outss << str[i];
    }
    return outss.str();
}

} // namespace ts
