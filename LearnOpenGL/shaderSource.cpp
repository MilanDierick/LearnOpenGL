#include "shaderSource.h"

ShaderSources::ShaderSources()
{
	vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";

	fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"uniform vec2 u_resolution;\n"
		"uniform float u_time;\n"
		"void main()\n"
		"{\n"
		"	vec2 st = gl_FragCoord.xy / u_resolution.xy;\n"	
		"	st.x *= u_resolution.x / u_resolution.y;\n"
		"	vec3 color = vec3(.0);\n"
		"	color = vec3(st.x,st.y,abs(sin(u_time)));\n"
		"   FragColor = vec4(color,1.0);\n"
		"}\n\0";
}
