#pragma once
#include <memory>
#include "renderable.hpp"
#include "color.hpp"
#include "coord.hpp"

namespace mvc {

/**
 * @brief The IShape interface
 */

class IShape : public IRenderable {
 public:
  using Ptr = std::unique_ptr<IShape>;
  enum class Shapes { line, rectangle, ellipse };
  virtual ~IShape() = default;

  /**
   * @brief Denotes actual shape
   * @return Shape type for a given implementation
   */
  virtual Shapes get_shape() const = 0;
  /**
   * @brief Creates a copy of current shape
   * @return pointer to the clone
   */
  virtual Ptr clone() = 0;
  /**
   * @brief Color setter
   * @param[in] color Color to be set
   */
  void set_color(Color color) { _color = color; }
  /**
   * @brief Color getter
   * @return Current shape color
   */
  Color get_color() const { return _color; }
  /**
   * @brief Fill setter
   * @return Set fill state
   */
  void set_fill(bool fill) { _filled = fill; }
  /**
   * @brief Fill getter
   * @return Current fill state
   */
  bool get_fill() const { return _filled; }
  /**
   * @brief Position setter
   * @param[in] color Position to place shape
   */
  void set_position(Coord::Position pos) { _pos = pos; }
  /**
   * @brief Position getter
   * @return Current shape position
   */
  Coord::Position get_position() const { return _pos; }
  /**
   * @brief Size getter
   * @return Current shape dimensions
   */
  virtual Coord::Position get_size() const = 0; // depends on shape
  /**
   * @brief Moves shape to specified distance
   * @param[in] shift distance to move
   * @return New shape position
   */
  Coord::Position move(Coord::Shift shift) { return _pos += shift; }
  /**
   * @brief Check if position hits the shape
   * @return True if pos is inside shape
   */
  virtual bool check_hit(Coord::Position pos) const = 0;

 private:
  Color _color;
  bool _filled{false};
  Coord::Position _pos;
};

/**
 * @brief The Line class
 * Represents a 2d stroke
 */
class Line : public IShape
{
public:
    /**
     * @brief Constructor from end coordinates
     * @param[in] point1 First point
     * @param[in] point2 Second point
     */
    Line(Coord point1, Coord point2)
    {
        set_position(point1);
        _length = point2 - point1;
    }

    Line(const Line&) = default;
    Line& operator=(const Line&) = default;
    Line(Line&&) = default;
    Line& operator=(Line&&) = default;

    ~Line() override = default;

    Shapes get_shape() const override {return Shapes::line;}
    Coord::Shift get_size() const override {
        return _length;
    }
    bool check_hit(Coord::Position pos) const override {
        return false; // implement actual math latter 
    }
    void render(Canvas& canvas) const override
    {
        canvas << "Line{ " << get_color() << ", " << get_position() << ", " << _length << " }";
    }
    Ptr clone() override
    {
        return std::make_unique<Line>(Line(*this));
    }

private:
    Coord::Shift _length;
};

class Rectangle : public IShape
{
public:
    /**
     * @brief Constructor from end coordinates
     * @param[in] point1 First point
     * @param[in] point2 Second point
     */
    Rectangle(Coord::Position corner, int width, int height)
    {
        set_position(corner);
        _size = {width, height};
    }

    Rectangle(const Rectangle&) = default;
    Rectangle& operator=(const Rectangle&) = default;
    Rectangle(Rectangle&&) = default;
    Rectangle& operator=(Rectangle&&) = default;

    ~Rectangle() override = default;

    Shapes get_shape() const override {return Shapes::rectangle;}
    Coord::Shift get_size() const override {
        return _size;
    }
    bool check_hit(Coord::Position pos) const override {
        pos -= get_position();
        return (pos.x >= 0 && pos.y >= 0 && pos.x <= _size.x && pos.y <= _size.y); // easy 
    }
    void render(Canvas& canvas) const override
    {
        canvas << "Rectangle{ " << get_color() << ", " << get_position() << ", " << _size << " }";
    }

    Ptr clone() override
    {
        return std::make_unique<Rectangle>(Rectangle(*this));
    }

private:
    Coord::Shift _size;
};

/**
 * @brief The Ellipse class
 * Represents a Ellipse on a plane
 */
class Ellipse : public IShape
{
public:
    /**
     * @brief Constructor from the center point and radii
     * @param[in] center Center point
     * @param[in] diam_x Diameter in horizontal direction
     * @param[in] diam_y Diameter in vertical direction
     */
    Ellipse(Coord::Position center, int diam_x, int diam_y)
    {
        set_position(center);
        _diam = {diam_x, diam_y};
    }

    Ellipse(const Ellipse&) = default;
    Ellipse& operator=(const Ellipse&) = default;
    Ellipse(Ellipse&&) = default;
    Ellipse& operator=(Ellipse&&) = default;

    ~Ellipse() override = default;

    Shapes get_shape() const override {return Shapes::ellipse;}
    Coord::Shift get_size() const override {
        return _diam;
    }
    bool check_hit(Coord::Position pos) const override {
        pos -= get_position();
        auto sqr = [](int x) {return x*x;};
        return (sqr(2*pos.x/_diam.x) + sqr(2*pos.y/_diam.y)) <= 1; // easy 
    }
    void render(Canvas& canvas) const override
    {
        canvas << "Ellipse{ " << get_color() << ", " << get_position() << ", " << _diam << " }";
    }

    Ptr clone() override
    {
        return std::make_unique<Ellipse>(Ellipse(*this));
    }

private:
    Coord::Shift _diam;
};

}  // namespace mvc
