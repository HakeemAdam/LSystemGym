#ifndef LSYSTEM_H

#include <string>
#include <vector>

#include "raymath.h"
//#include "raylib.h"

struct Rule
{
	char predecessor;
	std::string successor;
};

class Lsystem
{

private:
	int m_Iterations;
	std::string m_Axiom;
	std::vector<Rule> m_Rules;

	std::string m_currentString;

public:
	Lsystem() :m_Iterations(5), m_Axiom("Testing") {};
	~Lsystem() {};


	std::string GenerateLsystem(int iterations);
	std::string ProcessString(std::string Axiom);

	void SetAxiom(const std::string& axiom);

	std::string ApplyRules(char c);
	void AddRule(char predecessor, const std::string& successor);

	int GetIterations() const { return m_Iterations; }
	void SetIteration(int iteration);

	std::string GetCurrentString() const { return m_currentString; }


	void ClearRules();

	

};

#endif // !LSYSTEM_H