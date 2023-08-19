#include <GUIlib/GUIApp.hpp>

GUIApp app;

void appUpdate(GUIApp *gapp){
    ;
}

int main(int argc, char *argv[]) {
    RenderWindow window(VideoMode(1500, 900), "Mac shop");
    window.setFramerateLimit(60);

    app.setUpdateFunction(&appUpdate);
    app.bgColor = {200, 200, 200};
    app.res = {1500, 900};

    
    while(window.isOpen()){
        app.update(window, true);
    }

    return 0;
}