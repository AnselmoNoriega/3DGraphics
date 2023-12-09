#include "CmdSetCorrectUV.h"
#include "PrimitivesManager.h"
#include "VariableCache.h"

bool CmdSetCorrectUV::Execute(const std::vector<std::string>& params)
{
	if (params.size() < 1)
	{
		return false;
	}

	bool correct = VariableCache::Get()->GetBool(params[0]);
	PrimitivesManager::Get()->SetCorrectUV(correct);
	return true;
}
