#ifndef COMMUN_H
#define COMMUN_H

    // Include Windows

    //#include <GL/glew.h>

    #ifdef WIN32
        #include <GL/glew.h>


        // Include Mac

    #elif __APPLE__
        #define GL3_PROTOTYPES 1
        #include <OpenGL/gl3.h>


        // Include UNIX/Linux

    #else
        #define GL3_PROTOTYPES 1
        #include <GL3/gl3.h>

    #endif

    #include <glm/glm.hpp>
    #include <glm/gtx/transform.hpp>
    #include <glm/gtc/type_ptr.hpp>
    #include <glm/gtc/constants.hpp>

    #include <SDL.h>
    #include <string>
    #include <fstream>
    #include <iostream>
    #include <math.h>
    #include <vector>
    #include <time.h>

    #define M_2PI       6.2831853071795864769252867664
    #define M_PI_180    0.0174532925199432957692369076
    #define M_180_PI    57.295779513082320876798154814

#endif
