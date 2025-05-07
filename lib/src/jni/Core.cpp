#ifdef ANDROID

#include <jni/Core.hpp>

jni::Core jni::Core::attachCurrentThread()
{
    auto& activity = *sf::getNativeActivity();

    JavaVMAttachArgs lJavaVMAttachArgs;
    lJavaVMAttachArgs.version = JNI_VERSION_1_6;
    lJavaVMAttachArgs.name = "NativeThread";
    lJavaVMAttachArgs.group = nullptr;

    jint lResult = activity.vm->AttachCurrentThread(
        &activity.env, &lJavaVMAttachArgs);

    if (lResult == JNI_ERR)
        throw std::runtime_error("JNI: Could not attach current thread!");

    return Core(activity.vm, activity.env);
}

#endif
