# Manolache Andrei
# Grupa 344

# Aproximarea integralei (-inf, inf) e^(-x^2) folosind exponentiala
# Observam ca e^(-x^2) este para, deci I = integrala pe (-inf, inf) e^(-x^2)dx = 2 * integrala pe (0, inf) e^(-x^2)dx

# Aplicam S.V. t = x^2 => sqrt(t) = |x|
# x -> 0 => t -> 0
# x -> inf => t -> inf
# 2xdx = dt => dx = dt/2x => I = 2 * integrala pe (0, inf) e^(-t) * t^(-1/2)dt

# Fie exponentiala cu lambda=1 si f(x) = e^(-x) si h(x)=1/sqrt(x)
n <- 10^6
h <- function(x) 
{
  return (1/sqrt(x))
}

x_exp <- rexp(n, 1)
hu <- h(x_exp)
med_empirica_exp <- sum(hu)/n 