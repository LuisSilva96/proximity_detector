# include <register_direction.h>
# include <testbench.h>

int sc_main(int argc,char *argv[])
{
	sc_time DELAY(10,SC_NS);
	sc_time PERIOD(10,SC_NS);
	sc_clock clock("clock",PERIOD,0.5,DELAY,true);

  Register_direction register1("register");
  Testbench test("test");

  sc_signal<sc_uint<2> > write_eneable_sg;
  sc_signal<sc_uint<11> > data_sg;
  sc_signal<sc_uint<3> > output_sg;

  register1.write_eneable_in(write_eneable_sg);
  register1.data_in(data_sg);
  register1.data_out(output_sg);
  register1.clk_in(clock);

  test.write_eneable_out(write_eneable_sg);
  test.data_out(data_sg);
  test.data_in(output_sg);
  test.clk_in(clock);

  sc_start();

return 0;
}
