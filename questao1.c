#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_PAGINAS 100
#define MAX_REFERENCIAS 10000

typedef struct pagina {
  int pagina;
  int idade;
} pagina_t;

int pagina_presente(pagina_t *paginas_memoria, int pagina, int n_molduras) {
  for (int i = 0; i < n_molduras; i++) {
    if (paginas_memoria[i].pagina == pagina) {
      return 1;
    }
  }
  return 0;
}

pagina_t *gera_sequencia_paginas(int n_paginas, int n_referencias) {
  pagina_t *seq = malloc(n_referencias * sizeof(pagina_t));
  for (int i = 0; i < n_referencias; i++) {
    seq[i].pagina = rand() % n_paginas;
    seq[i].idade = 0;
  }
  return seq;
}

int substituicao_fifo(pagina_t *paginas_memoria, pagina_t *seq_paginas, int n_referencias, int n_molduras) {
  int faltas = 0;
  for (int i = 0; i < n_referencias; i++) {
    if (!pagina_presente(paginas_memoria, seq_paginas[i].pagina, n_molduras)) {
      faltas++;
      paginas_memoria[i % n_molduras] = seq_paginas[i];
    }
  }
  return faltas;
}

int substituicao_envelhecimento(pagina_t *paginas_memoria, pagina_t *seq_paginas, int n_referencias, int n_molduras) {
  int faltas = 0;
  for (int i = 0; i < n_referencias; i++) {
    if (!pagina_presente(paginas_memoria, seq_paginas[i].pagina, n_molduras)) {
      faltas++;
      pagina_t pagina_removida = paginas_memoria[i % n_molduras];
      for (int j = 0; j < n_molduras; j++) {
        paginas_memoria[j].idade++;
      }
      paginas_memoria[i % n_molduras] = seq_paginas[i];
    }
  }
  return faltas;
}

int main() {
  int n_paginas = 100;
  int n_referencias = 10000;
  int n_molduras;

  srand(time(NULL));

  for (n_molduras = 1; n_molduras <= 10; n_molduras++) {
    pagina_t *seq_paginas = gera_sequencia_paginas(n_paginas, n_referencias);
    pagina_t *paginas_memoria_fifo = malloc(n_molduras * sizeof(pagina_t));
    pagina_t *paginas_memoria_envelhecimento = malloc(n_molduras * sizeof(pagina_t));

    int faltas_fifo = substituicao_fifo(paginas_memoria_fifo, seq_paginas, n_referencias, n_molduras);
    int faltas_envelhecimento = substituicao_envelhecimento(paginas_memoria_envelhecimento, seq_paginas, n_referencias, n_molduras);

    printf("Número de molduras de página: %d\n", n_molduras);
    printf("Faltas de página FIFO: %d\n", faltas_fifo);
    printf("Faltas de página envelhecimento: %d\n", faltas_envelhecimento);

    free(seq_paginas);
    free(paginas_memoria_fifo);
    free(paginas_memoria_envelhecimento);
  }

  return 0;
}
