#include "ConfigPanel.h"
ConfigPanel::ConfigPanel() {}
ConfigPanel::~ConfigPanel() {}

void ConfigPanel::Render() {
    ImGui::Begin("Configuraci�n");
    // L�gica de renderizado del log de consola
    ImGui::End();
}

void ConfigPanel::Log(const char* message) {
    // Implementaci�n para registrar un mensaje
}
