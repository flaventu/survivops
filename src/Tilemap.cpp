#include "Tilemap.hpp"
#include <fstream>
#include <sstream>
#include <cmath>
using namespace std;
using namespace sf;

TileMap::TileMap(const filesystem::path& texture, const filesystem::path& map, const int solid) : m_tileset(texture), solidTileNum(solid)
{

    // Load the map from the CSV file
    if (!loadMapFromCSV(map))
        throw new Exception("Failed to load map from CSV file");

    // Map dimensions
    width = m_tiles.size();
    height = m_tiles[0].size();
    mapSize = {width * TILE_SIZE, height * TILE_SIZE};

    m_vertices.setPrimitiveType(sf::PrimitiveType::Triangles);
}

void TileMap::update(const View& view)
{

    Vector2f currentPosition = view.getCenter();

    if(currentPosition == lastPosition)
        return; // No need to update if the position hasn't changed

    lastPosition = currentPosition;

    m_vertices.resize(TileMap::maxVertexCount);

    // Calculate the visible area of the map based on the view
    sf::Vector2f topLeft(currentPosition - view.getSize() / 2.f);
    sf::Vector2f bottomRight(currentPosition + view.getSize() / 2.f);

    // Calculate the start and end tile indices based on the visible area
    int startX = max(0, static_cast<int>(floor((topLeft.x + mapSize.x / 2) / TILE_SIZE))-1);
    int startY = max(0, static_cast<int>(floor((topLeft.y + mapSize.y / 2) / TILE_SIZE))-1);
    int endX = min(width, static_cast<int>(ceil((bottomRight.x + mapSize.x / 2) / TILE_SIZE))+1);
    int endY = min(height, static_cast<int>(ceil((bottomRight.y + mapSize.y / 2) / TILE_SIZE))+1);

    int vertexIndex = 0;

    // Loop through the visible tiles and create the vertex array
    for (int i = startX; i < endX; ++i) {

        if (i >= width) continue; // Check if the tile index is valid

        for (int j = startY; j < endY; ++j) {

            if (j < 0) continue; // Check if the tile index is valid

            // Get the tile number from the map data
            int tileNumber = m_tiles[i][j];
            if (tileNumber < 0) continue; // Skip empty tiles

            // Calculate the column and row in the tileset
            int col = tileNumber % (m_tileset.getSize().x / TILE_SIZE);
            int row = static_cast<int>(floor(tileNumber / (m_tileset.getSize().x / TILE_SIZE)));

            // Calculate the position of the tile in the world
            int x = (i * TILE_SIZE) - mapSize.x / 2 + TILE_SIZE / 2;
            int y = (j * TILE_SIZE) - mapSize.y / 2 + TILE_SIZE / 2;

            // Create two triangles for each tile
            sf::Vertex* triangles = &m_vertices[vertexIndex];

            // Set the position and texture coordinates for each vertex
            triangles[0].position = {x - TILE_SIZE / 2.f, y - TILE_SIZE / 2.f};
            triangles[1].position = {x + TILE_SIZE / 2.f, y - TILE_SIZE / 2.f};
            triangles[2].position = {x - TILE_SIZE / 2.f, y + TILE_SIZE / 2.f};
            triangles[3].position = {x - TILE_SIZE / 2.f, y + TILE_SIZE / 2.f};
            triangles[4].position = {x + TILE_SIZE / 2.f, y - TILE_SIZE / 2.f};
            triangles[5].position = {x + TILE_SIZE / 2.f, y + TILE_SIZE / 2.f};

            triangles[0].texCoords = {static_cast<float>(col * TILE_SIZE), static_cast<float>(row * TILE_SIZE)};
            triangles[1].texCoords = {(col + 1.f) * TILE_SIZE, static_cast<float>(row * TILE_SIZE)};
            triangles[2].texCoords = {static_cast<float>(col * TILE_SIZE), static_cast<float>((row + 1.f) * TILE_SIZE)};
            triangles[3].texCoords = {static_cast<float>(col * TILE_SIZE), static_cast<float>((row + 1.f) * TILE_SIZE)};
            triangles[4].texCoords = {(col + 1.f) * TILE_SIZE, static_cast<float>(row * TILE_SIZE)};
            triangles[5].texCoords = {(col + 1.f) * TILE_SIZE, (row + 1.f) * TILE_SIZE};

            vertexIndex += 6;
        }
    }

    // Resize the vertex array to the actual number of vertices (to avoid drawing unused vertices)
    m_vertices.resize(vertexIndex);

}



void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const {

    states.transform *= getTransform();
    states.texture = &m_tileset;
    target.draw(m_vertices, states);

}

bool TileMap::loadMapFromCSV(const std::filesystem::path& filePath)
{

    ifstream file(filePath);

    if (!file.is_open())
        return false;

    // Read the file line by line
    string line;
    while (getline(file, line))
    {
        // For each line, create a vector of integers
        vector<int> row;
        stringstream ss(line);
        string cell;

        // Split the line by commas and convert each cell to an integer
        while (getline(ss, cell, ','))
            row.push_back(stoi(cell));

        m_tiles.push_back(row); // Add the row vector to the tiles vector
    }

    file.close();
    return true;
}

bool TileMap::collision(const sf::FloatRect& rect, const DIRECTIONS d, const float speed)
{
    float leftx = rect.position.x;
    float rightx = rect.position.x + HITBOX_SIZE;
    float topy = rect.position.y;
    float bottomy = rect.position.y + HITBOX_SIZE;

    float leftcol = (leftx  + (mapSize.x / 2.f)) / TILE_SIZE;
    float rightcol = (rightx + (mapSize.x / 2.f)) / TILE_SIZE;
    float toprow = (topy   + (mapSize.y / 2.f)) / TILE_SIZE;
    float bottomrow = (bottomy + (mapSize.y / 2.f)) / TILE_SIZE;

    int tileNum1, tileNum2;

    switch (d)
    {
        case UP:
            toprow = (topy - speed + (mapSize.y / 2.0f)) / TILE_SIZE;
            if(toprow < 0) return true; // Collision detected with the top edge of the map
            tileNum1 = m_tiles[static_cast<int>(leftcol)][static_cast<int>(toprow)];
            tileNum2 = m_tiles[static_cast<int>(rightcol)][static_cast<int>(toprow)];
            if (isSolid(tileNum1) || isSolid(tileNum2))
                return true; // Collision detected with solid tile
            break;
        case DOWN:
            bottomrow = (bottomy + speed + (mapSize.y / 2.0f)) / TILE_SIZE;
            if(bottomrow >= height) return true; // Collision detected with the bottom edge of the map
            tileNum1 = m_tiles[static_cast<int>(leftcol)][static_cast<int>(bottomrow)];
            tileNum2 = m_tiles[static_cast<int>(rightcol)][static_cast<int>(bottomrow)];
            if (isSolid(tileNum1) || isSolid(tileNum2))
                return true; // Collision detected with solid tile
            break;
        case LEFT:
            leftcol = (leftx - speed + (mapSize.x / 2.0f)) / TILE_SIZE;
            if(leftcol < 0) return true; // Collision detected with the left edge of the map
            tileNum1 = m_tiles[static_cast<int>(leftcol)][static_cast<int>(toprow)];
            tileNum2 = m_tiles[static_cast<int>(leftcol)][static_cast<int>(bottomrow)];
            if (isSolid(tileNum1) || isSolid(tileNum2))
                return true; // Collision detected with solid tile
            break;
        case RIGHT:
            rightcol = (rightx + speed + (mapSize.x / 2.0f)) / TILE_SIZE;
            if(rightcol >= width) return true; // Collision detected with the right edge of the map
            tileNum1 = m_tiles[static_cast<int>(rightcol)][static_cast<int>(toprow)];
            tileNum2 = m_tiles[static_cast<int>(rightcol)][static_cast<int>(bottomrow)];
            if (isSolid(tileNum1) || isSolid(tileNum2))
                return true; // Collision detected with solid tile
            break;
    }
    return false; // No collision detected
}