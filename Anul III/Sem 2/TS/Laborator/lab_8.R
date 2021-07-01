# laborator 8 09.04.2021
# simularea unei variabile normale standard
# din TS Simulare-metoda respingerii pentru v.a. continue.pdf

gen_1 <- function(a=5) {
  k <- 0
  while (T) {
    y <- rexp(1)
    u1 <- runif(1)
    k <-  k + 1
    if (u1 <= exp(-(y - 1)^2 / 2)) {
      
      module_x <- y
      
      u2 <- runif(1)
      if (u2 <= 1/2)
        x <- -module_x
      else
        x <- module_x
    
      return(c(x, k))
    }
  }
}

gen_1()

gen_n <- function(n) {
  res <- sapply(1:n, gen_1)
  return(res)
}

gen_n(3)

n <- 10^6
mat <- gen_n(n)
x <- mat[1,]
k <- mat[2,]

medie <- mean(k)
sqrt(2*exp(1) /pi)

hist(x, freq=F, col='blue')

t <- seq(-4,4, 0.001)
# desenarea peste histograma se face cu lines
lines(t, dnorm(t), col='magenta')


#######################################################
# Problema 2 din tema (pdf 341 344)                   #
#######################################################

# f(x)=1/2 * cos(x) x =[-pi/2,pi/2]
# Suportul e marginit pe -pi/2,pi/2 => luam y-ul uniforma -pi/2,pi/2

# y ~ unif(-pi2/2,pi/2)
# g(x) = 1/(b-a) = 1/pi x=[-pi/2,pi/2]
# Caut c >0 a.i. f(x)/g(x) <= c <==> pi/2 * cos(x) <= c => Putem alege c = pi/2

# Aleg c =pi/2
# f(x)/(c*g(x)) = cos(x)


# Algoritm:
# Pas 1: Generez U ~ unif(-pi/2,pi/2)
# Pas 2: Generez u2 ~ unif(0,1)
# Pas 3: Daca u2 <= cos(u1) at. x = u1
#                           else GOTO Pas 1)

f2 <- function(x) {
  return(0.5 * cos(x))
}
n <- 10^4
x <- runif(n, -pi/2, pi/2)

plot(x,f2(x))

gen_val2 <- function(n) {
  sol <- c()
  while(length(sol) < n){
    u1 <- runif(1, -pi/2, pi/2)
    u2 <- runif(1)
    if(u2 <= cos(u1)) {
      sol <- append(sol,u1)
    }
  }
  return(sol)
}

z <- gen_val2(n)
hist(z, freq=F)

t <- seq(-pi/2, pi/2, 0.001)
# desenarea peste histograma se face cu lines
lines(t, dnorm(t), col='magenta')

