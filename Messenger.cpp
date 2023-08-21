#include <GUIlib/GUIApp.hpp>

GUIApp app;

char passwordHandler(InputField *f, char ch){
    return '*';
}

void appUpdate(GUIApp *gapp){
}

int main(int argc, char *argv[]) {
    system("cls");

    app.res = {1100, 800};
    RenderWindow window(VideoMode(app.res.x, app.res.y), "Window");
    window.setFramerateLimit(60);

    app.setUpdateFunction(&appUpdate);
    app.bgColor = {198, 198, 198};
    
    vec2 center = app.res / 2.0f;

    app.mainlayer.addFigure(Figure("main-title", FigureType::CIRCLED_RECTANGLE, {0, 0}, app.res, {200, 200, 200}));
    app.mainlayer.getFigure("main-title").setGradientRect({{35, 44, 255}, {22, 146, 173}, {255, 0, 255}});
    app.mainlayer.getFigure("main-title").transparency = 170;
    app.mainlayer.getFigure("main-title").setSmoothnes(44);

    app.addLayer("title-front");
    app.getLayer("title-front").addSuperText(SuperText("title-front-slogo", "res/arial.ttf", {center.x, center.y - app.res.y/3}, 50, "center"));
    app.getLayer("title-front").getSuperText("title-front-slogo").getText() << sf::Text::Bold << Color::White << "YourOne" << sf::Text::Regular << " messenger\n\t " << sf::Text::Italic << "simple & fast";

    app.getLayer("title-front").addInputField(InputField("title-front-login", L"Log in", {center.x-app.res.x/3/2, center.y-50}, GUIlib::Text("imp", L"", {200, 200, 200}, {0, 0}, "res/sans.ttf"), {app.res.x/3, 50}, {50, 1}, {5, 20}, {200, 200, 200}));
    app.getLayer("title-front").getInputField("title-front-login").setFigure(Figure("imp", FigureType::CIRCLED_RECTANGLE, {0, 0}, {0, 0}, {50, 50, 50}));
    app.getLayer("title-front").getInputField("title-front-login").figure.transparency = 100;
    app.getLayer("title-front").getInputField("title-front-login").figure.setSmoothnes(20);
    app.getLayer("title-front").getInputField("title-front-login").setTextType(1);
    app.getLayer("title-front").getInputField("title-front-login").ttext.transparency = 150;

    app.getLayer("title-front").addInputField(InputField("title-front-password", L"Password", {center.x-app.res.x/3/2, center.y+20}, GUIlib::Text("imp", L"", {200, 200, 200}, {0, 0}, "res/sans.ttf"), {app.res.x/3, 50}, {50, 1}, {5, 20}, {200, 200, 200}));
    app.getLayer("title-front").getInputField("title-front-password").setFigure(Figure("imp", FigureType::CIRCLED_RECTANGLE, {0, 0}, {0, 0}, {50, 50, 50}));
    app.getLayer("title-front").getInputField("title-front-password").figure.transparency = 100;
    app.getLayer("title-front").getInputField("title-front-password").figure.setSmoothnes(20);
    app.getLayer("title-front").getInputField("title-front-password").setTextType(1);
    app.getLayer("title-front").getInputField("title-front-password").ttext.transparency = 150;
    app.getLayer("title-front").getInputField("title-front-password").setCharHandler(passwordHandler);

    app.getLayer("title-front").addButton(Button("title-front-login-button", {(app.res.x/3 - 20), 50}, {center.x-(app.res.x/3 - 20)/2, app.res.y - app.res.y/3}, {70, 70, 70}));
    app.getLayer("title-front").getButton("title-front-login-button").addText(L"Sign In", "C:\\Windows\\Fonts\\Ebrima.ttf", {255, 255, 255}, 25);
    app.getLayer("title-front").getButton("title-front-login-button").setFigure(Figure("imp", FigureType::CIRCLED_RECTANGLE, {0, 0}, {0, 0}, {0, 0, 0}));
    app.getLayer("title-front").getButton("title-front-login-button").figure.setSmoothnes(15);

    while(window.isOpen()){
        app.update(window, true);
    }

    return 0;
}