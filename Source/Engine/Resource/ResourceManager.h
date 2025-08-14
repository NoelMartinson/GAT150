#pragma once  
#include "Core/StringHelper.h"  
#include "Core/Singleton.h"
#include "Core/Logger.h"
#include "Resource.h"  

#include <string>  
#include <map>  
#include <iostream>  

namespace fox {
    class ResourceManager : public Singleton<ResourceManager> {
    public:
        void Clear() {resources.clear();}

        template<typename T, typename ... Args>
        res_t<T> Get(const std::string& name, Args&& ... args);

        template<typename T, typename ... Args>
        res_t<T> GetWithID(const std::string& id, const std::string& name, Args&& ... args);
             
    private:
		friend class Singleton<ResourceManager>;
        std::map<std::string, res_t<Resource>> resources;
    private:
        ResourceManager() = default;
    };

    template<typename T, typename ... Args>
    inline res_t<T> ResourceManager::Get(const std::string& name, Args&& ...args)
    {
		return GetWithID<T>(name, name, std::forward<Args>(args)...);
    }

    template<typename T, typename ...Args>
    inline res_t<T> ResourceManager::GetWithID(const std::string& id, const std::string& name, Args && ...args)
    {
        std::string key = tolower(id);

        auto iter = resources.find(key);
        if (iter != resources.end()) {
            auto base = iter->second;
            auto resource = std::dynamic_pointer_cast<T>(base);
            if (resource == nullptr) {
                Logger::Error("Resource type mismatch: {} is not of type {}", key, typeid(T).name());
                return res_t<T>();
            }
            return resource;
        }

        //load resource
        res_t<T> resource = std::make_shared<T>();
        if (resource->Load(name, std::forward<Args>(args)...) == false) {
            Logger::Error("Failed to load resource:", SDL_GetError());
            return res_t<T>();
        }

        //add resource to the manager
        resources[name] = resource;

        return resource;
    }

    inline ResourceManager& Resources() {return ResourceManager::Instance();}
}