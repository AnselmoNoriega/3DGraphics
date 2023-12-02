#include "CmdStartShading.h"

bool CmdStartShading::Execute(const std::vector<std::string>& params)
{
	if (params.size() < 1)
	{
		return false;
	}

	bool clip = params[0] == "true";

	return true;
}
