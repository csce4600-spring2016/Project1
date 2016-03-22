// RR2
// Charles Alan Macon
// David Cmar
// Noah Kindervag

// This was originally done as an exercise to see if I could think my way through it. One of the
// other members was "assigned" this task, but I got ahead of myself and finished it. Whoops.
// I'm a programmer, I write things to delegate tasks for me.
#include "gen_proc.h"

using namespace std;

int main()
{
	processes* proc = new processes();
	int time = 0;
	int currentProcess = 0;
	int waitingTime = 0;
	int avgWaitingTime = 0;
	int numFinishedProc = 0;
	int contextPenalty = 0;
	
	for (int i = 0; i < NUM_OF_PROC; i++)
	{
		// Show us our list of processes
		cout << "ID: " << proc->procs[i].getID() << "\tcpu: " << proc->procs[i].get_cycles() << "\tmem: " << proc->procs[i].get_mem() << "\tarr: " << proc->procs[i].get_arr() << endl;
	}
	
	while (numFinishedProc < NUM_OF_PROC)
	{
		int currentProcessStartTime = proc->procs[currentProcess].get_arr();
		
		// If the current process was supposed to have started by now, do things.
		if (currentProcessStartTime <= time)
		{
			// Here we do things.
			if (proc->procs[currentProcess].get_finished_state() == false)
			{
				// If the process hasn't already finished, actually do things.
				cout << "Time: " << time << endl;
				cout << "Current Process: " << currentProcess << endl;
				
				waitingTime += (time - proc->procs[currentProcess].get_time_stopped());
				cout << "Running Process" << endl;
			
				// Get # of cycles in current process
				int currentProcessCycles = proc->procs[currentProcess].get_cycles();
				cout << "Current Process Cycles: " << currentProcessCycles << endl;
				
				for (int i = 0; i < 50; i++)
				{
					// Quantum: 50
					if (currentProcessCycles > 0)
					{
						time++;
						currentProcessCycles--;
					}
					else
					{
						// If we're done with the process, we stop the clock and set it to finished.00
						proc->procs[currentProcess].set_finished_state(true);
					}
				}
				
				if (proc->procs[currentProcess].get_finished_state() == true)
				{
					// If we finished the process in the last state, make a note of it.
					numFinishedProc++;
				}
				else
				{
					// Otherwise, make note of when we stopped, and set how many cycles we
					// have left in that process.
					proc->procs[currentProcess].set_cycles(currentProcessCycles);
					proc->procs[currentProcess].set_time_stopped(time);
				}
				
				// CONTEXT SWITCH PENALTY MECHANISM. WHHOOOOA.
				if (numFinishedProc < (NUM_OF_PROC - 1))
				{
					for (int i = 0; i < 10; i++)
					{
						time++;
						contextPenalty++;
					}
				}
			}
			
			// Move to the next process, or loop back if we're at the end of the list.
			// This will continue on until we're out of processes.
			if (currentProcess < 49)
			{
				currentProcess++;
			}
			else
			{
				currentProcess = 0;
			}
			
		}
		else
		{
			cout << "Waiting for next process to arrive" << endl;
			time++;
		}
	}
	
	// Calculate things. Print out other things. Same old, same old.
	avgWaitingTime = waitingTime / NUM_OF_PROC;
	cout << "Finished RR simulation at time: " << time << endl;
	cout << "Average RR waiting time: " << avgWaitingTime << endl;
	cout << "Total context switch penalty: " << contextPenalty << endl;
	return 0;
}