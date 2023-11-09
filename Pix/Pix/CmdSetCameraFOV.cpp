#include "CmdSetCameraFOV.h"
#include "Camera.h"
#include "VariableCache.h"

bool CmdSetCameraFOV::Execute(const std::vector<std::string>& params)
{
	if (params.size() < 3)
	{
		return false;
	}
	VariableCache* vc = VariableCache::Get();
	float value = vc->GetFloat(params[0]);

	Camera::Get()->SetFOV(value * 3.1416 / 180);
	return true;
}


