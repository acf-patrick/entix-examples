#include <core.h>

#include "serializer.h"

class CustomHook : public entix::core::ApplicationHook {
    entix::core::EventListner _eventListener;

    void startup() override {
        entix::core::Application::Get().setSerializer<CustomSerializer>();
        _eventListener.listen(entix::core::Input::Event::QUIT,
                              []() { entix::core::Application::Quit(); });
    }
};

int main(int argc, char* argv[]) {
    entix::core::Application::setup<CustomHook>();
    return entix::main(argc, argv);
}