#include <GraphicsAPI/OpenGL/ShaderParser.h>
#include <fstream>
#include <iostream>
#include <string>

namespace GL {

LineStreamer::LineStreamer(const std::string& line)
    : m_line(line)
{
    next_token();
}

LineStreamer::LineStreamer(std::string&& line)
    : m_line(std::move(line))
{
    next_token();
}

void LineStreamer::calculate_current_token_size()
{
    m_current_token_size = 0;
    while (m_pos + m_current_token_size < m_line.size() && !need_to_skip(m_line[m_pos + m_current_token_size])) {
        m_current_token_size++;
    }
}

void ShaderParser::parse()
{
    for (auto& filename : m_filenames) {
        parse_file(filename);
    }
}

void ShaderParser::parse_file(const std::string& filename)
{
    auto file = std::ifstream(filename);
    std::string line;

    while (getline(file, line)) {
        auto streamer = LineStreamer(std::move(line));
        interpret_line(filename, streamer);
        line.clear();
    }
}

void ShaderParser::interpret_line(const std::string& filename, LineStreamer& streamer)
{
    if (streamer.line().starts_with("uniform")) {
        interpret_uniform(streamer);
    } else if (streamer.line().starts_with("in") && filename.ends_with(".vs")) {
        interpret_attribute(streamer);
    } else if (streamer.line().starts_with("#define")) {
        interpret_define(streamer);
    }
}

void ShaderParser::interpret_define(LineStreamer& streamer)
{
    streamer.eat("#define");
    auto key = std::string(streamer.token());
    streamer.eat();
    m_defines[key] = streamer.token();
}

void ShaderParser::interpret_uniform(LineStreamer& streamer)
{
    streamer.eat("uniform");
    streamer.eat(); // Eating var type
    auto uniform_var_name = streamer.token();

    // Check if it is an array
    if (auto left_bracket_pos = uniform_var_name.find("["); left_bracket_pos != std::string::npos) {
        int array_size = 0;
        auto array_name = std::string(uniform_var_name.substr(0, left_bracket_pos));

        auto right_bracket_pos = uniform_var_name.find("]");
        left_bracket_pos++, right_bracket_pos--;
        assert(right_bracket_pos != std::string::npos && left_bracket_pos <= right_bracket_pos);

        auto array_size_str = std::string(uniform_var_name.substr(left_bracket_pos,right_bracket_pos - left_bracket_pos + 1));
        if (is_number(array_size_str)) {
            array_size = to_number(array_size_str);
        } else {
            // If it's not [number], so we check for defines.
            assert(is_number(m_defines[array_size_str]));
            array_size = to_number(m_defines[array_size_str]);
        }

        m_uniform_builder.add_gl_array(array_name, array_size);
    } else {
        m_uniform_builder.add_var(std::string(uniform_var_name));
    }
}

void ShaderParser::interpret_attribute(LineStreamer& streamer)
{
    streamer.eat("in");
    streamer.eat(); // Eating var type
    auto attribute_var_name = streamer.token();
    m_attributes.emplace_back(std::string(attribute_var_name), m_attributes.size());
}
}