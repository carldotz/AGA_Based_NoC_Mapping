#include <iostream>
#include "tgff_manager.h"
#include "nag.h"

int main()
{
	ACG acg;
	TGFF_Manager tm(&acg);
	tm.change_properties("seed", "2");
	acg.add_from_tgff(tm);
	NAG nag(8,8);
	return 0;
}

