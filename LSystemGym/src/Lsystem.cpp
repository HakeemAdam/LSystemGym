#include "Lsystem.h"

std::string Lsystem::GenerateLsystem(int iterations, std::string Axiom)
{
	iterations = m_Iterations;


	std::string startString = Axiom;
	std::string endString = "";

	for (size_t i = 0; i < iterations; i++)
	{
		endString = ProcessString(startString);
		startString = endString;
	}
	
	return endString;
}

std::string Lsystem::ProcessString(std::string Axiom)
{
	return std::string();
}
