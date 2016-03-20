// RR2 - Charles Alan Macon
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
		
		
		if (currentProcessStartTime <= time)
		{
			if (proc->procs[currentProcess].get_finished_state() == false)
			{
				cout << "Time: " << time << endl;
				cout << "Current Process: " << currentProcess << endl;
				//need to figure out a new way to find waitingTime
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
						proc->procs[currentProcess].set_finished_state(true);
					}
				}
				
				if (proc->procs[currentProcess].get_finished_state() == true)
				{
					numFinishedProc++;
				}
				else
				{
					proc->procs[currentProcess].set_cycles(currentProcessCycles);
					proc->procs[currentProcess].set_time_stopped(time);
				}
				
				if (numFinishedProc < (NUM_OF_PROC - 1))
				{
					for (int i = 0; i < 10; i++)
					{
						time++;
						contextPenalty++;
					}
				}
			}
			
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
	
	avgWaitingTime = waitingTime / NUM_OF_PROC;
	cout << "Finished RR simulation at time: " << time << endl;
	cout << "Average RR waiting time: " << avgWaitingTime << endl;
	cout << "Total context switch penalty: " << contextPenalty << endl;
	return 0;
}