#include "HierarchyPanel.h"

HierarchyPanel::HierarchyPanel() : selectedGameObject(nullptr) {}
HierarchyPanel::~HierarchyPanel() {}

void HierarchyPanel::Render(const std::vector<std::unique_ptr<GameObject>>& gameObjects) {
    ImGui::Begin("Hierarchy");

    // Iterar sobre todos los GameObjects y mostrar sus nombres como elementos seleccionables
    for (const auto& gameObject : gameObjects) {
        // Obt�n el nombre del GameObject
        const std::string& name = gameObject->getName();

        // Crear un identificador �nico que combine el nombre y la direcci�n de memoria del objeto
        std::string uniqueID = name + "_" + std::to_string(reinterpret_cast<std::uintptr_t>(gameObject.get()));

        // Verifica si el objeto actual es el seleccionado
        bool isSelected = (gameObject.get() == selectedGameObject);

        // Crea el selectable usando el identificador �nico
        if (ImGui::Selectable(uniqueID.c_str(), isSelected)) {
            selectedGameObject = gameObject.get();  // Actualiza la selecci�n
        }

        // Si el GameObject est� seleccionado, se marcar� con un cuadro alrededor del nombre
        if (isSelected) {
            ImGui::SetItemDefaultFocus();  // Establece el foco por defecto al seleccionar un elemento
        }
    }

    ImGui::End();

    // Mostrar detalles del GameObject seleccionado en un panel de "Inspector"
    if (selectedGameObject) {
        ImGui::Begin("Inspector");

        // Mostrar posici�n con controles interactivos
        glm::vec3 position = selectedGameObject->getPosition();
        if (ImGui::DragFloat3("Position", &position.x, 0.1f)) {
            selectedGameObject->setPosition(position);
        }

        // Mostrar rotaci�n con controles interactivos
        glm::vec3 rotation = selectedGameObject->getRotation();
        if (ImGui::DragFloat3("Rotation", &rotation.x, 0.1f)) {
            selectedGameObject->setRotation(rotation);
        }

        // Mostrar escala con controles interactivos
        glm::vec3 scale = selectedGameObject->getScale();
        if (ImGui::DragFloat3("Scale", &scale.x, 0.1f)) {
            selectedGameObject->setScale(scale);
        }

        ImGui::End();
    }
}
