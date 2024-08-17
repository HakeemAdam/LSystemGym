#include "Lsystem.h"
#include "iostream"

std::string Lsystem::GenerateLsystem(int iterations, std::string Axiom)
{

	std::string startString = Axiom;
	std::string endString = "";

	for (size_t i = 0; i < m_Iterations; i++)
	{
		endString = ProcessString(startString);
		startString = endString;
	}
	
	return endString;
}

std::string Lsystem::ProcessString(std::string Axiom)
{
	std::string newString = "";

	for (char c : Axiom)
	{
		newString += ApplyRules(c);
	}
	return newString;
}

std::string Lsystem::ApplyRules(char c)
{
	for (const auto& rule : m_Rules)
	{
		if (rule.predecessor == c)
		{
			return rule.successor;
		}
	}
	return std::string(1,c);
}

void Lsystem::AddRule(char predecessor, const std::string& successor)
{
	m_Rules.push_back({ predecessor, successor });
}

void Lsystem::ClearRules()
{
	m_Rules.clear();
	//std::cout << "Rules cleared. Current rule count: " << m_Rules.size() << std::endl;
}


