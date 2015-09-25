#ifndef Mural_MuCanvas2DTypes_h
#define Mural_MuCanvas2DTypes_h

#include "MuOpenGL.h"
#include <cmath>

namespace mural {

  typedef union {
    struct {
      unsigned char r, g, b, a;
    } rgba;
    unsigned char components[4];
    unsigned int hex;
  } MuColorRGBA;

  struct MuVector2 {
    float x = 0.0f;
    float y = 0.0f;

    MuVector2(float x = 0.0f, float y = 0.0f): x(x), y(y) {}
  };

  struct MuVertex {
    MuVector2 pos;
    MuVector2 uv;
    MuColorRGBA color;
  };

  struct MuPoint {
    int x = 0;
    int y = 0;
    MuPoint(int x = 0, int y = 0): x(x), y(y) {}
  };

  struct MuSize {
    int width = 0;
    int height = 0;
    MuSize(int width = 0, int height = 0): width(width), height(height) {}
  };

  struct MuRect {
    MuPoint origin;
    MuSize size;

    MuRect(int x = 0, int y = 0, int w = 0, int h = 0):
      origin(x, y),
      size(w, h)
    {}
  };

  struct MuAffineTransform {
    float a = 1.0f, b = 0.0f, c = 0.0f, d = 1.0f;
    float tx = 0.0f, ty = 0.0f;

    MuAffineTransform() {}
  };

  static inline MuVector2 MuVector2Make( float x, float y ) {
    MuVector2 p(x, y);
    return p;
  }

  static inline MuVector2 MuVector2Add(MuVector2 a, MuVector2 b) {
    MuVector2 p(a.x + b.x, a.y + b.y);
    return p;
  }

  static inline MuVector2 MuVector2Sub(MuVector2 a, MuVector2 b) {
    MuVector2 p(a.x - b.x, a.y - b.y);
    return p;
  }

  static inline MuVector2 MuVector2Normalize( MuVector2 v ) {
    double ln = sqrtf(v.x * v.x + v.y * v.y);
    if (ln == 0) { return v; }

    v.x /= ln;
    v.y /= ln;
    return v;
  }

  static inline float MuVector2Length( MuVector2 v ) {
    return sqrtf(v.x*v.x + v.y*v.y);
  }

  static inline float MuVector2LengthSquared( MuVector2 v ) {
    return v.x*v.x + v.y*v.y;
  }

  static inline float MuVector2Dot( const MuVector2 v1, const MuVector2 v2 ) {
    return v1.x * v2.x + v1.y * v2.y;
  }

  static inline float MuVector2Distance( const MuVector2 v1, const MuVector2 v2 ) {
    return (v1.x - v2.x)*(v1.x - v2.x) + (v1.y - v2.y)*(v1.y - v2.y);
  }

  static inline float MuDistanceToLineSegmentSquared(const MuVector2 p, const MuVector2 v, const MuVector2 w) {
    float l2 = MuVector2Distance(v, w);
    if (l2 == 0) return MuVector2Distance(p, v);
    float t = ((p.x - v.x) * (w.x - v.x) + (p.y - v.y) * (w.y - v.y)) / l2;
    if (t < 0) return MuVector2Distance(p, v);
    if (t > 1) return MuVector2Distance(p, w);
    return MuVector2Distance(p, MuVector2Make(v.x + t * (w.x - v.x), v.y + t * (w.y - v.y) ));
  }

  static inline float MuDistanceToLineSegment(const MuVector2 p, const MuVector2 v, const MuVector2 w) {
    return sqrtf(MuDistanceToLineSegmentSquared(p,v,w));
  }

  static inline MuVector2 MuVector2ApplyTransform(MuVector2 p, MuAffineTransform t) {
    MuVector2 pt = {
      t.a * p.x + t.c * p.y + t.tx,
      t.b * p.x + t.d * p.y + t.ty
    };
    return pt;
  }

  static inline float MuAffineTransformGetScale(MuAffineTransform t) {
    return sqrtf(t.a*t.a + t.c*t.c);
  }

}

#endif
