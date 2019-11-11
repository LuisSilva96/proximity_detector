# include "testbench.h"

void Testbench::test()
{
  std::cout << "TIME | WRITE_ENEABLE | DATA_IN | DATA_OUT "
    << std::endl;

  write_eneable_out.write(2);
  data_out.write(1700);

  wait();
  print();

  write_eneable_out.write(2);
  data_out.write(37);

  wait();
  print();

  write_eneable_out.write(2);
  data_out.write(2045);

  wait();
  print();

  write_eneable_out.write(2);
  data_out.write(98);

  wait();
  print();

  sc_stop();
}

void Testbench::print()
{/*
  std::cout << sc_time_stamp() << " || " << write_eneable_out.read() << "\t || " <<
    data_out.read() << "     \t || " << data_in.read() << "\n";*/

    std::cout << sc_time_stamp() << " || " << write_eneable_out.read() << "\t || " <<
      data_out.read().to_string(SC_BIN) << "     \t || " << data_in.read().to_string(SC_BIN) << "\n";

  std::cout << "____________________________________________________" << std::endl;
}
