// FIFO
// Charles Alan Macon
// David Cmar
// Noah Kindervag
#include "gen_proc.h"

using namespace std;

int main()
{
	processes* proc = new processes();
	int time = 0;
	int currentProcess = 0;
	int waitingTime = 0;
	int avgWaitingTime = 0;
	int contextPenalty = 0;
	
	for (int i = 0; i < NUM_OF_PROC; i++)
	{
		// Show us our list of processes
		cout << "ID: " << proc->procs[i].getID() << "\tcpu: " << proc->procs[i].get_cycles() << "\tmem: " << proc->procs[i].get_mem() << "\tarr: " << proc->procs[i].get_arr() << endl;
	}
	
	// Unlike the other methods, we're not going to count the number of finished processes,
	// because we're completing them in the same order that we're getting them. As such,
	// once we finish the last process, we're done with all of them. Badda-bing, badda-boom.
	while (currentProcess < NUM_OF_PROC)
	{
		// Get process start time, wait until start time
		int currentProcessStartTime = proc->procs[currentProcess].get_arr();
		cout << "Time: " << time << endl;
		cout << "Current Process: " << currentProcess << endl;
		
		// If we're at the start time for this particular process:
		if (currentProcessStartTime <= time)
		{
			// This is a nice method of determining how long a process has been waiting.
			// If only it were this nice in RR.
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
			
			// Move to next process
			currentProcess++;
			
			// Context switch penalty
			for (int i = 0; i < 10; i++)
			{
				time++;
				contextPenalty++;
			}
		}
		else
		{
			// Otherwise announce that we're waiting for a new process
			cout << "Waiting for next process to arrive" << endl;
			time++;
		}
	}
	 
	// Easy as pie. Calculate the average waiting time and spit everything out.
	avgWaitingTime = waitingTime / NUM_OF_PROC;
	cout << "Finished FIFO simulation at time: " << time << endl;
	cout << "Average FIFO waiting time: " << avgWaitingTime << endl;
	cout << "Total context switch penalty: " << contextPenalty << endl;
	return 0;
}