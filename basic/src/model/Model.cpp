#include "Model.h"

void Model::loadModel(std::string path)
{
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals | aiProcess_JoinIdenticalVertices);
    if (!scene)
    {
        throw std::runtime_error("Model from " + path + " failed to load, " + importer.GetErrorString());
    }
    mMeshes.make_empty(scene->mNumMeshes);
    processNode(scene->mRootNode, scene);
}
void Model::processNode(aiNode *node, const aiScene *scene)
{
    for (size_t i = 0; i < node->mNumMeshes; i++)
    {
        mMeshes[meshItr++] = processMesh(scene->mMeshes[node->mMeshes[i]], scene);
    }
    for (size_t i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }
}
Mesh *Model::processMesh(aiMesh *mesh, const aiScene *scene)
{
    Mesh *mMesh = new Mesh();

    mMesh->vertices.make_empty(mesh->mNumVertices);
    for (size_t i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
        vertex.pos = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
        vertex.normal = glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
        if (mesh->mTextureCoords[0])
        {
            vertex.texCoord = glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
        }
        if (mesh->mColors[0])
        {
            vertex.colour = glm::vec4(mesh->mColors[0][i].r,
                                      mesh->mColors[0][i].g,
                                      mesh->mColors[0][i].b,
                                      mesh->mColors[0][i].a);
        }
        mMesh->vertices[i] = vertex;
    }

    mMesh->indices.make_empty(mesh->mNumFaces);
    for (size_t i = 0; i < mesh->mNumFaces; i++)
    {
        // potentially might break; probably not.
        if (mesh->mFaces[i].mNumIndices == 3)
        {
            Indice indice;
            indice.left = mesh->mFaces[i].mIndices[0];
            indice.right = mesh->mFaces[i].mIndices[1];
            indice.top = mesh->mFaces[i].mIndices[2];
            mMesh->indices[i] = indice;
        }
    }

    return mMesh;
}
// vector<Texture> loadMaterialTextures(aiMaterial *mat,
//                                      aiTextureType type,
//                                      std::string typeName);