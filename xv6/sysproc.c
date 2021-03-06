#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  int status; // CS 153
  argint(0, &status); // CS 153
  exit(status); // CS 153
  return 0;  // not reached
}

int
sys_wait(void)
{
  int *status; // CS 153
  argptr(0, (char**)&status, 1); // CS 153
  return wait(status); // CS 153
}

int // CS 153
sys_waitpid(void) // CS 153 // probably need to work on this function more
{ // CS 153
  int *status; // CS 153
  int pid; // CS 153
  int options; // CS 153
  
  if(argint(0, &pid) < 0) // CS 153
    return -1; // CS 153
  
  argptr(1, (char**)&status, 1); // CS 153
  
  if (argint(2, &options) < 0) // CS 153
    return -1; // CS 153
  
  return waitpid(pid, status, options); // CS 153
} // CS 153

int //CS 153
sys_setPriority(void) // CS 153 // finish
{
  int pc; // CS 153
  
  if (argint(0, &pc) < 0) // CS 153
  {
    return -1; // CS 153
  }
  
  return setPriority(pc); // CS 153
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}
