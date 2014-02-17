#ifndef TERMIOSWRAPPER_H
#define TERMIOSWRAPPER_H

#include <termios.h>

class TermiosWrapper
{
public:
    TermiosWrapper();
    int GetX();
    int GetY();
    int GetZ();
    void ReadChar();
    void Close();

private:
    struct termios tio;
    struct termios stdio;
    struct termios old_stdio;
    int tty_fd;
    unsigned char c;
};

#endif // TERMIOSWRAPPER_H
