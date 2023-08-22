#include <GUIlib/GUIApp.hpp>

GUIApp app;

char passwordHandler(InputField *f, char ch){
    return '*';
}

void sigin(Button *b){
    app.mainlayer.getInputField("password-input").setText(L"Complite");
    app.mainlayer.getInputField("login-input").setText(L"Complite");
    app.newAnimation("anim", FAST_TO_SLOW, {1500/2-150, -100}, {1500/2-150, 20}, app.tick);
}

void appUpdate(GUIApp *gapp){
    if(app.animator.isAnimationAlive("anim"))
        app.mainlayer.getFigure("alert").pos = app.animator.getPosition("anim");
}

int main(int argc, char *argv[]) {
    RenderWindow window(VideoMode(1500, 900), "Window");
    window.setFramerateLimit(60);

    app.setUpdateFunction(&appUpdate);
    app.bgColor = {50, 50, 50};

    auto &mainfigure = app.mainlayer.addFigure(Figure("main", FigureType::CIRCLED_RECTANGLE, {1500/2-200, 900/2 - 250}, {200 * 2, 250 * 2}, {100, 100, 100}));
    mainfigure.setSmoothnes(10);
    mainfigure.setImage(GUIlib::Image("imp", "res/keds2.jpg", {200 * 2, 250 * 2}, {0, 0, 0}));

    app.mainlayer.addText(GUIlib::Text("main-text", L"Nike", {255, 255, 255}, {1500/2, 900/2 - 210}, "res/arial.ttf", 90));

    auto &logininput = app.mainlayer.addInputField(InputField("login-input", L"Login", {1500/2-90, 900/2}, GUIlib::Text("imp", L" ", {0, 0, 0}, {0, 0}, "res/sans.ttf"), {200, 50}, {13, 1}, {5, 20}, {100, 100, 100}));
    logininput.setFigure(Figure("imp", FigureType::CIRCLED_RECTANGLE, {0, 0}, {0, 0}, {230, 230, 230}));
    logininput.setTextType(1);

    auto &password = app.mainlayer.addInputField(InputField("password-input", L"Password", {1500/2-90, 900/2 + 80}, GUIlib::Text("imp", L" ", {0, 0, 0}, {0, 0}, "res/sans.ttf"), {200, 50}, {19, 1}, {5, 20}, {100, 100, 100}));
    password.setFigure(Figure("imp", FigureType::CIRCLED_RECTANGLE, {0, 0}, {0, 0}, {230, 230, 230}));
    password.setTextType(1);
    password.setCharHandler(passwordHandler);

    auto &buybutton = app.mainlayer.addButton(Button("buy-button", {200, 50}, {1500/2-90, 900/2 + 170}, {210, 210, 210}, {255, 255, 255}, {180, 180, 180}, {180, 180, 180}));
    buybutton.setFigure(Figure("imp", FigureType::CIRCLED_RECTANGLE, {0, 0}, {0, 0}, {0, 0, 0}));
    buybutton.addText(L"Sign in", "res/sans.ttf", {0, 0, 0});
    buybutton.setCallback(sigin, "onClick");

    app.mainlayer.addFigure(Figure("alert", FigureType::CIRCLED_RECTANGLE, {1500/2-150, -100}, {150 * 2, 100}, {200, 200, 200}));
    app.mainlayer.addText(GUIlib::Text("alert-text", L"Complited!", {0, 0, 0}, {-100, -100}, "res/impact.ttf"));

    app.mainlayer.createDoubleLink<Figure, GUIlib::Text>("alert", "alert-text", {150, 50});

    while(window.isOpen()){
        app.update(window, true);
    }

    return 0;
}

//app.mainlayer.addCheckBox(CheckBox("check-box", {500/2-90, 900/2 + 150}, {20, 20}, {0, 0, 0}, {255, 0, 0}));