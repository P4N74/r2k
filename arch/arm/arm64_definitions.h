#ifndef __ARM64_DEFINITIONS_H
#define __ARM64_DEFINITIONS_H

static pgd_t *get_global_pgd (void)
{
	unsigned long ttb_reg;

	asm volatile (
	"       mrs     %0, TTBR1_EL1"
	: "=r" (ttb_reg));
	ttb_reg &= (0xffffffffffffffff << 0x9);

	return __va (ttb_reg);
}
#endif