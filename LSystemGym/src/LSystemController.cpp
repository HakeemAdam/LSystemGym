#include "LSystemController.h"

void LSystemController::DrawUI()
{

	ImGui::Begin("RAY_LSYSTEM", NULL);
	ImGui::Text("Angle");
	ImGui::SliderFloat("Angle", &m_angle, 0, 360, "%.3f", 0);
	ImGui::End();
}
