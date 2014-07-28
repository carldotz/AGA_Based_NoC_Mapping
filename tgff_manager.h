#ifndef TGFF_MANAGER_H
#define TGFF_MANAGER_H

#include <fstream>
#include <cstdlib>
#include <string>
#include <map>
#include "acg.h"

class ACG;
class TGFF_Manager {
public:
	explicit TGFF_Manager(ACG *a) : acg(a) {}
	void run_tgff()
	{
		std::system("./tgff ACG");
	}
	void change_properties(const std::string key, const std::string value)
	{
		properties[key] = value;
	}
	void write_option();
	void read_result();
	void clear_trash()
	{
		std::system("rm ACG.tgff");
		std::system("rm ACG.tgffopt");
		std::system("rm ACG.eps");
		std::system("rm ACG.vcg");
	}

private:
	const std::string result_filename = "ACG.tgff";
	const std::string properties_filename = "ACG.tgffopt";
	std::map<std::string,std::string> properties {
		{"seed","0"},
		{"period_mul", "1"},
		{"prob_multi_start_nodes", "0.8"},
		{"prob_periodic", "1"},
		{"start_node", "5 4"},
		{"task_type_cnt", "30"},
		{"task_cnt", "5 2"},
		{"trans_type_cnt", "50"},
		{"gen_series_parallel" ,""},
		{"series_len", "5 4"},
		{"series_wid", "5 4"},
		{"series_must_rejoin", "0"},
		{"series_subgraph_fork_out", "0.8"},
		{"series_local_xover", "4"},
		{"series_global_xover", "8"},
		{"table_label COMMUNICATION_TYPE", ""},
		{"table_cnt", "1"},
		{"type_attrib C", "30 20"},
	};
	ACG *acg;
};

#endif // TGF F_MANAGER_H
