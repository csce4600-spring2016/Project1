// Project #2
// Charles Alan Macon
// Noah Kindervag

#include "gen_proc.h"

using namespace std;

int64_t GetCPUCount( unsigned int loword, unsigned int hiword )
{
	__asm__ __volatile__ ("rdtsc" : "=a" (loword), "=d" (hiword));
	return ( (int64_t) hiword << 32) + loword;
}

int main()
{
	processes* proc = new processes();
	processes* proc_2 = proc;
	processes* proc_3a = proc;
	processes* proc_3b = proc;	// So we're using the same data for all of them.
	int time2 = 0;
	int currentProcess = 0;
	int waitingTime = 0;
	int avgWaitingTime = 0;
	int numFinishedProc = 0;
	int contextPenalty = 0;
	
	clock_t t1;
	clock_t t2;
	clock_t t3a;
	clock_t t3b;
	
	time_t now;
	time_t then;
	
	double part1Time = 0;
	double part2Time = 0;
	double part3aTime = 0;
	double part3bTime = 0;
	
	

	for (int i = 0; i < NUM_OF_PROC; i++)
	{
		// Show us our list of processes
		cout << "ID: " << proc->procs[i].getID() << "\tcpu: " << proc->procs[i].get_cycles() << "\tmem: " << proc->procs[i].get_mem() << "\tarr: " << proc->procs[i].get_arr() << endl;
	}
	
	// Part 1 - malloc() and free()
	
	unsigned int hi = 0, lo = 0;
	double T = GetCPUCount( lo, hi );
	while (currentProcess < NUM_OF_PROC)
	{
		int currentProcessStartTime = proc->procs[currentProcess].get_arr();
		
		// If the current process was supposed to have started by now, do things.
		if (currentProcessStartTime <= time2)
		{
			// Here we do things.
			if (proc->procs[currentProcess].get_finished_state() == false)
			{
				cout << "Executing Process: " << currentProcess << endl;
				// get system start time.
				
				// get number of cycles
				int currentProcessCycles = proc->procs[currentProcess].get_cycles();
				
				// get memory footprint
				int currentProcessMemFootprint = proc->procs[currentProcess].get_mem();
				
				// allocate memory with malloc()
				cout << "Allocating " << currentProcessMemFootprint << "kb in memory" << endl;
				
				char * mem;
				mem = (char*) malloc (currentProcessMemFootprint * 1024);
				
				// "Run" process
				
				for (currentProcessCycles; currentProcessCycles > 0; currentProcessCycles--)
				{
					// Don't really have to do anything here
					time2++;
					//cout << currentProcessCycles << endl;
				}
				
				// free memory with free()
				free (mem);
				
				currentProcess++;
				// stop clock and record
			}
		}
	}
	int64_t CycleCount = GetCPUCount( lo, hi ) - T;
	
	// Reset currentProcess
	currentProcess = 0;
	time2 = 0;

	// Part 2 - my_malloc() and my_free()
	t2 = clock();
	while (currentProcess < NUM_OF_PROC)
	{
		int currentProcessStartTime = proc_2->procs[currentProcess].get_arr();
		
		// If the current process was supposed to have started by now, do things.
		if (currentProcessStartTime <= time2)
		{
			// Here we do things.
			if (proc_2->procs[currentProcess].get_finished_state() == false)
			{
				cout << "Executing Process: " << currentProcess << endl;
				// get system start time.
				
				// get number of cycles
				int currentProcessCycles = proc_2->procs[currentProcess].get_cycles();
				
				// get memory footprint
				int currentProcessMemFootprint = proc_2->procs[currentProcess].get_mem();
				
				// allocate memory with my_malloc()
				cout << "Allocating " << currentProcessMemFootprint << "kb in memory" << endl;
				
				// "Run" process
				
				for (currentProcessCycles; currentProcessCycles > 0; currentProcessCycles--)
				{
					// Don't really have to do anything here
					time2++;
					//cout << currentProcessCycles << endl;
				}
				
				// free memory with my_free()
				
				currentProcess++;
				// stop clock and record
			}
		}
	}
	t2 = clock() - t2;
	part2Time = ((double)t2)/CLOCKS_PER_SEC;
	
	// Part 3a - System has 50% needed memory
	t3a = clock();
	//Stuff here
	t3a = clock() - t3a;
	part3aTime = ((double)t3a)/CLOCKS_PER_SEC;
	
	// Part 3b - System has 10% needed memory
	t3b = clock();
	t3b = clock() - t3b;
	part3bTime = ((double)t3b)/CLOCKS_PER_SEC;
	
	cout << "Part 1 in cycles:  " << CycleCount << endl;
	cout << "Part 2 in seconds:  " << part2Time << endl;
	cout << "Part 3a in seconds: " << part3aTime << endl;
	cout << "Part 3b in seconds: " << part3bTime << endl;
}