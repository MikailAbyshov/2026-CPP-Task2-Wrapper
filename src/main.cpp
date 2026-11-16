#include "engine.hpp"
#include "text_processor.hpp"
#include "wrapper.hpp"

#include <iostream>
#include <string>

namespace {

void demo_replace_words(Engine& engine, const std::string& text) {
    std::cout << "[replace_words] "
              << engine.execute("replace", {{"text", text},
                                            {"from", "кот"},
                                            {"to", "пёс"}})
              << '\n';
}

void demo_find_phrase(Engine& engine, const std::string& text) {
    std::cout << "[find_phrase] "
              << engine.execute("find", {{"text", text},
                                         {"phrase", "быстрый кот"}})
              << '\n';
}

void demo_capitalize_words(Engine& engine, const std::string& text) {
    std::cout << "[capitalize_words] "
              << engine.execute("cap_words", {{"text", text}})
              << '\n';
}

void demo_capitalize_sentences(Engine& engine, const std::string& text) {
    std::cout << "[capitalize_sentences] "
              << engine.execute("cap_sent", {{"text", text}})
              << '\n';
}

void demo_number_sentences(Engine& engine, const std::string& text) {
    std::cout << "[number_sentences]\n"
              << engine.execute("number", {{"text", text}});
}

} // namespace

int main() {
    TextProcessor processor;
    Engine engine;

    engine.register_command("replace", Wrapper(
        [&processor](const Wrapper::ArgMap& args) {
            return processor.replace_words(args.at("text"),
                                           args.at("from"),
                                           args.at("to"));
        },
        {{"from", ""}, {"to", ""}}));

    engine.register_command("find", Wrapper(
        [&processor](const Wrapper::ArgMap& args) {
            return processor.find_phrase(args.at("text"), args.at("phrase"));
        },
        {{"phrase", ""}}));

    engine.register_command("cap_words", Wrapper(
        [&processor](const Wrapper::ArgMap& args) {
            return processor.capitalize_words(args.at("text"));
        },
        {}));

    engine.register_command("cap_sent", Wrapper(
        [&processor](const Wrapper::ArgMap& args) {
            return processor.capitalize_sentences(args.at("text"));
        },
        {}));

    engine.register_command("number", Wrapper(
        [&processor](const Wrapper::ArgMap& args) {
            return processor.number_sentences(args.at("text"));
        },
        {}));

    const std::string text =
        "быстрый кот бежит по парку. кот любит гулять! ты видел этого кота?";
    const std::string sentence_text =
        "привет мир. это второй абзац! и это третий вопрос?";

    std::cout << "Исходный текст: " << text << "\n\n";

    demo_replace_words(engine, text);
    demo_find_phrase(engine, text);
    demo_capitalize_words(engine, text);
    demo_capitalize_sentences(engine, sentence_text);
    demo_number_sentences(engine, sentence_text);

    return 0;
}