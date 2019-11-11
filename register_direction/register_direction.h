# ifndef REGISTERDIRECTION_H
# define REGISTERDIRECTION_H

# include <systemc.h>
# include <iostream>

class Register_direction : public sc_module
{
	public:

		sc_in<bool> clk_in;
		sc_in<sc_uint<2> > write_eneable_in;
		sc_in<sc_uint<11> > data_in;
		sc_out<sc_uint<3> > data_out;

		sc_uint<3> data;

		SC_CTOR(Register_direction)
		{
			data = 7;

			SC_METHOD(reading_data)
				sensitive << clk_in.neg();

			SC_METHOD(writing_data)
				sensitive << clk_in.pos();
		}

	private:

		void reading_data()
		{
			if(write_eneable_in.read() == 2)
			{
				data = (data_in.read().range(10,8));
			}
				//aqui hacer split de la senal a la direction (ultimos tres);
				// aqui se debe verificar si esta funionando como debe xD, hacer testbench
		}

		void writing_data()
		{
			data_out.write(data);
		}
};

# endif
