#include "ConsolePanel.h"
ConsolePanel::ConsolePanel() {}
ConsolePanel::~ConsolePanel() {}

void ConsolePanel::Render() {
    ImGui::Begin("Consola");
    // L�gica de renderizado del log de consola
    ImGui::End();
}

void ConsolePanel::Log(const char* message) {
    // Implementaci�n para registrar un mensaje
}
