#include <iostream>
#include "controller.hpp"

int main()
{
    mvc::Canvas& canvas = std::cout; // view
    mvc::Controller editor; // controller
    const mvc::Document::Ptr& doc = editor.create_document(); // model

    // user manipulates interface so controller emmits commands:
    // user creates ellipse:
    const mvc::IShape::Ptr& circle_ptr = doc->add_shape(mvc::Ellipse({ 100, 150 }, 35, 70));
    // ...sets new color for it:
    circle_ptr->set_color(mvc::Color{ 155, 200, 255, 0 });
    // user creates line:
    const mvc::IShape::Ptr& line_ptr = doc->add_shape(mvc::Line({ 75, 50 }, { -30, -210 }));
    // ...sets new color for it:
    line_ptr->set_color(mvc::Color{ 255, 0, 0, 60 });
    // user copy-pastes line:
    const mvc::IShape::Ptr& line2_ptr = doc->add_shape(line_ptr->clone());
    // ...sets new color for it:
    line2_ptr->set_color(mvc::Color{ 255, 255, 255, 60 });
    // time to refresh
    doc->render(canvas);
    // user clicks the shape:
    const mvc::Coord click {100, 150};
    std::optional found = doc->find_shape({100, 150});
    // did he hit something usefull?
    std::cout << "at position " << click << "was found:\n";
    if(found.has_value()) {
        (*found)->render(std::cout);
    } else {
        std::cout << "nothing.\n";
    }
}
