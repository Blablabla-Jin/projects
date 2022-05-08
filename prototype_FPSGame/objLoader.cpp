#include <vector>
#include <stdio.h>
#include <string>
#include <cstring>
#include <math.h>
#include <iostream>
#include <glm/glm.hpp>
#include "objLoader.h"

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>
#endif


bool objLoader::loadObj(
	const char * path, 
	std::vector<glm::vec3> & vertices, 
	std::vector<glm::vec2> & uvs,
	std::vector<glm::vec3> & normals
){
	std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
	std::vector<glm::vec3> temp_vertices; 
	std::vector<glm::vec2> temp_uvs;
	std::vector<glm::vec3> temp_normals;


	FILE * file = fopen(path, "r");
	if( file == NULL ){
		printf("Impossible to open the file! Are you in the right path?\n");
		getchar();
		return false;
	}

	while( 1 ){

		char lineHeader[128];
		// read the first word of the line
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break; // End Of File. Quit the loop.
		
		if ( strcmp( lineHeader, "v" ) == 0 ){
			glm::vec3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z );
			temp_vertices.push_back(vertex);
		}else if ( strcmp( lineHeader, "vt" ) == 0 ){
			glm::vec2 uv;
			fscanf(file, "%f %f\n", &uv.x, &uv.y );
			uv.y = -uv.y; 
			temp_uvs.push_back(uv);
		}else if ( strcmp( lineHeader, "vn" ) == 0 ){
			glm::vec3 normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z );
			temp_normals.push_back(normal);
		}else if ( strcmp( lineHeader, "f" ) == 0 ){
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2] );
			if (matches != 9){
				printf("File can't be read :-( Try exporting with other ways\n");
				fclose(file);
				return false;
			}
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			uvIndices.push_back(uvIndex[0]);
			uvIndices.push_back(uvIndex[1]);
			uvIndices.push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		}else{

			char stupidBuffer[1000];
			fgets(stupidBuffer, 1000, file);
		}

	}

	// For each vertex of each triangle
	for( unsigned int i=0; i<vertexIndices.size(); i++ ){

		// Get the indices of its attributes
		unsigned int vertexIndex = vertexIndices[i];
		unsigned int uvIndex = uvIndices[i];
		unsigned int normalIndex = normalIndices[i];
		
		// Get the attributes thanks to the index
		glm::vec3 vertex = temp_vertices[ vertexIndex-1 ];
		glm::vec2 uv = temp_uvs[ uvIndex-1 ];
		glm::vec3 normal = temp_normals[ normalIndex-1 ];
		
		// Put the attributes in buffers
		vertices.push_back(vertex);
		uvs.push_back(uv);
		normals.push_back(normal);

	}
	fclose(file);
	return true;
}


void objLoader::draw(
	std::vector<glm::vec3> vert, 
	std::vector<glm::vec2> uvs,
	std::vector<glm::vec3> normals){

	glBegin(GL_TRIANGLES);
    for(int i = 0; i < vert.size(); i++){
        if(i%3 == 0){
			

			glNormal3f(normals[i][0], normals[i][1], normals[i][2]);
			glNormal3f(normals[i+1][0], normals[i+1][1], normals[i+1][2]);
			glNormal3f(normals[i+2][0], normals[i+2][1], normals[i+2][2]);

			glTexCoord2f(uvs[i][0], uvs[i][1]);
			glTexCoord2f(uvs[i+1][0], uvs[i+1][1]);
			glTexCoord2f(uvs[i+2][0], uvs[i+2][1]);

            glVertex3f(vert[i][0], vert[i][1], vert[i][2]);
            glVertex3f(vert[i+1][0], vert[i+1][1], vert[i+1][2]);
            glVertex3f(vert[i+2][0], vert[i+2][1], vert[i+2][2]);
        }
    }
    glEnd();
}