#include "Define.h"

void HeadTexture(GLuint object[])
{
	// Front
	Load_TextureBMP(object, 0, "Resource/�Ӹ�/HeadFront.bmp");
	// Back
	Load_TextureBMP(object, 1, "Resource/�Ӹ�/HeadBack.bmp");
	// Left
	Load_TextureBMP(object, 2, "Resource/�Ӹ�/HeadLeft.bmp");
	// Right
	Load_TextureBMP(object, 3, "Resource/�Ӹ�/HeadRight.bmp");
	// Top
	Load_TextureBMP(object, 4, "Resource/�Ӹ�/HeadTop.bmp");
	// Bottom
	Load_TextureBMP(object, 5, "Resource/�Ӹ�/HeadBottom.bmp");

	// �ؽ�ó ��� ����
	//glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);
	// �ؽ�ó ���� Ȱ��ȭ
}
void BodyTexture(GLuint object[])
{
	// Front
	Load_TextureBMP(object, 0, "Resource/����/BodyFront.bmp");
	// Back
	Load_TextureBMP(object, 1, "Resource/����/BodyBack.bmp");
	// Left
	Load_TextureBMP(object, 2, "Resource/����/BodyLeft.bmp");
	// Right
	Load_TextureBMP(object, 3, "Resource/����/BodyRight.bmp");
	// Top
	Load_TextureBMP(object, 4, "Resource/����/BodyTop.bmp");
	// Bottom
	Load_TextureBMP(object, 5, "Resource/����/BodyBottom.bmp");
}

void ArmTexture(GLuint object[], GLuint object2[])
{
	// ��---------------------------------------------------------------------
	// Front
	Load_TextureBMP(object, 0, "Resource/��/ArmsFront.bmp");
	// Back
	Load_TextureBMP(object, 1, "Resource/��/ArmsBack.bmp");
	// Left
	Load_TextureBMP(object, 2, "Resource/��/ArmsLeft.bmp");
	// Right
	Load_TextureBMP(object, 3, "Resource/��/ArmsRight.bmp");
	// Top
	Load_TextureBMP(object, 4, "Resource/��/ArmsTop.bmp");
	// Bottom
	Load_TextureBMP(object, 5, "Resource/��/ArmsBottom.bmp");

	// ��---------------------------------------------------------------------
	// Front
	Load_TextureBMP(object2, 0, "Resource/��/HandFront.bmp");
	// Back
	Load_TextureBMP(object2, 1, "Resource/��/HandBack.bmp");
	// Left
	Load_TextureBMP(object2, 2, "Resource/��/HandLeft.bmp");
	// Right
	Load_TextureBMP(object2, 3, "Resource/��/HandRight.bmp");
	// Top
	Load_TextureBMP(object2, 4, "Resource/��/HandTop.bmp");
	// Bottom
	Load_TextureBMP(object2, 5, "Resource/��/HandBottom.bmp");
}
void LegTexture(GLuint object[], GLuint object2[])
{
	// �����---------------------------------------------------------------------
	// Front
	Load_TextureBMP(object, 0, "Resource/�����/LegsFront.bmp");
	// Back
	Load_TextureBMP(object, 1, "Resource/�����/LegsBack.bmp");
	// Left
	Load_TextureBMP(object, 2, "Resource/�����/LegsLeft.bmp");
	// Right
	Load_TextureBMP(object, 3, "Resource/�����/LegsRight.bmp");
	// Top
	Load_TextureBMP(object, 4, "Resource/�����/LegsTop.bmp");
	// Bottom
	Load_TextureBMP(object, 5, "Resource/�����/LegsBottom.bmp");

	// ���Ƹ� + ��---------------------------------------------------------------------
	// Front
	Load_TextureBMP(object2, 0, "Resource/���Ƹ�/FootFront.bmp");
	// Back
	Load_TextureBMP(object2, 1, "Resource/���Ƹ�/FootBack.bmp");
	// Left
	Load_TextureBMP(object2, 2, "Resource/���Ƹ�/FootLeft.bmp");
	// Right
	Load_TextureBMP(object2, 3, "Resource/���Ƹ�/FootRight.bmp");
	// Top
	Load_TextureBMP(object2, 4, "Resource/���Ƹ�/FootTop.bmp");
	// Bottom
	Load_TextureBMP(object2, 5, "Resource/���Ƹ�/FootBottom.bmp");
}