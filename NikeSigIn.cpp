#include <GUIlib/GUIApp.hpp>

GUIApp app;

char passwordHandler(InputField *f, char ch){
    return '*';
}

void sigin(Button *b){
    app.mainlayer.getInputField("password-input").setText(L"Complite");
    app.mainlayer.getInputField("login-input").setText(L"Complite");
    app.newAnimation("anim", AnimationType::FAST_TO_SLOW, {1500/2-150, -100}, {1500/2-150, 20}, app.tick);
}

void appUpdate(GUIApp *gapp){
    if(app.animator.isAnimationAlive("anim")){
        app.mainlayer.getFigure("alert").pos = app.animator.getPosition("anim");
        //app.mainlayer.getText("alert-text").pos = app.mainlayer.getFigure("alert").pos + vec2(150, 50);
    }
}

int main(int argc, char *argv[]) {
    RenderWindow window(VideoMode(1500, 900), "Window");
    window.setFramerateLimit(60);

    app.setUpdateFunction(&appUpdate);
    app.bgColor = {50, 50, 50};

    app.mainlayer.addFigure(Figure("main", FigureType::CIRCLED_RECTANGLE, {1500/2-200, 900/2 - 250}, {200 * 2, 250 * 2}, {0, 0, 0}));
    app.mainlayer.addImage(GUIlib::Image("main-image", "res/keds2.jpg", {1500/2-210, 900/2 - 240}, {200 * 2 + 20, 250*2-20}, {100, 100, 100}));
    app.mainlayer.getFigure("main").setSmoothnes(10);

    app.mainlayer.addText(GUIlib::Text("main-text", L"Nike", {255, 255, 255}, {1500/2, 900/2 - 210}, "res/arial.ttf", 90));

    app.mainlayer.addInputField(InputField("login-input", L"Login", GUIlib::Text("imp", L" ", {0, 0, 0}, {1500/2-90, 900/2}, "res/sans.ttf"), {200, 50}, {13, 1}, {5, 20}, {100, 100, 100}));
    app.mainlayer.getInputField("login-input").setFigure(Figure("imp", FigureType::CIRCLED_RECTANGLE, {0, 0}, {0, 0}, {230, 230, 230}));
    app.mainlayer.getInputField("login-input").setTextType(1);
    
    app.mainlayer.addInputField(InputField("password-input", L"Password", GUIlib::Text("imp", L" ", {0, 0, 0}, {1500/2-90, 900/2 + 80}, "res/sans.ttf"), {200, 50}, {19, 1}, {5, 20}, {100, 100, 100}));
    app.mainlayer.getInputField("password-input").setFigure(Figure("imp", FigureType::CIRCLED_RECTANGLE, {0, 0}, {0, 0}, {230, 230, 230}));
    app.mainlayer.getInputField("password-input").setTextType(1);
    app.mainlayer.getInputField("password-input").setCharHandler(passwordHandler);

    app.mainlayer.addButton(Button("buy-button", {200, 50}, {1500/2-90, 900/2 + 170}, {210, 210, 210}, {255, 255, 255}, {180, 180, 180}, {180, 180, 180}));
    app.mainlayer.getButton("buy-button").setFigure(Figure("imp", FigureType::CIRCLED_RECTANGLE, {0, 0}, {0, 0}, {0, 0, 0}));
    app.mainlayer.getButton("buy-button").addText("Sign in", "res/sans.ttf", {0, 0, 0});
    app.mainlayer.getButton("buy-button").setCallback(sigin, "onClick");

    app.mainlayer.addFigure(Figure("alert", FigureType::CIRCLED_RECTANGLE, {1500/2-150, -100}, {150 * 2, 100}, {200, 200, 200}));
    app.mainlayer.addText(GUIlib::Text("alert-text", L"Complited!", {0, 0, 0}, {-100, -100}, "res/impact.ttf"));

    app.mainlayer.addCheckBox(CheckBox("check-box", {500/2-90, 900/2 + 150}, {20, 20}, {0, 0, 0}, {255, 0, 0}));

    app.mainlayer.addLink<Figure>("anim-empty", "alert", {0, 0}, true);
    app.mainlayer.addLink<GUIlib::Text>("anim-empty", "alert-text", {150, 50});

    while(window.isOpen()){
        app.update(window, true);
    }

    return 0;
}