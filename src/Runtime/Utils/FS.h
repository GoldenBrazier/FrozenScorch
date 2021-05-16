#include <fstream>
#include <string>

namespace Runtime::FS {
static inline std::string load_shader(const std::string& filename)
{
    auto file = std::ifstream(filename);

    std::string output;
    std::string line;

    while (getline(file, line)) {
        output.append(line);
        output.append("\n");
    }

    return output;
}
}