#include <core.h>

#include "./serializer.h"

class CustomHook : public entix::core::ApplicationHook {
   public:
    void startup() override {
        entix::core::Application::Get().setSerializer<CustomSerializer>();
    }
};

int main(int argc, char *argv[]) {
    entix::core::Application::setup<CustomHook>();
    return entix::main(argc, argv);
}
