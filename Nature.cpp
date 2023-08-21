#include <GUIlib/GUIApp.hpp>

GUIApp app;

void appUpdate(GUIApp *gapp){
}

int main(int argc, char *argv[]) {
    RenderWindow window(VideoMode(1500, 900), "Window");
    window.setFramerateLimit(60);

    app.setUpdateFunction(&appUpdate);
    app.bgColor = {200, 200, 200};
    app.res = {1500, 900};

    app.mainlayer.addImage(GUIlib::Image("main-image", "res/nature.jpg", {0, 0}, app.res, {100, 100, 100}));
    app.addLayer("front");
    app.getLayer("front").addFigure(Figure("main-frame-1", FigureType::CIRCLED_RECTANGLE, app.res / 2 - vec2(450, 150), {450 * 2, 290 * 2}, {200, 200, 200}));
    app.getLayer("front").getFigure("main-frame-1").transparency = 180;
    app.getLayer("front").getFigure("main-frame-1").setGradientRect({{255, 255, 0}, {0, 0, 255}, {255, 0, 0}});
    app.getLayer("front").getFigure("main-frame-1").setSmoothnes(30);
    app.mainlayer.addText(GUIlib::Text("main-text", L"\t\t\t Safe tropics\n\tOnly 1$ can safe one tree", {255, 255, 255}, {1500/2-25, 900/2 - 300}, "res/arial.ttf", 80));

    while(window.isOpen()){
        app.update(window, true);
    }

    return 0;
}
