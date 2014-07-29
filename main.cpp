#include <iostream>
#include <fstream>
#include "tgff_manager.h"
#include "nag.h"
#include "ga.h"

int main()
{
	ACG acg;
	TGFF_Manager tm(&acg);
	tm.change_properties("seed", "0");
	acg.add_from_tgff(tm);
	NAG nag(8,8);

	std::ofstream out("data");
	out << "un" << std::endl;

	for(int i=0;i<100;i++)
	{
		GA ga(&acg,&nag,200,100,1E-10);
		ga.execute();
	}
	return 0;
}

