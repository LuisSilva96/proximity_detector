# include "testbench.h"

void Testbench::test()
{
  std::cout << "\t\t________________NEW HORIZONS____________" << std::endl;
  std::cout << "\t\tTIME | PC_IN | RESULT_IN " << std::endl;

  for (int i = 0; i < 10; i++)
	{
    enable_out.write(1);
    pc_out.write(i);

    wait();
	  print();
  }
  sc_stop();
}


void Testbench::print()
{
  std::cout << "\t\t" << sc_time_stamp() << " | " << pc_out.read()
    << " | " << result_in.read() << std::endl;
  std::cout << "\t\t________________________________________" << std::endl;
}
