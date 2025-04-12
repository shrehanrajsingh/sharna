#include <sharna.h>

int
main (int argc, char const *argv[])
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

  return 0;
}