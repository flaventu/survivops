#pragma once
#include "const.hpp"
#include "maps.hpp"

class TileMap : public sf::Drawable, public sf::Transformable
{

    private:
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        sf::VertexArray m_vertices;
        sf::Texture m_tileset;
    public:
        bool load(const std::filesystem::path&, sf::Vector2u, const int*, unsigned int, unsigned int);

   
};
