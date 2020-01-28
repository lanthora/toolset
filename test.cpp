#include "lib/log.h"
#include "lib/tools.h"
#include <iostream>
using namespace std;
int main() {
    unsigned char uc[] = {0x7F, 0xFF, 0xFF, 0xFF};
    cout << ts::BigEndianHexStringToInt(uc, 4) << endl;
    cout << ts::LittleEndianHexStringToInt(uc, 4) << endl;
    char c[] = {0x54, 0x43, 0x50, 0x21};
    cout << ts::CharPointerToString(c, 3) << endl;
    cout << ts::CharPointerToString(c, 4) << endl;

    ts::LOG log;
    log.Init(7, "test.log");
    log.FormatWrite(1, "%d", 123);

    ts::Record record;
    record.Write("record", "record .");

    ts::HexDump hexdump;
    hexdump.Write(uc, 4, "dump.log", "flag");
    return 0;
}
