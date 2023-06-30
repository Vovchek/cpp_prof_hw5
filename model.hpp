#pragma once
#include <cassert>
#include <optional>
#include <unordered_set>
#include "shapes.hpp"

namespace mvc {
class Document : public IRenderable {
 public:
  using Ptr = std::unique_ptr<Document>;

  Document() = default;
  virtual ~Document() = default;

  /**
   * @brief Imports document from a file
   * @return Pointer to the imported document
   */
  static Ptr load(const std::string& filename) {
    std::cout << "Loading " << filename << "...\n";
    return std::make_unique<Document>();
  }

  /**
   * @brief Exports document to a file
   */
  static void save(const Ptr& /*document*/, const std::string& filename) {
    std::cout << "Saved to " << filename << "\n";
  }

  /**
   * @brief Render document on a canvas
   */
  void render(Canvas& canvas) const override {
    for (const IShape::Ptr& shape : _shapes) {
      shape->render(canvas);
      canvas << std::endl;
    }
  }

  /**
   * @brief Adds the given shape
   * @param[in] shape Shape to be added
   * @return Ptr to inserted shape
   */
  const IShape::Ptr& add_shape(IShape&& shape) {
    std::unique_ptr<IShape> ptr;
    switch (shape.get_shape()) {
      case IShape::Shapes::line:
        ptr = std::make_unique<Line>(dynamic_cast<Line&&>(shape));
        break;
      case IShape::Shapes::rectangle:
        ptr = std::make_unique<Rectangle>(dynamic_cast<Rectangle&&>(shape));
        break;
      case IShape::Shapes::ellipse:
        ptr = std::make_unique<Ellipse>(dynamic_cast<Ellipse&&>(shape));
        break;
    }
    auto [it, b_inserted] = _shapes.emplace(std::move(ptr));
    assert(b_inserted);
    return *it;
  }

/**
   * @brief Adds the given shape
   * @param[in] shape IShape::Ptr to a shape being added
   * @return Ptr to inserted shape
   */
  const IShape::Ptr& add_shape(IShape::Ptr&& shape) {
    auto [it, b_inserted] = _shapes.emplace(std::move(shape));
    assert(b_inserted);
    return *it;
  }

  /**
   * @brief Removes the given shape
   * @param[in] shape IShape::Ptr to a shape to be removed
   * @return `true` if a remove had place, `false` otherwise
   */
  bool remove_shape(const IShape::Ptr& shape) {
    std::size_t removed = _shapes.erase(shape);
    if (removed == 0)
      return false;
    return true;
  }
  /**
   * @brief Finds the shape at a given position (e.g. mouse click)
   * @param[in] pos position to check
   * @return Ishape * if shape was found, otherwize return value is not valid
   */
  std::optional<const IShape*> find_shape(Coord::Position pos) const {
    for (const IShape::Ptr& shape : _shapes) {
      if (shape->check_hit(pos)) {
        return std::optional<const IShape*>{shape.get()};
      }
    }
    return std::nullopt;
  }

 private:
  std::unordered_set<IShape::Ptr> _shapes;
};
}  // namespace mvc