#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"
#include "vm.h"

uint64
sys_exit(void)
{
  int n;
  argint(0, &n);
  kexit(n);
  return 0; // not reached
}

uint64
sys_getpid(void)
{
  return myproc()->pid;
}

uint64
sys_fork(void)
{
  return kfork();
}

uint64
sys_wait(void)
{
  uint64 p;
  argaddr(0, &p);
  return kwait(p);
}

uint64
sys_sbrk(void)
{
  uint64 addr;
  int t;
  int n;

  argint(0, &n);
  argint(1, &t);
  addr = myproc()->sz;

  if (t == SBRK_EAGER || n < 0)
  {
    if (growproc(n) < 0)
    {
      return -1;
    }
  }
  else
  {
    // Lazily allocate memory for this process: increase its memory
    // size but don't allocate memory. If the processes uses the
    // memory, vmfault() will allocate it.
    if (addr + n < addr)
      return -1;
    if (addr + n > TRAPFRAME)
      return -1;
    myproc()->sz += n;
  }
  return addr;
}

uint64
sys_pause(void)
{
  int n;
  uint ticks0;

  argint(0, &n);
  if (n < 0)
    n = 0;
  acquire(&tickslock);
  ticks0 = ticks;
  while (ticks - ticks0 < n)
  {
    if (killed(myproc()))
    {
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

uint64
sys_kill(void)
{
  int pid;

  argint(0, &pid);
  return kkill(pid);
}

// return how many clock tick interrupts have occurred
// since start.
uint64
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}
// This sends a specific hardware signal to the QEMU motherboard to shut down.
uint64
sys_halt(void)
{
  *(volatile uint32 *)0x100000 = 0x5555;
  return 0;
}

uint64
sys_sigalarm(void)
{
  int n;
  uint64 fn;

  argint(0, &n);
  argaddr(1, &fn);

  if (n < 0)
    return -1;

  struct proc *p = myproc();
  p->alarm_interval = n;
  p->alarm_handler = (void (*)())fn;
  p->alarm_ticks = 0;

  return 0;
}

uint64
sys_sigreturn(void)
{
  struct proc *p = myproc();
  memmove(p->trapframe, p->alarm_tf, sizeof(struct trapframe));
  p->alarm_is_running = 0;
  return p->trapframe->a0;
}

extern struct spinlock shm_lock;
extern struct
{
  int key;
  uint64 pa;
} shm_table[8];

uint64
sys_shm_get(void)
{
  int key;
  argint(0, &key);

  uint64 pa = 0;
  acquire(&shm_lock);
  for (int i = 0; i < 8; i++)
  {
    if (shm_table[i].key == key && shm_table[i].pa != 0)
    {
      pa = shm_table[i].pa;
      break;
    }
  }

  if (pa == 0)
  {
    for (int i = 0; i < 8; i++)
    {
      if (shm_table[i].pa == 0)
      { // empty slot
        shm_table[i].key = key;
        shm_table[i].pa = (uint64)kalloc();
        if (shm_table[i].pa == 0)
        {
          release(&shm_lock);
          return -1;
        }
        memset((void *)shm_table[i].pa, 0, PGSIZE);
        pa = shm_table[i].pa;
        break;
      }
    }
  }
  release(&shm_lock);

  if (pa == 0)
    return -1; // no space

  struct proc *p = myproc();
  uint64 va = PGROUNDUP(p->sz);

  if (mappages(p->pagetable, va, PGSIZE, pa, PTE_W | PTE_R | PTE_U) != 0)
  {
    return -1;
  }

  p->sz = va + PGSIZE;
  return va;
}
