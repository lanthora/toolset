#include "log.h"

#include <stdarg.h>

#include <stdexcept>
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <algorithm>
#include <memory>
#include <cstring>
#ifdef WIN32
#include "windows.h"
#else
#include <sys/time.h>
#endif


namespace ts {

LOG::LOG(): level_(0), filename_("") {
    msg_buffer_ = new char[LOGBUFFERSIZE];
};

LOG::~LOG() {
    delete[] msg_buffer_;
    msg_buffer_ = nullptr;
}

void LOG::Init(const int &level, const std::string &filename) {
    this->level_ = level;
    this->filename_ = filename;
}

void LOG::Write(const int &level, const std::string &log) {

    if (this->filename_ == "" || !(level & this->level_)) return;

    std::ofstream logfile;
    logfile.open(this->filename_, std::ios::app);
    logfile << "[" << LevelToString(level) << "]";
    logfile << "[" << CurrentTime() << "]:";
    logfile << log << std::endl;
    logfile.close();
}

void LOG::FormatWrite(const int &level, const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);

#if __cplusplus < 201103L
    vsnprintf_s(msg_buffer_, LOGBUFFERSIZE, _TRUNCATE, fmt, ap);
#else
    vsnprintf(msg_buffer_, LOGBUFFERSIZE - 1, fmt, ap);
#endif

    va_end(ap);
    this->Write(level, msg_buffer_);
}

std::string LOG::LevelToString(const int &level) {
    switch (level) {
    case 1:
        return "DBG";
    case 2:
        return "INF";
    case 4:
        return "ERR";
    }
    return "NONE";
}

std::string LOG::CurrentTime() {
    std::stringstream ss;

#ifdef WIN32
    SYSTEMTIME st;
    GetLocalTime(&st);
    ss << st.wYear;
    ss << "/" << std::setw(2) << std::setfill('0') << st.wMonth;
    ss << "/" << std::setw(2) << std::setfill('0') << st.wDay;
    ss << " " << std::setw(2) << std::setfill('0') << st.wHour;
    ss << ":" << std::setw(2) << std::setfill('0') << st.wMinute;
    ss << ":" << std::setw(2) << std::setfill('0') << st.wSecond;
#else
    time_t rawtime;
    time(&rawtime);
    struct tm *ptm;
    ptm = localtime(&rawtime);
    ss << ptm->tm_year + 1900;
    ss << "/" << std::setw(2) << std::setfill('0') << ptm->tm_mon + 1;
    ss << "/" << std::setw(2) << std::setfill('0') << ptm->tm_mday;
    ss << " " << std::setw(2) << std::setfill('0') << ptm->tm_hour;
    ss << ":" << std::setw(2) << std::setfill('0') << ptm->tm_min;
    ss << ":" << std::setw(2) << std::setfill('0') << ptm->tm_sec;
#endif
    return ss.str();
}

void Record::Write(const std::string &filename_prefix, const std::string &record) {
    std::ostringstream oss;
    oss.clear();
    oss << filename_prefix << "/" << CurrentTime() << ".txt";
    const std::string filename = oss.str();
    std::ofstream ofs;
    ofs.open(filename, std::ios::app);
    ofs << record << std::endl;
    ofs.close();
}

unsigned long long int Record::CurrentTime() {
#ifdef WIN32
    SYSTEMTIME st;
    GetLocalTime(&st);
    unsigned long long timestamp = st.wMilliseconds;
    std::time_t unix_timestamp = std::time(0);
    timestamp += unix_timestamp * 1000;
    return timestamp;
#else
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000 + tv.tv_usec / 1000;
#endif
}

void HexDump::Write(unsigned char *p, const unsigned int &len, const std::string filename, const std::string flag) {
    std::ofstream ofs;
    ofs.open(filename, std::ios::app);

    ofs << "------------------------------------------------------------------------[" << len << "]"
        << flag << std::endl;

    const unsigned short LINE_SIZE = 16;
    unsigned char line[LINE_SIZE];

    unsigned int offset = 0;
    while (offset < len) {

        ofs << std::setw(4) << std::setfill('0') << std::hex << offset << "   ";
        std::memset(line, 0, LINE_SIZE);
        int valid_size = std::min(static_cast<unsigned int>(LINE_SIZE), len - offset);
        std::memcpy(line, p + offset, valid_size);

        for (int i = 0; i < valid_size; ++i) {
            ofs << std::setw(2) << std::setfill('0') << std::hex
                << static_cast<unsigned short>(line[i]) << " ";
        }

        for (int i = valid_size; i < LINE_SIZE; ++i) {
            ofs << "   ";
        }

        ofs << " ";
        char current_char;
        for (int i = 0; i < valid_size; ++i) {
            current_char = (line[i] >= 0x20 && line[i] < 0x7f) ? line[i] : '.';
            ofs << current_char;
        }

        for (int i = valid_size; i < LINE_SIZE; ++i) {
            ofs << " ";
        }

        ofs << std::endl;

        offset += LINE_SIZE;
    }
    ofs.close();
}


} // namespace ts
