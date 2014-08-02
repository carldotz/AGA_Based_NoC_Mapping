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
	std::ofstream out_aga("aga_data");
	out_aga << "aga" << std::endl;
	std::ofstream out_ga_aga("ga_aga");
	out_ga_aga << " " << std::endl;
	std::ofstream out_ga_avg("ga_avg");
	out_ga_avg << " " << std::endl;
	std::ofstream out_aga_avg("aga_avg");
	out_aga_avg << " " << std::endl;
}

//void debug_aga(ACG *acg,NAG *nag)
//{
//	AGA aga(acg,nag,200,100,1E-10);
//	aga.set_k(0.9,0.6,0.2,0.01);
//	aga.execute();
//}

void aga_ga(ACG *acg,NAG *nag)
{
	double ga_s = 0;
	double ga_a[100][1000];
	for(int i=0;i<100;i++)
	{
		GA ga(acg,nag,200,100,1E-10);
		ga_s += (ga.execute(ga_a[i]));
	}
	double aga_s = 0;
	double aga_a[100][1000];
	for(int i=0;i<100;++i)
	{
		AGA aga(acg,nag,200,100,1E-10);
		aga.set_k(0.9,0.6,0.2,0.01);
		aga_s += (aga.execute(aga_a[i]));
	}

	std::ofstream out_ga("ga_avg",std::fstream::app);
	for(int i=0;i<1000;++i)
	{
		double avg = 0;
		for(int j=0;j<100;++j)
		{
			avg += ga_a[j][i];
		}
		out_ga << avg/100 << std::endl;
	}

	std::ofstream out_aga("aga_avg",std::fstream::app);
	for(int i=0;i<1000;++i)
	{
		double avg = 0;
		for(int j=0;j<100;++j)
		{
			avg += aga_a[j][i];
		}
		out_aga << avg/100 << std::endl;
	}

	std::ofstream out("ga_aga",std::fstream::app);
	out << "ga:" << ga_s << std::endl;
	out << "aga:" << aga_s << std::endl;
}

void test1()
{
	ACG acg;
	TGFF_Manager tm(&acg);
	tm.change_properties("seed", "10");
	acg.add_from_tgff(tm);
	NAG nag(7,7);
	aga_ga(&acg,&nag);
}

void test2()
{
	ACG acg;
	TGFF_Manager tm(&acg);
	tm.change_properties("seed", "0");
	acg.add_from_tgff(tm);
	NAG nag(2,3);
	aga_ga(&acg,&nag);
}

void test3()
{
	ACG acg;
	TGFF_Manager tm(&acg);
	tm.change_properties("seed", "2");
	acg.add_from_tgff(tm);
	NAG nag(4,5);
	aga_ga(&acg,&nag);
}

void test4()
{
	ACG acg;
	TGFF_Manager tm(&acg);
	tm.change_properties("seed", "2");
	acg.add_from_tgff(tm);
	NAG nag(8,8);
	aga_ga(&acg,&nag);
}

void test5()
{
	ACG acg;
	TGFF_Manager tm(&acg);
	tm.change_properties("seed", "8");
	acg.add_from_tgff(tm);
	NAG nag(7,7);
	aga_ga(&acg,&nag);
}

void test6()
{
	ACG acg;
	TGFF_Manager tm(&acg);
	tm.change_properties("seed", "11");
	acg.add_from_tgff(tm);
	NAG nag(5,4);
	aga_ga(&acg,&nag);
}

void test7()
{
	ACG acg;
	TGFF_Manager tm(&acg);
	tm.change_properties("seed", "72");
	acg.add_from_tgff(tm);
	NAG nag(8,8);
	aga_ga(&acg,&nag);
}

int main()
{
	clear_out_file();
//	test1();
//	test2();
//	test3();
//	test4();
	test5();
	test6();
	test7();
	return 0;
}
