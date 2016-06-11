#include    "sceneOpengl.h"
#include    "Shader.h"
#include    "Quadrilatere.h"

void showMat4Coords(glm::mat4 matrix){
    for(int i = 0; i < 4; i++){
        std::cout << "[ " << matrix[i][0] << " ]\t" << "[ " << matrix[i][1] << " ]\t" << "[ " << matrix[i][2] << " ]\t" << "[ " << matrix[i][3] << " ]" << std::endl;
    }
    std::cout << std::endl;
}

sceneOpengl::sceneOpengl(std::string title, int largeur, int hauteur)
    : m_titreFenetre(title), m_largeur(largeur), m_hauteur(hauteur), m_fenetre(0), m_contexteOpenGL(0)
{
    //ctor

    projection = glm::ortho(0.0, static_cast<double>(m_largeur), static_cast<double> (m_hauteur), 0.0);

    viewPosNZoomMatrix = glm::mat4(
        1.0, 0.0, 0.0, 0.0,
        0.0, 1.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 1.0
    );
}

sceneOpengl::~sceneOpengl()
{
    //dtor
    SDL_GL_DeleteContext(m_contexteOpenGL);
    SDL_DestroyWindow(m_fenetre);
    SDL_Quit();
}

bool sceneOpengl::initWindow(){

    // initialisation de sdl

    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        std::cout << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << std::endl;

        SDL_Quit();
        return false;
    }

    // version d'opengl
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

    //doublebuffering
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    // création de la fenêtre
    m_fenetre = SDL_CreateWindow(m_titreFenetre.c_str() , SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_largeur, m_hauteur, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

    if(m_fenetre == 0){
        std::cout << "Une erreur c'est produite lors de la création de la fenêtre : " << SDL_GetError() << std::endl;
        SDL_Quit();

        return false;
    }

    //création de la zoneopenGL

    m_contexteOpenGL = SDL_GL_CreateContext(m_fenetre);
    if (m_contexteOpenGL == 0){
        std::cout << "Une erreur c'est produite lors de la création de la zone OpenGL : " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(m_fenetre);
        SDL_Quit();

        return false;
    }

    return true;
}

bool sceneOpengl::initGL(){

    #ifdef WIN32
        // on initialise glew

        GLenum initialistationGLEW( glewInit() );

        if(initialistationGLEW != GLEW_OK){
            std::cout << "Une erreur c'est produite lors de l'initialisation de GLEW : " << glewGetErrorString(initialistationGLEW) << std::endl;

            SDL_GL_DeleteContext(m_contexteOpenGL);
            SDL_DestroyWindow(m_fenetre);
            SDL_Quit();

            return false;

        }
    #endif // WIN32

    return true;

}

void sceneOpengl::deplaceSommets(double* sommets, int nbSommets, glm::vec2 translation)
{
    for(int i = 0; i < nbSommets*2; i+=2){
        sommets[i]+=translation[0];
        sommets[i+1]+=translation[1];
    }
}

void sceneOpengl::bouclePrincipale(){

    bool terminer(false);

    showMat4Coords(viewPosNZoomMatrix);

    viewPosNZoomMatrix = glm::translate(viewPosNZoomMatrix, glm::vec3(m_largeur/2.0, m_hauteur/2.0, 0.0));

    showMat4Coords(viewPosNZoomMatrix);

    Quadrilatere carre(glm::mat2(0.0, 0.0, 10.0, 10.0), glm::vec2(0), 0xFF00CEFF);
    carre.setShaders("Shaders/projection2D.vert", "Shaders/couleur2D.frag");
    Quadrilatere carre2(glm::mat2(0.0, 0.0, 10.0, 10.0), glm::vec2(0), 0xFF00CEFF);
    carre2.setShaders("Shaders/projection2D.vert", "Shaders/couleur2D.frag");

    //viewPosNZoomMatrix = glm::scale(viewPosNZoomMatrix, glm::vec3(100.0));
    carre2.setPosition(glm::vec2(0, 0));
    carre.setPosition(glm::vec2(50, 50));
    while(!terminer){



        SDL_PollEvent(&m_events);

        if(m_events.window.event == SDL_WINDOWEVENT_CLOSE){
            terminer = true;
        }

        // nettoyage de l'écran
        glClear(GL_COLOR_BUFFER_BIT);

        // on affiche le quad


        carre2.afficher(projection, viewPosNZoomMatrix);
        carre2.tournerDeg(1);
        carre2.deplacer(glm::vec2(1.0, 0.0));


        carre.afficher(projection, viewPosNZoomMatrix);
        carre.tournerDeg(1);
        carre.deplacer(glm::vec2(1.0, 0.0));

        //draw2DScene(vertices, 0, 12, verticesColor, shaderBasique.getProgramID());

        // actualisation de la fenêtre

        SDL_GL_SwapWindow(m_fenetre);

    }

}

void sceneOpengl::draw2DScene(double* verticestab, int fisrtVertex, int verticesNumber, short* verticesColor, GLint id_shader){


    //draw2DScene(verticestab, fisrtVertex, verticesNumber, f_verticesColor, id_shader);
}

void sceneOpengl::draw2DScene(double* verticestab, int fisrtVertex, int verticesNumber, float* verticesColor, GLint id_shader){


    // on active le shader voulu
    glUseProgram(id_shader);


    // on remplis puis on active le tableau de Vertex Attrib 0
    glVertexAttribPointer(0, 2, GL_DOUBLE, GL_FALSE, 0, verticestab);


    glEnableVertexAttribArray(0);

    // on remplis puis on active le tableau de Vertex Attrib 0

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, verticesColor);


    glEnableVertexAttribArray(1);

    //on envoie les matrices aux shaders
    glUniformMatrix4fv( glGetUniformLocation(   id_shader,  "projection"        ),  1, GL_FALSE, glm::value_ptr(   projection )   );
    glUniformMatrix4fv( glGetUniformLocation(   id_shader,  "viewPosNZoomMatrix"),  1, GL_FALSE, glm::value_ptr(   viewPosNZoomMatrix
                                                                                                                              )   );


    glDrawArrays(GL_QUADS, fisrtVertex, verticesNumber);


    // on désactive le tableau Vertex Attrib puisque l'on n'en a plus besoin
    glDisableVertexAttribArray(1);


    // on désactive le tableau Vertex Attrib puisque l'on n'en a plus besoin
    glDisableVertexAttribArray(0);



    // on désactive le sharder
    glUseProgram(0);
}
