#include "testbench.h"

void testbench::test()
{
	std::cout << "\t" << "CLOCK" << " || " << "dir_in" << " | " << "data_out"
	<< " | " << "data_in" << " | " << "cod_op" << endl;

	for(int i = 0; i < 8; i++)
	{
		op_out.write(1);
		dir_out.write(i);
		data_out.write(i*3);

		wait();
		print();
	}

	for(int i = 0; i < 8; i++)
	{
		op_out.write(0);
		dir_out.write(i);
		data_out.write(i*3);
		wait();
		print();
	}

	sc_stop();
}

void testbench::print()
{
	std::cout << "\t" << sc_time_stamp() << " || " << dir_out.read() << "\t | "
	<< data_in.read().to_string(SC_BIN).substr(3) << " | "
	<< data_out.read().to_string(SC_BIN).substr(3) << " | " << op_out.read() << endl;
}
