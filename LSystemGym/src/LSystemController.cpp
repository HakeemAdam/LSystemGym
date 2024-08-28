#include "LSystemController.h"
#include "Lsystem.h"
#include "LSystemPreset.h"
#include <iostream>


//#include "LSystemVisualizer.h"


LSystemController::LSystemController(Lsystem* lsystem)
	:m_angle(20), m_length(5), m_lsystem(lsystem),
	m_iterations(5), m_currentColor(0, 0, 0, 255),
	m_animationMode(0),
	m_shouldRegenerate(false),
	m_shouldAnimate(false),
	m_animationSpeed(0.5f),
	m_isPaused(false)
{
	InitLystem();
	SetCustomStyle();
}

LSystemController::~LSystemController()
{
}

void LSystemController::DrawUI()
{
	float windowHeight = ImGui::GetFrameHeightWithSpacing() * 10; // Base height for other elements
	windowHeight += m_colorPickerExpanded ? 500 : 160; // Add height for color picker (expanded or collapsed)

	// Set size constraints for the window
	ImGui::SetNextWindowSizeConstraints(ImVec2(300, windowHeight), ImVec2(FLT_MAX, windowHeight));
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

	//ImGui::Separator();

	if (ImGui::BeginCombo("Presets", "Select a preset"))
	{
		for (const auto& preset : LSystemPresets::GetAllPresets())
		{
			if (ImGui::Selectable(preset.name.c_str()))
			{
				SetPreset(preset);
				//SetAngle(preset.angle);
				m_angle = preset.angle;
				m_shouldRegenerate = true;
			}
		}
		ImGui::EndCombo();
	}
	

	ImGui::Separator();

	if (ImGui::TreeNode("Color Picker"))
	{
		m_colorPickerExpanded = true;

		ImVec2 colorPickerSize = ImGui::GetContentRegionAvail();
		colorPickerSize.y = colorPickerSize.x;  // Make it square
		colorPickerSize.x = std::min(colorPickerSize.x, 200.0f);  // Limit maximum size
		colorPickerSize.y = std::min(colorPickerSize.y, 200.0f);  // Limit maximum size

		ImGuiColorEditFlags flags = ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoSmallPreview;
		if (ImGui::ColorPicker4("##picker", &m_currentColor.Value.x, flags, NULL))
		{
			m_currentColor = ImColor(m_currentColor.Value.x, m_currentColor.Value.y, m_currentColor.Value.z, m_currentColor.Value.w);
			m_shouldRegenerate = true;
		}

		ImGui::TreePop();
	}
	else
	{
		m_colorPickerExpanded = false;
		ImGui::ColorButton("Current Color", m_currentColor, ImGuiColorEditFlags_NoPicker | ImGuiColorEditFlags_NoTooltip, ImVec2(20, 20));
		ImGui::SameLine();
		ImGui::Text("Current Color: #%02X%02X%02X",
			static_cast<int>(m_currentColor.Value.x * 255),
			static_cast<int>(m_currentColor.Value.y * 255),
			static_cast<int>(m_currentColor.Value.z * 255));
	}

	ImGui::Separator();

	

	const char* modes[] = { "Growth", "Fade", "Cycle"};
	static int currentMode = 0;
	if (ImGui::Combo("Animation Mode", &currentMode, modes, IM_ARRAYSIZE(modes)))
	{
		switch (currentMode)
		{
		case 0:
			m_animationMode = 1;
			break;
		case 1:
			m_animationMode = 2;
			break;
		case 2:
			m_animationMode = 3;
			break;
		default:
			m_animationMode = 0;
			break;
		}

		if (m_animationMode != 3)
		{
			SetAngle(m_angle);
		}
	}
	//m_animationMode = (currentMode == 0) ? 1 : 2;
	

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
	ImGui::SameLine();

	if (ImGui::Button(m_isPaused ? "Resume" : "Pause")) {
		m_isPaused = !m_isPaused;
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

	// to do: check animation is not running before regenerating


	m_lsystem->GenerateLsystem(m_iterations);
	m_shouldRegenerate = true;
}
#pragma region styling
ImFont LSystemController::LoadCustomFont()
{
	ImGuiIO& io = ImGui::GetIO();
	ImFont returnfont;
	ImFont* font = io.Fonts->AddFontFromFileTTF("D:/dirs/Code/CPP/Rays/LSystemGym/LSystemGym/dependencies/fonts/Lato-Regular.ttf", 16.0f, NULL);
	if (font == nullptr) {
		std::cerr << "Failed to load font\n";
		// Use default font as fallback
		font = io.Fonts->AddFontDefault();
	}
	IM_ASSERT(font != nullptr);
	io.Fonts->Build();

	return returnfont = *font;
	
}

void LSystemController::SetCustomStyle()
{
	ImGuiStyle& style = ImGui::GetStyle();
	ImVec4* colors = style.Colors;

	// Set the window background to the specified green color
	colors[ImGuiCol_WindowBg] = ImVec4(0.2f, 0.6f, 0.06f, 1.0f);

	// Style for buttons
	colors[ImGuiCol_Button] = ImVec4(0.25f, 0.65f, 0.10f, 1.00f);
	colors[ImGuiCol_ButtonHovered] = ImVec4(0.30f, 0.70f, 0.13f, 1.00f);
	colors[ImGuiCol_ButtonActive] = ImVec4(0.35f, 0.75f, 0.15f, 1.00f);

	// Style for input fields (FrameBg is used for input fields, sliders, etc.)
	colors[ImGuiCol_FrameBg] = ImVec4(0.15f, 0.45f, 0.05f, 1.00f);
	colors[ImGuiCol_FrameBgHovered] = ImVec4(0.20f, 0.50f, 0.08f, 1.00f);
	colors[ImGuiCol_FrameBgActive] = ImVec4(0.25f, 0.55f, 0.10f, 1.00f);

	// Style for dropdown (combo box)
	colors[ImGuiCol_PopupBg] = ImVec4(0.15f, 0.45f, 0.05f, 1.00f);
	colors[ImGuiCol_Header] = ImVec4(0.25f, 0.65f, 0.10f, 1.00f);
	colors[ImGuiCol_HeaderHovered] = ImVec4(0.30f, 0.70f, 0.13f, 1.00f);
	colors[ImGuiCol_HeaderActive] = ImVec4(0.35f, 0.75f, 0.15f, 1.00f);

	// Style for slider grab
	colors[ImGuiCol_SliderGrab] = ImVec4(0.75f, 0.75f, 0.75f, 1.00f);
	colors[ImGuiCol_SliderGrabActive] = ImVec4(0.85f, 0.85f, 0.85f, 1.00f);

	// Set header to orange
	ImVec4 orangeColor = ImVec4(1.0f, 0.5f, 0.0f, 1.0f);  // Pure orange
	colors[ImGuiCol_Header] = orangeColor;
	colors[ImGuiCol_HeaderHovered] = ImVec4(1.0f, 0.6f, 0.1f, 1.0f);  // Slightly lighter orange
	colors[ImGuiCol_HeaderActive] = ImVec4(0.9f, 0.4f, 0.0f, 1.0f);   // Slightly darker orange

	// Set title bar colors to orange
	colors[ImGuiCol_TitleBg] = orangeColor;
	colors[ImGuiCol_TitleBgActive] = ImVec4(1.0f, 0.6f, 0.1f, 1.0f);  // Slightly lighter orange for active title bar
	colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.9f, 0.4f, 0.0f, 1.0f);  // Slightly darker orange for collapsed title bar

	// Style for scrollbar
	colors[ImGuiCol_ScrollbarBg] = ImVec4(0.15f, 0.45f, 0.05f, 0.5f);  // Semi-transparent dark green
	colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.3f, 0.7f, 0.1f, 1.0f);   // Light green
	colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.35f, 0.75f, 0.15f, 1.0f);
	colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.4f, 0.8f, 0.2f, 1.0f);

	// Text color for better contrast on green background
	colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);

	// Adjust rounding for buttons and input fields
	style.FrameRounding = 4.0f;
	style.GrabRounding = 4.0f;

	// Adjust global spacing
	style.ItemSpacing = ImVec2(8, 4);  // Space between widgets/lines
	style.ItemInnerSpacing = ImVec2(4, 4);  // Space between elements of a composed widget
	
}
#pragma endregion styling

void LSystemController::ResetFlags()
{
	m_shouldRegenerate = false;
	m_shouldAnimate = false;
}

bool LSystemController::SetFlags(bool flag)
{
	return m_shouldRegenerate = flag;
}
