#include <math.h>
#include <fstream>
#include <stddef.h>
#include <stdint.h>
#include <string>
#include <vector>
#include <sstream>

#include "udpc.h"

#define	DEBUG		1

using namespace std;
extern bool ex;

udps::~udps(){
	close(sockfd);
	cout<<"Object Com Erased"<<endl;
}
udps::udps(){
	state = true;
	if((sockfd = socket(AF_INET,SOCK_DGRAM, 0)) < 0 ){
        	state = false;
		cout << "socket failed " << endl;
		return;
	}
	bzero(&seraddr,sizeof(seraddr));
	bzero(&cliaddr,sizeof(cliaddr));
	seraddr.sin_family  = AF_INET;
	//seraddr.sin_addr.s_addr = INADDR_ANY;
	inet_pton(AF_INET, "192.168.1.106", &(seraddr.sin_addr));
	seraddr.sin_port = htons(stoi(string(PORT)));
	/*
	if(bind(sockfd, (const struct sockaddr *)&seraddr,sizeof(seraddr)) < 0 ){ 
        	state = false;
		cout << "bind failed " << endl;
		return;
    	}	
       */	
	con = false;
	sm = STOP;
	timeout.tv_sec = 0;
        timeout.tv_usec = 10;
        setsockopt(sockfd,SOL_SOCKET,SO_RCVTIMEO,&timeout,sizeof(timeout));
	
	cfg.push_back(SSID);
	cfg.push_back(PASS);
	cfg.push_back(IP);
	cfg.push_back(PORT);
	cfg.push_back(FILE_BEEP);
	cfg.push_back(FILE_BLIP);
	cfg.push_back(FILE_RING);
	cfg.push_back(FILE_SZ);
}

void udps::recv(void){
	int n = -1;
	socklen_t len  = sizeof(cliaddr);
	unsigned char buffer[BUF_LEN];
	n = recvfrom(sockfd,(char *)buffer,BUF_LEN,MSG_WAITALL,( struct sockaddr *) &cliaddr,&len); 
	if(n > 0){
		pdu p;
		memcpy((void *)&p,buffer,n);
		if(n == p.len){
#ifdef	DEBUG
			printf("%s RECV->BYTES:%d TYPE:%d\n",inet_ntop(AF_INET,&cliaddr.sin_addr,(char *)&buffer,BUF_LEN),n,(int)p.pdu_type);
#endif
			if(p.pdu_type == INIT){
				con = true;
				sm = RUN;
			}else rxfifo.push_back(p);
		}
	}
}
void udps::send(void){
	if(txfifo.size()){
		pdu p = txfifo[0];
		int n = -1;
		n = sendto(sockfd,(const char *)&p,p.len,MSG_CONFIRM, (const struct sockaddr *) &seraddr,sizeof(seraddr)); 
		if(n == p.len){
#ifdef	DEBUG
			printf("SEND->BYTES:%d TXQ:%d TYPE:%d\n",n,txfifo.size(),(int)p.pdu_type);
#endif
			txfifo.erase(txfifo.begin());
			sleep(1);
		}
	}
}
void udps::process(void){
	if(rxfifo.size()){
		pdu p = rxfifo[0];
		switch(p.pdu_type){
		case(GCFG):{
			if(sm != RUN)break;
			string msg(SSID);
			msg += string(":")+string(PASS)+string(":")+string(IP)+string(":")+string(PORT)+string(":")+string(FILE_BEEP)+string(":")+string(FILE_BLIP)+string(":")+string(FILE_RING)+string(":")+string(FILE_SZ)+string(":");
			printf("%s\n",msg.c_str());
			p.pdu_type = GCFG;
			p.len = HEADER_LEN+msg.length();
			memcpy(p.data,msg.data(),msg.length());
			txfifo.push_back(p);
			sm = CFG;
			break;
		}
		case(KALV):{
			sm = KAL;
			p.pdu_type = KALV;
			p.len = HEADER_LEN;
			txfifo.push_back(p);
			break;
		}
		}
		rxfifo.erase(rxfifo.begin());
	}
}
