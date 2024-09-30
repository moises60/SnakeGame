#ifndef SNAKE_H
#define SNAKE_H

#include <SFML/Graphics.hpp>
#include <list>

/**
 * @class Snake
 * @brief Representa a la serpiente en el juego, maneja su movimiento, crecimiento y colisiones.
 * 
 * Atributos:
 * - body: Lista de segmentos que componen el cuerpo de la serpiente.
 * - direction: Dirección actual de movimiento de la serpiente.
 * - speed: Velocidad actual de la serpiente.
 * - growing: Indica si la serpiente debe crecer en el siguiente movimiento.
 */
class Snake : public sf::Drawable {
public:
    Snake();
    void handleInput(const sf::Event& event);
    void move();
    void grow();
    bool checkCollision(const sf::Vector2f& position);
    bool checkSelfCollision();
    void reset();
    void increaseSpeed();

private:
    /**
     * @brief Dibuja la serpiente en el render target.
     * @param target Referencia al render target.
     * @param states Estados de renderizado.
     */
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    std::list<sf::RectangleShape> body;
    sf::Vector2f direction;
    int speed;
    bool growing;
};

#endif // SNAKE_H
