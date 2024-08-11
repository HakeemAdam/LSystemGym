#ifndef LSYSTEM_H

#include <string>

class Lsystem
{

private:
	int m_Iterations;
	std::string m_Axiom;

public:
	Lsystem() :m_Iterations(5), m_Axiom("Testing") {};
	~Lsystem() {};


	std::string GenerateLsystem(int iterations, std::string Axiom);
	std::string ProcessString(std::string Axiom);

};

#endif // !LSYSTEM_H