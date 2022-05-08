#ifndef OBJLOADER_H
#define OBJLOADER_H
#include <glm/glm.hpp>
#include <vector>


class objLoader{

    public:
        void draw(
        std::vector<glm::vec3> vert, 
		std::vector<glm::vec2> uvs,
		std::vector<glm::vec3> normals
        );
        
        bool loadObj(
	    const char * path, 
	    std::vector<glm::vec3> & vertices, 
	    std::vector<glm::vec2> & uvs, 
	    std::vector<glm::vec3> & normals
        );
        
};
#endif