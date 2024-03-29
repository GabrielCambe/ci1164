#include <stdio.h>
#include <math.h>

#include "utils.h"
#include "ZeroFuncao.h"

// ESTIMA INTERVALO
// int estimaInterv( double *a, double *b , double h){ 

int bisseccao (double (*f)(const double x), double a, double b,
               double eps, int *it, double *raiz)
{
  //double erro, fa, fr, fb, raiz_ant;
  int k = 1;
  int m;
  
#ifdef __DEBUG__
  fprintf(stderr, "\n\n****** Iterações Bissecção *******\n");
  fprintf(stderr, "=================================================================================================\n");
  fprintf(stderr, "  it            a            b           xs        f(xs)        |a-b|         f(a)         f(b)\n");
  fprintf(stderr, "=================================================================================================\n");
#endif  

   /* ENTRADA: Função f, extremos do intervalo a, b, tolerância TOL, número máximo de iterações NMAX
CONDIÇÕES: a < b, ou f(a) < 0 e f(b) > 0 ou f(a) > 0 e f(b) < 0
SAÍDA: valor que difere de uma raiz de f(x)=0 por menos do que TOL */

  while ( k <= (*it) ){ // limita o número de iterações para prevenir um loop infinito
    (*raiz) = (a + b)/2; // novo ponto médio
    
#ifdef __DEBUG__
  fprintf(stderr, "%4d %12.8g %12.8g %12.8g ", k, a, b, *raiz);
  fprintf(stderr, "%12.4e %12.4e %12.4e %12.4e\n", f(*raiz), fabs(a-b), f(a), f(b));
#endif
        
    if ( (f((*raiz)) == 0) || (b-a)/2 < eps )
      return 0; // solução encontrada
    k += 1; // incrementa o contador de iterações
    if ( (f((*raiz)) < 0 && f(a) < 0) || (f((*raiz)) >= 0 && f(a) >= 0) ) // )) então a ← c senão b ← c # novo intervalo
      a = (*raiz);
    else
      b = (*raiz);    
  }
  
  fprintf( stderr, "O algoritmo falhou! Núm. máximo de iterações excedido!"); 
  return -1; //solucao não encontrada
  
}


/**
 *
 */
int newton (double (*f)(const double x), double (*df)(const double x), double x0, 
            double eps, int *it, double *raiz)
{
  double fx, dfx, erro;

#ifdef __DEBUG__
  fprintf(stderr, "\n\n****** Iterações Newton-Raphson *******\n");
  fprintf(stderr, "=================================================================================================\n");
  fprintf(stderr, "  it           x0           x0         raiz       f(raiz)   |raiz-x0|        f(x0)       df(x0)\n");
  fprintf(stderr, "=================================================================================================\n");
#endif
  //if(x1*X2 > 0){
  //}
  
  for(int k = 0; k <= (*it); k++) {
    fx = f(x0);
    dfx = df(x0);
    (*raiz) = x0 - fx/dfx;

    erro = fabs(((*raiz) - x0)/(*raiz))*100;
    if (erro < eps || f((*raiz)) == 0) return 0;
    
#ifdef __DEBUG__
  fprintf(stderr, "%4d %12.8g %12.8g %12.8g ", k, x0, x0, *raiz);
  fprintf(stderr, "%12.4e %12.4e %12.4e %12.4e\n", f(*raiz), fabs(*raiz-x0), fx, dfx);
#endif

    x0 = (*raiz);
  }

  fprintf( stderr, "O algoritmo falhou! Núm. máximo de iterações excedido!"); 
  return -1;
}


/**
 *
 */

//float secantes(float (*func)(float), float x0, float x1, float tolerancia) { 
//}
 
int secante (double (*f)(const double x), double x0, double x1, 
             double eps, int *it, double *raiz)
{
  double fx0, fx1, erro, x2;

#ifdef __DEBUG__
  fprintf(stderr, "\n\n****** Iterações Secante *******\n");
  fprintf(stderr, "=================================================================================================\n");
  fprintf(stderr, "  it           x0           x1         raiz      f(raiz)    |raiz-x1|        f(x0)        f(x1)\n");
  fprintf(stderr, "=================================================================================================\n");
#endif  

  //void nrerror(char error_text[]);

  //float x2,f0,f1;
  //f0 = f(x0);
  fx0 = f(x0);
  for (int k = 1; k <= (*it); k++){
    //f1 = f(x1);
    fx1 = f(x1);
    //x2 = x1-((x1-x0)*f1/(f1-f0));
    x2 = x1 - ((x1-x0)*fx1/(fx1-fx0));
    if (fabs(x2-x1) < eps || f(x2) == 0.0){
      *raiz = x2;
      return 0; //solução encontrada
    }

#ifdef __DEBUG__
    fprintf(stderr, "%4d %12.8g %12.8g %12.8g ", k, x0, x1, *raiz);
    fprintf(stderr, "%12.4e %12.4e %12.4e %12.4e\n", f(*raiz), fabs(*raiz-x0), fx0, fx1);
#endif    
    
    x0=x1;
    fx0=fx1;

    x1=x2;
  }  
    
  //nrerror("Número máximo de iterações excedido!");
  fprintf( stderr, "Número máximo de iterações excedido!");
  return -1; //solução não encontrada
}

/**
 * Cálculo de Polinômios
 */
int calcPolinomioEDerivada(Polinomio pol, double x, double *px, double *dpx )
{
  double b, c;
  
  b = pol.p[pol.grau];
  c = 0;
  for( int i = 1; i < pol.grau; i++ ){
    b = ( b * x ) + pol.p[ pol.grau - i ];
    c = x * ( b + c );
  }
  b = ( b * x ) + pol.p[0];
  c = b + c;

  *px = b;
  *dpx = c;

  return 0;
}

/**
 * Cálculo de Média
 */
double media(double *valores, unsigned long n)
{
  double soma = 0.0;
  
  // implementação vanilla
  for ( int i = 0; i < n; i++ )
    soma += valores[i];
  
  return soma / n;
}


