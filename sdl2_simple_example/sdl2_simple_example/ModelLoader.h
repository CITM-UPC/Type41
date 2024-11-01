#ifndef MODELLOADER_H
#define MODELLOADER_H

#include <string>
#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

struct Vertex {
    float x, y, z;    // Posición
    float nx, ny, nz; // Normales
    float u, v;       // Coordenadas UV
};

class ModelLoader {
public:
    ModelLoader();
    ~ModelLoader();
    bool loadModel(const std::string& path);
    void createCube(float size);
    void createSphere(float radius, int segments, int rings);
    void drawModel();
    const aiScene* getScene() const;

private:
    void drawNode(aiNode* node, const aiScene* scene);
    void drawPrimitive();

    Assimp::Importer importer;
    const aiScene* scene;
    std::vector<Vertex> primitiveVertices;
};

#endif // MODELLOADER_H