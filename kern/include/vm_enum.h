#ifndef _VM_ENUM_H_
#define _VM_ENUM_H_

typedef enum {
  AX_READ = 4,
  AX_WRITE = 2,
  AX_EXECUTE = 1
} ax_permssion;


typedef enum {
<<<<<<< HEAD
	PS_FREE  = 1,
	PS_FIXED = 2,
	PS_CLEAN = 3,
	PS_DIRTY = 4,
	PS_VICTIM = 5
} page_state;


=======
	PS_FREE,
	PS_FIXED,
	PS_CLEAN,
	PS_DIRTY,
	PS_VICTIM
} page_state;

>>>>>>> 303fbe623dd51568515426c72523015c03df50f1
typedef enum{
	PTE_ONDISK = 1,
	PTE_LOCKED = 2
} pte_state;

#endif
