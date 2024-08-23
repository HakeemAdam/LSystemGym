#include "LSystemController.h"
#include "Lsystem.h"
#include "LSystemPreset.h"

//#include "LSystemVisualizer.h"


LSystemController::LSystemController(Lsystem* lsystem)
	:m_angle(20), m_length(5), m_lsystem(lsystem),
	m_iterations(5), m_currentColor(0, 0, 0, 255),
	m_animationMode(0),
	m_shouldRegenerate(false),
	m_shouldAnimate(false),
	m_animationSpeed(0.5f)
{
	InitLystem();
}

LSystemController::~LSystemController()
{
}

void LSystemController::DrawUI()
{

	ImGui::Begin("L-System Controller", NULL);
	
	float currentAngle = m_angle;
	if (ImGui::SliderFloat("Angle", &currentAngle, 0, 360, "%.0f", 0))
	{
		m_angle = currentAngle;
		m_shouldRegenerate = true;
	}
	ImGui::SameLine();
	if (ImGui::Button("Reset##Angle"))
	{
		m_angle = m_currentPreset->angle;
		m_shouldRegenerate = true;
	}

	if (ImGui::SliderInt("Length", &m_length, 1, 100, "%d", 0))
	{
		m_shouldRegenerate = true;
	}

	if (ImGui::SliderInt("Iteration", &m_iterations, 1, 10, "%d", 0))
	{
		m_lsystem->SetIteration(m_iterations);
		m_lsystem->GenerateLsystem(m_iterations);
		m_shouldRegenerate = true;
	}

	ImGui::Separator();

	static char axiomBuffer[256] = "F";
	strcpy_s(axiomBuffer, m_currentAxiom.c_str());
	if (ImGui::InputText("Axiom", axiomBuffer, IM_ARRAYSIZE(axiomBuffer)))
	{
		m_currentAxiom = std::string(axiomBuffer);
		m_lsystem->SetAxiom(m_currentAxiom);
		m_lsystem->GenerateLsystem(m_iterations);
		m_shouldRegenerate = true;
	}

	ImGui::Text("Rules");
	bool rulesChnaged = false;

	for (size_t i = 0; i < m_rulesInputs.size(); i++)
	{
		char buffer[256];
		strcpy_s(buffer, m_rulesInputs[i].c_str());
		std::string label = "Rule " + std::to_string(i + 1);
		if (ImGui::InputText(label.c_str(), buffer, IM_ARRAYSIZE(buffer), ImGuiInputTextFlags_EnterReturnsTrue))
		{
			m_rulesInputs[i] = buffer;
			rulesChnaged = true;
		}
	}

	if (rulesChnaged)
	{
		UpdateRules();
	}

	if (ImGui::Button("Add Rule"))
	{
		m_rulesInputs.push_back("");
		UpdateRules();
	}

	ImGui::SameLine();

	if (ImGui::Button("Apply Rules"))
	{
		UpdateRules();
	}

	ImGui::SameLine();
	
	if (ImGui::Button("Clear Rules"))
	{
		m_rulesInputs.clear();
		m_lsystem->ClearRules();
		m_lsystem->GenerateLsystem(m_iterations);
		m_shouldRegenerate = true;
		
	}

	ImGui::SameLine();

	if (ImGui::Button("Clear Axiom"))
	{
		m_currentAxiom = "";
		m_lsystem->SetAxiom("");
		m_shouldRegenerate = true;
	}

	ImGui::SameLine();

	if (ImGui::Button("Reset to Default"))
	{
		InitLystem();
		m_shouldRegenerate = true;
	}

	ImGui::Separator();

	if (ImGui::BeginCombo("Presets", "Select a preset"))
	{
		for (const auto& preset : LSystemPresets::GetAllPresets())
		{
			if (ImGui::Selectable(preset.name.c_str()))
			{
				SetPreset(preset);
				m_shouldRegenerate = true;
			}
		}
		ImGui::EndCombo();
	}
	

	ImGui::Separator();
	ImGui::Text("Color");
	ImVec2 colorPickerSize(200, 200);
	
	ImGui::BeginChild("ColorPickerChild", colorPickerSize);
	ImGuiColorEditFlags flags =  ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoSmallPreview;

	if (ImGui::ColorPicker4("##picker", &m_currentColor.Value.x, flags, NULL))
	{
		
		m_currentColor = ImColor(m_currentColor.Value.x, m_currentColor.Value.y, m_currentColor.Value.z, m_currentColor.Value.w);
		m_shouldRegenerate = true;
	}
	ImGui::EndChild();

	ImGui::Separator();

	

	const char* modes[] = { "Growth", "Fade" };
	static int currentMode = 0;
	ImGui::Combo("Animation Mode", &currentMode, modes, IM_ARRAYSIZE(modes));
	m_animationMode = (currentMode == 0) ? 1 : 2;

	if (ImGui::Button("Regenerate L-System"))
	{
		m_shouldRegenerate = true;
	}

	ImGui::SameLine();

	if (ImGui::Button("Animate"))
	{
		m_shouldAnimate = true;
	}

	ImGui::SameLine();

	if (ImGui::Button("Regenerate and Animate"))
	{
		m_shouldRegenerate = true;
		m_shouldAnimate = true;
	}

	ImGui::SliderFloat("Animation Speed", &m_animationSpeed, 0.001f, 1.0f, "%.04f", 0);

	ImGui::End();
}

void LSystemController::InitLystem()
{
	if (m_lsystem)
	{
		m_lsystem->ClearRules();
		InitDefaultRules();
		m_lsystem->GenerateLsystem(m_iterations);
	}
}

void LSystemController::InitDefaultRules()
{
	m_currentAxiom = "X";
	m_lsystem->SetAxiom(m_currentAxiom);
	m_rulesInputs = { "X=F+[[X]-X]-F[-FX]+X", "F=FF" };
	UpdateRules();
}

void LSystemController::SetPreset(const LSystemPreset& preset)
{
	m_currentPreset = &preset;
	m_currentAxiom = preset.axiom;
	m_lsystem->SetAxiom(m_currentAxiom);
	m_lsystem->ClearRules();

	m_rulesInputs.clear();

	for (const auto& rule : preset.rules )
	{
		std::string ruleStr = std::string(1, rule.first) + "=" + rule.second;
		m_rulesInputs.push_back(ruleStr);
		m_lsystem->AddRule(rule.first, rule.second);
	}
	
	m_angle = preset.angle;
	m_lsystem->GenerateLsystem(m_iterations);
	m_shouldRegenerate = true;
}

void LSystemController::UpdateRules()
{
	m_lsystem->ClearRules();
	for (const auto& rule : m_rulesInputs )
	{
		size_t equalPos = rule.find('=');
		if (equalPos != std::string::npos && equalPos > 0 && equalPos < rule.length() - 1)
		{
			char symbol = rule[0];
			std::string replacement = rule.substr(equalPos + 1);
			m_lsystem->AddRule(symbol, replacement);
		}
	}
	m_lsystem->GenerateLsystem(m_iterations);
	m_shouldRegenerate = true;
}

void LSystemController::ResetFlags()
{
	m_shouldRegenerate = false;
	m_shouldAnimate = false;
}
