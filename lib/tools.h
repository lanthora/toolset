#ifndef TS_TOOLS_H_
#define TS_TOOLS_H_

#include <string>

namespace ts {

int BigEndianHexStringToInt(const unsigned char *str, const  int &str_len);
int LittleEndianHexStringToInt(const unsigned char *str, const  int str_len);
std::string CharPointerToString(const char *str, const  int &str_len);

} // namespace ts

#endif // TS_TOOLS_H_
