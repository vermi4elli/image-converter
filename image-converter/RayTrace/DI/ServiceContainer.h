#pragma once
#include <map>
#include "SimpleContainer.h"

class ServiceContainer
{
public:

    template <typename T, typename... Args>
    void set(Args... args)
    {
        auto instance = std::make_unique<T>(args...);
        std::unique_ptr<SimpleContainer<T>> service = std::make_unique<SimpleContainer<T>>(std::move(instance));
        mContainer[typeId<T>()] = std::move(service);
    }

    template <typename T>
    T* get()
    {
        auto it = mContainer.find(typeId<T>());
        if (it == mContainer.end()) {
            std::cout << "Container empty";
            exit(0);
        }

        return static_cast<T*>(it->second->get());
    }

private:
    template <typename T>
    int typeId()
    {
        static int id = ++mLastTypeId;

        return id;
    }

private:
    int mLastTypeId = 0;
    std::map<int, std::unique_ptr<IContainer>> mContainer;
};
