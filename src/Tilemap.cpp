#include "../include/Tilemap.hpp"
using namespace std;
using namespace sf;

TileMap::TileMap(const filesystem::path& texture, const filesystem::path& map, const int solid, const bool fight) : m_tileset(texture), solidTileNum(solid), fightable(fight), spawnMonsterClock()
{

    // Load the map from the CSV file
    if (!loadMapFromCSV(map))
        throw new Exception("Failed to load map from CSV file");

    // Map dimensions
    width = m_tiles.size();
    height = m_tiles[0].size();
    mapSize = {width * TILE_SIZE, height * TILE_SIZE};

    m_vertices.setPrimitiveType(PrimitiveType::Triangles);
}

void TileMap::spawnEntity(Entity& npc) {

    // Spawn the NPC at a random non-solid tile position
    while(true) {

        // Get a random position (not on the edges)
        int x = 1 + rand() % (width - 2);
        int y = 1 + rand() % (height - 2);

        if(!isSolid({x, y})) {
            npc.setPosition(tileToPosition({x, y}));
            break;
        }
    }
}

void TileMap::update(const View& view)
{

    m_vertices.resize(TileMap::maxVertexCount);

    // Calculate the visible area of the map based on the view
    Vector2f topLeft(view.getCenter() - view.getSize() / 2.f);
    Vector2f bottomRight(view.getCenter() + view.getSize() / 2.f);

    // Calculate the corresponding tile indices
    Vector2i startTile = positionToTile(topLeft);
    Vector2i endTile = positionToTile(bottomRight);

    // Calculate the start and end tile indices based on the visible area
    int startX = max(0, startTile.x - 1);
    int startY = max(0, startTile.y - 1);
    int endX = min(width, endTile.x + 1);
    int endY = min(height, endTile.y + 1);

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
            Vector2f position = tileToPosition({i, j});
            int x = position.x;
            int y = position.y;

            // Create two triangles for each tile
            Vertex* triangles = &m_vertices[vertexIndex];

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



void TileMap::draw(RenderTarget& target, RenderStates states) const {

    states.transform *= getTransform();
    states.texture = &m_tileset;
    target.draw(m_vertices, states);

}

bool TileMap::loadMapFromCSV(const filesystem::path& filePath)
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

void TileMap::spawnMonster(const int playerLevel) {

    if(!fightable) return;

    if(entities.size() < MAX_MONSTERS && spawnMonsterClock.getElapsedTime().asSeconds() >= 5.f) {

        int roll = rand() % 100;

        switch (roll)
        {
        case 0 ... 49: // 50% chance to spawn a goblin
            entities.push_back(make_shared<Goblin>(chooseMonsterLevel(playerLevel)));
            spawnEntity(*entities.back());
            break;
        
        default:
            break;
        }
        
        spawnMonsterClock.restart();
    }
}

const int TileMap::chooseMonsterLevel(const int playerLevel) const {
    // Choose a monster level based on the player's level
    int level;
    int roll = rand() % 100;

    switch(roll) {
        case 0 ... 49: level = playerLevel; break; // 50% chance => spawn a monster of the same level
        case 50 ... 79: level = max(1, playerLevel - 1); break; // 30% chance => spawn a monster of level playerLevel - 1
        case 80 ... 89: level = playerLevel + 1; break; // 10% chance => spawn a monster of level playerLevel + 1
        default: level = playerLevel + 2; break; // 10% chance => spawn a monster of level playerLevel + 2
    }

    return level;
}