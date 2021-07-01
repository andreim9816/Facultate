# Manolache Andrei 344 

# ex1
n <- 10^5  # definim n-ul
u <- runif(n, 0, 1)  # generam n valori intre 0 si 1 uniforme

g1 <- function(x) {
  (1-x)^3 * x^5
}
teta1 <- integrate(g1, 0, 1)$value # valoarea adevarata 
g1u <- g1(u)
medie_empirica1 <- sum(g1u)/n # valoarea aproximata 

# ex2 
# definim functia. FOlosim aceleasi valori u
g2 <- function(x)
{
  exp(1) ^ (exp(1) ^ x)
}
teta2 <- integrate(g2, 0, 1)$value  # valoarea adevarata 
g2u <- g2(u)
medie_empirica2 <- sum(g2u)/n  # valoarea aproximata 

# ex 3

g3 <- function(x) 
{
  exp(x + x ^2)
}

teta3 <- integrate(g3, -2, 2)$value  # valoarea adevarata 
u <- runif(n, -2, 2)  # generam date noi (suntem pe alt interval [-2,2])
g3u <- g3(u)
medie_empirica3 <- sum(g3u)/n * 4 # valoarea aproximata. Inmultim cu (2 - (-2))

# ex 4
# Aplicam schimbarea de variabila t = arctan(x)
# tan(t) = x
# dt = 1/(1+x^2)
# Capete:
# lim x->inf arctan(x) = pi/2
# lim x->-inf arctan(x) = -pi/2

g4 <- function(x) 
{
  tan_2 = tan(x) * tan(x)
  exp(-tan_2) * (1 + tan_2)
}

mini_gaussian <- function(x)
{
  exp(-x^2)
}

real_answer <- integrate(mini_gaussian, -Inf, Inf) # valoarea adevarata 
teta4 <- integrate(g4, -pi/2, pi/2)$value  
u <- runif(n,-pi/2, pi/2)  # generam date noi
g4u <- g4(u)
medie_empirica4 <- sum(g4u)/n * pi # valoarea aproximata. Inmultim cu (pi/2 - (-pi/2))

