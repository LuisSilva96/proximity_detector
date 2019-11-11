# ifndef ALU_H
# define ALU_H

# include <systemc.h>
# include <iostream>

const sc_uint<8> NEAR = 50;
const sc_uint<8> MIDDLE = 100;
const sc_uint<8> FAR = 150;
const sc_uint<8> FARAWAY = 200;

class Alu : public sc_module
{
  public:
    sc_in<sc_uint<11> > a_in, b_in, c_in, d_in;
    sc_in<sc_uint<2> > control_in;
    sc_out<sc_uint<11> > e_out;

    SC_CTOR(Alu)
    {
      SC_METHOD(select);
        sensitive << a_in << b_in << c_in << d_in;
    }

  private:

    void compare()
    {
      sc_uint<8> data[4] = {a_in.read(), b_in.read(), c_in.read(), d_in.read()};

      sc_uint<8> aux = data[0];
      size_t pos = 0;

      for (size_t i = 1; i < 4; i++)
      {
        if (aux > data[i])
	      {
	         aux = data[i];
	         pos = i;
	      }
      }

      sc_uint<11> result;
      //std::cout << "position is: " << pos << std::endl;
      switch (pos)
      {
        case 0:
        {
      	  result = a_in.read();
      	  break;
        }
        case 1:
        {
      	  result = b_in.read();
      	  break;
        }
        case 2:
        {
      	  result = c_in.read();
      	  break;
        }
        case 3:
        {
      	  result = d_in.read();
      	  break;
        }
    }

    e_out.write(result);

    }

    void frequency()
    {

      sc_uint<8> aux = a_in.read();
      //aqui la alu bota como resultado de frequency siempre a lo que venga en a_in

      if (aux <= NEAR)
        e_out.write(4);
      else if (aux > NEAR and aux <= MIDDLE)
        e_out.write(3);
      else if (aux > MIDDLE and aux <= FAR)
        e_out.write(2);
      else if (aux > FAR and aux <= FARAWAY)
        e_out.write(1);
      else
        e_out.write(0);

    }

    void select()
		{
			if(control_in.read() == 2)
				compare();
			else if (control_in.read() == 3)
				frequency();
		}

};

# endif
