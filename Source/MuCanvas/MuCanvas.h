#ifndef Mural_MuCanvas_h
#define Mural_MuCanvas_h

#include "MuCanvasContext.h"

namespace mural {

  enum MuCanvasContextMode {
    kMuCanvasContextModeInvalid,
    kMuCanvasContextMode2D,
    kMuCanvasContextModeWebGL
  };

  class MuCanvas {
    public:
      short getWidth() { return width; }
      void setWidth(short newWidth);

      short getHeight() { return height; }
      void setHeight(short newHeight);

      MuCanvas();
      ~MuCanvas();

      MuCanvasContext *getContext(MuCanvasContextMode mode);

    private:
      MuCanvasContext *renderingContext = nullptr;
      MuCanvasContextMode contextMode;

      bool isScreenCanvas = false;

      short width = 200, height = 150;
  };

}

#endif
