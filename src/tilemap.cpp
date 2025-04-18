#include "tilemap.hpp"
#include "const.hpp"
#include <fstream>
#include <sstream>
using namespace sf;

bool TileMap::load(const std::filesystem::path& tileset, const std::filesystem::path& map)
{

    // Load the tileset texture
    if (!m_tileset.loadFromFile(tileset))
        return false;
        
    if (!loadMapFromCSV(map))
        return false; // If the map cannot be loaded, return false
        
    width = static_cast<unsigned int>(m_tiles.size()); // Number of columns in the map
    height = static_cast<unsigned int>(m_tiles[0].size()); // Number of rows in the map
    mapSize = sf::Vector2f(width * TILE_SIZE, height * TILE_SIZE); // Size of the map in pixels
    return true;
}

void TileMap::update(const sf::View& view)
{
    m_vertices.clear();
    m_vertices.setPrimitiveType(sf::PrimitiveType::Triangles);

    // Calculate the visible area of the map based on the view
    sf::Vector2f topLeft(view.getCenter() - view.getSize() / 2.f);
    sf::Vector2f bottomRight(view.getCenter() + view.getSize() / 2.f);

    // Calculate the start and end tile indices based on the view's position 
    // for startX and startY, we subtract 1 to ensure we include the tile that is partially visible
    int startX = std::max(0, static_cast<int>((topLeft.x + mapSize.x / 2) / TILE_SIZE)) -1;
    int startY = std::max(0, static_cast<int>((topLeft.y + mapSize.y / 2) / TILE_SIZE)) -1;
    int endX = std::min(static_cast<int>(width), static_cast<int>((bottomRight.x + mapSize.x / 2) / TILE_SIZE) + 1);
    int endY = std::min(static_cast<int>(height), static_cast<int>((bottomRight.y + mapSize.y / 2) / TILE_SIZE) + 1);

    // Loop through the visible tiles and create the vertex array
    for (int i = startX; i < endX; ++i) {
        for (int j = startY; j < endY; ++j) {

            if (i < 0 || i >= static_cast<int>(m_tiles.size()) || j < 0 || j >= static_cast<int>(m_tiles[i].size()))
                continue;

            // 1D to 2D conversion
            int tileNumber = m_tiles[i][j];

            float tu = tileNumber % (m_tileset.getSize().x / TILE_SIZE); // Column index in the tileset
            float tv = tileNumber / (m_tileset.getSize().x / TILE_SIZE); // Row index in the tileset

            // Calculate the position of the tile in the world
            float x = static_cast<float>(i * TILE_SIZE) - mapSize.x / 2.f;
            float y = static_cast<float>(j * TILE_SIZE) - mapSize.y / 2.f;

            // Create two triangles for each tile
            sf::Vertex triangles[6];

            // casting to float
            float tilesize = static_cast<float>(TILE_SIZE);

            // Set the position and texture coordinates for each vertex
            triangles[0].position = {x, y};
            triangles[1].position = {x + tilesize, y};
            triangles[2].position = {x, y + tilesize};
            triangles[3].position = {x, y + tilesize};
            triangles[4].position = {x + tilesize, y};
            triangles[5].position = {x + tilesize, y + tilesize};

            triangles[0].texCoords = {tu * tilesize, tv * tilesize};
            triangles[1].texCoords = {(tu + 1.0f) * tilesize, tv * tilesize};
            triangles[2].texCoords = {tu * tilesize, (tv + 1.0f) * tilesize};
            triangles[3].texCoords = {tu * tilesize, (tv + 1.0f) * tilesize};
            triangles[4].texCoords = {(tu + 1.0f) * tilesize, tv * tilesize};
            triangles[5].texCoords = {(tu + 1.0f) * tilesize, (tv + 1.0f) * tilesize};

            // Append the triangles to the vertex array
            for (int k = 0; k < 6; ++k)
                m_vertices.append(triangles[k]);
        }
    }
}



void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    states.texture = &m_tileset;
    target.draw(m_vertices, states);
}

bool TileMap::loadMapFromCSV(const std::filesystem::path& filePath)
{

    std::ifstream file(filePath);

    if (!file.is_open())
        return false; // If the file cannot be opened, return false

    // Read the file line by line
    std::string line;
    while (std::getline(file, line))
    {
        // For each line, create a vector of integers
        std::vector<int> row;
        std::stringstream ss(line);
        std::string cell;

        // Split the line by commas and convert each cell to an integer
        while (std::getline(ss, cell, ','))
            row.push_back(std::stoi(cell)); // Convert string to int and add to the row vector

        m_tiles.push_back(row); // Add the row vector to the tiles vector
    }

    file.close();
    return true;
}
