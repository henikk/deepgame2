#include <SFML/Graphics.hpp>
#include "dynamic_blur.hpp"

class Bloom
{
public:
    Bloom(sf::Vector2u render_size, int32_t iterations)
        : m_render_size(render_size)
        , m_iterations(iterations)
    {
        createTextures();
        createShaders();
    }

    sf::Sprite& apply(const sf::Texture& texture)
    {
        // Retrieve texture content and downscale it
        sf::Sprite sprite(texture);
        uint32_t current_buffer = 0;
        m_textures[current_buffer].draw(sprite);
        for (int32_t i(0); i < m_iterations; i += 2) {
            current_buffer = blurPass(current_buffer, i);
        }
        for (int32_t i(m_iterations); i >= 0; i -= 3) {
            current_buffer = blurPass(current_buffer, i);
        }
        m_textures[current_buffer].display();
        m_result.setTexture(m_textures[current_buffer].getTexture());
        return m_result;
    }

private:
    sf::Vector2i      m_render_size;
    int32_t           m_iterations;
    sf::RenderTexture m_textures[2];
    sf::Shader         m_horizontal;
    sf::Shader         m_vertical;
    sf::Sprite         m_result;

    void createTextures()
    {
        m_textures[0].create(m_render_size.x, m_render_size.y);
        m_textures[1].create(m_render_size.x, m_render_size.y);
        m_textures[0].setSmooth(true);
        m_textures[1].setSmooth(true);
        m_textures[0].display();
        m_textures[1].display();
    }

    void createShaders()
    {
        m_horizontal.loadFromMemory(VERTEX_SHADER_SRC, FRAG_X_SHADER_SRC);
        m_vertical.loadFromMemory(VERTEX_SHADER_SRC, FRAG_Y_SHADER_SRC);
        m_horizontal.setUniform("WIDTH", static_cast<float>(m_render_size.x));
        m_vertical.setUniform("HEIGHT", static_cast<float>(m_render_size.y));
    }

    void clear(uint32_t texture_id)
    {
        m_textures[texture_id].clear(sf::Color::Black);
    }

    void draw(const sf::Sprite& sprite, uint32_t dest_buffer, const sf::Shader& shader)
    {
        clear(dest_buffer);
        m_textures[dest_buffer].draw(sprite, &shader);
    }

    void draw(const sf::Sprite& sprite, uint32_t dest_buffer)
    {
        clear(dest_buffer);
        m_textures[dest_buffer].draw(sprite);
    }

    const sf::Texture& getTexture(uint32_t source_buffer)
    {
        return m_textures[source_buffer].getTexture();
    }

    uint32_t blurPass(uint32_t source_buffer, int32_t downscale)
    {
        const auto inv_scale = static_cast<float>(1 << downscale);
        const float scale = 1.0f / inv_scale;
        const int32_t current_pass_size_x = m_render_size.x >> downscale;
        const int32_t current_pass_size_y = m_render_size.y >> downscale;
        sf::Sprite sprite;
        sprite.setScale(scale, scale);
        sprite.setTexture(getTexture(source_buffer));
        draw(sprite, !source_buffer);

        sprite.setScale(1.0f, 1.0f);
        sprite.setTexture(getTexture(!source_buffer));
        sprite.setTextureRect({ 0, 0, current_pass_size_x, current_pass_size_y });
        draw(sprite, source_buffer, m_horizontal);

        sprite.setTexture(getTexture(source_buffer));
        draw(sprite, !source_buffer, m_vertical);

        const float safe_scale = 1.0f;
        sprite.setScale(inv_scale * safe_scale, inv_scale * safe_scale);
        sprite.setTexture(getTexture(!source_buffer));
        draw(sprite, source_buffer);

        return source_buffer;
    }
};
