#include "CameraMoveEvent.h"

CameraMoveEvent::CameraMoveEvent(int x, int y) : x(x), y(y) {}

void CameraMoveEvent::process() {
  Camera& camera = view->getCamera();

  if (camera.inLimits(x, y)) {
      camera.move(x, y);
  }
}