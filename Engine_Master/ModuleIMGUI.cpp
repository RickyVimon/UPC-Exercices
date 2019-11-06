#include "ModuleIMGUI.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "IMGUI/imgui.h"
#include "IMGUI/examples/imgui_impl_opengl3.h"
#include "IMGUI/examples/imgui_impl_sdl.h"
#include "ModuleCamera.h"
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
	show_demo_window = true;
	console_window = true;

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


	if (fps_window) {
		ImGui::Begin("FPS Window", &fps_window);
		fps_log.push_back(ImGui::GetIO().Framerate);
		if (fps_log.size() > 50) {
			char title[50];
			sprintf_s(title, 25, "Framerate %.1f", fps_log[fps_log.size() - 1]);
			ImGui::PlotHistogram("##framerate", &fps_log[0], fps_log.size(), 0, title, 0.0f, 100.0f, ImVec2(310, 100));
			fps_log.pop_back();
		}
		//fps_log.pop_back();
		ImGui::End();
	}

	if (console_window) {
		ImGui::Begin("LOG console", &console_window);
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
		if (ImGui::CollapsingHeader("About")) {
			
			ImGui::Text("Author: Ricard Vivó Montero");
			ImGui::BulletText("GitHub: RickyVimon");

		}

		//App camera draw editor
		if (ImGui::CollapsingHeader("Camera")) {

			if (ImGui::Checkbox("Ground", &App->camera->flag_ground)) {

			}
			if (ImGui::Checkbox("Axis", &App->camera->flag_axis)) {

			}
			float fov = App->camera->frustum.verticalFov;
			if (ImGui::SliderFloat("Vertical FOV", &fov , 0.01, math::pi, "%.3f", 1.0f))
			{
				App->camera->SetFOV(fov);
			}

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




