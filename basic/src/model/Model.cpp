#include "Model.h"

void Model::loadModel(std::string path)
{
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals | aiProcess_JoinIdenticalVertices);
    if (!scene)
    {
        throw std::runtime_error("Model from " + path + " failed to load, " + importer.GetErrorString());
    }
    directory = path.substr(0, path.find_last_of('/'));
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

    // std::vector<Texture> textures;
    // unsigned int randNum = RGEN::Uint(0, 100);
    // std::cout << "tex size [" << randNum << "]: " << scene->mNumMaterials << "\n";
    // if (mesh->mMaterialIndex >= 0)
    // {
    //     aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
    //     std::vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
    //     textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
    //     std::vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
    //     textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    // }
    // mMesh->textures.make_from(textures);
    // std::cout << "tex size [" << randNum << "]: " << mMesh->textures.size << "\n";

    if (mesh->mMaterialIndex >= 0)
    {
        aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
        aiString path;
        material->GetTexture(aiTextureType_DIFFUSE, 0, &path);
        std::stringstream filepath;
        filepath << directory << "/" << path.C_Str();

        Texture texture;
        texture.loadFromFile(filepath.str());
        texture.path = path.C_Str();

        mMesh->stex = texture;
    }

    return mMesh;
}
std::vector<Texture> Model::loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName)
{
    unsigned int size = mat->GetTextureCount(type);
    std::vector<Texture> textures(size);
    for (unsigned int i = 0; i < size; i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);
        std::stringstream filepath;
        filepath << directory << "/" << str.C_Str();

        Texture texture;
        texture.loadFromFile(filepath.str());
        texture.type = typeName;
        texture.path = str.C_Str();
        textures.push_back(texture);
    }
    return textures;
}