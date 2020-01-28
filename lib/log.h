#ifndef TS_LIB_LOG_H_
#define TS_LIB_LOG_H_

#include <string>

namespace ts {

class LOG {
public:
    static const int LEVEL_NONE = 0, LEVEL_DBG = 1, LEVEL_INFO = 2, LEVEL_ERR = 4, LEVEL_ALL = 7;

    void Init(const int &level, const std::string &filename);
    void FormatWrite(const int &level, const char *fmt, ...);


private:
    char *msg_buffer_;
    int level_;
    std::string filename_;

    void Write(const int &level, const std::string &log);
    std::string LevelToString(const int &level);
    std::string CurrentTime();
    static const unsigned int LOGBUFFERSIZE = 1024 * 512;
public:

#if _cplusplus>= 201103L
    // disable copy and move beacuse pointer is used
    LOG(const LOG &) = delete;
    LOG &operator=(const LOG &) = delete;
#endif

    LOG();
    ~LOG();
};

class Record {
public:
    void Write(const std::string &filename_prefix, const std::string &record);
private:
    unsigned long long int CurrentTime();
};

class HexDump {
public:
    void Write(unsigned char *p, const unsigned int &len, const std::string filename, const std::string flag = "");
};


} // namespace ts

#endif // TS_LIB_LOG_H_
