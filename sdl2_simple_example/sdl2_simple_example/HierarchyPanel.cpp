#include "HierarchyPanel.h"

HierarchyPanel::HierarchyPanel() {}
HierarchyPanel::~HierarchyPanel() {}

void HierarchyPanel::Render(const std::vector<std::unique_ptr<GameObject>>& gameObjects) {
    ImGui::Begin("Hierarchy");
    for (const auto& gameObject : gameObjects) {
        // Puedes mostrar informaci�n de cada objeto, como su posici�n.
        auto position = gameObject->getPosition();
        ImGui::Text("GameObject: Posici�n (%.2f, %.2f, %.2f)", position.x, position.y, position.z);
    }
    ImGui::End();
}
