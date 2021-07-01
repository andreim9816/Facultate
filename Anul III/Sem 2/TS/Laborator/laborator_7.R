# Manolache Andrei 344
# Simulam X ~ geom(p)
# Incepem prin a simula o valoare

simulare_geometrica <- function(p) {
  q <- 1 - p
  u <- runif(1)
  x <- floor(log(1 - u) / log(q)) + 1
  x
}

p <- 1/5

x <- simulare_geometrica(p)

# Simulam n valori din aceasta geometrica
simulare_geometrica_n <- function(n, p) {
  q <- 1 - p
  u <- runif(n)
  x <- floor(log(1 - u) / log(q)) + 1
  x
}
n <- 10^6

X <- simulare_geometrica_n(n, p)
#length(X[X == 0])
hist(X)

x1 <- rgeom(n, p)
x1 <- x1 + 1
length(x1[x1 == 0])

hist(x1, add=TRUE, col="blue")
