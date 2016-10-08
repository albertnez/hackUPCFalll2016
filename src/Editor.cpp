#include "Editor.hpp"
#include <cmath>

Editor::Editor(sf::RenderWindow* pwindow){
    window = pwindow;
    mousePressed = false;
}
    
void Editor::run(){
    
    while(window->isOpen()){

        sf::Event event;
        while(window->pollEvent(event)){
            switch (event.type){
                case sf::Event::Closed:
                    window->close();
                    exit(0);
                case  sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::Escape) {
                        return;
                    }
                    if (event.key.code == sf::Keyboard::U) {
                        if(!mousePressed){
                            if(circles.size() > 0){
                                circles.pop_back();
                                littleCircle.pop_back();
                            }
                        }
                    }
                    if (event.key.code == sf::Keyboard::S) {
                        std::ofstream aux("filename.txt");
                        if(aux.is_open()){
                            for(size_t i = 0; i < circles.size(); ++i){
                                
                                auto c = circles[i];
                                auto lc = littleCircle[i];
                                aux << c.getPosition().x << " " << c.getPosition().y << " " << lc.getPosition().x - c.getPosition().x << " " << lc.getPosition().y - c.getPosition().y << '\n';
                                littleCircle[i];
                            }
                            aux.close();
                        }
                    }
                default:
                    break;
            }
        }   

        float mouse_x, mouse_y;
        mouse_x = sf::Mouse::getPosition(*window).x; 
        mouse_y = sf::Mouse::getPosition(*window).y;
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            if(!mousePressed){ //82 de mida 
                mousePressed = true;
                sf::CircleShape auxCircle(40, 79);
                auxCircle.setOrigin(40,40);
                auxCircle.setFillColor(sf::Color(0,0,0));
                auxCircle.setPosition(mouse_x, mouse_y);
                circles.push_back(auxCircle);
            }
        }
        else { 
            if(mousePressed){
                sf::CircleShape auxCircle(2, 20);
                auxCircle.setOrigin(2,2);
                auxCircle.setFillColor(sf::Color(255,0,0));
                
                auto p1 = sf::Vector2f(circles[circles.size()-1].getPosition());
                auto p2 = sf::Vector2f(mouse_x, mouse_y);
                auto vector = sf::Vector2f(p2.x-p1.x, p2.y-p1.y);
                float module = std::sqrt(vector.x*vector.x + vector.y*vector.y);
                sf::Vector2f unitVector(vector.x/module, vector.y/module);
                sf::Vector2f finalPoint(unitVector.x*82, unitVector.y*82);
                auxCircle.setPosition(p1.x+finalPoint.x, p1.y+finalPoint.y);
                littleCircle.push_back(auxCircle);
            }
            mousePressed = false;
        }
        
        window->clear(sf::Color(255,251,239));

        for(size_t i = 0; i < circles.size(); ++i){
            window->draw(circles[i]);
        }
        for(size_t i = 0; i < littleCircle.size(); ++i){
            window->draw(littleCircle[i]);
            
            sf::Vertex line[] =
                {                    
                      sf::Vertex(circles[i].getPosition()),
                      sf::Vertex(littleCircle[i].getPosition())
                };

            window->draw(line, 2, sf::Lines);
        }
        window->display();
    }
    
}