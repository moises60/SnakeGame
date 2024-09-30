#include "Food.h"
#include <cstdlib>

Food::Food() {
    shape.setSize(sf::Vector2f(20, 20));
    shape.setFillColor(sf::Color::Red);
    respawn();
}

void Food::respawn() {
    /**
     * @brief Genera una nueva posición aleatoria para la comida dentro de los límites del juego.
     */
    int x = (std::rand() % 40) * 20;
    int y = (std::rand() % 30) * 20;
    shape.setPosition(x, y);
}

sf::Vector2f Food::getPosition() const {
    /**
     * @brief Obtiene la posición actual de la comida.

     * @return Posición de la comida (sf::Vector2f).
     */
    return shape.getPosition();
}

void Food::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    /**
     * @brief Dibuja la comida en el render target.
     * @param target Referencia al render target.
     * @param states Estados de renderizado.
     */
    target.draw(shape, states);
}
