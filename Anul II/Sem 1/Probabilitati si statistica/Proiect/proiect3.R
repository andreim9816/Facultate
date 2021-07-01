#a) Functie care genereaza reparitia comuna a celor 2 variabile X si Y
frepcomgen <- function(m , n)
{
  # Am considerat ca xi = i si yi = i
  
  names1 <- vector() # variabila X
  names2 <- vector() # variabila y

  for(i in 1 : m)
  {
    names1 <- c(names1 , paste("x", i , sep = ""))
  }
  names1 <- c(names1 , "q" )

  
  for(i in 1 : n)
  {
    names2 <- c(names2 , paste("y" , i , sep = ""))
  }
  names2 <- c(names2 , "p")
  
  # construieste matricea
  mat <- matrix(rep(0 ,(n + 1 ) * (m + 1)),nrow = m + 1 , ncol = n + 1 , dimnames = list(names1 , names2)) 
  
  #Generam numere random in matrice, iar la final impartim fiecare element la suma totala
  S <- 0
  for(i in 1 : m)
    for(j in 1 : n)
    {
      elem <- sample(1 : 20 , 1)
      S <- S + elem
      mat[i , j] = elem
    }
  
  for(i in 1 : m)
    for(j in 1 : n)
      mat[i , j] <- mat[i , j] / S
  
  #Calculam probabilitatile marginale
  for(i in 1 :m)
  {
    S <- 0
    for(j in 1 : n)
      S <- S + mat[i , j]
    mat[i , n + 1] <- S
  }
  
  for(j in 1 : n)
  {
    S <- 0
    for(i in 1 : m)
      S <- S + mat[i , j]
    mat[m + 1 ,j] <- S
  }
  
  #Marcam cu -1 ca fiind o casuta nemarcata
  
  # punem -1 pe diagonala principala
  min <- min(m , n)
  for(i in 1 : min)
    mat[i , i] <- -1
  
  # puntem -1 pe ultima linie / coloana (dupa caz)
  if(m < n)
  {
    j <- m + 1
    while(j <= n)
    {
      mat[m , j] <-  -1
      j <-j + 1
    }
    
  }
  else if(m > n)
  {
    i <- n + 1
    while(i <= m)
    {
      mat[i , n] <- -1
      i <- i + 1
    }
     
  }
  
  mat[m + 1 , n + 1] <- 1 # pune 1 pe coltul dreapta jos (suma tuturor probabilitatilor este 1)
  return (mat)
}

mat <- frepcomgen(7 , 3)
print(mat)


#b) Primeste o matrice si o completeaza
fcomplrepcom <- function(mat)
{
 S <- 0
 m <- nrow(mat) - 1 
 n <- ncol(mat) - 1
 
 #if m < n atunci parcurg pe coloane cand completez
 if(m < n)
 {
     
   for(j in 1 : n ) 
   {
      S <- 0
      poz <- 1 # pozitia unde se gasea acel element lipsa
      
       for(i in 1 : m)
       {
         
         if(mat[i , j] >= 0)
           {
            S = S + mat[i , j]
           }
         else poz <- i
       }
      mat[poz , j] <-  mat[m + 1 , j] - S # completeaza cu valoarea corecta
   }
 }
 else
 {
   for(i in 1 : m ) 
   {
     S <- 0
     poz <- 1 # pozitia unde se gasea acel element lipsa
     
     for(j in 1 : n)
     {
       
       if(mat[i , j] >= 0)
       {
         S = S + mat[i , j]
       }
       else poz <- j
     }
     mat[i , poz] <-  mat[i , n + 1] - S # completeaza cu valoarea corecta
   }
 }
 return (mat)
}

mat  <- fcomplrepcom(mat)
print(mat)

#c)
#Cov(3X,4Y) Primeste matricea cu repartitia comuna
cov <- function(mat)
{
  #Cov(3X,4Y) = 12COV(X,Y)
  
  m <- nrow(mat) - 1
  n <- ncol(mat) - 1
  
  medX <- 0 # E[x]
  medY <- 0 # E[Y]
  
  for(i in 1 : m)
   medX <- medX + i * mat[i , n + 1] 
  
  for(i in 1 : n)
    medY <- medY + i * mat[m+ 1 , i]
  
  medXY <- 0
  
  for(i in 1 : m)
    for(j in 1 : n)
      medXY <- medXY + mat[i , j] * i * j # E[XY] = sum((PI(i,j) * i * j)) (am convenit ca xi = i, yj = j)
  
  return (12 * (medXY - medX * medY))
}

print(cov(mat))

#P(0 < x < 5 | Y > 4)
probab1 <- function(mat)
{
  m <- nrow(mat) - 1
  n <- ncol(mat) -1
  
  S <- 0 # Suma in care calculam probabilitatea intersectiei
  SY <- 0
  
  if(n > 4)
  {
    for(i in 1 : min(4 , m))
     for(j in 5 : n)
       S <- S + mat[i , j]
    
    for(j in 5 : n)
      SY <- SY + mat[m + 1 , j]
  }
  
  if(SY > 0)
    return (S / SY) # P(0 < X < 5 , Y > 4) / P(Y>4)
  else return (0) # am considerat ca daca P(Y > 4) = 0, atunci probabilitatea este 0
}

print(probab1(mat))

#P(X > 3 , Y < 7)
probab2 <- function(mat)
{
  m <- nrow(mat) - 1
  n <- ncol(mat) -1
  
  S <- 0 # Suma in care calculam probabilitatea

  if(m > 3) # Daca exista cel putin un X=x a.i x >= 4
  {
    for(i in 4 : m)
      for(j in 1 : min( 7 , n))
        S <- S + mat[i , j]
  }
  
  return (S)
}

print(probab2(mat))

#d)
fverind <- function(mat)
{
  # Ca 2 variabile sa fie independente PI(i,j) = pi * qj 
  
  m <- nrow(mat) - 1
  n <- ncol(mat) -1
  
  for(i in 1 : m)
    for(j in 1 : n)
      if(mat[i , j] != mat[i , n + 1 ] * mat[m + 1 , j])
         return (0)
  return (1)
}
print(fverind(mat))

fvernecor <- function(mat)
{
  # Pentru a calcula daca 2 variabile sunt necoreate, este suficient sa calculam cov(X , Y)
  
  cov <- cov(mat) / 12 # am impartit la 12 caci mai sus calculasem cov(3X,4Y)

 if(cov == 0)
 {
   print("Sunt necorelate")
   return (1) # sunt necorelate
 }
  print("Sunt corelate")
  return (0)
}
print(fvernecor(mat))
