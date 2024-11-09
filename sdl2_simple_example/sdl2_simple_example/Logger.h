#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "ConsolePanel.h"  // Incluye la clase ConsolePanel

class Logger {
public:
    // M�todo para obtener la instancia del logger
    static Logger& GetInstance() {
        static Logger instance;  // Instancia �nica del logger
        return instance;
    }

    // M�todo para enviar un mensaje al console panel
    void Log(const std::string& message, LogType type) {
        std::cout << "Logger: Enviando mensaje: " << message << std::endl;  // Debug
        if (consolePanel) {
            std::cout << "ConsolePanel est� asignado. Enviando log..." << std::endl;  // Debug
            consolePanel->Log(message.c_str(), type);  // Pasa el mensaje a ConsolePanel
        }
        else {
            std::cout << "ConsolePanel no est� asignado" << std::endl;  // Debug
        }
    }


    // Establecer la instancia del ConsolePanel (se pasa en el WindowEditor)
    void SetConsolePanel(ConsolePanel* panel) {
        if (panel) {  // Verifica que no sea nullptr
            consolePanel = panel;
        }
        else {
            std::cerr << "Error: ConsolePanel no puede ser nullptr" << std::endl;
        }
    }

private:
    ConsolePanel* consolePanel = nullptr;  // ConsolePanel donde se mostrar�n los mensajes

    // Constructor privado para implementar el patr�n Singleton
    Logger() = default;

    // Desactivar la copia y asignaci�n
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
};
