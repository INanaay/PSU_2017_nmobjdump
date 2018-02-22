//
// Created by NANAA on 21/02/18.
//

#include "stdio.h"
#include <elf.h>
#include <string.h>
#include "../include/objdump.h"
#include "../include/nm.h"

static const char* get_machine_type642(Elf64_Half type)
{
    if (type == EM_S390)
        return "IBM S/390";
    if (type == EM_ARM)
        return "ARM";
    if (type == EM_SH)
        return "Renesas / SuperH SH";
    if (type == EM_SPARCV9)
        return "SPARC v00";
    if (type == EM_IA_64)
        return "Intel IA-64";
    if (type == EM_X86_64)
        return "i386:x86-64";
    return "NONE";
}

const char* get_machine_type64(Elf64_Half type)
{
    if (type == EM_X86_64)
        return "i386:x86-64";
    if (type == EM_NONE)
        return "None";
    if (type == EM_M32)
        return "WE32100";
    if (type == EM_SPARC)
        return "Sparc";
    if (type == EM_386)
        return "Intel 80860";
    if (type == EM_MIPS)
        return ("MIPS R3000");
    if (type == EM_PARISC)
        return ("HPPA");
    if (type == EM_SPARC32PLUS)
        return ("Sparc v8+");
    if (type == EM_PPC)
        return "PowerPC";
    if (type == EM_PPC64)
        return "PowerPC64";
    return get_machine_type642(type);
}

static const char* get_machine_type322(Elf32_Half type)
{
	if (type == EM_S390)
		return "IBM S/390";
	if (type == EM_ARM)
		return "ARM";
	if (type == EM_SH)
		return "Renesas / SuperH SH";
	if (type == EM_SPARCV9)
		return "SPARC v00";
	if (type == EM_IA_64)
		return "Intel IA-64";
	if (type == EM_X86_64)
		return "i386:x86-64";
	return "NONE";
}

const char* get_machine_type32(Elf32_Half type)
{
	if (type == EM_X86_64)
		return "i386:x86-64";
	if (type == EM_NONE)
		return "None";
	if (type == EM_M32)
		return "WE32100";
	if (type == EM_SPARC)
		return "Sparc";
	if (type == EM_386)
		return "i386";
	if (type == EM_MIPS)
		return ("MIPS R3000");
	if (type == EM_PARISC)
		return ("HPPA");
	if (type == EM_SPARC32PLUS)
		return ("Sparc v8+");
	if (type == EM_PPC)
		return "PowerPC";
	if (type == EM_PPC64)
		return "PowerPC64";
	return get_machine_type322(type);
}