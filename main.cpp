#include "sceneOpengl.h"

int main(int argc, char** argv){
    std::cout.precision(50);

    std::cout << "ligne 5 : main" << std::endl;
    sceneOpengl* scene = new sceneOpengl("Learning Simulator", 1024, 768);


    std::cout << "ligne 9 : main" << std::endl;
    if(scene->initWindow() == false) return -1;


    std::cout << "ligne 13 : main" << std::endl;
    if(scene->initGL() == false) return -1;


    std::cout << "ligne 17 : main" << std::endl;
    scene->bouclePrincipale();


    std::cout << "ligne 21 : main" << std::endl;
    delete scene;

    std::cout << "Le programme est terminé. Appuyez sur une touche pour quiter." << std::endl ;
    getchar();
    return 0;

}
