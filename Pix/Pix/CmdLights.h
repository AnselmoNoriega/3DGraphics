#pragma once
#include "Command.h"

class CmdSetLightAmbient : public Command
{
public:
	const char* GetName() override
	{
		return "SetLightAmbient";
	}
	const char* GetDescription() override
	{
		return "Sets Ambient";
	}

	bool Execute(const std::vector<std::string>& params);
};

class CmdSetLightDiffuse : public Command
{
public:
	const char* GetName() override
	{
		return "SetLightDiffuse";
	}
	const char* GetDescription() override
	{
		return "Sets Diffuse";
	}

	bool Execute(const std::vector<std::string>& params);
};

class CmdSetLightSpecular : public Command
{
public:
	const char* GetName() override
	{
		return "SetLightSpecular";
	}
	const char* GetDescription() override
	{
		return "Sets Specular";
	}

	bool Execute(const std::vector<std::string>& params);
};