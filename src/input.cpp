#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "input.h"

#include <iostream>
#include <string>


Input::Input(GLFWwindow* new_window) : window(new_window) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
    ImGui::GetIO().FontGlobalScale = 2.0f;

    set_input();
}

Input :: ~Input() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void Input :: set_input(){
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    ImGui::SetNextWindowSize(ImVec2(300, 100), ImGuiCond_Once);
    ImGui::Begin("Function Input");
    ImGui::Text("f(x) =");
    ImGui::SameLine();
    ImGui::InputText("##fx", input, 128);
    ImGui::End();
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

}

string Input :: get_input() {
    string str(input);
    return str;
}

