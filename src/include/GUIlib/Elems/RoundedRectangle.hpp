#include <GUIlib/HIDhandler.hpp>
#include <AdtClasses/AdtClasses.hpp>
#include <functional>

const float PREC = M_PI_2 / 15;

class RoundedRectangle : public sf::ConvexShape{       
    public:
    RoundedRectangle(sf::Rect<float> rt, float rs) : rect(rt), radius(rs){
        init();
        setPosition(rt.left , rt.top);
        sf::Shape::update();
    }

    RoundedRectangle(){}
 
    virtual size_t getPointCount() const { return m.size();}
    virtual sf::Vector2f getPoint(size_t i) const { return m[i];}
 
    private:
    sf::FloatRect rect;
    float radius;
    sf::Vector2f position{0.f, 0.f};
 
    std::vector<sf::Vector2f> m;
    unsigned PointCount;
 
    void init(){
        std::vector<sf::Vector2f> sin_4;
        for(  float f = 0.0; f < M_PI_2; f += PREC) sin_4.push_back({sinf(f) * radius, cosf(f)*radius});
 
        std::vector<sf::Vector2f> sin_4_reverse(sin_4.rbegin(), sin_4.rend());
 
        const float WIDE2 = rect.width - radius;
        const float HEIGHT2 = rect.height - radius;
        
        int half = sin_4.size() / 2, i = 0;
        for(const auto& e : sin_4_reverse) {m.push_back({WIDE2   + e.x, HEIGHT2 + e.y});i++;}
        for(const auto& e : sin_4) {m.push_back({radius  - e.x, HEIGHT2 + e.y});i++;}
        for(const auto& e : sin_4_reverse) {m.push_back({ radius - e.x, radius - e.y});i++;}
        for(const auto& e : sin_4) {m.push_back({ WIDE2  + e.x, radius - e.y});i++;}
    }
};