# include <iostream>
# include <testbench.h>
# include <alu.h>

int sc_main(int argv, char* argc[])
{
  sc_time PERIOD(10,SC_NS);//SC_PS SC_SEC . . .
  sc_time DELAY(10,SC_NS);
  sc_clock clock("clock",PERIOD,0.5,DELAY,true);

  Alu alu("alu");
  Testbench tb("tb");

  sc_signal<sc_uint<11> > a_sg, b_sg, c_sg, d_sg, e_sg;
  sc_signal<sc_uint<2> > control_sg;

  alu.a_in(a_sg);
  alu.b_in(b_sg);
  alu.c_in(c_sg);
  alu.d_in(d_sg);
  alu.control_in(control_sg);
  alu.e_out(e_sg);

  tb.clk_in(clock);
  tb.e_in(e_sg);
  tb.a_out(a_sg);
  tb.b_out(b_sg);
  tb.c_out(c_sg);
  tb.d_out(d_sg);
  tb.control_out(control_sg);

  sc_start();

  return 0;
}
