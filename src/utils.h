#ifndef INTERVAL_H
#define INTERVAL_H
#define NEAR_ZERO 1e-8

#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include "vec.h"
#include <jpeglib.h>

// Two numbers with extra steps
typedef struct {
  double min;
  double max;
} Interval;

Interval interval_new(double min, double max);
bool interval_surrounds(Interval interval, double x);
double interval_clamp(Interval interval, double threshold);
double interval_sizeof(Interval interval);

static inline double random_double() {
  return rand() / (double) (RAND_MAX) + 1.0;
}

static inline double random_interval(double min, double max) {
return min + (max - min) * (rand() / (double) RAND_MAX);
}


static inline Vec3_d random_unit_vector() {
      while(true) {
          Vec3_d p = vec3d_new(
              random_interval(-1.0, 1.0),
              random_interval(-1.0, 1.0),
              random_interval(-1.0, 1.0)
          );
          double sq = vec3d_lengthsq(p);
          if(1e-160 < sq && sq <= 1.0) {
          return vec3d_unit(p);    
      } 
    }
}

static inline Vec3_d random_on_hemisphere(Vec3_d normal) {
  Vec3_d on_unit_sphere = random_unit_vector();
  if (vec3d_dot(on_unit_sphere, normal) > 0.0) {
    return on_unit_sphere;
  } else {
    return vec3d_negate(on_unit_sphere);
  }
}
static inline double deg2rad(double deg) {
  return deg * 0.0174533;
}
static inline bool is_nan_vec3d(Vec3_d v) {
  return isnan(vec3d_x(v)) || isnan(vec3d_y(v)) || isnan(vec3d_z(v));
}
static inline bool is_inf_vec3d(Vec3_d v) {
  return isinf(vec3d_x(v)) || isinf(vec3d_y(v)) || isinf(vec3d_z(v));
}
static inline bool check_vec3d_near_zero(Vec3_d v) {
  return (fabs(vec3d_x(v)) < NEAR_ZERO  
          && fabs(vec3d_y(v)) < NEAR_ZERO 
          && fabs(vec3d_z(v)) < NEAR_ZERO);
}

/// `https://en.wikipedia.org/wiki/Schlick%27s_approximation`
static inline double schlicks_approx(double cosine, double ref_idx) {
    double r0 = (1 - ref_idx) / (1 + ref_idx);
    r0 = r0 * r0;
    return r0 + (1 - r0) * pow((1 - cosine), 5);
}

/// creates a new mf image buffer
static inline unsigned char* new_img_buffer( int width, int height ) {
  unsigned char* img_buffer = (unsigned char*)malloc(width * height * 3);
  if (!img_buffer) {
    return NULL;
  }
  return img_buffer;
}
/// refactor SIMD?!
static inline void store_pixel_in_buffer(unsigned char* img_buffer, int pixel_index , int r, int g, int b) {
  img_buffer[pixel_index] = r; 
  img_buffer[pixel_index + 1] = g;
  img_buffer[pixel_index + 2] = b;
}


/// writes image buffer to file, jpeg for now. upon `finishing` frees the image buffer.
static inline void write_img_buffer(unsigned char* img_buffer, int width, int height) {
  struct jpeg_compress_struct cinfo;
  struct jpeg_error_mgr jerr;
    FILE * outfile;
    if ((outfile = fopen("output.jpg", "wb")) == NULL) {
        fprintf(stderr, "Can't open output file\n");
        free(img_buffer);
        return;
    }
  cinfo.err = jpeg_std_error(&jerr);
  jpeg_create_compress(&cinfo);
  jpeg_stdio_dest(&cinfo, outfile);
  cinfo.image_width = width;
  cinfo.image_height = height;
  cinfo.input_components = 3;
  cinfo.in_color_space = JCS_RGB;

      jpeg_set_defaults(&cinfo);
    jpeg_set_quality(&cinfo, 100, TRUE);  

    jpeg_start_compress(&cinfo, TRUE);

      JSAMPROW row_pointer[1];
    while (cinfo.next_scanline < cinfo.image_height) {
        row_pointer[0] = &img_buffer[cinfo.next_scanline * width * 3];
        jpeg_write_scanlines(&cinfo, row_pointer, 1);
    }

    jpeg_finish_compress(&cinfo);
    fclose(outfile);
    jpeg_destroy_compress(&cinfo);

    free(img_buffer);
}

#endif

