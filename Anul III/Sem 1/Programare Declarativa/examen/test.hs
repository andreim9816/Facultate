
import Data.Char
-- ex 1
f :: [Char] -> [[Char]]
f [] = [[]]
f (x:xs) = (x:xs) : (f xs)



-- f list1 list2 = 
--     if length list1 /= length list2
--         then error "lungimi diferite!"
--     else
--        let rez = zip list1 list2 in
--        foldr (+) 0 (map(\(x,y) -> x ^ 2 + y ^ 2) rez)
      

-- ex 3

type Name = String

type Def = String

data Dictionar = I Name Def

     | Ld Name [Dictionar]

   deriving Show

 

d1 = Ld "animal"[Ld "mamifer"[I "elefant" "acesta e un elefant", I "caine" "acesta este un caine", I "pisica" "aceasta este o pisica"], I "animale domestice" "definitie"]

d2 = Ld "Animal"[Ld "Mamifer"[I "Elefant" "acesta e un elefant",I "caIne" "acesta este un caine",I "piSIca" "aceasta este o pisica"],I "animale domestice" "definitie"]

d3 = Ld "animal"[Ld "mamifer"[I "elefant" "Acesta e un Elefant", I "caine" "acesta este un caine", I "pisica" "aceasta este o pisica"], I "animale domestice" "definitie"]

d4 = Ld "animal"[Ld "mamifer"[I "pisica" "aceasta este o pisica", Ld "cc" [], I "elefant" "acesta e un elefant", I "caine" "acesta este un caine"], I "animale domestice" "definitie", I "ceva" "altceva"]

d5 = Ld "animal" [I "pis" "pis"]
-- a) !!
-- functie care pt o lista, verifica de cate ori se gaseste intrare
nrILista :: Num a => [Dictionar] -> a
nrILista [] = 0
nrILista ( (I _ _ ) : t) = 1 + (nrILista t) -- daca avem Intrare, adaugam 1 si mergem mai departe
nrILista ( h : t) = func1 h + nrILista t -- nu avem intrare, vedem cate intrari sunt pt Ld si cautam in continaure in lista

func1 :: Num a => Dictionar -> a
func1 (I _ _) = 1
func1(Ld _ []) = 0
func1 (Ld _ (  (Ld _ list2 ) : t) ) = -- daca avem tot Ld Name [Dictionar] si nu I Name Def 
    let rez1 = nrILista t in -- calculeaza pt restul listei rezultatul
    let rez2 = nrILista list2 in
    rez1 + rez2
func1(Ld _ list) = nrILista list -- daca headul este I Name Def, atunci aflam cate astfel de intrari sunt in lista



-- eqDictionar :: Dictionar -> Dictionar -> Bool
  
instance Eq Dictionar where
    (Ld tip1 []) == (Ld tip2 []) = ((map toUpper tip1) == (map toUpper tip2)) -- listele sunt goale, validam doar tipul
    (Ld _ []) == (Ld _ [_]) = False -- o lista e goala, celalata nu e
    (Ld _ [_]) == (Ld _ []) = False -- o lista e goala, celalata nu e
    (Ld _ _) == (I _ _) = False
    (I _ _ ) == (Ld _ _) = False
    (I tip1 def1) == (I tip2 def2) = (map toUpper tip1) == (map toUpper tip2) && (def1 == def2) -- not caseSenstitive + egalitate caseSensitive pe Def
    (Ld tip1 (h1:t1)) == (Ld tip2 (h2:t2)) =(h1 == h2) && (map toUpper tip1) == (map toUpper tip2)  && (Ld tip1 t1) == (Ld tip2 t2)  -- verificam Name, primul element din lista si apelam mai departe pe tailuri
