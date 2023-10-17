#include "CmdSetFillMode.h"
#include "Rasterizer.h"

bool CmdSetFillMode::Execute(const std::vector<std::string>& params)
{
	if (params.size() != 1)
	{
		return false;
	}

	if (params[0] == "WireFrame")
	{
		Rasterizer::Get()->SetFillMode(FillMode::WireFrame);
		return true;
	}
	else if (params[0] == "Solid")
	{
		Rasterizer::Get()->SetFillMode(FillMode::Solid);
		return true;
	}
	else
	{
		return false;
	}
}
