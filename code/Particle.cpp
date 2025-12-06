#include "Engine.h"
#include <SFML/Graphics.hpp>
#include "Particle-2.h"

using namespace sf;
using namespace std;

Particle::Particle(RenderTarget& target, int numPoints, Vector2i mouseClickPosition) : m_A(2, numPoints) {
    m_ttl = TTL;
    m_numPoints = numPoints;
    float randomNumber = static_cast<float>(rand()) / (RAND_MAX);

    m_radiansPerSec = static_cast<float>(randomNumber * M_PI);

    m_cartesianPlane.setCenter(0, 0);
    m_cartesianPlane.setSize(target.getSize().x, -1.0 * target.getSize().y);
    m_centerCoordinate = target.mapPixelToCoords(mouseClickPosition, m_cartesianPlane);

    m_vx = (rand() % 401 + 100) * (rand()% 2 ? 1 : -1);
    m_vy = rand() % 401 + 100;

    m_color1 = Color::White;
    m_color2 = Color(rand() % 256, rand() % 256, rand() % 256);

    double theta = (rand() / (double)RAND_MAX) * (M_PI / 2);
    double dTheta = (2 * M_PI) / (numPoints - 1);
    double r, dx, dy;

    for (int j = 0; j < numPoints; j++) {
        r = rand() % (80 - 20 + 1);

        dx = r * cos(theta);
        dy = r * sin(theta);

        m_A(0, j) = m_centerCoordinate.x + dx;
        m_A(1, j) = m_centerCoordinate.y + dy;
        theta += dTheta;
    }
}

void Particle::draw(RenderTarget& target, RenderStates states) const {
    VertexArray lines(TriangleFan, m_numPoints + 1);

    Vector2f center(target.mapCoordsToPixel(m_centerCoordinate, m_cartesianPlane));
    lines[0].position = center;
    lines[0].color = m_color1;

    for (int j = 1; j <= m_numPoints; j++) {
        lines[j].position = static_cast<Vector2f>(target.mapCoordsToPixel(Vector2f(m_A(0, j - 1), m_A(1, j - 1)), m_cartesianPlane));
        lines[j].color = m_color2;
    }
    target.draw(lines, states);
}

void Particle::update(float dt) {
    m_ttl -= dt;
    rotate(dt * m_radiansPerSec);
    scale(SCALE);

    float dx, dy;
    dx = m_vx * dt;
    m_vy -= G * dt;
    dy = m_vy * dt;

    translate(dx, dy);
}

void Particle::translate(double xShift, double yShift) {
    TranslationMatrix T(xShift, yShift, m_A.getCols());
    m_A = m_A + T;
    m_centerCoordinate.x += xShift;
    m_centerCoordinate.y += yShift;
}

void Particle::rotate(double theta) {
    Vector2f temp = m_centerCoordinate;
    translate(-m_centerCoordinate.x, -m_centerCoordinate.y);

    RotationMatrix R(theta);
    m_A = R * m_A;
    translate(temp.x, temp.y);
}


void Particle::scale(double c) {
    Vector2f temp = m_centerCoordinate;
    translate(-m_centerCoordinate.x, -m_centerCoordinate.y);
    ScalingMatrix S(c);
    m_A = S * m_A;
    translate(temp.x, temp.y);

}
