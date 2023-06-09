#include "../defines.h"
#include "../program.h"
#include "../block.h"
#include "../machine.h"
#include "../point.h"
#include <unistd.h>

int main(int argc, char const *argv[]) {
  machine_t *m = NULL;
  program_t *p = NULL;
  block_t *curr_b = NULL;
  point_t *pos = NULL;
  data_t t, tt = 0, tq, lambda, v, dt;

  if (argc != 3) {
    eprintf("I need exactly two arguments: g-code filename and INI filename\n");
    exit(EXIT_FAILURE);
  }
  m = machine_new(argv[2]);
  if (!m) {
    eprintf("Error in INI file\n");
    exit(EXIT_FAILURE);
  }
  machine_print_params(m);
  if (machine_connect(m, NULL) != EXIT_SUCCESS)
    goto fail;

  p = program_new(argv[1]);
  if (!p) {
    eprintf("Could not create program\n");
    exit(EXIT_FAILURE);
  }
  if (program_parse(p, m) < 0) {
    eprintf("Could not parse program\n");
    exit(EXIT_FAILURE);
  }
  program_print(p, stderr);

  tq = machine_tq(m);
  // ------------- Run program -------------- //
  program_reset(p);
  printf("# N t tt lambda s v X Y Z\n");
  while ((curr_b = program_next(p))) {
    fprintf(stderr, BRED"[%03zu]"CRESET" duration %f s ", block_n(curr_b), block_dt(curr_b));
    fflush(stderr);
    // Rapid motion
    if (block_type(curr_b) == RAPID) {
      point_t *sp = machine_setpoint(m);
      point_t *target = block_target(curr_b);
      fprintf(stderr, "\n");
      machine_listen_start(m);
      point_set_xyz(sp, point_x(target), point_y(target), point_z(target));
      while (machine_error(m) > machine_max_error(m)) {
        machine_sync(m, 1); // 1 cause we're in rapid motion
        usleep(machine_tq(m) * 1E6);
      }
      machine_listen_stop(m);
      continue;
    }
    // Interpolated motion
    dt = block_dt(curr_b);
    for (t = 0; t<dt + tq/10.0; t+= tq, tt += tq) {
      lambda = block_lambda(curr_b, t, &v);
      pos = block_interpolate(curr_b, lambda);
      if (!pos)
        continue;
      machine_sync(m, 0); // 0 because it's not a rapid motion
      printf("%lu %.3f %.3f %.6f %.3f %.3f %.3f %.3f %.3f\n", block_n(curr_b), t, tt, lambda, lambda * block_length(curr_b), v, point_x(pos), point_y(pos), point_z(pos));
      fprintf(stderr, "[%5.1f%%]", lambda*100);
      fflush(stderr);
      usleep(machine_tq(m) * 1E6);
      fprintf(stderr, "\b\b\b\b\b\b\b\b");
    }
    fprintf(stderr, "\n");
  }
  // --------------------------- //

  machine_disconnect(m);

fail:
  program_free(p);
  machine_free(m);
  return 0;
}