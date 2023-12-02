#pragma once
#include "Command.h"

class CmdStartShading : public Command
{
public:
	const char* GetName() override
	{
		return "StartShading";
	}

	const char* GetDescription() override
	{
		return
			"start Shade(true)";
	}

	bool Execute(const std::vector<std::string>& params) override;
};

