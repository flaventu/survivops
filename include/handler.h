// Aspect ratio of 16:9 and the size of the desktop
inline constexpr float ASPECT = static_cast<float>(SCREEN_WIDTH)/static_cast<float>(SCREEN_HEIGHT);
const sf::VideoMode DESKTOP = sf::VideoMode::getDesktopMode();

// Function prototypes for handling events
void handle_resize (const sf::Event::Resized&, sf::RenderWindow&, sf::Vector2f&);
void handle_fullscreen(const sf::Event::KeyPressed& ,sf::RenderWindow&, bool&);