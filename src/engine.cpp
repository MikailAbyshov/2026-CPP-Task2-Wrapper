#include "engine.hpp"

#include <stdexcept>
#include <utility>

void Engine::register_command(const std::string& name, Wrapper wrapper) {
    commands_.insert_or_assign(name, std::move(wrapper));
}

std::string Engine::execute(const std::string& name,
                            const Wrapper::ArgMap& args) const {
    const auto it = commands_.find(name);
    if (it == commands_.end()) {
        throw std::runtime_error("Unknown command: " + name);
    }
    return it->second.invoke(args);
}

bool Engine::has_command(const std::string& name) const {
    return commands_.find(name) != commands_.end();
}