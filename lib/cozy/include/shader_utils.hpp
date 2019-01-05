#pragma once

#include <string>
#include <glad/glad.hpp>
#include <GLFW/glfw3.h>

extern std::string read_file(const std::string& fname);
extern void init_default_shaders(GLuint* shader_prog);
extern void compile_shaders(GLuint vertex_shader, GLuint frag_shader);
extern bool check_shader_compilation(GLuint sh_id, const std::string& shtype);
extern bool create_shader_program(GLuint vertex_shader, GLuint frag_shader, GLuint* shprog);