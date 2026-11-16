#include "text_processor.hpp"

#include <cctype>
#include <sstream>
#include <string_view>

std::string TextProcessor::replace_words(const std::string& text,
                                         const std::string& from,
                                         const std::string& to) const {
    if (from.empty()) {
        return text;
    }
    std::string result;
    result.reserve(text.size());
    std::string::size_type pos = 0;
    while (true) {
        const auto found = text.find(from, pos);
        if (found == std::string::npos) {
            result.append(text, pos, std::string::npos);
            break;
        }
        result.append(text, pos, found - pos);
        result.append(to);
        pos = found + from.size();
    }
    return result;
}

std::string TextProcessor::find_phrase(const std::string& text,
                                       const std::string& phrase) const {
    if (phrase.empty()) {
        return "not found";
    }
    return text.find(phrase) != std::string::npos ? "found" : "not found";
}

std::string TextProcessor::capitalize_words(const std::string& text) const {
    std::string result = text;
    bool at_word_start = true;
    for (char& ch : result) {
        const auto uch = static_cast<unsigned char>(ch);
        if (std::isalpha(uch) != 0) {
            if (at_word_start) {
                ch = static_cast<char>(std::toupper(uch));
            }
            at_word_start = false;
        } else {
            at_word_start = true;
        }
    }
    return result;
}

std::string TextProcessor::capitalize_sentences(const std::string& text) const {
    std::string result = text;
    bool at_sentence_start = true;
    for (char& ch : result) {
        const auto uch = static_cast<unsigned char>(ch);
        if (at_sentence_start && std::isalpha(uch) != 0) {
            ch = static_cast<char>(std::toupper(uch));
            at_sentence_start = false;
        } else if (ch == '.' || ch == '!' || ch == '?') {
            at_sentence_start = true;
        }
    }
    return result;
}

std::string TextProcessor::number_sentences(const std::string& text) const {
    const auto sentences = split_sentences(text);
    std::ostringstream out;
    std::size_t index = 1;
    for (const auto& sentence : sentences) {
        if (sentence.empty()) {
            continue;
        }
        out << index << ". " << sentence << '\n';
        ++index;
    }
    return out.str();
}

std::vector<std::string> TextProcessor::split_sentences(const std::string& text) {
    std::vector<std::string> result;
    std::string current;
    for (const char ch : text) {
        if (ch == '\n') {
            if (!current.empty()) {
                result.push_back(current);
                current.clear();
            }
            continue;
        }
        current.push_back(ch);
        if (ch == '.' || ch == '!' || ch == '?') {
            result.push_back(current);
            current.clear();
        }
    }
    if (!current.empty()) {
        result.push_back(current);
    }
    return result;
}