/// this is cobbled together 
#ifndef TORTEM_KEYFRAME_H
#define TORTEM_KEYFRAME_H
#include <stdio.h>
#include <time.h>
#include "camera.h"
#include "hitable_list.h"
#include "ray.h"

#ifndef SAMPLES_PER_PIXEL
#define SAMPLES_PER_PIXEL 10
#endif

// generic keyframes , start and end and duration.
typedef struct {
  Vec3_d start_key_pos, end_key_pos; 
  double duration;
} Keyframe;

typedef enum {
  EASE_IN,
  EASE_OUT
} KeyframeEasing;

static inline Keyframe keyframe_new(Vec3_d start , Vec3_d end, double duration) {
  return (Keyframe) { start, end , duration}; 
}

/// returns a increment for a given keyframe , 
/// aka "how much to increase per frame given a start and end position" 
/// currently only linear animation is available :\
/// might add easing or something later idk
static inline Vec3_d keyframe_get_increment(Keyframe key) {
  if (key.duration <= 0.0) {
    fprintf(stderr, "KEYFRAME DURATION CANNOT BE 0!\n");
    abort(); 
  }
  Vec3_d delta_pos = vec3d_sub(key.end_key_pos, key.start_key_pos);
  return vec3d_div(delta_pos, vec3d_from_float(key.duration));
} 

// testing animations rendering 
static inline void render_keyframes(CameraSettings* _cam, Keyframe _keyframe, char* output_name, HitableList* _world) {
  Vec3_d increment = keyframe_get_increment(_keyframe); 
  Vec3_d _current_position = _keyframe.start_key_pos; 
  for (int i = 0; i < _keyframe.duration; i++) {
    fprintf(stdout, "RENDERING FRAME %d of %d\n",i,(int)_keyframe.duration);
    sprintf(output_name,"animation_output/output%d.jpg", i);
    _current_position = vec3d_add(_current_position, increment);     
    _cam->look_from = _current_position;
    render(_cam, _world, SAMPLES_PER_PIXEL, 10, output_name);
  }
}

#endif
