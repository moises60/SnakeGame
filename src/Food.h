#ifndef FOOD_H
#define FOOD_H

#include <SFML/Graphics.hpp>

/**
 * @class Food
 * @brief Representa la comida que la serpiente debe recoger.
 * 
 * Atributos:
 * - shape: Forma gráfica de la comida.
 */
class Food : public sf::Drawable {
public:
    Food();
    void respawn();
    sf::Vector2f getPosition() const;

private:
    /**
     * @brief Dibuja la comida en el render target.
     * @param target Referencia al render target.
     * @param states Estados de renderizado.
     */
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    sf::RectangleShape shape;
};

#endif // FOOD_H
