#ifndef __SYSCALL_HANDLERS_H_
#define __SYSCALL_HANDLERS_H_

#include <types.h>
#include <vmm/vmm.h>

#define NT_OPEN_PROCESS 0x26
#define NT_CREATE_USER_PROCESS 0xc8

typedef STATUS (*SYSCALL_HANDLER)();

#define REGISTER_SYSCALL_HANDLER(idx, hand) syscallsData[idx].handler = hand

typedef struct _SYSCALL_DATA
{
    // Defined statically
    SYSCALL_HANDLER handler;
    SYSCALL_HANDLER returnHandler;
    BYTE params;
    BYTE hookInstructionOffset;
    BOOL hookReturnEvent;
    // Defined dynamically
    QWORD hookedInstructionLength;
    QWORD hookedInstructionAddress;
    QWORD returnHookAddress;
    BYTE hookedInstrucion[X86_MAX_INSTRUCTION_LEN];
} SYSCALL_DATA, *PSYSCALL_DATA;

typedef struct _SYSCALL_EVENT
{
    QWORD params[17];
} SYSCALL_EVENT, *PSYSCALL_EVENT;

VOID InitSyscallData(IN QWORD syscallId, IN BYTE hookInstructionOffset, IN BYTE hookedInstructionLength,
    IN SYSCALL_HANDLER handler, IN BOOL hookReturn, IN SYSCALL_HANDLER returnHandler);
STATUS HandleNtOpenPrcoess();
STATUS HandleNtCreateUserProcess();

extern QWORD __ntDataStart;

#endif