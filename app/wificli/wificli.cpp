#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stddef.h>
#include <stdint.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <boost/timer/timer.hpp>

#include "udpc.h"

#define DEBUG		1

using namespace std;
bool ex = false;

int main() {
	udps *pc = new(udps);
	int c = 0;
    	while(!ex){
#ifdef DEBUG
		cout << "main " << (int)pc->sm << endl;
#endif
		pc->recv();
		if(pc->con)pc->process();
		switch(pc->sm){
		case(STOP):{
			pdu p;
			p.pdu_type = INIT;
			p.len = HEADER_LEN;
			pc->txfifo.push_back(p);
			sleep(1);
			break;
		}
		case(CFG):{
			pc->sm = CFG;
			sleep(1);
			break;
		}
		case(KAL):{
			break;
		}
		}
		pc->send();
		sleep(1);
    	}
	delete pc;
   	return 0;
}
