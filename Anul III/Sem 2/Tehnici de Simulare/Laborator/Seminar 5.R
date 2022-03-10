# Paul-Tiberiu Danciu, 344

# Generarea a n valori într-o variabila aleatoare X, repartizata exponential cu
# parametru lambda

n <- 10 ** 6
lambda <- 1

genereaza_exp <- function(n, lambda) {
  u <- runif(n)
  x <- -1 / lambda * log(u)
  x
}

x <- genereaza_exp(n, lambda)
x1 <- rexp(n, lambda)

par(mfrow=c(1, 2))

t <- seq(0, 10, 0.001)

hist(x, freq = F)
lines(t, dexp(t, lambda))

hist(x1, freq = F)
lines(t, dexp(t, lambda))


#plot(t, dexp(t, lambda))

par(mfrow=c(1, 1))

# Punem histogramele suprapuse
x <- genereaza_exp(n, lambda)
x1 <- rexp(n, lambda)

hist(x, freq = F, col='blue')

hist(x1, freq = F, col='red', add=T)

lines(t, dexp(t, lambda), col='green')
