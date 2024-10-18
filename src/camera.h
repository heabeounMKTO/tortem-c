#ifndef CAMERA_H
#define CAMERA_H

#include "hitable_list.h"
#include <jpeglib.h>
#include <math.h>
// #include <pngconf.h>
#include <time.h>
#include "ray.h"
#include "utils.h"
#include "vec.h"
#include "color.h"

#ifdef TORTEM_THREADED
#include <pthread.h>
#ifndef NUM_THREADS
#define NUM_THREADS 4 
#endif
#endif


/* renders image progress buffer with sdl :> */
#ifdef TORTEM_RENDER_GUI
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_pixels.h>
#include "sdl_utils.h"
static SDL_Window* window = NULL;
static SDL_Renderer* renderer = NULL;
static SDL_Texture* texture = NULL;
#endif

typedef struct {
  int width, height;
  double focus_distance,viewport_height,vfov, defocus_angle;
  Vec3_d camera_center, v_up, look_from, look_at; //Camera origin
} CameraSettings ;




static inline CameraSettings* new_camera_settings(int width, int height, double focus_distance, double viewport_height, double vfov, Vec3_d look_from, Vec3_d look_at, double defocus_angle){
  CameraSettings* _cam = (CameraSettings*)malloc(sizeof(CameraSettings));
  double theta = deg2rad(vfov);
  double h = tan(theta/2);
  _cam->width = width;
  _cam->height=height;
  _cam->viewport_height=2.0 * h * focus_distance;
  _cam->look_from = look_from;
  _cam->look_at = look_at;
  _cam->vfov=vfov;
  _cam->defocus_angle = defocus_angle;
  _cam->v_up=vec3d_new(0.0, 1.0, 0.0); 
  // _cam->focal_length=vec3d_length(vec3d_sub(_cam->look_from, _cam->look_at));
  _cam->focus_distance = focus_distance;
  return _cam;
}

static inline Vec3_d sample_square() {
  return vec3d_new( random_double()  - 0.5 , random_double() - 0.5 , 0.0);
}
static inline Vec3_d defocus_disk_sample(Vec3_d camera_origin, Vec3_d defocus_u, Vec3_d defocus_v) {
  Vec3_d p = random_in_unit_disk();
  Vec3_d _disk_u = vec3d_scale(defocus_u, vec3d_x(p) );
  Vec3_d _disk_v = vec3d_scale( defocus_v,vec3d_y(p) );
  return vec3d_add(_disk_v, vec3d_add(camera_origin, _disk_u));
}

static inline Ray get_ray(CameraSettings* camera,Vec3_d pixel00_loc,Vec3_d pixel_delta_u, Vec3_d pixel_delta_v, int i, int j, Vec3_d defocus_u, Vec3_d defocus_v) {
  Vec3_d offset = sample_square();
  Vec3_d pixel_sample = vec3d_add(vec3d_add(pixel00_loc, vec3d_mul(vec3d_from_float((double) i + vec3d_x(offset)), pixel_delta_u)), vec3d_mul(vec3d_from_float((double) j + vec3d_y(offset)), pixel_delta_v));
  Vec3_d ray_origin = (camera->defocus_angle <=0) ? camera->camera_center : defocus_disk_sample(camera->camera_center, defocus_u, defocus_v);
  Vec3_d ray_dir = vec3d_unit(vec3d_sub(pixel_sample, ray_origin));
  Ray final_ray = {.origin=ray_origin, .direction=ray_dir};
  return final_ray;
}

static inline int render(CameraSettings* cam, HitableList* world, int samples_per_pixel, int max_depth, char* output_name) {
  unsigned char* IMAGE_BUFFER = new_jpeg_buffer(cam->width, cam->height); 
  #ifdef TORTEM_RENDER_GUI 
  SDL_Event e;
  int quit = 0;
  if(!init_sdl(cam->width, cam->height, "tortem_render", &window, &renderer)) {
        fprintf(stderr, "Failed to allocate memory for image buffer\n");
        return 1;
  }
  texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB24, SDL_TEXTUREACCESS_STATIC, cam->width, cam->height);
  if (texture == NULL) {
    fprintf(stderr, "Texture could not be created! SDL_Error: %s\n", SDL_GetError());
    free(IMAGE_BUFFER);
    free_sdl(texture, window, renderer);
    return 1;
  }
  #endif 

  double aspect_ratio = (double) cam->width / (double) cam->height;
  double viewport_width = cam->viewport_height * aspect_ratio;
  cam->camera_center = cam->look_from;
  Vec3_d u,v,w; 
  w = vec3d_unit(vec3d_sub(cam->look_from, cam->look_at));
  u = vec3d_unit(vec3d_cross(cam->v_up, w));
  v = vec3d_cross(w, u);

  Vec3_d viewport_u = vec3d_scale(u, viewport_width);
  Vec3_d viewport_v = vec3d_scale(v, - cam->viewport_height);
  // Vec3_d viewport_u = vec3d_new(viewport_width, 0.0, 0.0);
  // Vec3_d viewport_v = vec3d_new(0.0, -cam->viewport_height, 0.0);

  Vec3_d pixel_delta_u = vec3d_div(viewport_u, vec3d_from_int(cam->width));
  Vec3_d pixel_delta_v = vec3d_div(viewport_v, vec3d_from_int(cam->height));
  double defocus_radius = cam->focus_distance * tan(deg2rad(cam->defocus_angle / 2.0));
  Vec3_d defocus_disk_u = vec3d_scale(u, defocus_radius);
  Vec3_d defocus_disk_v = vec3d_scale(v,defocus_radius);

 Vec3_d viewport_upper_left = vec3d_sub(
    vec3d_sub(
        vec3d_sub(
            cam->look_from,
            vec3d_mul(w, vec3d_from_float(cam->focus_distance))
        ),
        vec3d_div(viewport_u, vec3d_from_float(2.0))
    ),
    vec3d_div(viewport_v, vec3d_from_float(2.0))
);
  Vec3_d pixel00_loc;
  pixel00_loc = vec3d_add(viewport_upper_left,
                          vec3d_mul(vec3d_from_float(0.5),
                                    vec3d_add(pixel_delta_u, pixel_delta_v)));
  double pixel_samples_scale = 1.0 / (double) samples_per_pixel;
  
  #ifdef TORTEM_RENDER_GUI
  /* renders a two sample preview for preview!? 
   * "pre-rendering"?!
   * */
  fprintf(stdout,"running `preview` stage");
  fflush(stdout);
  for (int j = 0; j < cam->height; j++) {
    for (int i = 0; i < cam->width; i++) {
      Vec3_d pixel_color = vec3d_from_float(0.0);
      for (int sample = 0; sample < 1; sample++ ) {
        Vec3_d _ray_color = ray_color(get_ray(cam,pixel00_loc, pixel_delta_u, pixel_delta_v, i, j, defocus_disk_u, defocus_disk_v), world, 1);
        pixel_color = vec3d_add(pixel_color, _ray_color);
      }
      ScreenColor col = write_color(vec3d_mul(pixel_color, vec3d_from_float(pixel_samples_scale)), 1);
      int pixel_index = (j * cam->width + i) * 3;
      store_pixel_in_buffer_jpeg(IMAGE_BUFFER, pixel_index, col.r, col.g, col.b);
    }
  }
  fprintf(stdout,"done `preview` stage");
  fflush(stdout);
  #endif

  for (int j = 0; j < cam->height; j++) {
    for (int i = 0; i < cam->width; i++) {
      Vec3_d pixel_color = vec3d_from_float(0.0);
      for (int sample = 0; sample < samples_per_pixel; sample++ ) {
        Vec3_d _ray_color = ray_color(get_ray(cam,pixel00_loc, pixel_delta_u, pixel_delta_v, i, j, defocus_disk_u, defocus_disk_v), world, max_depth);
        pixel_color = vec3d_add(pixel_color, _ray_color);
      }
      ScreenColor col = write_color(vec3d_mul(pixel_color, vec3d_from_float(pixel_samples_scale)), 1);
      int pixel_index = (j * cam->width + i) * 3;

      /// print pixels
      #ifdef DEBUG_PIXELS
      printf("PIXELS x: %f y: %f z: %f\n", col.r, col.g, col.b);
      #endif
      store_pixel_in_buffer_jpeg(IMAGE_BUFFER, pixel_index, col.r, col.g, col.b);
    }
    #ifdef TORTEM_RENDER_GUI
        SDL_UpdateTexture(texture, NULL, IMAGE_BUFFER, cam->width * 3);
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
    #endif
  }

  write_img_buffer(IMAGE_BUFFER, cam->width, cam->height, OUTPUT_JPEG, output_name);
  #ifdef TORTEM_RENDER_GUI
      while(!quit) {
        while(SDL_PollEvent(&e) != 0) {
          if(e.type == SDL_QUIT) {
            quit =1;
        break;
          }
        }
      }
  free_sdl(texture, window, renderer);
  #endif
  return 1;
}

#ifdef TORTEM_THREADED
typedef struct {
    CameraSettings* cam;
    Vec3_d pixel00_loc;
    Vec3_d pixel_delta_u;
    Vec3_d pixel_delta_v;
    Vec3_d defocus_disk_u;
    Vec3_d defocus_disk_v;
    HitableList* world;
    unsigned char* image_buffer;  
    int max_depth;
    int start_row;
    int end_row;
    int image_width;
    int samples_per_pixel;
} tortem_thread_data_t;

static void* render_section(void* arg) {
  tortem_thread_data_t* data = (tortem_thread_data_t*) arg;
  CameraSettings* cam = data->cam;
  Vec3_d pixel00_loc = data->pixel00_loc;
  Vec3_d pixel_delta_u = data->pixel_delta_u;
  Vec3_d pixel_delta_v = data->pixel_delta_v;
  Vec3_d defocus_disk_u = data->defocus_disk_u;
  Vec3_d defocus_disk_v = data->defocus_disk_v;
  HitableList* world = data->world;
  unsigned char* image_buffer = data->image_buffer;
  int max_depth = data->max_depth;
  int start_row = data->start_row;
  int end_row = data->end_row;
  int image_width = data->image_width;
  int samples_per_pixel = data->samples_per_pixel;

  double pixel_samples_scale = 1.0 / (double) samples_per_pixel;
  for (int j = start_row; j < end_row; j++) {
        for (int i = 0; i < image_width; i++) {
            Vec3_d p_col = vec3d_from_float(0.0);
            for (int s = 0; s < samples_per_pixel; s++) {
                Vec3_d _ray_color = ray_color(get_ray(cam, pixel00_loc, pixel_delta_u, pixel_delta_v, i, j, defocus_disk_u, defocus_disk_v), world, max_depth);
                p_col = vec3d_add(p_col, _ray_color);
            }
            ScreenColor col = write_color(vec3d_mul(p_col, vec3d_from_float(pixel_samples_scale)), 1);
            int pixel_index = (j * image_width + i) * 3;
            store_pixel_in_buffer_jpeg(image_buffer, pixel_index, col.r, col.g, col.b);
        }
  }
  pthread_exit(NULL);
}

static inline int render_threaded(CameraSettings* cam, HitableList* world, 
                                  int samples_per_pixel, int max_depth, char* output_name) {
  unsigned char* IMAGE_BUFFER = new_jpeg_buffer(cam->width, cam->height); 

  #ifdef TORTEM_RENDER_GUI 
  SDL_Event e;
  int quit = 0;
  if(!init_sdl(cam->width, cam->height, "tortem_render", &window, &renderer)) {
        fprintf(stderr, "Failed to allocate memory for image buffer\n");
        return 1;
  }
  texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB24, SDL_TEXTUREACCESS_STATIC, cam->width, cam->height);
  if (texture == NULL) {
    fprintf(stderr, "Texture could not be created! SDL_Error: %s\n", SDL_GetError());
    free(IMAGE_BUFFER);
    free_sdl(texture, window, renderer);
    return 1;
  }
  #endif 

  double aspect_ratio = (double) cam->width / (double) cam->height;
  double viewport_width = cam->viewport_height * aspect_ratio;
  cam->camera_center = cam->look_from;
  Vec3_d u,v,w; 
  w = vec3d_unit(vec3d_sub(cam->look_from, cam->look_at));
  u = vec3d_unit(vec3d_cross(cam->v_up, w));
  v = vec3d_cross(w, u);

  Vec3_d viewport_u = vec3d_scale(u, viewport_width);
  Vec3_d viewport_v = vec3d_scale(v, - cam->viewport_height);
  // Vec3_d viewport_u = vec3d_new(viewport_width, 0.0, 0.0);
  // Vec3_d viewport_v = vec3d_new(0.0, -cam->viewport_height, 0.0);

  Vec3_d pixel_delta_u = vec3d_div(viewport_u, vec3d_from_int(cam->width));
  Vec3_d pixel_delta_v = vec3d_div(viewport_v, vec3d_from_int(cam->height));
  double defocus_radius = cam->focus_distance * tan(deg2rad(cam->defocus_angle / 2.0));

  Vec3_d defocus_disk_u = vec3d_scale(u, defocus_radius);
  Vec3_d defocus_disk_v = vec3d_scale(v,defocus_radius);

 Vec3_d viewport_upper_left = vec3d_sub(
    vec3d_sub(
        vec3d_sub(
            cam->look_from,
            vec3d_mul(w, vec3d_from_float(cam->focus_distance))
        ),
        vec3d_div(viewport_u, vec3d_from_float(2.0))
    ),
    vec3d_div(viewport_v, vec3d_from_float(2.0))
);
  Vec3_d pixel00_loc;
  pixel00_loc = vec3d_add(viewport_upper_left,
                          vec3d_mul(vec3d_from_float(0.5),
                                    vec3d_add(pixel_delta_u, pixel_delta_v)));
  double pixel_samples_scale = 1.0 / (double) samples_per_pixel;
  pthread_t threads[NUM_THREADS];
  tortem_thread_data_t thread_data[NUM_THREADS];
  int rows_per_thread = (int) ((float) cam->height / (float) NUM_THREADS);
  
  for (long t = 0; t < (int) NUM_THREADS; t++) {
      thread_data[t].cam = cam;
      thread_data[t].pixel00_loc = pixel00_loc;
      thread_data[t].pixel_delta_u = pixel_delta_u;
      thread_data[t].pixel_delta_v = pixel_delta_v;
      thread_data[t].defocus_disk_u = defocus_disk_u;
      thread_data[t].defocus_disk_v = defocus_disk_v;
      thread_data[t].world = world;
      thread_data[t].image_buffer = IMAGE_BUFFER;
      thread_data[t].max_depth = max_depth;
      thread_data[t].image_width = cam->width;
      thread_data[t].samples_per_pixel = samples_per_pixel;
      thread_data[t].start_row = t * rows_per_thread;
      thread_data[t].end_row = (t == (int) NUM_THREADS - 1) ? cam->height : (t + 1) * rows_per_thread;
      int rc = pthread_create(&threads[t], NULL, render_section, (void*) &thread_data[t]);
      if (rc) {
          printf("Error: Unable to create thread, %d\n", rc);
          exit(-1);
      }
  }
  #ifdef TORTEM_RENDER_GUI
  while(true) {
        SDL_UpdateTexture(texture, NULL, IMAGE_BUFFER, cam->width * 3);
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
  }
  #endif

  for (long t = 0; t < (int) NUM_THREADS; t++) {
      pthread_join(threads[t], NULL);
  }

  write_img_buffer(IMAGE_BUFFER, cam->width, cam->height, OUTPUT_JPEG, output_name);
  #ifdef TORTEM_RENDER_GUI
      while(!quit) {
        while(SDL_PollEvent(&e) != 0) {
          if(e.type == SDL_QUIT) {
            quit =1;
        break;
          }
                  if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_ESCAPE) {
                    quit = 1;  // Exit on Escape key press
                }
            }
        }
      }
  free_sdl(texture, window, renderer);
  #endif
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}

#endif

#endif
