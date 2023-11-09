#pragma once
#include "Command.h"

class CmdSetCameraNear: public Command
{
public:
	const char* GetName() override
	{
		return "SetCameraNear";
	}

	const char* GetDescription() override
	{
		return
			"SetCameraNear(x, y, z)\n"
			"\n"
			"- Sets Camera Near.";
	}

	bool Execute(const std::vector<std::string>& params) override;
};

