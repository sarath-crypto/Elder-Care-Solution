#ifndef UDPS_H
#define UDPS_H

#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sched.h>
#include <errno.h>
#include <getopt.h>
#include <inttypes.h>
#include <ctype.h>
#include <byteswap.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <math.h>
#include <boost/thread.hpp>
#include <condition_variable>
#include <netdb.h>
#include <time.h>
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 
#include <queue>

#define  PDU_MTU	1450
#define  HEADER_LEN	2
#define  BUF_LEN	1452
#define  WIFI_BEACON	5

#define  SSID		"myssid"
#define  PASS		"mypass"
#define  IP		"192.168.1.106"
#define  FLASH_SZ	"2949250"

#define  PORT		"8880"
#define  FILE_BEEP	"/beep.mp3#3984"
#define  FILE_BLIP	"/blip.mp3#5895"
#define  FILE_RING	"/ring.mp3#169735"
#define	 FILE_SZ	"181975"

using namespace std;

enum pdu_type{INIT = 1,GCFG,SCFG,FFMT,KALV,RSTD,ALRM};
enum sm{STOP = 1,RUN,CFG,KAL};

typedef struct pdu{
	unsigned char	pdu_type;
	unsigned char   len;
	unsigned char 	data[PDU_MTU];
}pdu;

class udps{
	private:
		int sockfd;
		struct sockaddr_in seraddr;
		struct sockaddr_in cliaddr;
		struct timeval timeout;
		vector<string>cfg;
	public:
		unsigned char sm;
		vector <pdu>txfifo;
		vector <pdu>rxfifo;
		bool state;
		bool con;
		udps();
		~udps();
		void recv(void);
		void send(void);
		void process(void);
};

#endif
