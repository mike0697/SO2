/*
 * Corso di Sistemi Operativi 2020
 * Schema soluzione seconda verifica: semafori
 *
 * Author: Riccardo Focardi
 */
#include <semaphore.h>
#include <stdio.h>

// dichiarazione semafori e variabili globali
sem_t conta_pallina;
int numero_palline_uscite;
sem_t mutex;
int N;
// inizializza semafori e variabili
// ATTENZIONE dim è la dimensione del gruppo che deve entrare
// nell'imbuto.
void inizializza_sem(int dim) {
    sem_init(&conta_pallina,0,dim);
    sem_init(&mutex,0,1);
    N = dim;
    numero_palline_uscite = 0;

}
 
// distruggi i semafori
void distruggi_sem() {
    sem_destroy(&conta_pallina);
    sem_destroy(&mutex);
}
 
// attende di entrare nell'imbuto
void entra_imbuto() {
    sem_wait(&conta_pallina);
}
 
// esce dall'imbuto
// ATTENZIONE usare una variabile intera condivisa per sapere 
// quante palline sono uscite (da proteggere con una sezione critica)!
void esci_imbuto() {
    
    sem_wait(&mutex);
    numero_palline_uscite++;
    if(numero_palline_uscite == N){
        for(int j = 0; j < N; j++)
        {
            sem_post(&conta_pallina);
        }
        numero_palline_uscite = 0;
    }
    sem_post(&mutex);
}
