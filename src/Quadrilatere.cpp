#include "Quadrilatere.h"

Quadrilatere::Quadrilatere()
{
    glm::mat2 matrice( -0.5, -0.5, 0.5, 0.5);

    this->m_sommets[0] = matrice[0][0];
    this->m_sommets[1] = matrice[0][1];
    this->m_sommets[2] = matrice[0][0];
    this->m_sommets[3] = matrice[1][1];
    this->m_sommets[4] = matrice[1][0];
    this->m_sommets[5] = matrice[1][1];
    this->m_sommets[6] = matrice[1][0];
    this->m_sommets[7] = matrice[0][1];

    for(int i = 0; i < 4; i++){
        std::cout << "[ " << m_sommets[i*2] << " ]\t" << "[ " << m_sommets[(i*2)+1] << " ]" << std::endl;
    }
    std::cout << std::endl;

    this->m_position = glm::vec2(0);
    ARGBConvertion(0xFFFFFFFF);

}

Quadrilatere::Quadrilatere(double taille, glm::vec2 position = glm::vec2(0), int argb = 0xFFFFFFFF)
{
    glm::mat2 matrice( -0.5 * taille, -0.5 * taille, 0.5 * taille, 0.5 * taille );

    this->m_sommets[0] = matrice[0][0];
    this->m_sommets[1] = matrice[0][1];
    this->m_sommets[2] = matrice[0][0];
    this->m_sommets[3] = matrice[1][1];
    this->m_sommets[4] = matrice[1][0];
    this->m_sommets[5] = matrice[1][1];
    this->m_sommets[6] = matrice[1][0];
    this->m_sommets[7] = matrice[0][1];

    this->m_position = position;
    ARGBConvertion(argb);

    for(int i = 0; i < 4; i++){
        std::cout << "[ " << m_sommets[i*2] << " ]\t" << "[ " << m_sommets[(i*2)+1] << " ]" << std::endl;
    }
    std::cout << std::endl;
    std::cout << "pos : " << m_position.x << ", " << m_position.y << std::endl;
    std::cout << "argb : " << m_argb[0] << ", " << m_argb[1] << ", " << m_argb[2] << ", " << m_argb[3] << " : " << argb << std::endl;
    std::cout << std::endl;
}

Quadrilatere::Quadrilatere(glm::mat2 matrice, glm::vec2 position = glm::vec2(0), int argb = 0xFFFFFFFF)
{
    this->m_sommets[0] = matrice[0][0];
    this->m_sommets[1] = matrice[0][1];
    this->m_sommets[2] = matrice[0][0];
    this->m_sommets[3] = matrice[1][1];
    this->m_sommets[4] = matrice[1][0];
    this->m_sommets[5] = matrice[1][1];
    this->m_sommets[6] = matrice[1][0];
    this->m_sommets[7] = matrice[0][1];

    this->m_position = position;
    ARGBConvertion(argb);

    for(int i = 0; i < 4; i++){
        std::cout << "[ " << m_sommets[i*2] << " ]\t" << "[ " << m_sommets[(i*2)+1] << " ]" << std::endl;
    }
    std::cout << std::endl;
    std::cout << "pos : " << m_position.x << ", " << m_position.y << std::endl;
    std::cout << "argb : " << m_argb[0] << ", " << m_argb[1] << ", " << m_argb[2] << ", " << m_argb[3] << " : " << argb << std::endl;
    std::cout << std::endl;
}

Quadrilatere::Quadrilatere(double* sommets, glm::vec2 position = glm::vec2(0), int argb = 0xFFFFFFFF)
{
    for(int i = 0; i < 8; i++){
        this->m_sommets[i] = sommets[i];
    }
    this->m_position = position;
    ARGBConvertion(argb);

    for(int i = 0; i < 4; i++){
        std::cout << "[ " << m_sommets[i*2] << " ]\t" << "[ " << m_sommets[(i*2)+1] << " ]" << std::endl;
    }
    std::cout << "pos : " << m_position.x << ", " << m_position.y << std::endl;
    std::cout << "argb : " << m_argb[0] << ", " << m_argb[1] << ", " << m_argb[2] << ", " << m_argb[3] << " : " << argb << std::endl;
    std::cout << std::endl;
}

void Quadrilatere::deplacer(glm::vec2 depl)
{
    m_position += depl;
}

void Quadrilatere::tournerRad(double angle)
{
    m_angleRad += angle;
    double junk;
    m_angleRad = modf(angle / M_2PI, &junk) * M_2PI ;
}

void Quadrilatere::tournerDeg(double angle)
{
    m_angleRad += (angle * (static_cast<double>(M_PI) / 180.0 ));
    double junk;
    m_angleRad = modf(angle / M_2PI, &junk) * M_2PI ;
}

void Quadrilatere::setPosition(glm::vec2 pos)
{
    m_position = pos;
}

void Quadrilatere::setAngleRad(double angle)
{
    double junk;
    m_angleRad = modf(angle / M_2PI, &junk) * M_2PI ;
}

void Quadrilatere::setAngleDeg(double angle)
{
    double junk;
    m_angleRad = modf(angle / M_2PI, &junk) * M_2PI ;
}

void Quadrilatere::setShaders(std::string vertexShader, std::string fragmentShader)
{
    m_shader = Shader(vertexShader, fragmentShader);
    m_shader.charger();
}

void Quadrilatere::ARGBConvertion(unsigned ARGB)
{
    m_argb[0] = m_argb[4] = m_argb[8] = m_argb[12] = ((ARGB >> 16) & 0x000000FF) / 255.0;
    m_argb[1] = m_argb[5] = m_argb[9] = m_argb[13] = ((ARGB >> 8) & 0x000000FF) / 255.0;
    m_argb[2] = m_argb[6] = m_argb[10] = m_argb[14] = (ARGB & 0x000000FF) / 255.0;
    m_argb[3] = m_argb[7] = m_argb[11] = m_argb[15] = ((ARGB >> 24) & 0x000000FF) / 255.0 ;
}


void Quadrilatere::afficher(glm::mat4 projection, glm::mat4 viewPosNZoomMatrix)
{
// on active le shader voulu
    glUseProgram(m_shader.getProgramID());



    std::cout << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl
         << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl;
    /*
    for(int i = 0; i < 4; i++){
        std::cout << "[ " << m_sommets[i*2] << " ]\t" << "[ " << m_sommets[(i*2)+1] << " ]" << std::endl;
    }
    */
    std::cout << "pos : " << m_position.x << ", " << m_position.y << std::endl
        << "argb : " << m_argb[0] << ", " << m_argb[1] << ", " << m_argb[2] << ", " << m_argb[3] << std::endl
        << "M_PI        : " << M_PI << std::endl
        << "100PI       : 3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679" << std::endl
        << "W_PI        : 3.1415926535897932384626433832795" << std::endl
        << "M_2PI       : " << M_2PI << std::endl
        << "W_PI  * 2   : 6.283185307179586476925286766559" << std::endl
        << "100PI * 2   : 6.2831853071795864769252867665590057683943387987502116419498891846156328125724179972660696506842341358" << std::endl
        << "M_PI  * 2   : " << M_PI * 2.0 << std::endl
        << "100PI / 180 : 3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679" << std::endl
        << "M_PI  / 180 : " << M_PI / 180.0 << std::endl
        << "W_PI  / 180 : 0.01745329251994329576923690768489" << std::endl
        << "M_PI_180    : " << M_PI_180 << std::endl
        << std::endl;

    SDL_Delay(0.16666666666666666666);

    // on remplis puis on active le tableau de Vertex Attrib 0

    glVertexAttribPointer(0, 2, GL_DOUBLE, GL_FALSE, 0, m_sommets);


    glEnableVertexAttribArray(0);

    // couleur des points

    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, m_argb);


    glEnableVertexAttribArray(1);

    //on envoie les matrices aux shaders
    glUniformMatrix4fv(
        glGetUniformLocation(
            m_shader.getProgramID(),
            "projection"
        ),
        1,
        GL_FALSE,
        glm::value_ptr(
            projection
        )
    );
    glUniformMatrix4fv(
        glGetUniformLocation(
            m_shader.getProgramID(),
            "viewPosNZoomMatrix"
        ),
        1,
        GL_FALSE,
        glm::value_ptr(
            viewPosNZoomMatrix
        )
    );


    glDrawArrays(GL_QUADS, 0, 4);

    // on désactive le tableau Vertex Attrib puisque l'on n'en a plus besoin
    glDisableVertexAttribArray(1);


    // on désactive le tableau Vertex Attrib puisque l'on n'en a plus besoin
    glDisableVertexAttribArray(0);

    // on désactive le sharder
    glUseProgram(0);
}

Quadrilatere::~Quadrilatere()
{
    //dtor
}
