#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 300

int main(int argc, char *argv[]) {
  FILE *old = NULL;
  // FILE *new = NULL;
  char *name = NULL, *tmp = NULL;
  // char *new_name = NULL;
  char last = 0;
  size_t n = 0;
  ssize_t nread = 0;
  int incr = 0, n_actual = 0, n_lines = 0, n_digits = 1, exit = 0;
  char *buffer = malloc(MAX_LENGTH);

  // Version with file output
  /*
  if (argc != 4) {
    printf("Exactly 3 argument must be passed: input gcode file name, output
  gcode file name and increment\n"); return 1; } else { printf("Passed input
  name file: %s\n", argv[1]); name = argv[1]; printf("Passed output name file:
  %s\n", argv[2]); new_name = argv[2]; printf("Passed increment: %d\n",
  atoi(argv[3])); incr = atoi(argv[3]);
  }
  */

  if (argc != 3) {
    printf("Exactly 2 argument must be passed: input gcode file name and "
           "increment\n");
    return 1;
  } else {
    fprintf(stderr, "Passed input name file: %s\n", argv[1]);
    name = argv[1];
    fprintf(stderr, "Passed increment: %d\n", atoi(argv[2]));
    incr = atoi(argv[2]);
  }

  old = fopen(name, "r");
  // new = fopen(new_name, "w");

  if (!old) {
    fprintf(stderr, "File not opened correctly\n");
    goto fail;
  }
  // else if (!new) {
  //   printf("New file not opened correctly\n");
  //   goto fail;
  // }
  else {
    fprintf(stderr, "File aperti correttamente\n");
  }

  // Count number of lines
  while ((nread = getline(&buffer, &n, old)) != -1) {
    // Flag ripristinata ogni volta che si legge una nuova riga
    exit = 1;
    // Ciclo for che continua finché non vengono esauriti i caratteri del buffer
    // o viene disattivata la variabile flag
    for (int i = 0; exit && i < nread; i++) {
      // Se viene trovato un carattere diverso da un whitespace la variabile
      // flag viene spenta e aumenta il numero di righe valido
      if (!isspace(buffer[i])) {
        exit = 0;
        n_lines++;
      }
    }
  }
  // Comando per riportare il file pointer all'inizio
  rewind(old);

  // Algorithm to determine number of digits
  // Numero effettivo di righe deve essere moltiplicato per l'incremento passato
  n_lines = n_lines * incr;
  // Se il numero di righe è minore di 10 si passa n_digits rimane inizializzata
  // a 1
  if (n_lines >= 10) {
    // altrimenti si divide per 10, finché non otteniamo un numero minore di 10
    // vuol dire che il numero è composto da un altro digit
    while ((n_lines /= 10) >= 10) {
      n_digits++;
    }
    // Ultima aggiunta per fare appattare tutto
    n_digits++;
  }

  // Parsing
  while ((nread = getline(&buffer, &n, old)) != -1) {
    // Modo simile a prima per escludere le righe che non siano solo whitespace
    exit = 1;
    for (int i = 0; exit && i < nread; i++) {
      if (!isspace(buffer[i])) {
        exit = 0;
      }
    }
    if (exit) {
      // Si passa alla prossima righa se il flag è ancora attivo, questo
      // significa che la riga è solo composta da whitespaces
      continue;
    }
    // In questo modo mi assicuro che tutte le righe finiscano con uno \n,
    // solitamente l'unica ad avere questa caratteristica potrebbe essere
    // l'ultima, uso la variabile flag last
    if (buffer[strlen(buffer) - 1] != '\n') {
      last = 1;
    }
    // Printo all'inizio della riga N seguito da 0 quanti i digit calcolati e
    // col numero attuale della riga
    fprintf(stdout, "N%0*d", n_digits, n_actual);
    n_actual += incr;
    while ((tmp = strsep(&buffer, " "))) {
      // Se la riga ha spazi iniziali tmp è una stringa vuota: "" = '\0', devo
      // fare il check che quindi il primo carattere del comando non sia vuoto o
      // uguale a N perché già printato
      tmp[0] = toupper(tmp[0]);
      // Porto a maiuscola ogni eventuale carattere di comando
      if (tmp[0] != '\0' && tmp[0] != 'N') {
        // stampo il valore della stringa tmp preceduta da uno spazio di
        // separazione
        fprintf(stdout, " %s", tmp);
      }
    }
    // Se la riga non presenta un newline lo aggiungo
    if (last) {
      fprintf(stdout, "\n");
    }
  }

fail:
  // Libero la memoria dinamica allocata dalla stringa
  free(buffer);
  // if (new)
  //   fclose(new);
  // chiudo il file
  if (old)
    fclose(old);
  return 0;
}