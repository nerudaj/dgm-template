#pragma once

#ifdef ANDROID

namespace jni
{

class Core
{
private:
    Core(JavaVM* vm) : vm(vm) {}

public:
    Core(Core&& other) noexcept
    {
        std::swap(m_vm, other.m_vm);
    }
    Core(const Core&&) = delete;
    ~Core()
    {
        if (m_vm)
            m_vm->DetachCurrentThread();
    }

public:
    static Core attachCurrentThread(JavaVM* vm, JNIEnv** env);

private:
    JavaVM* vm = nullptr;
};

}

#endif
