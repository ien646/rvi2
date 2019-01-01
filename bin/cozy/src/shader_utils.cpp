#include "shader_utils.hpp"

#include <glad/glad.hpp>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <sstream>

const static std::string VX_SHADER_SRC_PATH = "shaders/vxshader.glsl";
const static std::string PX_SHADER_SRC_PATH = "shaders/pxshader.glsl";
const int COMPILATION_LOG_BUFF_SZ = 512;

std::string read_file(const std::string& fname)
{
    std::ifstream ifs(fname);
    std::stringstream ss;
    ss << ifs.rdbuf();
    return ss.str();
}

void init_default_shaders(GLuint* shader_prog)
{
    GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    GLuint frag_shader = glCreateShader(GL_FRAGMENT_SHADER);

    compile_shaders(vertex_shader, frag_shader);

    bool vxsh_ok = check_shader_compilation(vertex_shader, "VERTEX");
    bool pxsh_ok = check_shader_compilation(frag_shader, "FRAGMENT");

    if(vxsh_ok && pxsh_ok)
    {
        create_shader_program(vertex_shader, frag_shader, shader_prog);
    }

    glDeleteShader(vertex_shader);
    glDeleteShader(frag_shader);
}

void compile_shaders(GLuint vertex_shader, GLuint frag_shader)
{
    std::string vxshsrc = read_file(VX_SHADER_SRC_PATH);
    std::string pxshsrc = read_file(PX_SHADER_SRC_PATH);
    vxshsrc.append('\0');
    pxshsrc.append('\0');

    auto vxshsrc_ptr = vxshsrc.c_str();
    auto pxshsrc_ptr = pxshsrc.c_str();

    glShaderSource(vertex_shader, 1, &vxshsrc_ptr, NULL);
    glShaderSource(frag_shader, 1, &pxshsrc_ptr, NULL);
    glCompileShader(vertex_shader);
    glCompileShader(frag_shader);
}

bool check_shader_compilation(GLuint sh_id, const std::string& shtype)
{   
    int success = 0;
    glGetShaderiv(sh_id, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        char compilation_log[COMPILATION_LOG_BUFF_SZ];
        std::cout << "ERROR(S) COMPILING [ " << shtype << " ] SHADER! " << std::endl;
        glGetShaderInfoLog(sh_id, COMPILATION_LOG_BUFF_SZ, NULL, compilation_log);
        std::cout << compilation_log << std::endl;        
        return false;
    }
    return true;
}

bool create_shader_program(GLuint vertex_shader, GLuint frag_shader, GLuint* shprog)
{
    GLuint shader_prog = glCreateProgram();
    glAttachShader(shader_prog, vertex_shader);
    glAttachShader(shader_prog, frag_shader);
    glLinkProgram(shader_prog);

    int success = 0;
    glGetProgramiv(shader_prog, GL_LINK_STATUS, &success);
    if(!success)
    {
        char prg_link_log[COMPILATION_LOG_BUFF_SZ];
        std::cout << "ERROR LINKING SHADER PROGRAM!" << std::endl;
        glGetProgramInfoLog(shader_prog, COMPILATION_LOG_BUFF_SZ, NULL, prg_link_log);
        std::cout << prg_link_log;
        return false;
    }

    *shprog = shader_prog;
    return true;
}