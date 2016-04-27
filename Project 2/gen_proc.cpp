#include "gen_proc.h"
using namespace std;
process::process(int new_id, int new_cyc, int new_mem, int new_arr)
{
	id = new_id;
	cycles = new_cyc;
	memory_size = new_mem;
	arrival_time = new_arr;
	is_finished = false;
	is_locked = false;
	time_stopped = new_arr;
}
int process::getID(void)
{
	return id;
}
int process::get_cycles(void)
{
	return cycles;
}

void process::set_cycles(int c)
{
	cycles = c;
	return;
}

int process::get_mem(void)
{
	return memory_size;
}

int process::get_arr(void)
{
	return arrival_time;
}

int process::get_time_stopped(void)
{
	return time_stopped;
}

void process::set_time_stopped(int t)
{
	time_stopped = t;
	return;
}

bool process::get_locked_state(void)
{
	return is_locked;
}

void process::set_locked_state(bool s)
{
	is_locked = s;
	return;
}

bool process::get_finished_state(void)
{
	return is_finished;
}

void process::set_finished_state(bool s)
{
	is_finished = s;
	return;
}

processes::processes()
{
	int randoms[12];
	int id=0;
	int cpu_time=0, mem_time=0, arr_time=0;
	srand(time(NULL));
	for (int z=0; z<NUM_OF_PROC; z++)
	{
		for (int i=0; i<12; i++)
		{
			randoms[i] = rand()%10000 + 1000;
			cpu_time+=randoms[i];
		} 
		cpu_time/=12;
		
		// total mem_time has to be less than 20MB for all processes.
		// Okay, so basically what we're doing right now is taking this number
		// and multiplying it by 1024 to give us whatever number this is in Kb.
		// There's no reason why it shouldn't be less than 20MB.
		
		for (int i=0; i<3; i++)
		{
			randoms[i] = rand()%166;
			mem_time += randoms[i];
		}
		mem_time = mem_time *.2 - 30;
		if (mem_time < 1)
			mem_time = rand()%20 + 1;
		procs.push_back(process(id, cpu_time, mem_time, arr_time));
		arr_time += 50;
		id++;
	}

}