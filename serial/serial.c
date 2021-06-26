#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include <errno.h>

static int serial;


void serial_open(char *path) {
	// O_RDWR - Read/Write access to serial port
	// O_NOCTTY - No terminal will control the process
	// O_NDELAY - Non Blocking Mode,Does not care about the
	// status of DCD line, open() returns immediatly

	if ((serial = open(path, O_RDWR | O_NOCTTY | O_NDELAY)) < 0) {
		printf(" ERROR: serial open fail: %s\n%s\n", strerror(errno), path);
		exit(10);
	}

	// Set the attributes to the termios structure
	struct termios st;
	fcntl(serial, F_SETFL, FNDELAY);
	bzero(&st, sizeof(st));
	st.c_cflag = B115200 | CS8 | CLOCAL | CREAD;
	st.c_iflag = IGNPAR;
	tcflush(serial, TCIFLUSH);

	if ((tcsetattr(serial, TCSANOW, &st)) != 0) {
		printf(" ERROR: serial open fail: tcsetattr: %s\n", strerror(errno));
		exit(11);
	}
}

void serial_close() {
	close(serial);
}

void serial_send(char *buff, uint len) {
	int ret;
	uint i = 0;

	while (i < len) {
		ret = write(serial, buff + i, len - i);
		if (ret < 0) {
			if (errno == EAGAIN) {
				continue;
			} else {
				printf(" ERROR: serial write fail: %s\n", strerror(errno));
				exit(12);
			}
		}
		i = i + ret;
	}
	tcdrain(serial);
}

void serial_recv(char *buff, uint len) {
	int ret;
	uint i = 0;

	while (i < len) {
		ret = read(serial, buff + i, len - i);
		if (ret < 0) {
			printf(" ERROR: serial read fail: %s\n", strerror(errno));
			exit(13);
		}
		i = i + ret;
	}
}
