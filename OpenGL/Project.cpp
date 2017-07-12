#include <stdlib.h>
//#include "TextureBuilder.h"
#include "Model_3DS.h"
//#include "GLTexture.h"
#include <glut.h>
#include <math.h>
#include <string>
#include "SOIL.h"
#include <iostream>
#include <Windows.h>
#include <MMSystem.h>

int counterForShelf = 0;
int score = 300000;
void renderBigTextDisplay(float, float, float, const char *string);
using namespace std;
int room2Unlocked = 0;
int room3Unlocked = 0;
//screen width and height
int height = glutGet(GLUT_SCREEN_HEIGHT);
int width = glutGet(GLUT_SCREEN_WIDTH);
//mouseX direction for camera rotation
float mouseX = 0;
int rot = 0;
double timerBarX = 50;
int deactivateMedicalShelf;

int takeTheKeyFromBag = 0;
int takeTheKeyFromVase = 0;
int takeTheKeyFromKhazna = 0;

int takeTheKeyFromMedicalShelf = 0;

int arrayOfKeysForRoom2[3];

int arrayOfKeysForRoom3[3];


GLuint floorTiles;
GLuint frontfacingWallOfSecondRoom;
GLuint wallBlood;
GLuint corridorFloor;
GLuint corridorRightAndLeft;
GLuint paperWall;
GLuint tdoor;
GLuint livingdoor;
GLuint bathdoor;




//##Camera Movement Variables##//
float ZDirectionVariable = -7;  //inside and outside the screen
float XDirectionVariable = 0; //left and right



// Model Variables
Model_3DS model_bath;
Model_3DS model_cabane;
Model_3DS model_sink;
Model_3DS model_table;
Model_3DS model_woodenchair;
Model_3DS model_fan;
Model_3DS model_fire;
Model_3DS model_sk;
Model_3DS model_crulchair;
Model_3DS model_dolab;
Model_3DS model_mshelf;
Model_3DS model_safe;
Model_3DS model_vase;
Model_3DS model_wtable;
Model_3DS model_tool1;
Model_3DS model_tool2;
Model_3DS model_tool3;
Model_3DS model_tool4;
Model_3DS model_tool5;
Model_3DS model_tool6;
Model_3DS model_bag;


float cameraVector[2];
float bathVector[2];


void objectsVectors()
{
	cameraVector[0] = XDirectionVariable;
	cameraVector[1] = ZDirectionVariable;

	bathVector[0] = -0.68;
	bathVector[1] = 5;

}

void setupLights() {

	GLfloat lmodel_ambient[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);

	GLfloat l0Diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat l0Ambient[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat l0Position[] = { mouseX, 0.0f, ZDirectionVariable, 1 };
	GLfloat l0Direction[] = { 0.0, 0.0, 1.0 };

	glLightfv(GL_LIGHT0, GL_DIFFUSE, l0Diffuse);
	glLightfv(GL_LIGHT0, GL_AMBIENT, l0Ambient);
	glLightfv(GL_LIGHT0, GL_POSITION, l0Position);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 20.0);
	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 2.0);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, l0Direction);



}

void mouseAngleRotation(int x, int y)

{
	mouseX = (x - (width / 2));
	cout << mouseX << endl;

}

void setupCamera() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, width / height, 0.001, 100);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(XDirectionVariable, 0, ZDirectionVariable, XDirectionVariable, 0, 14, 0.0, 1.0, 0.0);

}
bool isCollidedWithBanyo()
{
	if ((ZDirectionVariable > 2) && (ZDirectionVariable < 5) && (XDirectionVariable<0.9) && (XDirectionVariable>0.5))
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool enableCollidedWithMedicalShelf()
{
	if ((ZDirectionVariable > 4.5) && (ZDirectionVariable < 5) && (XDirectionVariable<0.6) && (XDirectionVariable>-0.6))
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool isCollidedWithSofra()
{
	if ((ZDirectionVariable > 0) && (ZDirectionVariable < 2) && (XDirectionVariable<0.9) && (XDirectionVariable>-0.4))
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool enableCollidedWithSofra()
{
	if ((ZDirectionVariable > -0.7) && (ZDirectionVariable < 1.7) && (XDirectionVariable<0.9) && (XDirectionVariable>-0.4))
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool canGoInsideRoom2()
{
	if (room2Unlocked == 0)
	{
		if ((/*Secondwall*/ (ZDirectionVariable > 1.8) && (ZDirectionVariable<2) && (XDirectionVariable>-1) && (XDirectionVariable<1) /*Secondwall*/))
		{
			return false;
		}
	}
	else
	{
		return true;
	}
}
bool canGoInsideRoom3()
{
	if (room3Unlocked == 0)
	{
		if ((/*thirdwall*/ (ZDirectionVariable > 4.8) && (ZDirectionVariable<5) && (XDirectionVariable>-1) && (XDirectionVariable<1) /*thirdwall*/))
		{
			return false;
		}
	}
	else
	{
		return true;
	}
}
bool isCollidedWithShelf()
{
	if ((ZDirectionVariable > -1) && (ZDirectionVariable < 0) && (XDirectionVariable<-0.7) && (XDirectionVariable>-1))
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool enableCollidedWithShelf()
{
	if ((ZDirectionVariable > -1.3) && (ZDirectionVariable < -0.3) && (XDirectionVariable<-0.7) && (XDirectionVariable>-1))
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool enableCollidedWithKhazna()
{

	if ((ZDirectionVariable > 1.5) && (ZDirectionVariable<2) && (XDirectionVariable>-0.6) && (XDirectionVariable<0.6))
	{
		return true;
	}
	else
	{
		return false;
	}

}
bool isCollidedWithWalls()
{
	if ((/*firstwall*/ (ZDirectionVariable > -2) && (ZDirectionVariable<-1.8) && (XDirectionVariable>-0.6) && (XDirectionVariable<1) /*firstwall*/) || (/*Secondwall*/ (ZDirectionVariable > 1.8) && (ZDirectionVariable<2) && (XDirectionVariable>-0.6) && (XDirectionVariable<1) /*Secondwall*/) || (/*thirdwall*/ (ZDirectionVariable > 4.8) && (ZDirectionVariable<5) && (XDirectionVariable>-0.6) && (XDirectionVariable<1) /*thirdwall*/))
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool isCollidedWith7ood()
{
	if ((/*thirdwall*/ (ZDirectionVariable > 3.4) && (ZDirectionVariable<4.5) && (XDirectionVariable<-0.6) && (XDirectionVariable>-1) /*thirdwall*/))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void cameraMovement(unsigned char k, int x, int y) {

	if (mouseX>-680 && mouseX<-640)
	{

		if (k == 'w')
		{
			if (!(isCollidedWithSofra() || isCollidedWithShelf() || isCollidedWithWalls() || isCollidedWith7ood() || isCollidedWithBanyo() || !canGoInsideRoom2() || !canGoInsideRoom3()))
			{

				if (ZDirectionVariable < 14 && XDirectionVariable>-0.9)

				{
					ZDirectionVariable -= 0.09;
					XDirectionVariable -= 0.2;

				}

			}
			else
			{
				ZDirectionVariable += 0.3;
				XDirectionVariable += 0.2;
			}

		}

	}


	////////////##################LAW BASES FEL NOS STARTTT#########################//////////
	if (mouseX<26 && mouseX>-26)
	{

		if (k == 'w')
		{
			if (!(isCollidedWithSofra() || isCollidedWithShelf() || isCollidedWithWalls() || isCollidedWith7ood() || isCollidedWithBanyo() || !canGoInsideRoom2() || !canGoInsideRoom3()))
			{

				if (ZDirectionVariable < 14)

				{
					ZDirectionVariable += 0.09;
				}

			}
			else
			{
				ZDirectionVariable -= 0.3;
			}

		}

	}


	////////////##############LAW BASES FEL NOS END#########################//////////



	////////////##############LAW BASES YMEEN SHWAYA STARTTT################//////////
	if (mouseX<180 && mouseX>26)
	{

		if (k == 'w')
		{

			if (ZDirectionVariable < 14 && XDirectionVariable > -0.9)
			{
				if (!(isCollidedWithSofra() || isCollidedWithShelf() || isCollidedWithWalls() || isCollidedWith7ood() || isCollidedWithBanyo() || !canGoInsideRoom2() || !canGoInsideRoom3()))
				{

					ZDirectionVariable += 0.04;
					XDirectionVariable -= 0.08;
				}
				else
				{
					ZDirectionVariable -= 0.3;
					XDirectionVariable += 0.3;
				}
			}

		}



	}

	////////////##############LAW BASES YMEEN SHWAYA STARTTT#########################//////////

	////////////##############LAW BASES SHMAL SHWAYA STARTTT#########################//////////
	if (mouseX > -180 && mouseX < -26)
	{

		if (k == 'w')
		{
			if (ZDirectionVariable < 14 && XDirectionVariable < 0.9)

			{
				if (!(isCollidedWithSofra() || isCollidedWithShelf() || isCollidedWithWalls() || isCollidedWith7ood() || isCollidedWithBanyo() || !canGoInsideRoom2() || !canGoInsideRoom3()))
				{


					ZDirectionVariable += 0.04;
					XDirectionVariable += 0.08;
				}
				else
				{
					ZDirectionVariable -= 0.3;
					XDirectionVariable += 0.3;
				}

			}

		}


	}

	////////////##############LAW BASES YMEEN AWE  STARTTT#########################//////////
	if (mouseX > 180 && mouseX < 430)
	{

		if (k == 'w')
		{
			if (XDirectionVariable > -0.9)

			{
				if (!(isCollidedWithSofra() || isCollidedWithShelf() || isCollidedWithWalls() || isCollidedWith7ood() || isCollidedWithBanyo() || !canGoInsideRoom2() || !canGoInsideRoom3()))
				{

					XDirectionVariable -= 0.08;
				}
				else
				{
					XDirectionVariable += 0.3;
				}
			}

		}


	}
	////////////#################### LAW BASES YMEEN AWE END #########################//////////

	////////////#################### LAW BASES WARA Shwaya shemal  START #########################//////////
	if (mouseX > 430 && mouseX < 540)
	{

		if (k == 'w')
		{
			if (XDirectionVariable > -0.9)

			{
				if (!(isCollidedWithSofra() || isCollidedWithShelf() || isCollidedWithWalls() || isCollidedWith7ood() || isCollidedWithBanyo() || !canGoInsideRoom2() || !canGoInsideRoom3()))
				{

					ZDirectionVariable -= 0.04;
					XDirectionVariable -= 0.04;
				}
				else
				{
					ZDirectionVariable += 0.3;
					XDirectionVariable += 0.3;
				}

			}

		}
	}
	////////////#################### LAW BASES WARA Shwaya Shemal END #########################//////////

	if (mouseX < -430 && mouseX >-540)
	{

		if (k == 'w')
		{
			if (XDirectionVariable <0.9)

			{
				if (!(isCollidedWithSofra() || isCollidedWithShelf() || isCollidedWithWalls() || isCollidedWith7ood() || isCollidedWithBanyo() || !canGoInsideRoom2() || !canGoInsideRoom3()))
				{

					ZDirectionVariable -= 0.04;
					XDirectionVariable += 0.04;
				}
				else
				{
					ZDirectionVariable += 0.3;
					XDirectionVariable -= 0.3;
				}
			}

		}
	}
	////////////#################### LAW BASES WARA SHWAYA YMEEN START #########################//////////
	if (mouseX <-180 && mouseX > -430)
	{

		if (k == 'w')
		{
			if (XDirectionVariable <0.9)

			{
				if (!(isCollidedWithSofra() || isCollidedWithShelf() || isCollidedWithWalls() || isCollidedWith7ood() || isCollidedWithBanyo() || !canGoInsideRoom2() || !canGoInsideRoom3()))
				{

					XDirectionVariable += 0.03;
				}
				else
				{
					XDirectionVariable -= 0.3;
				}
			}

		}
	}
	////////////#################### LAW BASES WARA SHWAYA YMEEN END #########################//////////


	////////////#################### LAW BASES WARA START #########################//////////
	if ((mouseX > 540 && mouseX < 640) || (mouseX <-540 && mouseX > -640))
	{

		if (k == 'w')
		{
			if (ZDirectionVariable >-7)

			{
				if (!(isCollidedWithSofra() || isCollidedWithShelf() || isCollidedWithWalls() || isCollidedWith7ood() || isCollidedWithBanyo() || !canGoInsideRoom2() || !canGoInsideRoom3()))
				{

					ZDirectionVariable -= 0.07;
				}
				else
				{
					ZDirectionVariable += 0.3;
				}
			}

		}

	}
	////////////#################### LAW BASES WARA END #########################//////////


	if (k == 'e')
	{


		if (enableCollidedWithShelf())
		{

			takeTheKeyFromBag = 1;
			arrayOfKeysForRoom2[0] = 1;
			PlaySound(TEXT("8 Bit Coin 1 1 SOUND Effect"), NULL, SND_FILENAME | SND_ASYNC);
		}
		if (enableCollidedWithSofra())
		{
			takeTheKeyFromVase = 1;
			arrayOfKeysForRoom2[1] = 1;
		}

		if (enableCollidedWithKhazna())
		{


			takeTheKeyFromKhazna = 1;
			arrayOfKeysForRoom2[2] = 1;

		}
		if (enableCollidedWithMedicalShelf())
		{

			arrayOfKeysForRoom3[0] = 1;
			if (counterForShelf == 1)
			{
				arrayOfKeysForRoom3[1] = 1;
			}
			if (counterForShelf == 2)
			{
				arrayOfKeysForRoom3[2] = 1;
			}
			counterForShelf++;


		}
	}
	glutPostRedisplay();

}

void Animation() {

	glutPostRedisplay();
}

void room1() {
	glPushMatrix();
	//frontClosing
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, wallBlood);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3d(-1, -1, 4);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3d(-1, 1, 4);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3d(0.6, 1, 4);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3d(0.6, -1, 4);
	glEnd();
	glPopMatrix();


	//frontClosing
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, wallBlood);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3d(-0.5, 0.2, 4);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3d(-0.5, 1, 4);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3d(1, 1, 4);
	glTexCoord2f(0.0f, 1 - .0f);
	glVertex3d(1, 0.2, 4);
	glEnd();
	glPopMatrix();

	//top//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor3f(0.54, 0.54, 0.54);
	glVertex3d(-1, 1, 0);
	glVertex3d(-1, 1, 4);
	glVertex3d(1, 1, 4);
	glVertex3d(1, 1, 0);
	glEnd();
	glPopMatrix();
	//bottom//
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, floorTiles);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3d(-1, -1, 0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3d(-1, -1, 4);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3d(1, -1, 4);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3d(1, -1, 0);
	glEnd();
	glPopMatrix();
	//right//
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, corridorRightAndLeft);
	glBegin(GL_QUADS);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3d(1, 1, 0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3d(1, 1, 4);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3d(1, -1, 4);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3d(1, -1, 0);
	glEnd();
	glPopMatrix();
	//left//
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, corridorRightAndLeft);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3d(-1, 1, 0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3d(-1, 1, 4);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3d(-1, -1, 4);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3d(-1, -1, 0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslated(-1.3, -0.1, 1);
	glRotated(90, 0, 1, 0);
	glScaled(0.8, 0.8, 0.8);
	// Draw table Model
	glPushMatrix();
	glTranslated(-0.2, -0.95, 1);
	glRotated(50, 0, 1, 0);
	glScaled(0.001, 0.001, 0.001);
	model_table.Draw();
	glPopMatrix();
	// Draw chair 1 Model
	glPushMatrix();
	glTranslated(0.5, -0.95, 0.8);
	glRotated(310, 0, 1, 0);
	glScaled(0.001, 0.001, 0.001);
	model_woodenchair.Draw();
	glPopMatrix();
	// Draw chair 2 Model
	glPushMatrix();
	glTranslated(0.5, -0.95, 1.4);
	glRotated(310, 0, 1, 0);
	glScaled(0.001, 0.001, 0.001);
	model_woodenchair.Draw();
	glPopMatrix();
	// Draw chair 3 Model
	glPushMatrix();
	glTranslated(-0.8, -0.95, 0.7);
	glRotated(130, 0, 1, 0);
	glScaled(0.001, 0.001, 0.001);
	model_woodenchair.Draw();
	glPopMatrix();
	// Draw chair 4 Model
	glPushMatrix();
	glTranslated(-0.9, -0.95, 1.25);
	glRotated(130, 0, 1, 0);
	glScaled(0.001, 0.001, 0.001);
	model_woodenchair.Draw();
	glPopMatrix();
	glPopMatrix();
	// Draw fan Model
	glPushMatrix();
	glTranslated(0, 1, 0.7);
	glRotated(rot++, 0, 1, 0);
	glScaled(0.04, 0.04, 0.04);
	model_fan.Draw();
	glPopMatrix();
	////////Draw safe///
	glPushMatrix();
	glTranslated(0.3, 0, 0);
	glScaled(0.0003, 0.0003, 0.0003);
	model_safe.Draw();
	glPopMatrix();
	/////////////Draw vase
	glPushMatrix();
	glTranslated(-0.5, -0.6, 1.1);
	glScaled(0.01, 0.01, 0.01);
	model_vase.Draw();
	glPopMatrix();
	//////////Draw bag////
	glPushMatrix();
	glTranslated(0.9, -0.2, 2.2);
	glScaled(0.01, 0.01, 0.01);
	model_bag.Draw();
	glPopMatrix();

	////////Draw dolab///
	glPushMatrix();
	glTranslated(1.05, 0, 2);
	glRotated(180, 0, 1, 0);
	glRotated(180, 1, 0, 0);
	glScaled(0.02, 0.02, 0.02);
	model_dolab.Draw();
	glPopMatrix();

	glPopMatrix();
}
void room2() {
	glPushMatrix();
	//frontClosing
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, paperWall);
	glBegin(GL_QUADS);
	glColor3f(0.5, 0.5, 0.5);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3d(-1, -1, 4);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3d(-1, 1, 4);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3d(0.6, 1, 4);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3d(0.6, -1, 4);
	glEnd();
	glPopMatrix();
	//door
	if (room2Unlocked == 0)
	{

		glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, livingdoor);
		glBegin(GL_QUADS);

		glTexCoord2f(0.0f, 0.0f);
		glVertex3d(0.6, -1, 4);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3d(0.6, 0.2, 4);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3d(1, 0.2, 4);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3d(1, -1, 4);
		glEnd();
		glPopMatrix();
	}
	//frontClosing
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, paperWall);
	glBegin(GL_QUADS);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3d(-0.5, 0.2, 4);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3d(-0.5, 1, 4);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3d(1, 1, 4);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3d(1, 0.2, 4);
	glEnd();
	glPopMatrix();
	//front//

	//top//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor3f(0.54, 0.54, 0.54);
	glVertex3d(-1, 1, 0);
	glVertex3d(-1, 1, 4);
	glVertex3d(1, 1, 4);
	glVertex3d(1, 1, 0);
	glEnd();
	glPopMatrix();
	//bottom//
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, floorTiles);
	glBegin(GL_QUADS);
	glColor3f(0.54, 0.54, 0.54);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3d(-1, -1, 0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3d(-1, -1, 4);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3d(1, -1, 4);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3d(1, -1, 0);
	glEnd();
	glPopMatrix();
	//right//
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, wallBlood);
	glBegin(GL_QUADS);

	glColor3f(0.52, 0.52, 0.52);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3d(1, 1, 0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3d(1, 1, 4);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3d(1, -1, 4);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3d(1, -1, 0);
	glEnd();
	glPopMatrix();
	//left//
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, wallBlood);
	glBegin(GL_QUADS);
	glColor3f(0.52, 0.52, 0.52);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3d(-1, 1, 0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3d(-1, 1, 4);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3d(-1, -1, 4);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3d(-1, -1, 0);
	glEnd();
	glPopMatrix();
	// Draw bath Model
	glPushMatrix();
	glTranslated(-0.68, -1, 1);
	//glRotated(90, 0, 1, 0);
	glScaled(0.0009, 0.0009, 0.0009);
	model_bath.Draw();
	glPopMatrix();
	//// Draw cabane Model
	glPushMatrix();
	glTranslated(-0.7, -1, 2);
	glRotated(90, 0, 1, 0);
	glScaled(0.002, 0.002, 0.002);
	model_cabane.Draw();
	glPopMatrix();
	//// Draw sink Model
	glPushMatrix();
	glTranslated(0.8, -1, 1.5);
	glRotated(150, 0, 1, 0);
	glScaled(0.002, 0.002, 0.002);
	model_sink.Draw();
	glPopMatrix();
	//// Draw medical shelf Model
	if (deactivateMedicalShelf == 0)
	{
		glPushMatrix();
		glTranslated(0, -0.3, 0);
		glRotated(-90, 0, 1, 0);
		glScaled(0.02, 0.02, 0.02);
		model_mshelf.Draw();
		glPopMatrix();
	}
	///////Draw 2 ms////////
	if (deactivateMedicalShelf == 0)
	{
		glPushMatrix();
		glTranslated(1, -0.3, 0.5);
		glRotated(180, 0, 1, 0);
		glScaled(0.007, 0.007, 0.007);
		model_mshelf.Draw();
		glPopMatrix();
	}
	///////Draw 3 ms////////
	if (deactivateMedicalShelf == 0)
	{
		glPushMatrix();
		glTranslated(1, -0.3, 3);
		glRotated(180, 0, 1, 0);
		glScaled(0.007, 0.007, 0.007);
		model_mshelf.Draw();
		glPopMatrix();
	}
	glPopMatrix();
}
void room3() {
	glPushMatrix();
	//frontClosing
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, corridorRightAndLeft);
	glBegin(GL_QUADS);
	glTexCoord2d(0.0f, 0.0f);
	glVertex3d(-1, -1, 4);
	glTexCoord2d(1.0f, 0.0f);
	glVertex3d(-1, 1, 4);
	glTexCoord2d(1.0f, 1.0f);
	glVertex3d(0.6, 1, 4);
	glTexCoord2d(0.0f, 1.0f);
	glVertex3d(0.6, -1, 4);
	glEnd();
	glPopMatrix();
	//door
	if (room3Unlocked == 0){
		glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, tdoor);
		glBegin(GL_QUADS);

		glTexCoord2f(0.0f, 0.0f);
		glVertex3d(0.6, -1, 4);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3d(0.6, 0.2, 4);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3d(1, 0.2, 4);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3d(1, -1, 4);
		glEnd();
		glPopMatrix();
	}
	//frontClosing
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, frontfacingWallOfSecondRoom);
	glBegin(GL_QUADS);

	glTexCoord2d(0.0f, 0.0f);
	glVertex3d(-0.5, 0.2, 4);
	glTexCoord2d(1.0f, 0.0f);
	glVertex3d(-0.5, 1, 4);
	glTexCoord2d(1.0f, 1.0f);
	glVertex3d(1, 1, 4);
	glTexCoord2d(0.0f, 1.0f);
	glVertex3d(1, 0.2, 4);
	glEnd();
	glPopMatrix();
	//front//
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, frontfacingWallOfSecondRoom);
	glBegin(GL_QUADS);

	glTexCoord2d(0.0f, 0.0f);
	glVertex3d(-1, -1, 0);
	glTexCoord2d(1.0f, 0.0f);
	glVertex3d(-1, 1, 0);
	glTexCoord2d(1.0f, 1.0f);
	glVertex3d(1, 1, 0);
	glTexCoord2d(0.0f, 1.0f);
	glVertex3d(1, -1, 0);
	glEnd();
	glPopMatrix();
	//top//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor3f(0.54, 0.54, 0.54);
	glVertex3d(-1, 1, 0);
	glVertex3d(-1, 1, 4);
	glVertex3d(1, 1, 4);
	glVertex3d(1, 1, 0);
	glEnd();
	glPopMatrix();
	//bottom//
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, floorTiles);
	glBegin(GL_QUADS);

	glTexCoord2d(0.0f, 0.0f);
	glVertex3d(-1, -1, 0);
	glTexCoord2d(1.0f, 0.0f);
	glVertex3d(-1, -1, 4);
	glTexCoord2d(1.0f, 1.0f);
	glVertex3d(1, -1, 4);
	glTexCoord2d(0.0f, 1.0f);
	glVertex3d(1, -1, 0);
	glEnd();
	glPopMatrix();
	//right//
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, frontfacingWallOfSecondRoom);
	glBegin(GL_QUADS);

	glTexCoord2d(0.0f, 0.0f);
	glVertex3d(1, 1, 0);
	glTexCoord2d(1.0f, 0.0f);
	glVertex3d(1, 1, 4);
	glTexCoord2d(1.0f, 1.0f);
	glVertex3d(1, -1, 4);
	glTexCoord2d(0.0f, 1.0f);
	glVertex3d(1, -1, 0);
	glEnd();
	glPopMatrix();
	//left//
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, frontfacingWallOfSecondRoom);
	glBegin(GL_QUADS);

	glTexCoord2d(0.0f, 0.0f);
	glVertex3d(-1, 1, 0);
	glTexCoord2d(1.0f, 0.0f);
	glVertex3d(-1, 1, 4);
	glTexCoord2d(1.0f, 1.0f);
	glVertex3d(-1, -1, 4);
	glTexCoord2d(0.0f, 1.0f);
	glVertex3d(-1, -1, 0);
	glEnd();
	glPopMatrix();
	//skelaton////
	glPushMatrix();
	glTranslated(0.7, -1, 0.8);
	//glRotated(150, 0, 1, 0);
	glScaled(0.6, 0.6, 0.6);
	model_sk.Draw();
	glPopMatrix();
	//wtable////
	glPushMatrix();
	glTranslated(0, -0.9, 0.3);
	//glRotated(150, 0, 1, 0);
	glScaled(0.01, 0.01, 0.01);
	model_wtable.Draw();
	glPopMatrix();
	/////crul chair/////
	glPushMatrix();
	glTranslated(0, -0.5, 1.2);
	//glRotated(150, 0, 1, 0);
	glScaled(0.0007, 0.0007, 0.0007);
	model_crulchair.Draw();
	glPopMatrix();

	///tool1////
	glPushMatrix();
	glTranslated(0, -0.2, 0);
	//glRotated(150, 0, 1, 0);
	glScaled(0.003, 0.003, 0.003);
	model_tool1.Draw();
	glPopMatrix();
	///tool2////
	glPushMatrix();
	glTranslated(0.2, -0.1, 0);
	//glRotated(150, 0, 1, 0);
	glScaled(0.01, 0.01, 0.01);
	model_tool2.Draw();
	glPopMatrix();
	///tool3////
	glPushMatrix();
	glTranslated(0.4, -0.1, 0);
	//glRotated(150, 0, 1, 0);
	glScaled(0.001, 0.001, 0.001);
	model_tool3.Draw();
	glPopMatrix();
	///tool4////
	glPushMatrix();
	glTranslated(0.6, -0.1, 0);
	//glRotated(150, 0, 1, 0);
	glScaled(0.001, 0.001, 0.001);
	model_tool4.Draw();
	glPopMatrix();
	///tool5////
	glPushMatrix();
	glTranslated(0.8, -0.1, 0);
	//glRotated(150, 0, 1, 0);
	glScaled(0.001, 0.001, 0.001);
	model_tool5.Draw();
	glPopMatrix();



	glPopMatrix();
}


void wrapperRoom()
{
	glPushMatrix();
	//top//
	glPushMatrix();
	glBegin(GL_QUADS);

	glVertex3d(-2, 1.001, 0);
	glVertex3d(-2, 1.001, 8);
	glVertex3d(2, 1.001, 8);
	glVertex3d(2, 1.001, 0);
	glEnd();

	glPopMatrix();
	//bottom//
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, corridorFloor);
	glBegin(GL_QUADS);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3d(-1, -1.001, 0);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3d(-1, -1.001, 8);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3d(1, -1.001, 8);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3d(1, -1.001, 0);

	glEnd();
	glPopMatrix();
	//right//
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, corridorRightAndLeft);
	glBegin(GL_QUADS);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3d(1.004, 1, 0);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3d(1.004, 1, 8);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3d(1.004, -1.1, 8);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3d(1.004, -1.1, 0);
	glEnd();
	glPopMatrix();
	//left//
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, corridorRightAndLeft);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3d(-1.004, 1, 0);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3d(-1.004, 1, 8);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3d(-1.004, -1.1, 8);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3d(-1.004, -1.1, 0);
	glEnd();
	glPopMatrix();
	glPopMatrix();
}
void time2(int val)//timer animation function, allows the user to pass an integer value to the timer function.
{
	if (timerBarX < 390)
	{
		if (val == 0)
		{

			timerBarX += 1.1333333333;

		}
		glutTimerFunc(1000, time2, 0);
	}

	glutPostRedisplay();

}
void key(int k, int x, int y) {
	if (k == GLUT_KEY_RIGHT) {

	}

	if (k == GLUT_KEY_LEFT) {

	}
	if (k == GLUT_KEY_UP) {

	}
	if (k == GLUT_KEY_DOWN) {

	}
	glutPostRedisplay();
}
void drawTimeBar()

{



	glPushMatrix();

	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	glVertex3d(width - 390, height - 50, 0);
	glVertex3d(width - 390, height - 40, 0);
	glVertex3d(width - timerBarX, height - 40, 0);
	glVertex3d(width - timerBarX, height - 50, 0);

	glEnd();
	glPopMatrix();



}
void Display() {





	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (score == 0){
		renderBigTextDisplay(0, 0, -1.5, "Game Over");
		return;
	}

	score--;


	std::string sc = std::to_string(score);
	const char *mycharpsc = sc.c_str();
	renderBigTextDisplay(-0.15, -1, -4, "Score:");
	renderBigTextDisplay(0, -1, -4, mycharpsc);

	if ((*(arrayOfKeysForRoom2) == 1 && *(arrayOfKeysForRoom2 + 1) == 1))
	{
		room2Unlocked = 1;
	}

	if ((*(arrayOfKeysForRoom3) == 1 && *(arrayOfKeysForRoom3 + 1) == 1 && *(arrayOfKeysForRoom3 + 2) == 1))
	{
		room3Unlocked = 1;
	}
	isCollidedWithBanyo();
	isCollidedWithSofra();
	isCollidedWithShelf();
	isCollidedWithWalls();
	isCollidedWith7ood();
	enableCollidedWithShelf();
	enableCollidedWithMedicalShelf();
	enableCollidedWithSofra();
	enableCollidedWithKhazna();
	canGoInsideRoom2();
	canGoInsideRoom3();

	if (deactivateMedicalShelf == 1)
	{
		renderBigTextDisplay(-0.3, 0, -1.5, "Press E To Check the Object");

	}

	glPushMatrix();

	//setupLights();
	setupCamera();
	glTranslated(XDirectionVariable, 0, ZDirectionVariable);
	glRotated(mouseX*0.3, 0, 1, 0);
	glTranslated(-XDirectionVariable, 0, -ZDirectionVariable);

	glPushMatrix();

	glTranslated(0, 0, 0);
	glRotated(-180, 0, 1, 0);
	wrapperRoom();
	glPopMatrix();

	//ROOM3
	glPushMatrix();
	glTranslated(0, 0, 10);
	glRotated(-180, 0, 1, 0);
	room3();
	glPopMatrix();

	//ROOM2 
	glPushMatrix();
	glTranslated(0, 0, 6);
	glRotated(-180, 0, 1, 0);
	room2();
	glPopMatrix();

	//ROOM1
	glPushMatrix();
	glTranslated(0, 0, 2);
	glRotated(-180, 0, 1, 0);
	room1();
	glPopMatrix();


	glPopMatrix();


	glFlush();
}

void mouseClick(int btn, int state, int x, int y) {
	if (btn == GLUT_LEFT_BUTTON && state == GLUT_UP) {

	}
	glutPostRedisplay();
}

void mouseMovement(int x, int y) {


	glutPostRedisplay();
}

void LoadAssets()
{
	// Loading Model files
	model_bath.Load("Models/Bath/Bath.3ds");
	model_cabane.Load("Models/cabane/Lavatory pan Roca Gap N020916.3ds");
	model_sink.Load("Models/7ood/Sink.3ds");
	model_table.Load("Models/Table/Table 2.3ds");
	model_woodenchair.Load("Models/WoodChair/Chair.3ds");
	model_fan.Load("Models/Fan/Luster 10ravens 12 N170713.3ds");
	model_fire.Load("Models/FirePlace/Fireplace N051214.3ds");
	model_sk.Load("Models/Skeleton/Skelet N031209.3ds");
	model_crulchair.Load("Models/MedicalChair/Medicalchair.3ds");
	model_dolab.Load("Models/wardobe/Shelf N021113.3ds");
	model_mshelf.Load("Models/medicalshelf/F¬áS.3ds");
	model_safe.Load("Models/safedoor/Safe deposit N100214.3ds");
	model_vase.Load("Models/vase/Vase 3.3ds");
	model_bag.Load("Models/Bag/Bag N300513.3ds");
	model_wtable.Load("Models/New folder/Console Borsani N210916.3ds");
	model_tool1.Load("Models/tool1/Tools chisel N191213.3ds");
	model_tool2.Load("Models/tool2/Spike weapon N161214.3ds");
	model_tool3.Load("Models/tool3/Sword N041214.3ds");
	model_tool4.Load("Models/tool4/Gas mask N260416.3ds");
	model_tool5.Load("Models/tool5/Saw STARTWIN electric chain saw N310513.3ds");
	model_tool6.Load("Models/tool6/colt^gun.3ds");

}

void loadImages(){

	bathdoor = SOIL_load_OGL_texture
		(
		"./textures/bathroom.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y
		);

	livingdoor = SOIL_load_OGL_texture
		(
		"./textures/livingroom.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y
		);

	tdoor = SOIL_load_OGL_texture
		(
		"./textures/troom.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y
		);
	frontfacingWallOfSecondRoom = SOIL_load_OGL_texture
		(
		"./textures/concreteWallFour.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y
		);

	paperWall = SOIL_load_OGL_texture
		(
		"./textures/paper.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y
		);


	floorTiles = SOIL_load_OGL_texture
		(
		"./textures/floor.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y
		);
	wallBlood = SOIL_load_OGL_texture
		(
		"./textures/WallBlood.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y
		);


	corridorFloor = SOIL_load_OGL_texture
		(
		"./textures/floorTiles.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y
		);

	corridorRightAndLeft = SOIL_load_OGL_texture
		(
		"./textures/concreteWallThree.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y
		);

}
void renderBigTextDisplay(float x, float y, float z, const char *string)
{

	int length = strlen(string);


	glRasterPos3f(x, y, z);


	for (int i = 0; i < length; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, int(string[i]));
	}
	glutPostRedisplay();

}
void time(int val)//timer animation function, allows the user to pass an integer value to the timer function.
{

	glutPostRedisplay();

}
void main(int argc, char** argv) {
	glutInit(&argc, argv);

	glutInitWindowSize(width, height);
	//glutInitWindowPosition(50, 50);

	glutCreateWindow("3D Game");
	glutDisplayFunc(Display);
	glutSpecialFunc(key);


	glutPassiveMotionFunc(mouseAngleRotation);
	glutKeyboardFunc(cameraMovement);
	glutMouseFunc(mouseClick);
	glutIdleFunc(Animation);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

	glutTimerFunc(300000, time, 0);

	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	glShadeModel(GL_SMOOTH);

	LoadAssets();
	//loadImages();
	objectsVectors();
	glutMainLoop();

}