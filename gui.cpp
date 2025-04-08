#include "imgui.h"

void renderUI() {
    static int tamano = 0;
    static float factor = 1.0f;
    static int modo = 0; // 0 = Arreglo, 1 = Matriz
    static bool calcular = false;

    // Campo de texto para tamaño
    ImGui::TextColored(ImVec4(0.4f, 0.4f, 1.0f, 1.0f), "tamaño");
    ImGui::SameLine();
    ImGui::InputInt("##Tamano", &tamano);

    // Campo para factor de crecimiento
    ImGui::TextColored(ImVec4(0.4f, 0.4f, 1.0f, 1.0f), "Factor de crecimiento");
    ImGui::SameLine();
    ImGui::InputFloat("##Factor", &factor);

    // Botón para calcular
    if (ImGui::Button("CALCULAR", ImVec2(120, 30))) {
        calcular = true;
        // Aquí llamas la lógica de cálculo
    }

    // Selector tipo arreglo o matriz
    ImGui::RadioButton("Arreglo", &modo, 0); ImGui::SameLine();
    ImGui::RadioButton("Matriz", &modo, 1);

    // Tabla de resultados
    if (ImGui::BeginTable("Resultados", 4, ImGuiTableFlags_Borders)) {
        ImGui::TableSetupColumn("");
        ImGui::TableSetupColumn("Tiempo de ejecución");
        ImGui::TableSetupColumn("Iteraciones");
        ImGui::TableSetupColumn("Comparaciones");
        ImGui::TableHeadersRow();

        const char* algoritmos[] = {"Burbuja", "Inserción", "Mezcla", "Selección", "Quick"};
        for (int i = 0; i < 5; i++) {
            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0); ImGui::Text("%s", algoritmos[i]);
            ImGui::TableSetColumnIndex(1); ImGui::Text("0.000s");   // Aquí va el tiempo real
            ImGui::TableSetColumnIndex(2); ImGui::Text("0");        // Iteraciones
            ImGui::TableSetColumnIndex(3); ImGui::Text("0");        // Comparaciones
        }

        ImGui::EndTable();
    }
}
