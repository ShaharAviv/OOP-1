#include "EditorControler.h"


EditorControler::EditorControler()
	:m_gameEditor(Editor(1, 1))
{

	if (!m_gameEditor.loadFromFile("level.txt"))
	{
		int arr[2] = { 0 };
		openWin2(arr);
		m_gameEditor.setSize(arr[0], arr[1]);
	}

}

void EditorControler::run()
{
	sf::RenderWindow window(sf::VideoMode(0, 0), "Editor",
		sf::Style::Fullscreen);
	int arr[2] = { 0,0 };

	while (window.isOpen())
		openWin1(window, arr);

}
void EditorControler::openAsk(sf::RenderWindow & window)
{
	sf::RenderWindow ask(sf::VideoMode(400, 150), "Are you sure?", sf::Style::Close);
	sf::Event event;
	sf::Font font;
	font.loadFromFile("font.ttf");
	sf::Text ansY("Yes", font, 40);
	ansY.setPosition(75, 60.f);
	sf::Text ansN("No", font, 40);
	ansN.setPosition(250, 60.f);
	ansY.setFillColor(sf::Color::Red);
	ansN.setFillColor(sf::Color::White);

	while (ask.isOpen())
	{
		while (ask.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::KeyPressed:
				if (event.key.code == (sf::Keyboard::Left))
				{
					ansY.setFillColor(sf::Color::Red);
					ansN.setFillColor(sf::Color::White);
				}
				if (event.key.code == (sf::Keyboard::Right))
				{
					ansN.setFillColor(sf::Color::Red);
					ansY.setFillColor(sf::Color::White);
				}
				if (event.key.code == (sf::Keyboard::Return))
				{
					if (ansY.getFillColor() == sf::Color::Red)
					{
						ask.close();
						window.close();
					}
					if (ansN.getFillColor() == sf::Color::Red)
					{
						ask.close();
					}
				}
			}
		}

		ask.draw(ansY);
		ask.draw(ansN);
		ask.display();
		ask.clear();
	}

}

void EditorControler::openWin1(sf::RenderWindow & window, int arr[])
{
	sf::RenderWindow window2;
	sf::Event event;
	sf::Vector2f Acurr_pos;

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				openAsk(window);
				break;

			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Escape)
					openAsk(window);
				break;
			}
		}

		Acurr_pos = (sf::Vector2f) sf::Mouse::getPosition(window);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			m_gameEditor.PlayButton((sf::Vector2f)Acurr_pos);

			if (m_gameEditor.reset())
			{
				m_gameEditor.drawE(window);
				window.display();
				int arr[2] = { 0 };
				openWin2(arr);
				m_gameEditor.setSize(arr[0], arr[1]);
				return;
			}

			m_gameEditor.drawE(window);
		}
		else
		{
			m_gameEditor.drawE(window);
			m_gameEditor.ShowButton((sf::Vector2f)Acurr_pos, window);
		}

		window.display();
		window.clear();
	}
}

void EditorControler::openWin2(int numbers[2])
{
	sf::RenderWindow window2(sf::VideoMode(500, 200), "message", sf::Style::Titlebar);
	sf::Event event;
	sf::Font font;
	font.loadFromFile("font.ttf");

	sf::Text text[2];
	text[0].setFont(font);
	text[0].setCharacterSize(40);
	text[0].setFillColor(sf::Color::White);
	text[0].setPosition(sf::Vector2f(85, 90));

	text[1] = text[0];
	text[1].setPosition(sf::Vector2f(255, 90));

	std::string msgWelcome = "Press size of the screen:\n\n\t\t\t       X";
	sf::Text startMessage(msgWelcome, font, 40);
	startMessage.setFillColor(sf::Color::White);

	int i = 0;
	while (window2.isOpen())
	{
		while (window2.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::KeyPressed:
				int key = (event.key.code);

				if (key == sf::Keyboard::Return)
				{
					if (numbers[i] != 0)
						i++;
					if (i == 2) {
						window2.close();
						return;
					}
				}
				else if (key >= sf::Keyboard::Num0 &&
					key <= sf::Keyboard::Num9)
				{
					numbers[i] = numbers[i] * 10 + (key - 26);
				}
				else if (key >= sf::Keyboard::Numpad0 &&
					key <= sf::Keyboard::Numpad9)
				{
					numbers[i] = numbers[i] * 10 + (key - 75);
				}

				else if (key == sf::Keyboard::BackSpace)
					numbers[i] = numbers[i] / 10;
			}
		}

		if (numbers[i] > 40)
			numbers[i] = 40;

		std::ostringstream ss;       //string buffer to convert numbers to string
		ss << numbers[i];			        // put float into string buffer
		text[i].setString(ss.str()); /// converts the string buffer into a regular string

		window2.draw(startMessage);

		for (int k = 0; k < i; k++)
			window2.draw(text[k]);
		if (numbers[i] != 0)
			window2.draw(text[i]);

		window2.display();
		window2.clear();
	}
}

int EditorControler::file_size(std::string filename)
{
	std::ifstream mySource;

	mySource.open(filename, std::ios_base::binary);
	mySource.seekg(0, std::ios_base::end);
	int size = (int)mySource.tellg();
	mySource.close();

	return size;
}

EditorControler::~EditorControler()
{
}
