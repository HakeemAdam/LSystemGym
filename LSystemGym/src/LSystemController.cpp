#include "LSystemController.h"
#include "Lsystem.h"
#include "LSystemPreset.h"
//#include "LSystemVisualizer.h"


LSystemController::LSystemController(Lsystem* lsystem)
	:m_angle(90), m_length(5), m_lsystem(lsystem),
	m_iterations(5), m_currentColor(0, 0, 0, 255),
	m_animationMode(0),
	m_shouldRegenerate(false),
	m_shouldAnimate(false),
	m_animationSpeed(0.5f)
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
	if (ImGui::SliderFloat("Angle", &m_angle, 0, 360, "%.0f", 0))
	{
		m_shouldRegenerate = true;
	}

	ImGui::Text("Length");
	if (ImGui::SliderInt("Length", &m_length, 1, 100, "%d", 0))
	{
		m_shouldRegenerate = true;
	}

	ImGui::Text("Iterations");
	//m_iterations = m_lsystem->GetIterations();
	if (ImGui::SliderInt("Iteration", &m_iterations, 1, 10, "%d", 0))
	{
		m_lsystem->SetIteration(m_iterations);
		m_lsystem->GenerateLsystem(m_iterations);
		m_shouldRegenerate = true;
	}

	ImGui::Separator();

	static char axiomBuffer[256] = "F";
	if (ImGui::InputText("Axiom", axiomBuffer, IM_ARRAYSIZE(axiomBuffer)))
	{
		m_lsystem->SetAxiom(axiomBuffer);
		m_lsystem->GenerateLsystem(m_iterations);
		m_currentAxiom = std::string(axiomBuffer);
		m_shouldRegenerate = true;
	}

	static char inputBuffer[256] = "";
	ImGui::Text("Rules");
	bool inputChanged = ImGui::InputText("Enter New Rule", inputBuffer, IM_ARRAYSIZE(inputBuffer), ImGuiInputTextFlags_EnterReturnsTrue);
	
	if (inputChanged || ImGui::Button("Apply Rules"))
	{
		if (inputBuffer[0] != '\0')
		{
			m_lsystem->ClearRules();
			m_lsystem->SetAxiom("F");
			m_lsystem->AddRule('F', std::string(inputBuffer));
			m_lsystem->GenerateLsystem(m_iterations);
			m_currentRule = std::string(inputBuffer);
			m_shouldRegenerate = true;

		}
	}
	
	

	if (ImGui::Button("Clear Rules"))
	{
		m_lsystem->ClearRules();
		m_lsystem->GenerateLsystem(m_iterations);
		inputBuffer[0] = '\0';
		m_shouldRegenerate = true;
		
	}

	if (ImGui::Button("Clear Axiom"))
	{
		m_lsystem->SetAxiom("");
		axiomBuffer[0] = '\0';
		m_shouldRegenerate = true;
	}


	size_t inputBufferSize = sizeof(inputBuffer);
	size_t axiomBufferSize = sizeof(axiomBuffer);

	if (ImGui::Button("Reset to Default"))
	{
		InitLystem();
		
		strncpy_s(inputBuffer, inputBufferSize, m_currentRule.c_str(), _TRUNCATE);
		strncpy_s(axiomBuffer, axiomBufferSize, m_currentAxiom.c_str(), _TRUNCATE);
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
				strncpy_s(axiomBuffer, axiomBufferSize, preset.axiom.c_str(), _TRUNCATE);
				m_shouldRegenerate = true;
			}
		}
		ImGui::EndCombo();
	}
	

	ImGui::Separator();
	//m_currentColor = ImColor(0, 0, 0, 255);
	if (ImGui::ColorPicker4("Set Color", &m_currentColor.Value.x))
	{
		
		m_currentColor = ImColor(m_currentColor.Value.x, m_currentColor.Value.y, m_currentColor.Value.z, m_currentColor.Value.w);
		m_shouldRegenerate = true;
	}

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

	ImGui::SliderFloat("Animation Speed", &m_animationSpeed, 0.01f, 1.0f, "%.03f", 0);

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
	m_lsystem->SetAxiom("X");
	m_lsystem->AddRule('X', "F+[[X]-X]-F[-FX]+X");
	m_lsystem->AddRule('F', "FF");
}

void LSystemController::SetPreset(const LSystemPreset& preset)
{
	m_currentAxiom = preset.axiom;
	m_currentRules = preset.rules;
	m_lsystem->SetAxiom(m_currentAxiom);
	m_lsystem->ClearRules();

	for (const auto& rule : m_currentRules )
	{
		m_lsystem->AddRule(rule.first, rule.second);
	}
	m_lsystem->GenerateLsystem(m_iterations);
}

void LSystemController::ResetFlags()
{
	m_shouldRegenerate = false;
	m_shouldAnimate = false;
}
