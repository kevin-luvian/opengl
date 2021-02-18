#pragma once

#include <unordered_map>
#include "TextureLookup.h"
#include "Texture.h"

class TextureManager
{
private:
    TextureManager() {}
    ~TextureManager() {}

    std::unordered_map<std::string, TextureLookup> tlLookup;

    TextureLookup *find(std::string path)
    {
        std::unordered_map<std::string, TextureLookup>::iterator it;
        it = tlLookup.find(path);
        if (it != tlLookup.end())
            return &it->second;
        return nullptr;
    }
    TextureLookup *createImpl(const std::string &path)
    {
        TextureLookup *tl = find(path);
        if (tl != nullptr)
        {
            tl->incrementReference();
            return tl;
        }
        tlLookup.insert(std::make_pair(path, TextureLookup()));
        return find(path);
    }
    void removeImpl(const std::string &path)
    {
        std::unordered_map<std::string, TextureLookup>::iterator it;
        it = tlLookup.find(path);
        if (it != tlLookup.end() && it->second.decrementReference())
            tlLookup.erase(it);
    }
    static TextureManager *GET()
    {
        static TextureManager instance;
        return &instance;
    }

public:
    static TextureLookup *Create(const std::string &path) { return GET()->createImpl(path); }
    static void Remove(const std::string &path) { GET()->removeImpl(path); }
};