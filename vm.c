#include "vm.h"

SH_API vm_t
sh_vm_new (void)
{
  vm_t v;
  v.ram = sh_ram_new ();
  v.cpu = sh_cpu_new ();
  v.rom = sh_rom_new ();

  return v;
}

SH_API void
sh_vm_run (vm_t *v)
{
  v->cpu.reg_16[R_PC] = v->ram.offsets.p_text;
  uint16_t *pc = &v->cpu.reg_16[R_PC];

  uint8_t *ra = &v->cpu.reg_8[R_A], *rb = &v->cpu.reg_8[R_B],
          *rc = &v->cpu.reg_8[R_C], *rd = &v->cpu.reg_8[R_D],
          *re = &v->cpu.reg_8[R_E], *rf = &v->cpu.reg_8[R_F];

  char c;

  while ((c = v->ram.v[*pc]) != HLT)
    {
      switch (c)
        {
        case MOV_rv:
          {
            char r = v->ram.v[++(*pc)];
            char vl = v->ram.v[++(*pc)];

            sh_mov_rv (v, r, vl);
          }
          break;

        case MOV_rr:
          {
            char r1 = v->ram.v[++(*pc)];
            char r2 = v->ram.v[++(*pc)];

            sh_mov_rr (v, r1, r2);
          }
          break;

        case ADD_rv:
          {
            char r = v->ram.v[++(*pc)];
            char vl = v->ram.v[++(*pc)];

            sh_add_rv (v, r, vl);
          }
          break;
        case ADD_rr:
          {
            char r1 = v->ram.v[++(*pc)];
            char r2 = v->ram.v[++(*pc)];

            sh_add_rr (v, r1, r2);
          }
          break;

        case INTERRUPT:
          {
            uint8_t r1 = v->ram.v[++(*pc)];
            // printf ("found interrupt: [A = %d] [B = %d] [C = %d] [D =
            // %d]\n",
            //         *ra, *rb, *rc, *rd);

            switch (r1)
              {
              case SC_IO:
                {
                  /* all IO routines use a filestream */
                  FILE *fptr = NULL;

                  switch (*rb)
                    {
                    case IOFS_STDOUT:
                      fptr = (FILE *)stdout;
                      break;

                    case IOFS_STDIN:
                      fptr = (FILE *)stdin;
                      break;

                    case IOFS_CUST:
                      {
                        __development__
                      }
                      break;

                    default:
                      break;
                    }

                  assert (fptr != NULL);

                  uint8_t *msgbuf = &v->ram.v[*rc];

                  switch (*ra)
                    {
                    case SC_IO_WRITE:
                      {
                        sh_int_sys_io_write (fptr, msgbuf, *rd);
                      }
                      break;

                    case SC_IO_READ:
                      {
                        sh_int_sys_io_read (fptr, msgbuf, *rd);
                      }
                      break;

                    default:
                      break;
                    }
                }
                break;

              default:
                break;
              }
          }
          break;

        case JE_v:
          {
            char b1 = v->ram.v[++(*pc)];
            char b2 = v->ram.v[++(*pc)];

            sh_je_v (v, b1, b2);
          }
          break;

        case JNE_v:
          {
            char b1 = v->ram.v[++(*pc)];
            char b2 = v->ram.v[++(*pc)];

            sh_jne_v (v, b1, b2);
            // printf ("%d\n", *pc);
          }
          break;

        case CMP_rr:
          {
            char r1 = v->ram.v[++(*pc)];
            char r2 = v->ram.v[++(*pc)];

            sh_cmp_rr (v, r1, r2);
          }
          break;

        case CMP_rv:
          {
            char r1 = v->ram.v[++(*pc)];
            char v1 = v->ram.v[++(*pc)];

            sh_cmp_rv (v, r1, v1);
          }
          break;

        case CMP_byte_r_v:
          {
            char r1 = v->ram.v[++(*pc)];
            char v1 = v->ram.v[++(*pc)];

            sh_cmp_byte_r_v (v, r1, v1);
          }
          break;

        case CMP_byte_r_r:
          {
            char r1 = v->ram.v[++(*pc)];
            char r2 = v->ram.v[++(*pc)];

            sh_cmp_byte_r_r (v, r1, r2);
          }
          break;

        case JMP_v:
          {
            char b1 = v->ram.v[++(*pc)];
            char b2 = v->ram.v[++(*pc)];

            sh_jmp_v (v, b1, b2);
          }
          break;

        case PUSH_r:
          {
            char r = v->ram.v[++(*pc)];
            sh_push_r (v, r);
          }
          break;

        case PUSH_v:
          {
            char b = v->ram.v[++(*pc)];
            sh_push_v (v, b);
          }
          break;

        case POP_r:
          {
            char b = v->ram.v[++(*pc)];
            sh_pop_r (v, b);
          }
          break;

        case CALL_v:
          {
            char b1 = v->ram.v[++(*pc)];
            char b2 = v->ram.v[++(*pc)];

            sh_call_v (v, b1, b2);
          }
          break;

        case RET:
          {
            sh_ret (v);
          }
          break;

        case SUB_rr:
          {
            char r1 = v->ram.v[++(*pc)];
            char r2 = v->ram.v[++(*pc)];

            sh_sub_rr (v, r1, r2);
          }
          break;

        case SUB_rv:
          {
            char r = v->ram.v[++(*pc)];
            char vl = v->ram.v[++(*pc)];

            sh_sub_rv (v, r, vl);
          }
          break;

        case INC_r:
          {
            char r = v->ram.v[++(*pc)];
            sh_inc_r (v, r);
          }
          break;

        case DEC_r:
          {
            char r = v->ram.v[++(*pc)];
            sh_dec_r (v, r);
          }
          break;

        default:
          {
            eprintf ("sh_vm_run: invalid instruction %d\nExiting VM...\n", c);
            return;
          }
          break;
        }

    le:
      (*pc)++;
    }
}