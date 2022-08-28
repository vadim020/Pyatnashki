#include <SFML/Graphics.hpp>

using namespace sf;


RenderWindow window(VideoMode(1000, 600), "SFML Works!");

class Boolean {
public:
	bool stop = true, play = false, pusk = false;
	int puskgame = 1000;
};

Boolean boolean;

class img {
public:
	void im() {
		Texture	menuTexture1, menuTexture2;
		menuTexture1.loadFromFile("images/start1.png");
		menuTexture2.loadFromFile("images/vu.png");
		Sprite menu1(menuTexture1), menu2(menuTexture2);
		menu1.setPosition(450, 200);
		menu2.setPosition(410, 350);
		window.draw(menu1);
		window.draw(menu2);
	}
};

img Img;

void menu1(RenderWindow & window) {
	Font font;
	font.loadFromFile("static/Montserrat-Light.ttf");

	Text text("you won game Pyatnashki  press  start to start game ", font, 20);
	text.setPosition(300, 65);
	bool isMenu = true;
	int menuNum = 0;;
	while (isMenu) {
		menuNum = 0;
		window.clear(Color(129, 181, 221));
		if (IntRect(450, 200, 550, 300).contains(Mouse::getPosition(window))) menuNum = 1;
		if (IntRect(410, 350, 570, 450).contains(Mouse::getPosition(window))) menuNum = 2;
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			if (Mouse::isButtonPressed(Mouse::Left)) {
				Vector2i pos = Mouse::getPosition(window);
				if (menuNum == 1) { isMenu = false; boolean.pusk = true; }
				if (menuNum == 2) { window.close(); isMenu = false; }
			}
		}
		Img.im();
		window.draw(text);
		window.display();
	}
};

class Game {
public:
	Sprite s[17];
	int w = 150;
	int grid[6][6] = { 0 };
	int n = 0;

	int b = 16, x = 0, y = 0;
	void up() {
		grid[1][1] = 3;
		grid[1][2] = 4;
		grid[1][3] = 2;
		grid[1][4] = 1;
	}
	Game(Texture&image) {
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++) {
				n++;
				s[n].setTexture(image);
				s[n].setTextureRect(IntRect(i* w, j* w, w, w));
				grid[i + 1][j + 1] = n;
			}
	}

	void update() {
		int dx = 0;
		int dy = 0;


		if (grid[x + 1][y] == b) {
			dx = 1;
			dy = 0;
		};
		if (grid[x - 1][y] == b) {
			dx = -1;
			dy = 0;
		}
		if (grid[x][y + 1] == b) {
			dx = 0;
			dy = 1;
		}
		if (grid[x][y - 1] == b) {
			dx = 0;
			dy = -1;
		}

		n = grid[x][y];
		grid[x][y] = b;
		grid[x + dx][y + dy] = n;

		if (grid[1][1] == 1) {

			up();

			menu1(window);

			boolean.play = false;
			boolean.stop = true;

			boolean.puskgame = 1000;
		}
	}
};

void menu(RenderWindow & window) {
	Font font;
	font.loadFromFile("static/Montserrat-Light.ttf");
	Text text("game Pyatnashki ", font, 40);
	text.setPosition(365, 65);

	bool isMenu = true;
	int menuNum = 0;
	while (isMenu) {
		menuNum = 0;
		window.clear(Color(129, 181, 221));
		if (IntRect(450, 200, 550, 300).contains(Mouse::getPosition(window))) menuNum = 1;
		if (IntRect(410, 350, 570, 450).contains(Mouse::getPosition(window))) menuNum = 2;
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			if (Mouse::isButtonPressed(Mouse::Left)) {
				Vector2i pos = Mouse::getPosition(window);
				if (menuNum == 1) { isMenu = false; boolean.pusk = true; }
				if (menuNum == 2) { window.close(); isMenu = false; }
			}
		}

		Img.im();
		window.draw(text);
		window.display();
	}
};
int main()
{

	Texture t;

	t.loadFromFile("images/kj.png");
	Game game(t);
	game.up();
	menu(window);

	Sprite picture(t);

	picture.setScale(0.3, 0.3);
	picture.setPosition(700, 130);

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			if (event.type == Event::MouseButtonPressed)
				if (event.key.code == Mouse::Left) {
					Vector2i pos = Mouse::getPosition(window);
					if (boolean.play) {
						game.x = pos.x / game.w + 1;
						game.y = pos.y / game.w + 1;
					}
					else if (boolean.stop) {
						if (pos.x >= 750 && pos.x <= 900 &&
							pos.y >= 400 && pos.y <= 465) {
							boolean.stop = false;
							boolean.pusk = true;

							window.setFramerateLimit(0);
						}
					}
				}
		}
		if (boolean.pusk) {
			game.x = rand() % 4 + 1;
			game.y = rand() % 4 + 1;

			boolean.puskgame--;
		}
		else if (boolean.play) {
			window.setFramerateLimit(60);
		}
		if (boolean.puskgame == 0) {
			boolean.pusk = false;
			boolean.play = true;
		}
		window.clear(Color::White);
		game.update();
		window.draw(picture);
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++) {
				game.n = game.grid[i + 1][j + 1];
				game.s[game.n].setPosition(i* game.w, j* game.w);
				window.draw(game.s[game.n]);
			}
		window.display();
	}
	return 0;
};
