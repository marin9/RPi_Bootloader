#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include <errno.h>


static int serial;


void serial_open(char *path){
	// O_RDWR - Read/Write access to serial port
	// O_NOCTTY - No terminal will control the process
	// O_NDELAY - Non Blocking Mode,Does not care about the
	// status of DCD line, open() returns immediatly
	if((serial=open(path, O_RDWR|O_NOCTTY|O_NDELAY))<0){
		printf("ERROR: serial_open: %s\n", strerror(errno));
		exit(1);
	}

	// Set the attributes to the termios structure
	struct termios st;
	fcntl(serial, F_SETFL, FNDELAY);
	bzero(&st, sizeof(st));
	st.c_cflag=B115200|CS8|CLOCAL|CREAD;
	st.c_iflag=IGNPAR;
	tcflush(serial, TCIFLUSH);
	
	if((tcsetattr(serial, TCSANOW, &st))!=0){
		printf("ERROR: tcsetattr: %s\n", strerror(errno));
		exit(2);
	}
}

void serial_close(){
	close(serial);
}

void serial_send(char *buff, int len){
	int r, i=0;
	while(i<len){
		r=write(serial, buff+i, len-i);
		if(r<0 && errno!=11){
			printf("ERROR: serial_write: %d %s\n", errno, strerror(errno));
			exit(3);
		}else if(r<0 && errno==11){
			continue;
		}
		i+=r;
	}
	tcdrain(serial);
}

void serial_recv(char *buff, int len){
	int r, i=0;
	while(i<len){
		r=read(serial, buff+i, len-i);
		if(r<0){
			printf("ERROR: serial_read: %s\n", strerror(errno));
			exit(4);
		}
		i+=r;
	}
}
