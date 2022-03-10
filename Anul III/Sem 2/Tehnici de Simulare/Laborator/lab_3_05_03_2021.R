n <- 10^5

x <- runif(n, -1, 1)
y <- runif(n, -1, 1)

in_circle <- sum(x^2+y^2 <1)
pi_approx = 4 * (in_circle / n)

# Sa se reprezinte grafic punctele care pica pe cerc, respectiv in afara cercului, dar in patrat

arch <- function(x) {
  sqrt(1 - x^2)
}

plot(0, 0)

xy = data.frame(x, y)

points(xy[which(xy$x ^2 +xy$y ^2 < 1),], col ='magenta')
points(xy[which(xy$x ^2 +xy$y ^2 > 1),], col ='green')


#g(x,y)= e^(-y) * x^2 de integrat de la 0,1 0,1
g <- function(x,y) {
  exp(-y) * x ^2
} 

u1 <- runif(n, 0, 1)
u2 <- runif(n, 0, 1)
gu <- g(u1, u2)
medie_emp <- sum(gu)/n
integrala <- integral2(g, 0, 1, 0, 1)$Q

