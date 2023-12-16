#include "CmdSetAddressMode.h"
#include "TextureCache.h"

bool CmdSetAddressMode::Execute(const std::vector<std::string>& params)
{
	if (params.size() < 1)
	{
		return false;
	}

	AddressMode mode;
	if (params[0] == "Clamp")
	{
		mode = AddressMode::Clamp;
	}
	else if (params[0] == "Border")
	{
		mode = AddressMode::Border;
	}
	else if (params[0] == "Mirror")
	{
		mode = AddressMode::Mirror;
	}
	else if (params[0] == "Wrap")
	{
		mode = AddressMode::Wrap;
	}

	TextureCache::Get()->SetAddressMode(mode);
}
