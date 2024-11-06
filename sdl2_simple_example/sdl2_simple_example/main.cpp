#include <GL/glew.h>
#include <iostream>
#include <GL/gl.h>
#include <chrono>
#include <thread>
#include <exception>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> 
#include <SDL2/SDL_events.h>
#include <memory>
#include "MyWindow.h"
#include "imgui_impl_sdl2.h"
#include "WindowEditor.h"
#include "ModelLoader.h"
#include "Material.h"
#include "GameObject.h"
#include "Camera.h" 

using namespace std;

using hrclock = chrono::high_resolution_clock;
using u8vec4 = glm::u8vec4;
using ivec2 = glm::ivec2;
using vec3 = glm::dvec3;

static const ivec2 WINDOW_SIZE(1600, 900);
static const unsigned int FPS = 60;
static const auto FRAME_DT = 1.0s / FPS;

static void init_openGL() {
    glewInit();
    if (!GLEW_VERSION_3_0) throw exception("OpenGL 3.0 API is not available");
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.5, 0.5, 0.5, 1.0);
}

static bool processEvents(Camera& camera, float deltaTime) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            return false;
            break;
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_f) {
                camera.resetFocus(glm::vec3(0.0f));
            }
            else if (event.key.keysym.sym == SDLK_LSHIFT || event.key.keysym.sym == SDLK_RSHIFT) {
                camera.enableFPSMode(true);
            }
            else {
                camera.processKeyboard(event.key.keysym.sym, deltaTime);
            }
            break;
        case SDL_KEYUP:
            if (event.key.keysym.sym == SDLK_LSHIFT || event.key.keysym.sym == SDLK_RSHIFT) {
                camera.enableFPSMode(false);
            }
            break;
        case SDL_MOUSEMOTION:
            if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_RIGHT)) {
                camera.processMouseMovement(event.motion.xrel, -event.motion.yrel);
            }
            else if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_MIDDLE)) {
                camera.processMousePan(event.motion.xrel, event.motion.yrel); // Movimiento 2D al pulsar la rueda
            }
            break;
        case SDL_MOUSEWHEEL:
            camera.processMouseScroll(event.wheel.y); // Zoom con la rueda del rat�n
            break;
        default:
            ImGui_ImplSDL2_ProcessEvent(&event);
        }
    }
    return true;
}

int main(int argc, char** argv) {
    MyWindow window("SDL2 Simple Example", WINDOW_SIZE.x, WINDOW_SIZE.y);
    init_openGL();

    std::vector<std::unique_ptr<GameObject>> gameObjects;
    auto gameObject1 = std::make_unique<GameObject>();
    gameObject1->loadModel("BakerHouse.fbx");

    Material material;
    material.loadTexture("Baker_house.png");
    gameObject1->setMaterial(material);
    gameObjects.push_back(std::move(gameObject1));

    // gameObject1->setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
    // gameObject1->setScale(glm::vec3(0.01f, 0.01f, 0.01f));
    // gameObject1->setRotation(glm::vec3(0.0f, 0.0f, 180.0f));

    // auto gameObject2 = std::make_unique<GameObject>();
    // gameObject2->loadModel("masterchief.fbx");
    // gameObjects.push_back(std::move(gameObject2));

    // A�ade m�s GameObjects seg�n sea necesario
    // auto gameObjectN = std::make_unique<GameObject>();
    // gameObjectN->loadModel("otro_modelo.fbx");
    // gameObjects.push_back(std::move(gameObjectN));

    WindowEditor editor;

    Camera camera;
    float deltaTime = 0.0f;
    auto lastFrame = hrclock::now();


    while (processEvents(camera, deltaTime)) {
        const auto t0 = hrclock::now();
        deltaTime = chrono::duration<float>(t0 - lastFrame).count();
        lastFrame = t0;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Configuraci�n de la matriz de proyecci�n para el zoom
        glMatrixMode(GL_PROJECTION);
        glm::mat4 projection = camera.getProjectionMatrix(static_cast<float>(WINDOW_SIZE.x) / WINDOW_SIZE.y);
        glLoadMatrixf(&projection[0][0]);
        glMatrixMode(GL_MODELVIEW);

        // Configuraci�n de la vista de la c�mara
        glm::mat4 view = camera.getViewMatrix();
        glLoadMatrixf(&view[0][0]);

        // Dibujar los objetos
        for (auto& gameObject : gameObjects) {
            gameObject->draw();
        }

        // Renderizar el editor
        editor.Render();

        window.swapBuffers();

        const auto t1 = hrclock::now();
        const auto dt = t1 - t0;
        if (dt < FRAME_DT) this_thread::sleep_for(FRAME_DT - dt);
    }

    return 0;
}
