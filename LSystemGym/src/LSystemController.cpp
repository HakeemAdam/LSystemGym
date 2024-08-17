#include "LSystemController.h"
#include "Lsystem.h"

LSystemController::LSystemController(Lsystem* lsystem)
	:m_angle(90), m_length(5), m_lsystem(lsystem), m_iterations(5)
{
	//m_lsystem = new Lsystem();
}

LSystemController::~LSystemController()
{
	//delete m_lsystem;
}

void LSystemController::DrawUI()
{

	ImGui::Begin("L-System Controller", NULL);
	ImGui::Text("Angle");
	ImGui::SliderFloat("Angle", &m_angle, 0, 360, "%.3f", 0);

	ImGui::Text("Length");
	ImGui::SliderInt("Length", &m_length, 1, 10, "%d", 0);

	ImGui::Text("Iterations");
	//m_iterations = m_lsystem->GetIterations();
	if (ImGui::SliderInt("Iteration", &m_iterations, 1, 10, "%d", 0))
	{
		m_lsystem->SetIteration(m_iterations);
		m_lsystem->GenerateLsystem(m_iterations);
	}

	ImGui::Separator();


	if (ImGui::Button("Clear Rules"))
	{
		m_lsystem->ClearRules();
		m_lsystem->GenerateLsystem(m_iterations);
		
	}

	if (ImGui::Button("Generate L-System"))
	{
		InitLystem();
	}
	

	ImGui::End();
}

void LSystemController::InitLystem()
{
	if (m_lsystem)
	{
		m_lsystem->SetAxiom("F");
		m_lsystem->AddRule('F', "FF+[+F-F-F]-[-F+F+F]");
		m_lsystem->GenerateLsystem(m_iterations);
	}
}
