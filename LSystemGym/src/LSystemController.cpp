#include "LSystemController.h"

void LSystemController::DrawUI()
{

	ImGui::Begin("L-System Controller", NULL);
	ImGui::Text("Angle");
	ImGui::SliderFloat("Angle", &m_angle, 0, 360, "%.3f", 0);

	ImGui::Separator();

	ImGui::Text("Iterations");
	ImGui::SliderInt("Iteration", &m_iterations, 1, 10, "%d", 0);


	ImGui::End();
}
