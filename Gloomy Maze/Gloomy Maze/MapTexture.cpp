#include "Define.h"

void GroundTexture(GLuint object[])
{
	Load_TextureBMP(object,0,"Resource/ground.bmp");

	//�ؽ��İ� �������� �ؽ����� ����� �����ȼ�������� ���踦 �����Ѵ�
	//glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);
	
}

void BlockTexture(GLuint object[])
{
	// Front
	Load_TextureBMP(object, 0, "Resource/block.bmp");
	// Back
	Load_TextureBMP(object, 1, "Resource/block.bmp");
	// Left
	Load_TextureBMP(object, 2, "Resource/block.bmp");
	// Right
	Load_TextureBMP(object, 3, "Resource/block.bmp");
	// Top
	Load_TextureBMP(object, 4, "Resource/block.bmp");
	// Bottom
	Load_TextureBMP(object, 5, "Resource/block.bmp");

	// �ؽ�ó ��� ����
	//glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);
	// �ؽ�ó ���� Ȱ��ȭ
}

