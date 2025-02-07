#pragma once
#include <vector>
#include <memory>
#include "GameObject.h"
#include "imgui.h"

class HierarchyPanel {
public:
    HierarchyPanel();
    ~HierarchyPanel();

    // Renderiza la lista de GameObjects y maneja la selecci�n
    void Render(const std::vector<std::unique_ptr<GameObject>>& gameObjects);
    GameObject* getSelectedGameObject() const { return selectedGameObject; }

private:
    GameObject* selectedGameObject;  // Puntero al GameObject actualmente seleccionado
};
