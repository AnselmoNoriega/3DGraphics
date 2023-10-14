#pragma once
#include "Command.h"

class CmdBeginDraw : public Command
{
public:
	const char* GetName() override
	{
		return "BeginDraw";
	}

	const char* GetDescription() override
	{
		return
			"BeginDraw(x, y)\n"
			"\n"
			"- Begins the rasterization.";
	}

	bool Execute(const std::vector<std::string>& params) override;
};