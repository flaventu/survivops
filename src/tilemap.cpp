#include "tilemap.hpp"
#include <fstream>
#include <sstream>
using namespace sf;

bool TileMap::load(const std::filesystem::path& tileset, const std::filesystem::path& map, const int solid)
{

    // Load the tileset texture
    if (!m_tileset.loadFromFile(tileset))
        return false;
        
    if (!loadMapFromCSV(map))
        return false; // If the map cannot be loaded, return false
        
    width = static_cast<unsigned int>(m_tiles.size()); // Number of columns in the map
    height = static_cast<unsigned int>(m_tiles[0].size()); // Number of rows in the map
    mapSize = sf::Vector2f(width * TILE_SIZE, height * TILE_SIZE); // Size of the map in pixels
    solidTileNum = solid; // Set the solid tile number
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
        if (i < 0 || i >= static_cast<int>(m_tiles.size())) continue; // Check if the tile index is valid
        for (int j = startY; j < endY; ++j) {

            if (j < 0 || j >= static_cast<int>(m_tiles[i].size())) continue; // Check if the tile index is valid

            // Get the tile number from the map data
            int tileNumber = m_tiles[i][j];
            if (tileNumber < 0) continue; // Skip empty tiles

            visibleObjects({i, j}); // Check if the tile has objects

            float tu = tileNumber % (m_tileset.getSize().x / TILE_SIZE); // Column index in the tileset
            float tv = tileNumber / (m_tileset.getSize().x / TILE_SIZE); // Row index in the tileset

            // Calculate the position of the tile in the world
            float x = static_cast<float>(i * TILE_SIZE) - mapSize.x / 2.f + TILE_SIZE / 2.f;
            float y = static_cast<float>(j * TILE_SIZE) - mapSize.y / 2.f + TILE_SIZE / 2.f;

            // Create two triangles for each tile
            sf::Vertex triangles[6];

            // casting to float
            float tilesize = static_cast<float>(TILE_SIZE);

            // Set the position and texture coordinates for each vertex
            triangles[0].position = {x - tilesize / 2.f, y - tilesize / 2.f};
            triangles[1].position = {x + tilesize / 2.f, y - tilesize / 2.f};
            triangles[2].position = {x - tilesize / 2.f, y + tilesize / 2.f};
            triangles[3].position = {x - tilesize / 2.f, y + tilesize / 2.f};
            triangles[4].position = {x + tilesize / 2.f, y - tilesize / 2.f};
            triangles[5].position = {x + tilesize / 2.f, y + tilesize / 2.f};

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

    drawObjects(target); // Draw the objects on the map
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
            if(containsObjects({static_cast<int>(leftcol), static_cast<int>(toprow)}))
                pickObject({static_cast<int>(leftcol), static_cast<int>(toprow)}); // Pick up the object if it is present
            if(containsObjects({static_cast<int>(rightcol), static_cast<int>(toprow)}))
                pickObject({static_cast<int>(rightcol), static_cast<int>(toprow)}); // Pick up the object if it is present
            break;
        case DOWN:
            bottomrow = (bottomy + speed + (mapSize.y / 2.0f)) / TILE_SIZE;
            if(bottomrow >= height) return true; // Collision detected with the bottom edge of the map
            tileNum1 = m_tiles[static_cast<int>(leftcol)][static_cast<int>(bottomrow)];
            tileNum2 = m_tiles[static_cast<int>(rightcol)][static_cast<int>(bottomrow)];
            if (isSolid(tileNum1) || isSolid(tileNum2))
                return true; // Collision detected with solid tile
            if(containsObjects({static_cast<int>(leftcol), static_cast<int>(bottomrow)}))
                pickObject({static_cast<int>(leftcol), static_cast<int>(bottomrow)}); // Pick up the object if it is present
            if(containsObjects({static_cast<int>(rightcol), static_cast<int>(bottomrow)}))
                pickObject({static_cast<int>(rightcol), static_cast<int>(bottomrow)}); // Pick up the object if it is present
            break;
        case LEFT:
            leftcol = (leftx - speed + (mapSize.x / 2.0f)) / TILE_SIZE;
            if(leftcol < 0) return true; // Collision detected with the left edge of the map
            tileNum1 = m_tiles[static_cast<int>(leftcol)][static_cast<int>(toprow)];
            tileNum2 = m_tiles[static_cast<int>(leftcol)][static_cast<int>(bottomrow)];
            if (isSolid(tileNum1) || isSolid(tileNum2))
                return true; // Collision detected with solid tile
            if(containsObjects({static_cast<int>(leftcol), static_cast<int>(toprow)}))
                pickObject({static_cast<int>(leftcol), static_cast<int>(toprow)}); // Pick up the object if it is present
            if(containsObjects({static_cast<int>(leftcol), static_cast<int>(bottomrow)}))
                pickObject({static_cast<int>(leftcol), static_cast<int>(bottomrow)}); // Pick up the object if it is present
            break;
        case RIGHT:
            rightcol = (rightx + speed + (mapSize.x / 2.0f)) / TILE_SIZE;
            if(rightcol >= width) return true; // Collision detected with the right edge of the map
            tileNum1 = m_tiles[static_cast<int>(rightcol)][static_cast<int>(toprow)];
            tileNum2 = m_tiles[static_cast<int>(rightcol)][static_cast<int>(bottomrow)];
            if (isSolid(tileNum1) || isSolid(tileNum2))
                return true; // Collision detected with solid tile
            if(containsObjects({static_cast<int>(rightcol), static_cast<int>(toprow)}))
                pickObject({static_cast<int>(rightcol), static_cast<int>(toprow)}); // Pick up the object if it is present
            if(containsObjects({static_cast<int>(rightcol), static_cast<int>(bottomrow)}))
                pickObject({static_cast<int>(rightcol), static_cast<int>(bottomrow)}); // Pick up the object if it is present
            break;
    }
    return false; // No collision detected
}

bool TileMap::loadObjects(const std::filesystem::path& filePath)
{
    std::ifstream file(filePath);
    if (!file.is_open())
        return false; // If the file cannot be opened, return false

    std::string line;
    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string cell;

        // Leggi posizione X, posizione Y, larghezza, altezza e percorso della texture
        float posX, posY;
        std::string name,texturePath;

        std::getline(ss, cell, ',');
        posX = std::stof(cell);
        std::getline(ss, cell, ',');
        posY = std::stof(cell);
        std::getline(ss, cell, ',');
        name = cell;
        std::getline(ss, cell, ',');
        texturePath = cell;

        sf::Texture* texture = new sf::Texture();
        if (!texture->loadFromFile(texturePath))
        {
            delete texture; // Libera la memoria se la texture non può essere caricata
            continue;
        }
        // Crea l'oggetto e aggiungilo al vettore
        Object* object = new Object(*texture, {((posX * TILE_SIZE) - (mapSize.x / 2.f)), ((posY * TILE_SIZE) - (mapSize.y / 2.f))}, {TILE_SIZE, TILE_SIZE}, name);
        object->setTiles({posX, posY}); // Set the tile coordinates of the object
        m_objects[{posX, posY}] = object;
    }

    file.close();
    return true;
}

void TileMap::drawObjects(sf::RenderTarget& target) const
{
    for (const auto& object : m_objects)
    {
        if (!object.second->isVisible()) continue; // Skip not visible objects
        target.draw(object.second->getShape()); // Draw each object in the vector
        // reset the visibility of the object to false
        object.second->setVisible(false); // Reset the visibility of the object to false
    }
}

void TileMap::visibleObjects(const Vector2i tileNums) const
{
    if(!containsObjects(tileNums)) return; // If there are no objects in the tile, return
    m_objects.at({tileNums.x, tileNums.y})->setVisible(true); // Set the object to visible
}

void TileMap::pickObject(const Vector2i tileNums)
{
    Object* object = m_objects.at({tileNums.x, tileNums.y}); // Get the object from the map
    pickableObjects.push_back(object); // Add the object to the pickable objects vector
    m_objects.erase({tileNums.x, tileNums.y}); // Remove the object from the map
}