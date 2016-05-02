// Project #2
// Charles Alan Macon
// Noah Kindervag

#include "gen_proc.h"
#include <stdlib.h>

using namespace std;

int64_t GetCPUCount( unsigned int loword, unsigned int hiword )
{
	__asm__ __volatile__ ("rdtsc" : "=a" (loword), "=d" (hiword));
	return ( (int64_t) hiword << 32) + loword;
}

char* my_malloc(const int bytes_to_alloc, char* total_mem, int total_mem_size) {
    int bytes_free = 0;
    int offset; // loop counter, holds relative memory location

    // find the required number of free bytes in our total pool
    // since we aren't actually allocating memory at an OS level, we assume NULL is free
    for (offset = 0; offset < total_mem_size; offset++) {
        if (total_mem[offset] == 0) {
            bytes_free++;
        } else {
            bytes_free = 0;
        }

        if (bytes_free >= bytes_to_alloc) {
            break;
        }
    }

    // return pointer to beginning of allocated memory if found, otherwise 0
    if (bytes_free != bytes_to_alloc) {
        return 0;
    } else {
        return total_mem + offset - bytes_to_alloc + 1;
    }
}


void my_free(int length, char* allocated) {
    // as we don't have any access to OS-level memory management constructs
    // we must be given the length of the allocated memory space
    for (int i = 0; i < length; i++) {
        allocated[i] = 0;
    }
}

void run_malloc(processes* proc)
{
	int currentProcess = 0;
	int time2 = 0;
	
	for (int i = 0; i < NUM_OF_PROC; i++)
	{
		proc->procs[i].set_finished_state(false);
	}
	
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
	
	return;
}

void run_my_malloc(processes* proc_2, char* total_memory, int memsize)
{
	int currentProcess = 0;
	int time2 = 0;
	
	for (int i = 0; i < NUM_OF_PROC; i++)
	{
		proc_2->procs[i].set_finished_state(false);
	}
	
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
                char* mem = my_malloc(currentProcessMemFootprint*1024, total_memory, memsize);

				// "Run" process

				for (currentProcessCycles; currentProcessCycles > 0; currentProcessCycles--)
				{
					// Don't really have to do anything here
					time2++;
					//cout << currentProcessCycles << endl;
				}

				// free memory with my_free()
                my_free(currentProcessMemFootprint*1024, mem);

				currentProcess++;
				// stop clock and record
			}
		}
	}
	
	return;
}

bool run_malloc_with_queue(processes* proc, int memsize)
{
	int currentProcess = 0;
	int finishedProcesses = 0;
	int looptimes = 0;
	int time2 = 0;
	
	cout << "Entering malloc with queue" << endl;
	
	for (int i = 0; i < NUM_OF_PROC; i++)
	{
		proc->procs[i].set_finished_state(false);
	}
	
	while (finishedProcesses < NUM_OF_PROC)
	{
		int currentProcessStartTime = proc->procs[currentProcess].get_arr();
		//cout << currentProcess << endl;
		// If the current process was supposed to have started by now, do things.
		if (currentProcessStartTime <= time2)
		{
			if (proc->procs[currentProcess].get_mem() < (memsize / 1024))
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
					memsize = memsize - (currentProcessMemFootprint * 1024);

					// "Run" process

					for (currentProcessCycles; currentProcessCycles > 0; currentProcessCycles--)
					{
						// Don't really have to do anything here
						time2++;
						//cout << currentProcessCycles << endl;
					}
					
					proc->procs[currentProcess].set_finished_state(true);
					finishedProcesses++;
					cout << finishedProcesses << endl;
					
					// free memory with free()
					free (mem);
					memsize = memsize + (currentProcessMemFootprint * 1024);

					if (currentProcess == 63)
					{
						currentProcess = 0;
					}
					else
					{
						currentProcess++;
					}
					// stop clock and record
				}
			}
			else
			{
				looptimes++;
				
				if (looptimes > 100)
				{
					return false;
				}
				
				if (currentProcess == 63)
				{
					currentProcess = 0;
				}
				else
				{
					currentProcess++;
				}
			}
		}
	}
	
	return true;
}

bool run_my_malloc_with_queue(processes* proc_2, char* total_memory, int memsize)
{
	int currentProcess = 0;
	int finishedProcesses = 0;
	int looptimes = 0;
	int time2 = 0;
	
	cout << "Entering my_malloc with queue" << endl;
	
	for (int i = 0; i < NUM_OF_PROC; i++)
	{
		proc_2->procs[i].set_finished_state(false);
	}
	
	while (finishedProcesses < NUM_OF_PROC)
	{
		int currentProcessStartTime = proc_2->procs[currentProcess].get_arr();
		//cout << currentProcessStartTime << endl;
		// If the current process was supposed to have started by now, do things.
		if (currentProcessStartTime <= time2)
		{
			if (proc_2->procs[currentProcess].get_mem() < (memsize / 1024))
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
					char* mem = my_malloc(currentProcessMemFootprint*1024, total_memory, memsize);
					memsize = memsize - (currentProcessMemFootprint * 1024);
					// "Run" process

					for (currentProcessCycles; currentProcessCycles > 0; currentProcessCycles--)
					{
						// Don't really have to do anything here
						time2++;
						//cout << currentProcessCycles << endl;
					}
					
					proc_2->procs[currentProcess].set_finished_state(true);
					finishedProcesses++;
					cout << finishedProcesses << endl;

					// free memory with my_free()
					my_free(currentProcessMemFootprint*1024, mem);
					memsize = memsize + (currentProcessMemFootprint * 1024);

					if (currentProcess == 63)
					{
						currentProcess = 0;
					}
					else
					{
						currentProcess++;
					}
					// stop clock and record
				}
			}
			else
			{
				looptimes++;
				
				if (looptimes > 100)
				{
					return false;
				}
				
				if (currentProcess == 63)
				{
					currentProcess = 0;
				}
				else
				{
					currentProcess++;
				}
			}
		}
	}
	
	return true;
}


int main()
{
	processes* proc     = new processes();


	clock_t t1;
	clock_t t2;
	clock_t t3a;
	clock_t t3a2;
	clock_t t3b;
	clock_t t3b2;


	double part1Time   = 0;
	double part2Time   = 0;
	double part3aTime  = 0;
	double part3a2Time = 0;
	double part3bTime  = 0;
	double part3b2Time = 0;



	for (int i = 0; i < NUM_OF_PROC; i++)
	{
		// Show us our list of processes
		cout << "ID: " << proc->procs[i].getID() << "\tcpu: " << proc->procs[i].get_cycles() << "\tmem: " << proc->procs[i].get_mem() << "\tarr: " << proc->procs[i].get_arr() << endl;
	}

	//////////////////////////////////////////
	// Part 1 - malloc() and free()
	//////////////////////////////////////////

	unsigned int hi = 0, lo = 0;
	double T = GetCPUCount( lo, hi );
	
	run_malloc(proc);
		
	int64_t CycleCount = GetCPUCount( lo, hi ) - T;

    

	//////////////////////////////////////////
	// Part 2 - my_malloc() and my_free()
	//////////////////////////////////////////
	t2 = clock();
	
	T = GetCPUCount( lo, hi );

	char* total_memory = (char*) calloc(2097152,1); // Allocate and NULL-initialize 20MB
	int memsize = 2097152;
	
	run_my_malloc(proc, total_memory, memsize);
	
	free(total_memory);
	
	t2 = clock() - t2;
	part2Time = ((double)t2)/CLOCKS_PER_SEC;
	int64_t CycleCount2 = GetCPUCount( lo, hi ) - T;
  
	//////////////////////////////////////////
	// Part 3a - System has 50% needed memory
	//////////////////////////////////////////
	
	//Stuff here
	
	int totalMemFootprint = 0;
	
	for (int i = 0; i < NUM_OF_PROC; i++)
	{
		totalMemFootprint = totalMemFootprint + proc->procs[i].get_mem();
	}
	
	cout << totalMemFootprint << endl;
	// Needs to be 50% of needed memory.
	totalMemFootprint = totalMemFootprint / 2;
	cout << totalMemFootprint << endl;
	
	// Part 3a - Malloc
	t3a = clock();
	T = GetCPUCount( lo, hi );
	bool p3a = run_malloc_with_queue(proc, (totalMemFootprint * 1024));
	cout << "Test" << endl;
	t3a = clock() - t3a;
	part3aTime = ((double)t3a)/CLOCKS_PER_SEC;
	int64_t CycleCount3a = GetCPUCount( lo, hi ) - T;
	
	// Part 3a2 - My_Malloc
	t3a2 = clock();
	T = GetCPUCount( lo, hi );
	total_memory = (char*) calloc((totalMemFootprint * 1024),1); // Allocate and NULL-initialize 20MB
	bool p3a2 = run_my_malloc_with_queue(proc, total_memory, (totalMemFootprint * 1024));
	free(total_memory);
	t3a2 = clock() - t3a2;
	part3a2Time = ((double)t3a2)/CLOCKS_PER_SEC;
	int64_t CycleCount3a2 = GetCPUCount( lo, hi ) - T;
	
	
	
	
	//////////////////////////////////////////
	// Part 3b - System has 10% needed memory
	//////////////////////////////////////////

	// Stuff here
	
	totalMemFootprint = 0;
	
	for (int i = 0; i < NUM_OF_PROC; i++)
	{
		totalMemFootprint = totalMemFootprint + proc->procs[i].get_mem();
	}
	
	cout << totalMemFootprint << endl;
	// Needs to be 10% of needed memory.
	totalMemFootprint = totalMemFootprint / 10;
	cout << totalMemFootprint << endl;
	
	// Part 3b - Malloc
	t3b = clock();
	T = GetCPUCount( lo, hi );
	bool p3b = run_malloc_with_queue(proc, (totalMemFootprint * 1024));
	t3b = clock() - t3b;
	part3bTime = ((double)t3b)/CLOCKS_PER_SEC;
	int64_t CycleCount3b = GetCPUCount( lo, hi ) - T;
	
	// Part 3b2 - My_Malloc
	t3b2 = clock();
	T = GetCPUCount( lo, hi );
	total_memory = (char*) calloc((totalMemFootprint * 1024),1); // Allocate and NULL-initialize 20MB
	bool p3b2 = run_my_malloc_with_queue(proc, total_memory, (totalMemFootprint * 1024));
	free(total_memory);
	t3b2 = clock() - t3b2;
	part3b2Time = ((double)t3b2)/CLOCKS_PER_SEC;
	int64_t CycleCount3b2 = GetCPUCount( lo, hi ) - T;
	
	

	cout << "Part 1  - malloc() in cycles:     " << CycleCount << "\tIn Seconds: " << part1Time << endl;
	cout << "Part 2  - my_malloc() in cycles:  " << CycleCount2 << "\tIn Seconds: " << part2Time << endl;
	if (p3a == true)
	{
		cout << "Part 3a - malloc() in cycles:     " << CycleCount3a << "\tIn Seconds: " << part3aTime << endl;
	}
	else
	{
		cout << "Part 3a - malloc() in cycles: INF. \tIn Seconds: INF." << endl;
	}
	if (p3a2 == true)
	{
		cout << "Part 3a - my_malloc() in cycles:  " << CycleCount3a2 << "\tIn Seconds: " << part3a2Time << endl;
	}
	else
	{
		cout << "Part 3a - my_malloc() in cycles: INF. \tIn Seconds: INF." << endl;
	}
	if (p3b == true)
	{
		cout << "Part 3b - malloc() in cycles:     " << CycleCount3b << "\tIn Seconds: " << part3bTime << endl;
	}
	else
	{
		cout << "Part 3b - malloc() in cycles: INF. \tIn Seconds: INF." << endl;
	}
	if (p3b2 == true)
	{
		cout << "Part 3b - my_malloc() in cycles:  " << CycleCount3b2 << "\tIn Seconds: " << part3b2Time << endl;
	}
	else
	{
		cout << "Part 3b - my_malloc() in cycles: INF. \tIn Seconds: INF." << endl;
	}
}
