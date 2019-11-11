#ifndef DIRECTION_MEMORY_H
#define DIRECTION_MEMORY_H

# include <systemc.h>
# include <fstream>
# include <string>
# include <iostream>

using namespace std;

# define data_lenght 11
# define memory_lenght 8

class Direction_Memory : public sc_module
{
	public:

		sc_in<sc_uint<3> > dir_in;
		sc_in<sc_uint<2> > op_in;
		sc_in<sc_uint<data_lenght> > data_in;
		sc_out<sc_uint<data_lenght> > data_out;

		SC_CTOR(Direction_Memory)
		{
			SC_METHOD(select);
				sensitive << dir_in;
		}

		~Direction_Memory(){}

	private:
		sc_uint<data_lenght> memory[memory_lenght];
		ifstream memory_file_in;
		ofstream memory_file_out;

		void load()
		{
			memory_file_in.open("dir_memory.txt");

			string tmp;
			sc_uint<data_lenght> data;

			for(int i = 0; i < memory_lenght; i++)
			{
				getline(memory_file_in, tmp);

				for(int j = 0; j < data_lenght; j++)
				{
					if(tmp[j] == '1')
						data[data_lenght-1-j] = 1;
					else
						data[data_lenght-1-j] = 0;
				}
				memory[i] = data;
			}

			data_out.write(memory[dir_in.read()]);

			memory_file_in.close();
		}

		void store()
		{
			memory[dir_in.read()] = data_in.read();

			memory_file_out.open("dir_memory.txt");

			for(int i = 0; i < memory_lenght; i++)
			{
				memory_file_out << memory[i].to_string(SC_BIN).substr(3) << endl;
			}

			memory_file_out.close();
		}

		void select()
		{
			if(op_in.read() == 0)
				load();
			else if (op_in.read() == 1)
				store();
		}
};

#endif
