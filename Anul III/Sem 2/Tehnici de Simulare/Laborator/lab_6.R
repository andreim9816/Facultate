# Problema 1 din lab 5 (ca tema)

n <- 10 ^ 6
alfa <- 0.1
beta <- 0.25


# F'(x) = f(x) densitatea pe care vrem sa o suprapunem peste histograma
denstitate <- function(x, alfa, beta) {
  alfa * beta * x^(beta - 1) * exp(-alfa * x ^ beta)
}

n <- 10 ^ 4
lambda <- 1
beta <- 2

# x = F-1(u)
genereaza_1 <- function (n, lambda, beta) {
  u <- runif(n)
  x <- - 1/alfa * log(u)
  x <- x ^ (1/beta)
}

x <- genereaza_1(n, alfa, beta)


hist(x, freq=FALSE, col="blue")
t <- seq(0, 4, 0.001)

lines(t, denstitate(t, alfa, beta), col="red")  # trece prin mijloc, e ok

# length(x[x>20])
# length(x[x<5])

x_filtrat <- x[x < 10^6]
x_filtrat2 <- x_filtrat[x < 4*10^5]
hist(x_filtrat, freq=FALSE, col="red")
hist(x_filtrat2, freq=FALSE, col="red")



# Simlarea uniformei pe 1 2 3 ... m (discrete)
n <- 10 ^6
u <- runif(n)
m <- 10

x <- floor(m*u) + 1

# histograma grupeaza valorile pe intervale
hist(x, col="blue")
