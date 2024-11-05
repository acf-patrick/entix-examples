#include "application/hook.h"
#include "scripts/scripts.h"
#include "serializer.h"

using namespace entix::core;
using namespace entix::ecs;

class CustomHook : public ApplicationHook {
    EventListner eventListener;

   public:
    void startup() override {
        auto& application = Application::Get();
        application.setSerializer<CustomSerializer>();

        eventListener.listen(Input::Event::QUIT, [] { Application::Quit(); })
            .listen(Input::Event::MOUSE_BUTTON_UP,
                    [&] { createEntityAtMousePosition(); })
            .listen(Input::Event::KEY_DOWN, [&]() {
                if (Input::isKeyPressed(SDL_SCANCODE_LCTRL) &&
                    Input::isKeyPressed(SDL_SCANCODE_S)) {
                    auto sceneManager = SceneManager::Get();
                    sceneManager->getActive().save("scene-snapshot");
                }
            });
    }

    void createEntityAtMousePosition() const {
        auto& entity = SceneManager::Get()->getActive().getEntities().create();
        entity.useTemplate("prefabs/mob.entt");

        auto mousePos = Input::getMousePosition();
        if (entity.has<Mob>()) {
            entity.get<Mob>().setPosition(
                (b2Vec2){PXtoM(mousePos.x), PXtoM(mousePos.y)});

            entix::Logger::info("Controller") << "entity position set";
            entix::Logger::endline();
        }
    }
};

int main(int argc, char* argv[]) {
    Application::setup<CustomHook>();
    return entix::main(argc, argv);
}