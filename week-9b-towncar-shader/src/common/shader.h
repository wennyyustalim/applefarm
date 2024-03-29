#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>

// Load vertex and fragment shader and return the shader program id
GLuint LoadShaders(const char * vertex_shader_file_path, const char * fragment_shader_file_path);

#endif
