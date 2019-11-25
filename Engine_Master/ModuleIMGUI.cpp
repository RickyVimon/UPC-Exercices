#include "ModuleIMGUI.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "IMGUI/imgui.h"
#include "IMGUI/examples/imgui_impl_opengl3.h"
#include "IMGUI/examples/imgui_impl_sdl.h"
#include "ModuleCamera.h"
#include "ModuleInput.h"
#include "ModuleModelLoader.h"
#include "ModuleTexture.h"
#include "Libraries/MathGeoLib/include/Math/MathAll.h"

#if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
#include <GL/gl3w.h>    // Initialize with gl3wInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
#include <GL/glew.h>    // Initialize with glewInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
#include <glad/glad.h>  // Initialize with gladLoadGL()
#else
#include IMGUI_IMPL_OPENGL_LOADER_CUSTOM
#endif


ModuleIMGUI::ModuleIMGUI()
{

}


ModuleIMGUI::~ModuleIMGUI()
{
}

bool ModuleIMGUI::Init() 
{
	const char* glsl_version = "#version 130";
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();

	ImGui::CreateContext();

	ImGuiIO& io = ImGui::GetIO(); (void)io;

	ImGui::StyleColorsDark();
	ImGui_ImplSDL2_InitForOpenGL(App->window->window, App->renderer->context);
	ImGui_ImplOpenGL3_Init(glsl_version);
	//show_demo_window = true;
	console_window = true;
	configuration_window = true;
	propierties_window = true;

	bool show_another_window = false;


	return true;

}
update_status ModuleIMGUI::PreUpdate()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame(App->window->window);
	ImGui::NewFrame();
	return UPDATE_CONTINUE;
}

// Called every draw update
update_status ModuleIMGUI::Update()
{
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("About"))
		{
			if (ImGui::MenuItem("Author"))
				LOG("Ricard Vivó Montero");
			if (ImGui::MenuItem("License"))
				LOG("Whatever");
			if (ImGui::MenuItem("Engine"))
				LOG("AWACHINDOWN IN DA STRIT");
			ImGui::EndMenu();
		};
		if (ImGui::BeginMenu("Tools"))
		{
			if (ImGui::MenuItem("Fps graphs"))
				fps_window = true;
			if (ImGui::MenuItem("License"))
				LOG("Whatever");
			if (ImGui::MenuItem("Engine"))
				LOG("AWACHINDOWN IN DA STRIT");
			ImGui::EndMenu();

		};
		ImGui::EndMainMenuBar();
	}

	if (configuration_window)
	{
		ImGui::Begin("Configuration", &configuration_window);
		//App camera draw editor
		if (ImGui::CollapsingHeader("Camera")) {
		
			App->camera->SetImgui();

		}
		if (ImGui::CollapsingHeader("Hardware")) {

			char tmp_string[4096];

			ImGui::Text("CPUs:");
			ImGui::SameLine();
			int num_cpus = SDL_GetCPUCount();
			int cpu_cache_line_size = SDL_GetCPUCacheLineSize();
			sprintf_s(tmp_string, "%d (Cache: %d bytes)", num_cpus, cpu_cache_line_size);
			ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), tmp_string);

			ImGui::Text("System RAM:");
			ImGui::SameLine();
			float system_ram = SDL_GetSystemRAM() / 1000.f;
			sprintf_s(tmp_string, "%.2f GB", system_ram);
			ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), tmp_string);

			ImGui::Separator();

			ImGui::Text("GPU:");
			ImGui::SameLine();
			sprintf_s(tmp_string, "%s %s", glGetString(GL_VENDOR), glGetString(GL_RENDERER));
			ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), tmp_string);

			int vram_budget, vram_available;
			glGetIntegerv(GL_GPU_MEMORY_INFO_TOTAL_AVAILABLE_MEMORY_NVX, &vram_budget);
			glGetIntegerv(GL_GPU_MEMORY_INFO_CURRENT_AVAILABLE_VIDMEM_NVX, &vram_available);

			ImGui::Text("VRAM Budget:");
			ImGui::SameLine();
			sprintf_s(tmp_string, "%.2f MB", vram_budget / 1000.f);
			ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), tmp_string);

			ImGui::Text("VRAM Usage:");
			ImGui::SameLine();
			sprintf_s(tmp_string, "%.2f MB", (vram_budget - vram_available) / 1000.f);
			ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), tmp_string);

			ImGui::Text("VRAM Available:");
			ImGui::SameLine();
			sprintf_s(tmp_string, "%.2f MB", vram_available / 1000.f);
			ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), tmp_string);
			fps_log.push_back(ImGui::GetIO().Framerate);
			if (fps_log.size() > 50) {
				char title[50];
				sprintf_s(title, 25, "Framerate %.1f", fps_log[fps_log.size() - 1]);
				ImGui::PlotHistogram("##framerate", &fps_log[0], fps_log.size(), 0, title, 0.0f, 100.0f, ImVec2(310, 100));
				fps_log.erase(fps_log.begin());
			}

		}
		if (ImGui::CollapsingHeader("Software Versions"))
		{

			ImGui::Text("Using Glew %s", glewGetString(GLEW_VERSION)); // Should be 2.0
			ImGui::Text("OpenGL version supported %s", glGetString(GL_VERSION));
			ImGui::Text("GLSL: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
			ImGui::Text("DevIL 1.8");
			ImGui::Text("Assimp 5.0");
			ImGui::Text("Assimp ImGui 1.73");
			
		}
		if (ImGui::CollapsingHeader("Input"))
		{

			App->input->SetImgui();

		}
		ImGui::End();
	}

	if (fps_window) {
		ImGui::Begin("FPS Window", &fps_window);
		fps_log.push_back(ImGui::GetIO().Framerate);
		if (fps_log.size() > 50) {
			char title[50];
			sprintf_s(title, 25, "Framerate %.1f", fps_log[fps_log.size() - 1]);
			ImGui::PlotHistogram("##framerate", &fps_log[0], fps_log.size(), 0, title, 0.0f, 100.0f, ImVec2(310, 100));
			fps_log.erase(fps_log.begin());
		}
		//fps_log.pop_back();
		ImGui::End();
	}

	if (console_window) {
		ImGui::Begin("LOG console", &console_window);
		
		if (ImGui::CollapsingHeader("About")) {
			
			ImGui::Text("Author: Ricard Vivó Montero");
			ImGui::BulletText("GitHub: RickyVimon");

		}

		ImGui::Text("Custom Log Window. (%s)", IMGUI_VERSION);
		ImGui::Spacing();

		char title[25] = "Application";
		//sprintf_s(titile, 25, "Framerate %.1f", 1000.0f/ImGui::GetIO().Framerate,	)
		ImGui::TextUnformatted(Buf.begin()); 
		if (ScrollToBottom)
			ImGui::SetScrollHere(1.0f);
		ScrollToBottom = false;
		ImGui::End();
	}

	if (propierties_window = true) {
		ImGui::Begin("Propierties", &propierties_window);
		if (ImGui::CollapsingHeader("Transform")) 
		{
			float3 translation = float3::zero;
			float3 rotation = float3::zero;
			float3 scale = float3::one;

			ImGui::DragFloat3("Translation", &translation[0], NULL, NULL, NULL);
			ImGui::DragFloat3("Rotation", &rotation[0], NULL, NULL, NULL);
			ImGui::DragFloat3("Scale", &scale[0], NULL, NULL, NULL);

		}
		if (ImGui::CollapsingHeader("Geometry")) 
		{
			App->moduleloader->SetImgui();
		}
		if (ImGui::CollapsingHeader("Textures")) 
		{
			App->moduleloader->SetImguiTextures();
			//App->texture->SetImgui();
		}
		ImGui::End();
	}
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	return UPDATE_CONTINUE;
}

update_status ModuleIMGUI::PostUpdate()
{

	return UPDATE_CONTINUE;
}

bool ModuleIMGUI::CleanUp() {
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
	return true;
}




