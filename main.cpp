#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <GLFW/glfw3.h> // ¡Incluye GLFW después de las definiciones de OpenGL!
#include <iostream>

// ========================
// Función para dibujar UI
// ========================
void renderUI() {
    ImGui::Begin("Simulación");

    // Campo tamaño
    static int tamano = 0;
    ImGui::Text("tamaño");
    ImGui::SameLine(150);
    ImGui::InputInt("##tamano", &tamano);

    // Campo factor de crecimiento
    static float factor = 1.0f;
    ImGui::Text("Factor de crecimiento");
    ImGui::SameLine(250);
    ImGui::InputFloat("##factor", &factor);

    // Botón calcular
    if (ImGui::Button("CALCULAR", ImVec2(150, 30))) {
        // lógica para calcular
        std::cout << "CALCULAR presionado: tamaño = " << tamano << ", factor = " << factor << "\n";
    }

    // Selector Arreglo o Matriz
    static int tipo = 0;
    ImGui::RadioButton("Arreglo", &tipo, 0); ImGui::SameLine();
    ImGui::RadioButton("Matriz", &tipo, 1);

    // Tabla
    if (ImGui::BeginTable("resultados", 4, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg)) {
        ImGui::TableSetupColumn(" ");
        ImGui::TableSetupColumn("Tiempo de ejecución");
        ImGui::TableSetupColumn("Iteraciones");
        ImGui::TableSetupColumn("Comparaciones");
        ImGui::TableHeadersRow();

        const char* algoritmos[] = {"Burbuja", "Inserción", "Mezcla", "Selección", "Quick"};
        for (int i = 0; i < 5; ++i) {
            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0); ImGui::Text("%s", algoritmos[i]);
            ImGui::TableSetColumnIndex(1); ImGui::Text("0.00 ms"); // Dummy data
            ImGui::TableSetColumnIndex(2); ImGui::Text("0");
            ImGui::TableSetColumnIndex(3); ImGui::Text("0");
        }

        ImGui::EndTable();
    }

    ImGui::End();
}

// ========================
// MAIN
// ========================
int main() {
    // Inicializar GLFW
    if (!glfwInit()) {
        std::cerr << "Error al inicializar GLFW\n";
        return -1;
    }

    // Crear ventana GLFW
    GLFWwindow* window = glfwCreateWindow(800, 600, "Simulación", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        std::cerr << "Error al crear ventana\n";
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // vsync

    // Inicializar ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();

    // Inicializar backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    // Loop principal
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        renderUI(); // Mostrar interfaz

        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    // Limpieza
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
