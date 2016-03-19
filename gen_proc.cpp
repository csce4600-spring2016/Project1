#include "gen_proc.h"
using namespace std;
process::process(int new_id, int new_cyc, int new_mem, int new_arr)
{
	id = new_id;
	cycles = new_cyc;
	memory_size = new_mem;
	arrival_time = new_arr;
	is_finished = false;
}
int process::getID(void)
{
	return id;
}
int process::get_cycles(void)
{
	return cycles;
}
int process::get_mem(void)
{
	return memory_size;
}

int process::get_arr(void)
{
	return arrival_time;
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
		/*
		for (int i=0; i<12; i++)
		{
			randoms[i] = rand()%130;
			mem_time+=randoms[i];
		}*/
		/* clean up memory generation */
		/*mem_time/=12;
		mem_time = mem_time*0.2-30;
		if (mem_time<1)
		{
			mem_time=rand()%50+1;
		}*/
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