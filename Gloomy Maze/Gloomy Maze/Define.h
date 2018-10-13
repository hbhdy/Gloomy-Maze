#ifndef __DEFINE_H
#define __DEFINE_H
#include <GL/glut.h> // includes gl.h glu.h
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>


//#include <mmsystem.h>

// BGM ����� ����
#pragma comment(lib, "winmm.lib") 

// OpenGL Aux ����� ����
//#pragma comment(lib, "./OpenGL_Aux/GLAUX")
#include "OpenGL_Aux/GLAUX.H"
#pragma comment(lib, "./OpenGL_Aux/GLAUX")

//legacy_stdio_definitions.lib  <- ��Ŀ�� �߰����Ӽ��� �߰��Ͽ���.  ( �ȳ����� �ȵ��ư� )

void LocationGround(GLuint object, int x, int y, int z);
void SetGround(int size, GLuint object);
void LocationBlock(GLuint object[], int x, int y, int z);
void SetBlock(int size, GLuint object[]);

// �̷� �� �ؽ���
void BlockTexture(GLuint[]);
// �ٴ� �ؽ���
void GroundTexture(GLuint[]);
// �÷��̾� �ؽ���
void HeadTexture(GLuint[]);
void BodyTexture(GLuint[]);
void ArmTexture(GLuint[], GLuint[]);
void LegTexture(GLuint[], GLuint[]);
// ���� �ؽ��� 4��
void Ghost1Texture(GLuint[]);  
void Ghost2Texture(GLuint[]);
void Ghost3Texture(GLuint[]);
void Ghost4Texture(GLuint[]);


// �ٴ� �׸��� �Լ�
void DrawGround(GLuint);

// �� �׸��� �Լ�
void DrawBlock(GLuint[]);

// ���� �� �׸��� �Լ�
void DrawBlockTop(int, bool, GLuint);
void DrawBlockBottom(int, bool, GLuint);
void DrawBlockFront(int, bool, GLuint);
void DrawBlockBack(int, bool, GLuint);
void DrawBlockLeft(int, bool, GLuint);
void DrawBlockRight(int, bool, GLuint);

// �̷� �� ����
static GLuint blockObject[6];

// �ٴ� ����
static GLuint groundObject[1];

// �÷��̾� ����
static GLuint headObject[6];  // �Ӹ�
static GLuint bodyObject[6];  // ����
static GLuint armObject[6];   // �� 
static GLuint handObject[6];  // ��
static GLuint legObject[6];   // �����
static GLuint footObject[6];  // ���Ƹ� + ��

// ���� ����
static GLuint ghostObject1[6];           
static GLuint ghostObject2[6];
static GLuint ghostObject3[6];
static GLuint ghostObject4[6];



// ��Ʈ�� ����
void Load_TextureBMP(GLuint[], int, char *);
AUX_RGBImageRec *LoadBMP(char *Filename);

#endif