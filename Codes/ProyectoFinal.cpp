/*---------------------------------------------------------*/
/*--------------------- Proyecto Final --------------------*/
/*---------------------    2024-1   -----------------------*/

/*------------- Alumno: Muñoz Tamés María Ángel -----------*/
/*------------- No. Cuenta: 314124638 ---------------------*/

/*------------- Alumno: Recinos Hernandez Luis Mario ------*/
/*------------- No. Cuenta: 317244331 ---------------------*/

/*------------- Alumno: Álvarez Sánchez Casandra Itzel------*/
/*------------- No. Cuenta: 317229505 ---------------------*/
#include <Windows.h>

#include <glad/glad.h>
#include <glfw3.h>	//main
#include <stdlib.h>		
#include <glm/glm.hpp>	//camera y model
#include <glm/gtc/matrix_transform.hpp>	//camera y model
#include <glm/gtc/type_ptr.hpp>
#include <time.h>


#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>	//Texture

#define SDL_MAIN_HANDLED
#include <SDL/SDL.h>

#include <shader_m.h>
#include <camera.h>
#include <modelAnim.h>
#include <model.h>
#include <Skybox.h>
#include <iostream>

//mariposa
float rotAlas1 = 0.0f,
	rotAlas2;

//#pragma comment(lib, "winmm.lib")

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
//void my_input(GLFWwindow *window);
void my_input(GLFWwindow* window, int key, int scancode, int action, int mods);
void animate(void);

//Color prendido
float varColorR = 0.0f;
float varColorG = 0.0f;
float varColorB = 0.0f;
int elegirColor = 0;
int cont = 3000;
int prendida = 0;

//*****************************
// settings
unsigned int SCR_WIDTH = 800;
unsigned int SCR_HEIGHT = 600;
GLFWmonitor *monitors;

void getResolution(void);

// camera
Camera camera(glm::vec3(0.0f, 4.0f, 3.0f));
float MovementSpeed = 0.1f;
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
const int FPS = 60;
const int LOOP_TIME = 1000 / FPS; // = 16 milisec // 1000 millisec == 1 sec
double	deltaTime = 0.0f,
		lastFrame = 0.0f;

//Lighting
glm::vec3 lightPosition(0.0f, 15.0f, -10.0f);
glm::vec3 lightDirection(-1.0f, -1.0f, 0.0f);

float myVar = 0.0f;

//// Light
glm::vec3 lightColor = glm::vec3(0.7f);
glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f);
glm::vec3 ambientColor = diffuseColor * glm::vec3(0.75f);

//cambio de skybox
boolean noche = false;

/****************************************************
						Flippers
****************************************************/

float flipper1,
flipper2,
flipper3;


//***************************************************
//VALORES DE POSICIÓN Y ANIMACIÓN DE POMPOMPURIN
//***************************************************

// posiciones 
float	posX = 0.0f,
		posY = 0.0f,
		posZ = 0.0f,
		giroBrazoDer = 180.0f,
		giroBrazoIzq = 180.0f,
		giroPiernaDer = 0.0f,
		giroPiernaIzq = 0.0f,
		orienta = 180.0f;
	//Debería activarse cuando se mueva el personaje para comenzar su ciclo de animación
bool	walkCycle = false,
		regresoWalkCycle = false;

int cont1 = 0;

//***************************************************
//VALORES DE POSICIÓN DE LA CANICA [1]
//***************************************************
//Keyframes (Manipulación y dibujo)

//***************************************************
//VALORES BASURA (PROYECTO ANTERIOR) 		(No tocar, se rompe el proyecto)
//***************************************************
float	posCanicaX = 0.0f,
		posCanicaY = 0.0f,
		posCanicaZ = 0.0f,
		giroMariposa = 0.0f,
		rotRodDer = 0.0f,
		rotRodIzq = 0.0f,
		cabezaRot;//Para manipular el dibujo
float	incX = 0.0f,
		incY = 0.0f,
		incZ = 0.0f,
		giroMariposaInc = 0.0f,
		rotAlas1Inc = 0.0f,
		rotAlas2Inc = 0,
		rotInc = 0.0f,
		rotInc2 = 0.0f,
		brazoDerInc = 0.0f,
		brazoIzqInc = 0.0f,
		cabezaInc; //Para calculo del incremento 

#define MAX_FRAMES 9 //tamaño del arrgelo de frames (el máximo que podremos ocupar)
int i_max_steps = 60;
int i_curr_steps = 0;
typedef struct _frame
{
	//Variables para GUARDAR Key Frames
	float posX;		//Variable para PosicionX
	float posY;		//Variable para PosicionY
	float posZ;		//Variable para PosicionZ

	float rotRodIzq;
	float rotRodDer;

	float giroMariposa;

	float giroBrazoDer;
	float giroBrazoIzq;

	float cabezaRot;

	/*Mariposa*/

	float rotAlas1,
		rotAlas2;

}FRAME;

FRAME KeyFrame[MAX_FRAMES];
int FrameIndex = 7;			//introducir número en caso de tener Key guardados
bool play = false;
int playIndex = 0;

void saveFrame(void)
{
	//printf("frameindex %d\n", FrameIndex);
	//std::cout << "Frame Index = " << FrameIndex << std::endl;
//
	//KeyFrame[FrameIndex].posX = posX;
	//KeyFrame[FrameIndex].posY = posY;
	//KeyFrame[FrameIndex].posZ = posZ;
//
	//KeyFrame[FrameIndex].rotRodIzq = rotRodIzq;
	//KeyFrame[FrameIndex].rotRodDer = rotRodDer;
//
	//KeyFrame[FrameIndex].giroMariposa = giroMariposa;
//
	//KeyFrame[FrameIndex].rotAlas1 = rotAlas2;
//
	//KeyFrame[FrameIndex].giroBrazoDer = giroBrazoDer;
	//KeyFrame[FrameIndex].giroBrazoIzq = giroBrazoIzq;
//
	//KeyFrame[FrameIndex].cabezaRot = cabezaRot;
//
	//FrameIndex++;
}

void resetElements(void)
{
	//posX = KeyFrame[0].posX;
	//posY = KeyFrame[0].posY;
	//posZ = KeyFrame[0].posZ;
//
	//rotRodIzq = KeyFrame[0].rotRodIzq;
	//rotRodDer = KeyFrame[0].rotRodDer;
//
	//giroMariposa = KeyFrame[0].giroMariposa;
	//rotAlas1 = KeyFrame[0].rotAlas1;
	//rotAlas2= KeyFrame[0].rotAlas2;
//
	//giroBrazoDer = KeyFrame[0].giroBrazoDer;
	//giroBrazoIzq = KeyFrame[0].giroBrazoIzq;
//
	//cabezaRot = KeyFrame[0].cabezaRot;

}

void interpolation(void)
{
	incX = (KeyFrame[playIndex + 1].posX - KeyFrame[playIndex].posX) / i_max_steps;
	incY = (KeyFrame[playIndex + 1].posY - KeyFrame[playIndex].posY) / i_max_steps;
	incZ = (KeyFrame[playIndex + 1].posZ - KeyFrame[playIndex].posZ) / i_max_steps;

	rotInc = (KeyFrame[playIndex + 1].rotRodIzq - KeyFrame[playIndex].rotRodIzq) / i_max_steps;
	rotInc2 = (KeyFrame[playIndex + 1].rotRodDer - KeyFrame[playIndex].rotRodDer) / i_max_steps;

	//giroMonitoInc = (KeyFrame[playIndex + 1].giroMonito - KeyFrame[playIndex].giroMonito) / i_max_steps;

	brazoDerInc = (KeyFrame[playIndex + 1].giroBrazoDer - KeyFrame[playIndex].giroBrazoDer) / i_max_steps;
	brazoIzqInc = (KeyFrame[playIndex + 1].giroBrazoIzq - KeyFrame[playIndex].giroBrazoIzq) / i_max_steps;

	cabezaInc = (KeyFrame[playIndex + 1].cabezaRot - KeyFrame[playIndex].cabezaRot) / i_max_steps;
}

void animate(void)
{
	lightPosition.x = 300.0f * sin(myVar);
	lightPosition.z = 300.0f * cos(myVar);
	myVar += 0.01f;

	cont += 1;
	if (prendida == 1 && (cont % 250) == 0) {
		cont = 0;
		elegirColor += 1;

		//Día (naranja)
		if (elegirColor == 1){
			varColorR = 1.0f;
			varColorG = 0.3f;
			varColorB = 0.0f;
			noche = false;
		}
		else if (elegirColor == 2) {
			varColorR = 0.95f;
			varColorG = 0.15f;
			varColorB = 0.3f;
		}
		//atardecer (rosa)
		else if (elegirColor == 3) {
			varColorR = 0.9f;
			varColorG = 0.0f;
			varColorB = 0.6f;
		}
		else if (elegirColor == 4) {
			noche = true;
			varColorR = 0.55f;
			varColorG = 0.0f;
			varColorB = 0.4f;

		}
		//noche (morado)
		else if (elegirColor == 5) {
			varColorR = 0.1f;
			varColorG = 0.0f;
			varColorB = 0.25f;
			elegirColor = 0;
		}
	}

	if (play)
	{
		if (i_curr_steps >= i_max_steps) //end of animation between frames?
		{
			playIndex++;
			if (playIndex > FrameIndex - 2)	//end of total animation?
			{
				std::cout << "Animation ended" << std::endl;
				//printf("termina anim\n");
				playIndex = 0;
				play = false;
			}
			else //Next frame interpolations
			{
				i_curr_steps = 0; //Reset counter
								  //Interpolation
				interpolation();
			}
		}
		else
		{
			//Draw animation
			posX += incX;
			posY += incY;
			posZ += incZ;

			rotRodIzq += rotInc;
			rotRodDer += rotInc2;

			giroMariposa += giroMariposaInc;

			rotAlas1 += rotAlas1Inc;
			rotAlas2 += rotAlas2Inc;

			giroBrazoDer += brazoDerInc;
			giroBrazoIzq += brazoIzqInc;

			cabezaRot += cabezaInc;

			i_curr_steps++;
		}
	}

//***************************************************
	//Animación de caminata de Pompompurin
//***************************************************
	//Este ciclo se activará con cualquiera de las 

	/*if (walkCycle) {
		for (int i = 0; i < 15; i++) {
			giroBrazoDer += 0.1;
			giroBrazoIzq -= 0.1;
		}
		for (int j = 0; j < 15; j++) {
			giroBrazoDer -= 0.1;
			giroBrazoIzq -= 0.1;
		}
		//giroBrazoIzq = 180.0f;
		//giroPiernaDer = 0.0f;
		//giroPiernaIzq = 0.0f;
	}*/
}

void getResolution()
{
	const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	SCR_WIDTH = mode->width;
	SCR_HEIGHT = (mode->height) - 80;
}


int main()
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);*/

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// glfw window creation
	// --------------------
	// --------------------
	monitors = glfwGetPrimaryMonitor();
	getResolution();

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "CGeIHC 20241", NULL, NULL);
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

	// tell GLFW to capture our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	//Casandra Itzel 
	// configure global opengl state
	// -----------------------------
	glEnable(GL_DEPTH_TEST);

	// build and compile shaders
	// -------------------------
	Shader staticShader("Shaders/shader_Lights.vs", "Shaders/shader_Lights_mod.fs");
	Shader skyboxShader("Shaders/skybox.vs", "Shaders/skybox.fs");
	Shader animShader("Shaders/anim.vs", "Shaders/anim.fs");

	vector<std::string> faces
	{
		"resources/skybox/2/der.jpg",
		"resources/skybox/2/izq.jpg",
		"resources/skybox/2/arriba.jpg",
		"resources/skybox/2/abajo.jpg",
		"resources/skybox/2/frente.jpg",
		"resources/skybox/2/atras.jpg"
	};

	vector<std::string> faces2
	{
		"resources/skybox/4/der.jpg",
		"resources/skybox/4/izq.jpg",
		"resources/skybox/4/arriba.jpg",
		"resources/skybox/4/abajo.jpg",
		"resources/skybox/4/frente.jpg",
		"resources/skybox/4/atras.jpg"
	};

	Skybox skybox = Skybox(faces);
	Skybox skybox2 = Skybox(faces2);

	// Shader configuration
	// --------------------
	skyboxShader.use();
	skyboxShader.setInt("skybox", 0);

	Model CajonPiso("resources/objects/CajonPiso/PisoCajon.obj");
	Model CoraRosita("resources/objects/CoraRosita/cora.obj");
	Model Cajon("resources/objects/Cajon/Cajon.obj");
	Model Bumper("resources/objects/bumper/bumperNaranjita.obj");
	Model Pared("resources/objects/Pared/Pared.obj");
	Model Barrera1("resources/objects/Barrera1/Barrera1.obj");
	Model Barrera2("resources/objects/Barrera2/Barrera2.obj");
	Model PlataformaPiso("resources/objects/PlataformaPiso/PlataformaPiso.obj");
	Model Plataforma("resources/objects/Plataforma/Plataforma.obj");
	Model Flipper("resources/objects/Flipper/Flipper.obj");

	Model piso("resources/objects/piso/piso.obj");

	//Carga de secciones de Pompompurin
	Model piernaDer("resources/objects/Pompompurin/piernader.obj");
	Model piernaIzq("resources/objects/Pompompurin/piernader.obj");
	Model torso("resources/objects/Pompompurin/torso.obj");
	Model brazoDer("resources/objects/Pompompurin/brazoder.obj");
	Model brazoIzq("resources/objects/Pompompurin/brazoizq.obj");

	//Inicialización de KeyFrames
	for (int i = 0; i < MAX_FRAMES; i++)
	{
		KeyFrame[0].posX = 0;
		KeyFrame[0].posY = 0;
		KeyFrame[0].posZ = 0;
		KeyFrame[0].rotAlas1 = 0;
		KeyFrame[0].rotAlas2 = 0;
		KeyFrame[0].giroMariposa = 0;

		KeyFrame[1].posX = 0;
		KeyFrame[1].posY = 10;
		KeyFrame[1].posZ = -27;
		KeyFrame[1].rotAlas1 = -100;
		KeyFrame[1].rotAlas2 = 100;
		KeyFrame[1].giroMariposa = -45;

		KeyFrame[2].posX = 0;
		KeyFrame[2].posY = 10;
		KeyFrame[2].posZ = -55;
		KeyFrame[2].rotAlas1 = 0;
		KeyFrame[2].rotAlas2 = 0;
		KeyFrame[2].giroMariposa = -90;

		KeyFrame[3].posX = -20;
		KeyFrame[3].posY = 5;
		KeyFrame[3].posZ = -55;
		KeyFrame[3].rotAlas1 = -100;
		KeyFrame[3].rotAlas2 = 100;
		KeyFrame[3].giroMariposa = -45;

		KeyFrame[4].posX = -40;
		KeyFrame[4].posY = 5;
		KeyFrame[4].posZ = -55;
		KeyFrame[4].rotAlas1 = 0;
		KeyFrame[4].rotAlas2 = 0;
		KeyFrame[4].giroMariposa = 0;

		KeyFrame[5].posX = -40;
		KeyFrame[5].posY = 0;
		KeyFrame[5].posZ = -27;
		KeyFrame[5].rotAlas1 = -100;
		KeyFrame[5].rotAlas2 = 100;
		KeyFrame[5].giroMariposa = 30;

		KeyFrame[6].posX = 0;
		KeyFrame[6].posY = 0;
		KeyFrame[6].posZ = 0;
		KeyFrame[6].rotAlas1 = 0;
		KeyFrame[6].rotAlas2 = 0;
		KeyFrame[6].giroMariposa = 60;

	}

	// draw in wireframe
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		//if(elegirColor==1)


		skyboxShader.setInt("skybox", 0);

		// per-frame time logic
		// --------------------
		lastFrame = SDL_GetTicks();

		// input
		// -----
		//my_input(window);
		prendida = 1;
		animate();

		// render
		// ------
		glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// don't forget to enable shader before setting uniforms
		staticShader.use();

		//Día y noche
		staticShader.setVec3("viewPos", camera.Position);
		staticShader.setVec3("dirLight.direction", lightDirection);
		staticShader.setVec3("dirLight.ambient", glm::vec3(varColorR, varColorG, varColorB)); //afecta a todo
		staticShader.setVec3("dirLight.diffuse", glm::vec3(0.1f, 0.05f, 0.05f)); //afecta a ciertas caras
		staticShader.setVec3("dirLight.specular", glm::vec3(0.1f, 0.05f, 0.05f)); //afecta el brillo que reflejan los objetos

		staticShader.setVec3("pointLight[0].position", glm::vec3(-200.0f, 14.0f, -80.0f));
		staticShader.setVec3("pointLight[0].ambient", glm::vec3(0.2f, 0.2f, 0.0f));
		staticShader.setVec3("pointLight[0].diffuse", glm::vec3(0.8f, 0.7f, 0.5f));
		staticShader.setVec3("pointLight[0].specular", glm::vec3(0.2f, 0.2f, 0.0f));
		staticShader.setFloat("pointLight[0].constant", 0.08f); //distancia
		staticShader.setFloat("pointLight[0].linear", 0.00001f); //distancia (entre más chico más viaja)
		staticShader.setFloat("pointLight[0].quadratic", 0.0006f); //entre más chico menos atenúa (mayor luz)

		staticShader.setVec3("pointLight[1].position", glm::vec3(-80.0, 0.0f, 0.0f));
		staticShader.setVec3("pointLight[1].ambient", glm::vec3(0.0f, 0.6f, 0.0f));
		staticShader.setVec3("pointLight[1].diffuse", glm::vec3(0.0f, 0.7f, 0.0f));
		staticShader.setVec3("pointLight[1].specular", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setFloat("pointLight[1].constant", 1.0f);
		staticShader.setFloat("pointLight[1].linear", 0.0009f);
		staticShader.setFloat("pointLight[1].quadratic", 0.0032f);

		//Luz de día
		staticShader.setVec3("pointLight[2].position", glm::vec3(0.0f, 1.0f, 0.0f));
		staticShader.setVec3("pointLight[2].ambient", glm::vec3(varColorR, varColorG, varColorB));
		staticShader.setVec3("pointLight[2].diffuse", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setVec3("pointLight[2].specular", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setFloat("pointLight[2].constant", 1.0f);
		staticShader.setFloat("pointLight[2].linear", 1.0f);
		staticShader.setFloat("pointLight[2].quadratic", 1.0f);

		//Luz de noche
		/*staticShader.setVec3("pointLight[3].position", glm::vec3(0.0f, 1.0f, 0.0f));
		staticShader.setVec3("pointLight[3].ambient", glm::vec3(varColorR2, varColorG2, varColorB2));
		staticShader.setVec3("pointLight[3].diffuse", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setVec3("pointLight[3].specular", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setFloat("pointLight[3].constant", 1.0f);
		staticShader.setFloat("pointLight[3].linear", 1.0f);
		staticShader.setFloat("pointLight[3].quadratic", 1.0f);*/

		staticShader.setVec3("spotLight[0].position", glm::vec3(0.0f, 0.5f, 0.0f));
		staticShader.setVec3("spotLight[0].direction", glm::vec3(0.0f, 0.0f, -1.0));//
		staticShader.setVec3("spotLight[0].ambient", glm::vec3(1.0f, 0.3f, 0.3f));
		staticShader.setVec3("spotLight[0].diffuse", glm::vec3(0.9f, 0.9f, 0.9f));
		staticShader.setVec3("spotLight[0].specular", glm::vec3(0.9f, 0.0f, 0.0f));
		staticShader.setFloat("spotLight[0].cutOff", glm::cos(glm::radians(5.0f))); //radio del circulo de luz directa
		staticShader.setFloat("spotLight[0].outerCutOff", glm::cos(glm::radians(30.0f))); //radio del circulo de luz extra
		staticShader.setFloat("spotLight[0].constant", 1.0f);
		staticShader.setFloat("spotLight[0].linear", 0.0009f);
		staticShader.setFloat("spotLight[0].quadratic", 0.0032f);

		/*staticShader.setVec3("spotLight[1].position", glm::vec3(-200.0f, 25.0f, -290.0f));
		staticShader.setVec3("spotLight[1].direction", glm::vec3(camera.Front.x, camera.Front.y, camera.Front.z));
		staticShader.setVec3("spotLight[1].ambient", glm::vec3(0.3f, 0.3f, 0.3f));
		staticShader.setVec3("spotLight[1].diffuse", glm::vec3(0.9f, 0.9f, 0.9f));
		staticShader.setVec3("spotLight[1].specular", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setFloat("spotLight[1].cutOff", glm::cos(glm::radians(5.0f))); //radio del circulo de luz directa
		staticShader.setFloat("spotLight[1].outerCutOff", glm::cos(glm::radians(30.0f))); //radio del circulo de luz extra
		staticShader.setFloat("spotLight[1].constant", 0.01f);
		staticShader.setFloat("spotLight[1].linear", 0.9f);
		staticShader.setFloat("spotLight[1].quadratic", 0.5f);*/

		/*staticShader.setVec3("spotLight[0].position", glm::vec3(camera.Position.x, camera.Position.y, camera.Position.z));
		staticShader.setVec3("spotLight[0].direction", glm::vec3(camera.Front.x, camera.Front.y, camera.Front.z));
		staticShader.setVec3("spotLight[0].ambient", glm::vec3(0.3f, 0.3f, 0.3f));
		staticShader.setVec3("spotLight[0].diffuse", glm::vec3(0.9f, 0.9f, 0.9f));
		staticShader.setVec3("spotLight[0].specular", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setFloat("spotLight[0].cutOff", glm::cos(glm::radians(5.0f))); //radio del circulo de luz directa
		staticShader.setFloat("spotLight[0].outerCutOff", glm::cos(glm::radians(30.0f))); //radio del circulo de luz extra
		staticShader.setFloat("spotLight[0].constant", 0.01f);
		staticShader.setFloat("spotLight[0].linear", 0.9f);
		staticShader.setFloat("spotLight[0].quadratic", 0.5f);*/

		staticShader.setFloat("material_shininess", 32.0f);

		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 tmp = glm::mat4(1.0f);
		// view/projection transformations
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 10000.0f);
		glm::mat4 view = camera.GetViewMatrix();
		staticShader.setMat4("projection", projection);
		staticShader.setMat4("view", view);

		// -------------------------------------------------------------------------------------------------------------------------
		// Personaje Animacion
		// -------------------------------------------------------------------------------------------------------------------------
		//Remember to activate the shader with the animation
		animShader.use();
		animShader.setMat4("projection", projection);
		animShader.setMat4("view", view);

		animShader.setVec3("material.specular", glm::vec3(0.5f));
		animShader.setFloat("material.shininess", 32.0f);
		animShader.setVec3("light.ambient", ambientColor);
		animShader.setVec3("light.diffuse", diffuseColor);
		animShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);
		animShader.setVec3("light.direction", lightDirection);
		animShader.setVec3("viewPos", camera.Position);

		// -------------------------------------------------------------------------------------------------------------------------
		// Escenario
		// -------------------------------------------------------------------------------------------------------------------------
		staticShader.use();
		staticShader.setMat4("projection", projection);
		staticShader.setMat4("view", view);

		/*model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, -21.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.002f));
		staticShader.setMat4("model", model);
		piso.Draw(staticShader);*/

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(10.0f));
		staticShader.setMat4("model", model);
		Cajon.Draw(staticShader);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.05f, 0.0f));
		model = glm::scale(model, glm::vec3(10.0f));
		staticShader.setMat4("model", model);
		CajonPiso.Draw(staticShader);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(10.0f));
		staticShader.setMat4("model", model);
		CoraRosita.Draw(staticShader);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(10.0f));
		staticShader.setMat4("model", model);
		Bumper.Draw(staticShader);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(10.0f));
		staticShader.setMat4("model", model);
		Pared.Draw(staticShader);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		tmp = model = glm::scale(model, glm::vec3(10.0f));
		staticShader.setMat4("model", model);
		Barrera1.Draw(staticShader);

		model = glm::mat4(tmp);
		model = glm::translate(model, glm::vec3(-0.05f, 0.39f, 0.01f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0));
		staticShader.setMat4("model", model);
		Barrera1.Draw(staticShader);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(10.0f));
		staticShader.setMat4("model", model);
		Barrera2.Draw(staticShader);

		model = glm::mat4(tmp);
		model = glm::translate(model, glm::vec3(-0.05f, 0.39f, 0.02f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0));
		staticShader.setMat4("model", model);
		Barrera2.Draw(staticShader);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(10.0f));
		staticShader.setMat4("model", model);
		Plataforma.Draw(staticShader);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(10.0f));
		staticShader.setMat4("model", model);
		PlataformaPiso.Draw(staticShader);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-0.25f, 1.9f, 2.8f));
		model = glm::rotate(model, glm::radians(flipper1), glm::vec3(0.0f, 1.0f, 0.0));
		model = glm::scale(model, glm::vec3(9.5f));
		staticShader.setMat4("model", model);
		Flipper.Draw(staticShader);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-0.95f, 1.9f, 5.8f));
		model = glm::rotate(model, glm::radians(10 + flipper2), glm::vec3(0.0f, 1.0f, 0.0));
		model = glm::scale(model, glm::vec3(9.5f));
		staticShader.setMat4("model", model);
		Flipper.Draw(staticShader);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.42f, 1.9f, 5.8f));
		model = glm::rotate(model, glm::radians(-115 + flipper3), glm::vec3(0.0f, 1.0f, 0.0));
		model = glm::scale(model, glm::vec3(9.5f));
		staticShader.setMat4("model", model);
		Flipper.Draw(staticShader);








		//***************************************************
		//VALORES DE POSICIÓN Y ANIMACIÓN DE POMPOMPURIN
		//***************************************************

		model = glm::translate(glm::mat4(1.0f), glm::vec3(0, 1.705, 0));
		model = glm::translate(model, glm::vec3(posX, posY, posZ));
		//model = glm::translate(model, glm::vec3(0,0,0));Puede que esta línea no sea importante para la posición de Pompompurin
		model = glm::scale(model, glm::vec3(0.075f));
		//La variable orienta se encarga de girar a Pompompurin, para que rote de izquierda a derecha, se hace en referencia al eje Y
		tmp = model = glm::rotate(model, glm::radians(orienta), glm::vec3(0.0f, 1.0f, 0.0));
		staticShader.setMat4("model", model);
		torso.Draw(staticShader);

				//Pierna Der
		model = glm::scale(tmp, glm::vec3(1.4f));
		model = glm::translate(tmp, glm::vec3(1.0f, 2.8f, -1.0f));
		model = glm::rotate(model, glm::radians(180 + giroPiernaDer), glm::vec3(1.0f, 0.0f, 0.0));
		staticShader.setMat4("model", model);
		piernaDer.Draw(staticShader);

				//Pierna Izq
		model = glm::scale(tmp, glm::vec3(1.4f));
		model = glm::translate(tmp, glm::vec3(0.0f, 2.8f, -1.0f));
		model = glm::rotate(model, glm::radians(180 - giroPiernaDer), glm::vec3(1.0f, 0.0f, 0.0));
		staticShader.setMat4("model", model);
		piernaIzq.Draw(staticShader);

				//Brazo Der
		model = glm::translate(tmp, glm::vec3(-2.8f, 3.0f, -1.0f));
		model = glm::translate(model, glm::vec3(-0.75f, 2.75f, 0));
		model = glm::rotate(model, glm::radians(giroBrazoDer), glm::vec3(1.0f, 0.f, 0.0f));
		staticShader.setMat4("model", model);
		brazoDer.Draw(staticShader);

			//Brazo Izq
		model = glm::translate(tmp, glm::vec3(2.8f, 3.0f, -1.0f));
		model = glm::translate(model, glm::vec3(0.75f, 2.75f, 0));
		model = glm::rotate(model, glm::radians(-giroBrazoDer), glm::vec3(1.0f, 0.0f, 0.0f)); //Hacemos que el giro dependa de la variable declarada para el giro
		staticShader.setMat4("model", model);
		brazoIzq.Draw(staticShader);



		//-------------------------------------------------------------------------------------
		// draw skybox as last
		// -------------------
		if (noche) {
			skyboxShader.use();
			skybox2.Draw(skyboxShader, view, projection, camera);
		}
		else {
			skyboxShader.use();
			skybox.Draw(skyboxShader, view, projection, camera);
		}

		// Limitar el framerate a 60
		deltaTime = SDL_GetTicks() - lastFrame; // time for full 1 loop
		//std::cout <<"frame time = " << frameTime << " milli sec"<< std::endl;
		if (deltaTime < LOOP_TIME)
		{
			SDL_Delay((int)(LOOP_TIME - deltaTime));
		}

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	skybox.Terminate();

	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void my_input(GLFWwindow *window, int key, int scancode, int action, int mode)
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
	//To Configure Model
	//if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS)
	//	posZ++;
	//if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS)
	//	posZ--;
	//if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
	//	posX--;
	//if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
	//	posX++;
	//if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)
	//	posY++;
	//if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
	//	posY--;

	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS && flipper1 < 55)
		flipper1 += 65;
	else flipper1 = 0;
	if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS && flipper2 < 55)
		flipper2 += 55;
	else flipper2 = 0;
	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS && flipper3 > -55)
		flipper3 -= 55;
	else flipper3 = 0;


	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) {
		rotAlas1--;
		rotAlas2++;
	}
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		cabezaRot--;
	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) {
		rotRodIzq++;
		rotRodDer--;
	}
	if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS)
		giroMariposa--;
	if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS)
		giroMariposa++;
	if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
		lightPosition.x++;
	if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS)
		lightPosition.x--;

	//***************************************************
	//Activación del ciclo de animación de Pompompurin
	//***************************************************
	//Al presionar cualquiera de las teclas direccionales, se activará la función "walkCycle"
	//para hacer que los brazos y piernas del personaje comiencen a moverse.
	if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) {
		posZ += 0.05;

		cont1 += 1;
		if (cont1 >= 15) {
			regresoWalkCycle = !regresoWalkCycle;
			cont1 = 0;
		}
		if (regresoWalkCycle == true) {
			giroPiernaDer += 1.5;
			giroBrazoDer += 1.5;
		}
		else {
			giroPiernaDer -= 1.5;
			giroBrazoDer -= 1.5;
		}
	}

	if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS) {
		posZ -= 0.05;

		cont1 += 1;
		if (cont1 >= 15) {
			regresoWalkCycle = !regresoWalkCycle;
			cont1 = 0;
		}
		if (regresoWalkCycle == true) {
			giroPiernaDer += 1.5;
			giroBrazoDer += 1.5;
		}
		else {
			giroPiernaDer -= 1.5;
			giroBrazoDer -= 1.5;
		}
	}

	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
		walkCycle = true;
		std::cout << "walkCycle F = " << walkCycle << std::endl;
		posX -= 0.1;
	}else{
		walkCycle = false;
	}

	

	if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS) {
		walkCycle = true;
		std::cout << "walkCycle H = " << walkCycle << std::endl;
		posX += 0.1;
	}else{
		walkCycle = false;
	}

	//To play KeyFrame animation 
	if (key == GLFW_KEY_P && action == GLFW_PRESS)
	{
		if (play == false && (FrameIndex > 1))
		{
			std::cout << "Play animation" << std::endl;
			resetElements();
			//First Interpolation				
			interpolation();

			play = true;
			playIndex = 0;
			i_curr_steps = 0;
		}
		else
		{
			play = false;
			std::cout << "Not enough Key Frames" << std::endl;
		}
	}

	//To Save a KeyFrame
	/*if (key == GLFW_KEY_L && action == GLFW_PRESS)
	{
		if (FrameIndex < MAX_FRAMES)
		{
			saveFrame();
		}
	}*/

	//Prender Luz
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
		varColorR = 0.9f;
		varColorG = 0.9f;
		varColorB = 0.9f;
		prendida = 1;
	}

	//if (key == GLFW_KEY_2 && action == GLFW_PRESS) {
	//	movAuto_z = 0.0f;
	//	movAuto_z = 0.0f;
	//}
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}
// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}