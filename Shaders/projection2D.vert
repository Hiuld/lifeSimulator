// Version du GLSL

#version 150 core


// Entrées

in vec2 in_Vertex;
in vec4 in_Color;


// Uniform

uniform mat4 projection;
uniform mat4 direction;
uniform mat4 deplacement;
uniform mat4 position;


// Sortie

out vec4 color;


// Fonction main

void main()
{
    // projection du sommet

    gl_Position =  projection * (( vec4(in_Vertex, 0.0, 1.0) * position * direction )) ;

    // Envoi de la couleur au Fragment Shader

    color = in_Color;
}
