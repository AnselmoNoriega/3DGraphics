#pragma once

#include "Command.h"

class CmdSetViewPort : public Command
{
public:
	const char* GetName() override
	{
		return "SetViewPort";
	}

	const char* GetDescription() override
	{
		return
			"SetViewPort(x, y, width, height)\n"
			"\n"
			"- SetViewPort.\n";
	}

	bool Execute(const std::vector<std::string>& params) override;
};

