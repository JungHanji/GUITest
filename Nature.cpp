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
    auto &front = app.addLayer("front");
    auto &cont = front.addContainer(Container("main-container"));
    auto &frame = cont.addFigure(Figure("main-frame-1", FigureType::CIRCLED_RECTANGLE, app.res / 2 - vec2(450, 150), {450 * 2, 290 * 2}, {200, 200, 200}));
    frame.transparency = 180;
    frame.setGradientRect({{255, 255, 0}, {0, 0, 255}, {255, 0, 0}});
    frame.setSmoothnes(30);

    auto &spt = app.mainlayer.addSuperText(SuperText("main-sptext", "res/arial.ttf", {1500/2-25, 900/2 - 300}, 80, "center"));
    spt.getText() << sf::Text::Regular << Color::Red << "\t\t\t Safe tropics" << Color::White << "\n\tOnly 1$ can safe one tree";

    
    cont.addAndLinkWidget<Figure>("main-frame-1");
    cont.pos = {0, 0};

    while(window.isOpen()){
        app.update(window, true);
    }

    return 0;
}
