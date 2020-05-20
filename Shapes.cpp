//
//  Shapes
//
//  Routines for tessellating a number of basic shapes
//
//  Students are to supply their implementations for the functions in
//  this file using the function addTriangle() to do the tessellation.
//
//  This code can be compiled as either C or C++.
//

#include <cmath>

// Canvas.h pulls in all the OpenGL/GLFW/etc. header files for us
#include "Shapes.h"
#include "Canvas.h"
#include "Vertex.h"
#include "glm/glm.hpp"

#include <iostream>
#define TINYOBJLOADER_IMPLEMENTATION // define this in only *one* .cc
#include "tiny_obj_loader.h"
#include <SOIL.h>


///
// makeCube - Create a unit cube, centered at the origin, with a given number
// of subdivisions in each direction on each face.
//
// @param subdivision - number of equal subdivisions to be made in each 
//        direction along each face
//
// Can only use calls to C.addTriangle()
///
void makeCube( Canvas &C, int subdivisions, GLuint program )
{
    C.setParameterVal(0);
    if( subdivisions < 1 )
        subdivisions = 1;

    //variables
    Vertex a;
    Vertex b;
    Vertex c;
    int i;
    int j;
    

    

    // specifying paramaters
 /*   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);*/


    
    //glUniform1i(glGetUniformLocation(program, "diamondTexture"), 0);

    //loop through x and y for planes.
    for (i=-subdivisions; i<subdivisions; i+=2){
        for (j=-subdivisions; j<subdivisions; j+=2){
            
            //
            //front and back
            //
            
            a.x = .5*i/subdivisions;
            a.y = .5*j/subdivisions;
            a.z = .5;
            a.txX = 1;
            a.txY = 1;
            a.nx = 0;
            a.ny = 0;
            a.nz = -1;

            b.x = .5*i/subdivisions;
            b.y = .5*(j+2)/subdivisions;
            b.z = .5;
            b.txX = 1;
            b.txY = 0;
            b.nx = 0;
            b.ny = 0;
            b.nz = -1;
            
            c.x = .5*(i+2)/subdivisions;
            c.y = .5*j/subdivisions;
            c.z = .5;
            c.txX = 0;
            c.txY = 1;
            c.nx = 0;
            c.ny = 0;
            c.nz = -1;
            
            C.addTriangleTexCoord(a,b,c);
            
           
            a.z = -.5;
            b.z = -.5;
            c.z = -.5;

            
            a.nz = 1;
            b.nz = 1;
            c.nz = 1;
            
            C.addTriangleTexCoord(c,b,a);
            
            a.x = .5*(i+2)/subdivisions;
            a.y = .5*(j+2)/subdivisions;
            a.z = .5;
            b.z = .5;
            c.z = .5;
            a.nz = -1;
            b.nz = -1;
            c.nz = -1;

            C.addTriangleTexCoord(b,a,c);
            
            a.z = -.5;
            b.z = -.5;
            c.z = -.5;

            a.nz = 1;
            b.nz = 1;
            c.nz = 1;
            
            C.addTriangleTexCoord(c,a,b);
            
            //
            //left and right
            //
            
            a.y = .5*i/subdivisions;
            a.z = .5*j/subdivisions;
            a.x = .5;
            a.txX = 1;
            a.txY = 1;

            a.nx = 1;
            a.ny = 0;
            a.nz = 0;
            b.nx = 1;
            b.ny = 0;
            b.nz = 0;
            c.nx = 1;
            c.ny = 0;
            c.nz = 0;

            b.y = .5*i/subdivisions;
            b.z = .5*(j+2)/subdivisions;
            b.x = .5;
            b.txX = 0;
            b.txY = 1;
            
            c.y = .5*(i+2)/subdivisions;
            c.z = .5*j/subdivisions;
            c.x = .5;
            c.txX = 1;
            c.txY = 0;
            
            C.addTriangleTexCoord(a,b,c);
            
            a.x = -.5;
            b.x = -.5;
            c.x = -.5;
            a.nx = -1;
            b.nx = -1;
            c.nx = -1;
      
            
            C.addTriangleTexCoord(c,b,a);
            
            a.y = .5*(i+2)/subdivisions;
            a.z = .5*(j+2)/subdivisions;
            a.x = .5;
            b.x = .5;
            c.x = .5;
            a.nx = 1;
            b.nx = 1;
            c.nx = 1;
            
            C.addTriangleTexCoord(b,a,c);
            
            a.x = -.5;
            b.x = -.5;
            c.x = -.5;
            a.nx = -1;
            b.nx = -1;
            c.nx = -1;
            
            C.addTriangleTexCoord(c,a,b);
            
            //
            //top and bottom
            //
            
            a.z = .5*i/subdivisions;
            a.x = .5*j/subdivisions;
            a.y = .5;
            a.txX = 1;
            a.txY = 1;

            b.z = .5*i/subdivisions;
            b.x = .5*(j+2)/subdivisions;
            b.y = .5;
            b.txX = 1;
            b.txY = 0;
            
            c.z = .5*(i+2)/subdivisions;
            c.x = .5*j/subdivisions;
            c.y = .5;
            c.txX = 0;
            c.txY = 1;

            a.nx = 0;
            a.ny = 1;
            a.nz = 0;
            b.nx = 0;
            b.ny = 1;
            b.nz = 0;
            c.nx = 0;
            c.ny = 1;
            c.nz = 0;
            
            C.addTriangleTexCoord(a,b,c);
            
            a.y = -.5;
            b.y = -.5;
            c.y = -.5;
            a.ny = -1;
            b.ny = -1;
            c.ny = -1;
            
            C.addTriangleTexCoord(c,b,a);
            
            a.z = .5*(i+2)/subdivisions;
            a.x = .5*(j+2)/subdivisions;
            a.y = .5;
            b.y = .5;
            c.y = .5;
            a.ny = 1;
            b.ny = 1;
            c.ny = 1;
           
            
            C.addTriangleTexCoord(b,a,c);
            
            a.y = -.5;
            b.y = -.5;
            c.y = -.5;
            a.ny = -1;
            b.ny = -1;
            c.ny = -1;
            
            C.addTriangleTexCoord(c,a,b);
            
        }
    }
    
}

// draws the floor for the scene
void makeFloor(Canvas& C, GLuint program)
{
    // a floor is just the front of a cube

    Vertex a;
    Vertex b;
    Vertex c;
    int i, j;
    int subdivisions = 1;
 
    //
    //front and back
    //
    //loop through x and y for planes.
    for (i = -subdivisions; i < subdivisions; i += 2) {
        for (j = -subdivisions; j < subdivisions; j += 2) {
            //
            //front and back
            //
            
            a.x = .5 * i / subdivisions;
            a.y = .5 * j / subdivisions;
            a.z = .5;
            a.txX = 8;
            a.txY = 8;
            a.nx = 0;
            a.ny = 0;
            a.nz = 1;

            b.x = .5 * i / subdivisions;
            b.y = .5 * (j + 2) / subdivisions;
            b.z = .5;
            b.txX = 8;
            b.txY = 0;
            b.nx = 0;
            b.ny = 0;
            b.nz = 1;

            c.x = .5 * (i + 2) / subdivisions;
            c.y = .5 * j / subdivisions;
            c.z = .5;
            c.txX = 0;
            c.txY = 8;
            c.nx = 0;
            c.ny = 0;
            c.nz = 1;

            C.addTriangleTexCoord(a, b, c);


            a.z = -.5;
            b.z = -.5;
            c.z = -.5;


            a.ny = -1;
            b.ny = -1;
            c.ny = -1;

            C.addTriangleTexCoord(c, b, a);

            a.x = .5 * (i + 2) / subdivisions;
            a.y = .5 * (j + 2) / subdivisions;
            a.z = .5;
            b.z = .5;
            c.z = .5;
            a.ny = 1;
            b.ny = 1;
            c.ny = 1;

            C.addTriangleTexCoord(b, a, c);

            a.z = -.5;
            b.z = -.5;
            c.z = -.5;

            a.ny = -1;
            b.ny = -1;
            c.ny = -1;
            
            C.addTriangleTexCoord(c, a, b);
            
            
            //
            //left and right
            //

            a.y = .5 * i / subdivisions;
            a.z = .5 * j / subdivisions;
            a.x = .5;
            a.txX = 8;
            a.txY = 8;

            a.nx = 0;
            a.ny = 0;
            a.nz = -1;
            b.nx = 0;
            b.ny = 0;
            b.nz = -1;
            c.nx = 0;
            c.ny = 0;
            c.nz = -1;

            b.y = .5 * i / subdivisions;
            b.z = .5 * (j + 2) / subdivisions;
            b.x = .5;
            b.txX = 0;
            b.txY = 8;

            c.y = .5 * (i + 2) / subdivisions;
            c.z = .5 * j / subdivisions;
            c.x = .5;
            c.txX = 8;
            c.txY = 0;

            C.addTriangleTexCoord(a, b, c);

            a.x = -.5;
            b.x = -.5;
            c.x = -.5;
            a.nz = 1;
            b.nz = 1;
            c.nz = 1;


            C.addTriangleTexCoord(c, b, a);

            a.y = .5 * (i + 2) / subdivisions;
            a.z = .5 * (j + 2) / subdivisions;
            a.x = .5;
            b.x = .5;
            c.x = .5;
            a.nz = -1;
            b.nz = -1;
            c.nz = -1;

            C.addTriangleTexCoord(b, a, c);

            a.x = -.5;
            b.x = -.5;
            c.x = -.5;
            a.nz = 1;
            b.nz = 1;
            c.nz = 1;

            C.addTriangleTexCoord(c, a, b);
            
            //
            //top and bottom
            //

            a.z = .5 * i / subdivisions;
            a.x = .5 * j / subdivisions;
            a.y = .5;
            a.txX = 8;
            a.txY = 8;

            b.z = .5 * i / subdivisions;
            b.x = .5 * (j + 2) / subdivisions;
            b.y = .5;
            b.txX = 8;
            b.txY = 0;

            c.z = .5 * (i + 2) / subdivisions;
            c.x = .5 * j / subdivisions;
            c.y = .5;
            c.txX = 0;
            c.txY = 8;

            a.nx = -1;
            a.ny = 0;
            a.nz = 0;
            b.nx = -1;
            b.ny = 0;
            b.nz = 0;
            c.nx = -1;
            c.ny = 0;
            c.nz = 0;

            C.addTriangleTexCoord(a, b, c);

            a.y = -.5;
            b.y = -.5;
            c.y = -.5;
            a.nx = 1;
            b.nx = 1;
            c.nx = 1;

            C.addTriangleTexCoord(c, b, a);

            a.z = .5 * (i + 2) / subdivisions;
            a.x = .5 * (j + 2) / subdivisions;
            a.y = .5;
            b.y = .5;
            c.y = .5;
            a.nx = -1;
            b.nx = -1;
            c.nx = -1;


            C.addTriangleTexCoord(b, a, c);

            a.y = -.5;
            b.y = -.5;
            c.y = -.5;
            a.nx = 1;
            b.nx = 1;
            c.nx = 1;

            C.addTriangleTexCoord(c, a, b);
            
        }
    }
}


void makeSteve(Canvas& C, GLuint program)
{
    std::string inputfile = "objects/steve.obj";
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;

    std::string warn;
    std::string err;

    bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, inputfile.c_str());

    if (!warn.empty()) {
        std::cout << warn << std::endl;
    }

    if (!err.empty()) {
        std::cerr << err << std::endl;
    }

    if (!ret) {
        exit(1);
    }

    
    //glUniform1i(glGetUniformLocation(program, "steveTexture"), 0);

    // Loop over shapes
    for (size_t s = 0; s < shapes.size(); s++) {
        // Loop over faces(polygon)
        size_t index_offset = 0;

        // 2d array of our tex cords for each 3 vertex face

        // this is a face
        GLfloat tex_coords[6];
        std::cout << "This shape has " << shapes[s].mesh.num_face_vertices.size() << " faces." << std::endl;
        for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
            int fv = shapes[s].mesh.num_face_vertices[f];

            // we know our faces are made up of object files for this paticular obj file
            std::cout << "size: " << fv << std::endl;

            // this is the first index for the face
            tinyobj::index_t idx_a = shapes[s].mesh.indices[index_offset + 0];
            // this is our second index for the face
            tinyobj::index_t idx_b = shapes[s].mesh.indices[index_offset + 1];
            // this is our third index for the face
            tinyobj::index_t idx_c = shapes[s].mesh.indices[index_offset + 2];

            // constructing our vertices to store our triangle data
            Vertex a;
            Vertex b;
            Vertex c;

            a.x = attrib.vertices[3 * idx_a.vertex_index + 0];
            a.y = attrib.vertices[3 * idx_a.vertex_index + 1];
            a.z = attrib.vertices[3 * idx_a.vertex_index + 2];

            b.x = attrib.vertices[3 * idx_b.vertex_index + 0];
            b.y = attrib.vertices[3 * idx_b.vertex_index + 1];
            b.z = attrib.vertices[3 * idx_b.vertex_index + 2];

            c.x = attrib.vertices[3 * idx_c.vertex_index + 0];
            c.y = attrib.vertices[3 * idx_c.vertex_index + 1];
            c.z = attrib.vertices[3 * idx_c.vertex_index + 2];

            // texure coordinates for these verices
            a.txX = attrib.texcoords[2 * idx_a.texcoord_index + 0];
            a.txY = attrib.texcoords[2 * idx_a.texcoord_index + 1];

            b.txX = attrib.texcoords[2 * idx_b.texcoord_index + 0];
            b.txY = attrib.texcoords[2 * idx_b.texcoord_index + 1];

            c.txX = attrib.texcoords[2 * idx_c.texcoord_index + 0];
            c.txY = attrib.texcoords[2 * idx_c.texcoord_index + 1];

            // normals
            a.nx = attrib.normals[3 * idx_a.normal_index + 0];
            a.ny = attrib.normals[3 * idx_a.normal_index + 1];
            a.nz = attrib.normals[3 * idx_a.normal_index + 2];

            b.nx = attrib.normals[3 * idx_b.normal_index + 0];
            b.ny = attrib.normals[3 * idx_b.normal_index + 1];
            b.nz = attrib.normals[3 * idx_b.normal_index + 2];

            c.nx = attrib.normals[3 * idx_c.normal_index + 0];
            c.ny = attrib.normals[3 * idx_c.normal_index + 1];
            c.nz = attrib.normals[3 * idx_c.normal_index + 2];


            // adding our triangle
            C.addTriangleTexCoord(a, b, c);
            //C.addTexCoord(a, b, c);

            index_offset += fv;
        }
        /*glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);*/

    }

}

//  makes a torch
void makeTorch(Canvas& C, GLuint program)
{
    std::string inputfile = "objects/torch.obj";
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;

    std::string warn;
    std::string err;

    bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, inputfile.c_str());

    if (!warn.empty()) {
        std::cout << warn << std::endl;
    }

    if (!err.empty()) {
        std::cerr << err << std::endl;
    }

    if (!ret) {
        exit(1);
    }

    
    //glUniform1i(glGetUniformLocation(program, "steveTexture"), 0);

    // Loop over shapes
    for (size_t s = 0; s < shapes.size(); s++) {
        // Loop over faces(polygon)
        size_t index_offset = 0;

        // 2d array of our tex cords for each 3 vertex face

        // this is a face
        GLfloat tex_coords[6];
        std::cout << "This shape has " << shapes[s].mesh.num_face_vertices.size() << " faces." << std::endl;
        for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
            int fv = shapes[s].mesh.num_face_vertices[f];

            // we know our faces are made up of object files for this paticular obj file
            std::cout << "size: " << fv << std::endl;

            // this is the first index for the face
            tinyobj::index_t idx_a = shapes[s].mesh.indices[index_offset + 0];
            // this is our second index for the face
            tinyobj::index_t idx_b = shapes[s].mesh.indices[index_offset + 1];
            // this is our third index for the face
            tinyobj::index_t idx_c = shapes[s].mesh.indices[index_offset + 2];

            // constructing our vertices to store our triangle data
            Vertex a;
            Vertex b;
            Vertex c;

            a.x = attrib.vertices[3 * idx_a.vertex_index + 0];
            a.y = attrib.vertices[3 * idx_a.vertex_index + 1];
            a.z = attrib.vertices[3 * idx_a.vertex_index + 2];

            b.x = attrib.vertices[3 * idx_b.vertex_index + 0];
            b.y = attrib.vertices[3 * idx_b.vertex_index + 1];
            b.z = attrib.vertices[3 * idx_b.vertex_index + 2];

            c.x = attrib.vertices[3 * idx_c.vertex_index + 0];
            c.y = attrib.vertices[3 * idx_c.vertex_index + 1];
            c.z = attrib.vertices[3 * idx_c.vertex_index + 2];

            // texure coordinates for these verices
            a.txX = attrib.texcoords[2 * idx_a.texcoord_index + 0];
            a.txY = attrib.texcoords[2 * idx_a.texcoord_index + 1];

            b.txX = attrib.texcoords[2 * idx_b.texcoord_index + 0];
            b.txY = attrib.texcoords[2 * idx_b.texcoord_index + 1];

            c.txX = attrib.texcoords[2 * idx_c.texcoord_index + 0];
            c.txY = attrib.texcoords[2 * idx_c.texcoord_index + 1];

            // normals
            a.nx = attrib.normals[3 * idx_a.normal_index + 0];
            a.ny = attrib.normals[3 * idx_a.normal_index + 1];
            a.nz = attrib.normals[3 * idx_a.normal_index + 2];

            b.nx = attrib.normals[3 * idx_b.normal_index + 0];
            b.ny = attrib.normals[3 * idx_b.normal_index + 1];
            b.nz = attrib.normals[3 * idx_b.normal_index + 2];

            c.nx = attrib.normals[3 * idx_c.normal_index + 0];
            c.ny = attrib.normals[3 * idx_c.normal_index + 1];
            c.nz = attrib.normals[3 * idx_c.normal_index + 2];


            // adding our triangle
            C.addTriangleTexCoord(a, b, c);
            //C.addTexCoord(a, b, c);

            index_offset += fv;
        }
        /*glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);*/

    }

}

///
// makeCylinder - Create polygons for a cylinder with unit height, centered at
// the origin, with separate number of radial subdivisions and height 
// subdivisions.
//
// @param radius - Radius of the base of the cylinder
// @param radialDivision - number of subdivisions on the radial base
// @param heightDivisions - number of subdivisions along the height
//
// Can only use calls to C.addTriangle()
///
void makeCylinder( Canvas &C, float radius, int radialDivisions, int heightDivisions )
{

    if( radialDivisions < 3 )
        radialDivisions = 3;

    if( heightDivisions < 1 )
        heightDivisions = 1;

    //constants
    const double mypi = std::acos(-1);
    const float rad = 2*mypi/radialDivisions;
    
    //variables
    Vertex a;
    Vertex b;
    Vertex c;
    int i;
    int j;
    
    for (i=0; i<radialDivisions; i+=1){
        for (j=-heightDivisions; j<heightDivisions; j+=2){
            
            a.x=radius*std::cos(i*rad);
            a.y=radius*std::sin(i*rad);
            a.z=.5*j/heightDivisions;

            b.x=radius*std::cos(i*rad);
            b.y=radius*std::sin(i*rad);
            b.z=.5*(j+2)/heightDivisions;
            
            c.x=radius*std::cos((i+1)*rad);
            c.y=radius*std::sin((i+1)*rad);
            c.z=.5*j/heightDivisions;
            
            C.addTriangle(a,b,c);
            
            a.x=radius*std::cos((i+1)*rad);
            a.y=radius*std::sin((i+1)*rad);

            c.z=.5*(j+2)/heightDivisions;
            
            C.addTriangle(b,c,a);
            
        }
        a.x=0;
        a.y=0;
        a.z=.5;
        b.z=.5;
        c.z=.5;

        C.addTriangle(a,c,b); //create tri at one of the ends
        
        a.z=-.5;
        b.z=-.5;
        c.z=-.5;
            
        C.addTriangle(a,b,c); //create tri at the oppisite end
    }
}


///
// makeCone - Create polygons for a cone with unit height, centered at the
// origin, with separate number of radial subdivisions and height 
// subdivisions.
//
// @param radius - Radius of the base of the cone
// @param radialDivision - number of subdivisions on the radial base
// @param heightDivisions - number of subdivisions along the height
//
// Can only use calls to C.addTriangle()
///
void makeCone( Canvas &C, float radius, int radialDivisions, int heightDivisions )
{

    if( radialDivisions < 3 )
        radialDivisions = 3;

    if( heightDivisions < 1 )
        heightDivisions = 1;

    //constants
    const double mypi = std::acos(-1);
    const float myrad = 2*mypi/radialDivisions;
    
    //variables
    Vertex a;
    Vertex b;
    Vertex c;
    int i;
    int j;
    for (i=0; i<radialDivisions; i+=1){
        for (j=-heightDivisions; j<heightDivisions; j+=2){
            float radiu=(j+heightDivisions)*.5*radius/heightDivisions;
            float radin=(j+2+heightDivisions)*.5*radius/heightDivisions;
            
            a.x=radiu*std::cos(i*myrad);
            a.y=radiu*std::sin(i*myrad);
            a.z=.5*j/heightDivisions;

            b.x=radin*std::cos(i*myrad);
            b.y=radin*std::sin(i*myrad);
            b.z=.5*(j+2)/heightDivisions;
            
            c.x=radiu*std::cos((i+1)*myrad);
            c.y=radiu*std::sin((i+1)*myrad);
            c.z=.5*j/heightDivisions;
            
            C.addTriangle(a,b,c);
            
            a.x=radin*std::cos((i+1)*myrad);
            a.y=radin*std::sin((i+1)*myrad);
            a.z=.5*(j+2)/heightDivisions;
            
            C.addTriangle(b,a,c);
            
        }
        a.x=radius*std::cos(i*myrad);
        a.y=radius*std::sin(i*myrad);
        a.z=.5;

        b.x=radius*std::cos((i+1)*myrad);
        b.y=radius*std::sin((i+1)*myrad);
        b.z=.5;
            
        c.x=0;
        c.y=0;
        c.z=.5;
            
        C.addTriangle(c,b,a);
    }
}


///
// makeSphere - Create sphere of a given radius, centered at the origin, 
// using spherical coordinates with separate number of thetha and 
// phi subdivisions.
//
// @param radius - Radius of the sphere
// @param slices - number of subdivisions in the theta direction
// @param stacks - Number of subdivisions in the phi direction.
//
// Can only use calls to C.addTriangle()
///
void makeSphere( Canvas &C, float radius, int slices, int stacks )
{

    C.setParameterVal(0);
    // IF DOING RECURSIVE SUBDIVISION:
    //   use a minimum value of 1 instead of 3
    //   add an 'else' clause to set a maximum value of 5
    if( slices < 3 )
        slices = 3;

    if( stacks < 3 )
        stacks = 3;
    
    //constants
    const double mypi = std::acos(-1);
    const float myrad1 = 2*mypi/slices;
    const float myrad2 = mypi/stacks;
    
    //variables
    Vertex a;
    Vertex b;
    Vertex c;
    int i;
    int j;
    float sin1;     //place to hold the value of the sin of myrad1*current_step
    float cos1;     //place to hold the value of the cos of myrad1*current_step
    float sin2;     //place to hold the value of the sin of myrad2*current_step
    float cos2;     //place to hold the value of the cos of myrad2*current_step
    float nsin1;    //place to hold the value of the sin of myrad1*next_step
    float ncos1;    //place to hold the value of the cos of myrad1*next_step
    float nsin2;    //place to hold the value of the sin of myrad2*next_step
    float ncos2;    //place to hold the value of the cos of myrad2*next_step
    
    //loop throught both angles in steps.
    for (i=0; i<slices; i+=1){
        for (j=0; j<stacks; j+=1){
            sin1 = std::sin(i*myrad1);
            cos1 = std::cos(i*myrad1);
            sin2 = std::sin(j*myrad2);
            cos2 = std::cos(j*myrad2);
            nsin1 = std::sin((i+1)*myrad1);
            ncos1 = std::cos((i+1)*myrad1);
            nsin2 = std::sin((j+1)*myrad2);
            ncos2 = std::cos((j+1)*myrad2);
            
            a.x = radius*cos1*sin2;
            a.y = radius*sin1*sin2;
            a.z = radius*cos2;
            
            b.x = radius*cos1*nsin2;
            b.y = radius*sin1*nsin2;
            b.z = radius*ncos2;
            
            c.x=radius*ncos1*sin2;
            c.y=radius*nsin1*sin2;
            c.z=radius*cos2;
            
            C.addTriangle(a,b,c);   //create tri
            
            a.x=radius*ncos1*nsin2;
            a.y=radius*nsin1*nsin2;
            a.z=radius*ncos2;
            
            C.addTriangle(b,a,c);   //create partner tri
            
        }
    }
}
