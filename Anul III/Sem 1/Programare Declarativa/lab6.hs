-- lab 6

contains :: Integer -> [Integer] -> Bool
contains _ [] = False 
contains x (h:t) = if x == h then True else False









-------------------

data Alegere = Piatra | Foarfece | Hartie

data Figura = Cerc Float | Patrat Float | Dreptunghi Float Float 


aria (Cerc raza) = raza^2 * pi
aria (Patrat latura) = latura ^ 2
aria (Dreptunghi lat lung) = lat * lung

-- Constructorii incep cu litera mare, sau daca sunt operator si incep si se termina cu :

-- Expr i se mai zice si Type Constructor
-- Numar = data constructor
data Expr a = Numar a | (Expr a):+: (Expr a) | (Expr a) :*: (Expr a)

eval (Numar x) = x
eval (x :+: y) = (eval x) + (eval y)
eval (x :*: y) = (eval x) * (eval y)

numere (Numar x) = [x]
numere (x :+: y) = (numere x) ++ (numere y)
numere (x :*: y) = (numere x) ++ (numere y)