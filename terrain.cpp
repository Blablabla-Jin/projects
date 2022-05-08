#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <time.h>
#include <vector>

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>
#endif
#include "terrain.h"





void terrain::randCircles(){

	srand(time(NULL));
	for(int i = 0; i < iterations; i++){
		circles[i][0] = rand() % (terrainSize - 1); // circle vertex x
		circles[i][1] = rand() % (terrainSize - 1); // circle vertex y
		circles[i][2] = rand() % terrainSize / 30 ;  // displacement
		circles[i][3] = rand() % 5 + terrainSize / 5; // cricle size
	}
}



/*for each terrain point (tx,tz) do
	pd = distance from circle center * 2 / terrainCircleSize
	if fabs(pd) <= 1.0
		height(tx,tz) +=  disp/2 + cos(pd*3.14)*disp/2;*/
void terrain::circleAlgo(int x1, int z1, int disp, int circleSize){

	for(int x = 0; x < terrainSize; x++){
		for(int z = 0; z < terrainSize; z++){
			float pd = sqrt(pow(x1 - x, 2) + pow(z1 - z, 2)) / circleSize;
			if(fabs(pd) <= 1.0){
				height[x][z] += disp / 2 + cos(pd * 3.14) * disp / 2;
			}
		}
	}
}





void terrain::resetHeightMap(void){

	for(int x = 0; x < terrainSize; x++){
		for(int z = 0; z <terrainSize; z++){
			height[x][z] = 0;
		}
	}
}



void terrain::getNormals(){

	float x1, y1, z1, x2, y2, z2, xn, yn, zn;
	for(int x = 0; x < terrainSize - 1; x++){
		for(int z = 0; z < terrainSize - 1; z++){
			x1 = x + 1;
			y1 = height[x + 1][z] - height[x][z];
			z1 = z;

			x2 = x;
            y2 = height[x][z + 1] - height[x][z];
            z2 = z + 1;

            xn = y1 * z2 - z1 * y2;
            yn = z1 * x2 - x1 * z2;
            zn = x1 * y2 - y1 * x2;

            float n = sqrtf(xn * xn + yn * yn + zn * zn);

            normals[x][z][0] = xn / n;
            normals[x][z][1] = yn / n;
            normals[x][z][2] = zn / n;
		}
	}
}



void terrain::findMax(){

	maxHeight = 0;
	for(int i = 0; i < terrainSize; i++){
		for(int j = 0; j < terrainSize; j++){
			if(height[i][j] > maxHeight)
				maxHeight = height[i][j];
		}
	}
}


void terrain::heightMap(void){

	resetHeightMap();
	randCircles();
	for(int i = 0; i < iterations; i++){
		circleAlgo(circles[i][0], circles[i][1], circles[i][2], circles[i][3]);
	}
	

	findMax();
	drawHeight = true;
	getNormals();
}



void terrain::setVertex(int x, int z){

	float y = height[x + terrainSize / 2][z + terrainSize / 2];
	
	glNormal3fv(normals[x + terrainSize / 2][z + terrainSize / 2]);
	double texCordx = ((x + terrainSize / 2) % 100) / 100.0;
	double texCordz = ((z + terrainSize / 2) % 100) / 100.0;
	glTexCoord2f(texCordx, texCordz);	
	glVertex3f(x, y, z);
}



void terrain::drawTerrain(void){


	glBegin(GL_TRIANGLE_STRIP);

	// Order: CCW
	for(int z = -terrainSize / 2; z <= terrainSize / 2 - 2; z++){
		if(z % 2 == 0){

			for(int x = -terrainSize / 2; x <= terrainSize / 2 - 1; x++){

				setVertex(x, z);
				setVertex(x, z + 1);
			}
		}
		
		else{

			for(int x = terrainSize / 2 - 1; x >= -terrainSize / 2; x--){

				setVertex(x, z + 1);
				setVertex(x, z);
			}
		}
	}
	glEnd();
}



void terrain::display(){

    if(!drawHeight){
		heightMap();
	}
    
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	drawTerrain();

}


float terrain::setHeight(int x, int z){

	return height[x + terrainSize / 2][z + terrainSize / 2];
}

