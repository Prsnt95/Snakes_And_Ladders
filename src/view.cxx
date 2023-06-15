#include <iostream>
#include "view.hxx"

//from hw5
using Transform = ge211::Transform;






View::View(Model const& model)
        : model_(model),

          window_dimensions_(800, 600),
          board_dimensions(400, 400),
          grid_square_dimensions(40, 40),
          dice_dimensions(136, 136),
          player_radius(15),
          grid_square_sprite({ 40, 40 }),
          board_sprite_("board_sprite.png"),
          dice_1_sprite("dice_1.png"),
          dice_2_sprite("dice_2.png"),
          dice_3_sprite("dice_3.png"),
          dice_4_sprite("dice_4.png"),
          dice_5_sprite("dice_5.png"),
          dice_6_sprite("dice_6.png"),
          player_light_sprite_(player_radius, ge211::Color(255, 0, 0, 255)),
          player_dark_sprite_(player_radius, ge211::Color(0, 0, 255, 255)),
          background_image_sprite("snakes_and_ladders_board.png"),
          red_turn_sprite("red_turn_sprite.png"),
          blue_turn_sprite("blue_turn_sprite.png"),
          logo_sprite("snlLogo.png"),

          red1("red1.png"),
          red2("red2.png"),
          red3("red3.png"),
          red4("red4.png"),
          red5("red5.png"),
          red6("red6.png"),
          blue1("blue1.png"),
          blue2("blue2.png"),
          blue3("blue3.png"),
          blue4("blue4.png"),
          blue5("blue5.png"),
          blue6("blue6.png"),
          redwin("winner_red_sprite.png"),
          bluewin("winner_blue_sprite.png")

{

    // Initialize board_rectangle
    int screen_center_x = window_dimensions_.width / 2;
    int board_top_left_x = screen_center_x - board_dimensions.width / 2;
    int board_top_left_y = 25;
    board_rectangle = Rectangle(board_top_left_x, board_top_left_y,
                                board_dimensions.width, board_dimensions
                                .height);

    int dice_top_left_x = screen_center_x - dice_dimensions.width / 2;
    die_rectangle = Rectangle(dice_top_left_x, 450, dice_dimensions.width,
                              dice_dimensions.height);

    initialize_grid_square_rectangles();
}

void
View::initialize_grid_square_rectangles()
{
    Position origin = { (board_rectangle.bottom_left().x), (board_rectangle
                        .bottom_left().y - grid_square_dimensions.height)};
    // This needs to do something!
    for (int i = 0; i < 101; i++) {
        int number = i;
        int x = (number - 1) % 10;
        int y = (number - 1) / 10;
        int scaled_x = x * grid_square_dimensions.width;
        int scaled_y = y * grid_square_dimensions.height;
        int actual_x = (origin.x + scaled_x);
        if (y % 2 == 1) {
            actual_x = (origin.x + board_dimensions.width -
                    grid_square_dimensions.width - scaled_x);
        }
        int actual_y = (origin.y - scaled_y);
        Rectangle grid_square(actual_x, actual_y,
                grid_square_dimensions.width,
                grid_square_dimensions.height);
        grid_square_rectangles.push_back(grid_square);
    }

    // test this function with REPL

    // DEBUG initialize_grid_square_rectangles
    // std::cout << "Window Dimensions \twidth: " << window_dimensions_.width <<
    // "\theight: " << window_dimensions_.height << "\n";
    // std::cout << "Origin \tx: " << origin.x << "\ty: " << origin.y << "\n";
    // std::cout << "Center \tx: " << center.x << "\ty: " << center.y << "\n";
    // std::cout << "Top-left \tx: " << top_left.x << "\ty: " << top_left.y <<
    // "\n";
    //
    // for (int i = 0; i < 100; i++) {
    //     Rectangle square = grid_square_rectangles.at(i);
    //     std::cout << "Rectangle #" << i << "\tx: " << square.top_left().x
    //     << "\ty: "
    //     << square.top_left().y << "\twidth: " << square.width << "\theight: "
    //     << square
    //     .height << "\n";
    // }

}
Transform
View::get_turn_image_transform()
{
    double raw_image_width = 1000;
    double raw_image_height = 1000;
    double scale_x = static_cast<double>(board_dimensions.width) /
                     raw_image_width;
    double scale_y = static_cast<double>(board_dimensions.height) /
                     raw_image_height;
    Transform t;
    t.set_scale_x(scale_x);
    t.set_scale_y(scale_y);

    // Test this function REPL
    /*
    std::cout << "Board Image Transform \tscale_x: " << t.get_scale_x() <<
    "\tscale_y: " << t.get_scale_y() << "\n";
     */

    return t;
}


Transform
View::get_board_image_transform()
{
    double raw_image_width = 1800;
    double raw_image_height = 1800;
    double scale_x = static_cast<double>(board_dimensions.width) /
            raw_image_width;
    double scale_y = static_cast<double>(board_dimensions.height) /
            raw_image_height;
    Transform t;
    t.set_scale_x(scale_x);
    t.set_scale_y(scale_y);

    // Test this function REPL
    /*
    std::cout << "Board Image Transform \tscale_x: " << t.get_scale_x() <<
    "\tscale_y: " << t.get_scale_y() << "\n";
     */

    return t;
}



void
View::draw(ge211::Sprite_set& set)
{

    // Draw grid_square Positions
    // DO NOT DELETE
    // To be commented out when we have the board
    // int count = 0;
    // for (const auto& grid_square_rectangle : grid_square_rectangles) {
    //     Position grid_square_position = grid_square_rectangle.top_left();
    //     set.add_sprite(grid_square_sprite, grid_square_position, 0);
    //     count++;
    // }
    // std::cout << "number of positions: " << count << "\n";

    // Draw background image
    Transform background_image_transform = get_board_image_transform();
    Position board_top_left = board_rectangle.top_left();
    set.add_sprite(background_image_sprite, board_top_left, 0,
                   background_image_transform);

    // Draw player positions
    for (const auto& player : model_.playerPositions) {
        Player player_type = player.first;
        int position_number = player.second;
        Position radius_center = grid_square_rectangles.at(position_number)
                .center();
        Position player_top_left((radius_center.x - player_radius),
                                 (radius_center.y - player_radius));

        if (player_type == Player::light) {
            set.add_sprite(player_light_sprite_, player_top_left, 1);
        }
        else if (player_type == Player::dark) {
            set.add_sprite(player_dark_sprite_, player_top_left, 1);
        }

    }

    // DEBUG Print player positions
    const int p1 = model_.playerPositions.at(static_cast<Player
            const>
            (Player::light));
    std::cout << "Light Player Position: " << p1 << "\n";

    // Draw die
    if (model_.die == 0) {
        set.add_sprite(dice_1_sprite,die_rectangle.top_left(),1);
    }
    if (model_.die == 1) {
        set.add_sprite(dice_1_sprite,die_rectangle.top_left(),1);
    }
    else if (model_.die == 2) {
        set.add_sprite(dice_2_sprite,die_rectangle.top_left(),1);
    }
    else if (model_.die == 3) {
        set.add_sprite(dice_3_sprite,die_rectangle.top_left(),1);
    }
    else if (model_.die == 4) {
        set.add_sprite(dice_4_sprite,die_rectangle.top_left(),1);
    }
    else if (model_.die == 5) {
        set.add_sprite(dice_5_sprite,die_rectangle.top_left(),1);
    }
    else if (model_.die == 6) {
        set.add_sprite(dice_6_sprite,die_rectangle.top_left(),1);
    }

    Transform turn_image_transform = get_turn_image_transform();

    if (model_.lightScore==1){
        set.add_sprite(red1,die_rectangle.top_right().right_by(10),1,
                       turn_image_transform);
    }
    else if (model_.lightScore==2){
        set.add_sprite(red2,die_rectangle.top_right().right_by(10),1,
                       turn_image_transform);
    }
    else if (model_.lightScore==3){
        set.add_sprite(red3,die_rectangle.top_right().right_by(10),1,
                       turn_image_transform);
    }
    else if (model_.lightScore==4){
        set.add_sprite(red4,die_rectangle.top_right().right_by(10),1,
                       turn_image_transform);
    }
    else if (model_.lightScore==5){
        set.add_sprite(red5,die_rectangle.top_right().right_by(10),1,
                       turn_image_transform);
    }
    else if (model_.lightScore==6){
        set.add_sprite(red6,die_rectangle.top_right().right_by(10),1,
                       turn_image_transform);
    }

    if (model_.darkScore==1){
        set.add_sprite(blue1,die_rectangle.top_right().right_by(10).down_by
        (25),1,
                       turn_image_transform);
    }
    else if (model_.darkScore==2){
        set.add_sprite(blue2,die_rectangle.top_right().right_by(10).down_by
        (25),1,
                       turn_image_transform);
    }
    else if (model_.darkScore==3){
        set.add_sprite(blue3,die_rectangle.top_right().right_by(10).down_by
        (25),1,
                       turn_image_transform);
    }
    else if (model_.darkScore==4){
        set.add_sprite(blue4,die_rectangle.top_right().right_by(10).down_by
        (25),1,
                       turn_image_transform);
    }
    else if (model_.darkScore==5){
        set.add_sprite(blue5,die_rectangle.top_right().right_by(10).down_by
        (25),1,
                       turn_image_transform);
    }
    else if (model_.darkScore==6){
        set.add_sprite(blue6,die_rectangle.top_right().right_by(10).down_by
        (25),1,
                       turn_image_transform);
    }


    // Testing: board corners
    // DO NOT DELETE
    // set.add_sprite(player_light_sprite_, board_rectangle.top_left());
    // set.add_sprite(player_light_sprite_, board_rectangle.bottom_left());
    // set.add_sprite(player_light_sprite_, board_rectangle.top_right());
    // set.add_sprite(player_light_sprite_, board_rectangle.bottom_right());


    set.add_sprite(logo_sprite,{20,100},1,turn_image_transform);
    if(model_.winner==Player::neither) {
        if (model_.turn == Player::light) {

            set.add_sprite(red_turn_sprite, {20, 200}, 1, turn_image_transform);
        }
        if (model_.turn == Player::dark) {

            set.add_sprite(blue_turn_sprite,
                           {20, 200},
                           1,
                           turn_image_transform);
        }
    }
    else if(model_.winner==Player::dark){
        set.add_sprite(bluewin, {9, 200}, 2,
                       turn_image_transform);
    }
    else if (model_.winner==Player::light){
        set.add_sprite(redwin, {9, 200}, 2,
                       turn_image_transform);
    }

}


