#ifndef __JJC__RS232GENERIC__H__
#define __JJC__RS232GENERIC__H__

#include <sys/ioctl.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <iostream>


#define SC SerialController

class SerialController {
private:
    termios tty;
    int fd = -1;
    bool serialPortSet = false;
    void parityEnable(void);

public:
    enum PARITY {
        ODD, EVEN, OFF
    };

    enum WORDSIZE {
        _7, _8
    };

    enum STOPBITS {
        _1, _2
    };

    // constructor that does nothing
    SerialController(void);

    // constructor with serial port as argument
    SerialController(const char* serialPort);

    // specify a serial device to use
    void set_SerialPort(const char* serialPort);

    // read a certain number of bytes from the serial port
    void readBuffer(char* buffer, int bufSize);

    // write a certain number of bytes from the serial port
    void writeBuffer(char* buffer, int bufSize);

    // set the read/write speeds for the serial port
    void set_BaudRate(int baudrate);

    // set odd/even/no parity for this serial port
    void set_Parity(PARITY parity);

    // set either 7 or 8 bit word for this serial port
    void set_WordSize(WORDSIZE wordsize);

    // set either 1 or 2 stop bits for this port
    void set_StopBits(STOPBITS stopbits);

    // dont use either of these two methods yet, still figuring out
    bool set_ModeBlocking(void);    // set the serial port as blocking, returns true on success
    bool set_ModeNonblocking(void); // set the serial port as non-blocking, returns true on success

    // how much data can currently be read from the serial port
    int hasData(void);

    // start serial communications
    void start(void);

    // return the file descriptor of the serial port
    int get_FileDescriptor(void);
};


SC::SerialController(void) {
    ;
}

SC::SerialController(const char* serialPort) {
    SerialController::set_SerialPort(serialPort);
}

void SC::set_SerialPort(const char* serialPort) {
    memset(&tty, 0, sizeof tty);
    fd = open(serialPort, O_RDWR | O_NOCTTY | O_NDELAY); // pretty standard flags
    if(fd < 0) {
        int e = errno;
        std::cerr << "Error opening file" << std::endl;
        std::cerr << "    Error: " << strerror(e) << std::endl;
        exit(-1);
    }

    if(tcgetattr(fd, &tty) < 0) {
        int e = errno;
        std::cerr << "Error retrieving attributes" << std::endl;
        std::cerr << "    Error: " << strerror(e) << std::endl;
        exit(-1);
    }

    serialPortSet = true;
}

void SC::parityEnable(void) {
    tty.c_cflag |= PARENB;
}

void SC::writeBuffer(char* buffer, int bufSize) {
    write(fd, buffer, bufSize);
}

void SC::readBuffer(char* buffer, int bufSize) {
    read(fd, buffer, bufSize);
}

void SC::set_BaudRate(int baudrate) {
    cfsetispeed(&tty, baudrate);
    cfsetospeed(&tty, baudrate);
}

void SC::set_Parity(SC::PARITY parity) {
    switch(parity) {
        case EVEN:
            tty.c_cflag |= PARENB;
            tty.c_cflag &= ~PARODD;
            break;
        case ODD:
            tty.c_cflag |= PARENB;
            tty.c_cflag |= PARODD;
            break;
        case OFF: // disable the parity bit
            tty.c_cflag &= ~PARENB;
            break;
        default:
            std::cerr << "Invalid parity argument" << std::endl;
            exit(-1); // all error comditions return -1
    }
}

void SC::set_StopBits(SC::STOPBITS stopbits) {
    switch(stopbits) {
        case _1:
            tty.c_cflag &= ~CSTOPB;
            break;
        case _2:
            tty.c_cflag |= CSTOPB;
            break;
        default:
            std::cerr << "Invalid stop bit argument" << std::endl;
            exit(-1);
    }
}

void SC::set_WordSize(SC::WORDSIZE wordsize) {
    switch(wordsize) {
        case _7:
            tty.c_cflag &= ~CSIZE;
            tty.c_cflag |= CS7;
            break;
        case _8:
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

bool SerialController::set_ModeBlocking(void) {
    if(!serialPortSet) {
        std::cerr << "Error: serial port not started" << std::endl;
        exit(-1);
    }

    int sFlags = fcntl(fd, F_GETFL, 0);

    if(sFlags == -1)
        return false;

    sFlags &= ~O_NONBLOCK;

    if(fcntl(fd, F_SETFL, sFlags) == -1)
        return false;

    // return success
    return true;
}

bool SerialController::set_ModeNonblocking(void) {
    int sFlags = fcntl(fd, F_GETFL, 0);

    if(sFlags == -1)
        return false;

    sFlags |= O_NONBLOCK;

    if(fcntl(fd, F_SETFL, sFlags) == -1)
        return false;

    // return success
    return true;
}

int SerialController::hasData(void) {
    int bAvail;
    ioctl(fd, FIONREAD, &bAvail);
    return bAvail;
}

int SerialController::get_FileDescriptor(void) {
    return fd;
}

#endif // __JJC__RS232GENERIC__H__
