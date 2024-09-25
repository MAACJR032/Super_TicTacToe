#pragma once

#include <SFML/Graphics.hpp>
#include "Utils/colors.hpp"
#include "types/status.hpp"

class square
{
    protected:
        int8_t m_grid;
        Status m_status;
        sf::RectangleShape m_rect;

    public:
        square(int8_t grid);

        void set_position(const sf::Vector2f &position);
        void set_status(Status status);
        Status get_status() const;
        int8_t get_grid() const;
        sf::RectangleShape& get_rectangle();
        bool square_clicked(sf::RenderWindow &window);
        void draw(sf::RenderWindow &window);
};

class subgrid : public square
{
    private:
        int8_t m_sub_grid;

    public:
        subgrid(int8_t sub_grid, int8_t grid);

        void set_subgrid(int8_t sub_grid);
        void set_subgrid(int8_t sub_grid, int8_t grid);
        int8_t get_subgrid() const;
};