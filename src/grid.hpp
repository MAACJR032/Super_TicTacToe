#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "squares.hpp"

class Subgrid
{
    private:
        int m_subgrid;
        int m_grid;
        Clickable_square m_rect;

    public:
        // subgrid(int sub_grid, int grid);
        Subgrid(int grid, int subgrid);

        int get_grid() const;
        int get_subgrid() const;
        Status get_status() const;
        sf::RectangleShape& get_rectangle();
        sf::RectangleShape get_rectangle() const;

        bool is_mouse_on_square(sf::RenderWindow &window) const;
        bool was_clicked(sf::RenderWindow &window);
        
        void set_status(Status status);
        void set_position(const sf::Vector2f &position);
        void fill(Status m_player);
        void reset();
        void draw(sf::RenderWindow &window) const;
};

class Grid
{
    private:
        int m_grid;
        Status m_status = Status::EMPTY;
        Square m_background;
        std::vector<Subgrid> m_subgrids;
        
    public:
        Grid(int grid);

        
        Subgrid& get_subgrid(int index);
        const Subgrid& get_subgrid(int index) const;
        
        Status get_status() const;
        void set_status(Status status);
        
        void set_position(const sf::Vector2f& position);
        
        void fill(Status player);
        
        void update_grid_score(Status current_player);
        void check_for_tie();
        
        void hover_effect(sf::RenderWindow &window, int8_t next_grid);
        void draw(sf::RenderWindow& window) const;
        void reset();
};
