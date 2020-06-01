#ifndef SHADER_H
#define SHADER_H


#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class screenShader
{
public :
	unsigned int ID;

	screenShader(const char* vertexPath, const char* fragmentPath) {
		//1. 소스 코드 검색
		std::string vertexCode;
		std::string fragmentCode;
		std::ifstream vShaderFile;
		std::ifstream fShaderFile;
		//예외 처리
		vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try {
			//open file
			vShaderFile.open(vertexPath);
			fShaderFile.open(fragmentPath);
			std::stringstream vShaderStream, fShaderStream;
			//resd buffer
			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();
			//close file handler
			vShaderFile.close();
			fShaderFile.close();
			//stream convert to string
			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();
		}
		catch (std::ifstream::failure e) {
			std::cout << "ERROR::SHADER::FILE_NOT_READ" << std::endl;
		}
		const char* vShaderCode = vertexCode.c_str();
		const char* fShaderCode = fragmentCode.c_str();
		//2. shader compile
		unsigned int vertex, fragemt;
		int success;
		char infoLog[512];

		//vertexShader
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vShaderCode, NULL);
		glCompileShader(vertex);
		//compile error
		glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(vertex, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::PROGRAM::INKING::FAILURE" << infoLog << std::endl;
		}

		//fragmentShder
		fragemt = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragemt, 1, &fShaderCode, NULL);
		glCompileShader(fragemt);
		//compile error
		glGetShaderiv(fragemt, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(fragemt, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::PROGRAM::INKING::FAILURE" << infoLog << std::endl;
		}

		ID = glCreateProgram();
		glAttachShader(ID, vertex);
		glAttachShader(ID, fragemt);
		glLinkProgram(ID);
		//linking error
		glGetProgramiv(ID, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(ID, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::PRGRAM::LINKING_FAILED" << infoLog << std::endl;
		}

		glDeleteShader(vertex);
		glDeleteShader(fragemt);
	}

	void use() {
		glUseProgram(ID);
	}

	void setBool(const std::string& name, bool value) const
	{
		glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
	}
	void setInt(const std::string& name, int value) const {
		glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
	}
	void setFloat(const std::string& name, float value) const {
		glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
	}

};

#endif
