#include "../include/Collision.hpp"
using namespace sf;


bool Collision::collision(const FloatRect& rect, const DIRECTIONS d, const float speed) const
{
    // Calculate the offset based on the direction
    Vector2f offset(0.f, 0.f);
    switch (d) {
        case UP: offset.y = -speed; break;
        case DOWN: offset.y = speed; break;
        case LEFT: offset.x = -speed; break;
        case RIGHT: offset.x = speed; break;
    }

    // Calculate new corners of the rectangle with applied offset
    Vector2f topLeft = { rect.position.x + offset.x, rect.position.y + offset.y };
    Vector2f bottomRight = { rect.position.x + HITBOX_SIZE + offset.x, rect.position.y + HITBOX_SIZE + offset.y };

    // Convert to tile coordinates
    Vector2i tileTopLeft = tilemap.positionToTile(topLeft);
    Vector2i tileBottomRight = tilemap.positionToTile(bottomRight);

    // Check for out-of-bounds tiles
    if (tileTopLeft.x < 0 || tileTopLeft.y < 0 || tileBottomRight.x >= tilemap.getWidth() || tileBottomRight.y >= tilemap.getHeight())
        return true;

    // Check collision based on direction
    switch (d)
    {
        case UP:
            return tilemap.isSolid({tileTopLeft.x, tileTopLeft.y}) || tilemap.isSolid({tileBottomRight.x, tileTopLeft.y});
        case DOWN:
            return tilemap.isSolid({tileTopLeft.x, tileBottomRight.y}) || tilemap.isSolid({tileBottomRight.x, tileBottomRight.y});
        case LEFT:
            return tilemap.isSolid({tileTopLeft.x, tileTopLeft.y}) || tilemap.isSolid({tileTopLeft.x, tileBottomRight.y});
        case RIGHT:
            return tilemap.isSolid({tileBottomRight.x, tileTopLeft.y}) || tilemap.isSolid({tileBottomRight.x, tileBottomRight.y});
    }

    return false;
}

bool Collision::collision(const FloatRect& rect, const DIRECTIONS d, const float speed, const Entity& entity) const
{
    
    // Calculate the offset based on the direction
    Vector2f offset(0.f, 0.f);
    switch (d) {
        case UP: offset.y = -speed; break;
        case DOWN: offset.y = speed; break;
        case LEFT: offset.x = -speed; break;
        case RIGHT: offset.x = speed; break;
    }

    // Calculate new corners of the rectangle with applied offset
    Vector2f topLeft = { rect.position.x + offset.x, rect.position.y + offset.y };
    Vector2f bottomRight = { rect.position.x + HITBOX_SIZE + offset.x, rect.position.y + HITBOX_SIZE + offset.y };

    // Convert to tile coordinates
    Vector2i tileTopLeft = tilemap.positionToTile(topLeft);
    Vector2i tileBottomRight = tilemap.positionToTile(bottomRight);

    FloatRect movedRect({ rect.position.x + offset.x, rect.position.y + offset.y},{ rect.size.x, rect.size.y });

    return (movedRect.findIntersection(entity.getHitbox())) ? true : false;
}

bool Collision::collision(const FloatRect& rect, const DIRECTIONS d, const float speed, const FloatRect& otherRect) const
{
    
    // Calculate the offset based on the direction
    Vector2f offset(0.f, 0.f);
    switch (d) {
        case UP: offset.y = -speed; break;
        case DOWN: offset.y = speed; break;
        case LEFT: offset.x = -speed; break;
        case RIGHT: offset.x = speed; break;
    }

    FloatRect movedRect({ rect.position.x + offset.x, rect.position.y + offset.y},{ rect.size.x, rect.size.y });
    return (movedRect.findIntersection(otherRect)) ? true : false;
}