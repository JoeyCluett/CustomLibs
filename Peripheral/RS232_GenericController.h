#ifndef __JJC__RS232GENERIC__H__
#define __JJC__RS232GENERIC__H__

#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <iostream>
#include <vector>

#define SC SerialController

enum Parity {
    Parity_ODD,
    Parity_EVEN,
    Parity_OFF
};

enum WordSize {
    WordSize_7, WordSize_8
};

enum StopBits {
    StopBits_1, StopBits_2

#include <stdlib.h>

#define SC SerialController

enum WORDSIZE {
    _7, _8
};

enum PARITY {
    ODD, EVEN, OFF
};

enum STOPBITS {
    _1, _2
};

class SerialController {
private:
    termios tty;
    int fd = -1;
    bool serialPortSet = false;
    void parityEnable(void);

public:
    // constructor that does nothing
    SerialController(void);

    // constructor with serial port as argument
    SerialController(const char* serialPort);

    // specify a serial device to use
    void set_SerialPort(const char* serialPort);

    // try to read a certain number of bytes from the serial port
    int readBuffer(char* buffer, int bufSize);

<<<<<<< HEAD
    // try write a certain number of bytes from the serial port
    int writeBuffer(char* buffer, int bufSize);

    // block until operations are complete
    void readChunk(char* buffer, int bufSize);
=======
    // guarantee read bufSize bytes
    void readChunk(char* buffer, int bufSize);

    // try to write a certain number of bytes from the serial port
    int writeBuffer(char* buffer, int bufSize);

    // guarantee write bufSize bytes
>>>>>>> 8d1092d38bd85bb031b51f1716662ca32222c80c
    void writeChunk(char* buffer, int bufSize);

    // set the read/write speeds for the serial port
    void set_BaudRate(int baudrate);

    // set odd/even/no parity for this serial port
    void set_Parity(Parity parity);

    // set either 7 or 8 bit word for this serial port
    void set_WordSize(WordSize wordsize);

    // set either 1 or 2 stop bits for this port
    void set_StopBits(StopBits stopbits);

    // start serial communications
    void start(void);

    int get_FileDescriptor(void);

    int updateBuffer(std::vector<char>& vec);
};

SC::SerialController(void) {
    ;
}

SC::SerialController(const char* serialPort) {
    SerialController::set_SerialPort(serialPort);
}

int SC::updateBuffer(std::vector<char>& vec) {
    char buf[1024];
    int i = read(fd, buf, 1024);

    for(int j = 0; j < i; j++)
        vec.push_back(buf[j]);

    return i;
}

void SC::set_SerialPort(const char* serialPort) {
    memset(&tty, 0, sizeof tty);
    fd = open(serialPort, O_RDWR | O_NOCTTY | O_NDELAY); // pretty standard flags
    if(fd < 0) {
        int e = errno;
        std::cerr << "Error opening file" << std::endl;
        std::cerr << "    Error code: " << e << std::endl;
        std::cerr << " -- " << strerror(e) << std::endl;
        exit(-1);
    }

    if(tcgetattr(fd, &tty) < 0) {
        int e = errno;
        std::cerr << "Error retrieving attributes" << std::endl;
        std::cerr << "    Error code: " << e << std::endl;
        std::cerr << " -- " << strerror(e) << std::endl;
        exit(-1);
    }
    serialPortSet = true;
}

void SC::parityEnable(void) {
    tty.c_cflag |= PARENB;
}

int SC::writeBuffer(char* buffer, int bufSize) {
    return write(fd, buffer, bufSize);
<<<<<<< HEAD
}

int SC::readBuffer(char* buffer, int bufSize) {
    return read(fd, buffer, bufSize);
}

void SC::readChunk(char* buffer, int bufSize) {
    int bytes_read = 0;
    while(bytes_read < bufSize)
        bytes_read += read(fd, buffer+bytes_read, bufSize-bytes_read);
}

void SC::writeChunk(char* buffer, int bufSize) {
    int bytes_writ = 0;
    while(bytes_writ < bufSize)
        bytes_writ += write(fd, buffer+bytes_writ, bufSize-bytes_writ);
=======
}

int SC::readBuffer(char* buffer, int bufSize) {
    return read(fd, buffer, bufSize);
}

void SC::writeChunk(char* buffer, int bufSize) {
    int bytes_written = 0;

    while(bytes_written != bufSize) {
        bytes_written += write(fd, buffer+bytes_written, bufSize-bytes_written);
    }

}

void SC::readChunk(char* buffer, int bufSize) {
    int bytes_read = 0;

    while(bytes_read != bufSize) {
        bytes_read += read(fd, buffer+bytes_read, bufSize-bytes_read);
    }
>>>>>>> 8d1092d38bd85bb031b51f1716662ca32222c80c
}

void SC::set_BaudRate(int baudrate) {
    cfsetispeed(&tty, baudrate);
    cfsetospeed(&tty, baudrate);
}

<<<<<<< HEAD
void SC::set_Parity(Parity parity) {
=======
void SC::set_Parity(PARITY parity) {
>>>>>>> 8d1092d38bd85bb031b51f1716662ca32222c80c
    switch(parity) {
        case Parity_EVEN:
            tty.c_cflag |= PARENB;
            tty.c_cflag &= ~PARODD;
            break;
        case Parity_ODD:
            tty.c_cflag |= PARENB;
            tty.c_cflag |= PARODD;
            break;
        case Parity_OFF: // disable the parity bit
            tty.c_cflag &= ~PARENB;
            break;
        default:
            std::cerr << "Invalid parity argument" << std::endl;
            exit(-1); // all error comditions return -1
    }
}

<<<<<<< HEAD
void SC::set_StopBits(StopBits stopbits) {
=======
void SC::set_StopBits(STOPBITS stopbits) {
>>>>>>> 8d1092d38bd85bb031b51f1716662ca32222c80c
    switch(stopbits) {
        case StopBits_1:
            tty.c_cflag &= ~CSTOPB;
            break;
        case StopBits_2:
            tty.c_cflag |= CSTOPB;
            break;
        default:
            std::cerr << "Invalid stop bit argument" << std::endl;
            exit(-1);
    }
}

<<<<<<< HEAD
void SC::set_WordSize(WordSize wordsize) {
=======
void SC::set_WordSize(WORDSIZE wordsize) {
>>>>>>> 8d1092d38bd85bb031b51f1716662ca32222c80c
    switch(wordsize) {
        case WordSize_7:
            tty.c_cflag &= ~CSIZE;
            tty.c_cflag |= CS7;
            break;
        case WordSize_8:
            tty.c_cflag &= ~CSIZE;
            tty.c_cflag |= CS8;
            break;
        default:
            std::cerr << "Invalid word size argument" << std::endl;
            exit(-1);
    }
}

void SerialController::start(void) {
    if(serialPortSet == false) {
        std::cerr << "Serial port has not been opened" << std::endl;
        exit(-1);
    }

    if(tcsetattr(fd, TCSANOW, &tty) != 0) {
        std::cerr << "Error starting serial communications" << std::endl;
        std::cerr << "    Error code: " << errno << std::endl;
        exit(-1);
    }
}

int SerialController::get_FileDescriptor(void) {
    return fd;
}

#endif // __JJC__RS232GENERIC__H__
