#pragma once

#include <string>
#include <vector>

class TextProcessor {
public:
    [[nodiscard]] std::string replace_words(const std::string& text,
                                            const std::string& from,
                                            const std::string& to) const;
    [[nodiscard]] std::string find_phrase(const std::string& text,
                                          const std::string& phrase) const;
    [[nodiscard]] std::string capitalize_words(const std::string& text) const;
    [[nodiscard]] std::string capitalize_sentences(const std::string& text) const;
    [[nodiscard]] std::string number_sentences(const std::string& text) const;

private:
    [[nodiscard]] static std::vector<std::string> split_sentences(const std::string& text);
};