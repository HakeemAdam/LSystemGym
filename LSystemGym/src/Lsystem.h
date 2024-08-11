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

public:
	Lsystem() :m_Iterations(5), m_Axiom("Testing") {};
	~Lsystem() {};


	std::string GenerateLsystem(int iterations, std::string Axiom);
	std::string ProcessString(std::string Axiom);

	std::string ApplyRules(char c);
	void AddRule(char predecessor, const std::string& successor);

	

};

#endif // !LSYSTEM_H