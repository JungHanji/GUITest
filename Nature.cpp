#include <GUIlib/GUIApp.hpp>

GUIApp app;

void appUpdate(GUIApp *gapp){
    auto &front = app.getLayer("front");
    auto &cont = front.getContainer("main-container");
    app.getLayer("front").getText("tt").changeText(to_wstring(cont.mainEmpty.pos.x) + L" " + to_wstring(cont.mainEmpty.pos.y));
    cont.pos += 0.1;
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
    front.addText(GUIlib::Text("tt", L"empty-pos", {255, 255, 255}, {1500/2-25, app.res.y-300}, "res/sans.ttf"));
    auto &spt = app.mainlayer.addSuperText(SuperText("main-sptext", "res/arial.ttf", {1500/2-25, 900/2 - 300}, 80, "center"));
    spt.getText() << sf::Text::Regular << Color::Red << "\t\t\t Safe tropics" << Color::White << "\n\tOnly 1$ can safe one tree";

    //auto &slider = cont.addSlider(Slider("slider", {100, 100}, {400, 100}, {100,100,100}, {255, 255, 255}, 30, 10));
    //slider.transperancy = 180;
    cont.addAndLinkWidget<Figure>("main-frame-1", LOCALY);

    cont.pos = {0, 100};

    while(window.isOpen()){
        app.update(window, true);
    }

    return 0;
}
