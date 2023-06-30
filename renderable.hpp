#pragma once
#include <ostream>

namespace mvc
{

using Canvas = std::ostream;

class IRenderable
{
public:
    /**
     * @brief Renders object on the given canvas
     * @param[in,out] canvas Canvas where to render
     */
    virtual void render(Canvas& canvas) const = 0;
    virtual ~IRenderable() = default;
};

} // namespace mvc