# include <testbench.h>

Testbench::Testbench(sc_module_name nm)
  : sc_module(nm)
{
  SC_THREAD(test);
  sensitive << clk_in.neg();
}

Testbench::~Testbench()
{

}

void Testbench::test()
{
    cout << "A\t B\t C\t D\t E\t" << endl;
  a_out.write(1);
  b_out.write(2);
  c_out.write(3);
  d_out.write(4);
  control_out.write(3);

  wait();
  print();

  a_out.write(4);
  b_out.write(3);
  c_out.write(2);
  d_out.write(1);
  control_out.write(3);

  wait();
  print();

  a_out.write(15);
  b_out.write(18);
  c_out.write(42);
  d_out.write(243);
  control_out.write(3);

  wait();
  print();

  a_out.write(189);
  b_out.write(69);
  c_out.write(82);
  d_out.write(2000);
  control_out.write(3);

  wait();
  print();

  a_out.write(1);
  b_out.write(2);
  c_out.write(3);
  d_out.write(4);
  control_out.write(2);

  wait();
  print();

  a_out.write(4);
  b_out.write(3);
  c_out.write(2);
  d_out.write(1);
  control_out.write(2);

  wait();
  print();

  a_out.write(15);
  b_out.write(18);
  c_out.write(42);
  d_out.write(243);
  control_out.write(2);

  wait();
  print();

  a_out.write(189);
  b_out.write(69);
  c_out.write(82);
  d_out.write(199);
  control_out.write(2);

  wait();
  print();

  sc_stop();
}

void Testbench::print()
{
  cout << a_out.read() << '\t'
       << b_out.read() << '\t'
       << c_out.read() << '\t'
       << d_out.read() << '\t'
       << e_in.read() << endl;
  /*
  cout << "A B C D E" << endl;
  cout << a_out.read().to_string(SC_BIN) << '\t'
       << b_out.read().to_string(SC_BIN) << '\t'
       << c_out.read().to_string(SC_BIN) << '\t'
       << d_out.read().to_string(SC_BIN) << '\t'
       << e_in.read().to_string(SC_BIN) << endl;*/
}
