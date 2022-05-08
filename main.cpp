#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <time.h>
#include <vector>
#include <cstring>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#include <GLFW/glfw3.h>

#include "terrain.h"
#include "objLoader.h"
#include "Weapons_ak47.h"
#include "Weapons_pistol.h"
#include "playerInfo.h"
#include "Enemy.h"

//Screen
int screenx;
int screeny;
int monitorCount;
bool isfullscreen = true;
int windowHeight = 1050;
int windowWidth = 1680;

//Enemy
bool enemyLoad = false;
int enemyNum = 0;
int killedEnemyNum = 0;

//Texture
int texturewidth, textureheight,
	texturewidth1, textureheight1,
	texturewidth2, textureheight2,
	texturewidth3, textureheight3,
	texturewidth4, textureheight4,
	texturewidth5, textureheight5,
	texturewidth6, textureheight6,
	texturewidth7, textureheight7,
	texturewidth8, textureheight8,
	texturewidth9, textureheight9;
GLuint textures[10];
GLuint skyBoxFront, skyBoxLeft, skyBoxRight, skyBoxBack, skyBoxTop;

//Player Motion
float moveSpeed = 2.0;
float runSpeed = 3.0;
int key_state[4] = {0, 0, 0, 0};
bool isrun = false;

float light_pos1[4] = {-500 / 2, 500 / 10, 500 / 2, 0.0}; //Light Position
/*Values for light2*/
float light_pos2[4] = {500 / 2, 500 / 10, -500 / 2, 0.0}; //Light Position
float diff[4] = {1.0, 1.0, 1.0, 1.0};					  //Diffuse values
float spec[4] = {0.5, 0.5, 0.5, 1.0};					  //Specular values
float amb[4] = {0.7, 0.7, 0.7, 1.0};					  //Ambient values

//Weapons
bool ak47 = true;
bool pistol = false;
bool vSigh = true;

//Animation
float moveAnimation = 0.05;
float fastAnimation = 0.09;
float animation;
int jumping = 0;
float jump_speed;
float jump_height;
float jump;

//Game level
int level = 10;
bool start = false;

GLdouble world_x, world_y, world_z; //最终结果

void GetPos();

void drawSkyBox(GLuint textureID)
{
	GLfloat wall_vert[][3] = {-50000, -50000, -50000,
							  50000, -50000, -50000,
							  50000, 50000, -50000,
							  -50000, 50000, -50000};
	GLubyte index_list[][4] = {0, 1, 2, 3};
	GLfloat tex_coor[][2] = {0, 0, 1, 0, 1, 1, 0, 1};
	glBindTexture(GL_TEXTURE_2D, textureID);
	glEnable(GL_TEXTURE_2D);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, wall_vert);
	glTexCoordPointer(2, GL_FLOAT, 0, tex_coor);
	glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, index_list);
}

GLubyte *LoadPPM(char *file, int *width, int *height)
{
	GLubyte *img;
	FILE *fd;
	int n, m;
	int k, nm;
	char c;
	int i;
	char b[100];
	float s;
	int red, green, blue;

	fd = fopen(file, "r");
	fscanf(fd, "%[^\n] ", b);
	if (b[0] != 'P' || b[1] != '3')
	{
		printf("%s is not a PPM file!\n", file);
		exit(0);
	}
	fscanf(fd, "%c", &c);
	while (c == '#')
	{
		fscanf(fd, "%[^\n] ", b);
		printf("%s\n", b);
		fscanf(fd, "%c", &c);
	}
	ungetc(c, fd);
	fscanf(fd, "%d %d %d", &n, &m, &k);

	nm = n * m;

	img = (GLubyte *)(malloc(3 * sizeof(GLuint) * nm));

	s = 255.0 / k;

	for (i = 0; i < nm; i++)
	{
		fscanf(fd, "%d %d %d", &red, &green, &blue);
		img[3 * nm - 3 * i - 3] = red * s;
		img[3 * nm - 3 * i - 2] = green * s;
		img[3 * nm - 3 * i - 1] = blue * s;
	}

	*width = n;
	*height = m;

	return img;
}

GLuint testDL;
static void testDisplayList();
static void initDisplayList();

terrain Terrain;

struct camera
{
	glm::vec4 direction = glm::vec4(0, 0, -1, 0);
	glm::vec4 right = glm::vec4(1, 0, 0, 0);
	glm::vec4 up = glm::vec4(0, 1, 0, 0);
	glm::vec4 pos = glm::vec4(10, Terrain.setHeight(10, 10) + 60, 10, 0);
	glm::vec4 jump = glm::vec4(0, 0, 0, 0);

	void changeView(float yaw, float pitch)
	{
		glm::mat4 yawRotate = glm::rotate(glm::mat4(1.0f), glm::radians(-yaw), glm::vec3(0, 1, 0));

		direction = yawRotate * glm::vec4(0, 0, -1, 0);
		right = yawRotate * glm::vec4(1, 0, 0, 0);
		glm::mat4 pitchRotate = glm::rotate(glm::mat4(1.0f), glm::radians(-pitch), glm::vec3(right));

		direction = pitchRotate * direction;
		up = pitchRotate * glm::vec4(0, 1, 0, 0);
	}
};

camera Camera;
Weapons_ak47 ak;
Weapons_pistol pis;
playerInfo PlayerInfo;

struct viewControl
{
	float yaw = 0;
	float pitch = 0;
	bool rightButton = false;
	int lastX = 0, lastY = 0;
};
viewControl ViewControl;

void mouseMotionFunc(int x, int y)
{

	ViewControl.yaw += (x - ViewControl.lastX) * 0.3;
	ViewControl.pitch += (y - ViewControl.lastY) * 0.3;
	if (ViewControl.yaw > 180)
		ViewControl.yaw = -180;
	else if (ViewControl.yaw < -180)
		ViewControl.yaw = 180;
	if (ViewControl.pitch > 75)
		ViewControl.pitch = 75;
	else if (ViewControl.pitch < -75)
		ViewControl.pitch = -75;
	ViewControl.lastX = x;
	ViewControl.lastY = y;
	Camera.changeView(ViewControl.yaw, ViewControl.pitch);
}

void mousePassiveMotion(int x, int y)
{
	ViewControl.yaw += (x - ViewControl.lastX) * 0.3;
	ViewControl.pitch += (y - ViewControl.lastY) * 0.3;
	if (ViewControl.yaw > 180)
		ViewControl.yaw = -180;
	else if (ViewControl.yaw < -180)
		ViewControl.yaw = 180;
	if (ViewControl.pitch > 75)
		ViewControl.pitch = 75;
	else if (ViewControl.pitch < -75)
		ViewControl.pitch = -75;
	ViewControl.lastX = x;
	ViewControl.lastY = y;
	Camera.changeView(ViewControl.yaw, ViewControl.pitch);
}

struct move
{

	void fall()
	{

		if (jumping == 0)
		{
			if (Camera.pos.y > Terrain.setHeight(Camera.pos.x, Camera.pos.z) + 60)
			{
				Camera.pos.y = Terrain.setHeight(Camera.pos.x, Camera.pos.z) + 60;
			}
		}

		if (Camera.pos.y < Terrain.setHeight(Camera.pos.x, Camera.pos.z) + 60)
		{
			Camera.pos.y = Terrain.setHeight(Camera.pos.x, Camera.pos.z) + 60;
		}
	}

	void playerJump()
	{

		if (jumping == 1)
			return;
		jump = 0;
		jump_speed = 0.06;
		jump_height = 0.6;
		jumping = 1;
	}

	void set(unsigned char key)
	{

		switch (key)
		{
		case 'w':
		case 'W':
			if (key_state[0] == 1)
				return;
			else
			{
				key_state[0] = 1;
				if (!isrun)
				{
					if (abs(animation + moveAnimation) > 0.5)
						moveAnimation = -moveAnimation;
					animation += moveAnimation;
				}
				else
				{
					if (abs(animation + fastAnimation) > 0.5)
						fastAnimation = -fastAnimation;
					animation += fastAnimation;
				}
			}
			break;
		case 'a':
		case 'A':
			if (key_state[1] == 1)
				return;
			else
			{
				key_state[1] = 1;
				if (!isrun)
				{
					if (abs(animation + moveAnimation) > 0.5)
						moveAnimation = -moveAnimation;
					animation += moveAnimation;
				}
				else
				{
					if (abs(animation + fastAnimation) > 0.5)
						fastAnimation = -fastAnimation;
					animation += fastAnimation;
				}
			}
			break;
		case 's':
		case 'S':
			if (key_state[2] == 1)
				return;
			else
			{
				key_state[2] = 1;
				if (!isrun)
				{
					if (abs(animation + moveAnimation) > 0.5)
						moveAnimation = -moveAnimation;
					animation += moveAnimation;
				}
				else
				{
					if (abs(animation + fastAnimation) > 0.5)
						fastAnimation = -fastAnimation;
					animation += fastAnimation;
				}
			}
			break;
		case 'd':
		case 'D':
			if (key_state[3] == 1)
				return;
			else
			{
				key_state[3] = 1;
				if (!isrun)
				{
					if (abs(animation + moveAnimation) > 0.5)
						moveAnimation = -moveAnimation;
					animation += moveAnimation;
				}
				else
				{
					if (abs(animation + fastAnimation) > 0.5)
						fastAnimation = -fastAnimation;
					animation += fastAnimation;
				}
			}
			break;
		}
	}

	glm::vec4 moveVector(camera &Camera)
	{
		glm::vec4 forWard;
		glm::vec4 leftWard;
		glm::vec4 backWard;
		glm::vec4 rightWard;

		if (key_state[0] == 0 & key_state[1] == 0 & key_state[2] == 0 & key_state[3] == 0)
		{
			return glm::vec4(0, 0, 0, 0);
		}
		else
		{
			if (Camera.pos.x > 495.0f)
			{
				Camera.pos.x = 495.0f;
				return glm::vec4(0, 0, 0, 0);
			}
			if (Camera.pos.x < -495.0f)
			{
				Camera.pos.x = -495.0f;
				return glm::vec4(0, 0, 0, 0);
			}
			if (Camera.pos.z > 495.0f)
			{
				Camera.pos.z = 495.0f;
				return glm::vec4(0, 0, 0, 0);
			}
			if (Camera.pos.z < -495.0f)
			{
				Camera.pos.z = -495.0f;
				return glm::vec4(0, 0, 0, 0);
			}

			else
			{

				if (key_state[0] == 1)
					forWard = Camera.direction;
				if (key_state[1] == 1)
					leftWard = -Camera.right;
				if (key_state[2] == 1)
					backWard = -Camera.direction;
				if (key_state[3] == 1)
					rightWard = Camera.right;

				if (!isrun)
				{
					return (forWard + leftWard + backWard + rightWard) * moveSpeed;
				}
				else
				{
					return (forWard + leftWard + backWard + rightWard) * runSpeed;
				}
			}
		}
	}
};

move Move;

void normalKey(unsigned char key, int x, int y)
{
	int mod = glutGetModifiers();

	if (mod == GLUT_ACTIVE_SHIFT && !isrun)
	{
		isrun = true;
	}

	else if (mod == GLUT_ACTIVE_CTRL && isrun)
	{
		isrun = false;
	}

	Move.set(key);
	switch (key)
	{

	case 27:
		exit(0);
		break;
	case '1':
		ak47 = true;
		pistol = false;
		break;
	case '2':
		pistol = true;
		ak47 = false;
		break;
	case ' ':
		Move.playerJump();
		break;
	}
}

void releasKey(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'W':
	case 'w':
		key_state[0] = 0;
		break;
	case 'A':
	case 'a':
		key_state[1] = 0;
		break;
	case 'S':
	case 's':
		key_state[2] = 0;
		break;
	case 'D':
	case 'd':
		key_state[3] = 0;
		break;
	case 'r':
	case 'R':
		if (ak47)
		{
			ak.meg_changing = clock() / 1000000.0;
			ak.changflag = 1;
		}
		else
		{
			pis.meg_changing = clock() / 1000000.0;
			pis.changflag = 1;
		}
		break;
	}
}

void specialKey(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_F1:
		start = true;
		break;
	}
}

class Bullet
{
public:
	//Position
	float x, y, z;
	//Direction
	float gx, gy, gz;
	//Next position
	float nx, ny, nz;
	float speed = 40;
	Bullet() {}

	Bullet(float x, float y, float z, float gx, float gy, float gz) : x(x), y(y), z(z), gx(gx - x), gy(gy - y), gz(gz - z)
	{
	}
	//Draw every bullet
	void DrawBullet()
	{
		float len = 5;
		glBegin(GL_LINES);
		glColor3f(1, 1, 1);
		glVertex3i(x, y, z);
		glVertex3i(x + gx * len, y + gy * len, z + gz * len);
		nx = x + gx * speed;
		ny = y + gy * speed;
		nz = z + gz * speed;
		x = nx;
		y = ny;
		z = nz;
		glEnd();
	}
	//Collision judge arguments are robots' pos
	bool JudgeHit(float x, float y, float z, float v)
	{
		float X = this->x, Y = this->y, Z = this->z;
		for (int i = 0; i < speed; i++)
		{
			if (sqrt(pow(x - X, 2) + pow(y + 60 - Y, 2) + pow(z - Z, 2)) < v)
			{
				return true;
			}
			X += gx;
			Y += gy;
			Z += gz;
		}
		return false;
	}
};

std::vector<Enemy> robots;
std::vector<Bullet> bullet;

class Game
{
public:
	void GunDamage()
	{
		float f1 = (clock() / 1000000.0 - ak.shot_before);

		if (ak47 && ak.shooting == 1 && f1 > ak.shot_interval)
		{
			if (ak.bulletNum == 0 && ak.changflag == 0)
			{
				ak.meg_changing = clock() / 1000000.0;
				ak.changflag = 1;
			}
			else
			{
				if (ak.changflag == 1)
					return;
				ak.beginShoot();
				ak.shot_before = clock() / 1000000.0;
				ak.beginShoot();
				bullet.push_back(Bullet(Camera.pos.x, Camera.pos.y, Camera.pos.z, Camera.pos.x + Camera.direction.x, Camera.pos.y + Camera.direction.y, Camera.pos.z + Camera.direction.z));
				ak.bulletNum -= 1;
			}
		}

		std::vector<Bullet>::iterator it;
		for (it = bullet.begin(); it != bullet.end();)
		{
			//Find need to remove the bullet or not
			if ((*it).x < -500 || (*it).x > 500 || (*it).z < -500 || (*it).z > 500 || (*it).y < Terrain.setHeight((*it).x, (*it).z) || (*it).y > Terrain.setHeight((*it).x, (*it).z) + 300)
				it = bullet.erase(it);
			else
			{
				//Collision
				bool judge = false;
				std::vector<Enemy>::iterator it2;
				for (it2 = robots.begin(); it2 != robots.end();)
				{
					if ((*it2).live == false)
					{
						it2++;
						continue;
					}
					//Collision
					judge = (*it).JudgeHit((*it2).x, (*it2).y, (*it2).z, 3.5 * (*it2).size);

					if (judge)
					{

						(*it2).blood -= (ak47 == true ? ak.damage_ak : pis.damage_pis);
						it = bullet.erase(it);
						break;
					}
					it2++;
				}
				if (!judge)
				{
					(*it).DrawBullet();
					it++;
				}
			}
		}
	}
	void judgeAlive(Enemy *r)
	{

		if (r->blood <= 0 && r->live)
		{
			r->live = false;
			r->tryGoToGoalFlag = 0;
			enemyNum -= 1;
			killedEnemyNum += 1;
		}
	}

	void DrawEnemy(float x, float y, float z)
	{
		std::vector<Enemy>::iterator it;
		for (it = robots.begin(); it != robots.end();)
		{

			//Automatically attack when close to player
			glPushMatrix();

			double range = 15; //enemy attack range
			if ((*it).enemyAtk_interval < 120)
			{
				(*it).enemyAtk_interval += 1;
			}

			if (abs(x - (*it).x) < range && abs(z - (*it).z) < range)
			{
				if ((*it).attackFlag == false && (*it).enemyAtk_interval == 120)
				{
					(*it).enemyStartAttack();
					(*it).enemyAtk_interval = 0;
				}
			}

			(*it).y = Terrain.setHeight((*it).x, (*it).z);

			//Enemy move to playPos
			if ((*it).tryGoToGoalFlag == 1)
			{
				double toX = x;
				double toZ = z;
				if (!(abs(toX - (*it).x) < range && abs(toZ - (*it).z) < range))
				{
					(*it).moveToPlayer(toX, 0, toZ);
				}
			}

			glBindTexture(GL_TEXTURE_2D, textures[3]);
			(*it).drawEnemy();

			judgeAlive(&(*it));
			if ((*it).live == false)
			{

				it = robots.erase(it);
				glPopMatrix();
				return;
			}
			if ((*it).live == true)
			{

				if ((*it).attackFlag == true)
				{
					PlayerInfo.Hp -= (*it).atk_dmg;
					(*it).attackFlag = false;
					if (PlayerInfo.Hp <= 0)
						start = false;
				}
			}
			glPopMatrix();
			it++;
		}
	}

	void HUD()
	{

		//draw virtualSigh
		glRasterPos3f(Camera.pos.x + Camera.direction.x,
					  Camera.pos.y + Camera.direction.y,
					  Camera.pos.z + Camera.direction.z);
		std::string virtualSigh = "+";
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, virtualSigh[0]);

		char temp1[20]; //Enemy Remains
		char temp2[20]; //player hp
		char temp3[20]; //Enemy Killed
		char temp4[20]; //ak47 bullet number
		char temp5[20]; //pistol bullet number

		std::string enemylife = "Enemy Remain: ";
		std::string playerlife = "Player HP: ";
		std::string enemyKill = "Enemy Killed: ";
		std::string ammonum = "Bullet: ";

		sprintf(temp2, "%d", PlayerInfo.Hp);
		sprintf(temp1, "%d", enemyNum);
		sprintf(temp3, "%d", killedEnemyNum);

		std::string numberen(temp1);
		std::string playerHp(temp2);
		std::string killscore(temp3);

		glRasterPos3i(0, 300, 800);
		for (int i = 0; i < enemylife.size(); i++)
		{
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, enemylife[i]);
		}
		for (int i = 0; i < numberen.size(); i++)
		{
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, numberen[i]);
		}
		glRasterPos3i(0, 275, 800);
		for (int i = 0; i < playerlife.size(); i++)
		{
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, playerlife[i]);
		}
		for (int i = 0; i < playerHp.size(); i++)
		{
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, playerHp[i]);
		}
		glRasterPos3i(0, 250, 800);
		for (int i = 0; i < enemyKill.size(); i++)
		{
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, enemyKill[i]);
		}
		for (int i = 0; i < killscore.size(); i++)
		{
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, killscore[i]);
		}

		glRasterPos3i(0, 300, -800);
		for (int i = 0; i < enemylife.size(); i++)
		{
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, enemylife[i]);
		}
		for (int i = 0; i < numberen.size(); i++)
		{
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, numberen[i]);
		}
		glRasterPos3i(0, 275, -800);
		for (int i = 0; i < playerlife.size(); i++)
		{
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, playerlife[i]);
		}
		for (int i = 0; i < playerHp.size(); i++)
		{
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, playerHp[i]);
		}
		glRasterPos3i(0, 250, -800);
		for (int i = 0; i < enemyKill.size(); i++)
		{
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, enemyKill[i]);
		}
		for (int i = 0; i < killscore.size(); i++)
		{
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, killscore[i]);
		}

		if (ak47)
		{
			sprintf(temp4, "%d", ak.bulletNum);
			std::string bulnum0(temp4);
			glRasterPos3i(0, 225, 800);
			for (int i = 0; i < ammonum.size(); i++)
			{
				glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ammonum[i]);
			}
			for (int i = 0; i < bulnum0.size(); i++)
			{
				glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, bulnum0[i]);
			}
			glRasterPos3i(0, 225, -800);
			for (int i = 0; i < ammonum.size(); i++)
			{
				glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ammonum[i]);
			}
			for (int i = 0; i < bulnum0.size(); i++)
			{
				glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, bulnum0[i]);
			}
		}
		else
		{
			sprintf(temp5, "%d", pis.bulletNum);
			std::string bulnum1(temp5);
			glRasterPos3i(0, 225, 800);
			for (int i = 0; i < ammonum.size(); i++)
			{
				glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ammonum[i]);
			}
			for (int i = 0; i < bulnum1.size(); i++)
			{
				glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, bulnum1[i]);
			}
			glRasterPos3i(0, 225, -800);
			for (int i = 0; i < ammonum.size(); i++)
			{
				glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ammonum[i]);
			}
			for (int i = 0; i < bulnum1.size(); i++)
			{
				glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, bulnum1[i]);
			}
		}
	}

	void Processing()
	{
		float playX = Camera.pos.x, playY = Camera.pos.y, playZ = Camera.pos.z;

		GunDamage();
		DrawEnemy(playX, playY, playZ);

		//HUD();
		/*
		if (enemyNum == 5)
		{
			enemyLoad = true;
			return;
		}

		else if (enemyNum == 0)
			enemyLoad = false;
		*/

		float enemyX = (rand() % 1000) - 500;
		float enemyZ = (rand() % 1000) - 500;
		if (abs(enemyX - Camera.pos.x) > 50 && abs(enemyZ - Camera.pos.z) > 50)
		{
			if (rand() % 99 == 1)
			{
				//std::std::cout << (rand() % 100) << std::std::endl;
				robots.push_back(Enemy(enemyX, Terrain.setHeight(enemyX + Terrain.terrainSize / 2, enemyZ + Terrain.terrainSize / 2), enemyZ, 3, 100));
				enemyNum += 1;
			}
			else
				return;
		}
		else
			return;
	}
};
Game gameInfo;

static void testDisplayList()
{
	glBindTexture(GL_TEXTURE_2D, textures[0]);
	Terrain.display();
}

static void initDisplayList()
{
	testDL = glGenLists(1);
	glNewList(testDL, GL_COMPILE);
	testDisplayList();
	glEndList();
}

objLoader *obj;

void display(void)
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	Camera.pos = Camera.pos + Move.moveVector(Camera) * 1.0f;

	if (jumping == 1)
	{

		jump += jump_height;
		jump_height -= jump_speed;
		jump += jump_height;
		Camera.pos.y += jump;
		if (Camera.pos.y < Terrain.setHeight(Camera.pos.x, Camera.pos.z) + 60)
			jumping = 0;
	}
	Move.fall();

	gluLookAt(
		Camera.pos.x, Camera.pos.y, Camera.pos.z,
		Camera.pos.x + Camera.direction.x, Camera.pos.y + Camera.direction.y, Camera.pos.z + Camera.direction.z,
		Camera.up.x, Camera.up.y, Camera.up.z);

	if (ak47)
	{
		std::vector<glm::vec3> AK47_vertices;
		std::vector<glm::vec2> AK47_uvs;
		std::vector<glm::vec3> AK47_normals;
		glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, textures[2]);
		glTranslatef(Camera.pos.x, Camera.pos.y, Camera.pos.z);
		glRotatef(-ViewControl.yaw, 0, 1, 0);
		glRotatef(-ViewControl.pitch, 1, 0, 0);
		glTranslatef(10, -12, -12);
		glTranslatef(0, animation, 0);
		if (ak.shoot == 1)
		{
			if ((ak.r + ak.step) < -8)
				ak.step = -ak.step;
			if ((ak.r + ak.step) > 0)
				ak.shoot = 0;
			ak.r += ak.step;
			glRotatef(-ak.r, 1, 0, 0);
		}
		glRotatef(90, 0, 1, 0);
		glScalef(0.5, 0.5, -1.0);
		obj->loadObj("Obj/AK47.obj", AK47_vertices, AK47_uvs, AK47_normals);
		obj->draw(AK47_vertices, AK47_uvs, AK47_normals);
		ak.reload();
		glPopMatrix();
	}

	if (pistol)
	{
		std::vector<glm::vec3> Pisto_vertices;
		std::vector<glm::vec2> Pisto_uvs;
		std::vector<glm::vec3> Pisto_normals;
		glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, textures[1]);
		glTranslatef(Camera.pos.x, Camera.pos.y, Camera.pos.z);
		glRotatef(-ViewControl.yaw, 0, 1, 0);
		glRotatef(-ViewControl.pitch, 1, 0, 0);
		glTranslatef(12, -12, -12);
		glTranslatef(0, animation, 0);
		if (pis.shoot == 1)
		{
			if ((pis.r + pis.step) < -10)
				pis.step = -pis.step;
			if ((pis.r + pis.step) > 0)
				pis.shoot = 0;
			pis.r += pis.step;
			glRotatef(-pis.r, 1, 0, 0);
		}
		glRotatef(-90, 0, 1, 0);
		glScalef(0.1, 0.1, -0.1);
		obj->loadObj("Obj/gun.obj", Pisto_vertices, Pisto_uvs, Pisto_normals);
		obj->draw(Pisto_vertices, Pisto_uvs, Pisto_normals);
		pis.reload();
		glPopMatrix();
	}

	if (start && PlayerInfo.Hp > 0)
	{
		gameInfo.Processing();
		glDisable(GL_TEXTURE_2D);
		gameInfo.HUD();
		
		
	}

	else{
		glDisable(GL_TEXTURE_2D);
		
	}
	

	

	if (!start && PlayerInfo.Hp > 0)
	{
		glRasterPos3f(Camera.pos.x + Camera.direction.x, Camera.pos.y + Camera.direction.y, Camera.pos.z + Camera.direction.z);
		std::string youdie = "PRESS F1 TO START";
		for (int i = 0; i < youdie.size(); i++)
		{
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, youdie[i]);
		}
	}

	if (PlayerInfo.Hp == 0)
	{
		glRasterPos3f(Camera.pos.x + Camera.direction.x, Camera.pos.y + Camera.direction.y, Camera.pos.z + Camera.direction.z);
		std::string youdie = "YOU DEAD PRESS ESC TO LEAVE";
		for (int i = 0; i < youdie.size(); i++)
		{
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, youdie[i]);
		}
	}

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);

	glLightfv(GL_LIGHT0, GL_POSITION, light_pos1);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diff);
	glLightfv(GL_LIGHT0, GL_SPECULAR, spec);
	glLightfv(GL_LIGHT0, GL_AMBIENT, amb);

	glLightfv(GL_LIGHT1, GL_POSITION, light_pos2);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diff);
	glLightfv(GL_LIGHT1, GL_SPECULAR, spec);
	glLightfv(GL_LIGHT1, GL_AMBIENT, amb);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glPushMatrix();
	glTranslatef(Camera.pos.x, Camera.pos.y, Camera.pos.z);
	drawSkyBox(textures[4]);
	glRotatef(90, 0, 1, 0);
	drawSkyBox(textures[7]);
	glRotatef(90, 0, 1, 0);
	drawSkyBox(textures[5]);
	glRotatef(90, 0, 1, 0);
	drawSkyBox(textures[6]);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(Camera.pos.x, Camera.pos.y, Camera.pos.z);
	glRotatef(90, 1, 0, 0);
	drawSkyBox(textures[8]);
	glPopMatrix();

	glCallList(testDL);

	glutSwapBuffers();
}

void mouseMotion(int button, int state, int x, int y)
{

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		//Set mode of ak to auto
		if (ak47)
		{
			ak.shot_before = clock() / 1000000.0;
			ak.shooting = 1;
		}

		//Pistol things
		else if (pistol)
		{

			if (pis.bulletNum == 0 && pis.changflag == 0)
			{
				pis.meg_changing = clock() / 1000000.0;
				pis.changflag = 1;
			}
			else
			{
				if (start)
				{
					if (pis.changflag == 1)
						return;
					pis.beginShoot();
					bullet.push_back(Bullet(Camera.pos.x, Camera.pos.y, Camera.pos.z, Camera.pos.x + Camera.direction.x, Camera.pos.y + Camera.direction.y, Camera.pos.z + Camera.direction.z));
					pis.bulletNum -= 1;
				}
			}
		}
	}

	//Stop auto mode
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		if (ak47)
		{
			ak.shooting = 0;
		}
	}
}

void reshape(int w, int h)
{

	int windowsWidth = w;
	int windowsHeight = h;

	glViewport(0, 0, (GLsizei)w, (GLsizei)h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(90.0, (GLfloat)w / (GLfloat)h, 1, 100000.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(
		Camera.pos.x, Camera.pos.y, Camera.pos.z,
		Camera.pos.x + Camera.direction.x, Camera.pos.y + Camera.direction.y, Camera.pos.z + Camera.direction.z,
		Camera.up.x, Camera.up.y, Camera.up.z);
}

void timeFunc(int value)
{
	glutPostRedisplay();
	glutTimerFunc(16, timeFunc, 1); //7
}

void init(void)
{
	glGenTextures(10, textures);

	GLubyte *terrain = LoadPPM("texture/grass.ppm", &texturewidth, &textureheight);
	GLubyte *pistol = LoadPPM("texture/gun.ppm", &texturewidth1, &textureheight1);
	GLubyte *ak47Tex = LoadPPM("texture/ak47.ppm", &texturewidth2, &textureheight2);
	GLubyte *starFighter = LoadPPM("texture/starFighter.ppm", &texturewidth3, &textureheight3);
	GLubyte *skyBoxFront = LoadPPM("texture/front.ppm", &texturewidth4, &textureheight4);
	GLubyte *skyBoxBack = LoadPPM("texture/back.ppm", &texturewidth5, &textureheight5);
	GLubyte *skyBoxLeft = LoadPPM("texture/left.ppm", &texturewidth6, &textureheight6);
	GLubyte *skyBoxRight = LoadPPM("texture/right.ppm", &texturewidth7, &textureheight7);
	GLubyte *skyBoxTop = LoadPPM("texture/top.ppm", &texturewidth8, &textureheight8);

	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, textures[0]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texturewidth, textureheight, 0, GL_RGB, GL_UNSIGNED_BYTE, terrain);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, textures[1]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texturewidth1, textureheight1, 0, GL_RGB, GL_UNSIGNED_BYTE, pistol);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, textures[2]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texturewidth2, textureheight2, 0, GL_RGB, GL_UNSIGNED_BYTE, ak47Tex);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, textures[3]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texturewidth3, textureheight3, 0, GL_RGB, GL_UNSIGNED_BYTE, starFighter);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, textures[4]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texturewidth4, textureheight4, 0, GL_RGB, GL_UNSIGNED_BYTE, skyBoxFront);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, textures[5]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texturewidth5, textureheight5, 0, GL_RGB, GL_UNSIGNED_BYTE, skyBoxBack);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, textures[6]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texturewidth6, textureheight6, 0, GL_RGB, GL_UNSIGNED_BYTE, skyBoxLeft);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, textures[7]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texturewidth7, textureheight7, 0, GL_RGB, GL_UNSIGNED_BYTE, skyBoxRight);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, textures[8]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texturewidth8, textureheight8, 0, GL_RGB, GL_UNSIGNED_BYTE, skyBoxTop);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glClearColor(0, 0, 0, 0);

	glutReshapeFunc(reshape);
	glutMotionFunc(mouseMotionFunc);
	glutMouseFunc(mouseMotion);
	glutPassiveMotionFunc(mousePassiveMotion);

	//Hide cursor
	glutSetCursor(GLUT_CURSOR_NONE);

	glutSpecialFunc(specialKey);
	glutKeyboardUpFunc(releasKey);
	glutKeyboardFunc(normalKey);
}

int main(int argc, char **argv)
{

	glfwInit();
	// Set all the required options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	if (isfullscreen)
	{
		GLFWmonitor **pMonitor = glfwGetMonitors(&monitorCount);
		const GLFWvidmode *mode = glfwGetVideoMode(pMonitor[0]);
		screenx = mode->width;
		screeny = mode->height;
		isfullscreen = false;
	}

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(screenx, screeny);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Terrain");
	init();

	initDisplayList();

	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
	glEnable(GL_DEPTH_TEST);

	glutDisplayFunc(display);
	glutTimerFunc(16, &timeFunc, 1);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisable(GL_TEXTURE_2D);
	glfwTerminate();
	glutMainLoop();
}