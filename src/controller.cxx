#include "controller.hxx"
#include "model.hxx"

Controller::Controller()
        : model_(),
          view_(model_)
{}

void
Controller::on_key(ge211::Key key)
{
    if (key == ge211::Key::code('q')) {
        quit();
    }
}

void
Controller::draw(ge211::Sprite_set& set)
{
    view_.draw(set);
}


void
Controller::on_mouse_down(ge211::Mouse_button button, ge211::Posn<int> mouse)
{


    int die_left_x = view_.die_rectangle.top_left().x;
    int die_right_x = view_.die_rectangle.top_right().x;
    int die_top_y = view_.die_rectangle.top_left().y;
    int die_bottom_y = view_.die_rectangle.bottom_left().y;
    if(model_.winner==Player::neither) {
        if (mouse.x > die_left_x && mouse.x < die_right_x && mouse.y > die_top_y
            && mouse.y < die_bottom_y) {
            model_.rollDie();
        }
    }
}