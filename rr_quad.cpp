// RR2 (Quad core) - Charles Alan Macon
#include "gen_proc.h"

using namespace std;

// GLOBAL VARIABLES ARE EVIL (but feel so good)
processes* proc = new processes();
int timeClick = 0;
int numFinishedProc = 0;
int waitingtimeClick = 0;
int currentProcess[4] = {0, 1, 2, 3};
int quantum[4] = {50, 50, 50, 50};
int context[4] = {0, 0, 0, 0};

void processor(int p)
{
	if (proc->procs[currentProcess[p]].get_locked_state() == true && proc->procs[currentProcess[p]].get_finished_state() == false && proc->procs[currentProcess[p]].get_arr() <= timeClick)
			{
				// Need to get waiting timeClick ONCE
				
				// if "currentProcess" still has cycles, we need to subtract one from it
				if (proc->procs[currentProcess[p]].get_cycles() > 1 && quantum[p] > 1)
				{
					int cycles = proc->procs[currentProcess[p]].get_cycles();
					proc->procs[currentProcess[p]].set_cycles(cycles - 1);
					quantum[p]--;
				}
				else if (quantum[p] == 1 && proc->procs[currentProcess[p]].get_cycles() > 1)
				{
					int cycles = proc->procs[currentProcess[p]].get_cycles();
					proc->procs[currentProcess[p]].set_cycles(cycles - 1);
					
					// the last four processes shouldn't switch context
					// Once they're locked in at that point, they should stay locked in, because
					// They're the last processes for that core. Round Robin is finished at that point.
					
					// My reasoning is this: Once the RR algorithm hits the very last process, it should just
					// finish that process, not keep doing context switches every time the quantum is up.
					// Seeing as we have 4 cores, should they not work the same way?
					if(numFinishedProc < NUM_OF_PROC - 4)
					{
						proc->procs[currentProcess[p]].set_time_stopped(timeClick);
						context[p] = 10;
						quantum[p] = 50;
					}
				}
				else
				{
					// otherwise, we need to mark it finished and add one to numFinishedProc
					int cycles = proc->procs[currentProcess[p]].get_cycles();
					proc->procs[currentProcess[p]].set_cycles(cycles - 1);
					proc->procs[currentProcess[p]].set_finished_state(true);
					numFinishedProc++;
							
					context[p] = 10;
				}
			}
	return;
}

int findNextProcess(int core)
{
	int cp = currentProcess[core];
	int oldp = cp;
	bool foundNextProcess = false;
	proc->procs[cp].set_locked_state(false);	// unlock current process
	
	while (!foundNextProcess)
	{
		if (cp < 49)
		{
			cp++;
			
			if (proc->procs[cp].get_locked_state() == false && proc->procs[cp].get_finished_state() == false)
			{
				foundNextProcess = true;
			}
		}
		else
		{
			cp = 0;
			
			if (proc->procs[cp].get_locked_state() == false && proc->procs[cp].get_finished_state() == false)
			{
				foundNextProcess = true;
			}
		}
		
		if (cp == oldp)
		{
			cout << "Core " << core << " has no more processes" << endl;
			foundNextProcess = true;
		}
	}
	
	proc->procs[cp].set_locked_state(true); // lock it up
	waitingtimeClick += (timeClick - (proc->procs[cp].get_time_stopped())); // this isn't right
	return cp;
}

int main()
{
	//processes* proc = new processes();
	//int timeClick = 0;
	//int currentProcess[4] = {0, 1, 2, 3};
	//int numFinishedProc = 0;
	//int waitingtimeClick = 0;
	int avgWaitingtimeClick = 0;
	int contextPenalty = 0;
	//int context[4] = {0, 0, 0, 0};
	int cycles[4] = {0, 0, 0, 0};
	
	for (int i = 0; i < NUM_OF_PROC; i++)
	{
		// Show us our list of processes
		cout << "ID: " << proc->procs[i].getID() << "\tcpu: " << proc->procs[i].get_cycles() << "\tmem: " << proc->procs[i].get_mem() << "\tarr: " << proc->procs[i].get_arr() << endl;
	}
	
	for (int i = 0; i < 4; i++)
	{
		// lock first four processes to their CPUs
		proc->procs[currentProcess[i]].set_locked_state(true);
		
		// add first four waiting timeClicks to waiting timeClick
		waitingtimeClick += (0 + 50 + 100 + 150);
	}
	
	while (numFinishedProc < NUM_OF_PROC)
	{
		// So, this is a little tricky, because I can't use for loops. I need to do this iteration by iteration.
		cout << timeClick << endl;
		// Core 0
		if (context[0] == 0)
		{
			if (proc->procs[currentProcess[0]].get_cycles() > 0)
			{
				cout << "Core 0 process ID: " << currentProcess[0] << "\tRemaining Cycles: " << proc->procs[currentProcess[0]].get_cycles() <<endl;
			}
			else
			{
				cout << proc->procs[currentProcess[0]].get_cycles() << endl;
				cout << "Core 0 idle" << endl;
			}
			// We need to make sure the process we have is: (locked in && not finished).
			processor(0);
		}
		else
		{
			cout << "Core 0 context switching" << endl;
			context[0] = context[0] - 1;
			contextPenalty++;
			
			// if context penalty is now 0, unlock the process
			// and switch current process over. (THIS MEANS NOT FINDING NEXT PROCESS UNTIL HERE)
			if (context[0] == 0)
			{
				currentProcess[0] = findNextProcess(0);
			}
			
		}
		// Core 1
		if (context[1] == 0)
		{
			if (proc->procs[currentProcess[1]].get_cycles() > 0)
			{
				cout << "Core 1 process ID: " << currentProcess[1] << "\tRemaining Cycles: " << proc->procs[currentProcess[1]].get_cycles() <<endl;
			}
			else
			{
				cout << "Core 1 idle" << endl;
			}
			// We need to make sure the process we have is: (locked in && not finished).
			processor(1);
		}
		else
		{
			
			context[1] = context[1] - 1;
			contextPenalty++;
			cout << "Core 1 context switching" << endl;
			// if context penalty is now 0, unlock the process
			// and switch current process over. (THIS MEANS NOT FINDING NEXT PROCESS UNTIL HERE)
			if (context[1] == 0)
			{
				currentProcess[1] = findNextProcess(1);
			}
		}
		// Core 2
		if (context[2] == 0)
		{
			if (proc->procs[currentProcess[2]].get_cycles() > 0)
			{
			cout << "Core 2 process ID: " << currentProcess[2] << "\tRemaining Cycles: " << proc->procs[currentProcess[2]].get_cycles() <<endl;
			}
			else
			{
				cout << "Core 2 idle" << endl;
			}
			
			processor(2);
		}
		else
		{
			context[2] = context[2] - 1;
			contextPenalty++;
			cout << "Core 2 context switching" << endl;
			// if context penalty is now 0, unlock the process
			// and switch current process over. (THIS MEANS NOT FINDING NEXT PROCESS UNTIL HERE)
			if (context[2] == 0)
			{
				currentProcess[2] = findNextProcess(2);
			}
		}
		// Core 3
		if (context[3] == 0)
		{
			if (proc->procs[currentProcess[3]].get_cycles() > 0)
			{
				cout << "Core 3 process ID: " << currentProcess[3] << "\tRemaining Cycles: " << proc->procs[currentProcess[3]].get_cycles() <<endl;
			}
			else
			{
				cout << "Core 3 idle" << endl;
			}
			// We need to make sure the process we have is: (locked in && not finished).
			processor(3);
		}
		else
		{
			context[3] = context[3] - 1;
			contextPenalty++;
			cout << "Core 3 context switching" << endl;
			// if context penalty is now 0, unlock the process
			// and switch current process over. (THIS MEANS NOT FINDING NEXT PROCESS UNTIL HERE)
			if (context[3] == 0)
			{
				currentProcess[3] = findNextProcess(3);
			}
		}
		// Unbiased Clock
		timeClick++;		
	}
	
	avgWaitingtimeClick = waitingtimeClick / NUM_OF_PROC;
	cout << "Finished RR_QUAD simulation at timeClick: " << timeClick << endl;
	cout << "Average RR_QUAD waiting timeClick: " << avgWaitingtimeClick << endl;
	cout << "Total context switch penalty: " << contextPenalty << endl;
	return 0;
}