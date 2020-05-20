//
//  Canvas.h
//
//  Created by Warren R. Carithers 2016/09/30.
//  Based on a C++ version created by Joe Geigel.
//  Copyright 2016 Rochester Institute of Technology. All rights reserved.
//
//  Prototypes for routines for manipulating a simple canvas
//  holding point information along with color data.
//
//  This file should not be modified by students.
//

#ifndef _CANVAS_H_
#define _CANVAS_H_

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#endif

#ifndef __APPLE__
#include <GL/glew.h>
#endif

#include <GLFW/glfw3.h>

using namespace std;

#include <vector>

#include "Vertex.h"

///
// Simple canvas class that allows for pixel-by-pixel rendering.
///

class Canvas {

    ///
    // canvas size information
    ///
    int width;
    int height;

    // this determines the texture to be currently drawn
    GLfloat parameterValue;

    ///
    // point-related data
    ///
    vector<float> points;
    vector<float> texCoords;
    float* texCoordArray;
    float *pointArray;
    int numElements;
    GLuint *elemArray;

    ///
    // color-related data
    ///
    vector<float> colors;
    float *colorArray;
    GLfloat currentColor[3]; // RGB only - A is fixed

public:
    ///
    // Constructor
    //
    // @param w width of canvas
    // @param h height of canvas
    ///
    Canvas( int w, int h );

    ///
    // Destructor
    ///
    ~Canvas( void );

    ///
    // clears the canvas
    ///
    void clear( void );

    ///
    // adds a triangle to the current shape
    //
    // @param p0 first triangle vertex
    // @param p1 second triangle vertex
    // @param p2 final triangle vertex
    ///
    void addTriangle( Vertex p0, Vertex p1, Vertex p2 );

    void addTriangleTexCoord(Vertex p0, Vertex p1, Vertex p2);

    ///
    // Sets the current color
    //
    // @param r The red component of the new color (between 0-1)
    // @param g The green component of the new color (between 0-1)
    // @param b The blue component of the new color (between 0-1);
    ///
    void setColor( float r, float g, float b );

    ///
    // writes a pixel using the current color
    //
    // @param x The x coord of the pixel to be set
    // @param y The y coord of the pixel to be set
    ///
    void setPixel( int x, int y );

    ///
    // retrieve the array of element data from this Canvas
    ///
    GLuint *getElements( void );

    ///
    // retrieve the array of vertex data from this Canvas
    ///
    float *getVertices( void );

    ///
    // retrieve the array of color data from this Canvas
    ///
    float *getColors( void );

    // retrieves the tex coords data from this canvas
    float* getTexCoords( void );

    ///
    // retrieve the vertex count from this Canvas
    ///
    int numVertices( void );

    // retrieves the parameter value
    GLfloat getParameterVal( void );

    // sets the parameter value
    void setParameterVal(GLfloat val );

};

#endif
