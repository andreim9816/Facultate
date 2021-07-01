n <- 10^4

x <- runif(n, -1, 1)
y <- runif(n, -1, 1)

k <- 0
#Versiunea 1
for (i in 1:n) {
  if (x[i]^2 + y[i]^2 <= 1) {
    k <- k + 1
  }
}

#Versiunea eficientizata
k <- sum(x^2 + y^2 <= 1)

pi = k / n * 4
print(pi)

#Reprezentare grafica v1
plot(0, 0, col="black")

for (i in 1:n) {
  if (x[i]^2 + y[i]^2 <= 1) {
    points(x[i], y[i], col="red")
  }
  else {
    points(x[i], y[i], col="blue")
  }
}
#TEMA
#De eficientizat reprezentarea grafica