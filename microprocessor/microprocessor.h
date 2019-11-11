# ifndef MICROPROCESSOR_H
# define MICROPROCESSOR_H

# include <systemc.h>

# include "../instruction_memory/instruction_memory.h"
# include "../alu/alu.h"
# include "../direction_memory/direction_memory.h"
# include "../multiplexor1/multiplexor1.h"
# include "../multiplexor2/multiplexor2.h"
# include "../register2/regs2.h"
# include "../register3/regs3.h"
# include "../register7/regs7.h"
# include "../register8/regs8.h"
# include "../register11/regs11.h"
# include "../register_direction/register_direction.h"
# include "../register_file/register_file.h"

class Microprocessor : public sc_module
{
  private:

    Instruction_Memory *ins_mem;

    Regs8 *reg8_1;

    Register_file *reg_file;
    Register_direction *reg_dir;
    Multiplexor1 *mul1;

    Regs11 *reg11_1, *reg11_2, *reg11_3, *reg11_4;
    Regs3 *reg3_1, *reg3_2;
    Regs2 *reg2_1;

    Alu *alu;

    Regs11 *reg11_5, *reg11_6;
    Regs3 *reg3_3, *reg3_4;
    Regs2 *reg2_2;

    Direction_Memory *dir_mem;
    Multiplexor2 *mul2;

    Regs11 *reg11_7;
    Regs3 *reg3_5;
    Regs2 *reg2_3;
    //declaracion de registro de prueba
    Regs11 *reg11_8;

    sc_signal<sc_uint<8> > instruction_sg, reg8_1_sg;
    sc_signal<sc_uint<3> > rn_1_sg, rn_2_sg, rn_3_sg, rn_4_sg;
    sc_signal<sc_uint<3> > dirmem_1_sg, dirmem_2_sg, dirmem_3_sg;
    sc_signal<sc_uint<2> > op_1_sg, op_2_sg, op_3_sg, op_4_sg;
    sc_signal<sc_uint<3> > mul1_sg, reg_dir_sg;
    sc_signal<sc_uint<11> > data_1_sg, data_2_sg, data_3_sg, data_4_sg, data_14_sg;
    sc_signal<sc_uint<11> > data_5_sg, data_6_sg, data_7_sg, data_8_sg, data_9_sg;
    sc_signal<sc_uint<11> > data_10_sg, data_11_sg, data_12_sg, data_13_sg;

    void split()
    {
      //Prove Nedded
      op_1_sg = reg8_1_sg.read().range(7,6);
      dirmem_1_sg = reg8_1_sg.read().range(5,3);
      rn_1_sg = reg8_1_sg.read().range(2,0);
    }

  public:

    sc_in_clk clk_in;
    sc_in<bool> enable_in;
    sc_in<sc_uint<4> > pc_in;
    //prueba de salidas
    sc_out<sc_uint<11> > result_out;

    SC_CTOR(Microprocessor)
    {
      SC_METHOD(split)
        sensitive << reg8_1_sg;

      ins_mem = new Instruction_Memory("ins_mem");
      reg8_1 = new Regs8("reg8_1");
      reg_file = new Register_file("reg_file");
      reg_dir = new Register_direction("reg_dir");
      mul1 = new Multiplexor1("mul1");
      reg11_1 = new Regs11("reg11_1");
      reg11_2 = new Regs11("reg11_2");
      reg11_3 = new Regs11("reg11_3");
      reg11_4 = new Regs11("reg11_4");
      reg3_1 = new Regs3("reg3_1");
      reg3_2 = new Regs3("reg3_2");
      reg2_1 = new Regs2("reg2_1");
      alu = new Alu("alu");
      reg11_5 = new Regs11("reg11_5");
      reg11_6 = new Regs11("reg11_6");
      reg3_3 = new Regs3("reg3_3");
      reg3_4 = new Regs3("reg3_4");
      reg2_2 = new Regs2("reg2_2");
      dir_mem = new Direction_Memory("dir_mem");
      mul2 = new Multiplexor2("mul2");
      reg11_7 = new Regs11("reg11_7");
      reg3_5 = new Regs3("reg3_5");
      reg2_3 = new Regs2("reg2_3");
      //registro 11 de prueba
      reg11_8 = new Regs11("reg11_8");

      // FETCH
      //----------------------------------------------
      ins_mem->dir_in(pc_in);
      ins_mem->instr_out(instruction_sg);
      //----------------------------------------------
      reg8_1->clk_in(clk_in);
      reg8_1->enable_in(enable_in);
      reg8_1->data_in(instruction_sg);
      reg8_1->data_out(reg8_1_sg);
      //----------------------------------------------

      // DECODE
      //----------------------------------------------
      reg_file->write_eneable_in(op_4_sg);
      reg_file->clk_in(clk_in);
      reg_file->dirdata_in(rn_4_sg);
      reg_file->data_in(data_14_sg);
      reg_file->dir_in(mul1_sg);
      reg_file->readn_out(data_1_sg);
      reg_file->reads_out(data_2_sg);
      reg_file->reade_out(data_3_sg);
      reg_file->reado_out(data_4_sg);

      reg_dir->clk_in(clk_in);
      reg_dir->write_eneable_in(op_4_sg);
      reg_dir->data_in(data_14_sg);
      reg_dir->data_out(reg_dir_sg);

      mul1->rn_in(rn_1_sg);
      mul1->rd_in(reg_dir_sg);
      mul1->ctrl_in(op_1_sg);
      mul1->slct_out(mul1_sg);
      //----------------------------------------------
      reg11_1->clk_in(clk_in);
      reg11_1->enable_in(enable_in);
      reg11_1->data_in(data_1_sg);
      reg11_1->data_out(data_5_sg);

      reg11_2->clk_in(clk_in);
      reg11_2->enable_in(enable_in);
      reg11_2->data_in(data_2_sg);
      reg11_2->data_out(data_6_sg);

      reg11_3->clk_in(clk_in);
      reg11_3->enable_in(enable_in);
      reg11_3->data_in(data_3_sg);
      reg11_3->data_out(data_7_sg);

      reg11_4->clk_in(clk_in);
      reg11_4->enable_in(enable_in);
      reg11_4->data_in(data_4_sg);
      reg11_4->data_out(data_8_sg);

      reg3_1->clk_in(clk_in);
      reg3_1->enable_in(enable_in);
      reg3_1->data_in(rn_1_sg);
      reg3_1->data_out(rn_2_sg);

      reg3_2->clk_in(clk_in);
      reg3_2->enable_in(enable_in);
      reg3_2->data_in(dirmem_1_sg);
      reg3_2->data_out(dirmem_2_sg);

      reg2_1->clk_in(clk_in);
      reg2_1->enable_in(enable_in);
      reg2_1->data_in(op_1_sg);
      reg2_1->data_out(op_2_sg);
      //----------------------------------------------

      // EXECUTE
      //----------------------------------------------
      alu->a_in(data_5_sg);
      alu->b_in(data_6_sg);
      alu->c_in(data_7_sg);
      alu->d_in(data_8_sg);
      alu->control_in(op_2_sg);
      alu->e_out(data_9_sg);
      //----------------------------------------------
      reg11_5->clk_in(clk_in);
      reg11_5->enable_in(enable_in);
      reg11_5->data_in(data_9_sg);
      reg11_5->data_out(data_10_sg);

      reg11_6->clk_in(clk_in);
      reg11_6->enable_in(enable_in);
      reg11_6->data_in(data_5_sg);
      reg11_6->data_out(data_11_sg);

      reg3_3->clk_in(clk_in);
      reg3_3->enable_in(enable_in);
      reg3_3->data_in(rn_2_sg);
      reg3_3->data_out(rn_3_sg);

      reg3_4->clk_in(clk_in);
      reg3_4->enable_in(enable_in);
      reg3_4->data_in(dirmem_2_sg);
      reg3_4->data_out(dirmem_3_sg);

      reg2_2->clk_in(clk_in);
      reg2_2->enable_in(enable_in);
      reg2_2->data_in(op_2_sg);
      reg2_2->data_out(op_3_sg);
      //----------------------------------------------

      // MEMORY
      //----------------------------------------------
      dir_mem->dir_in(dirmem_3_sg);
      dir_mem->op_in(op_3_sg);
      dir_mem->data_in(data_11_sg);
      dir_mem->data_out(data_12_sg);

      mul2->datamem_in(data_12_sg);
      mul2->dataalu_in(data_10_sg);
      mul2->ctrl_in(op_3_sg);
      mul2->slct_out(data_13_sg);
      //----------------------------------------------

      // WRITE BACK
      //----------------------------------------------
      reg11_7->clk_in(clk_in);
      reg11_7->enable_in(enable_in);
      reg11_7->data_in(data_13_sg);
      reg11_7->data_out(data_14_sg);

      reg3_5->clk_in(clk_in);
      reg3_5->enable_in(enable_in);
      reg3_5->data_in(rn_3_sg);
      reg3_5->data_out(rn_4_sg);

      reg2_3->clk_in(clk_in);
      reg2_3->enable_in(enable_in);
      reg2_3->data_in(op_3_sg);
      reg2_3->data_out(op_4_sg);

      //registro 8 de prueba de resultado
      reg11_8->clk_in(clk_in);
      reg11_8->enable_in(enable_in);
      reg11_8->data_in(data_13_sg);
      reg11_8->data_out(result_out);
      //----------------------------------------------

    }

};

# endif
