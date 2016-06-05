#ifndef SCENEOPENGL_H
#define SCENEOPENGL_H

#include "commun.h"

typedef std::vector<double> dvect;

class sceneOpengl
{
    public:
        sceneOpengl(std::string title, int largeur, int hauteur);
        ~sceneOpengl();

        bool initWindow();
        bool initGL();

        void deplaceSommets(double* sommets, int nbSommets, glm::vec2);
        void bouclePrincipale();
        void draw2DScene(double* vertices, int fisrtVertex, int verticesNumber, float* verticesColor, GLint id_shader);
        void draw2DScene(double* vertices, int fisrtVertex, int verticesNumber, short* verticesColor, GLint id_shader);

    protected:

    private:

        std::string m_titreFenetre;
        int m_largeur;
        int m_hauteur;

        SDL_Window* m_fenetre;
        SDL_GLContext m_contexteOpenGL;
        SDL_Event m_events;

        glm::mat4 projection;
        glm::mat4 viewPosNZoomMatrix;
};

#endif // SCENEOPENGL_H
