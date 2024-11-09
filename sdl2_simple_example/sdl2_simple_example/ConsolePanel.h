// ConsolePanel.h
#ifndef CONSOLE_PANEL_H
#define CONSOLE_PANEL_H

#include <vector>
#include <string>
#include "imgui.h"  // Aseg�rate de incluir ImGui para los m�todos gr�ficos

// Enum para los diferentes tipos de log
enum LogType {
    INFO,
    WARNING,
    ERROR
};

class ConsolePanel {
public:
    ConsolePanel();  // Constructor
    ~ConsolePanel();  // Destructor

    // M�todo para renderizar el panel
    void Render();

    // M�todo para registrar un mensaje en el log
    void Log(const char* message, LogType type = INFO);

private:
    std::vector<std::string> messages;  // Contenedor de mensajes
};

#endif  // CONSOLE_PANEL_H
