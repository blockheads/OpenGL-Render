//
//  tessMain.cpp
//
//  Created by Warren R. Carithers 2016/11/04.
//  Based on code created by Joe Geigel and updated by
//    Vasudev Prasad Bethamcherla.
//  Copyright 2016 Rochester Institute of Technology.  All rights reserved.
//
//  Main program for tessellation assignment.
//
//  This file should not be modified by students.
//

#include <cstdlib>
#include <iostream>

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#endif

#ifndef __APPLE__
#include <GL/glew.h>
#endif

#include <GLFW/glfw3.h>

#include "Buffers.h"
#include "ShaderSetup.h"
#include "Canvas.h"
#include "Shapes.h"
#include <soil.h>

using namespace std;

// The shapes that we can draw
#define CUBE 0
#define CYLINDER 1
#define CONE 2
#define SPHERE 3
#define STEVE 4

int currentShape = CUBE;

// dimensions of the drawing window
int w_width  = 512;
int w_height = 512;

// subdivisions for tessellation
int division1 = 1;
int division2 = 1;

// are we animating?
bool animating = false;

// do we need to do a display() call?
bool updateDisplay = true;

// how to calculate an offset into the vertex buffer
#define BUFFER_OFFSET(i) ((char *)NULL + (i))

// our Canvas
Canvas *canvas;

// buffer information
BufferSet shapeBuffers;

// GLSL shader program handle
GLuint program;

// "fall back" to GLSL 1.20 shaders?
bool useAltShaders = false;

// shader arguments
GLuint theta;      // theta uniform location
GLuint vPosition;  // vertex location

// rotation control
float anglesReset[3] = {30.0, 30.0, 0.0};
float angles[3] = {30.0, 30.0, 0.0};
float angleInc = 5.0;

// for our model view
// current values for transformations
GLfloat rotateDefault[3] = { 0.0f, 0.0f, 0.0f };
GLfloat translateDefault[3] = { 0.0f, 0.0f, 0.0f };
GLfloat scaleDefault[3] = { 0.5f, 0.5f, 0.5f };

// current view values
GLfloat eyeDefault[3] = { 1.0f, 10.0f, -5.0f };
GLfloat lookDefault[3] = { 1.0f, 3.0f, 0.0f };
GLfloat upDefault[3] = { 0.0f, 1.0f, 0.0f };
// light pos
GLfloat lightPos[3] = { 5.5,3.0f,0.0f };

// clipping window boundaries
GLfloat cwLeft = -1.0f;
GLfloat cwRight = 1.0f;
GLfloat cwTop = 1.0f;
GLfloat cwBottom = -1.0f;
GLfloat cwNear = 3.0f;
GLfloat cwFar = 100.5f;

// textures
GLuint diamondTexture;
GLuint steveTexture;
GLuint cobbleTexture;
GLuint torchTexture;


///
// OpenGL initialization
///
void init( void ) {

    // Create our Canvas
    canvas = new Canvas( w_width, w_height );

    if( canvas == NULL ) {
        cerr << "error - cannot create Canvas" << endl;
	glfwTerminate();
	exit( 1 );
    }

    // Load shaders and use the resulting shader program
    ShaderError error;
    if( useAltShaders ) {
        program = shaderSetup( "alt.vert", "alt.frag", &error );
    } else {
        program = shaderSetup( "shader.vert", "shader.frag", &error );
    }
    if( !program ) {
        cerr << "Error setting up shaders - " <<
	    errorString(error) << endl;
	glfwTerminate();
	exit( 1 );
    }
    
    // select this shader program
    glUseProgram( program );

    // get location of shader global variables
    vPosition = glGetAttribLocation( program, "vPosition" );
    theta = glGetUniformLocation( program, "theta" );

    glEnable( GL_DEPTH_TEST );
    glEnable(GL_CULL_FACE);
    glCullFace( GL_BACK );
    glClearColor( 0.0, 0.0, 0.0, 1.0 );
    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
    glClearDepth( 1.0 );

    // setting up our view
    GLint leftLoc = glGetUniformLocation(program, "left");
    GLint rightLoc = glGetUniformLocation(program, "right");
    GLint topLoc = glGetUniformLocation(program, "top");
    GLint bottomLoc = glGetUniformLocation(program, "bottom");
    GLint nearLoc = glGetUniformLocation(program, "near");
    GLint farLoc = glGetUniformLocation(program, "far");

    glUniform1f(leftLoc, cwLeft);
    glUniform1f(rightLoc, cwRight);
    glUniform1f(topLoc, cwTop);
    glUniform1f(bottomLoc, cwBottom);
    glUniform1f(nearLoc, cwNear);
    glUniform1f(farLoc, cwFar);

    GLint posLoc = glGetUniformLocation(program, "cPosition");
    GLint lookLoc = glGetUniformLocation(program, "cLookAt");
    GLint upVecLoc = glGetUniformLocation(program, "cUp");

    glUniform3fv(posLoc, 1, eyeDefault);
    glUniform3fv(lookLoc, 1, lookDefault);
    glUniform3fv(upVecLoc, 1, upDefault);

    GLint thetaLoc = glGetUniformLocation(program, "theta");
    GLint transLoc = glGetUniformLocation(program, "trans");
    GLint scaleLoc = glGetUniformLocation(program, "scale");

    glUniform3fv(thetaLoc, 1, rotateDefault);
    glUniform3fv(transLoc, 1, translateDefault);
    glUniform3fv(scaleLoc, 1, scaleDefault);

    // for lighting
    GLint lightLoc = glGetUniformLocation(program, "lightPos");
    glUniform3fv(lightLoc, 1, lightPos);

    // for our textures
    // loading textures

    // loading in minecraft steve's texture
    diamondTexture = SOIL_load_OGL_texture // load an image file directly as a new OpenGL texture 
    (
        "objects/diamond.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB
    );

    // loading in the floors texture
    cobbleTexture = SOIL_load_OGL_texture // load an image file directly as a new OpenGL texture 
    (
        "objects/cobble.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB
    );

    // loading in minecraft steve's texture
    steveTexture = SOIL_load_OGL_texture // load an image file directly as a new OpenGL texture 
    (
        "objects/Steve.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB
    );

    // loading in minecraft steve's texture
    torchTexture = SOIL_load_OGL_texture // load an image file directly as a new OpenGL texture 
    (
        "objects/torch.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB
    );

    /* init_resources */
    GLint attribute_texcoord = glGetAttribLocation(program, "texcoord");
}

///
// selectBuffers() - bind the correct vertex and element buffers
//
// @param program - GLSL program object
// @param B       - the BufferSet to update
///
void selectBuffers( GLuint program, BufferSet &B ) {

    // bind the buffers
    glBindBuffer( GL_ARRAY_BUFFER, B.vbuffer );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, B.ebuffer );

    // set up the vertex attribute variables
    
    // for vertex positions, size of 4 float
    glEnableVertexAttribArray(vPosition);
    glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)0);
    

    GLint texAttrib = glGetAttribLocation(program, "texcoord");
    glEnableVertexAttribArray(texAttrib);
    glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE,
        9 * sizeof(float), (void*)(4 * sizeof(float)));

    GLint normAttrib = glGetAttribLocation(program, "vNormal");
    glEnableVertexAttribArray(normAttrib);
    glVertexAttribPointer(normAttrib, 3, GL_FLOAT, GL_FALSE,
        9 * sizeof(float), (void*)(6 * sizeof(float)));

    
    glUniform3fv(theta, 1, angles);

    // send down our rotation angles
    glUniform3fv( theta, 1, angles );
}

void resetTranslate() {
    GLint transLoc = glGetUniformLocation(program, "trans");
    GLint scaleLoc = glGetUniformLocation(program, "scale");
    glUniform3fv(transLoc, 1, translateDefault);
    glUniform3fv(scaleLoc, 1, scaleDefault);
}

void display( void ) {


    std::cout << "displaying.. " << std::endl;
    // clear the frame buffer
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    // STEVE

    // use back face culling for steve
    glCullFace(GL_BACK);
    
    // reseting our scale and translation
    resetTranslate();

    GLint transLoc = glGetUniformLocation(program, "trans");
    glUniform3fv(transLoc, 1, new GLfloat[3]{ -.7,0, 0 });

    //texturing
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, steveTexture);

    makeSteve(*canvas, program);

    // texturing
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, steveTexture);


    shapeBuffers.createBuffers(*canvas);

    selectBuffers(program, shapeBuffers);

    // draw our shape
    glDrawElements(GL_TRIANGLES, shapeBuffers.numElements,
        GL_UNSIGNED_INT, (void*)0);

    // clear our canvas
    canvas->clear();



    // CUBE

    GLint scaleLoc = glGetUniformLocation(program, "scale");

    glUniform3fv(transLoc, 1, new GLfloat[3]{ 3.05,1.15, 0 });
    glUniform3fv(scaleLoc, 1, new GLfloat[3]{ 1.6,1.6,1.6 });

    // use front face culling for our cube

    glCullFace(GL_FRONT);

    // texutring
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, diamondTexture);
   
    // apply our shape transformation
    makeCube(*canvas, division1, program);

    shapeBuffers.createBuffers(*canvas);
    
    // bind our buffers
    selectBuffers(program, shapeBuffers);
    // draw our shape
    glDrawElements( GL_TRIANGLES, shapeBuffers.numElements,
                    GL_UNSIGNED_INT, (void *)0 );

    // clear our canvas
    canvas->clear();

    // FLOOR
    glCullFace(GL_BACK);


    glUniform3fv(transLoc, 1, new GLfloat[3]{ -1.7,5.2, 1 });
    glUniform3fv(scaleLoc, 1, new GLfloat[3]{15,10,15 });
    
    // our floor is a cube we see inside of, so it's techincally our containing box
    // just was originally a floor

    // texturing
    // specifying paramaters
   

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, cobbleTexture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // apply our shape transformation
    makeFloor(*canvas, program);

    shapeBuffers.createBuffers(*canvas);

    // bind our buffers
    selectBuffers(program, shapeBuffers);
    
    glDrawElements(GL_TRIANGLES, shapeBuffers.numElements,
        GL_UNSIGNED_INT, (void*)0);

    // clear our canvas
    canvas->clear();


    // TORCH

    glCullFace(GL_BACK);
    resetTranslate();

    glUniform3fv(transLoc, 1, lightPos);
    glUniform3fv(scaleLoc, 1, new GLfloat[3]{ 1.0,1.0,1.0 });

    // our floor is a cube we see inside of, so it's techincally our containing box
    // just was originally a floor

    // texturing
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, torchTexture);

    // apply our shape transformation
    makeTorch(*canvas, program);

    shapeBuffers.createBuffers(*canvas);

    // bind our buffers
    selectBuffers(program, shapeBuffers);
    // draw our shape
    glDrawElements(GL_TRIANGLES, shapeBuffers.numElements,
        GL_UNSIGNED_INT, (void*)0);


    // clear our canvas
    canvas->clear();
    
}

// Can cause gimbal lock which also happened on Apollo 11
// http://en.wikipedia.org/wiki/Gimbal_lock#Gimbal_lock_on_Apollo_11
// Solution? Use Quaternions (Taught in Comp. Animation: Algorithms)
//
// TIDBIT:
// Quaternion plaque on Brougham (Broom) Bridge, Dublin, which says:
// 
//    "Here as he walked by
//    on the 16th of October 1843
// 
//    Sir William Rowan Hamilton 
//    
//    in a flash of genius discovered
//    the fundamental formula for
//    quaternion multiplication
//    i^2 = j^2 = k^2 = ijk = -1
//    & cut it on a stone of this bridge"

void animate() {
    int i;
    static int level = 0;

    if( level >= 450 ) {
        level = 0;
	animating = false;
    }

    if( !animating ) {
        return;
    }

    angles[1] -= angleInc / 3;

    ++level;
    updateDisplay = true;
}


void keyboard( GLFWwindow *window, unsigned int codepoint )
{

    switch( codepoint & 0x7f ) {

	// termination
        case 033:  // Escape key
        case 'q': case 'Q':
            glfwSetWindowShouldClose( window, 1 );

	// automated animation
        case 'a': case 'A':
	    animating = true;
	    break;

	// incremental rotation along the axes
        case 'x': angles[0] -= angleInc; break;
        case 'y': angles[1] -= angleInc; break;
        case 'z': angles[2] -= angleInc; break;
        case 'X': angles[0] += angleInc; break;
        case 'Y': angles[1] += angleInc; break;
        case 'Z': angles[2] += angleInc; break;

	// reset
	    case 'r': case 'R':
	    angles[0] = anglesReset[0];
	    angles[1] = anglesReset[1];
	    angles[2] = anglesReset[2];
	    break;
    }

    updateDisplay = true;
}


void glfwError( int code, const char *desc )
{
    cerr << "GLFW error " << code << ": " << desc << endl;
    exit( 2 );
}

///
// main program for tessellation assignment
///
int main( int argc, char **argv ) {

    glfwSetErrorCallback( glfwError );

    if( !glfwInit() ) {
        cerr << "Can't initialize GLFW!" << endl;
        exit( 1 );
    }

    GLFWwindow *window = glfwCreateWindow( w_width, w_height,
        "CSCI 510 Final - Nicholas Pueschel", NULL, NULL );

    if( !window ) {
        cerr << "GLFW window create failed!" << endl;
        glfwTerminate();
        exit( 1 );
    }

    glfwMakeContextCurrent( window );

#ifndef __APPLE__
    GLenum err = glewInit();
    if( err != GLEW_OK ) {
        cerr << "GLEW error: " << glewGetErrorString(err) << endl;
        glfwTerminate();
        exit( 1 );
    }
    if( !GLEW_VERSION_3_2 ) {
        cerr << "GLEW: OpenGL 3.2 not available" << endl;
        if( !GLEW_VERSION_2_1 ) {
            cerr << "GLEW: OpenGL 2.1 not available, either!" << endl;
            glfwTerminate();
            exit( 1 );
        }
    }
#endif

    // determine whether or not we can use GLSL 1.50
    int maj = glfwGetWindowAttrib( window, GLFW_CONTEXT_VERSION_MAJOR );
    int min = glfwGetWindowAttrib( window, GLFW_CONTEXT_VERSION_MINOR );

    cerr << "GLFW: using " << maj << "." << min << " context" << endl;
    if( maj < 3 || (maj == 3 && min < 2) ) {
        // nope!
        useAltShaders = true;
    }

    init();

    glfwSetCharCallback( window, keyboard );

    while( !glfwWindowShouldClose(window) ) {
        animate();
        if( updateDisplay ) {
            updateDisplay = false;
            display();
            glfwSwapBuffers( window );
        }
        glfwPollEvents();
    }

    glfwDestroyWindow( window );
    glfwTerminate();

    return 0;
}
