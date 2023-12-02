#pragma once
#include "Command.h"

class CmdSetShading : public Command
{
public:
	const char* GetName() override
	{
		return "SetShade";
	}

	const char* GetDescription() override
	{
		return
			"SetShade(mode)";
	}

	bool Execute(const std::vector<std::string>& params) override;
};

