#ifndef QUADRILATERE_H
#define QUADRILATERE_H

#include "commun.h"
#include "Shader.h"

class Quadrilatere
{
    public:
        Quadrilatere();

        Quadrilatere(double taille, glm::vec2 position, int argb);
        Quadrilatere(glm::mat2 matrice, glm::vec2 position, int argb);
        Quadrilatere(double* sommets, glm::vec2 position, int argb);

        virtual ~Quadrilatere();

        void deplacer(glm::vec2 depl);
        void tournerRad(double angle);
        void tournerDeg(double angle);

        void setPosition(glm::vec2 pos);
        void setAngleRad(double angle);
        void setAngleDeg(double angle);

        void afficher(glm::mat4 projection, glm::mat4 viewPosNZoomMatrix);

        void setShaders(std::string vertexShader, std::string fragmentShader);

    protected:

    private:
        void ARGBConvertion(unsigned ARGB);
        void appliquerAngle();
        void appliquerPosition();

        double m_sommets[8];
        glm::vec2 m_position;
        Shader m_shader;
        double m_angleRad;
        float m_argb[16];
};

#endif // QUADRILATERE_H
