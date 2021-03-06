#include "termioswrapper.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "termios.h"

#include <QApplication>

TermiosWrapper::TermiosWrapper()
    : c('D')
{
    tcgetattr(STDOUT_FILENO, &old_stdio);
    /* Parse argv. */
    QStringList arguments = qApp->arguments();
    const char* argv0_ptr = arguments.at(0).toStdString().c_str();
    const char* argv1_ptr = arguments.at(1).toStdString().c_str();

    printf("Please start with %s /dev/ttyS1 (for example)\n", argv0_ptr);

    memset(&stdio,0,sizeof(stdio));
    stdio.c_iflag=0;
    stdio.c_oflag=0;
    stdio.c_cflag=0;
    stdio.c_lflag=0;
    stdio.c_cc[VMIN]=1;
    stdio.c_cc[VTIME]=0;
    tcsetattr(STDOUT_FILENO,TCSANOW,&stdio);
    tcsetattr(STDOUT_FILENO,TCSAFLUSH,&stdio);
    fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK); // make the reads non-blocking

    memset(&tio,0,sizeof(tio));
    tio.c_iflag=0;
    tio.c_oflag=0;
    tio.c_cflag=CS8|CREAD|CLOCAL; // 8n1, see termios.h for more information
    tio.c_lflag=0;
    tio.c_cc[VMIN]=1;
    tio.c_cc[VTIME]=5;

    tty_fd = open(argv1_ptr, O_RDWR | O_NONBLOCK);
    cfsetospeed(&tio, B38400);            // 38400 baud
    cfsetispeed(&tio, B38400);            // 38400 baud

    tcsetattr(tty_fd,TCSANOW,&tio);
}

void TermiosWrapper::ReadChar() {
    if (read(tty_fd, &c, 1) > 0) {
        write(STDOUT_FILENO, &c, 1);
        // handle char
    }
}

void TermiosWrapper::Close() {
    close(tty_fd);
    tcsetattr(STDOUT_FILENO,TCSANOW,&old_stdio);
}
