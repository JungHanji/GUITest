#include <GUIlib/GUIApp.hpp>

GUIApp app;

void appUpdate(GUIApp *gapp){
}

int main(int argc, char *argv[]) {
    system("cls");

    RenderWindow window(VideoMode(1500, 900), "Window");
    window.setFramerateLimit(60);

    app.setUpdateFunction(&appUpdate);
    app.bgColor = {200, 200, 200};
    app.res = {1500, 900};

    app.mainlayer.addImage(GUIlib::Image("main-image", "res/nature.jpg", {0, 0}, app.res, {100, 100, 100}));
    app.addLayer("front");
    app.getLayer("front").addFigure(Figure("main-frame-1", "circled-rectangle", app.res / 2 - vec2(300, 200), {300 * 2, 290 * 2}, {200, 200, 200}));
    app.getLayer("front").getFigure("main-frame-1").transparency = 100;
    app.mainlayer.addText(GUIlib::Text("main-text", L"Nike", {255, 255, 255}, {1500/2, 900/2 - 210}, "res/arial.ttf", 90));

    while(window.isOpen()){
        app.update(window, true);
    }

    return 0;
}