#include "LSystemController.h"
#include "Lsystem.h"

LSystemController::LSystemController()
	:m_angle(90), m_length(5), m_lsystem(nullptr)
{
	m_lsystem = new Lsystem();
}

LSystemController::~LSystemController()
{
	delete m_lsystem;
}

void LSystemController::DrawUI()
{

	ImGui::Begin("L-System Controller", NULL);
	ImGui::Text("Angle");
	ImGui::SliderFloat("Angle", &m_angle, 0, 360, "%.3f", 0);

	ImGui::Separator();

	ImGui::Text("Length");
	ImGui::SliderInt("Iteration", &m_length, 1, 10, "%d", 0);

	if (ImGui::Button("Clear Rules"))
	{
		m_lsystem->ClearRules();
		
	}
	

	ImGui::End();
}
