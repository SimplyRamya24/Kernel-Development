/*
 * Copyright (c) 2000, 2001, 2002, 2003, 2004, 2005, 2008, 2009
 *	The President and Fellows of Harvard College.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE UNIVERSITY AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE UNIVERSITY OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#ifndef _ADDRSPACE_H_
#define _ADDRSPACE_H_

/*
 * Address space structure and operations.
 */


// #include <vm.h>
#include "vm_enum.h"
#include "opt-dumbvm.h"
#include <wchan.h>
struct vnode;


/*
 * Address space - data structure associated with the virtual memory
 * space of a process.
 *
 */
<<<<<<< HEAD
extern struct cv *pte_cv;
extern struct lock *pte_lock;


struct state_field {
    unsigned int pte_lock_ondisk:2;
=======

struct state_field {
    int pte_lock_ondisk:2;
>>>>>>> 303fbe623dd51568515426c72523015c03df50f1
    int swap_index:12;
};

struct page_table_entry{
  vaddr_t vaddr;
  paddr_t paddr;
  // ax_permssion permission;
  struct state_field pte_state;
  struct page_table_entry * next;
};

struct region_entry{
  vaddr_t reg_base;
  size_t bounds;
  ax_permssion original_perm;
  ax_permssion backup_perm; //only for loadelf
  struct region_entry *next;
};

struct addrspace {
#if OPT_DUMBVM
        vaddr_t as_vbase1;
        paddr_t as_pbase1;
        size_t as_npages1;
        vaddr_t as_vbase2;
        paddr_t as_pbase2;
        size_t as_npages2;
        paddr_t as_stackpbase;
#else
        struct page_table_entry *page_table;
        struct region_entry* regions;
        vaddr_t heap_start;
        vaddr_t heap_end;
        vaddr_t stack_end;
        struct wchan *swap_wc;
#endif
};

/*
 * Functions in addrspace.c:
 *
 *    as_create - create a new empty address space. You need to make
 *                sure this gets called in all the right places. You
 *                may find you want to change the argument list. May
 *                return NULL on out-of-memory error.
 *
 *    as_copy   - create a new address space that is an exact copy of
 *                an old one. Probably calls as_create to get a new
 *                empty address space and fill it in, but that's up to
 *                you.
 *
 *    as_activate - make the specified address space the one currently
 *                "seen" by the processor. Argument might be NULL,
 *                meaning "no particular address space".
 *
 *    as_destroy - dispose of an address space. You may need to change
 *                the way this works if implementing user-level threads.
 *
 *    as_define_region - set up a region of memory within the address
 *                space.
 *
 *    as_prepare_load - this is called before actually loading from an
 *                executable into the address space.
 *
 *    as_complete_load - this is called when loading from an executable
 *                is complete.
 *
 *    as_define_stack - set up the stack region in the address space.
 *                (Normally called *after* as_complete_load().) Hands
 *                back the initial stack pointer for the new process.
 */

struct addrspace *as_create(void);
int               as_copy(struct addrspace *src, struct addrspace **ret);
void              as_activate(struct addrspace *);
void              as_destroy(struct addrspace *);

int               as_define_region(struct addrspace *as,
                                   vaddr_t vaddr, size_t sz,
                                   int readable,
                                   int writeable,
                                   int executable);
int               as_prepare_load(struct addrspace *as);
int               as_complete_load(struct addrspace *as);
int               as_define_stack(struct addrspace *as, vaddr_t *initstackptr);

/************ RB:Auxillary as functions ************/
void as_check_regions(struct addrspace *as);

/*
 * Functions in loadelf.c
 *    load_elf - load an ELF user program executable into the current
 *               address space. Returns the entry point (initial PC)
 *               in the space pointed to by ENTRYPOINT.
 */

int load_elf(struct vnode *v, vaddr_t *entrypoint);


/************ RB:Page table and region linked list functions ************/
struct page_table_entry *add_pte(struct addrspace* as, vaddr_t vaddr, paddr_t paddr);
struct page_table_entry *get_pte(struct page_table_entry* page_table, vaddr_t vaddr);

struct region_entry *add_region(struct addrspace* as, vaddr_t rbase,size_t sz,int r,int w,int x);
struct region_entry *get_region(struct region_entry* regions, vaddr_t vaddr);
<<<<<<< HEAD
void print_page_table(struct page_table_entry *entry);
=======
void printPageTable(struct page_table_entry *entry);
>>>>>>> 303fbe623dd51568515426c72523015c03df50f1

#endif /* _ADDRSPACE_H_ */
