// FIFO (Quad core) - Charles Alan Macon
#include "gen_proc.h"

using namespace std;

int main()
{
	processes* proc = new processes();
	int time = 0;
	int currentProcess[4] = {0, 1, 2, 3};
	int numFinishedProc = 0;
	int waitingTime = 0;
	int avgWaitingTime = 0;
	int contextPenalty = 0;
	int context[4] = {0, 0, 0, 0};
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
		
		// add first four waiting times to waiting time
		waitingTime += (0 + 50 + 100 + 150);
	}
	
	while (numFinishedProc < NUM_OF_PROC)
	{
		// So, this is a little tricky, because I can't use for loops. I need to do this iteration by iteration.
		cout << time << endl;
		// Core 0
		if (context[0] == 0)
		{
			if (proc->procs[currentProcess[0]].get_cycles() > 0)
			{
				cout << "Core 0 process ID: " << currentProcess[0] << "\tRemaining Cycles: " << proc->procs[currentProcess[0]].get_cycles() <<endl;
			}
			else
			{
				cout << "Core 0 idle" << endl;
			}
			// We need to make sure the process we have is: (locked in && not finished).
			if (proc->procs[currentProcess[0]].get_locked_state() == true && proc->procs[currentProcess[0]].get_finished_state() == false && proc->procs[currentProcess[0]].get_arr() <= time)
			{
				// Need to get waiting time ONCE
				
				// if "currentProcess" still has cycles, we need to subtract one from it
				if (proc->procs[currentProcess[0]].get_cycles() > 1)
				{
					int cycles = proc->procs[currentProcess[0]].get_cycles();
					proc->procs[currentProcess[0]].set_cycles(cycles - 1);
				}
				else
				{
					// otherwise, we need to mark it finished and add one to numFinishedProc
					int cycles = proc->procs[currentProcess[0]].get_cycles();
					proc->procs[currentProcess[0]].set_cycles(cycles - 1);
					proc->procs[currentProcess[0]].set_finished_state(true);
					numFinishedProc++;
					
					// then, we need to find the next unlocked process, set that as our next
					// process, lock it, and set context to 10.
					
					for (int i = 0; i < NUM_OF_PROC; i++)
					{
						if (proc->procs[i].get_locked_state() == false)
						{
							proc->procs[i].set_locked_state(true); // lock it down!
							waitingTime += (time - (proc->procs[i].get_arr() + 10));	// set waitingTime to after context switch.
							currentProcess[0] = i;
							i = NUM_OF_PROC;
							context[0] = 10;
						}
					}
				}
			}
		}
		else
		{
			context[0] = context[0] - 1;
			contextPenalty++;
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
			if (proc->procs[currentProcess[1]].get_locked_state() == true && proc->procs[currentProcess[1]].get_finished_state() == false && proc->procs[currentProcess[1]].get_arr() <= time)
			{
				// Need to get waiting time ONCE
				
				// if "currentProcess" still has cycles, we need to subtract one from it
				if (proc->procs[currentProcess[1]].get_cycles() > 1)
				{
					int cycles = proc->procs[currentProcess[1]].get_cycles();
					proc->procs[currentProcess[1]].set_cycles(cycles - 1);
				}
				else
				{
					// otherwise, we need to mark it finished and add one to numFinishedProc
					int cycles = proc->procs[currentProcess[1]].get_cycles();
					proc->procs[currentProcess[1]].set_cycles(cycles - 1);
					proc->procs[currentProcess[1]].set_finished_state(true);
					numFinishedProc++;
					
					// then, we need to find the next unlocked process, set that as our next
					// process, lock it, and set context to 10.
					
					for (int i = 0; i < NUM_OF_PROC; i++)
					{
						if (proc->procs[i].get_locked_state() == false)
						{
							proc->procs[i].set_locked_state(true); // lock it down!
							waitingTime += (time - (proc->procs[i].get_arr() + 10));	// set waitingTime to after context switch.
							currentProcess[1] = i;
							i = NUM_OF_PROC;
							context[1] = 10;
						}
					}
				}
			}
		}
		else
		{
			context[1] = context[1] - 1;
			contextPenalty++;
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
			
			// We need to make sure the process we have is: (locked in && not finished).
			if (proc->procs[currentProcess[2]].get_locked_state() == true && proc->procs[currentProcess[2]].get_finished_state() == false && proc->procs[currentProcess[2]].get_arr() <= time)
			{
				// Need to get waiting time ONCE
				
				// if "currentProcess" still has cycles, we need to subtract one from it
				if (proc->procs[currentProcess[2]].get_cycles() > 1)
				{
					int cycles = proc->procs[currentProcess[2]].get_cycles();
					proc->procs[currentProcess[2]].set_cycles(cycles - 1);
				}
				else
				{
					// otherwise, we need to mark it finished and add one to numFinishedProc
					int cycles = proc->procs[currentProcess[2]].get_cycles();
					proc->procs[currentProcess[2]].set_cycles(cycles - 1);
					proc->procs[currentProcess[2]].set_finished_state(true);
					numFinishedProc++;
					
					// then, we need to find the next unlocked process, set that as our next
					// process, lock it, and set context to 10.
					
					for (int i = 0; i < NUM_OF_PROC; i++)
					{
						if (proc->procs[i].get_locked_state() == false)
						{
							proc->procs[i].set_locked_state(true); // lock it down!
							waitingTime += (time - (proc->procs[i].get_arr() + 10));	// set waitingTime to after context switch.
							currentProcess[2] = i;
							i = NUM_OF_PROC;
							context[2] = 10;
						}
					}
				}
			}
		}
		else
		{
			context[2] = context[2] - 1;
			contextPenalty++;
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
			if (proc->procs[currentProcess[3]].get_locked_state() == true && proc->procs[currentProcess[3]].get_finished_state() == false && proc->procs[currentProcess[3]].get_arr() <= time)
			{
				// Need to get waiting time ONCE
				
				// if "currentProcess" still has cycles, we need to subtract one from it
				if (proc->procs[currentProcess[3]].get_cycles() > 1)
				{
					int cycles = proc->procs[currentProcess[3]].get_cycles();
					proc->procs[currentProcess[3]].set_cycles(cycles - 1);
				}
				else
				{
					// otherwise, we need to mark it finished and add one to numFinishedProc
					int cycles = proc->procs[currentProcess[3]].get_cycles();
					proc->procs[currentProcess[3]].set_cycles(cycles - 1);
					proc->procs[currentProcess[3]].set_finished_state(true);
					numFinishedProc++;
					
					// then, we need to find the next unlocked process, set that as our next
					// process, lock it, and set context to 10.
					
					for (int i = 0; i < NUM_OF_PROC; i++)
					{
						if (proc->procs[i].get_locked_state() == false)
						{
							proc->procs[i].set_locked_state(true); // lock it down!
							waitingTime += (time - (proc->procs[i].get_arr() + 10));	// set waitingTime to after context switch.
							currentProcess[3] = i;
							i = NUM_OF_PROC;
							context[3] = 10;
						}
					}
				}
			}
		}
		else
		{
			context[3] = context[3] - 1;
			contextPenalty++;
		}
		// Unbiased Clock
		time++;		
	}
	
	avgWaitingTime = waitingTime / NUM_OF_PROC;
	cout << "Finished FIFO_QUAD simulation at time: " << time << endl;
	cout << "Average FIFO_QUAD waiting time: " << avgWaitingTime << endl;
	cout << "Total context switch penalty: " << contextPenalty << endl;
	return 0;
}