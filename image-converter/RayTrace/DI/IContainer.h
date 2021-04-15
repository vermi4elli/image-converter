#pragma once
class IContainer
{
public:
    IContainer() = default;
    virtual ~IContainer() = default;

    IContainer& operator=(IContainer&& other) noexcept
    {
        mRawPointer = other.mRawPointer;
        other.mRawPointer = nullptr;

        return *this;
    }

    void* get() { return mRawPointer; }

protected:
    explicit IContainer(void* ptr) : mRawPointer(ptr) {}

private:
    void* mRawPointer = nullptr;
};