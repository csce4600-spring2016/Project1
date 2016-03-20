// SJF - Charles Alan Macon
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
		cout << "Time: " << time << endl;
		cout << "Current Process: " << currentProcess << endl;
		
		if (currentProcessStartTime <= time)
		{
			waitingTime += (time - currentProcessStartTime);
			cout << "Running process" << endl;
			
			// Get # of cycles in current process
			int currentProcessCycles = proc->procs[currentProcess].get_cycles();
			cout << "Current Process Cycles: " << currentProcessCycles << endl;
			
			// Simulate process
			for (currentProcessCycles; currentProcessCycles > 0; currentProcessCycles--)
			{
				time++;
			}
			
			// mark process as complete
			proc->procs[currentProcess].set_finished_state(true);
			numFinishedProc++;
			
			int nextProcess = 0;
			// find next process
			for (int i = 0; i < NUM_OF_PROC; i++)
			{
				if (proc->procs[i].get_finished_state() == false)
				{
					if (proc->procs[nextProcess].get_finished_state() == false)
					{
						if (proc->procs[i].get_cycles() < proc->procs[nextProcess].get_cycles())
						{
							nextProcess = i;
						}
					}
					else
					{
						nextProcess = i;
					}
				}
				else
				{
					// skip it, it's already done.
				}
			}
			
			currentProcess = nextProcess;
			// Context switch penalty
			for (int i = 0; i < 10; i++)
			{
				time++;
				contextPenalty++;
			}
		}
		else
		{
			cout << "Waiting for next process to arrive" << endl;
			time++;
		}
	}
	
	avgWaitingTime = waitingTime / NUM_OF_PROC;
	cout << "Finished SJF simulation at time: " << time << endl;
	cout << "Average SJF waiting time: " << avgWaitingTime << endl;
	cout << "Total context switch penalty: " << contextPenalty << endl;
	return 0;
}