#include "CameraMove.h"

CameraMove::CameraMove(int x, int y) : x(x), y(y) {}

void CameraMove::process() {
  Camera& camera = view->getCamera();

  if (camera.inLimits(x, y)) {
      camera.move(x, y);
  }
}