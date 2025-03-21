#include <DGM/dgm.hpp>
#include <appstate/AppStateMainMenu.hpp>
#include <misc/CMakeVars.hpp>
#include <misc/DependencyContainer.hpp>
#include <misc/Compatibility.hpp>

std::expected<tgui::Font, dgm::Error>
loadTguiFont(const std::filesystem::path& path)
{
    return tgui::Font(path.string());
}

dgm::ResourceManager
initializeResourceManager(const std::filesystem::path& rootDir)
{
    dgm::ResourceManager resmgr;

    auto myfont = dgm::Utility::loadFont("fonts/ChunkFive-Regular.ttf");
    sf::err() << "fuck" << std::filesystem::is_directory("fonts") << std::endl;
    for (auto&& itr : std::filesystem::directory_iterator("fonts"))
    {
        sf::err() << itr.path().string() << std::endl;
    }

    if (auto result = resmgr.loadResourcesFromDirectory<sf::Font>(
            rootDir  / "fonts", dgm::Utility::loadFont, { ".ttf" });
        !result)
    {
        throw std::runtime_error(uni::format(
            "Could not load font: {}", result.error().getMessage()));
    }

    if (auto result = resmgr.loadResourcesFromDirectory<tgui::Font>(
            rootDir  / "fonts", loadTguiFont, { ".ttf" });
        !result)
    {
        throw std::runtime_error(uni::format(
            "Could not load font: {}", result.error().getMessage()));
    }

    if (auto result = resmgr.loadResourcesFromDirectory<sf::Texture>(
            rootDir  / "graphics",
            dgm::Utility::loadTexture,
            { ".png" });
        !result)
    {
        throw std::runtime_error(uni::format(
            "Could not load texture: {}", result.error().getMessage()));
    }

    if (auto result = resmgr.loadResourcesFromDirectory<dgm::AnimationStates>(
            rootDir  / "graphics",
            dgm::Utility::loadAnimationStates,
            { ".anim" });
        !result)
    {
        throw std::runtime_error(uni::format(
            "Could not load animation states: {}",
            result.error().getMessage()));
    }

    if (auto result = resmgr.loadResourcesFromDirectory<dgm::Clip>(
            rootDir  / "graphics",
            dgm::Utility::loadClip,
            { ".clip" });
        !result)
    {
        throw std::runtime_error(uni::format(
            "Could not load clip: {}", result.error().getMessage()));
    }

    if (auto result = resmgr.loadResourcesFromDirectory<sf::SoundBuffer>(
            rootDir  / "sounds", dgm::Utility::loadSound, { ".wav" });
        !result)
    {
        throw std::runtime_error(uni::format(
            "Could not load sound: {}", result.error().getMessage()));
    }

    return resmgr;
}

int main(int, char*[])
{
    sf::err() << "init" << std::endl;

    // TODO: Resolve appdata folder
    // TODO: Attept to load settings from appdata

    auto&& settings = AppSettings {
        .video =
            VideoSettings {
#ifdef _DEBUG
                .resolution = sf::VideoMode::getDesktopMode().size,
#else
                .resolution = sf::VideoMode::getDesktopMode().size,
#endif
            },
    };
    sf::err() << "before window" << std::endl;

    auto&& window = dgm::Window(dgm::WindowSettings {
        .resolution = settings.video.resolution,
        .title = CMakeVars::TITLE,
        .useFullscreen = settings.video.fullscreen,
    });
    sf::err() << "before app" << std::endl;
    auto&& app = dgm::App(window);
    sf::err() << "after window" << std::endl;

    tgui::Gui gui(window.getSfmlWindowContext());
    tgui::Theme guiTheme;
    sf::err() << "after gui" << std::endl;

    try
    {
        auto dependencies = DependencyContainer {
            .resmgr = initializeResourceManager("."),
            .strings = StringProvider(Language::English),
            .gui = Gui(gui, guiTheme),
            .input = Input(),
        };

        gui.setFont(
            dependencies.resmgr.get<tgui::Font>("ChunkFive-Regular.ttf"));

        app.pushState<AppStateMainMenu>(dependencies, settings);
        app.run();
    }
    catch (const std::exception& ex)
    {
        sf::err() << ex.what() << std::endl;
        return 1;
    }

    // TODO: capture window settings
    // TODO: store settings in appdata

    return 0;
}

/*
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <format>
#include <ranges>
#include <expected>
#include <DGM/dgm.hpp>

// Do we want to showcase direct JNI/NDK interaction?
// Undefine this to get real cross-platform code.
// Uncomment this to try JNI access; this seems to be broken in latest NDKs
// #define USE_JNI

#if defined(USE_JNI)
// These headers are only needed for direct NDK/JDK interaction
#include <android/native_activity.h>
#include <jni.h>

// Since we want to get the native activity from SFML, we'll have to use an
// extra header here:
#include <SFML/System/NativeActivity.hpp>

// NDK/JNI sub example - call Java code from native code
int vibrate(sf::Time duration)
{
    // First we'll need the native activity handle
    ANativeActivity& activity = *sf::getNativeActivity();

    // Retrieve the JVM and JNI environment
    JavaVM& vm  = *activity.vm;
    JNIEnv& env = *activity.env;

    // First, attach this thread to the main thread
    JavaVMAttachArgs attachargs;
    attachargs.version = JNI_VERSION_1_6;
    attachargs.name    = "NativeThread";
    attachargs.group   = nullptr;
    jint res           = vm.AttachCurrentThread(&env, &attachargs);

    if (res == JNI_ERR)
        return EXIT_FAILURE;

    // Retrieve class information
    jclass natact  = env.FindClass("android/app/NativeActivity");
    jclass context = env.FindClass("android/content/Context");

    // Get the value of a constant
    jfieldID fid    = env.GetStaticFieldID(context, "VIBRATOR_SERVICE", "Ljava/lang/String;");
    jobject  svcstr = env.GetStaticObjectField(context, fid);

    // Get the method 'getSystemService' and call it
    jmethodID getss   = env.GetMethodID(natact, "getSystemService", "(Ljava/lang/String;)Ljava/lang/Object;");
    jobject   vib_obj = env.CallObjectMethod(activity.clazz, getss, svcstr);

    // Get the object's class and retrieve the member name
    jclass    vib_cls = env.GetObjectClass(vib_obj);
    jmethodID vibrate = env.GetMethodID(vib_cls, "vibrate", "(J)V");

    // Determine the timeframe
    jlong length = duration.asMilliseconds();

    // Bzzz!
    env.CallVoidMethod(vib_obj, vibrate, length);

    // Free references
    env.DeleteLocalRef(vib_obj);
    env.DeleteLocalRef(vib_cls);
    env.DeleteLocalRef(svcstr);
    env.DeleteLocalRef(context);
    env.DeleteLocalRef(natact);

    // Detach thread again
    vm.DetachCurrentThread();
}
#endif

// This is the actual Android example. You don't have to write any platform
// specific code, unless you want to use things not directly exposed.
// ('vibrate()' in this example; undefine 'USE_JNI' above to disable it)
int main(int argc, char* argv[])
{
    sf::VideoMode screen(sf::VideoMode::getDesktopMode());
    auto&& window = dgm::Window(screen.size, "", false);
    window.getSfmlWindowContext().setFramerateLimit(30);

    sf::err() << "mylog" << std::endl;

    const sf::Texture texture("image.png");

    sf::Sprite image(texture);
    image.setPosition(sf::Vector2f(screen.size) / 2.f);
    image.setOrigin(sf::Vector2f(texture.getSize()) / 2.f);

    const sf::Font font("tuffy.ttf");

    sf::Text text(font, "Tap anywhere to move the logo.", 64);
    text.setFillColor(sf::Color::Black);
    text.setPosition({10, 10});

    sf::View view = window.getSfmlWindowContext().getDefaultView();

    sf::Color background = sf::Color::White;

    // We shouldn't try drawing to the screen while in background
    // so we'll have to track that. You can do minor background
    // work, but keep battery life in mind.
    bool active = true;

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>() ||
                (event->is<sf::Event::KeyPressed>() &&
                 event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Escape))
            {
                std::ignore = window.close();
            }

            else if (const auto* resized = event->getIf<sf::Event::Resized>())
            {
                const auto size = sf::Vector2f(resized->size);
                view.setSize(size);
                view.setCenter(size / 2.f);
                window.getSfmlWindowContext().setView(view);
            }
            else if (event->is<sf::Event::FocusLost>())
            {
                background = sf::Color::Black;
            }
            else if (event->is<sf::Event::FocusGained>())
            {
                background = sf::Color::White;
            }
                // On Android MouseLeft/MouseEntered are (for now) triggered,
                // whenever the app loses or gains focus.
            else if (event->is<sf::Event::MouseLeft>())
            {
                active = false;
            }
            else if (event->is<sf::Event::MouseEntered>())
            {
                active = true;
            }
            else if (const auto* touchBegan = event->getIf<sf::Event::TouchBegan>())
            {
                if (touchBegan->finger == 0)
                {
                    image.setPosition(sf::Vector2f(touchBegan->position));
#if defined(USE_JNI)
                    vibrate(sf::milliseconds(10));
#endif
                }
            }
        }

        if (active)
        {
            window.clear(background);
            window.draw(image);
            window.draw(text);
            window.display();
        }
        else
        {
            sf::sleep(sf::milliseconds(100));
        }
    }
}
*/