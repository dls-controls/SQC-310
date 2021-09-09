// Adapted from code snippet in SQC-310 manual

#include <iostream>
#include <string.h>
#include <sstream>

class CRC14 {
  public:
    CRC14() {
        crc = 0x0;
    };

    short crc;

    short calcCRC(unsigned char* str) {
        int length = (str != NULL) ? 1 + str[1] - 34 : 0;
        if (length > 0) {
            crc = (short) 0x3fff;
            for (int jx = 1; jx <= length; jx++) {
                crc = (short) (crc ^ (short) str[jx]);
                for (int ix = 0; ix < 8; ix++) {
                    short tmpCRC = crc;
                    crc = (short) (crc >> 1);
                    if ((tmpCRC & 0x1) == 1) {
                        crc = (short) (crc ^ 0x2001);
                    }
                }
                crc = (short) (crc & 0x3fff);
            }
        }
        return crc;
    }

    unsigned char crc1() {
        unsigned char val = (unsigned char) ((crc & 0x7f) + 34);
        return val;
    }

    unsigned char crc2() {
        unsigned char val = (unsigned char) (((crc >> 7) & 0x7f) + 34);
        return val;
    }
};

int main(int argc, char* argv[]) {
    unsigned char* command = (unsigned char*) argv[1];

    int length = strlen((const char*) command) + 34;
    char ascii_length = (char) length;

    std::cout << "(ASCII, Decimal, Hexadecimal)" << std::endl;
    std::cout << "Length (+34): " << (char) length << ", " << length << ", 0x" << std::hex << length << std::endl;

    std::stringstream full_command;
    full_command << "!" << ascii_length << command;

    CRC14 crc = CRC14();
    crc.calcCRC((unsigned char*) full_command.str().c_str());
    unsigned char crc1 = crc.crc1();
    unsigned char crc2 = crc.crc2();

    std::cout << "Command (without CRC): " << full_command.str().c_str() << std::endl;
    std::cout << "CRC1: " << crc1 << ", " << std::dec << (int) crc1 << ", 0x" << std::hex << (int) crc1 << std::endl;
    std::cout << "CRC2: " << crc2 << ", " << std::dec << (int) crc2 << ", 0x" << std::hex << (int) crc2 << std::endl;

    full_command << crc1 << crc2;
    std::cout << "Full Command: " << full_command.str().c_str() << std::endl;

    return 0;
}
