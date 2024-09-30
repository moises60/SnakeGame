#include "Obstacle.h"
#include <cstdlib>

Obstacle::Obstacle() {
    /**
     * @brief Constructor que inicializa el obstáculo con una posición aleatoria y apariencia definida.
     */
    shape.setSize(sf::Vector2f(20, 20));
    shape.setFillColor(sf::Color::Blue);

    int x = (std::rand() % 40) * 20;
    int y = (std::rand() % 30) * 20;
    shape.setPosition(x, y);
}

sf::Vector2f Obstacle::getPosition() const {
    /**
     * @brief Obtiene la posición actual del obstáculo.
     * @return Posición del obstáculo (sf::Vector2f).
     */
    return shape.getPosition();
}

void Obstacle::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    /**
     * @brief Dibuja el obstáculo en el render target.
     * @param target Referencia al render target.
     * @param states Estados de renderizado.
     */
    target.draw(shape, states);
}
