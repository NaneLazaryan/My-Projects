#pragma once

#include <vector>
#include <string>

struct Rule
{
	std::string target;
	std::vector<std::string> dependencies;
	std::vector<std::string> commands;
};