#pragma once

#ifdef ANDROID

#include <jni/Jni.hpp>

namespace jni
{

class Core
{
private:
    Core(JavaVM* vm, JNIEnv* env) : vm(vm), env(env) {}

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
    static Core attachCurrentThread();

    [[nodiscard]] JNIEnv* getEnv()
    {
        return env;
    }

private:
    JavaVM* vm = nullptr;
    JNIEnv* env = nullptr;
};

}

#endif
