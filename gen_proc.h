#ifndef __gen_proc__
#define __gen_proc__

#include <iostream>
#include <vector>
#include <cstdlib>
#include <time.h>
#define NUM_OF_PROC 50
using namespace std;

class process{
	private:
		int id;
		int cycles;
		int memory_size;
		int arrival_time;
	public:
		process(int new_id, int new_cyc, int new_mem, int new_arr);
		int getID(void);
		int get_cycles(void);
		int get_mem(void);
		int get_arr(void);
};
class processes{
	public:
		vector<process> procs;
		processes();
};
#endif