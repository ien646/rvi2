#include <glad/glad.hpp>
#include <GLFW/glfw3.h>

#include <vector>

struct vframe
{
    GLuint vao;
    GLuint vbo;
    std::vector<float> line_data;

    vframe() = default;
    vframe(const vframe& cp_src) = delete;

    vframe(vframe&& mv_src);

    ~vframe();

private:
    bool _moved = false;
};