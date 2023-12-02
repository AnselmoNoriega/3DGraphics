#include "CmdSetShading.h"
#include "PrimitivesManager.h"
#include "Rasterizer.h"

bool CmdSetShading::Execute(const std::vector<std::string>& params)
{
	if (params.size() < 1)
	{
		return false;
	}

	ShadeMode shadeMode = ShadeMode::Gouraud;
	
	if (params[0] == "falt")
	{
		shadeMode = ShadeMode::Flat;
	}
	else if (params[0] == "gouraud")
	{
		shadeMode = ShadeMode::Gouraud;
	}
	else if (params[0] == "phong")
	{
		shadeMode = ShadeMode::Phoh;
	}

	Rasterizer::Get()->SetShadeMode(shadeMode);
	return true;
}
