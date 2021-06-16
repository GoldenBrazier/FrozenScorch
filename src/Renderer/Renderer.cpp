#include "Renderer.h"
#include <Model.h>

namespace Generic {

void Renderer::draw_model(const Model& model)
{
    model.draw();
}

}