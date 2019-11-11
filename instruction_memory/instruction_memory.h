#ifndef INSTRUCTION_MEMORY_H
#define INSTRUCTION_MEMORY_H

# include <systemc.h>
# include <iostream>
# include <fstream>

using namespace std;

#define instruction_length 8

class Instruction_Memory : public sc_module
{
	public:

		sc_in<sc_uint<4> > dir_in;
		sc_out<sc_uint<instruction_length> > instr_out;

		SC_CTOR(Instruction_Memory)
		{
			SC_METHOD(search);
				sensitive << dir_in;

			memory_file.open("memory_file.txt");
		}

		~Instruction_Memory()
		{
			memory_file.close();
		}

	private:

		ifstream memory_file;

		void search()
		{
			unsigned int dir;
			sc_uint<instruction_length> instruction;
			char instruction_tmp[instruction_length];

			dir = dir_in.read();

			memory_file.seekg(dir*(instruction_length+1), ios::beg);

			memory_file.getline(instruction_tmp, instruction_length+1);

			for(int i=0; i < instruction_length; i++)
			{
				if(instruction_tmp[i] == '1')
					instruction[instruction_length-1-i] = 1;
				else
					instruction[instruction_length-1-i] = 0;
			}
			std::cout << "La instruccion leida es: " << instruction << std::endl;
			instr_out.write(instruction);
		}
};

#endif
