#include "InspectorPanel.h"
InspectorPanel::InspectorPanel() {}
InspectorPanel::~InspectorPanel() {}

void InspectorPanel::Render() {
    ImGui::Begin("Inspector");
    // L�gica de renderizado del log de consola
    ImGui::End();
}

void InspectorPanel::Log(const char* message) {
    // Implementaci�n para registrar un mensaje
}
