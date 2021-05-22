//
//  objloader.hpp
//  CG_assignment3
//
//  Created by 도승욱 on 2021/05/09.
//

#ifndef objloader_hpp
#define objloader_hpp

#include <vector>
#include <stdio.h>
#include <string>
#include <cstring>

#include <glm/glm.hpp>

#include "objloader.hpp"

bool loadOBJ(
    const char * path,
    std::vector<glm::vec3> & out_vertices,
    std::vector<glm::vec2> & out_uvs,
    std::vector<glm::vec3> & out_normals
);



bool loadAssImp(
    const char * path,
    std::vector<unsigned short> & indices,
    std::vector<glm::vec3> & vertices,
    std::vector<glm::vec2> & uvs,
    std::vector<glm::vec3> & normals
);


#endif /* objloader_hpp */
