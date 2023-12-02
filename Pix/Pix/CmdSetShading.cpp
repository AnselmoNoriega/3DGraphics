#include "CmdSetShading.h"
#include "PrimitivesManager.h"

bool CmdSetShading::Execute(const std::vector<std::string>& params)
{
	if (params.size() < 1)
	{
		return false;
	}
	
	if (params[0] == "groud")
	{

	}
	PrimitivesManager::Get()->set
}
