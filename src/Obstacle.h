#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <SFML/Graphics.hpp>

/**
 * @class Obstacle
 * @brief Representa un obstáculo en el campo de juego que la serpiente debe evitar.
 * 
 * Atributos:
 * - shape: Forma gráfica del obstáculo.
 */
class Obstacle : public sf::Drawable {
public:
    Obstacle();
    sf::Vector2f getPosition() const;

private:
    /**
     * @brief Dibuja el obstáculo en el render target.
     * @param target Referencia al render target.
     * @param states Estados de renderizado.
     */
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    sf::RectangleShape shape;
};

#endif // OBSTACLE_H
