#pragma once
#include "imgui.h"

class HierarchyPanel {
public:
    HierarchyPanel();
    ~HierarchyPanel();

    void Render(); // Renderiza el log de consola
    void Log(const char* message); // M�todo para registrar mensajes en consola

private:
    // Estructuras necesarias para el log
};
