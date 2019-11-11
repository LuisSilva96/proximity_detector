# include <register_file.h>
# include <testbench.h>

int sc_main(int argc,char *argv[])
{
	sc_time DELAY(10,SC_NS);
	sc_time PERIOD(10,SC_NS);
	sc_clock clock("clock",PERIOD,0.5,DELAY,true);

	Register_file registerfile("registerfile");
	Testbench test("test");

	sc_signal<sc_uint<2> > write_eneable_sg;
	sc_signal<sc_uint<3> > dirdata_sg, dir_sg;
	sc_signal<sc_uint<11> > data_sg, readn_sg, reads_sg, reade_sg, reado_sg;

	registerfile.write_eneable_in(write_eneable_sg);
	registerfile.dirdata_in(dirdata_sg);
	registerfile.data_in(data_sg);
	registerfile.dir_in(dir_sg);
	registerfile.readn_out(readn_sg);
	registerfile.reads_out(reads_sg);
	registerfile.reade_out(reade_sg);
	registerfile.reado_out(reado_sg);
	registerfile.clk_in(clock);

	test.write_eneable_out(write_eneable_sg);
	test.dirdata_out(dirdata_sg);
	test.data_out(data_sg);
	test.dir_out(dir_sg);
	test.readn_in(readn_sg);
	test.reads_in(reads_sg);
	test.reade_in(reade_sg);
	test.reado_in(reado_sg);
	test.clk_in(clock);

	sc_start();

return 0;
}
