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
	ImGui::SliderFloat("Angle", &m_angle, 0, 360, "%.0f", 0);

	ImGui::Text("Length");
	ImGui::SliderInt("Length", &m_length, 1, 100, "%d", 0);

	ImGui::Text("Iterations");
	//m_iterations = m_lsystem->GetIterations();
	if (ImGui::SliderInt("Iteration", &m_iterations, 1, 10, "%d", 0))
	{
		m_lsystem->SetIteration(m_iterations);
		m_lsystem->GenerateLsystem(m_iterations);
	}

	ImGui::Separator();

	static char axiomBuffer[256] = "F";
	if (ImGui::InputText("Axiom", axiomBuffer, IM_ARRAYSIZE(axiomBuffer)))
	{
		m_lsystem->SetAxiom(axiomBuffer);
		m_lsystem->GenerateLsystem(m_iterations);
		m_currentAxiom = std::string(axiomBuffer);
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

		}
	}
	
	

	if (ImGui::Button("Clear Rules"))
	{
		m_lsystem->ClearRules();
		m_lsystem->GenerateLsystem(m_iterations);
		inputBuffer[0] = '\0';
		
	}

	if (ImGui::Button("Clear Axiom"))
	{
		m_lsystem->SetAxiom("");
		axiomBuffer[0] = '\0';
	}

	if (ImGui::Button("Reset to Default"))
	{
		InitLystem();
		size_t inputBufferSize = sizeof(inputBuffer);
		size_t axiomBufferSize = sizeof(axiomBuffer);

		strncpy_s(inputBuffer, inputBufferSize, m_currentRule.c_str(), _TRUNCATE);
		strncpy_s(axiomBuffer, axiomBufferSize, m_currentAxiom.c_str(), _TRUNCATE);
	}
	

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
