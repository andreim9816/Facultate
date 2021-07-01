# Laborator dublu, 26-02-2021

# Aproximarea lui Pi

n <- 10^5  # definim n-ul
x <- runif(n, -1, 1)  # generam n valori 
y <- runif(n, -1, 1)

k <- sum(x^2 + y^2 <= 1)

aprox_pi = k / n * 4

# reprezentare grafica

plot(0,0,col="black")
for (i in 1:n) {
  if(x[i]^2 + y[i]^2 <= 1) {
    points(x[i], y[i], col="red")
  } else {
    points(x[i], y[i], col="blue")
  }
}


# De luat exercitiile facute 



# ex 4 Integrala dubla 
g <- function(x, y) {
  exp((x+y)^2)
}

teta0 <- integral2(g, 0, 1, 0, 1)$Q

# tema De creat o functie care sa calculeze integrala dubla folosind functia 
# integrate de 2 ori (imbricat) si apoi de estimat prin simulare integrala 