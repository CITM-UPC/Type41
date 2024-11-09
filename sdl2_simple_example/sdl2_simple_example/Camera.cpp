#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp> 

glm::mat4 Camera::getProjectionMatrix(float aspectRatio) const {
    return glm::perspective(glm::radians(zoom), aspectRatio, 0.1f, 100.0f);
}

Camera::Camera()
    : position(glm::vec3(0.0f, 0.0f, 3.0f)), front(glm::vec3(0.0f, 0.0f, -1.0f)),
    up(glm::vec3(0.0f, 1.0f, 0.0f)), worldUp(up), yaw(-90.0f), pitch(0.0f),
    movementSpeed(2.5f), mouseSensitivity(0.1f), zoom(45.0f), fpsMode(false) {
    updateCameraVectors();
}

glm::mat4 Camera::getViewMatrix() const {
    return glm::lookAt(position, position + front, up);
}

void Camera::processKeyboard(SDL_Keycode key, float deltaTime) {
    float velocity = movementSpeed * (fpsMode ? 2.0f : 1.0f) * deltaTime;
    if (key == SDLK_w) position += front * velocity;
    if (key == SDLK_s) position -= front * velocity;
    if (key == SDLK_a) position -= right * velocity;
    if (key == SDLK_d) position += right * velocity;
}

void Camera::processMouseMovement(float xoffset, float yoffset) {
    xoffset *= mouseSensitivity;
    yoffset *= mouseSensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if (pitch > 89.0f) pitch = 89.0f;
    if (pitch < -89.0f) pitch = -89.0f;

    updateCameraVectors();
}

void Camera::processMouseOrbit(float xoffset, float yoffset, const glm::vec3& targetPosition) {
    float orbitSpeed = 1.0f;

    // Modificar el �ngulo de la c�mara seg�n el movimiento del rat�n
    yaw += xoffset * orbitSpeed;
    pitch += yoffset * orbitSpeed;

    // Limitar el �ngulo de elevaci�n (pitch)
    if (pitch > 89.0f) pitch = 89.0f;
    if (pitch < -89.0f) pitch = -89.0f;

    // Calcular la nueva direcci�n de la c�mara basada en la orbita
    updateCameraVectors();

    // Posicionar la c�mara en torno al objeto seleccionado
    position = targetPosition - front * glm::length(targetPosition - position);
}


void Camera::processMouseScroll(float yoffset) {
    // Aumentamos o disminuimos la distancia de la c�mara, bas�ndonos en el movimiento de la rueda del rat�n
    float zoomSpeed = 0.1f;  // Controla qu� tan r�pido cambia la distancia
    position += front * yoffset * zoomSpeed;  // Ajustamos la posici�n de la c�mara a lo largo de la direcci�n 'front'

    // Limitar la distancia de la c�mara
    if (glm::length(position) < 1.0f) position = glm::normalize(position) * 1.0f;  // No dejar que la c�mara se acerque demasiado
    if (glm::length(position) > 80.0f) position = glm::normalize(position) * 80.0f;  // No dejar que la c�mara se aleje demasiado
}


void Camera::processMousePan(float xoffset, float yoffset) {
    float panSpeed = mouseSensitivity * 0.05f;
    position += right * -xoffset * panSpeed; // Mueve en X
    position -= up * yoffset * panSpeed;     // Mueve en Y
}

void Camera::update(float deltaTime) {}

void Camera::resetFocus(const glm::vec3& targetPosition, const glm::vec3& meshSize) {
    // Calcular la distancia de la c�mara en funci�n del tama�o de la malla
    float distance = glm::length(meshSize) * 0.2f;  // Multiplicamos por un factor para dar espacio

    // Ajustar la posici�n de la c�mara
    position = targetPosition - front * distance;

    // Actualizamos los vectores de la c�mara
    updateCameraVectors();
}

void Camera::enableFPSMode(bool enable) {
    fpsMode = enable;
}

bool Camera::isFPSModeEnabled() const {
    return fpsMode;
}

void Camera::updateCameraVectors() {
    glm::vec3 newFront;
    newFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    newFront.y = sin(glm::radians(pitch));
    newFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(newFront);

    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(right, front));
}
