#include "tilemap.hpp"
using namespace sf;

bool TileMap::load(const std::filesystem::path &tileset, sf::Vector2u tileSize, const int *tiles, unsigned int width, unsigned int height)
{
    if (!m_tileset.loadFromFile(tileset))
        return false;

    m_vertices.setPrimitiveType(sf::PrimitiveType::Triangles);
    m_vertices.resize(width * height * 6);

    // Calcola l'offset per centrare la mappa su (0, 0)
    float offsetX = static_cast<float>(width * tileSize.x) / 2.0f;
    float offsetY = static_cast<float>(height * tileSize.y) / 2.0f;

    for (unsigned int i = 0; i < width; ++i)
    {
        for (unsigned int j = 0; j < height; ++j)
        {
            const int tileNumber = tiles[i + j * width];

            const int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
            const int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);

            sf::Vertex *triangles = &m_vertices[(i + j * width) * 6];

            float x = static_cast<float>(i * tileSize.x) - offsetX;
            float y = static_cast<float>(j * tileSize.y) - offsetY;

            triangles[0].position = sf::Vector2f(x, y);
            triangles[1].position = sf::Vector2f(x + tileSize.x, y);
            triangles[2].position = sf::Vector2f(x, y + tileSize.y);
            triangles[3].position = sf::Vector2f(x, y + tileSize.y);
            triangles[4].position = sf::Vector2f(x + tileSize.x, y);
            triangles[5].position = sf::Vector2f(x + tileSize.x, y + tileSize.y);

            triangles[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
            triangles[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
            triangles[2].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
            triangles[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
            triangles[4].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
            triangles[5].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
        }
    }

    return true;
}


void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    states.texture = &m_tileset;
    target.draw(m_vertices, states);
}
