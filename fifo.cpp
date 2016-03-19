// FIFO - Charles Alan Macon
#include "gen_proc.h"

using namespace std;

int main()
{
	processes* proc = new processes();
	int time = 0;
	int currentProcess = 0;
	int waitingTime = 0;
	int avgWaitingTime = 0;
	
	for (int i = 0; i < NUM_OF_PROC; i++)
	{
		// Show us our list of processes
		cout << "ID: " << proc->procs[i].getID() << "\tcpu: " << proc->procs[i].get_cycles() << "\tmem: " << proc->procs[i].get_mem() << "\tarr: " << proc->procs[i].get_arr() << endl;
	}
	
	while (currentProcess < NUM_OF_PROC)
	{
		// Get process start time, wait until start time
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
				//cout << "Cycles Remaining: " << currentProcessCycles << endl;
				time++;
			}
			
			// Move to next process
			currentProcess++;
		}
		else
		{
			cout << "Waiting to start process" << endl;
			time++;
		}
	}
	
	avgWaitingTime = waitingTime / NUM_OF_PROC;
	cout << "Finished FIFO simulation at time: " << time << endl;
	cout << "Average FIFO waiting time: " << avgWaitingTime << endl;
	return 0;
}