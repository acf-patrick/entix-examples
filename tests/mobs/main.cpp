#include "application/hook.h"
#include "resources/world.h"
#include "scripts/scripts.h"
#include "serializer.h"
#include "systems.h"

using namespace entix::core;
using namespace entix::ecs;

class CustomHook : public ApplicationHook {
    EventListner eventListener;

   public:
    void startup() override {
        auto& application = Application::Get();
        application.setSerializer<CustomSerializer>();

        auto systems = SystemManager::Get();
        systems->add<WorldSystem>();

        auto resources = entix::ResourceManager::Get();
        b2Vec2 gravity = {.x = 0, .y = 10.0f};
        resources->add<World>(gravity);

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
            b2Body_SetTransform(
                entity.get<Mob>().bodyId,
                (b2Vec2){mousePos.x / MtoPX, mousePos.y / MtoPX},
                b2Rot_identity);

            entix::Logger::info("Controller") << "entity position set";
            entix::Logger::endline();
        }
    }
};

int main(int argc, char* argv[]) {
    Application::setup<CustomHook>();
    return entix::main(argc, argv);
}