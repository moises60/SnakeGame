#include "Game.h"
#include <sstream>

Game::Game() : window(sf::VideoMode(800, 600), "Snake Game"), score(0), lives(3), mode(CLASSIC), isGameOver(false), inMainMenu(true) {
    window.setFramerateLimit(7); // Ajustar la velocidad de la serpiente.

    if (!font.loadFromFile("assets/font.ttf")) {
        // Esta línea la puse porque tuve un error al ejecutar el juego ya que no localizaba font.ttf.
        //Si se coloca así no hay ningún problema, aunque el archivo ejecutable se cree en la carpeta bin.
        exit(EXIT_FAILURE);
    }

    loadMainMenu();
}

void Game::run() {
    while (window.isOpen()) {
        processEvents();
        if (!inMainMenu && !isGameOver) {
            update();
        }
        render();
    }
}

void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();

        // Manejo de la entrada del usuario en el menú principal
        if (inMainMenu) {
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Num1) {
                    mode = EASY;
                    lives = 5;
                    inMainMenu = false;
                    resetGame();
                } else if (event.key.code == sf::Keyboard::Num2) {
                    mode = CLASSIC;
                    lives = 3;
                    inMainMenu = false;
                    resetGame();
                } else if (event.key.code == sf::Keyboard::Num3) {
                    mode = TIMETRIAL;
                    lives = 2;
                    timeLimit = sf::seconds(120);
                    gameClock.restart();
                    inMainMenu = false;
                    resetGame();
                }
            }
        } else if (isGameOver) {
            // Permitir reiniciar el juego al presionar una tecla
            if (event.type == sf::Event::KeyPressed) {
                inMainMenu = true;
                isGameOver = false;
            }
        } else {
            snake.handleInput(event);
        }
    }
}

void Game::update() {
    snake.move();
    handleCollisions();

    // Actualizar el tiempo en el modo contrarreloj
    if (mode == TIMETRIAL) {
        elapsedTime = gameClock.getElapsedTime();
        if (elapsedTime >= timeLimit) {
            isGameOver = true;
        } else {
            int secondsLeft = static_cast<int>(timeLimit.asSeconds() - elapsedTime.asSeconds());
            timerText.setString("Tiempo: " + std::to_string(secondsLeft) + "s");
        }
    }
}

void Game::render() {
    window.clear();

    if (inMainMenu) {
        // Renderizar el menú principal
        sf::Text title("Snake Game", font, 50);
        title.setPosition(250, 100);
        title.setFillColor(sf::Color::White);

        sf::Text options("Selecciona un modo de juego:\n\n1. Facil (5 vidas)\n2. Clasico (3 vidas)\n3. Contrarreloj (2 vidas, 2 minutos)", font, 24);
        options.setPosition(200, 200);
        options.setFillColor(sf::Color::White);

        window.draw(title);
        window.draw(options);
    } else if (isGameOver) {
        // Renderizar pantalla de fin del juego
        sf::Text gameOverText("¡Juego Terminado!", font, 50);
        gameOverText.setPosition(200, 200);
        gameOverText.setFillColor(sf::Color::Red);

        sf::Text finalScore("Puntaje Final: " + std::to_string(score), font, 30);
        finalScore.setPosition(250, 300);
        finalScore.setFillColor(sf::Color::White);

        sf::Text restartText("Presiona cualquier tecla para volver al menú principal", font, 20);
        restartText.setPosition(150, 400);
        restartText.setFillColor(sf::Color::White);

        window.draw(gameOverText);
        window.draw(finalScore);
        window.draw(restartText);
    } else {
        // Renderizar el juego
        window.draw(snake);
        window.draw(food);
        for (const auto& obstacle : obstacles) {
            window.draw(obstacle);
        }
        window.draw(scoreText);
        window.draw(livesText);
        if (mode == TIMETRIAL) {
            window.draw(timerText);
        }
    }

    window.display();
}

void Game::handleCollisions() {
    // Colisión con la comida
    if (snake.checkCollision(food.getPosition())) {
        snake.grow();
        food.respawn();
        score += 10;
        scoreText.setString("Puntaje: " + std::to_string(score));

        // Animación al comer (se puede mejorar)
        // snake.increaseSpeed(); // Opcional si quieres aumentar la velocidad al comer
    }

    // Colisión con obstáculos
    for (const auto& obstacle : obstacles) {
        if (snake.checkCollision(obstacle.getPosition())) {
            lives--;
            livesText.setString("Vidas: " + std::to_string(lives));
            snake.reset();
            if (lives <= 0) {
                isGameOver = true;
            }
            break;
        }
    }

    // Colisión consigo misma
    if (snake.checkSelfCollision()) {
        lives--;
        livesText.setString("Vidas: " + std::to_string(lives));
        snake.reset();
        if (lives <= 0) {
            isGameOver = true;
        }
    }
}

void Game::loadMainMenu() {
    // Cargar elementos del menú principal
}

void Game::resetGame() {
    // Reiniciar variables del juego
    score = 0;
    isGameOver = false;
    snake.reset();
    food.respawn();

    // Crear obstáculos aleatorios
    obstacles.clear();
    int numObstacles = 5;
    for (int i = 0; i < numObstacles; ++i) {
        Obstacle obstacle;
        obstacles.push_back(obstacle);
    }

    // Configurar textos
    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(10, 10);
    scoreText.setString("Puntaje: 0");

    livesText.setFont(font);
    livesText.setCharacterSize(24);
    livesText.setFillColor(sf::Color::White);
    livesText.setPosition(10, 40);
    livesText.setString("Vidas: " + std::to_string(lives));

    if (mode == TIMETRIAL) {
        timerText.setFont(font);
        timerText.setCharacterSize(24);
        timerText.setFillColor(sf::Color::White);
        timerText.setPosition(10, 70);
        timerText.setString("Tiempo: 120s");
        gameClock.restart();
    }
}
