#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>
#include <random>
#include <math.h>
#include <string>
#include <vector>
#include <fstream>

#define PI 3.14159265
#define velocity 15
#define maxvelocity 300
#define lasernum 10
#define laservelocity 50
#define borderx 1000
#define bordery 600
#define asteroidnum 30
#define heartnum 3

struct player {
	std::string name;
	int difficulty = 4;
	int points = 0;
};

class startmenu {
private:
	bool menuflaga;
	int num;
	int diffpos;
	std::string str;
	sf::Font czcionka;
	sf::Text tekst[6];
	sf::RectangleShape menuwindow, diffwindow[3];
	std::vector<char> nazwa;
public:
	startmenu() {
		menuflaga = 0;
		num = 0;
		diffpos = 4;
		menuwindow.setSize(sf::Vector2f(600, 400));
		menuwindow.setFillColor(sf::Color(80, 80, 80));
		menuwindow.setPosition(300, 100);
		menuwindow.setOutlineThickness(5);
		menuwindow.setOutlineColor(sf::Color(140, 140, 140));
		for (int i = 0; i < 3; i++) {
			diffwindow[i].setFillColor(sf::Color(200, 200, 200));
			diffwindow[i].setOutlineThickness(5);
			diffwindow[i].setOutlineColor(sf::Color(140, 140, 140));
			diffwindow[i].setSize(sf::Vector2f(140, 60));
		}
		diffwindow[0].setPosition(327, 378);
		diffwindow[1].setPosition(522, 378);
		diffwindow[2].setPosition(722, 378);
		if (!czcionka.loadFromFile("AGENCYB.ttf")) return;
		for (int i = 0; i < 6; i++) {
			tekst[i].setFont(czcionka);
			tekst[i].setFillColor(sf::Color::White);
		}
		tekst[0].setString("~Asteroid Shooter~");
		tekst[0].setPosition(358, 140);
		tekst[0].setCharacterSize(70);
		tekst[1].setString("Name: ");
		tekst[1].setPosition(350, 250);
		tekst[1].setCharacterSize(50);

		tekst[2].setPosition(470, 250);
		tekst[2].setCharacterSize(50);
		
		tekst[3].setString("Easy");
		tekst[3].setPosition(360, 375);
		tekst[3].setCharacterSize(50);
		tekst[4].setString("Normal");
		tekst[4].setPosition(530, 375);
		tekst[4].setCharacterSize(50);
		tekst[4].setFillColor(sf::Color(80,80,80));
		tekst[5].setString("Hard");
		tekst[5].setPosition(750, 375);
		tekst[5].setCharacterSize(50);
	}
	bool getFlaga() {
		return menuflaga;
	}
	void setFlaga(bool i) {
		menuflaga = i;
	}
	int getDiffPos() {
		return diffpos;
	}
	void closeStart() {
		menuflaga++;
	}
	void setChar(char znak) {
		nazwa.push_back(znak);
		std::string name(nazwa.begin(), nazwa.end());
		tekst[2].setString(name);
		str = name;
	}
	void deleteChar() {
		nazwa.pop_back();
		std::string name(nazwa.begin(), nazwa.end());
		tekst[2].setString("                                 ");
		tekst[2].setString(name);
		str = name;
	}
	void setDiff(bool direction) {
		if (direction) {
			if (diffpos != 5) {
				tekst[diffpos].setFillColor(sf::Color::White);
				diffpos++;
				tekst[diffpos].setFillColor(sf::Color(80, 80, 80));
			}
		}
		if (direction == 0) {
			if (diffpos != 3) {
				tekst[diffpos].setFillColor(sf::Color::White);
				diffpos--;
				tekst[diffpos].setFillColor(sf::Color(80, 80, 80));
			}
		}
	}
	std::string getName() {
		return str;
	}
	void drawStart(sf::RenderWindow& window) {
		window.draw(menuwindow);
		for (int i = 0; i < 3; i++) window.draw(diffwindow[i]);
		for (int i = 0; i < 6; i++) {
			window.draw(tekst[i]);
		}
	}
};

class helpmenu {
private:
	bool menuflaga;
	sf::Font czcionka;
	sf::Text tekst[2];
	sf::RectangleShape menuwindow;
public:
	helpmenu() {
		menuflaga = 0;
		if (!czcionka.loadFromFile("AGENCYB.ttf")) return;
		menuwindow.setSize(sf::Vector2f(900, 500));
		menuwindow.setFillColor(sf::Color(30, 30, 30));
		menuwindow.setPosition(50, 50);
		menuwindow.setOutlineThickness(5);
		menuwindow.setOutlineColor(sf::Color(140, 140, 140));
		for (int i = 0; i < 2; i++) {
			tekst[i].setFont(czcionka);
			tekst[i].setCharacterSize(20);
			tekst[i].setFillColor(sf::Color::White);
		}
		tekst[0].setPosition(70, 60);
		tekst[0].setString("How to start:\nWrite your name and choose the difficulty using left and right keys. \nStart the game by pressing Enter. \n\nHow to Play:\nShoot asteroids to get points. Each shot asteroid is worth 100 points. \nWhen you get hit by an asteroid you loose a life. \nIf you loose all 3 hearts, it's game over.\n\nControls:\nWASD - movement keys\nLMB - shooting\nMouse - aiming\nF1 - Help\nEsc - Exiting the game");
		tekst[1].setPosition(70, 500);
		tekst[1].setString("~Press F1 to exit this window~");
	}
	bool getFlaga() {
		return menuflaga;
	}
	void setFlaga(bool i) {
		menuflaga = i;
	}
	void drawMenu(sf::RenderWindow& window) {
		window.draw(menuwindow);
		window.draw(tekst[0]);
		window.draw(tekst[1]);
	}
};

class escapemenu {
private:
	bool menuflaga;
	bool choice;
	sf::Font czcionka;
	sf::Text tekst[3];
	sf::RectangleShape menuwindow, choicewindow[2];
public:
	escapemenu() {
		menuflaga = 0;
		choice = 1;
		if (!czcionka.loadFromFile("AGENCYB.ttf")) return;
		menuwindow.setSize(sf::Vector2f(400, 200));
		menuwindow.setFillColor(sf::Color(30, 30, 30));
		menuwindow.setPosition(400, 200);
		menuwindow.setOutlineThickness(5);
		menuwindow.setOutlineColor(sf::Color(140, 140, 140));
		for (int i = 0; i < 3; i++) {
			tekst[i].setFont(czcionka);
			tekst[i].setFillColor(sf::Color::White);
			tekst[i].setCharacterSize(40);
		}
		for (int i = 0; i < 2; i++) {
			choicewindow[i].setFillColor(sf::Color(200, 200, 200));
			choicewindow[i].setOutlineThickness(5);
			choicewindow[i].setOutlineColor(sf::Color(140, 140, 140));
			choicewindow[i].setSize(sf::Vector2f(90, 50));
		}
		choicewindow[0].setPosition(460, 320);
		choicewindow[1].setPosition(635, 320);
		tekst[0].setString("Do you want to exit?");
		tekst[0].setPosition(450, 220);
		tekst[1].setString("Yes");
		tekst[1].setPosition(480, 320);
		tekst[2].setString("No");
		tekst[2].setPosition(660, 320);
		tekst[2].setFillColor(sf::Color(80, 80, 80));
	}
	void setChoice(bool direction) {
		if (direction == 1 && choice == 0) {
			tekst[1].setFillColor(sf::Color::White);
			choice = 1;
			tekst[2].setFillColor(sf::Color(80, 80, 80));
		}
		if (direction == 0 && choice == 1) {
			tekst[2].setFillColor(sf::Color::White);
			choice = 0;
			tekst[1].setFillColor(sf::Color(80, 80, 80));
		}
	}
	bool getChoice() {
		return choice;
	}
	bool getFlaga() {
		return menuflaga;
	}
	void setFlaga(bool i) {
		menuflaga = i;
	}
	void drawMenu(sf::RenderWindow& window) {
		window.draw(menuwindow);
		for (int i = 0; i < 2; i++) window.draw(choicewindow[i]);
		for (int i = 0; i < 3; i++) window.draw(tekst[i]);
		
	}
};

class gameover {
private:
	bool menuflaga;
	bool choice;
	sf::Font czcionka;
	sf::Text tekst[10];
	sf::RectangleShape menuwindow, choicewindow[2];
public:
	gameover() {
		menuflaga = 0;
		choice = 1;
		if (!czcionka.loadFromFile("AGENCYB.ttf")) return;
		menuwindow.setSize(sf::Vector2f(400, 450));
		menuwindow.setFillColor(sf::Color(30, 30, 30));
		menuwindow.setPosition(400, 100);
		menuwindow.setOutlineThickness(5);
		menuwindow.setOutlineColor(sf::Color(140, 140, 140));
		for (int i = 0; i < 10; i++) {
			tekst[i].setFont(czcionka);
			tekst[i].setFillColor(sf::Color::White);
			tekst[i].setCharacterSize(40);
		}
		for (int i = 0; i < 2; i++) {
			choicewindow[i].setFillColor(sf::Color(200, 200, 200));
			choicewindow[i].setOutlineThickness(5);
			choicewindow[i].setOutlineColor(sf::Color(140, 140, 140));
			choicewindow[i].setSize(sf::Vector2f(90, 50));
		}
		choicewindow[0].setPosition(460, 270);
		choicewindow[1].setPosition(635, 270);
		tekst[0].setString("Do you want to quit?");
		tekst[0].setPosition(450, 180);
		tekst[1].setString("Yes");
		tekst[1].setPosition(480, 270);
		tekst[2].setString("No");
		tekst[2].setPosition(660, 270);
		tekst[2].setFillColor(sf::Color(80, 80, 80));
		tekst[3].setString("Name:");
		tekst[3].setPosition(450, 360);
		tekst[4].setString("---");
		tekst[4].setPosition(550, 360);
		tekst[5].setString("Score:");
		tekst[5].setPosition(450, 420);
		tekst[6].setString("---");
		tekst[6].setPosition(560, 420);
		tekst[7].setString("Difficulty:");
		tekst[7].setPosition(450, 480);
		tekst[8].setString("---");
		tekst[8].setPosition(600, 480);
		tekst[9].setCharacterSize(40);
		tekst[9].setString("Game Over");
		tekst[9].setPosition(500, 120);
		tekst[9].setFillColor(sf::Color::Red);
	}
	void setChoice(bool direction) {
		if (direction == 1 && choice == 0) {
			tekst[1].setFillColor(sf::Color::White);
			choice = 1;
			tekst[2].setFillColor(sf::Color(80, 80, 80));
		}
		if (direction == 0 && choice == 1) {
			tekst[2].setFillColor(sf::Color::White);
			choice = 0;
			tekst[1].setFillColor(sf::Color(80, 80, 80));
		}
	}
	bool getChoice() {
		return choice;
	}
	bool getFlaga() {
		return menuflaga;
	}
	void setFlaga(bool i) {
		menuflaga = i;
	}
	void setGameover(std::string str, int diff, int score) {
		tekst[4].setString(str);
		switch (diff) {
		case 3:
			tekst[8].setString("Easy");
			break;
		case 4:
			tekst[8].setString("Normal");
			break;
		case 5:
			tekst[8].setString("Hard");
			break;
		}
		tekst[6].setString(std::to_string(score));
	}
	void drawMenu(sf::RenderWindow& window) {
		window.draw(menuwindow);
		for (int i = 0; i < 2; i++) window.draw(choicewindow[i]);
		for (int i = 0; i < 10; i++) window.draw(tekst[i]);
	}
};

class menu {
private:
	int points;
	int difficulty;
	sf::Font czcionka;
	sf::Text tekst[10];
	sf::RectangleShape sidebar;
	std::string highname, highpoints;
public:
	menu() {
		points = 0;
		difficulty = 0;
		if (!czcionka.loadFromFile("AGENCYB.ttf")) return;
		sidebar.setSize(sf::Vector2f(200,600));
		sidebar.setFillColor(sf::Color(30, 30, 30));
		sidebar.setPosition(0, 0);
		for (int i = 0; i < 10; i++) {
			tekst[i].setFont(czcionka);
			tekst[i].setFillColor(sf::Color::White);
		}
		for (int i = 8; i < 10; i++) {
			tekst[i].setCharacterSize(20);
		}
		tekst[0].setString("Difficulty:");
		tekst[0].setPosition(10.f, 10.f);
		tekst[1].setString("---");
		tekst[1].setPosition(10.f, 50.f);
		tekst[2].setString("Score:");
		tekst[2].setPosition(10.f, 100.f);
		tekst[3].setString(std::to_string(points));
		tekst[3].setPosition(10.f, 140.f);
		tekst[4].setString("Lives:");
		tekst[4].setPosition(10.f, 190.f);
		tekst[5].setString("Highscore:");
		tekst[5].setPosition(10.f, 300.f);
		tekst[6].setString("---");
		tekst[6].setPosition(10.f, 340.f);
		tekst[7].setString("---");
		tekst[7].setPosition(10.f, 380.f);
		tekst[8].setString("F1 - Help");
		tekst[8].setPosition(10.f, bordery-80);
		tekst[9].setString("Esc - Exit");
		tekst[9].setPosition(10.f, bordery-40);
	}
	void setDifficulty(int i) {
		switch (i) {
		case 3:
			tekst[1].setString("Easy");
			break;
		case 4:
			tekst[1].setString("Normal");
			break;
		case 5:
			tekst[1].setString("Hard");
			break;
		}
	}
	std::string getHighpoints() {
		return highpoints;
	}
	void setHigh(int i) {
		std::fstream log("Log.txt");
		if (log.is_open())
		{
			int licznik = 0;
			int beg = 0;
			int end = 1;
			bool flaga = 1;
			std::string line;
			switch (i) {
			case 3:
				beg = 0;
				end = 1;
				break;
			case 4:
				beg = 2;
				end = 3;
				break;
			case 5:
				beg = 4;
				end = 5;
				break;
			}		
			while (std::getline(log, line)) {
				if (licznik == beg) {
					tekst[6].setString(line);
					highname = line;
				}
				if (licznik == end) {
					tekst[7].setString(line);
					highpoints = line;
				}
				licznik++;
			}
			log.close();
		}
		else std::cout << "Unable to open file";
	}
	int getPoints() {
		return points;
	}
	void resetPoints() {
		points = 0;
		tekst[3].setString(std::to_string(points));
		tekst[1].setString("---");
	}
	void resetHigh() {
		tekst[6].setString("---");
		tekst[7].setString("---");
	}
	void addPoints() {
		points += 100;
		tekst[3].setString(std::to_string(points));
	}
	void drawMenu(sf::RenderWindow& window) {
		window.draw(sidebar);
		for (int i = 0; i < 10; i++) window.draw(tekst[i]);
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
		pos.x = x;
		pos.y = y;
	}
	void setPos(float X, float Y) {
		x = X;
		y = Y;
	}
	void getVel(sf::Vector2f& vel) {
		vel.x = dx;
		vel.y = dy;
	}
	void rotateShip(sf::Vector2i mousepos) {
		angle = (atan2(mousepos.y, mousepos.x) * 180 / PI) + 90;
		statek.setRotation(angle);
	}
	void newPos(float Dx, float Dy) {
		if (Dx != 0) {
			if (dx < maxvelocity && dx > -maxvelocity) {
				dx += Dx;
			}
			x += (dx * 0.03);
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
			if (dy < maxvelocity && dy > -maxvelocity) {
				dy += Dy;
			}
			y += (dy * 0.03);
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
			if (dx > 0)dx -= velocity;
			if (dx < 0)dx += velocity;
			x += (dx * 0.03);
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
			if (dy > 0)dy -= velocity;
			if (dy < 0)dy += velocity;
			y += (dy * 0.03);
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
	void resetPosition() {
		x = 600;
		y = 400;
		dx = 0;
		dy = 0;
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
		id[i] = 0;
	}
	int getFired() {
		return number;
	}
	void shootLaser(sf::Vector2i mousepos, sf::Vector2f pos) {
		ang[number] = (atan2(mousepos.y, mousepos.x) * 180 / PI) + 90;
		posl[number] = pos;
		laser[number].setPosition(pos.x, pos.y);
		laser[number].setRotation(ang[number]);
		vell[number].x = laservelocity * cos((ang[number] + 90) * PI / 180);
		vell[number].y = laservelocity * sin((ang[number] + 90) * PI / 180);
		vellconst[number] = vell[number];
		id[number] = 1;
		number += 1;
		if (number == lasernum) {
			number = 0;
		}
	}
	void moveLaser() {
		for (int i = 0; i < number; i++) {
			sf::Vector2f newposl = posl[i] - vell[i];
			laser[i].setPosition(newposl);
			vell[i] += vellconst[i];
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
	void resetHeart() {
		stan = heartnum;
	}
	void subHeart() {
		if (stan > 0) stan -= 1;
	}
	int getStan() {
		return stan;
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
	float difficulty;
	sf::Sprite rock[asteroidnum];
	sf::Texture tekstura1, tekstura2, tekstura3, tekstura4;
	sf::Vector2f posa[asteroidnum];
	sf::Vector2f vela[asteroidnum];
	sf::Vector2f velaconst[asteroidnum];
	std::random_device rd;
public:
	rocks() {
		difficulty = 1;
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
	bool getExpId(int i) {
		return expid[i];
	}
	void getExpId_and_Id(bool *expid_in, bool *id_in, int i) {
		*expid_in = this->expid[i];
		*id_in = this->id[i];
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
				posa[i].x = x;
				flagax = 1;
			}
		}
		while (flagay == 0) {
			y = disty(gen);
			if (y < -50 || y > bordery+50) {
				posa[i].y = y;
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
		vela[i].x = distvx(gen);
		vela[i].y = distvy(gen);
		vela[i].x *= difficulty;
		vela[i].y *= difficulty;
		velaconst[i] = vela[i];
		id[i] = 1;
	}
	void moveRocks() {
		for (int i = 0; i < asteroidnum; i++) {
			sf::Vector2f newposa = posa[i] - vela[i];
			rock[i].setPosition(newposa);
			vela[i] += velaconst[i];
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
	void setDifficulty(int i) {
		switch (i) {
		case 3:
			difficulty = 0.7;
			break;
		case 4:
			difficulty = 1;
			break;
		case 5:
			difficulty = 1.5;
			break;
		}
	}
	void resetRocks() {
		for (int i = 0; i < asteroidnum; i++) {
			newPositionRock(i);
			counter[i] = 0;
			expid[i] = 0;
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

void savePlayer(player *p, std::string highpoints) {
	int intHighpoints = std::stoi(highpoints);
	if (p[0].points > intHighpoints) {
		std::fstream log1("Log.txt");
		std::string line;
		std::string file[6];
		if (log1.is_open())
		{
			int licznik = 0;
			while (getline(log1, line))
			{
				file[licznik] = line;
				licznik++;
			}
			log1.close();
		}
		else std::cout << "Unable to open file";
		std::ofstream log2("Log.txt");
		if (log2.is_open())
		{
			int beg = 0;
			int end = 1;
			switch (p[0].difficulty) {
			case 3:
				beg = 0;
				end = 1;
				break;
			case 4:
				beg = 2;
				end = 3;
				break;
			case 5:
				beg = 4;
				end = 5;
				break;
			}
			for (int i = 0; i < 6; i++) {

				if (i == beg) log2 << p[0].name << '\n';
				else if (i == end) log2 << p[0].points << '\n';
				else log2 << file[i] << '\n';
			}
			log2.close();
		}
		else std::cout << "Unable to open file";
	}	
}

int main() {

	sf::Clock zegar, zegarLaser;
	player p[1];
	ship s1;
	lasers l1;
	rocks r1;
	hearts h1;
	menu m1;
	startmenu sm1;
	helpmenu hm1;
	escapemenu em1;
	gameover go1;
	sf::RenderWindow window(sf::VideoMode(borderx, bordery), "~Asteroid Shooter~",sf::Style::Close);
	sf::Event event;
	sf::Cursor cursor;
	cursor.loadFromSystem(sf::Cursor::Cross);
	window.setMouseCursor(cursor);

	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::EventType::Closed)
				window.close();
		}
		//startmenu
		if (em1.getFlaga() == 0 && hm1.getFlaga() == 0 && sm1.getFlaga() == 0 && zegar.getElapsedTime().asMilliseconds() > 100.f) {
			if (event.type == sf::Event::TextEntered)
			{
				char znak = (event.text.unicode);
				if (znak == 13) {
					m1.setDifficulty(sm1.getDiffPos());
					m1.setHigh(sm1.getDiffPos());
					r1.setDifficulty(sm1.getDiffPos());
					p[0].difficulty = sm1.getDiffPos();
					p[0].name = sm1.getName();
					sm1.closeStart();
				}
				else if (znak == 27) {
					em1.setFlaga(1);
				}
				else if (znak == 8) {
					sm1.deleteChar();
				}
				else sm1.setChar(znak);
			}
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Left)
				{
					sm1.setDiff(0);
				}
				if (event.key.code == sf::Keyboard::Right)
				{
					sm1.setDiff(1);
				}
				if (event.key.code == sf::Keyboard::F1)
				{
					hm1.setFlaga(1);
				}
			}


			window.clear();
			zegar.restart();
			m1.drawMenu(window);
			h1.drawHeart(window);
			sm1.drawStart(window);
			window.display();
		}
		//game
		else if (go1.getFlaga() == 0 && em1.getFlaga() == 0 && hm1.getFlaga() == 0 && sm1.getFlaga() && zegar.getElapsedTime().asMilliseconds() > 30.f) {			
			if (event.type == sf::Event::TextEntered)
			{
				char znak = (event.text.unicode);	
				if (znak == 27) {
					em1.setFlaga(1);
				}
			}
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::F1)
				{
					hm1.setFlaga(1);
				}
			}

			sf::Vector2f pos, vel;
			sf::Vector2i mousepos;
			s1.getPos(pos);
			s1.getVel(vel);

			mousepos = s1.getPosition(window);
			mousepos.x -= (pos.x);
			mousepos.y -= (pos.y);

			s1.rotateShip(mousepos);
			r1.checkId();

			//sterowanie i strzelanie
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
					s1.newPos(0, -velocity);
					s1.drawMoving();
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
					s1.newPos(0, velocity);
					s1.drawMoving();
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
					s1.newPos(-velocity, 0);
					s1.drawMoving();
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
					s1.newPos(velocity, 0);
					s1.drawMoving();
				}
			}
			else {
				s1.newPos(0, 0);
				s1.drawStatic();
			}
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				if (zegarLaser.getElapsedTime().asMilliseconds() > 500.f) {
					l1.shootLaser(mousepos, pos);
					zegarLaser.restart();
				}
			}
			l1.moveLaser();
			r1.moveRocks();

			//kolizja laser/asteroida
			for (int i = 0; i < lasernum; i++) {
				for (int j = 0; j < asteroidnum; j++) {
					bool expid, id;
					r1.getExpId_and_Id(&expid, &id, j);
					if (expid == 0 && id && l1.getId(i) && (l1.getLaser(i).getGlobalBounds().intersects(r1.getRock(j).getGlobalBounds()))) {
						r1.makeExplode(j);
						l1.deleteLaser(i);
						m1.addPoints();
						p[0].points += 100;
					}
				}
			}
			//kolizja asteroida/statek
			for (int i = 0; i < asteroidnum; i++) {
				if (s1.getId() == 0 && r1.getExpId(i) == 0 && s1.getStatek().getGlobalBounds().intersects(r1.getRock(i).getGlobalBounds())) {
					h1.subHeart();
					s1.statekImmune();
				}
			}
			
			//gameover preperation
			if (h1.getStan() == 0) {
				savePlayer(&p[0], m1.getHighpoints());
				go1.setFlaga(1);
				go1.setGameover(sm1.getName(), sm1.getDiffPos(), m1.getPoints());
			}

			zegar.restart();
			window.clear();

			l1.drawLaser(window);
			s1.drawShip(window);
			r1.drawRocks(window);
			m1.drawMenu(window);
			h1.drawHeart(window);
			
			window.display();
		}
		//escmenu
		else if (em1.getFlaga() && zegar.getElapsedTime().asMilliseconds() > 100.f) {
			zegar.restart();
			if (event.type == sf::Event::TextEntered)
			{
				char znak = (event.text.unicode);
				if (znak == 13) {
					if (em1.getChoice()) em1.setFlaga(0);
					if (em1.getChoice() == 0) {
						savePlayer(&p[0], m1.getHighpoints());
						return 0;
					}
				}
			}
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Left)
				{
					em1.setChoice(0);
				}
				if (event.key.code == sf::Keyboard::Right)
				{
					em1.setChoice(1);
				}
			}
			em1.drawMenu(window);
			window.display();
		}
		//helpmenu
		else if (hm1.getFlaga() && zegar.getElapsedTime().asMilliseconds() > 100.f) {
			zegar.restart();
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::F1)
				{
					hm1.setFlaga(0);
				}
			}
			hm1.drawMenu(window);
			window.display();
		}
		//gameover
		else if (go1.getFlaga() && zegar.getElapsedTime().asMilliseconds() > 100.f) {
		zegar.restart();
		if (event.type == sf::Event::TextEntered)
		{
			char znak = (event.text.unicode);
			if (znak == 13) {
				if (go1.getChoice()) {
					go1.setFlaga(0);
					sm1.setFlaga(0);
					h1.resetHeart();
					p[0].points = 0;
					m1.resetPoints();
					m1.resetHigh();
					r1.resetRocks();
					s1.resetPosition();
				}
				if (go1.getChoice() == 0) {
					p[0].points = 0;
					return 0;
				}
			}
		}
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Left) go1.setChoice(0);
			if (event.key.code == sf::Keyboard::Right) go1.setChoice(1);
		}
		go1.drawMenu(window);
		window.display();
		}
	}
	return  0;
}