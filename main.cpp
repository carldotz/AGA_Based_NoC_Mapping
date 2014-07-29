#include <iostream>
#include <fstream>
#include "tgff_manager.h"
#include "nag.h"
#include "ga.h"
#include "aga.h"

int main()
{
	ACG acg;
	TGFF_Manager tm(&acg);
	tm.change_properties("seed", "0");
	acg.add_from_tgff(tm);
	NAG nag(8,8);

//	std::ofstream out_ga("ga_data");
//	out_ga << "ga" << std::endl;
//	out_ga.close();
	std::ofstream out_aga("aga_data");
	out_aga << "aga" << std::endl;
	out_aga.close();

//	for(int i=0;i<100;i++)
//	{
//		GA ga(&acg,&nag,200,100,1E-10);
//		ga.execute();
//	}
	for(float k1=0.1;k1<1;k1+=0.05)
	{
		for(float k2=0.1;k2<0.5;k2+=0.05)
		{
			std::ofstream out_aga("aga_data",std::ofstream::app);
			out_aga << "************************\n"
					<< "k1=" << k1 << ",k2=" << k2
					<< "\n************************" << std::endl;
			out_aga.close();
			for(int i=0;i<10;i++)
			{
				AGA aga(&acg,&nag,200,100,1E-10);
				aga.set_k(k1,k2);
				aga.execute();
			}
		}
	}
	return 0;
}

