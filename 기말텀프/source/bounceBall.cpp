//실습20 :파묻혀도 됨
#define _CRT_SECURE_NO_WARNINGS
#include "stdafx.h"
#include "ProjectLibrary.h"

using namespace TestNameSpace;

GLfloat xRotated, yRotated, zRotated;
GLdouble radius = 2;
GLfloat qaBlack[] = { 0.0, 0.0, 0.0, 1.0 }; //Black Color
GLfloat qaGreen[] = { 0.0, 1.0, 0.0, 1.0 }; //Green Color
GLfloat qaWhite[] = { 1.0, 1.0, 1.0, 1.0 }; //White Color
GLfloat qaRed[] = { 1.0, 0.0, 0.0, 1.0 }; //White Color

										  // Set lighting intensity and color
GLfloat qaAmbientLight[] = { 0.1, 0.1, 0.1, 1.0 };
GLfloat qaDiffuseLight[] = { 1, 1, 1, 1.0 };
GLfloat qaSpecularLight[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat emitLight[] = { 0.9, 0.9, 0.9, 0.01 };
GLfloat Noemit[] = { 0.0, 0.0, 0.0, 1.0 };
// Light source position
GLfloat qaLightPosition[] = { 0, 1500, 100, 1 };


GLfloat qaSpotLightPosition[] = { 0.0, 100.0, 0.0, 1.0 };
GLfloat qaSpotLightDirection[3] = { 0, -1.0f, 0.0f };
GLfloat spotLightDegree = { 50 };
GLfloat spotLightExponent = { 0 };




MasterMatrix* masterMatrix2 = new MasterMatrix();
RectangularClock *rectangularClock = new RectangularClock();


MasterMatrix* masterMatrix = new MasterMatrix();

void display(void);
void reshape(int x, int y);
void TimerFunc(int);
void Start();
void Mouse(int button, int state, int x, int y);
void MouseWheel(int button, int state, int x, int y);
void MouseDrag(int x, int y);
void Keyboard(unsigned char key, int x, int y);
void KeyboardUp(unsigned char key, int x, int y);
bool LiangBarsky(double edgeLeft, double edgeRight, double edgeBottom, double edgeTop,   // Define the x/y clipping values for the border.
	double x0src, double y0src, double x1src, double y1src,                 // Define the start and end points of the line.
	double &x0clip, double &y0clip, double &x1clip, double &y1clip);         // The output values, so declare these outside.



void ApplyRotate();
void LoadResource();
void LoadStage(int num);
int GetCurrentNumberOfStar();
void DrawSlash(float size);
bool CheckStageCleared();
void TitleAnimation();


GLVector3 CardinalSplineAnimation(GLVector3 vector1, GLVector3 vector2);



//declare like this to create object.and use pointer
//GLint cubeList[10];

GLdouble sample2[16]

{
	1,0,0,0,
	0,1,0,0,
	0,0,1,0,
	-85,190,0,1
};
GLdouble sample3[16]

{
	1,0,0,0,
	0,1,0,0,
	0,0,1,0,
	-100,190,0,1
};


GLdouble sample4[16]

{
	1,0,0,0,
	0,1,0,0,
	0,0,1,0,
	-130,190,0,1
};
GLdouble sample5[16]

{
	1,0,0,0,
	0,1,0,0,
	0,0,1,0,
	-145,190,0,1
};






GLdouble sample[16]

{
	1,0,0,0,
	0,1,0,0,
	0,0,1,0,
	0,0,0,1
};
GLdouble rotateMatrix[12]
{
	0,0,0,0,
	0,0,0,0,
	0,0,0,0

};
GLdouble scaleMatrix[3]
{
	1,1,1

};



enum SimpleGameState
{
	LogoState,
	TitleState,
	InGameState,
	GameOverState


};


//철,아이스,뽁뽁이,야스오,오리,전기,초원,달,눈,물

LPCSTR soundFileName[]
{

	"wavFile/metal.wav",
	"wavFile/ice.wav",
	"wavFile/aircap.wav",
	"wavFile/yasuo1.wav",
	"wavFile/duck.wav",
	"wavFile/electricity.wav",
	"wavFile/grass.wav",
	"wavFile/moon.wav",
	"wavFile/snow.wav",
	"wavFile/water.wav",
	"wavFile/yasuo2.wav",
	"wavFile/line.wav",
	"wavFile/warp.wav",
	"wavFile/youtubeADLogo.wav"


};


LPCSTR musicFileName[]
{

	"open \"mp3/LCK BGM.mp3\" type mpegvideo alias mp3",
	"open \"mp3/ice_bgm.mp3\" type mpegvideo alias mp3",
	"open \"mp3/aircap_bgm.mp3\" type mpegvideo alias mp3",
	"open \"mp3/Initial D - Deja Vu.mp3\" type mpegvideo alias mp3",
	"open \"mp3/duck_bgm.mp3\" type mpegvideo alias mp3",
	"open \"mp3/electricity_bgm.mp3\" type mpegvideo alias mp3",
	"open \"mp3/grass_bgm.mp3\" type mpegvideo alias mp3",
	"open \"mp3/moon_bgm.mp3\" type mpegvideo alias mp3",
	"open \"mp3/snow_bgm.mp3\" type mpegvideo alias mp3",
	"open \"mp3/water_bgm.mp3\" type mpegvideo alias mp3",
	"open \"mp3/yasuo_bgm.mp3\" type mpegvideo alias mp3"


};




struct StageProperty
{

	GLVector3 startPoint = GLVector3(0, 100, 0);
	GLVector3 deathPoint = GLVector3(0, -2000, 0);
	int numberOfStar = 0;
	int starCount = 0;

	int textureIndex = 0;



};


bool useHighLight = false;
bool useBaseLight = true;
bool quadOrSphereMap = true;
int stageLimit = 10;

std::vector<StageProperty> stagePropertyVector;
StageProperty stageProperty[50];
int currentStageIndex = 0;


SimpleGameState simpleGameState = LogoState;


OrthoData viewportData;





//
//
//only for temporary




Polygon0 *testYo = new Polygon0(masterMatrix);

Polygon0 *testClass = new Polygon0(masterMatrix);
Polygon0 *testClass2 = new Polygon0(masterMatrix);
BounceBall *bounceBall = new BounceBall(masterMatrix);
Polygon0 *backgroundCube = new Polygon0(masterMatrix);

ChulbongPeople *chulbongPeople = new ChulbongPeople(masterMatrix);


//월드에 종속되지 않고 화면 그자체에 종속됨
ScoreUI *scoreUI = new ScoreUI();
LogoScreen *blackScreen = new LogoScreen();
LogoScreen *logoScreen = new LogoScreen();
TitleScreen *titleScreen = new TitleScreen();
TitleScreen *startButton = new TitleScreen();
TitleScreen *quitButton = new TitleScreen();
TitleScreen *cursor = new TitleScreen();


int titleCursorPosition = 1;


Polygon0 *slash = new Polygon0();




std::vector<Polygon0> cubes;
std::vector<Polygon0> stars;

struct CollisionData
{
	double leftX;
	double topZ;
	double rightX;
	double bottomZ;

	GLVector3 position;

};

struct POINT3D
{
	double x, y, z;
};
POINT3D map_1[237];
POINT3D star_1[237];
int map1_index, star1_index;


double color4[4]
{
	1,1,1,1
};

int viewDegree = 0;


GLubyte * LoadDIBitmap(const char *filename, BITMAPINFO **info);
std::vector<BITMAPINFO*> m_bitInfo;   // 비트맵 헤더 저장할 변수
std::vector<GLubyte*> m_bitmap;   // 비트맵 데이터를 가리킬 포인터
std::vector<GLuint> texture;


std::vector<BITMAPINFO*> backgroundBitmapInfo;   // 비트맵 헤더 저장할 변수
std::vector<GLubyte*> backgroundBitmapData;   // 비트맵 데이터를 가리킬 포인터
std::vector<GLuint> backgroundBitmapTexture;


std::vector<BITMAPINFO*> backgroundBitmapInfo2;   // 비트맵 헤더 저장할 변수
std::vector<GLubyte*> backgroundBitmapData2;   // 비트맵 데이터를 가리킬 포인터
std::vector<GLuint> backgroundBitmapTexture2;


std::vector<BITMAPINFO*> uIBitmapInfo;   // 비트맵 헤더 저장할 변수
std::vector<GLubyte*> uIBitmapData;   // 비트맵 데이터를 가리킬 포인터
std::vector<GLuint> uIBitmapTexture;





void SetCameraOnBounceBall();
void LogoAnimation();


LightSource *lightSource = new LightSource(masterMatrix);

bool CollisionCheck(CollisionData collisionData1, CollisionData collisionData2);

void idleFunc(void)
{
	if (zRotated > 360.0)
	{
		zRotated -= 360.0*floor(zRotated / 360.0);   // Don't allow overflow
	}

	if (yRotated > 360.0)
	{
		yRotated -= 360.0*floor(yRotated / 360.0);   // Don't allow overflow
	}

	if (xRotated > 360.0)
	{
		xRotated -= 360.0*floor(xRotated / 360.0);   // Don't allow overflow
	}
	//zRotated += 0.01;
	//yRotated += 0.01;
	display();

}
void initLighting()
{

	// Enable lighting
	glEnable(GL_LIGHTING);

	//중앙 조명
	if (useBaseLight)
	{
		glEnable(GL_LIGHT3);
	}
	else
	{
		glDisable(GL_LIGHT3);
	}
	//하이라이트

	if (useHighLight)
	{
		glEnable(GL_LIGHT4);
	}

	else
	{
		glDisable(GL_LIGHT4);

	}

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, qaAmbientLight);
	glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, 0.0);
	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, 0.0);


	//핵심코드
	// Set lighting intensity and color
	glLightfv(GL_LIGHT3, GL_AMBIENT, qaAmbientLight);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, qaDiffuseLight);
	glLightfv(GL_LIGHT3, GL_SPECULAR, qaSpecularLight);

	qaSpotLightPosition[0] = bounceBall->Position().x;
	qaSpotLightPosition[1] = bounceBall->Position().y + 100;
	qaSpotLightPosition[2] = bounceBall->Position().z;
	qaSpotLightPosition[3] = 1;


	glLightfv(GL_LIGHT4, GL_AMBIENT, qaAmbientLight);
	glLightfv(GL_LIGHT4, GL_DIFFUSE, qaDiffuseLight);
	glLightfv(GL_LIGHT4, GL_SPECULAR, qaSpecularLight);


	glLightfv(GL_LIGHT4, GL_POSITION, qaSpotLightPosition);
	glLightfv(GL_LIGHT4 , GL_SPOT_DIRECTION, qaSpotLightDirection);
	glLightf(GL_LIGHT4, GL_SPOT_CUTOFF, spotLightDegree);
	glLightf(GL_LIGHT4 , GL_SPOT_EXPONENT, spotLightExponent);


	// Set the light position
	glLightfv(GL_LIGHT3, GL_POSITION, qaLightPosition);
	
	glEnable(GL_DEPTH_TEST);
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1000, 1000);
	glutCreateWindow("glutBase");
	initLighting();

	xRotated = yRotated = zRotated = 0.0;

	//glutIdleFunc(idleFunc);
	glutTimerFunc(100, TimerFunc, 1);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	glutMouseFunc(Mouse);
	glutMouseWheelFunc(MouseWheel);
	glutMotionFunc(MouseDrag);
	glutKeyboardFunc(Keyboard);
	glutKeyboardUpFunc(KeyboardUp);
	Start();
	glutMainLoop();
	return 0;
}

void display(void)
{

	if (simpleGameState == InGameState)
	{


		initLighting();

		static int temps = 0;

		glMatrixMode(GL_MODELVIEW);
		// clear the drawing buffer.
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



		//glEnable(GL_CULL_FACE_MODE);



		//glCullFace(GL_BACK);


		// clear the identity matrix.
		masterMatrix->glLoadMasterMatrix();



		masterMatrix->glSetMasterMatrix(sample, rotateMatrix, scaleMatrix);

		//testClass->DrawXYZLine(viewportData.width, false, false);




		bounceBall->AllProcess();
		lightSource->DrawLightSource();


		DrawSlash(1);


		glColor4f(1, 1, 1, 1);
		glEnable(GL_TEXTURE_2D);
		for (int i = 0; i < map1_index; ++i)
		{
			cubes[i].DrawTextureCube(50, texture[currentStageIndex]);
		}
		glDisable(GL_LIGHTING);
		if (quadOrSphereMap)
		{
			backgroundCube->DrawTextureCube2(5000, 
				backgroundBitmapTexture[currentStageIndex],backgroundBitmapTexture2[currentStageIndex]);
		}
		else
		{
			backgroundCube->DrawTextureSphere(7500,30, backgroundBitmapTexture[currentStageIndex]);

		}
		glEnable(GL_LIGHTING);
		glDisable(GL_TEXTURE_2D);

		for (int i = 0; i < star1_index; ++i)
		{
			stars[i].DrawStar(50);
		}






		rectangularClock->RectangularClockNum(masterMatrix2, GetCurrentNumberOfStar() % 10, 2, sample4, true, color4);
		rectangularClock->RectangularClockNum(masterMatrix2, GetCurrentNumberOfStar() / 10, 2, sample5, true, color4);


		rectangularClock->RectangularClockNum(masterMatrix2, stageProperty[currentStageIndex].numberOfStar % 10, 2, sample2, true, color4);
		rectangularClock->RectangularClockNum(masterMatrix2, stageProperty[currentStageIndex].numberOfStar / 10, 2, sample3, true, color4);


		testClass2->DrawStar(100);
		testClass2->SetPosition(0, 500, 0);

		//disable culling
		//glDisable(GL_CULL_FACE);

	}


	else if (simpleGameState == LogoState)
	{
		glMatrixMode(GL_MODELVIEW);
		// clear the drawing buffer.
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		LogoAnimation();


	}

	else if (simpleGameState == TitleState)
	{

		glMatrixMode(GL_MODELVIEW);
		// clear the drawing buffer.
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);




		TitleAnimation();

	}

	else if (simpleGameState == GameOverState)
	{


	}


	glutSwapBuffers();
}

void reshape(int x, int y)
{

	if (y == 0 || x == 0) return;

	glViewport(0, 0, x, y);  //Use the whole window for rendering

	masterMatrix->glLoadMasterMatrix();

	viewportData.screenLTX = -x / 2;
	viewportData.screenRBX = x / 2;
	viewportData.screenRBY = -y / 2;
	viewportData.screenLTY = y / 2;
	viewportData.zNear = -800;
	viewportData.zFar = 800;
	viewportData.width = x;
	viewportData.height = y;
	viewportData.zSize = fabs(viewportData.zNear - viewportData.zFar);



	//glLoadIdentity();
	//glMatrixMode(GL_TEXTURE);
	//glMatrixMode(GL_PROJECTION);
	//gluLookAt(0, 0, 400, 0, 0, 0, 0, 1, 0);


}

void TimerFunc(int value)
{
	//printf("teapot : (%f,%f,%f)\n", teapot->Position().x, teapot->Position().y, teapot->Position().z);


	if (simpleGameState == InGameState)
	{

		static int dir = 1;

		static int temp = 0;

		static int fuel = 10;
		static int curFrame = 0;
		static int keyFrame = 60;

		static bool leftKeyPressed = false;
		static bool rightKeyPressed = false;
		static bool upKeyPressed = false;
		static bool downKeyPressed = false;
		static bool jumpKeyPressed = false;


		static bool sideCheck = false;

		GLVector3 tempVector3;

		/*

		masterMatrix->thisCamera.eyeX = masterMatrix->thisCamera.centerX;
		masterMatrix->thisCamera.eyeY = 1000;
		masterMatrix->thisCamera.eyeZ = masterMatrix->thisCamera.centerZ + 1000;

		masterMatrix->thisCamera.centerX = CardinalSplineAnimation(GLVector3(-300,100,200),GLVector3(100,0,-100)).x;
		masterMatrix->thisCamera.centerY = CardinalSplineAnimation(GLVector3(-300, 100, 200), GLVector3(100, 0, -100)).y;
		masterMatrix->thisCamera.centerZ = CardinalSplineAnimation(GLVector3(-300, 100, 200), GLVector3(100, 0, -100)).z;

		*/

		SetCameraOnBounceBall();

		if (GetAsyncKeyState(VK_ESCAPE))
		{

			simpleGameState = TitleState;
			currentStageIndex = 0;
			LoadStage(currentStageIndex);

		}


		if (GetAsyncKeyState(VK_LEFT))
		{


			leftKeyPressed = true;
		}


		else if (GetAsyncKeyState(VK_RIGHT))
		{

			rightKeyPressed = true;
		}

		if (GetAsyncKeyState(VK_UP))
		{

			upKeyPressed = true;
		}
		else if (GetAsyncKeyState(VK_DOWN))
		{

			downKeyPressed = true;
		}


		if (GetAsyncKeyState(VK_SPACE))
		{

			if (bounceBall->bounceBallProperty.landingActivate)
			{

				bounceBall->stateStack.push_back(BounceBall::SimpleState::SuperJumpup);
			}

		}
		if (GetAsyncKeyState(VK_F1))
		{

			bounceBall->bounceBallProperty.velocity.y += 2;

		}
		/*
		if (bounceBall->bounceBallProperty.landingActivate)
		{

			bounceBall->stateStack.push_back(BounceBall::SimpleState::SuperJumpup);
		}
		*/






		for (int i = 0; i < map1_index; ++i)
		{

			if (bounceBall->CollisionCheckOriginal(*bounceBall, cubes[i]))
			{


				bounceBall->bounceBallProperty.velocity.x -= bounceBall->bounceBallProperty.velocity.x;

				bounceBall->bounceBallProperty.velocity.z -= bounceBall->bounceBallProperty.velocity.z;

				temp += 1;
				if (bounceBall->CollisionCheckUpper(*bounceBall, cubes[i]))
				{

					bounceBall->bounceBallProperty.landingYPosition = cubes[i].GetCollisionBox3D().topY;
					bounceBall->bounceBallProperty.landingActivate = true;


					if (currentStageIndex == 3)
					{
						if (rand() % 2 == 1)
						{
							bounceBall->soundFileName = soundFileName[10];
						}
						else
						{
							bounceBall->soundFileName = soundFileName[currentStageIndex];
						}
					}


					temp += 1;

				}
			}

		}

		for (int i = 0; i < star1_index; ++i)
		{
			if (stars[i].objectActivate)
			{
				if (bounceBall->CollisionCheckOriginal(*bounceBall, stars[i]))
				{

					stars[i].objectActivate = false;
					PlaySoundA(soundFileName[11], NULL, SND_ASYNC);

				}
			}
		}



		if (temp == 0)
		{
			bounceBall->bounceBallProperty.landingActivate = false;
		}




		temp = 0;


		if (bounceBall->Position().y < stageProperty[currentStageIndex].deathPoint.y)
		{
			bounceBall->SetPosition(stageProperty[currentStageIndex].startPoint);
			bounceBall->bounceBallProperty.velocity.y = 0;
			PlaySoundA(soundFileName[12], NULL, SND_ASYNC | SND_NOSTOP);

		}



		if (!leftKeyPressed && !rightKeyPressed)
		{

			bounceBall->bounceBallProperty.velocity.x = 0;

			bounceBall->bounceBallProperty.velocity.z = 0;


		}
		if (!upKeyPressed && !downKeyPressed)
		{

			bounceBall->bounceBallProperty.velocity.x = 0;

			bounceBall->bounceBallProperty.velocity.z = 0;


		}


		if (!leftKeyPressed && rightKeyPressed)
		{

			if (viewDegree == 90)
			{

				bounceBall->bounceBallProperty.velocity.z = 5;

			}
			else if (viewDegree == 180)
			{

				bounceBall->bounceBallProperty.velocity.x = -5;

			}
			else if (viewDegree == 270)
			{
				bounceBall->bounceBallProperty.velocity.z = -5;
			}

			else
			{
				bounceBall->bounceBallProperty.velocity.x = 5;
			}





		}
		else if (leftKeyPressed && !rightKeyPressed)
		{

			if (viewDegree == 90)
			{

				bounceBall->bounceBallProperty.velocity.z = -5;

			}
			else if (viewDegree == 180)
			{

				bounceBall->bounceBallProperty.velocity.x = 5;

			}
			else if (viewDegree == 270)
			{
				bounceBall->bounceBallProperty.velocity.z = 5;
			}

			else
			{
				bounceBall->bounceBallProperty.velocity.x = -5;
			}
		}


		if (!upKeyPressed && downKeyPressed)
		{
			if (viewDegree == 90)
			{

				bounceBall->bounceBallProperty.velocity.x = -5;

			}
			else if (viewDegree == 180)
			{

				bounceBall->bounceBallProperty.velocity.z = -5;

			}
			else if (viewDegree == 270)
			{
				bounceBall->bounceBallProperty.velocity.x = 5;
			}

			else
			{
				bounceBall->bounceBallProperty.velocity.z = 5;
			}



		}
		else if (upKeyPressed && !downKeyPressed)
		{
			if (viewDegree == 90)
			{

				bounceBall->bounceBallProperty.velocity.x = 5;

			}
			else if (viewDegree == 180)
			{

				bounceBall->bounceBallProperty.velocity.z = 5;

			}
			else if (viewDegree == 270)
			{
				bounceBall->bounceBallProperty.velocity.x = -5;
			}

			else
			{
				bounceBall->bounceBallProperty.velocity.z = -5;
			}
		}



		leftKeyPressed = false;
		rightKeyPressed = false;
		upKeyPressed = false;
		downKeyPressed = false;


		//두번다시 이딴코딩은 짜지않는다

		if (CheckStageCleared())
		{
			if (currentStageIndex + 1 < stageLimit)
				LoadStage(++currentStageIndex);
			else if (currentStageIndex == stageLimit - 1)
			{
				simpleGameState = TitleState;
				currentStageIndex = 0;
				LoadStage(currentStageIndex);
			}

		}

		ApplyRotate();




	}

	else if (simpleGameState == LogoState)
	{
		static bool firstGenerated = false;


		if (!firstGenerated)
		{
			firstGenerated = true;
			PlaySoundA(soundFileName[13], NULL, SND_ASYNC | SND_NOSTOP);
		}

	}

	else if (simpleGameState == TitleState)
	{
		if (GetAsyncKeyState(VK_UP))
		{

			titleCursorPosition--;
			if (titleCursorPosition < 1)
			{
				titleCursorPosition = 1;
			}
			if (titleCursorPosition > 2)
			{
				titleCursorPosition = 2;
			}

		}
		else if (GetAsyncKeyState(VK_DOWN))
		{
			titleCursorPosition++;
			if (titleCursorPosition < 1)
			{
				titleCursorPosition = 1;
			}
			if (titleCursorPosition > 2)
			{
				titleCursorPosition = 2;
			}


		}
		else if (GetAsyncKeyState(VK_SPACE))
		{
			if (titleCursorPosition == 1)
			{
				simpleGameState = InGameState;
				LoadStage(0);
			}

			else if (titleCursorPosition == 2)
			{

				exit(0);

			}
		}

	}

	else if (simpleGameState == GameOverState)
	{


	}


	glutPostRedisplay();

	glutTimerFunc(1000 / 60, TimerFunc, 1);

}


void Start()
{
	srand((unsigned)time(NULL));

	masterMatrix->thisCamera.eyeY += 1000.0;
	masterMatrix->thisCamera.eyeZ += 1000.0;

	simpleGameState = LogoState;

	LoadStage(currentStageIndex);
	LoadResource();

	bounceBall->InitializeBall(50, false, false, 
		GLVector3(0, 0, 0), GLVector3(0, 15, 0), 1);
	bounceBall->boundingBoxSize = 45;

	testClass2->color4D = GLVector4(0.7, 0.5, 0, 1);
}

void Mouse(int button, int state, int x, int y)
{

}

void MouseWheel(int button, int state, int x, int y)
{


}

void MouseDrag(int x, int y)
{

}

void Keyboard(unsigned char key, int x, int y)
{

	static GLVector3 temp;

	if (simpleGameState == InGameState)
	{

		if (key == 'i')
		{

			glEnable(GL_DEPTH_TEST);

		}
		if (key == 'I')
		{

			glDisable(GL_DEPTH_TEST);

		}
		if (key == 'd')
		{


			//glEnable(GL_CULL_FACE);
			//바운스볼 이동 wasd 또는 화살표키
		}
		else
		{

		}

		if (key == 'a')
		{


		}
		if (key == 'w')
		{
			LoadStage(currentStageIndex);
		}
		if (key == 'W')
		{


		}

		if (key == 's')
		{
			currentStageIndex++;
			if (currentStageIndex >= stageLimit)
			{
				currentStageIndex = stageLimit - 1;
			}

			LoadStage(currentStageIndex);

		}
		if (key == 'S')
		{
			currentStageIndex--;
			if (currentStageIndex < 0)
			{
				currentStageIndex = 0;
			}

			LoadStage(currentStageIndex);
		}

		if (key == 'b')
		{

			//glShadeModel(GL_SMOOTH); // 또는 glShadeModel (GL_FLAT)


		}
		if (key == 'B')
		{
			//glShadeModel(GL_FLAT); // 또는 glShadeModel (GL_FLAT)

		}

		if (key == 'k')
		{

		}
		if (key == 'K')
		{

		}

		if (key == 'm')
		{


			quadOrSphereMap = !quadOrSphereMap;



		}
		if (key == 't')
		{

			masterMatrix->thisCamera.eyeX = 0;
			masterMatrix->thisCamera.eyeY = 300;
			masterMatrix->thisCamera.eyeZ = 1;

			masterMatrix->thisCamera.centerX = 0;
			masterMatrix->thisCamera.centerY = 0;
			masterMatrix->thisCamera.centerZ = 0;


			
		}

		if (key == 'l')
		{
			useBaseLight = !useBaseLight;

		}
		if (key == 'L')
		{

			useHighLight = !useHighLight;
		}
		if (key == 'N')
		{


			printf("%f\n", qaLightPosition[2]);
			qaLightPosition[2] += 100;


		}
		if (key == 'n')
		{
			qaLightPosition[2] -= 100;
			printf("??");
		}


		if (key == 'r' || key == 'R')
		{
			viewDegree = (viewDegree + 90) % 360;


		}

		if (key == 'o' || key == 'O')
		{





		}
		else if (key == 'O')
		{

			yRotated -= 2.0;

		}
		if (key == 'y')
		{

			yRotated += 2.0;


		}
		else if (key == 'Y')
		{

			yRotated -= 2.0;

		}

		if (key == 'z')
		{


			zRotated += 2.0;

		}
		else if (key == 'Z')
		{

			zRotated -= 2.0;

		}
		if (key == 'x')
		{


			xRotated += 2.0;

		}
		else if (key == 'X')
		{

			xRotated -= 2.0;

		}
		if (key == 'f')
		{
			zRotated = 0;
			xRotated = 0;
			yRotated = 0;
			masterMatrix->thisCamera.eyeX = 0.0;
			masterMatrix->thisCamera.eyeY = 0.0;
			masterMatrix->thisCamera.eyeZ = 300.0;

		}

		if (key == ']')
		{

			zRotated = 0;
			xRotated = 0;
			yRotated = 0;
			masterMatrix->thisCamera.eyeX = 0.0;
			masterMatrix->thisCamera.eyeY = 0.0;
			masterMatrix->thisCamera.eyeZ = 300.0;
		}

		if (key == 'q')
		{

			masterMatrix->thisCamera.eyeY -= 5.0;


		}
		else if (key == 'Q')
		{

			masterMatrix->thisCamera.eyeY += 5.0;
		}

		else if (key == 'e')
		{


			masterMatrix->thisCamera.eyeZ -= 5.0;

		}

		else if (key == 'E')
		{


			masterMatrix->thisCamera.eyeZ += 5.0;

		}
		else if (key == 'v')
		{


			masterMatrix->thisCamera.eyeX -= 5.0;

		}

		else if (key == 'V')
		{


			masterMatrix->thisCamera.eyeX += 5.0;

		}
	}

	else if (simpleGameState == LogoState)
	{
		printf("키입력 - 로고\n");
	}

	else if (simpleGameState == TitleState)
	{

		printf("키입력 - 타이틀\n");
	}

	else if (simpleGameState == GameOverState)
	{

		printf("키입력 - 게임오버\n");
	}



}
void KeyboardUp(unsigned char key, int x, int y)
{


}

void ApplyRotate()
{
	if (zRotated > 360.0)
	{
		zRotated -= 360.0*floor(zRotated / 360.0);   // Don't allow overflow
	}

	if (yRotated > 360.0)
	{
		yRotated -= 360.0*floor(yRotated / 360.0);   // Don't allow overflow
	}

	if (xRotated > 360.0)
	{
		xRotated -= 360.0*floor(xRotated / 360.0);   // Don't allow overflow
	}


	rotateMatrix[4] = yRotated;
	rotateMatrix[5] = 0;
	rotateMatrix[6] = 1;
	rotateMatrix[7] = 0;

	rotateMatrix[0] = xRotated;
	rotateMatrix[1] = 1;
	rotateMatrix[2] = 0;
	rotateMatrix[3] = 0;

	rotateMatrix[8] = zRotated;
	rotateMatrix[9] = 0;
	rotateMatrix[10] = 0;
	rotateMatrix[11] = 1;

}


bool CollisionCheck(CollisionData collisionData1, CollisionData collisionData2)
{

	if (collisionData1.leftX > collisionData2.rightX)
		return false;

	if (collisionData1.rightX < collisionData2.leftX)

		return false;

	if (collisionData1.topZ < collisionData2.bottomZ)
		return false;

	if (collisionData1.bottomZ > collisionData2.topZ)
		return false;

	return true;


}


bool LiangBarsky(double edgeLeft, double edgeRight, double edgeBottom, double edgeTop,   // Define the x/y clipping values for the border.
	double x0src, double y0src, double x1src, double y1src,                 // Define the start and end points of the line.
	double &x0clip, double &y0clip, double &x1clip, double &y1clip)         // The output values, so declare these outside.
{

	double t0 = 0.0;    double t1 = 1.0;
	double xdelta = x1src - x0src;
	double ydelta = y1src - y0src;
	double p, q, r;

	for (int edge = 0; edge < 4; edge++)
	{   // Traverse through left, right, bottom, top edges.
		if (edge == 0) { p = -xdelta;    q = -(edgeLeft - x0src); }
		if (edge == 1) { p = xdelta;     q = (edgeRight - x0src); }
		if (edge == 2) { p = -ydelta;    q = -(edgeBottom - y0src); }
		if (edge == 3) { p = ydelta;     q = (edgeTop - y0src); }
		r = q / p;
		if (p == 0 && q < 0) return false;   // Don't draw line at all. (parallel line outside)

		if (p < 0)
		{
			if (r > t1) return false;         // Don't draw line at all.
			else if (r > t0) t0 = r;            // Line is clipped!
		}
		else if (p > 0)
		{
			if (r < t0) return false;      // Don't draw line at all.
			else if (r < t1) t1 = r;         // Line is clipped!
		}
	}

	x0clip = x0src + t0 * xdelta;
	y0clip = y0src + t0 * ydelta;
	x1clip = x0src + t1 * xdelta;
	y1clip = y0src + t1 * ydelta;

	return true;        // (clipped) line is drawn
}



GLubyte * LoadDIBitmap(const char *filename, BITMAPINFO **info)
{
	FILE *fp;
	GLubyte *bits;

	int bitsize;
	int infosize;
	BITMAPFILEHEADER header;
	if (fopen_s(&fp, filename, "rb") != NULL)
	{   // 비트맵 파일을 바이너리 모드로 연다. (return_value == NULL) 일 경우 파일열기 성공.
		return NULL;
	}

	if (fread(&header, sizeof(BITMAPFILEHEADER), 1, fp) < 1)   // 비트맵의 헤더 정보를 읽는다.
	{
		fclose(fp);
		return NULL;
	}

	if (header.bfType != 'MB')      // 만일 비트맵이 아니라면 실행을 중지한다.
	{
		fclose(fp);
		return NULL;
	}

	infosize = header.bfOffBits - sizeof(BITMAPFILEHEADER);      // BITMAPINFO의 위치를 계산한다.

	if ((*info = (BITMAPINFO *)malloc(infosize)) == NULL)
	{
		fclose(fp);
		return NULL;
	}

	if (fread(*info, 1, infosize, fp) < (unsigned int)infosize)      // BITMAPINFO를 읽는다.
	{
		free(*info);
		fclose(fp);
		return NULL;
	}

	if ((bitsize = (*info)->bmiHeader.biSizeImage) == 0)      // 비트맵 이미지의 크기를 계산한다.
	{
		bitsize = ((*info)->bmiHeader.biWidth *
			(*info)->bmiHeader.biBitCount + 7) / 8 *
			abs((*info)->bmiHeader.biHeight);
	}

	if ((bits = (unsigned char*)malloc(bitsize)) == NULL)      // 비트맵 데이터를 읽고 파일을 닫는다.
	{
		free(*info);
		fclose(fp);
		return NULL;
	}

	if (fread(bits, 1, bitsize, fp) < (unsigned int)bitsize)
	{
		free(*info);
		free(bits);
		fclose(fp);
		return NULL;
	}

	fclose(fp);
	return bits;
}


void LoadResource()
{



	texture.push_back(GLint());
	m_bitInfo.push_back(&BITMAPINFO());
	m_bitmap.push_back(LoadDIBitmap("tiles/footboard.bmp", &m_bitInfo.back()));



	texture.push_back(GLint());
	m_bitInfo.push_back(&BITMAPINFO());
	m_bitmap.push_back(LoadDIBitmap("tiles/ice_box.bmp", &m_bitInfo.back()));


	texture.push_back(GLint());
	m_bitInfo.push_back(&BITMAPINFO());
	m_bitmap.push_back(LoadDIBitmap("tiles/aircap_box.bmp", &m_bitInfo.back()));

	texture.push_back(GLint());
	m_bitInfo.push_back(&BITMAPINFO());
	m_bitmap.push_back(LoadDIBitmap("tiles/yasuo_box.bmp", &m_bitInfo.back()));


	texture.push_back(GLint());
	m_bitInfo.push_back(&BITMAPINFO());
	m_bitmap.push_back(LoadDIBitmap("tiles/duck_box.bmp", &m_bitInfo.back()));



	texture.push_back(GLint());
	m_bitInfo.push_back(&BITMAPINFO());
	m_bitmap.push_back(LoadDIBitmap("tiles/electricity_box.bmp", &m_bitInfo.back()));



	texture.push_back(GLint());
	m_bitInfo.push_back(&BITMAPINFO());
	m_bitmap.push_back(LoadDIBitmap("tiles/grass_box.bmp", &m_bitInfo.back()));



	texture.push_back(GLint());
	m_bitInfo.push_back(&BITMAPINFO());
	m_bitmap.push_back(LoadDIBitmap("tiles/moon_box.bmp", &m_bitInfo.back()));



	texture.push_back(GLint());
	m_bitInfo.push_back(&BITMAPINFO());
	m_bitmap.push_back(LoadDIBitmap("tiles/snow_box.bmp", &m_bitInfo.back()));



	texture.push_back(GLint());
	m_bitInfo.push_back(&BITMAPINFO());
	m_bitmap.push_back(LoadDIBitmap("tiles/water_box.bmp", &m_bitInfo.back()));






	//철,아이스,뽁뽁이,야스오,오리,전기,초원,달,눈,물



	backgroundBitmapTexture.push_back(GLint());
	backgroundBitmapInfo.push_back(&BITMAPINFO());
	backgroundBitmapData.push_back(LoadDIBitmap("background/metal_bg.bmp", &backgroundBitmapInfo.back()));



	backgroundBitmapTexture.push_back(GLint());
	backgroundBitmapInfo.push_back(&BITMAPINFO());
	backgroundBitmapData.push_back(LoadDIBitmap("background/ice_bg.bmp", &backgroundBitmapInfo.back()));



	backgroundBitmapTexture.push_back(GLint());
	backgroundBitmapInfo.push_back(&BITMAPINFO());
	backgroundBitmapData.push_back(LoadDIBitmap("background/aircap_bg.bmp", &backgroundBitmapInfo.back()));


	backgroundBitmapTexture.push_back(GLint());
	backgroundBitmapInfo.push_back(&BITMAPINFO());
	backgroundBitmapData.push_back(LoadDIBitmap("background/yasuo_bg4.bmp", &backgroundBitmapInfo.back()));


	backgroundBitmapTexture.push_back(GLint());
	backgroundBitmapInfo.push_back(&BITMAPINFO());
	backgroundBitmapData.push_back(LoadDIBitmap("background/duck_bg.bmp", &backgroundBitmapInfo.back()));


	backgroundBitmapTexture.push_back(GLint());
	backgroundBitmapInfo.push_back(&BITMAPINFO());
	backgroundBitmapData.push_back(LoadDIBitmap("background/electricity_bg.bmp", &backgroundBitmapInfo.back()));



	backgroundBitmapTexture.push_back(GLint());
	backgroundBitmapInfo.push_back(&BITMAPINFO());
	backgroundBitmapData.push_back(LoadDIBitmap("background/grass_bg.bmp", &backgroundBitmapInfo.back()));



	backgroundBitmapTexture.push_back(GLint());
	backgroundBitmapInfo.push_back(&BITMAPINFO());
	backgroundBitmapData.push_back(LoadDIBitmap("background/moon_bg.bmp", &backgroundBitmapInfo.back()));


	backgroundBitmapTexture.push_back(GLint());
	backgroundBitmapInfo.push_back(&BITMAPINFO());
	backgroundBitmapData.push_back(LoadDIBitmap("background/snow_bg.bmp", &backgroundBitmapInfo.back()));



	backgroundBitmapTexture.push_back(GLint());
	backgroundBitmapInfo.push_back(&BITMAPINFO());
	backgroundBitmapData.push_back(LoadDIBitmap("background/water_bg.bmp", &backgroundBitmapInfo.back()));






	//철,아이스,뽁뽁이,야스오,오리,전기,초원,달,눈,물



	backgroundBitmapTexture2.push_back(GLint());
	backgroundBitmapInfo2.push_back(&BITMAPINFO());
	backgroundBitmapData2.push_back(LoadDIBitmap("background/metal_un.bmp", &backgroundBitmapInfo2.back()));



	backgroundBitmapTexture2.push_back(GLint());
	backgroundBitmapInfo2.push_back(&BITMAPINFO());
	backgroundBitmapData2.push_back(LoadDIBitmap("background/ice_un.bmp", &backgroundBitmapInfo2.back()));



	backgroundBitmapTexture2.push_back(GLint());
	backgroundBitmapInfo2.push_back(&BITMAPINFO());
	backgroundBitmapData2.push_back(LoadDIBitmap("background/aircap_un.bmp", &backgroundBitmapInfo2.back()));


	backgroundBitmapTexture2.push_back(GLint());
	backgroundBitmapInfo2.push_back(&BITMAPINFO());
	backgroundBitmapData2.push_back(LoadDIBitmap("background/yasuo_un.bmp", &backgroundBitmapInfo2.back()));


	backgroundBitmapTexture2.push_back(GLint());
	backgroundBitmapInfo2.push_back(&BITMAPINFO());
	backgroundBitmapData2.push_back(LoadDIBitmap("background/duck_un.bmp", &backgroundBitmapInfo2.back()));


	backgroundBitmapTexture2.push_back(GLint());
	backgroundBitmapInfo2.push_back(&BITMAPINFO());
	backgroundBitmapData2.push_back(LoadDIBitmap("background/electricity_un.bmp", &backgroundBitmapInfo2.back()));



	backgroundBitmapTexture2.push_back(GLint());
	backgroundBitmapInfo2.push_back(&BITMAPINFO());
	backgroundBitmapData2.push_back(LoadDIBitmap("background/grass_un.bmp", &backgroundBitmapInfo2.back()));



	backgroundBitmapTexture2.push_back(GLint());
	backgroundBitmapInfo2.push_back(&BITMAPINFO());
	backgroundBitmapData2.push_back(LoadDIBitmap("background/moon_un.bmp", &backgroundBitmapInfo2.back()));


	backgroundBitmapTexture2.push_back(GLint());
	backgroundBitmapInfo2.push_back(&BITMAPINFO());
	backgroundBitmapData2.push_back(LoadDIBitmap("background/snow_un.bmp", &backgroundBitmapInfo2.back()));



	backgroundBitmapTexture2.push_back(GLint());
	backgroundBitmapInfo2.push_back(&BITMAPINFO());
	backgroundBitmapData2.push_back(LoadDIBitmap("background/water_un.bmp", &backgroundBitmapInfo2.back()));
























	uIBitmapTexture.push_back(GLint());
	uIBitmapInfo.push_back(&BITMAPINFO());
	uIBitmapData.push_back(LoadDIBitmap("uI/black.bmp", &uIBitmapInfo.back()));




	uIBitmapTexture.push_back(GLint());
	uIBitmapInfo.push_back(&BITMAPINFO());
	uIBitmapData.push_back(LoadDIBitmap("uI/kpuCredit.bmp", &uIBitmapInfo.back()));




	uIBitmapTexture.push_back(GLint());
	uIBitmapInfo.push_back(&BITMAPINFO());
	uIBitmapData.push_back(LoadDIBitmap("uI/title2.bmp", &uIBitmapInfo.back()));





	uIBitmapTexture.push_back(GLint());
	uIBitmapInfo.push_back(&BITMAPINFO());
	uIBitmapData.push_back(LoadDIBitmap("uI/PlayButton.bmp", &uIBitmapInfo.back()));




	uIBitmapTexture.push_back(GLint());
	uIBitmapInfo.push_back(&BITMAPINFO());
	uIBitmapData.push_back(LoadDIBitmap("uI/QuitButton.bmp", &uIBitmapInfo.back()));



	uIBitmapTexture.push_back(GLint());
	uIBitmapInfo.push_back(&BITMAPINFO());
	uIBitmapData.push_back(LoadDIBitmap("uI/Star.bmp", &uIBitmapInfo.back()));










	glGenTextures(texture.size(), &texture[0]);

	glGenTextures(backgroundBitmapTexture.size(), &backgroundBitmapTexture[0]);

	glGenTextures(backgroundBitmapTexture2.size(), &backgroundBitmapTexture2[0]);

	glGenTextures(uIBitmapTexture.size(), &uIBitmapTexture[0]);




	for (int i = 0; i < texture.size(); ++i)
	{


		glBindTexture(GL_TEXTURE_2D, texture[i]);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, m_bitInfo[i]->bmiHeader.biWidth, m_bitInfo[i]->bmiHeader.biHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, m_bitmap[i]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);

	}


	for (int i = 0; i < backgroundBitmapTexture.size(); ++i)
	{


		glBindTexture(GL_TEXTURE_2D, backgroundBitmapTexture[i]);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, backgroundBitmapInfo[i]->bmiHeader.biWidth, backgroundBitmapInfo[i]->bmiHeader.biHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, backgroundBitmapData[i]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);

	}


	for (int i = 0; i < backgroundBitmapTexture2.size(); ++i)
	{


		glBindTexture(GL_TEXTURE_2D, backgroundBitmapTexture2[i]);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, backgroundBitmapInfo2[i]->bmiHeader.biWidth, backgroundBitmapInfo2[i]->bmiHeader.biHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, backgroundBitmapData2[i]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);

	}




	for (int i = 0; i < uIBitmapTexture.size(); ++i)
	{


		glBindTexture(GL_TEXTURE_2D, uIBitmapTexture[i]);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, uIBitmapInfo[i]->bmiHeader.biWidth, uIBitmapInfo[i]->bmiHeader.biHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, uIBitmapData[i]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);

	}




}


GLVector3 CardinalSplineAnimation(GLVector3 vector1, GLVector3 vector2)
{
	static int start = 0;

	for (int i = start; i < 500; ++i)
	{

		start++;
		return 	masterMatrix->CalcCadinalSpline(GLVector3(vector1.x - (200), vector1.y - (200), vector1.z - (200)), vector1, vector2, GLVector3(vector2.x + (200), vector2.y + (200), vector2.z + (200)), i / 500.0);;
	}

	start = 0;
	return 	masterMatrix->CalcCadinalSpline(GLVector3(vector1.x - (200), vector1.y - (200), vector1.z - (200)), vector1, vector2, GLVector3(vector2.x + (200), vector2.y + (200), vector2.z + (200)), start / 500.0);

}


void LoadStage(int stageNumber)
{
	FILE *fp_map1, *fp_star1;

	string str1 = "mapData/map";
	string str2 = "mapData/star";
	string extension = ".txt";

	char asd[10];
	char asd2[10];



	_itoa(stageNumber + 1, asd, 10);
	str1.append(asd);
	str1.append(extension);



	_itoa(stageNumber + 1, asd2, 10);
	str2.append(asd);
	str2.append(extension);

	map1_index = 0;
	star1_index = 0;

	fopen_s(&fp_map1, str1.c_str(), "r");
	while (fscanf_s(fp_map1, "%lf %lf %lf", &(map_1[map1_index].x), &(map_1[map1_index].y), &(map_1[map1_index].z)) != EOF)
	{
		map1_index++;
	}
	fclose(fp_map1);

	fopen_s(&fp_star1, str2.c_str(), "r");
	while (fscanf_s(fp_star1, "%lf %lf %lf", &(star_1[star1_index].x), &(star_1[star1_index].y), &(star_1[star1_index].z)) != EOF)
	{
		star1_index++;
	}
	fclose(fp_star1);

	for (int i = 0; i < map1_index; i++)
	{

		if (cubes.size() <= i)
		{
			cubes.push_back(Polygon0(masterMatrix));
		}
		cubes[i].boundingBoxSize = 50;

		cubes[i].SetPosition(map_1[i].x * 2, map_1[i].y * 2, map_1[i].z * 2);
		
	}

	for (int i = 0; i < star1_index; i++)
	{

		if (stars.size() <= i)
		{
			stars.push_back(Polygon0(masterMatrix));
		}
		stars[i].boundingBoxSize = 50;

		stars[i].SetPosition(star_1[i].x * 2, star_1[i].y * 2, star_1[i].z * 2);
		stars[i].color4D = GLVector4(1, 1, 0, 1);
		stars[i].objectActivate = true;
	}

	currentStageIndex = stageNumber;

	bounceBall->soundFileName = soundFileName[stageNumber];

	bounceBall->SetPosition(stageProperty[stageNumber].startPoint);
	stageProperty[stageNumber].numberOfStar = star1_index;

	mciSendStringA("close mp3", NULL, 0, NULL);
	if (simpleGameState == TitleState)
	{

		mciSendStringA(musicFileName[10], NULL, 0, NULL);
		mciSendString("play mp3 repeat", NULL, 0, NULL);
	}
	else if (simpleGameState == InGameState)
	{
		printf("??");
		mciSendStringA(musicFileName[stageNumber], NULL, 0, NULL);
		mciSendString("play mp3 repeat", NULL, 0, NULL);
	}



	viewDegree = 0;

}

void SetCameraOnBounceBall()
{



	if (viewDegree == 90)

	{

		masterMatrix->thisCamera.centerX = bounceBall->Position().x;
		masterMatrix->thisCamera.centerY = bounceBall->Position().y;
		masterMatrix->thisCamera.centerZ = bounceBall->Position().z;

		masterMatrix->thisCamera.eyeX = masterMatrix->thisCamera.centerX - 1000;
		masterMatrix->thisCamera.eyeY = 1000 + bounceBall->Position().y;
		masterMatrix->thisCamera.eyeZ = masterMatrix->thisCamera.centerZ;
	}
	else if (viewDegree == 180)

	{

		masterMatrix->thisCamera.centerX = bounceBall->Position().x;
		masterMatrix->thisCamera.centerY = bounceBall->Position().y;
		masterMatrix->thisCamera.centerZ = bounceBall->Position().z;

		masterMatrix->thisCamera.eyeX = masterMatrix->thisCamera.centerX;
		masterMatrix->thisCamera.eyeY = 1000 + bounceBall->Position().y;
		masterMatrix->thisCamera.eyeZ = masterMatrix->thisCamera.centerZ - 1000;
	}
	else if (viewDegree == 270)

	{

		masterMatrix->thisCamera.centerX = bounceBall->Position().x;
		masterMatrix->thisCamera.centerY = bounceBall->Position().y;
		masterMatrix->thisCamera.centerZ = bounceBall->Position().z;

		masterMatrix->thisCamera.eyeX = masterMatrix->thisCamera.centerX + 1000;
		masterMatrix->thisCamera.eyeY = 1000 + bounceBall->Position().y;
		masterMatrix->thisCamera.eyeZ = masterMatrix->thisCamera.centerZ;
	}

	else
	{

		masterMatrix->thisCamera.centerX = bounceBall->Position().x;
		masterMatrix->thisCamera.centerY = bounceBall->Position().y;
		masterMatrix->thisCamera.centerZ = bounceBall->Position().z;

		masterMatrix->thisCamera.eyeX = masterMatrix->thisCamera.centerX;
		masterMatrix->thisCamera.eyeY = 1000 + bounceBall->Position().y;
		masterMatrix->thisCamera.eyeZ = masterMatrix->thisCamera.centerZ + 1000;

	}

}

/*
		masterMatrix->thisCamera.centerX = bounceBall->Position().x;
		masterMatrix->thisCamera.centerY = bounceBall->Position().y;
		masterMatrix->thisCamera.centerZ = bounceBall->Position().z;

		masterMatrix->thisCamera.eyeX = masterMatrix->thisCamera.centerX;
		masterMatrix->thisCamera.eyeY = 1000 + bounceBall->Position().y;
		masterMatrix->thisCamera.eyeZ = masterMatrix->thisCamera.centerZ + 1000;

*/



void LogoAnimation()
{
	static int curFrame = 0;
	static int keyFrame = 360;

	static int simpleLevel = 0;






	logoScreen->SetPosition(0, 20, 0);


	if (simpleLevel == 0)
	{
		blackScreen->alpha = (double)curFrame * (1.0 / (120.0));
		blackScreen->SetPosition(0, 20, 0);
		blackScreen->DrawLogoScreen(200, uIBitmapTexture[1]);

		curFrame++;

		if (curFrame > 120)
		{
			simpleLevel++;
		}

	}

	else if (simpleLevel == 1)
	{
		blackScreen->SetPosition(0, 20, 0);
		blackScreen->DrawLogoScreen(200, uIBitmapTexture[1]);

		curFrame++;




		if (curFrame > 240)
		{
			simpleLevel++;
		}

	}



	else if (simpleLevel == 2)
	{
		blackScreen->alpha = (double)(120 - (curFrame % 120)) * (1.0 / (120.0));
		blackScreen->SetPosition(0, 20, 0);
		blackScreen->DrawLogoScreen(200, uIBitmapTexture[1]);

		curFrame++;


		if (curFrame >= keyFrame)
		{
			simpleGameState = SimpleGameState::TitleState;
			LoadStage(0);
		}

	}






}

void TitleAnimation()
{

	static bool temp = false;


	//titleScreen->DrawTitleScreen(150,)
	titleScreen->DrawTitleScreen(200, uIBitmapTexture[2]);
	titleScreen->SetPosition(0, 20, 0);

	startButton->DrawTitleScreen(20, uIBitmapTexture[3]);
	startButton->SetPosition(0, -90, 2);

	quitButton->DrawTitleScreen(20, uIBitmapTexture[4]);
	quitButton->SetPosition(0, -130, 2);


	cursor->Create3DObject(7, 5, false, true);
	cursor->Rotate2(1, 1, 1, 1, 0);
	if (!temp)
	{
		temp = true;
		cursor->SetPosition(-50, -85, 20);
	}
	cursor->SetPosition(-50, -50 - (titleCursorPosition * 35), 20);
}


bool CheckStageCleared()
{

	static int keyFrame = 150;
	static int currentFrame = 0;



	if (currentFrame >= keyFrame)
	{
		currentFrame = 0;
		return true;
	}

	if (GetCurrentNumberOfStar() <= 0)
	{
		currentFrame++;
		return false;
	}

	currentFrame = 0;

	return false;
}


int GetCurrentNumberOfStar()
{
	static int temp;
	temp = 0;

	for (int i = 0; i < star1_index; ++i)
	{
		if (i < stars.size())
			if (stars[i].objectActivate)
			{
				temp++;
			}
	}


	return temp;

}



void DrawSlash(float size)
{

	slash->SetPosition(-120, 175, 0);




	slash->Translate(1 * size, 2.5 * size, 0);
	slash->DrawCube(1 * size, false, false);
	slash->Translate(-1 * size, -2.5 * size, 0);


	slash->Translate(2 * size, 5 * size, 0);
	slash->DrawCube(1 * size, false, false);
	slash->Translate(-2 * size, -5 * size, 0);


	slash->Translate(3 * size, 7.5 * size, 0);
	slash->DrawCube(1 * size, false, false);
	slash->Translate(-3 * size, -7.5 * size, 0);


	slash->Translate(4 * size, 10 * size, 0);
	slash->DrawCube(1 * size, false, false);
	slash->Translate(-4 * size, -10 * size, 0);


	slash->Translate(5 * size, 12.5 * size, 0);
	slash->DrawCube(1 * size, false, false);
	slash->Translate(-5 * size, -12.5 * size, 0);

	slash->Translate(6 * size, 15 * size, 0);
	slash->DrawCube(1 * size, false, false);
	slash->Translate(-6 * size, -15 * size, 0);


	slash->Translate(7 * size, 17.5 * size, 0);
	slash->DrawCube(1 * size, false, false);
	slash->Translate(-7 * size, -17.5 * size, 0);


	slash->Translate(8 * size, 20 * size, 0);
	slash->DrawCube(1 * size, false, false);
	slash->Translate(-8 * size, -20 * size, 0);


	slash->Translate(9 * size, 22.5 * size, 0);
	slash->DrawCube(1 * size, false, false);
	slash->Translate(-9 * size, -22.5 * size, 0);


	slash->Translate(10 * size, 25 * size, 0);
	slash->DrawCube(1 * size, false, false);
	slash->Translate(-10 * size, -25 * size, 0);



}