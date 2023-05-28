#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>


using std::cout;
using std::endl;

const unsigned int WIDTH = 800;
const unsigned int HEIGHT = 600;
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
	
	// Verificar GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{	
		cout << "Nao foi possivel carregar o contexto OpenGl" << endl;
		return -1;
	}
	while (!glfwWindowShouldClose(window))
	{

		//Expecificar os valores de cor RGBA, e limpar os buffers de cores
		glClearColor(0.20f, .30f, 0.30f, 1.0f);

		// Definir quais buffers precisam ser limpos
		glClear(GL_COLOR_BUFFER_BIT);

		// Trazer os "Back Buffers" para frente
		glfwSwapBuffers(window);

		// processamento dos eventos
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}