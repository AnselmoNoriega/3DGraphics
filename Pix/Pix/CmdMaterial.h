#pragma once
#include "Command.h"

class CmdSetMaterialAmbient : public Command
{
public:
	const char* GetName() override
	{
		return "SetMaterialAmbient";
	}
	const char* GetDescription() override
	{
		return "Sets Ambient";
	}

	bool Execute(const std::vector<std::string>& params);
};

class CmdSetMaterialDiffuse : public Command
{
public:
	const char* GetName() override
	{
		return "SetMaterialDiffuse";
	}
	const char* GetDescription() override
	{
		return "Sets Diffuse";
	}

	bool Execute(const std::vector<std::string>& params);
};

class CmdSetMaterialSpecular : public Command
{
public:
	const char* GetName() override
	{
		return "SetMaterialSpecular";
	}
	const char* GetDescription() override
	{
		return "Sets Specular";
	}

	bool Execute(const std::vector<std::string>& params);
};

class CmdSetMaterialShininess : public Command
{
public:
	const char* GetName() override
	{
		return "SetMaterialShininess";
	}
	const char* GetDescription() override
	{
		return "Sets Shininess";
	}

	bool Execute(const std::vector<std::string>& params);
};