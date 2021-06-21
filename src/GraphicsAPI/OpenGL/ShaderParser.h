#pragma once
#include <GL/glew.h>
#include <GraphicsAPI/Generic/Shader.h>
#include <GraphicsAPI/Generic/Var.h>
#include <GraphicsAPI/Generic/Uniform.h>
#include <iostream>
#include <memory>
#include <string>
#include <string_view>
#include <type_traits>
#include <unordered_map>
#include <vector>

namespace GL {

class LineStreamer {
public:
    explicit LineStreamer(const std::string& line);
    explicit LineStreamer(std::string&& line);
    ~LineStreamer() = default;

    const std::string& line() const { return m_line; }

    std::string_view token() { return std::string_view(&m_line[m_pos], m_current_token_size); }
    bool eof() const { return m_eof; }
    void eat(const std::string& want)
    {
        if (want.size() != m_current_token_size || want != token()) {
            std::cerr << "[LineStreamer] want " << want << " got " << token();
            std::abort();
        }
        eat();
    }

    void eat()
    {
        m_pos += m_current_token_size;
        next_token();
    }

private:
    bool need_to_skip(char c) const { return c == ' ' || c == ';'; }

    void skip_gaps() {
        while (m_pos < m_line.size() && need_to_skip(m_line[m_pos])) m_pos++;
        m_eof = m_pos == m_line.size();
    }

    void calculate_current_token_size();
    void next_token()
    {
        if (skip_gaps(); eof()) {
            return;
        }
        calculate_current_token_size();
    }

    std::string m_line;
    std::size_t m_pos { 0 };
    std::size_t m_current_token_size { 0 };
    bool m_eof { false };
};

class ShaderParser {
public:
    explicit ShaderParser(const std::vector<std::string>& files)
        : m_filenames(files)
    {
    }

    explicit ShaderParser(std::vector<std::string>&& files)
        : m_filenames(std::move(files))
    {
    }

    ~ShaderParser() = default;

    void parse();
    const std::vector<std::pair<std::string, int>>& attributes() const { return m_attributes; }
    const Generic::UniformList& uniforms() const { return m_uniform_builder.data(); }

private:
    void parse_file(const std::string& filename);
    void interpret_line(const std::string& filename, LineStreamer& streamer);
    void interpret_define(LineStreamer& streamer);
    void interpret_uniform(LineStreamer& streamer);
    void interpret_attribute(LineStreamer& streamer);

    bool is_number(const std::string& s) { return !s.empty() && std::all_of(s.begin(), s.end(), ::isdigit); }
    int to_number(const std::string& s) { return std::stoi(s); }

    std::vector<std::string> m_filenames;
    std::unordered_map<std::string, std::string> m_defines;
    Generic::UniformBuilder m_uniform_builder;
    std::vector<std::pair<std::string, int>> m_attributes; // TODO: Replace with builder.

};

}