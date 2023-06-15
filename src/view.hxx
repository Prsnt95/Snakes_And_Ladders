#pragma once

#include "model.hxx"
#include "ge211.hxx"
#include <unordered_map>


class View
{
public:
    /// View dimensions will use `int` coordinates.
    using Dimensions = ge211::Dims<int>;

    /// View positions will use `int` coordinates.
    using Position = ge211::Posn<int>;


    /// View rectangles will use `int` coordinates.
    using Rectangle = ge211::Rect<int>;

    using Transform = ge211::Transform;

    /// Constructs a view that knows about the given model.
    explicit View(Model const& model);

    void draw(ge211::Sprite_set& set);




    Rectangle die_rectangle;




private:
    Model const& model_;
    // Dimensions
    const Dimensions window_dimensions_;
    Dimensions board_dimensions;
    Dimensions grid_square_dimensions;
    Dimensions dice_dimensions;
    int player_radius;

    // Rectangles that box sprites
    // Rationale: so that we can access the four corners and center of the
    // sprite's bounding box
    Rectangle board_rectangle;
    std::vector<Rectangle> grid_square_rectangles;


    // grid_square_rectangles is initialized in the constructor
    void initialize_grid_square_rectangles();
    Transform get_board_image_transform();
    Transform get_turn_image_transform();
    ge211::Rectangle_sprite grid_square_sprite;

    ge211::Image_sprite board_sprite_;
    ge211::Image_sprite dice_1_sprite;
    ge211::Image_sprite dice_2_sprite;
    ge211::Image_sprite dice_3_sprite;
    ge211::Image_sprite dice_4_sprite;
    ge211::Image_sprite dice_5_sprite;
    ge211::Image_sprite dice_6_sprite;
    ge211::Circle_sprite player_light_sprite_;
    ge211::Circle_sprite player_dark_sprite_;
    ge211::Image_sprite background_image_sprite;

    ge211::Image_sprite red_turn_sprite;
    ge211::Image_sprite blue_turn_sprite;
    ge211::Image_sprite logo_sprite;

    ge211::Image_sprite red1;
    ge211::Image_sprite red2;
    ge211::Image_sprite red3;
    ge211::Image_sprite red4;
    ge211::Image_sprite red5;
    ge211::Image_sprite red6;
    ge211::Image_sprite blue1;
    ge211::Image_sprite blue2;
    ge211::Image_sprite blue3;
    ge211::Image_sprite blue4;
    ge211::Image_sprite blue5;
    ge211::Image_sprite blue6;

    ge211::Image_sprite redwin;
    ge211::Image_sprite bluewin;




};

