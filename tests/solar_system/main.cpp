#include <core.h>

#include "serializer.h"

class CustomHook : public entix::core::ApplicationHook {
    entix::core::EventListner eventListener;

   public:
    void startup() override {
        entix::core::Application::setSerializer<Serializer>();

        eventListener.listen(entix::core::Input::Event::QUIT,
                             [&] { entix::core::Application::Quit(); });
    }
};

int main(int argc, char* argv[]) {
    entix::core::Application::setup<CustomHook>();
    return entix::main(argc, argv);
}