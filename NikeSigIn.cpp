#include <GUIlib/GUIApp.hpp>

GUIApp app;

int tickStart = 0;
bool anim = false;

char passwordHandler(InputField *f, char ch){
    return '*';
}

void sigin(Button *b){
    app.getInputField("password-input").setText(L"Complite");
    app.getInputField("login-input").setText(L"Complite");
    tickStart = app.tick;
    anim = true;
}

void appUpdate(GUIApp *gapp){
    if(anim){
        app.getFigure("alert").pos = animationFastToSlow({1500/2-150, -100}, {1500/2-150, 20}, tickStart, app.tick);
        app.getText("alert-text").pos = app.getFigure("alert").pos + vec2(150, 50);
        if(app.getFigure("alert").pos.y >= 20) {anim = false;}
    } else if(tickStart != 0){
        app.getFigure("alert").transparency -= 3;
        
    }

    if(app.getFigure("alert").transparency <= 0){
        tickStart = 0;
        app.getFigure("alert").transparency = 255;
        app.getFigure("alert").pos = {-100, -100};
        app.getText("alert-text").pos = {-100, -100};
    }
}

int main(int argc, char *argv[]) {
    system("cls");
    
    RenderWindow window(VideoMode(1500, 900), "Window");
    window.setFramerateLimit(60);

    app.setUpdateFunction(&appUpdate);
    app.bgColor = {50, 50, 50};

    app.addFigure(Figure("main", "circled-rectangle", {1500/2-200, 900/2 - 250}, {200 * 2, 250 * 2}, {0, 0, 0}));
    app.addImage(GUIlib::Image("main-image", "res/keds2.jpg", {1500/2-210, 900/2 - 240}, {200 * 2 + 20, 250*2-20}, {100, 100, 100}));
    app.getFigure("main").setSmoothnes(10);

    app.addText(GUIlib::Text("main-text", L"Nike", {255, 255, 255}, {1500/2, 900/2 - 210}, "res/arial.ttf", 90));

    app.addInputField(InputField("login-input", L"Login", GUIlib::Text("imp", L" ", {0, 0, 0}, {1500/2-90, 900/2}, "res/sans.ttf"), {200, 50}, {19, 1}, {5, 20}, {100, 100, 100}));
    app.getInputField("login-input").setFigure(Figure("imp", "circled-rectangle", {0, 0}, {0, 0}, {230, 230, 230}));
    app.getInputField("login-input").setTextType(1);
    
    app.addInputField(InputField("password-input", L"Password", GUIlib::Text("imp", L" ", {0, 0, 0}, {1500/2-90, 900/2 + 80}, "res/sans.ttf"), {200, 50}, {19, 1}, {5, 20}, {100, 100, 100}));
    app.getInputField("password-input").setFigure(Figure("imp", "circled-rectangle", {0, 0}, {0, 0}, {230, 230, 230}));
    app.getInputField("password-input").setTextType(1);
    app.getInputField("password-input").setCharHandler(passwordHandler);

    app.addButton(Button("buy-button", {200, 50}, {1500/2-90, 900/2 + 170}, {210, 210, 210}, {255, 255, 255}, {180, 180, 180}, {180, 180, 180}));
    app.getButton("buy-button").setFigure(Figure("imp", "circled-rectangle", {0, 0}, {0, 0}, {0, 0, 0}));
    app.getButton("buy-button").addText("Sign in", "res/sans.ttf", {0, 0, 0});
    app.getButton("buy-button").setCallback(sigin, "onClick");

    app.addFigure(Figure("alert", "circled-rectangle", {1500/2-150, -100}, {150 * 2, 100}, {200, 200, 200}));
    app.addText(GUIlib::Text("alert-text", L"Complited!", {0, 0, 0}, {-100, -100}, "res/impact.ttf"));

    while(window.isOpen()){
        app.update(window, true);
    }

    return 0;
}
/*
app.addButton({"1", {200.f, 150.f}, {10.f, 160.f}, {255.f, 0.f, 255.f}, {255, 255, 255}, {100, 100, 100}, {0, 0, 255}});
app.addButton({"2", {200.f, 150.f}, {220.f, 10.f}, {255.f, 0.f, 255.f}, {255, 255, 255}, {100, 100, 100}, {0, 0, 255}});
app.addButton({"3", {300.f, 150.f}, {10.f, 10.f}, "Hello World", "sans.ttf", {255, 255, 255}, {255, 255, 255}, {100, 100, 100}, {255, 0, 0}, {0, 255, 0}, 20});

app.getButton("1").setImage("res/1.jpg");

for(int i = 0; i < app.buttons.size(); i++) app.buttons[i].setCallback(click, "onClick");

    app.addFigure(Figure("fig1", "rectangle", {50, 50}, {1400, 800}, {100, 100, 100}));
app.addImage(GUIlib::Image("img1", "res/1.jpg", {50, 50}, {300, 300}, {10, 10, 10}));
app.addSlider({"slider", {50, 200}, {200, 200}, {255, 255, 255}, {255, 0, 0}, 10});
app.addSlider({"slider2", {200, 50}, {200, 200}, {255, 255, 255}, {255, 0, 0}, 10});
app.addSlider({"slider3", {50, 300}, {200, 300}, {255, 255, 255}, {255, 0, 0}, 30, 5});
app.addSlider({"slider4", {50, 350}, {50, 450}, {255, 255, 255}, {255, 0, 0}, 30, 5});
app.getSlider("slider").setFunc(updateText);
app.getSlider("slider2").setFunc(updateText);
app.getSlider("slider3").setFunc(updateText2);

app.addText({"text", "slider1 val: un", {255, 255, 255}, {100, 100, 100}, {200, 70}, {300, 50}, "res/sans.ttf", 20});
app.addText({"text2", "slider2 val: un", {255, 255, 255}, {100, 100, 100}, {200, 200}, {300, 50}, "res/sans.ttf", 20});
app.addText({"text3", "slider3", {255, 255, 255}, {100, 100, 100}, {200, 300}, {300, 50}, "res/sans.ttf", 20});

app.addInputField(InputField("input1", L"Start...", GUIlib::Text("inc", L"", {255, 255, 255}, {100, 0, 100}, {300, 200}, {105, 105}, "res/sans.ttf"), {10, 5}, {10, 10}, true));
app.getInputField("input1").setTextType(1);
*/