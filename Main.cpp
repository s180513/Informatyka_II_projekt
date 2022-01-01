#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>
#include <random>
#include <math.h>

#define PI 3.14159265
#define velocity 15
#define maxvelocity 300
#define lasernum 5
#define laservelocity 50
#define borderx 1000
#define bordery 600
#define asteroidnum 30
#define heartnum 3

class menu {
private:
	int points;
	sf::Font czcionka;
	sf::Text tekst[7];
	sf::RectangleShape sidebar;
public:
	menu() {
		points = 0;
		if (!czcionka.loadFromFile("AGENCYB.ttf")) return;
		sidebar.setSize(sf::Vector2f(200,600));
		sidebar.setFillColor(sf::Color(30, 30, 30));
		sidebar.setPosition(0, 0);
		for (int i = 0; i < 7; i++) {
			tekst[i].setFont(czcionka);
			tekst[i].setFillColor(sf::Color::White);
		}
		tekst[0].setString("Difficulty:");
		tekst[0].setPosition(10.f, 10.f);
		tekst[1].setString("Hard");
		tekst[1].setPosition(10.f, 50.f);
		tekst[2].setString("Score:");
		tekst[2].setPosition(10.f, 100.f);
		//cords for points (10.f,140.f)
		tekst[3].setString("Lives:");
		tekst[3].setPosition(10.f, 190.f);
		tekst[4].setString("Ammunition:");
		tekst[4].setPosition(10.f, 300.f);
		tekst[5].setString("F1 - Help");
		tekst[5].setPosition(10.f, bordery-80);
		tekst[5].setCharacterSize(20);
		tekst[6].setString("Esc - Exit");
		tekst[6].setPosition(10.f, bordery-40);
		tekst[6].setCharacterSize(20);
	}

	void drawMenu(sf::RenderWindow& window) {
		window.draw(sidebar);
		for (int i = 0; i < 7; i++) window.draw(tekst[i]);
	}
};

class ship :public sf::Mouse {
private:
	float x;
	float y;
	float dx;
	float dy;
	float angle;
	bool id;
	int counter;
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
		id = 0;
		counter = 0;
		statek.setOrigin(19.5, 33.5);
		statek.setPosition(x, y);
	}
	sf::Sprite getStatek() {
		return statek;
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
		this->angle = (atan2(mousepos.y, mousepos.x) * 180 / PI) + 90;
		statek.setRotation(this->angle);
	}
	void newPos(float Dx, float Dy) {
		if (Dx != 0) {
			if (this->dx < maxvelocity && this->dx > -maxvelocity) {
				this->dx += Dx;
			}
			this->x += (dx * 0.03);
			if (x > borderx - 10) {
				dx = 0;
				x = borderx - 10;
			}
			if (x < 200) {
				dx = 0;
				x = 200;
			}
		}
		if (Dy != 0) {
			if (this->dy < maxvelocity && this->dy > -maxvelocity) {
				this->dy += Dy;
			}
			this->y += (dy * 0.03);
			if (y > bordery - 10) {
				dy = 0;
				y = bordery - 10;
			}
			if (y < 10) {
				dy = 0;
				y = 10;
			}
		}
		if (Dx == 0) {
			if (this->dx > 0)this->dx -= velocity;
			if (this->dx < 0)this->dx += velocity;
			this->x += (dx * 0.03);
			if (x > borderx - 10) {
				dx = 0;
				x = borderx - 10;
			}
			if (x < 200) {
				dx = 0;
				x = 200;
			}
		}

		if (Dy == 0) {
			if (this->dy > 0)this->dy -= velocity;
			if (this->dy < 0)this->dy += velocity;
			this->y += (dy * 0.03);
			if (y > bordery - 10) {
				dy = 0;
				y = bordery - 10;
			}
			if (y < 10) {
				dy = 0;
				y = 10;
			}
		}
	}
	bool getId() {
		return id;
	}
	void statekImmune() {
		id = 1;
	}
	void drawStatic() {
		tekstura.loadFromFile("Ship.png");
	}
	void drawMoving() {
		tekstura.loadFromFile("Shipmove.png");
	}
	void drawShip(sf::RenderWindow& window) {
		if (id) {
			counter++;
			if (counter == 100) {
				id = 0;
				counter = 0;
			}
		}
		statek.setPosition(x, y);
		if (counter % 2 == 0) window.draw(statek);
	}
};

class lasers :public ship, sf::Transformable {
private:
	int number;
	bool id[lasernum];
	double ang[lasernum];
	sf::Vector2f posl[lasernum];
	sf::Texture tekstura;
	sf::Sprite laser[lasernum];
	sf::Vector2f vell[lasernum];
	sf::Vector2f vellconst[lasernum];
public:
	lasers() {
		number = 0;
		tekstura.loadFromFile("Laser.png");
		for (int i = 0; i < lasernum; i++) {
			ang[i] = 0;
			id[i] = 0;
			posl[i].x = 0;
			posl[i].y = 0;
			vell[i].x = 0;
			vell[i].y = 0;
			vellconst[i].x = 0;
			vellconst[i].y = 0;
			laser[i].setTexture(tekstura);
			laser[i].setTextureRect(sf::IntRect(0, 0, 9, 55));
			laser[i].setOrigin(4.5, 22.5);
		}
	}
	sf::Sprite getLaser(int i) {
		return laser[i];
	}
	bool getId(int i) {
		return id[i];
	}
	void deleteLaser(int i) {
		this->id[i] = 0;
	}
	int getFired() {
		return this->number;
	}
	void shootLaser(sf::Vector2i mousepos, sf::Vector2f pos) {
		this->ang[number] = (atan2(mousepos.y, mousepos.x) * 180 / PI) + 90;
		this->posl[number] = pos;
		laser[number].setPosition(pos.x, pos.y);
		laser[number].setRotation(ang[number]);
		this->vell[number].x = laservelocity * cos((ang[number] + 90) * PI / 180);
		this->vell[number].y = laservelocity * sin((ang[number] + 90) * PI / 180);
		this->vellconst[number] = vell[number];
		id[number] = 1;
		this->number += 1;
		if (number == lasernum) {
			number = 0;
			//add some reloading shit idk
		}
	}
	void moveLaser() {
		for (int i = 0; i < number; i++) {
			sf::Vector2f newposl = posl[i] - vell[i];
			laser[i].setPosition(newposl);
			this->vell[i] += vellconst[i];
			if ((newposl.x > borderx + 30) || (newposl.x < 170) || (newposl.y > bordery + 30) || (newposl.y < -30)) {
				id[i] = 0;
			}
		}
	}
	void drawLaser(sf::RenderWindow& window) {
		for (int i = 0; i < number; i++) {
			if (id[i]) window.draw(laser[i]);
		}
	}
};

class hearts {
private:
	sf::ConvexShape Heart[3];
	int stan;
public:
	hearts() {
		stan = heartnum;
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
		Heart[0].setPosition(20.f, 240.f);
		Heart[1].setPosition(80.f, 240.f);
		Heart[2].setPosition(140.f, 240.f);
	}
	void addHeart() {
		if (stan < 3) stan += 1;
	}
	void subHeart() {
		if (stan > 0) stan -= 1;
	}
	void drawHeart(sf::RenderWindow& window) {
		for (int i = 0; i < stan; i++) {
			window.draw(Heart[i]);
		}
	}
};

class rocks {
private:
	bool id[asteroidnum];
	bool expid[asteroidnum];
	int counter[asteroidnum];
	sf::Sprite rock[asteroidnum];
	sf::Texture tekstura1, tekstura2, tekstura3, tekstura4;
	sf::Vector2f posa[asteroidnum];
	sf::Vector2f vela[asteroidnum];
	sf::Vector2f velaconst[asteroidnum];
	std::random_device rd;
public:
	rocks() {
		for (int i = 0; i < asteroidnum; i++) {
			newPositionRock(i);
			counter[i] = 0;
			expid[i] = 0;
		}
		tekstura1.loadFromFile("Rock1.png");
		tekstura2.loadFromFile("Rock2.png");
		tekstura3.loadFromFile("Rock3.png");
		tekstura4.loadFromFile("Explosion.png");
	}
	sf::Sprite getRock(int i) {
		return rock[i];
	}
	bool getId(int i) {
		return id[i];
	}
	bool getExpId(int i) {
		return expid[i];
	}
	void makeExplode(int i) {
		rock[i].setTexture(tekstura4);
		expid[i] = 1;
	}
	void deleteRock(int i) {
		id[i] = 0;
		expid[i] = 0;
		counter[i] = 0;
	}
	void newPositionRock(int i) {
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> distx(0, 1200);
		std::uniform_int_distribution<> disty(-200, 800);
		std::uniform_int_distribution<> distt(1, 3);
		std::uniform_int_distribution<> distr(0, 360);
		std::uniform_int_distribution<> distvx(-5, 5);
		std::uniform_int_distribution<> distvy(-5, 5);
		std::uniform_real_distribution<> dists(0.1, 0.3);
		int x, y;
		double scale;
		bool flagax = 0;
		bool flagay = 0;
		while (flagax == 0) {
			x = distx(gen);
			if (x < 150 || x > borderx+50) {
				this->posa[i].x = x;
				flagax = 1;
			}
		}
		while (flagay == 0) {
			y = disty(gen);
			if (y < -50 || y > bordery+50) {
				this->posa[i].y = y;
				flagay = 1;
			}
		}
		switch (distt(gen)) {
		case 1:
			rock[i].setTexture(tekstura1);
			rock[i].setTextureRect(sf::IntRect(0, 0, 320, 259));
			rock[i].setOrigin(180, 229.5);
			break;
		case 2:
			rock[i].setTexture(tekstura2);
			rock[i].setTextureRect(sf::IntRect(0, 0, 278, 239));
			rock[i].setOrigin(139, 119.5);
			break;
		case 3:
			rock[i].setTexture(tekstura3);
			rock[i].setTextureRect(sf::IntRect(0, 0, 249, 222));
			rock[i].setOrigin(124.5, 111);
			break;
		}
		scale = dists(gen);
		rock[i].setScale(scale, scale);
		rock[i].setRotation(distr(gen));
		this->vela[i].x = distvx(gen);
		this->vela[i].y = distvy(gen);
		this->velaconst[i] = vela[i];
		id[i] = 1;
	}
	void moveRocks() {
		for (int i = 0; i < asteroidnum; i++) {
			sf::Vector2f newposa = posa[i] - vela[i];
			rock[i].setPosition(newposa);
			this->vela[i] += velaconst[i];
			if ((newposa.x > borderx + 200) || (newposa.x < 0) || (newposa.y > bordery + 200) || (newposa.y < - 200)) {
				id[i] = 0;
			}
		}
	}
	void checkId() {
		for (int i = 0; i < asteroidnum; i++) {
			if (id[i] == 0) newPositionRock(i);
		}
	}
	void drawRocks(sf::RenderWindow& window) {
		for (int i = 0; i < asteroidnum; i++) {
			if (expid[i]) {
				counter[i]++;
				sf::Vector2f newscale;
				newscale = rock[i].getScale();
				rock[i].setScale(1.01*newscale.x, 1.01*newscale.y);
			}
			if (counter[i] == 10) deleteRock(i);
		}
		for (int i = 0; i < asteroidnum; i++) {
			window.draw(rock[i]);
		}
	}
};

class ammo {
private:
	sf::RectangleShape bullet[lasernum];
public:
	ammo() {
		for (int i = 0; i < lasernum; i++) {
			bullet[i].setFillColor(sf::Color::White);
			bullet[i].setSize(sf::Vector2f(15, 30));
		}
	}
};

int main() {

	sf::Clock zegar, zegarLaser;

	ship p1;
	lasers l1;
	rocks r1;
	hearts h1;
	menu m1;
	sf::RenderWindow window(sf::VideoMode(borderx, bordery), "~Asteroid Shooter~");
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
			r1.checkId();

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
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				if (zegarLaser.getElapsedTime().asMilliseconds() > 250.f) {
					l1.shootLaser(mousepos, pos);
					zegarLaser.restart();
				}	
			}
			l1.moveLaser();
			r1.moveRocks();


			for (int i = 0; i < lasernum; i++) {
				for (int j = 0; j < asteroidnum; j++) {
					if (r1.getExpId(j) == 0 && r1.getId(j) && l1.getId(i) && (l1.getLaser(i).getGlobalBounds().intersects(r1.getRock(j).getGlobalBounds()))) {
						r1.makeExplode(j);
						l1.deleteLaser(i);
						//add points
					}
				}
			}
			for (int i = 0; i < asteroidnum; i++) {
				if (p1.getId() == 0 && r1.getExpId(i) == 0 && p1.getStatek().getGlobalBounds().intersects(r1.getRock(i).getGlobalBounds())) {
					h1.subHeart();
					p1.statekImmune();
				}
			}
			


			//printf("x = %f, y = %f\n", pos.x, pos.y);
			//printf("dx = %f, dy = %f\n", vel.x, vel.y);
			//printf("mouse.x = %d, mouse.y = %d\n", mousepos.x, mousepos.y);
			zegar.restart();
			window.clear();

			
			l1.drawLaser(window);
			p1.drawShip(window);
			r1.drawRocks(window);
			m1.drawMenu(window);
			h1.drawHeart(window);
			window.display();
		}

	}

	return  0;

}