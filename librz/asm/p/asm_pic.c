// SPDX-FileCopyrightText: 2018 thestr4ng3r <info@florianmaerkl.de>
// SPDX-FileCopyrightText: 2018 courk <courk@courk.cc>
// SPDX-License-Identifier: LGPL-3.0-only

#include <rz_asm.h>
#include <rz_lib.h>

#include "../arch/pic/pic_baseline.h"
#include "../arch/pic/pic_pic18.h"
#include "../arch/pic/pic_midrange.h"

static int asm_pic_disassemble(RzAsm *a, RzAsmOp *op, const ut8 *b, int l) {
	int res = -1;
	if (a->cpu && strcasecmp(a->cpu, "baseline") == 0) {
		res = pic_baseline_disassemble(op, b, l);
	} else if (a->cpu && strcasecmp(a->cpu, "midrange") == 0) {
		res = pic_midrange_disassemble(op, b, l);
	} else if (a->cpu && strcasecmp(a->cpu, "pic18") == 0) {
		res = pic_pic18_disassemble(op, b, l);
	}
	return op->size = res;
}

RzAsmPlugin rz_asm_plugin_pic = {
	.name = "pic",
	.arch = "pic",
	.cpus = "baseline,midrange,pic18",
	.bits = 8,
	.license = "LGPL3",
	.desc = "PIC disassembler",
	.disassemble = &asm_pic_disassemble
};

#ifndef RZ_PLUGIN_INCORE
RZ_API RzLibStruct rizin_plugin = {
	.type = RZ_LIB_TYPE_ASM,
	.data = &rz_asm_plugin_pic
};
#endif
