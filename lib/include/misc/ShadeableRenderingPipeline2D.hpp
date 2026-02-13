#include <DGM/classes/Window.hpp>
#include <SFML/Graphics.hpp>

class [[nodiscard]] ShadeableRenderingPipeline2D final
{
public:
    ShadeableRenderingPipeline2D(
        const sf::Texture& texture, const sf::Shader& shader);

public:
    void clear()
    {
        currentVertexIdx = 0;
    }

    void addFace(
        const sf::Vector2f& origin,
        const sf::Angle& rotation,
        const sf::FloatRect& textureRect);

    void renderTo(dgm::Window& window)
    {
        window.getSfmlWindowContext().draw(vertices, renderStates);
    }

private:
    sf::VertexArray vertices;
    size_t currentVertexIdx = 0;
    sf::RenderStates renderStates;
};
