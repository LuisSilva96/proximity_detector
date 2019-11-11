# include "testbench.h"

void Testbench::test()
{
  std::cout << "TIME | WRITE_ENEABLE | DIRDATA | DATA | DIR_IN | READN | READS | READ E | READO"
    << std::endl;

  write_eneable_out.write(0);
  dirdata_out.write(4);
  data_out.write(69);
  dir_out.write(3);

  wait();
  print();

  write_eneable_out.write(2);
  dirdata_out.write(3);
  data_out.write(100);
  dir_out.write(3);

  wait();
  print();

  write_eneable_out.write(3);
  dirdata_out.write(0);
  data_out.write(75);
  dir_out.write(1);

  wait();
  print();

  write_eneable_out.write(1);
  dirdata_out.write(0);
  data_out.write(33);
  dir_out.write(1);

  wait();
  print();

  sc_stop();

}

void Testbench::print()
{
  std::cout << sc_time_stamp() << " || " << write_eneable_out.read() << "\t || " <<
    dirdata_out.read() << "     \t || " << data_out.read() << "\t || " << dir_out.read() <<
    "||||||| " << readn_in.read() << " | " << reads_in.read() << "  |  " << reade_in.read() <<
    "  |  " << reado_in.read() << "\n";
  std::cout << "____________________________________________________" << std::endl;
}
