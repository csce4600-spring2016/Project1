#include "gen_proc.h"
using namespace std;
int main (void)
{
	processes* proc = new processes();
	for (int i=0; i<NUM_OF_PROC; i++)
	{
		cout<<"ID: "<<proc->procs[i].getID()<<"\tcpu: "<<proc->procs[i].get_cycles()<<"\tmem: "<<proc->procs[i].get_mem()<<"\n";
	}
	/* for testing *//*
	for (int i=0; i<NUM_OF_PROC; i++)
	{
		cout<<"id:\t"<<proc[i].getID();
	}
	/* end testing */
	return 0;
}