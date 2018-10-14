/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <lkaser@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/13 19:33:44 by lkaser            #+#    #+#             */
/*   Updated: 2018/10/13 19:33:45 by lkaser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <emscripten.h>
#include <emscripten/html5.h>
#include "scop.h"

void	validate_shader(GLuint shader)
{
	GLint	success;
	GLint	log_size;
	char	*log;

	success = 0;
	log_size = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE)
	{
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_size);
		log = malloc(log_size);
		glGetShaderInfoLog(shader, log_size, NULL, log);
		printf("%s\n", log);
		free(log);
		exit(1);
	}
}

GLuint	compile_shader(const char *path, GLenum shader_type)
{
	size_t	size;
	FILE	*shader_file;
	char	*shader_str;
	GLuint	id;

	if ((shader_file = fopen(path, "r")) == NULL)
	{
		perror("File error");
		exit(1);
	}
	fseek(shader_file, 0L, SEEK_END);
	size = ftell(shader_file);
	rewind(shader_file);
	shader_str = malloc(size);
	fread(shader_str, 1, size + 1, shader_file);
	shader_str[size] = '\0';
	fclose(shader_file);
	id = glCreateShader(shader_type);
	glShaderSource(id, 1, (const GLchar**)&shader_str, NULL);
	glCompileShader(id);
	free(shader_str);
	validate_shader(id);
	return (id);
}

void	validate_program(GLuint program_id)
{
	GLint	success;
	GLint	log_size;
	char	*log;

	glGetProgramiv(program_id, GL_LINK_STATUS, &success);
	glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &log_size);
	if (success == GL_FALSE)
	{
		glGetShaderiv(program_id, GL_INFO_LOG_LENGTH, &log_size);
		log = malloc(log_size);
		glGetProgramInfoLog(program_id, log_size, NULL, log);
		printf("%s\n", log);
		exit(1);
	}
}

GLuint	make_program(const char *frag, const char *vert)
{
	GLuint frag_id;
	GLuint vert_id;
	GLuint program_id;

	frag_id = compile_shader(frag, GL_FRAGMENT_SHADER);
	vert_id = compile_shader(vert, GL_VERTEX_SHADER);
	program_id = glCreateProgram();
	glAttachShader(program_id, vert_id);
	glAttachShader(program_id, frag_id);
	glLinkProgram(program_id);
	validate_program(program_id);
	glDetachShader(program_id, vert_id);
	glDetachShader(program_id, frag_id);
	glDeleteShader(vert_id);
	glDeleteShader(frag_id);
	return (program_id);
}
