#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "Snake.h"
#include "Food.h"
#include "Obstacle.h"

/**
 * @class Game
 * @brief Clase principal que gestiona el bucle del juego, los eventos, la lógica y el renderizado.
 * 
 * Atributos:
 * - window: Ventana principal del juego.
 * - snake: Objeto de la clase Snake que representa a la serpiente.
 * - food: Objeto de la clase Food que representa la comida.
 * - obstacles: Vector de obstáculos en el juego.
 * - font: Fuente utilizada para el texto en pantalla.
 * - scoreText: Texto que muestra el puntaje.
 * - livesText: Texto que muestra las vidas restantes.
 * - timerText: Texto que muestra el tiempo restante (modo contrarreloj).
 * - score: Puntaje actual del jugador.
 * - lives: Número de vidas restantes.
 * - mode: Modo de juego seleccionado.
 * - timeLimit: Límite de tiempo para el modo contrarreloj.
 * - elapsedTime: Tiempo transcurrido desde el inicio del juego.
 * - isGameOver: Indica si el juego ha terminado.
 * - inMainMenu: Indica si estamos en el menú principal.
 */
class Game {
public:
    Game();
    void run();

private:
    void processEvents();
    void update();
    void render();
    void handleCollisions();
    void loadMainMenu();
    void resetGame();

    sf::RenderWindow window;
    Snake snake;
    Food food;
    std::vector<Obstacle> obstacles;
    sf::Font font;
    sf::Text scoreText;
    sf::Text livesText;
    sf::Text timerText;
    int score;
    int lives;
    enum GameMode { EASY, CLASSIC, TIMETRIAL } mode;
    sf::Time timeLimit;
    sf::Clock gameClock;
    sf::Time elapsedTime;
    bool isGameOver;
    bool inMainMenu;
};

#endif // GAME_H
