#pragma once

#include "Command.h"

class CmdShowViewPort : public Command
{
public:
	const char* GetName() override
	{
		return "ShowViewPort";
	}

	const char* GetDescription() override
	{
		return
			"ShowViewPort(bool)\n"
			"\n"
			"- ShowViewPort\n";
	}

	bool Execute(const std::vector<std::string>& params) override;
};

