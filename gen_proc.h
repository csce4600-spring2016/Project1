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
		int time_stopped;
		bool is_locked;
		bool is_finished;
	public:
		process(int new_id, int new_cyc, int new_mem, int new_arr);
		int getID(void);
		int get_cycles(void);
		void set_cycles(int c);
		int get_mem(void);
		int get_arr(void);
		int get_time_stopped(void);
		void set_time_stopped(int t);
		bool get_locked_state(void);
		void set_locked_state(bool s);
		bool get_finished_state(void);
		void set_finished_state(bool s);
};
class processes{
	public:
		vector<process> procs;
		processes();
};
#endif