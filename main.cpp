#include <iostream>
#include <fstream>
#include "tgff_manager.h"
#include "nag.h"
#include "ga.h"
#include "aga.h"

void clear_out_file()
{
	std::ofstream out_ga("ga_data");
	out_ga << "ga" << std::endl;
	out_ga.close();
	std::ofstream out_aga("aga_data");
	out_aga << "aga" << std::endl;
	out_aga.close();
}

void debug_aga(ACG *acg,NAG *nag)
{
	AGA aga(acg,nag,200,100,1E-10);
	aga.set_k(1,0.5);
	aga.execute();
}

void aga_ga(ACG *acg,NAG *nag)
{
//	for(int i=0;i<100;i++)
//	{
//		GA ga(acg,nag,200,100,1E-10);
//		ga.execute();
//	}
	for(int i=0;i<100;++i)
	{
		AGA aga(acg,nag,200,100,1E-10);
		aga.set_k(1,0.5);
		aga.execute();
	}
}

void aga_parameter_scan(ACG *acg,NAG *nag)
{
	for(float k1=0.1;k1<1;k1+=0.1)
	{
		for(float k3=0.1;k3<1;k3+=0.1)
		{
			std::ofstream out_aga("aga_data",std::ofstream::app);
			out_aga << "************************\n"
					<< "k1=" << k1 << ",k3=" << k3
					<< "\n************************" << std::endl;
			out_aga.close();
			for(int i=0;i<100;i++)
			{
				AGA aga(acg,nag,200,100,1E-10);
				aga.set_k(k1,k3);
				aga.execute();
			}
		}
	}
}

int main()
{
	ACG acg;
	TGFF_Manager tm(&acg);
	tm.change_properties("seed", "2");
	acg.add_from_tgff(tm);
	NAG nag(8,8);
	clear_out_file();
//	debug_aga(&acg,&nag);
	aga_ga(&acg,&nag);
//	aga_parameter_scan(&acg,&nag);
	return 0;
}
