#pragma once
#include "IContainer.h"
template <class T>
class SimpleContainer : public IContainer
{
public:
    explicit SimpleContainer(std::unique_ptr<T> ptr) : IContainer(ptr.get()), mPointer(std::move(ptr)) {}
    ~SimpleContainer() override = default;

private:
    std::unique_ptr<T> mPointer;
};