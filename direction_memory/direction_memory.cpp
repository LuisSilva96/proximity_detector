# include "direction_memory.h"

Direction_Memory::Direction_Memory(sc_module_name nm):sc_module(nm)
{
	int cod = cod_op.read();

	if(cod == 0)
	{
		load();
	}
	else if (cod == 1)
	{
		store();
	}
}
