#include <sharna.h>

void
test1 ()
{
  char text[] = "Hello, World!";
  char code[] = { MOV, R_A, 1, MOV, R_B, 2, HLT };
  vm_t vm = sh_vm_new ();

  /* burn program to ROM */
  for (char i = 0; code[i] != HLT; i++)
    sh_rom_push (&vm.rom, code[i]);
  sh_rom_push (&vm.rom, HLT);

  /* load text section */
  sh_ram_load (&vm.ram, vm.rom.v, 0, vm.rom.l);

  /* load data stction */
  sh_ram_load (&vm.ram, text, 0, strlen (text));

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

  //   printf ("%s\n", qp.fcont);
  for (size_t i = 0; i < qp.fls; i++)
    {
      printf ("(%d) %s\n", i, qp.flines[i]);
    }

  sh_qp_close (&qp);
}

int
main (int argc, char const *argv[])
{
  test3 ();
  return 0;
}