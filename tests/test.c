#include <sharna.h>

void
test1 ()
{
  char data[] = "Hello, World!";
  char code[] = { MOV, R_A, 1, MOV, R_B, 2, HLT };
  vm_t vm = sh_vm_new ();

  /* burn program to ROM */
  for (char i = 0; code[i] != HLT; i++)
    sh_rom_push (&vm.rom, code[i]);
  sh_rom_push (&vm.rom, HLT);

  /* load text section */
  sh_ram_load (&vm.ram, vm.rom.v, 0, vm.rom.l);

  /* load data section */
  sh_ram_load (&vm.ram, data, 0, strlen (data));

  /* set offsets */
  sh_ram_reset_offsets_m (&vm.ram, 0, vm.rom.l, vm.ram.l, RAM_SIZE - 1);

  /* run the machine */
  sh_vm_run (&vm);

  //   int i = 0;
  //   for (i = 0; i < vm.ram.l; i++)
  //     {
  //       printf ("%d\n", vm.ram.v[i]);
  //     }

  for (int i = 0; i < R_8bit; i++)
    {
      printf ("%s: %d\n", REGNAMES[i], vm.cpu.reg_8[i]);
    }

  printf ("PC: %d\n", vm.cpu.reg_16[0]);
  printf ("SP: %d\n", vm.cpu.reg_16[1]);
}

void
test2 ()
{
  sh_asm_ctx_t ctx = sh_asm_ctx_new_fromFilename ("tests/test1.sp");

  for (size_t i = 0; i < ASM_CTX_SECTION_TEXT_SIZE; i++)
    {
      ctx.text[i] = 0;
      ctx.data[i] = 0;
    }

  sh_asm_tok_parse (&ctx);
  sh_asm_ast_parse_toks (&ctx);

  for (size_t i = 0; i < ctx.trs; i++)
    {
      printf ("%d\n", ctx.tree[i].type);
    }

  sh_asm_codegen (&ctx);

  printf ("----\n");
  for (size_t i = 0; ctx.text[i] != HLT; i++)
    {
      printf ("%d\n", ctx.text[i]);
    }
}

void
test3 ()
{
  sh_qp_t qp = sh_qp_new_fromFile ("tests/test.sp");

  // printf ("%s\n", qp.fcont);
  // for (size_t i = 0; i < qp.fls; i++)
  //   {
  //     printf ("(%d) %s\n", i, qp.flines[i]);
  //   }

  sh_qp_parse (&qp);

  // printf ("codegen size: %d\n", qp.cgc);
  // for (size_t i = 0; i < qp.cgc; i++)
  //   {
  //     printf ("%d  ", qp.cg[i]);
  //   }

  // printf ("\nSections:\n");
  // for (size_t i = 0; i < qp.ps_c; i++)
  //   {
  //     printf ("%s: %d\n",
  //             qp.prog_sections[i].name ? qp.prog_sections[i].name : "EOP",
  //             (int)qp.prog_sections[i].bc);
  //   }

  vm_t vm = sh_vm_new ();

  sh_ram_load (&vm.ram, qp.cg, 0, qp.cgc);

  size_t sec_data_bc = 0;
  size_t sec_text_bc = 0;
  size_t sec_eop_bc = 0;

  for (size_t i = 0; i < qp.ps_c; i++)
    {
      if (qp.prog_sections[i].name
          && !strcmp (qp.prog_sections[i].name, "data"))
        sec_data_bc = qp.prog_sections[i].bc;
      else if (qp.prog_sections[i].name
               && !strcmp (qp.prog_sections[i].name, "text"))
        sec_text_bc = qp.prog_sections[i].bc;
      else if (qp.prog_sections[i].name == NULL)
        sec_eop_bc = qp.prog_sections[i].bc;
    }

  sh_ram_reset_offsets_m (&vm.ram, sec_text_bc, sec_data_bc, sec_eop_bc,
                          RAM_SIZE - 1);

  vm.cpu.reg_16[R_SP] = vm.ram.offsets.stack;

  for (size_t i = 0; i < vm.ram.l; i++)
    {
      printf ("%d\t", vm.ram.v[i]);
    }
  printf ("\n");

  printf ("\n---------\n");
  sh_vm_run (&vm);
  printf ("\n---------\n");

  // for (size_t i = 0; i < qp.fls; i++)
  //   {
  //     printf ("%s\n", qp.flines[i]);
  //   }

  printf ("\nRegisters:\n");

  for (int i = 0; i < R_8bit; i++)
    {
      printf ("%s: %d\n", REGNAMES[i], vm.cpu.reg_8[i]);
    }

  printf ("PC: %d\n", vm.cpu.reg_16[0]);
  printf ("SP: %d\n", vm.cpu.reg_16[1]);

  sh_qp_close (&qp);
}

void
test4 ()
{
  sh_qp_vtable_t vt;
  sh_qp_addtovtable (&vt, "hello", 1);
  sh_qp_addtovtable (&vt, "Hello", 2);
  sh_qp_addtovtable (&vt, "hey", 3);
  sh_qp_addtovtable (&vt, "heY", 4);

  printf ("%d\n", sh_qp_getfromvtable (&vt, "hello"));
  printf ("%d\n", sh_qp_getfromvtable (&vt, "Hello"));
  printf ("%d\n", sh_qp_getfromvtable (&vt, "hey"));
  printf ("%d\n", sh_qp_getfromvtable (&vt, "heY"));
}

void
test5 ()
{
  uint8_t data[] = "Hello, World!\n";
  uint8_t text[] = { MOV, R_A, 1,   MOV, R_B,       1, MOV, R_C,
                     15,  MOV, R_D, 14,  INTERRUPT, 1, HLT };
  vm_t vm = sh_vm_new ();

  for (size_t i = 0; text[i] != HLT; i++)
    sh_rom_push (&vm.rom, text[i]);
  sh_rom_push (&vm.rom, HLT);

  /* load text section */
  sh_ram_load (&vm.ram, vm.rom.v, 0, vm.rom.l);

  /* load data section */
  sh_ram_load (&vm.ram, data, 0, strlen (data));

  /* set offsets */
  sh_ram_reset_offsets_m (&vm.ram, 0, vm.rom.l, vm.ram.l, RAM_SIZE - 1);

  /* run the vm */
  sh_vm_run (&vm);
}

int
main (int argc, char const *argv[])
{
  test3 ();
  return 0;
}