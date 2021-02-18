#pragma once

#include <sstream>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "mesh/core/TextureManager.h"
#include "draw/entity/Movable.h"
#include "draw/shader/core/ShaderType.h"
#include "mesh/core/Texture.h"
#include "ModelObject.h"

class Model : public Movable
{
public:
    Model() {}
    Model(std::string path, bool flip = false) : filepath(path), flipTexture(flip)
    {
        tLookup = TextureManager::Create(path);
    }
    ~Model()
    {
        TextureManager::Remove(filepath);
    }

    void create();
    void update();
    void render(Shader *shader);
    void operator=(const Model &other)
    {
        if (this != &other) // not a self-assignment
        {
            tLookup = other.tLookup;
            mObjects = other.mObjects;
            filepath = other.filepath;
            directory = other.directory;
            flipTexture = other.flipTexture;
            tLookup->incrementReference();
        }
    }

    static const ShaderType SHADER_TYPE;

private:
    TextureLookup *tLookup;
    Array<ModelObject> mObjects;
    std::string filepath; // should not change after initialization
    std::string directory;
    bool flipTexture;

    void loadModel(const std::string &path);
    void processNode(aiNode *node, const aiScene *scene);
    ModelObject processMesh(aiMesh *mesh, const aiScene *scene);
    Array<Texture> loadTextures(aiMaterial *mat, aiTextureType aiType, unsigned int texType);
};

const ShaderType Model::SHADER_TYPE = ShaderType::Light;

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
        mObjects[i].render(*shader);
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
    size_t offset = mObjects.size;
    size_t mSize = node->mNumMeshes;
    mObjects.resize(offset + mSize);
    for (size_t i = 0; i < mSize; i++)
    {
        mObjects[offset + i] = processMesh(scene->mMeshes[node->mMeshes[i]], scene);
    }
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
        vertex.pos = mesh->mVertices[i];

        if (mesh->mNormals)
            vertex.normal = mesh->mNormals[i];

        if (mesh->mTextureCoords[0])
            vertex.texCoord = unit::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);

        if (mesh->mColors[0])
            vertex.color = mesh->mColors[0][i];

        mObj.vertices[i] = vertex;
    }

    Indice indice;
    mObj.indices.make_empty(mesh->mNumFaces);
    for (size_t i = 0; i < mesh->mNumFaces; i++)
    {
        // potentially might break; probably not.
        if (mesh->mFaces[i].mNumIndices == 3)
            mObj.indices[i] = mesh->mFaces[i].mIndices;
    }
    if (mesh->mMaterialIndex >= 0)
    {
        aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
        mObj.textures.append(loadTextures(material, aiTextureType_DIFFUSE, GLSLI::Texture::DIFFUSE));
        mObj.textures.append(loadTextures(material, aiTextureType_SPECULAR, GLSLI::Texture::SPECULAR));
    }

    return mObj;
}

Array<Texture> Model::loadTextures(aiMaterial *mat, aiTextureType aiType, unsigned int texType)
{
    unsigned int size = mat->GetTextureCount(aiType);
    Array<Texture> textures(size);
    for (unsigned int i = 0; i < size; i++)
    {
        aiString path;
        if (mat->GetTexture(aiType, i, &path) == aiReturn_SUCCESS)
        {
            std::string filepath = directory + "/" + path.C_Str();
            textures[i] = tLookup->texture(filepath, texType, flipTexture);
        }
        else
            textures[i] = tLookup->empty(Colors::WHITE, texType);
    }
    // std::cout << "tex size: " << textures.size << "\n";
    return textures;
}