#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>


using std::cout;
using std::endl;

const unsigned int WIDTH = 800;
const unsigned int HEIGHT = 600;

// protótipo de função
void frameBufferSizeCallback(GLFWwindow* window, int width, int height);


// Vertex Shader
const char* vertexShaderSource = "#version 330 core\n"
	"layout (location = 0) in vec3 aPos;\n"
	"void main()\n"
	"{\n"
	"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
	"}\0";

// Fragment Shader
const char* fragmentShaderSource = "#version 330 core\n"
	"out vec4 FragColor;\n"
	"void main()\n"
	"{\n"
	"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
	"}\n\0";

int main()
{

	// Inicializar lib GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Instanciar GLFWwindow
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "DiarioOpenGl", NULL, NULL);
	if (window == NULL) 
	{
		cout << "Falha ao criar GLFWwindow" << endl;
		return -1;
	}
	
	// Definir window como contecto actual da thread chamada
	glfwMakeContextCurrent(window);
	
	// Definir funcao de retorno de chamada para redimensionamento da janela
	glfwSetFramebufferSizeCallback(window, frameBufferSizeCallback);
	
	// Verificar GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{	
		cout << "Nao foi possivel carregar o contexto OpenGl" << endl;
		return -1;
	}

	// Vertex Shader
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	// Fragment Shader
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	// Shader Program
	unsigned int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram); // VIncular shaderProgram ao OpenGl

	// Verificar erro de vinculacao
	int success;
	char infoLog[512];
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	
	if(!success)
	{
	
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		cout << "Erro ao vincular Shader Program" << endl;
		cout << infoLog << endl;
	}

	// Deletar shaders inutilizados (liberar espaço da memória)
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// Vertices do triangulo
	float vertices[] =
	{
		-0.5f, -0.5f, 0.0f, // A
		0.0f, 0.5f, 0.0f, // B
		0.5f, -0.5f, 0.0f // C
	};

	//Vertex Buffer Object (VBO)
	unsigned int  VBO;
	glGenBuffers(1, &VBO);

	// Vertex Array Object (VAO)
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);

	// Vincular VAO e VBO ao openGl
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER,VBO);

	// copiar dados dos vertices para o VBO vinculado
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Atribuir ponteiros aos vertices
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (void*)0);
	glEnableVertexAttribArray(0);

	// Desvincular VBA e VBO para não modificar acidentalmente
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);



	while (!glfwWindowShouldClose(window))
	{

		//Expecificar os valores de cor RGBA, e limpar os buffers de cores
		glClearColor(0.20f, .30f, 0.30f, 1.0f);

		// Definir quais buffers precisam ser limpos
		glClear(GL_COLOR_BUFFER_BIT);

		// Definir qual shader program  o programa de ve usar
		glUseProgram(shaderProgram);

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// Trazer os "Back Buffers" para frente
		glfwSwapBuffers(window);

		// processamento dos eventos
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}

void frameBufferSizeCallback(GLFWwindow* window, int width, int height)
{
	cout << "Foi redimensionada" << endl;
	glad_glViewport(0, 0, width, height);
}