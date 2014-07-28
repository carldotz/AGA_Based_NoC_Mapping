#include "tgff_manager.h"
#include "acg_node.h"
#include "acg.h"
#include <vector>
#include <string>
#include <fstream>
#include <memory>
#include <exception>

using std::vector;
using std::string;
using std::ifstream;
using std::ofstream;
using std::shared_ptr;

void TGFF_Manager::write_option()
{
	ofstream pro_file(properties_filename,std::fstream::out);
	if(pro_file.fail())	throw std::runtime_error("tgff properties file open fail");
	for(auto p : properties) {
		pro_file << p.first << " " << p.second << std::endl;
	}
	pro_file << "trans_write" << std::endl;
	pro_file << "tg_cnt 1" << std::endl;
	pro_file << "tg_write" << std::endl;
	pro_file << "eps_write" << std::endl;
}

void TGFF_Manager::read_result()
{
	ifstream result(result_filename,std::fstream::in);
	if(result.fail())	throw std::runtime_error("tgff result file open fail");

	string str;
	vector<float> commCost;

	const string prefix1("@COMMUNICATION_TYPE");
	const string prefix2("@TASK_GRAPH");
	const string prefix3("\tTASK");
	const string prefix4("\tARC");

	while(getline(result,str)){
		if (!str.compare(0, prefix1.size(), prefix1)){
			getline(result,str);
			getline(result,str);
			getline(result,str);
			getline(result,str);
			getline(result,str);

			while(getline(result,str) && str[0]!='}') {
				commCost.push_back(stof(str.substr(7)));
			}
		} else if (!str.compare(0, prefix2.size(), prefix2)){
			getline(result,str);
			getline(result,str);

			Node::no_type acg_i = 0;
			int index;
			while(getline(result,str) && str[0]!='}') {
				if (!str.compare(0, prefix3.size(), prefix3)){
					(*acg).add_node(acg_i++);
				} else if (!str.compare(0, prefix4.size(), prefix4)){
					index = str.find("FROM");
					str = str.substr(index+8);
					index = str.find("TO");

					auto source = (*acg)[(stof(str.substr(0,index-1)))];
					str = str.substr(index+7);
					index = str.find("TYPE");
					auto target = (*acg)[(stof(str.substr(0,index-1)))];
					index = stof(str.substr(index+4));
					(*source).add_edge(target,commCost[index]);
				}
			}
		}
	}
}
