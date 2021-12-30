#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>
#include <random>
#include <math.h>

#define PI 3.14159265
#define velocity 15
#define maxvelocity 300


class ship :public sf::Mouse {
private:
	float x;
	float y;
	float dx;
	float dy;
	float angle;
	sf::Texture tekstura;
	sf::Sprite statek;
public:
	ship() {
		tekstura.loadFromFile("Ship.png");
		statek.setTexture(tekstura);
		statek.setTextureRect(sf::IntRect(0, 0, 39, 67));
		x = 600;
		y = 400;
		dx = 0;
		dy = 0;
		angle = 0;
		statek.setOrigin(19.5, 33.5);
		statek.setPosition(x, y);
	}
	void getPos(sf::Vector2f& pos) {
		pos.x = this->x;
		pos.y = this->y;
	}
	void setPos(float X, float Y) {
		this->x = X;
		this->y = Y;
	}
	void getVel(sf::Vector2f& vel) {
		vel.x = this->dx;
		vel.y = this->dy;
	}
	void rotateShip(sf::Vector2i mousepos) {
		this->angle = (atan2f(mousepos.y, mousepos.x) * 180 / PI) + 90;
		statek.setRotation(this->angle);
		printf("%f\n", this->angle);
	}
	void newPos(float Dx, float Dy) {

		//fubar
		if (Dx != 0) {
			if (this->dx < maxvelocity && this->dx > -maxvelocity) {
				this->dx += Dx;
			}
			this->x += (dx * 0.03);
		}
		if (Dy != 0) {
			if (this->dy < maxvelocity && this->dy > -maxvelocity) {
				this->dy += Dy;
			}
			this->y += (dy * 0.03);
		}
		if (Dx == 0) {
			if (this->dx > 0)this->dx -= velocity;
			if (this->dx < 0)this->dx += velocity;
			this->x += (dx * 0.03);
		}
		if (Dy == 0) {
			if (this->dy > 0)this->dy -= velocity;
			if (this->dy < 0)this->dy += velocity;
			this->y += (dy * 0.03);
		}
	}
	void drawStatic() {
		tekstura.loadFromFile("Ship.png");
	}
	void drawMoving() {
		tekstura.loadFromFile("Shipmove.png");
	}
	void drawShip(sf::RenderWindow& window) {
		statek.setPosition(x, y);
		window.draw(statek);
	}
};

class lasers :public ship {
private:
	int nFired;
	sf::Texture tekstura;
	sf::Sprite laser[20];
public:
	lasers() {
		nFired = 0;
		tekstura.loadFromFile("Laser.png");
		for (int i = 0; i < 20; i++) {
			laser[i].setTexture(tekstura);
			laser[i].setTextureRect(sf::IntRect(0, 0, 9, 55));
			laser[i].setOrigin(4.5, 22.5);
		}
	}
	void shootLaser(sf::Vector2i mousepos, sf::Vector2f pos) {
		float ang, x, y;
		ang = (atan2f(mousepos.y, mousepos.x) * 180 / PI) + 90;
		x = 50 * cos(ang);
		y = 50 * sin(ang);
		laser[this->nFired].setPosition(pos.x - x, pos.y - y);
		laser[this->nFired].setRotation(ang);

		this->nFired += 1;
	}
	void drawLaser(sf::RenderWindow& window) {
		for (int i = 0; i < this->nFired; i++) {
			window.draw(laser[i]);
		}
	}
};

class hearts {
private:
	sf::ConvexShape Heart[3];
public:
	hearts() {
		for (int i = 0; i < 3; i++) {
			Heart[i].setPointCount(10);
			Heart[i].setFillColor(sf::Color::Red);
			Heart[i].setOutlineThickness(2);
			Heart[i].setOutlineColor(sf::Color(51, 51, 51));
			Heart[i].setPoint(0, sf::Vector2f(0.f, 10.f));
			Heart[i].setPoint(1, sf::Vector2f(0.f, 20.f));
			Heart[i].setPoint(2, sf::Vector2f(20.f, 40.f));
			Heart[i].setPoint(3, sf::Vector2f(40.f, 20.f));
			Heart[i].setPoint(4, sf::Vector2f(40.f, 10.f));
			Heart[i].setPoint(5, sf::Vector2f(33.f, 3.f));
			Heart[i].setPoint(6, sf::Vector2f(27.f, 3.f));
			Heart[i].setPoint(7, sf::Vector2f(20.f, 10.f));
			Heart[i].setPoint(8, sf::Vector2f(13.f, 3.f));
			Heart[i].setPoint(9, sf::Vector2f(7.f, 3.f));
		}
		Heart[0].setPosition(15.f, 300.f);
		Heart[1].setPosition(60.f, 300.f);
		Heart[2].setPosition(105.f, 300.f);
	}
	void addHeart(int* stan) {
		if (*stan < 3) *stan += 1;
	}
	void subHeart(int* stan) {
		if (*stan > 0) *stan -= 1;
	}
	void drawHeart(sf::RenderWindow& window, int* stan) {
		for (int i = 0; i < *stan; i++) {
			window.draw(Heart[i]);
		}
	}
};

int main() {

	sf::Clock zegar, zegarLaser;

	ship p1;
	lasers l1;
	hearts h1;
	int stan = 3;
	int* stanp = &stan;
	sf::RenderWindow window(sf::VideoMode(1000, 600), "~Asteroid Shooter~");
	sf::Event event;

	sf::Cursor cursor;
	if (cursor.loadFromSystem(sf::Cursor::Cross))
		window.setMouseCursor(cursor);

	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::EventType::Closed)
				window.close();
		}

		if (zegar.getElapsedTime().asMilliseconds() > 30.f) {

			sf::Vector2f pos, vel;
			sf::Vector2i mousepos;
			p1.getPos(pos);
			p1.getVel(vel);



			mousepos = p1.getPosition(window);
			mousepos.x -= (pos.x);
			mousepos.y -= (pos.y);

			p1.rotateShip(mousepos);

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
					p1.newPos(0, -velocity);
					p1.drawMoving();
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
					p1.newPos(0, velocity);
					p1.drawMoving();
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
					p1.newPos(-velocity, 0);
					p1.drawMoving();
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
					p1.newPos(velocity, 0);
					p1.drawMoving();
				}
			}
			else {
				p1.newPos(0, 0);
				p1.drawStatic();
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
				if (zegarLaser.getElapsedTime().asMilliseconds() > 500.f) {
					l1.shootLaser(mousepos, pos);
					zegarLaser.restart();
				}
			}





			//printf("x = %f, y = %f\n", pos.x, pos.y);
			//printf("dx = %f, dy = %f\n", vel.x, vel.y);
			//printf("mouse.x = %d, mouse.y = %d\n", mousepos.x, mousepos.y);
			zegar.restart();
			window.clear();

			h1.drawHeart(window, stanp);
			p1.drawShip(window);
			l1.drawLaser(window);
			window.display();
		}

	}

	return  0;

}