#pragma once

#include <sstream>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "mesh/Mesh.h"
#include "mesh/Texture.h"

#include "random/RGEN.h"

class Model
{
public:
    Model(char *path) {}
    ~Model() {}
    void render();
    void clear();

private:
    DetailedArray<Mesh *> mMeshes;
    DetailedArray<Texture *> mTextures;
    DetailedArray<unsigned int> mMeshToTexture;
    std::string directory;

    unsigned int meshItr = 0;

    void loadModel(std::string path);
    void processNode(aiNode *node, const aiScene *scene);
    // heap allocated. might cause memmory leaks
    Mesh *processMesh(aiMesh *mesh, const aiScene *scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
};