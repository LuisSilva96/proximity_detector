# include <microprocessor.h>
# include <testbench.h>

int sc_main(int argc,char *argv[])
{
  sc_time DELAY(10,SC_NS);
	sc_time PERIOD(10,SC_NS);
	sc_clock clock("clock",PERIOD,0.5,DELAY,true);

  Microprocessor micro("micro");
  Testbench test("test");

  sc_signal<bool> enable_sg;
  sc_signal<sc_uint<4> > pc_sg;
  sc_signal<sc_uint<11> > result_sg;

  micro.enable_in(enable_sg);
  micro.pc_in(pc_sg);
  micro.clk_in(clock);
  micro.result_out(result_sg);

  test.enable_out(enable_sg);
  test.pc_out(pc_sg);
  test.clk_in(clock);
  test.result_in(result_sg);

  sc_start();

  return 0;
}
