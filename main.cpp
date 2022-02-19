#include <SFML/Graphics.hpp>
#include <iostream>  
#include <stdio.h>
#include <stdlib.h>
using namespace std;


enum direction {
  up,
  down,
  lleft,
  rright
};

class Point {
public:
  Point() {
    x = 0;
    y = 0;
  }
  Point(int x, int y) :x(x), y(y) {
  }
  int x;
  int y;
};

class Trace {
public:
  Trace(Point a) : p(a) {}
  void Move(direction d, Point a) {
    p = a;
    switch (d) {
    case up: p.x -= 30; dir = d; break;
    case down: p.x += 50; p.y += 20; dir = d; break;
    case lleft: p.y += 50; dir = d; break;
    case rright: p.x += 20; p.y -= 30; dir = d; break;
    }
  }
  void Draw(sf::RenderWindow& window, bool status) {
    if (status) {
      sf::CircleShape trace(40.f, 3);
      trace.setFillColor(sf::Color(255, 174, 66));
      switch (dir) {
      case up: trace.rotate(0.f); break;
      case down: trace.rotate(180.f); break;
      case lleft: trace.rotate(270.f); break;
      case rright: trace.rotate(90.f); break;
      }
      trace.setPosition((float)p.x, (float)p.y);
      window.draw(trace);
    }
  }
private:
  direction dir;
  Point p;
};

class Pointer {
public:
  Pointer(Point a, int s) : p(a), speed(s) {}
  void Move(direction d, Trace& Tr) {
    Tr.Move(d, p);
    switch (d) {
    case up: p.y -= speed; break;
    case down: p.y += speed; break;
    case lleft: p.x -= speed; break;
    case rright: p.x += speed; break;
    }
  }
  void Draw(sf::RenderWindow& window) {
    sf::CircleShape shape(0.5f);
    shape.setFillColor(sf::Color::Yellow);
    shape.setPosition(p.x, p.y);
    window.draw(shape);
  }
private:
  int speed;
public:Point p;
};

int main()
{
  sf::RenderWindow window(sf::VideoMode(1000, 1000), "MovePoint");
  window.setVerticalSyncEnabled(true);
  Point a(391, 109);
  Point b(169, 915);
  Point c(765, 150);
  Point t(0, 0), tmp(0, 0);

  Pointer pa(a, 4);
  Pointer pb(b, 4);
  Pointer pc(c, 4);
  Pointer pt(t, 4);
  //Trace t(a);

  pa.Draw(window);
  pb.Draw(window);
  pc.Draw(window);
  for (int i = 0; i < 100000; i++)
  {
    int cub = rand() % 6 + 1;
    if (cub == 1 || cub == 2) {
      pt.p.x = (pa.p.x + pt.p.x)/2;
      pt.p.y = (pa.p.y + pt.p.y) / 2;
    }
    else if (cub == 3 || cub == 4) {
      pt.p.x = (pc.p.x + pt.p.x) / 2;
      pt.p.y = (pc.p.y + pt.p.y) / 2;
    }
    else if (cub == 5 || cub == 6) {
      pt.p.x = (pb.p.x + pt.p.x) / 2;
      pt.p.y = (pb.p.y + pt.p.y) / 2;
    }
    pt.Draw(window);
    
    /*sleep(sf::seconds(0.0001));*/
  }
   
  window.display();
  while (window.isOpen())
  {
    sf::Event event;
    bool status = false;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
    }
    /*while (window.pollEvent(event)){
      if (event.type == sf::Event::Closed)
        window.close();
      if (event.type == sf::Event::KeyPressed) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
          p.Move(lleft, t);
          status = true;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
          p.Move(rright, t);
          status = true;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
          p.Move(up, t);
          status = true;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
          p.Move(down, t);
          status = true;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
          window.close();
        }
        else {
          status = false;
        }
        break;
      }
    }   */
    
    /*window.clear();
    t.Draw(window, status);
    p.Draw(window);*/
  }

  return 0;
}