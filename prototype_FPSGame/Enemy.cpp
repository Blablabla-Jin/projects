#include "Enemy.h"
#include "objLoader.h"
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>
#endif

#include <iostream>


#define PI 3.14159





objLoader *enemy;


void Enemy::drawEnemy(){
    std::vector<glm::vec3> enemy_vertices;
	std::vector<glm::vec2> enemy_uvs;
	std::vector<glm::vec3> enemy_normals;
    enemy->loadObj("Obj/StarFighter.obj", enemy_vertices, enemy_uvs, enemy_normals);

    glTranslatef(this->x, this->y + 60, this->z);
	glRotatef(90, 0, 1, 0);
	glRotatef(this->angle, 0, 1, 0);
    glScalef(2, 2, 2);
	enemy->draw(enemy_vertices, enemy_uvs, enemy_normals);

}

void Enemy::moveToPlayer(double px, double py, double pz)
{

	double xDifferenceValue = abs(px - this->x);
	double zDifferenceValue = abs(pz - this->z);
	if (pz > this->z && px >= this->x)
	{
		this->robotToGoalAngle = (atan(xDifferenceValue / zDifferenceValue) / PI) * 180;
		this->robotToGoalAngle += 0;
	}
	else if (pz < this->z && px > this->x)
	{
		this->robotToGoalAngle = (atan(zDifferenceValue / xDifferenceValue) / PI) * 180;
		this->robotToGoalAngle += 90;
	}
	else if (pz < this->z && px <= this->x)
	{
		this->robotToGoalAngle = (atan(xDifferenceValue / zDifferenceValue) / PI) * 180;
		this->robotToGoalAngle += 180; 
	}
	else if (pz >= this->z && px < this->x)
	{
		this->robotToGoalAngle = (atan(zDifferenceValue / xDifferenceValue) / PI) * 180;
		this->robotToGoalAngle += 270; 
	}



	if (this->robotToGoalAngle >= 360)
	{
		this->robotToGoalAngle -= 360;
	}
	this->angle = this->robotToGoalAngle; 

	//Speed of enemy
	double zs = (this->zstep);

	this->z = this->z + cos(this->angle / 360 * 2 * PI)*zs;
	this->x = this->x + sin(this->angle / 360 * 2 * PI)*zs;
}

void Enemy::enemyStartAttack()
{
	this->attackFlag = true;
}

void  Enemy::judgeDamage(int damage)
{
	blood -= damage;
}