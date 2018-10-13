#define _CRT_SECURE_NO_WARNINGS
#include "Define.h"
#include <math.h>

GLvoid DrawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Keyboard(unsigned char key, int x, int y);
void Motion(int x, int y);
void TimerFunction(int value);

// �÷��̾� �׸��� �Լ�
void DrawPlayer();

//ī�޶� �������� �Լ�
void Target(int x, int y);

// ����4�� �׸��� �Լ�
void DrawGhost1();
void DrawGhost2();
void DrawGhost3();
void DrawGhost4();

// �� ���� ����
char mapData[6][30][30];

// �ؽ�Ʈ �б�� �Լ�
void MapTextRead1();
void MapTextRead2();
void MapTextRead3();
void MapTextRead4();
void MapTextRead5();
void MapTextRead6();

// �ؽ��� ���� �Լ�
void InitTexture();

// �浹üũ �Լ�
void CollisionCheck();

// ���� �� ������ �Լ�
void show_Light();
void FlashLight();

// UI �׸��� �Լ�
void draw_UI(int CharX, int CharZ);


int width, height; // �ʺ�, ����


// ī�޶� ����
float camRotateX = -90, camRotateY = -90, viewX = 0, viewY = 0, viewZ = -1000;
float playerX = 0, playerZ = 6920, playerY = 0;
float nx = 0, ny = 0, bx = 0, by = 0;
int characterSpeed = 16, camDistance = 400, mouseSpeed = 10;
bool RotateCam = true;

// �÷��̾� ��� �� �� ������ ���� ���� 
float rightSholderX, rightSholderY, rightSholderZ;
float leftShoulderX, leftShoulderY, leftShoulderZ;
float rightElbowX, rightElbowY, rightElbowZ;
float leftElbowX, leftElbowY, leftElbowZ;

// �浹 üũ ���� 
int collisionDist = 90;

// �̷� ��ȭ�� ���� ��
int changeYpos = 240;
int changeMapNumber = 0;
bool changeDown = false;
bool changeUP = false;

// UI ����
char drawTimeCount[100];
int timeCount = 35;

// ���� �̵� ���� 
float ghost1Angle;
float ghost2Angle;
float ghost3X = 500, ghost3Z = 500, ghost3Angle = 90;
bool ghost3Change = false;
float ghost4X = 500, ghost4Z = 500, ghost4Angle = 0;
bool ghost4Change = false;


void main()
{
	MapTextRead1();
	MapTextRead2();
	MapTextRead3();
	MapTextRead4();
	MapTextRead5();
	MapTextRead6();

	leftShoulderY = 70;
	leftShoulderZ = -75;
	rightSholderY = 30;
	rightSholderZ = 0;
	leftElbowX = 25;
	rightElbowX = -30;

	//������ �ʱ�ȭ �� ����
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); //���÷��� ��� ����
	glutInitWindowPosition(500, 0); // ������ ��ġ ����
	glutInitWindowSize(1200, 800); //������ ũ�� ����
	glutCreateWindow("Gloomy Maze"); //������ ����(������ �̸�)

									 //���� ���� �ʱ�ȭ �Լ�
	InitTexture(); // �ؽ��� �ʱ�ȭ
	glutSetCursor(GLUT_CURSOR_NONE); // ȭ�� ���콺 Ŀ�� ����


	// �ݹ� �Լ�
	glutDisplayFunc(DrawScene); //��� �Լ��� ����
	glutTimerFunc(10, TimerFunction, 1);
	glutTimerFunc(10, TimerFunction, 2);
	glutTimerFunc(1000, TimerFunction, 3);
	glutTimerFunc(10, TimerFunction, 4);
	glutPassiveMotionFunc(Motion); // ���콺 Ŭ������ ���� ���·� �����϶� ȣ��Ǵ� �ݹ��Լ�
	glutKeyboardFunc(Keyboard);//Ű�����Է�
	PlaySound("Sound/Breath&Heart.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP | SND_NODEFAULT);
	//SND_ASYNC �񵿱��� ���, ����߿��� ���α׷��� ������ �ʰ� ���ư�
	//SND_LOOP  �ݺ���� ( SND_ASYNC�� ���� ��ߵ�)
	//SND_NODEFAULT ������ ��ο� wav������ ��� ������� ������ ����

	glutReshapeFunc(Reshape);
	glutMainLoop(); //���� ���� ����

}

//������ ��� �Լ�
GLvoid DrawScene(GLvoid)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);//��������'black'������
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);// ������ ������ ��ü�� ĥ�ϱ�

	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0f, (float)width / (float)height, 1.0, 5000.0);
	glMatrixMode(GL_MODELVIEW);

	glEnable(GL_LIGHTING);      // ���� Ȱ��ȭ
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHT0);

	glLoadIdentity();
	gluLookAt(playerX, playerY + 200, playerZ, playerX + viewX, playerY + viewY + 170, playerZ + viewZ, 0.0, 1.0, 0.0);

	glPushMatrix();
	glEnable(GL_DEPTH_TEST); // ������ �� ����
	glEnable(GL_CULL_FACE);


	//----------------------------------------------------
	// ���� , ������ , �÷��̾� 
	glPushMatrix();
	glTranslatef(playerX, playerY + 130, playerZ);
	glRotatef(camRotateX + 180, 0, 1, 0);
	FlashLight();
	DrawPlayer();
	show_Light();
	glPopMatrix();


	//-----------------------------------------------------
	// ����1
	glPushMatrix();
	glTranslatef(6500.f, 0.f, 6900.f);
	glRotatef(-ghost1Angle, 0, 1, 0);
	glTranslatef(4000.f, 0.f, 4000.f);
	glRotatef(-ghost1Angle, 0, 1, 0);
	DrawGhost1();
	glPopMatrix();
	//-----------------------------------------------------
	// ����2
	glPushMatrix();
	glTranslatef(6500.f, 0.f, 6900.f);
	glRotatef(-ghost2Angle, 0, 1, 0);
	glTranslatef(2000.f, 0.f, 2000.f);
	glRotatef(-ghost2Angle, 0, 1, 0);
	DrawGhost2();
	glPopMatrix();
	//-----------------------------------------------------
	// ����3
	glPushMatrix();
	glTranslatef(ghost3X, 0, ghost3Z);
	glRotatef(ghost3Angle, 0, 1, 0);
	DrawGhost3();
	glPopMatrix();
	//-----------------------------------------------------
	// ����4
	glPushMatrix();
	glTranslatef(ghost4X, 0, ghost4Z);
	glRotatef(ghost4Angle, 0, 1, 0);
	DrawGhost4();
	glPopMatrix();


	//-----------------------------------------------------
	// �ٴ� �׸���
	glPushMatrix();
	glTranslatef(240.f, 0.f, 240.f);
	DrawGround(groundObject[0]);
	glPopMatrix();

	//-----------------------------------------------------
	// �̷� �׸���
	glPushMatrix();
	glTranslatef(240.f, 0.f, 240.f);
	DrawBlock(blockObject);
	glPopMatrix();

	// ���ݱ����� POP~
	glPopMatrix();

	//-----------------------------------------------------
	// UI �׸���
	glPushMatrix();
	draw_UI(playerX, playerZ);
	glPopMatrix();
	glutSwapBuffers();
}

GLvoid Reshape(int w, int h)
{
	//����Ʈ ��ȯ ����
	glViewport(0, 0, w, h);
	width = w;
	height = h;

	//���� ��� ���� �缳��
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//Ŭ���� ���� ���� : ��������
	gluPerspective(60.0f, (float)width / (float)height, 0.1, 5000.0);

	//�� �� ��� ���� �缳��
	glMatrixMode(GL_MODELVIEW);
}

void Motion(int x, int y)
{
	Target(x, y);
}

void TimerFunction(int value)
{
	switch (value)
	{
	case 1:
		if (RotateCam)
			glutWarpPointer(400, 300);
		CollisionCheck();
		glutTimerFunc(10, TimerFunction, 1);
		break;

	case 2:
		if (changeDown == true) {
			changeYpos -= 2;
			if (changeYpos <= -250) {
				changeDown = false;
				changeUP = true;
				changeMapNumber += 1;
				if (changeMapNumber >= 6)
					changeMapNumber = 0;

			}
		}
		if (changeUP == true) {
			changeYpos += 5;
			if (changeYpos >= 240)
				changeUP = false;
		}
		glutTimerFunc(10, TimerFunction, 2);
		break;

	case 3:
		timeCount -= 1;
		if (timeCount <= 0) {
			changeDown = true;
			timeCount = 75;
		}
		glutTimerFunc(1000, TimerFunction, 3);
		break;

	case 4:
		ghost1Angle += 0.1;
		ghost2Angle += 0.3;
		//---------------------------------------
		// ����3 �̵�
		if (ghost3Change == false)
			ghost3X += 15;
		else {
			ghost3X -= 15;
		}
		if (ghost3X >= 12000) {
			ghost3Change = true;
			ghost3Angle = -90;
			ghost3Z += 1000;
		}
		if (ghost3X <= 0) {
			ghost3Change = false;
			ghost3Angle = 90;
			ghost3Z += 1000;
		}
		if (ghost3Z >= 12000)
			ghost3Z = 1000;
		//--------------------------------------------------
		// ����4 �̵�
		if (ghost4Change == false)
			ghost4Z += 15;
		else {
			ghost4Z -= 15;
		}
		if (ghost4Z >= 12000) {
			ghost4Change = true;
			ghost4Angle = 180;
			ghost4X += 1000;
		}
		if (ghost4Z <= 0) {
			ghost4Change = false;
			ghost4Angle = 0;
			ghost4X += 1000;
		}
		if (ghost4X >= 12000)
			ghost4X = 1000;
		glutTimerFunc(10, TimerFunction, 4);
	}
	glutPostRedisplay();
}

void Keyboard(unsigned char key, int x, int y)
{
	if (key == 27) {  // 27�� ESC  excpae
		exit(1);
	}
	if (key == 'w')
	{
		playerX += characterSpeed * cos((-camRotateX - 90) * 3.141592 / 180);
		playerZ += characterSpeed * sin((-camRotateX - 90) * 3.141592 / 180);

	}
	else if (key == 's')
	{
		playerX -= characterSpeed * cos((-camRotateX - 90) * 3.141592 / 180);
		playerZ -= characterSpeed * sin((-camRotateX - 90) * 3.141592 / 180);

	}
	if (key == 'a')
	{
		playerX -= characterSpeed * cos((-camRotateX) * 3.141592 / 180);
		playerZ -= characterSpeed * sin((-camRotateX) * 3.141592 / 180);

	}
	else if (key == 'd')
	{
		playerX += characterSpeed * cos((-camRotateX) * 3.141592 / 180);
		playerZ += characterSpeed * sin((-camRotateX) * 3.141592 / 180);
	}

	if (key == '1') {
		changeDown = true;
	}

	glutPostRedisplay();
}


void InitTexture()
{
	// �ٴ� �ؽ�ó ������ ����
	GroundTexture(groundObject);

	// �÷��̾� �ؽ�ó ������ ����
	HeadTexture(headObject);
	BodyTexture(bodyObject);
	ArmTexture(armObject, handObject);
	LegTexture(legObject, footObject);

	// �� �ؽ�ó ������ ����
	BlockTexture(blockObject);

	// ���� �ؽ�ó ������ ����
	Ghost1Texture(ghostObject1);
	Ghost2Texture(ghostObject2);
	Ghost3Texture(ghostObject3);
	Ghost4Texture(ghostObject4);
}

void Target(int x, int y)
{
	if (RotateCam == true)
	{
		nx = 400 - x;
		ny = 300 - y;

		camRotateX = camRotateX + (nx / mouseSpeed);
		camRotateY = camRotateY + (ny / mouseSpeed);
		leftShoulderX = camRotateY;
		rightSholderX = camRotateY;

		viewZ = 1000 * sin((camRotateY)* 3.141592 / 180) * cos((camRotateX)* 3.141592 / 180);
		viewX = 1000 * sin((camRotateY)* 3.141592 / 180) * sin((camRotateX)* 3.141592 / 180);
		viewY = 1000 * cos((camRotateY)* 3.141592 / 180);

		if (camRotateX <= -360 || camRotateX >= 360)
			camRotateX = 0;

		if (camRotateY < -179)
			camRotateY = -179;
		else if (camRotateY > -1)
			camRotateY = -1;
		bx = nx;
		by = ny;

	}
}
void DrawGhost1()
{
	glPushMatrix(); 
	glTranslated(0, 170, 0);
	glScaled(2.0, 2.0, 1.4);
	DrawBlockFront(30, false, ghostObject1[0]);
	DrawBlockBack(30, false, ghostObject1[1]);
	DrawBlockLeft(30, false, ghostObject1[2]);
	DrawBlockRight(30, false, ghostObject1[3]);
	DrawBlockTop(30, false, ghostObject1[4]);
	DrawBlockBottom(30, false, ghostObject1[5]);
	glPopMatrix();
}

void DrawGhost2()
{
	glPushMatrix();
	glTranslated(0, 170, 0);
	
	glScaled(2.0, 2.0, 1.4);
	DrawBlockFront(30, false, ghostObject2[0]);
	DrawBlockBack(30, false, ghostObject2[1]);
	DrawBlockLeft(30, false, ghostObject2[2]);
	DrawBlockRight(30, false, ghostObject2[3]);
	DrawBlockTop(30, false, ghostObject2[4]);
	DrawBlockBottom(30, false, ghostObject2[5]);
	glPopMatrix(); 
}

void DrawGhost3()
{
	glPushMatrix(); 
	glTranslated(0, 170, 0);
	glScaled(2.0, 2.0, 1.4);
	DrawBlockFront(30, false, ghostObject3[0]);
	DrawBlockBack(30, false, ghostObject3[1]);
	DrawBlockLeft(30, false, ghostObject3[2]);
	DrawBlockRight(30, false, ghostObject3[3]);
	DrawBlockTop(30, false, ghostObject3[4]);
	DrawBlockBottom(30, false, ghostObject3[5]);
	glPopMatrix();
}

void DrawGhost4()
{
	glPushMatrix(); 
	glTranslated(0, 170, 0);
	glScaled(2.0, 2.0, 1.4);
	DrawBlockFront(30, false, ghostObject4[0]);
	DrawBlockBack(30, false, ghostObject4[1]);
	DrawBlockLeft(30, false, ghostObject4[2]);
	DrawBlockRight(30, false, ghostObject4[3]);
	DrawBlockTop(30, false, ghostObject4[4]);
	DrawBlockBottom(30, false, ghostObject4[5]);
	glPopMatrix();
}

void DrawPlayer() {
	glPushMatrix(); 

	glPushMatrix();  // �Ӹ�
	glTranslated(0, 75, 0);
	glRotatef(-(camRotateY + 90) / 3, 1, 0, 0);
	glScaled(1.0, 1.0, 0.7);
	DrawBlockFront(30, false, headObject[0]);
	DrawBlockBack(30, false, headObject[1]);
	DrawBlockLeft(30, false, headObject[2]);
	DrawBlockRight(30, false, headObject[3]);
	DrawBlockTop(30, false, headObject[4]);
	DrawBlockBottom(30, false, headObject[5]);
	glPopMatrix();

	glPushMatrix(); // ����
	glScaled(1.0, 1.5, 0.5);
	DrawBlockFront(30, false, bodyObject[0]);
	DrawBlockBack(30, false, bodyObject[1]);
	DrawBlockLeft(30, false, bodyObject[2]);
	DrawBlockRight(30, false, bodyObject[3]);
	DrawBlockTop(30, false, bodyObject[4]);
	DrawBlockBottom(30, false, bodyObject[5]);
	glPopMatrix();

	glPushMatrix(); // ������
	glTranslated(-45, 44, 0);
	glRotatef(-rightSholderX + 210, 1, 0, 0);
	glRotatef(rightSholderY, 0, 1, 0);
	glRotatef(rightSholderZ, 0, 0, 1);
	glScaled(0.5, 0.75, 0.5);
	DrawBlockFront(30, true, armObject[0]);
	DrawBlockBack(30, true, armObject[1]);
	DrawBlockLeft(30, true, armObject[2]);
	DrawBlockRight(30, true, armObject[3]);
	DrawBlockTop(30, true, armObject[4]);
	DrawBlockBottom(30, true, armObject[5]);
	glScaled(2, 1.333333, 2);

	glPushMatrix(); // ������
	glTranslated(0, -45, 0);
	glRotatef(rightElbowX, 1, 0, 0);
	glScaled(0.5, 0.75, 0.5);
	glPushMatrix();
	DrawBlockFront(30, true, handObject[0]);
	DrawBlockBack(30, true, handObject[1]);
	DrawBlockLeft(30, true, handObject[2]);
	DrawBlockRight(30, true, handObject[3]);
	DrawBlockTop(30, true, handObject[4]);
	DrawBlockBottom(30, true, handObject[5]);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();


	glPushMatrix(); // ����
	glTranslated(45, 44, 0);
	glRotatef(-leftShoulderX - 90, 1, 0, 0);
	glRotatef(leftShoulderY, 0, 1, 0);
	glRotatef(leftShoulderZ, 0, 0, 1);
	glScaled(0.5, 0.75, 0.5);
	DrawBlockFront(30, true, armObject[0]);
	DrawBlockBack(30, true, armObject[1]);
	DrawBlockLeft(30, true, armObject[2]);
	DrawBlockRight(30, true, armObject[3]);
	DrawBlockTop(30, true, armObject[4]);
	DrawBlockBottom(30, true, armObject[5]);
	glScaled(2, 1.333333, 2);

	glPushMatrix(); // �޼�
	glTranslated(0, -45, 0);
	glScaled(0.5, 0.75, 0.5);
	DrawBlockFront(30, true, handObject[0]);
	DrawBlockBack(30, true, handObject[1]);
	DrawBlockLeft(30, true, handObject[2]);
	DrawBlockRight(30, true, handObject[3]);
	DrawBlockTop(30, true, handObject[4]);
	DrawBlockBottom(30, true, handObject[5]);
	glPopMatrix();
	glPopMatrix();
	//glPopMatrix();


	 // -------------------------------------------------------------------------

	glPushMatrix(); // ������ �����
	glTranslated(-15, -40, 0);
	glScaled(0.5, 0.75, 0.5);
	DrawBlockFront(30, true, legObject[0]);
	DrawBlockBack(30, true, legObject[1]);
	DrawBlockLeft(30, true, legObject[2]);
	DrawBlockRight(30, true, legObject[3]);
	DrawBlockTop(30, true, legObject[4]);
	DrawBlockBottom(30, true, legObject[5]);
	glScaled(2, 1.333333, 2);

	glPushMatrix(); //������ ���Ƹ� �� ��
	glTranslated(0, -45, 0);
	glScaled(0.5, 0.75, 0.5);
	DrawBlockFront(30, true, footObject[0]);
	DrawBlockBack(30, true, footObject[1]);
	DrawBlockLeft(30, true, footObject[2]);
	DrawBlockRight(30, true, footObject[3]);
	DrawBlockTop(30, true, footObject[4]);
	DrawBlockBottom(30, true, footObject[5]);
	glPopMatrix();

	glPopMatrix();


	glPushMatrix(); //���� �����
	glTranslated(15, -40, 0);
	glScaled(0.5, 0.75, 0.5);
	DrawBlockFront(30, true, legObject[0]);
	DrawBlockBack(30, true, legObject[1]);
	DrawBlockLeft(30, true, legObject[2]);
	DrawBlockRight(30, true, legObject[3]);
	DrawBlockTop(30, true, legObject[4]);
	DrawBlockBottom(30, true, legObject[5]);
	glScaled(2, 1.333333, 2);

	glPushMatrix(); // ���� ���Ƹ� �� ��
	glTranslated(0, -45, 0);
	glScaled(0.5, 0.75, 0.5);
	DrawBlockFront(30, true, footObject[0]);
	DrawBlockBack(30, true, footObject[1]);
	DrawBlockLeft(30, true, footObject[2]);
	DrawBlockRight(30, true, footObject[3]);
	DrawBlockTop(30, true, footObject[4]);
	DrawBlockBottom(30, true, footObject[5]);
	glPopMatrix();

	glPopMatrix();

	glPopMatrix();
}
void MapTextRead6()
{
	// �̷� 6�� �б�
	FILE *fps6;
	fps6 = fopen("�̷�6.txt", "rt");
	if (fps6 == NULL) {
		printf("�б� ���� \n");
	}
	char ch6;
	int i = 0;
	int j = 0;
	while (fscanf(fps6, "%c", &ch6) != EOF) {
		if (strchr(&ch6, '\n') == NULL) {
			mapData[5][i][j] = ch6;
			j++;
			if (j == 30) {
				j = 0;
				i++;
			}
		}
	}
	printf("%d, %d\n", i, j);

	fclose(fps6);
}
void MapTextRead5()
{
	// �̷� 5�� �б�
	FILE *fps5;
	fps5 = fopen("�̷�5.txt", "rt");
	if (fps5 == NULL) {
		printf("�б� ���� \n");
	}
	char ch5;
	int i = 0;
	int j = 0;
	while (fscanf(fps5, "%c", &ch5) != EOF) {
		if (strchr(&ch5, '\n') == NULL) {
			mapData[4][i][j] = ch5;
			j++;
			if (j == 30) {
				j = 0;
				i++;
			}
		}
	}
	printf("%d, %d\n", i, j);

	fclose(fps5);
}
void MapTextRead4()
{
	// �̷� 4�� �б�
	FILE *fps4;
	fps4 = fopen("�̷�4.txt", "rt");
	if (fps4 == NULL) {
		printf("�б� ���� \n");
	}
	char ch4;
	int i = 0;
	int j = 0;
	while (fscanf(fps4, "%c", &ch4) != EOF) {
		if (strchr(&ch4, '\n') == NULL) {
			mapData[3][i][j] = ch4;
			j++;
			if (j == 30) {
				j = 0;
				i++;
			}
		}
	}
	printf("%d, %d\n", i, j);

	fclose(fps4);
}
void MapTextRead3()
{
	// �̷� 3�� �б�
	FILE *fps3;
	fps3 = fopen("�̷�3.txt", "rt");
	if (fps3 == NULL) {
		printf("�б� ���� \n");
	}
	char ch3;
	int i = 0;
	int j = 0;
	while (fscanf(fps3, "%c", &ch3) != EOF) {
		if (strchr(&ch3, '\n') == NULL) {
			mapData[2][i][j] = ch3;
			j++;
			if (j == 30) {
				j = 0;
				i++;
			}
		}
	}
	printf("%d, %d\n", i, j);

	fclose(fps3);
}
void MapTextRead2()
{
	// �̷� 2�� �б�
	FILE *fps2;
	fps2 = fopen("�̷�2.txt", "rt");
	if (fps2 == NULL) {
		printf("�б� ���� \n");
	}
	char ch2;
	int i = 0;
	int j = 0;
	while (fscanf(fps2, "%c", &ch2) != EOF) {
		if (strchr(&ch2, '\n') == NULL) {
			mapData[1][i][j] = ch2;
			j++;
			if (j == 30) {
				j = 0;
				i++;
			}
		}
	}
	printf("%d, %d\n", i, j);

	fclose(fps2);
}
void MapTextRead1()
{
	// �̷� 1�� �б�
	FILE *fps1;
	fps1 = fopen("�̷�1.txt", "rt");
	if (fps1 == NULL) {
		printf("�б� ���� \n");
	}
	char ch1;
	int i = 0;
	int j = 0;
	while (fscanf(fps1, "%c", &ch1) != EOF) {
		if (strchr(&ch1, '\n') == NULL) {
			mapData[0][i][j] = ch1;
			j++;
			if (j == 30) {
				j = 0;
				i++;
			}
		}
	}
	printf("%d, %d\n", i, j);
	fclose(fps1);
}

void DrawBlock(GLuint object[])
{
	glPushMatrix();
	int i = 0;
	for (int i = 0; i < 30; ++i) {  // ����
		for (int j = 0; j < 30; ++j) {  // ����
			if (mapData[changeMapNumber][i][j] == 88) {
				LocationBlock(object, i, changeYpos, j);
			}
		}
	}
	glPopMatrix();
}

void CollisionCheck()
{

	if (playerX <= 0)
		playerX = 0;
	// ��ǥ�� ��ġ�� int������ �޾Ƽ� �ʵ����Ϳ� ��üũ�Ѵ�
	int X = (playerX / 480);
	int Z = (playerZ / 480);
	//���� < - �׸�
	//��ۡ�    �� < - �÷��̾�
	//����    �÷��̾� �������� 8���� �浹 üũ�� �Ѵ�.
	if (changeDown == false) {   //  ���� �������� �浹üũ�� ����.
		for (int z = Z - 1; z < Z + 2; z++)
		{
			for (int x = X - 1; x < X + 2; x++)
			{
				if (mapData[changeMapNumber][x][z] == 'X')
				{
					if ((x == X) && (z == Z))  // ���� ��ġ üũ 
					{
						if (playerX < x * 480 + 120)
							playerX = x * 480;
						else if (playerX > x * 480)
							playerX = x * 480 + 480;
						else if (playerZ < z * 480 + 60)
							playerZ = z * 480;
						else if (playerZ > z * 480)
							playerZ = z * 480 + 480;
					}
					else if ((x == X - 1) && (z == Z - 1)) //�밢�� üũ
					{
						if ((playerX < ((x * 480) + 480 + collisionDist)) && (playerZ < ((z * 480) + 480 + collisionDist)))
						{
							playerX = ((x * 480) + 480 + collisionDist);
							playerZ = ((z * 480) + 480 + collisionDist);
						}
					}
					else if ((x == X - 1) && (z == Z + 1))
					{
						if ((playerX < ((x * 480) + 480 + collisionDist)) && (((z * 480) - collisionDist) < playerZ))
						{
							playerX = ((x * 480) + 480 + collisionDist);
							playerZ = ((z * 480) - collisionDist);
						}
					}
					else if ((x == X + 1) && (z == Z - 1))
					{
						if ((((x * 480) - collisionDist) < playerX) && (playerZ < ((z * 480) + 480 + collisionDist)))
						{
							playerX = ((x * 480) - collisionDist);
							playerZ = ((z * 480) + 480 + collisionDist);
						}
					}
					else if ((x == X + 1) && (z == Z + 1))
					{
						if ((((x * 480) - collisionDist) < playerX) && (((z * 480) - collisionDist) < playerZ))
						{
							playerX = ((x * 480) - collisionDist);
							playerZ = ((z * 480) - collisionDist);
						}
					}
					else if (x == X - 1) // �⺻ �߾ӿ��� ���� �¿� üũ(���� �׸� ����)
					{
						if (playerX < ((x * 480) + 480 + collisionDist))
							playerX = ((x * 480) + 480 + collisionDist);
					}
					else if (X + 1 == x)
					{
						if (((x * 480) - collisionDist) < playerX)
							playerX = ((x * 480) - collisionDist);
					}
					else if (z == Z - 1)
					{
						if (playerZ < ((z * 480) + 480 + collisionDist))
							playerZ = ((z * 480) + 480 + collisionDist);
					}
					else if (Z + 1 == z)
					{
						if (((z * 480) - collisionDist) < playerZ)
							playerZ = ((z * 480) - collisionDist);
					}
				}
			}
		}
	}
}

void show_Light() {
	GLfloat AmbientLight[] = { 0.1, 0.1, 0.1, 1.0f };
	//GLfloat DiffuseLight[] = { 1.0, 1.0, 1.0, 1.0f };
	GLfloat lightpos[] = { playerX, 200, playerZ, 1 };
	GLfloat SpecularLight[] = { 1, 1, 1, 1.0 };
	glLightf(GL_LIGHT0, GL_SPOT_DIRECTION, (0, 0, 1));
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, (25));
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, AmbientLight);
	glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, AmbientLight);
	//glLightfv(GL_LIGHT0, GL_DIFFUSE, DiffuseLight);
	//glLightfv(GL_LIGHT0, GL_SPECULAR, SpecularLight);
	glLighti(GL_LIGHT0, GL_SPOT_EXPONENT, 5);
}

void draw_UI(int CharX, int CharZ) {

	glPushMatrix();

	glViewport(0, 0, 1200, 800);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, 1200, 800, 0, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//glPopMatrix();

	glPushMatrix(); // ���� �ð� ǥ��
	glColor3f(255.0f,255.0f,255.0f);
	glTranslatef(550, 30, 0);
	//glScalef(2.0f, 2.0f, 2.0f);
	glRasterPos2f(0, 0);
	glColor3f(255.0f, 255.0f, 255.0f);
	sprintf(drawTimeCount, "Time remaining until maze is changed : %d", timeCount);
	glColor3f(255.0f, 255.0f, 255.0f);
	int len = (int)strlen(drawTimeCount);
	for (int i = 0; i < len; i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, drawTimeCount[i]);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(990, 0, 0);
	for (int i = 0; i < 30; ++i) {
		for (int j = 0; j < 30; ++j) {
			int dataX = (i * 7), dataY = (i * 7) + 7;
			int LimitH = (j * 7) + 7;
			int char_X = (CharX / 480), char_Z = (CharZ / 480);  // ��ǥ�� ���
			glBegin(GL_POLYGON);
			if (i == char_X && j == char_Z) {  // ĳ���� ��ġ ǥ��
				glColor3f(0, 10, 0);
			}
			else if (i > 12 && i < 17 && j>12 && j < 17) { // ������Ƽ��
				glColor3f(0, 10, 10);
			}
			else if (i == 29 && j == 14) { // Ż�� ����
				glColor3f(0, 10, 7);
			}
			else {
				glColor3f(0.1, 0.1, 0.1);  //������ �� 
			}
			// �׸���
			glVertex3f(dataX, 0, 0);
			glVertex3f(dataX, LimitH, 0);
			glVertex3f(dataY, LimitH, 0);
			glVertex3f(dataY, 0, 0);
			glEnd();
		}
	}
	glPopMatrix();
}

void FlashLight()
{
	glPushMatrix();
	glTranslatef(0, 60, 0);
	glRotatef(-rightSholderX - 90, 1, 0, 0);
	glTranslatef(0, -15, 50);

	// ���� ���� �κ�
	glPushMatrix();
	glColor3f(1.0, 1.0, 0.2);
	glTranslatef(-10, -10, 35);
	glScalef(0.35, 0.35, 0.5);
	glutSolidCube(40);
	glPopMatrix();

	// ���� �Ӹ� �κ�
	glPushMatrix();
	glColor3f(0.1, 0.1, 0.1);
	glTranslatef(-10, -10, 55);
	glScalef(0.35, 0.35, 0.5);
	glutSolidCube(40);
	glPopMatrix();
	glPopMatrix();
}