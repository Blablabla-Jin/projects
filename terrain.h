
#ifndef TERRAIN_H
#define TERRAIN_H

class terrain
{
		
	public:
		int terrainSize = 1000; 						
	int iterations = 100;                       
	float maxHeight = 0.0;
	bool drawHeight = false;

	float height [1050][1050];     //the height y of the point (x, y)
	float normals [1050][1050][3]; //normals for lighting
	int circles [100][4];
		 		
		
		void randCircles();
		void circleAlgo(int x1, int z1, int disp, int circleSize);
		void faultAlgo();
		void resetHeightMap(void);
		void getNormals();
		void findMax();
		void heightMap(void);
		void setVertex(int x, int z);
		void drawTerrain(void);
		void display();
		float setHeight(int x, int z);
};

#endif