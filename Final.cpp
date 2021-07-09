/*-----------------PROYECTO FINAL - COMPUTACIÓN GRÁFICA E INTERACCIÓN HUMANO COMPUTADORA--------------------------*/
//INTEGRANTES:
//
// DÍAZ GARCÍA PORFIRIO 
// NARVÁEZ MARQUEDA RICARDO ANDRÉ SEBASTIÁN
// PÉREZ GUTIÉRREZ SANDRA SUSANA 

#include <Windows.h>

#include <glad/glad.h>
#include <glfw3.h>	
#include <stdlib.h>		
#include <glm/glm.hpp>	
#include <glm/gtc/matrix_transform.hpp>	
#include <glm/gtc/type_ptr.hpp>
#include <time.h>


#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>	

#define SDL_MAIN_HANDLED
#include <SDL/SDL.h>

#include <shader_m.h>
#include <camera.h>
#include <modelAnim.h>
#include <model.h>
#include <Skybox.h>
#include <iostream>



void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

void my_input(GLFWwindow* window, int key, int scancode, int action, int mods);
void animate(void);


unsigned int SCR_WIDTH = 1920;
unsigned int SCR_HEIGHT = 1080;
GLFWmonitor* monitors;

void getResolution(void);

// camera
Camera camera(glm::vec3(0.0f, 0.5f, 0.0f));
float MovementSpeed = 1.0f;
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
const int FPS = 60;
const int LOOP_TIME = 1000 / FPS; // = 16 milisec // 1000 millisec == 1 sec
double	deltaTime = 0.0f,
lastFrame = 0.0f;

//Lighting
glm::vec3 lightPosition(0.0f, 4.0f, 10.0f); // Dirección de la luz --Modificar de acuerdo a la SKYBOX [ANDRE]
glm::vec3 lightDirection(0.0f, -1.0f, 1.0f);

bool dia = true;

//Debuggeo para posición de elementos
float movx = 0;
float movy = 0;
float movz = 0;





//Keyframes (Manipulación y dibujo)


#define MAX_FRAMES 9


typedef struct _frame
{


}FRAME;

FRAME KeyFrame[MAX_FRAMES];
int FrameIndex = 0;			//introducir datos
bool play = false;
int playIndex = 0;

void saveFrame(void)
{
	//printf("frameindex %d\n", FrameIndex);
	std::cout << "Frame Index = " << FrameIndex << std::endl;


	FrameIndex++;
}

void resetElements(void)
{

}

void interpolation(void)
{


}

void animate(void)
{


	// ANIMACIONES AQUÍ [ANDRÉ]
}




void getResolution()
{
	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	SCR_WIDTH = mode->width;
	SCR_HEIGHT = (mode->height) - 80;
}


int main()
{

	glfwInit();


#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	monitors = glfwGetPrimaryMonitor();
	getResolution();

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "CGeIHC", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwSetWindowPos(window, 0, 30);
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetKeyCallback(window, my_input);


	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);


	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}


	glEnable(GL_DEPTH_TEST);


	Shader staticShader("Shaders/shader_Lights.vs", "Shaders/shader_Lights.fs");
	Shader skyboxShader("Shaders/skybox.vs", "Shaders/skybox.fs");
	Shader animShader("Shaders/anim.vs", "Shaders/anim.fs");

	vector<std::string> faces
	{
		"resources/skybox/right.jpg",
		"resources/skybox/left.jpg",
		"resources/skybox/top.jpg",
		"resources/skybox/bottom.jpg",
		"resources/skybox/front.jpg",
		"resources/skybox/back.jpg"
	};

	vector<std::string> facesNoche
	{
		"resources/skybox/rightNoche.jpg",
		"resources/skybox/leftNoche.jpg",
		"resources/skybox/topNoche.jpg",
		"resources/skybox/bottomNoche.jpg",
		"resources/skybox/frontNoche.jpg",
		"resources/skybox/backNoche.jpg"
	};

	Skybox skybox = Skybox(faces);
	Skybox skyboxNoche = Skybox(facesNoche);

	// Shader configuration
	// --------------------
	skyboxShader.use();
	skyboxShader.setInt("skybox", 0);

	skyboxShader.use();
	skyboxShader.setInt("skyboxNoche", 0);

	// 1. CARGA DE MODELOS
	// -----------
	Model pisoDef("resources/objects/pisoDef/pisoDef.obj");
	Model banorte("resources/objects/Banorte/Banorte.obj");
	Model casaHC("resources/objects/CasaHC/casaHC.obj");
	Model avenida("resources/objects/Avenida/avenida.obj");
	Model tope("resources/objects/topes/tope.obj");
	Model arbolMaceta("resources/objects/arboles/arbolMaceta.obj"); 
	Model tel("resources/objects/telefonos/telPublico.obj");
	Model posteLuz("resources/objects/posteLuz/posLuz.obj");
	Model banca("resources/objects/banca/banca.obj");
	Model areasVerdes("resources/objects/areasVerdes/areasVerdes.obj");



	//Aquí se cargan los modelos 





	// LOOP DE RENDERIZADO
	while (!glfwWindowShouldClose(window))
	{
		skyboxShader.setInt("skybox", 0);
		skyboxShader.setInt("skyboxNoche", 0);
		lastFrame = SDL_GetTicks();


		animate();


		glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		staticShader.use();
		//Setup Advanced Lights
		staticShader.setVec3("viewPos", camera.Position);
		staticShader.setVec3("dirLight.direction", lightDirection);
		staticShader.setVec3("dirLight.ambient", glm::vec3(0.3f, 0.3f, 0.3f));//luz gris
		staticShader.setVec3("dirLight.diffuse", glm::vec3(1.0f, 1.0f, 1.0f));
		staticShader.setVec3("dirLight.specular", glm::vec3(1.0f, 1.0f, 1.0f));
		//Luz Direccional


		staticShader.setVec3("pointLight[0].position", lightPosition);
		staticShader.setVec3("pointLight[0].ambient", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setVec3("pointLight[0].diffuse", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setVec3("pointLight[0].specular", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setFloat("pointLight[0].constant", 0.08f);
		staticShader.setFloat("pointLight[0].linear", 0.009f);
		staticShader.setFloat("pointLight[0].quadratic", 0.032f);

		staticShader.setVec3("pointLight[1].position", glm::vec3(-80.0, 0.0f, 0.0f));
		staticShader.setVec3("pointLight[1].ambient", glm::vec3(1.0f, 0.0f, 0.0f));//Luz Roja
		staticShader.setVec3("pointLight[1].diffuse", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setVec3("pointLight[1].specular", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setFloat("pointLight[1].constant", 1.0f);
		staticShader.setFloat("pointLight[1].linear", 0.009f);
		staticShader.setFloat("pointLight[1].quadratic", 0.032f);

		staticShader.setFloat("material_shininess", 32.0f);

		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 tmp = glm::mat4(1.0f);
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 10000.0f);
		glm::mat4 view = camera.GetViewMatrix();
		staticShader.setMat4("projection", projection);
		staticShader.setMat4("view", view);
		//// Light
		glm::vec3 lightColor = glm::vec3(0.6f);
		glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f);
		glm::vec3 ambientColor = diffuseColor * glm::vec3(0.75f);

		//2. DIBUJADO DE MODELOS

		//*****ENTORNO GENERAL Y SUPERFICIE******

		//TOPES
		for (int i = 0; i < 20; i++) {
			model = glm::mat4(1.0f);
			model = glm::translate(model, glm::vec3(2.5f, -1.0f, -0.6f-(i*1.2)));
			staticShader.setMat4("model", model);
			tope.Draw(staticShader);
		}//Telefono
		for (int i = 0; i < 3; i++) {
			model = glm::mat4(1.0f);
			model = glm::translate(model, glm::vec3(-4.0f+i, -1.2f, -15.8f));
			staticShader.setMat4("model", model);
			tel.Draw(staticShader);
		}

		//POSTE DE LUZ
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-1.5f, -1.2f, -12.4f));
		staticShader.setMat4("model", model);
		posteLuz.Draw(staticShader);
		

		//DECLARACIÓN DE SUELOS
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-10.0f, -1.0f, -12.0f));
		staticShader.setMat4("model", model);
		pisoDef.Draw(staticShader);

		//****AREAS VERDES****
		for (int i = 0; i < 3; i++) {
			model = glm::mat4(1.0f);
			if (i == 2) {
				model = glm::translate(model, glm::vec3(-12.0f - i * 4, -1.5f, -12.6f));
			}else{
				model = glm::translate(model, glm::vec3(-12.0f + i * 4, -1.5f, -12.6f));
			}

			model = glm::scale(model, glm::vec3(0.4));
			staticShader.setMat4("model", model);
			arbolMaceta.Draw(staticShader);
			}


		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-3.5f, -0.8f, -20.6f));
		staticShader.setMat4("model", model);
		areasVerdes.Draw(staticShader);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-15.0f, -0.8f, -20.6f));
		staticShader.setMat4("model", model);
		areasVerdes.Draw(staticShader);


		//Bancas
		

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-7.4f, -1.0f, -11.2f));
		staticShader.setMat4("model", model);
		banca.Draw(staticShader);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-11.4f, -1.0f, -11.2f));
		staticShader.setMat4("model", model);
		banca.Draw(staticShader);


		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-9.4f, -1.0f, -14.4f));
		staticShader.setMat4("model", model);
		banca.Draw(staticShader);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-16.0f, -1.0f, -14.4f));
		staticShader.setMat4("model", model);
		banca.Draw(staticShader);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-14.5f, -1.0f, -14.4f));
		staticShader.setMat4("model", model);
		banca.Draw(staticShader);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-18.0f, -1.0f, -12.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		staticShader.setMat4("model", model);
		banca.Draw(staticShader);


		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-12.5f, -1.0f, -12.0f));
		model = glm::rotate(model, glm::radians(270.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		staticShader.setMat4("model", model);
		banca.Draw(staticShader);






	
		
		


		//****AVENIDAS*****
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(8.5f, - 0.95f,  0.4f));
		staticShader.setMat4("model", model);
		avenida.Draw(staticShader);

		//EDIFICIOS
		//BANORTE
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0, -1.5f, 4));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f,1.0f,0.0f));
		staticShader.setMat4("model", model);
		banorte.Draw(staticShader);
		//Casa de Hernán Cortéz
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-15.5f,-0.8f,1.2f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		staticShader.setMat4("model", model);
		casaHC.Draw(staticShader);

		











		//DIBUJO SKYBOX
		skyboxShader.use();
		if (dia == true) {
			skybox.Draw(skyboxShader, view, projection, camera);
		}
		else {
			skyboxNoche.Draw(skyboxShader, view, projection, camera);
		}


		// Limitar el framerate a 60
		deltaTime = SDL_GetTicks() - lastFrame; // time for full 1 loop

		if (deltaTime < LOOP_TIME)
		{
			SDL_Delay((int)(LOOP_TIME - deltaTime));
		}
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	skyboxNoche.Terminate();
	skybox.Terminate();

	glfwTerminate();
	return 0;
}

//CONFIGURACIÓN DE ENTRADAS
void my_input(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS) {
		if (dia == true) {
			dia = false;
		}
		else {
			dia = true;
		}

	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		movx += 0.5f;
	}

		if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
			movx -= 0.5f;
	}

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS){

		movz += 0.2f;
	
	}

	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
			movz -= 0.2f;

	}
	if (glfwGetKey(window, GLFW_KEY_PAGE_DOWN) == GLFW_PRESS) {
		movy -= 0.2f;
	}
	if (glfwGetKey(window, GLFW_KEY_PAGE_UP) == GLFW_PRESS) {
		movy += 0.2f;
	}
	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) { //Imprime las coordenadas en pantalla para saber donde va el elemento
		std::cout << "COORDENADAS EN X, Y,  Z " << movx << "f," << movy << "f," << movz <<"f" << std::endl;

	}



}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{

	glViewport(0, 0, width, height);
}


void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}
//FIELD OF VIEW AJUSTABLE
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}