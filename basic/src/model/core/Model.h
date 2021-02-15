#pragma once

#include <sstream>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "draw/entity/Movable.h"
#include "draw/shader/core/GLSLInterface.h"
#include "draw/shader/core/ShaderType.h"
#include "mesh/core/Texture.h"
#include "ModelObject.h"

class Model : public Movable
{
public:
    Model(const std::string &path) : filepath(path) {}
    ~Model() { clear(); }

    void clear()
    {
        for (size_t i = 0; i < mObjects.size; i++)
        {
            mObjects[i].release();
        }
        mObjects.release();
        filepath.clear();
        directory.clear();
    }

    void create();
    void update();
    void render(Shader *shader);
    static ShaderType getShaderType() { return ShaderType::Textured; }

private:
    Array<ModelObject> mObjects;
    std::string filepath;
    std::string directory;

    void loadModel(const std::string &path);
    void processNode(aiNode *node, const aiScene *scene);
    // heap allocated. might cause memmory leaks
    ModelObject processMesh(aiMesh *mesh, const aiScene *scene);
    Texture loadTexture(aiMaterial *mat, aiTextureType type, std::string typeName);
    std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
};

void Model::create()
{
    loadModel(filepath);
    for (size_t i = 0; i < mObjects.size; i++)
    {
        mObjects[i].create();
    }
    update();
    std::cout << "model [obj count: " << mObjects.size << "] created\n";
}

void Model::update() { move(); }

void Model::render(Shader *shader)
{
    shader->setMat4(GLSLI::VMODEL, model);
    for (size_t i = 0; i < mObjects.size; i++)
    {
        mObjects[i].render();
    }
}

void Model::loadModel(const std::string &path)
{
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals | aiProcess_JoinIdenticalVertices);
    if (!scene)
        throw std::runtime_error("Model from :" + path + " failed to load, " + importer.GetErrorString());
    directory = path.substr(0, path.find_last_of('/'));
    // std::cout << "path: " << path.c_str() << ", dir: " << directory.c_str() << "\n";
    processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode *node, const aiScene *scene)
{
    Array<ModelObject> objects(scene->mNumMeshes);
    // mObjects.make_empty(scene->mNumMeshes);
    for (size_t i = 0; i < node->mNumMeshes; i++)
    {
        objects[i] = processMesh(scene->mMeshes[node->mMeshes[i]], scene);
    }
    mObjects.append(objects);
    for (size_t i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }
}

ModelObject Model::processMesh(aiMesh *mesh, const aiScene *scene)
{
    ModelObject mObj;
    Vertex vertex;
    mObj.vertices.make_empty(mesh->mNumVertices);
    for (size_t i = 0; i < mesh->mNumVertices; i++)
    {
        vertex.pos = unit::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);

        if (mesh->mNormals)
            vertex.normal = unit::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);

        if (mesh->mTextureCoords[0])
            vertex.texCoord = unit::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);

        if (mesh->mColors[0])
            vertex.color = unit::color(mesh->mColors[0][i].r,
                                       mesh->mColors[0][i].g,
                                       mesh->mColors[0][i].b,
                                       mesh->mColors[0][i].a);
        else
            vertex.color = Colors::OCEAN;
        mObj.vertices[i] = vertex;
        // if (i == 0)
        //     std::cout << "Vertex::" << vertex << "\n";
    }

    Indice indice;
    mObj.indices.make_empty(mesh->mNumFaces);
    for (size_t i = 0; i < mesh->mNumFaces; i++)
    {
        // potentially might break; probably not.
        if (mesh->mFaces[i].mNumIndices == 3)
        {
            indice.left = mesh->mFaces[i].mIndices[0];
            indice.right = mesh->mFaces[i].mIndices[1];
            indice.top = mesh->mFaces[i].mIndices[2];
            mObj.indices[i] = indice;
        }
    }
    if (mesh->mMaterialIndex >= 0)
    {
        aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
        mObj.texture = loadTexture(material, aiTextureType_DIFFUSE, "texture_diffuse");
    }

    return mObj;
}

Texture Model::loadTexture(aiMaterial *mat, aiTextureType type, std::string typeName)
{
    Texture tex;
    unsigned int count = mat->GetTextureCount(type);
    if (count >= 0)
    {
        aiString path;
        if (mat->GetTexture(type, 0, &path) == aiReturn_SUCCESS)
        {
            std::string filepath = directory + "/" + path.data;
            tex = TextureFactory::FromFile(filepath);
            tex.type = typeName;
        }
        else
        {
            tex = TextureFactory::Empty(Colors::OCEAN);
        }
        std::cout << "Texture path: " << path.C_Str() << "\n";
    }
    return tex;
}

std::vector<Texture> Model::loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName)
{
    unsigned int size = mat->GetTextureCount(type);
    std::vector<Texture> textures(size);
    Texture texture;
    for (unsigned int i = 0; i < size; i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);
        std::stringstream filepath;
        filepath << directory << "/" << str.C_Str();

        texture = TextureFactory::FromFile(filepath.str());
        texture.type = typeName;
        textures.push_back(texture);
    }
    return textures;
}