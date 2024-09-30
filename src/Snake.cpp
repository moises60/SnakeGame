#include "Snake.h"

Snake::Snake() {
    reset();
}

void Snake::reset() {
    body.clear();
    sf::RectangleShape segment(sf::Vector2f(20, 20));
    segment.setFillColor(sf::Color::Green);
    segment.setPosition(400, 300);
    body.push_back(segment);
    direction = sf::Vector2f(-20, 0);
    speed = 20;
    growing = false;
}

void Snake::handleInput(const sf::Event& event) {
    /**
     * @brief Maneja la entrada del usuario para cambiar la dirección de la serpiente.
     * @param event Evento de entrada del usuario.
     */
    if (event.type == sf::Event::KeyPressed) {
        if ((event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::W) && direction.y == 0) {
            direction = sf::Vector2f(0, -speed);
        } else if ((event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S) && direction.y == 0) {
            direction = sf::Vector2f(0, speed);
        } else if ((event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::A) && direction.x == 0) {
            direction = sf::Vector2f(-speed, 0);
        } else if ((event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::D) && direction.x == 0) {
            direction = sf::Vector2f(speed, 0);
        }
    }
}

void Snake::move() {
    /**
     * @brief Mueve la serpiente en la dirección actual, manejando el envolvimiento de pantalla.

     */
    sf::Vector2f newPosition = body.front().getPosition() + direction;

    // Envolver al salir de los límites
    if (newPosition.x < 0) newPosition.x = 780;
    else if (newPosition.x >= 800) newPosition.x = 0;
    if (newPosition.y < 0) newPosition.y = 580;
    else if (newPosition.y >= 600) newPosition.y = 0;

    sf::RectangleShape newSegment(sf::Vector2f(20, 20));
    newSegment.setFillColor(sf::Color::Green);
    newSegment.setPosition(newPosition);
    body.push_front(newSegment);

    if (!growing) {
        body.pop_back();
    } else {
        growing = false;
    }
}

void Snake::grow() {
    /**
     * @brief Indica que la serpiente debe crecer en el siguiente movimiento.
     */
    growing = true;
}

bool Snake::checkCollision(const sf::Vector2f& position) {
    /**
     * @brief Verifica si la cabeza de la serpiente colisiona con una posición dada.
     * @param position Posición a verificar (sf::Vector2f).
     * @return true si hay colisión, false en caso contrario.
     */
    return body.front().getPosition() == position;
}

bool Snake::checkSelfCollision() {
    /**
     * @brief Verifica si la serpiente colisiona consigo misma.
     * @return true si hay colisión, false en caso contrario.
     */
    auto headPos = body.front().getPosition();
    for (auto it = ++body.begin(); it != body.end(); ++it) {
        if (headPos == it->getPosition())
            return true;
    }
    return false;
}

void Snake::increaseSpeed() {
    /**
     * @brief Incrementa la velocidad de la serpiente.
     */
    // Implementación opcional para aumentar la velocidad
}

void Snake::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    /**
     * @brief Dibuja cada segmento de la serpiente en el render target.
     * @param target Referencia al render target.
     * @param states Estados de renderizado.
     */
    for (const auto& segment : body) {
        target.draw(segment, states);
    }
}
