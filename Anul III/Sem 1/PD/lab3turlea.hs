{-# LANGUAGE FlexibleContexts #-}

-- Ex1 lista divizorilor 

-- list comprehension

factori :: Int -> [Int]
factori n = [x | let listDiviz = [1..n], x <- listDiviz, mod n x == 0]

-- recursiv
factoriRec :: Int -> [Int]
factoriRec n = aux n 1

aux :: Int -> Int -> [Int]
aux n contor =
    if (mod n contor == 0) && contor <= n
       then contor : (aux n (contor + 1))
    else if contor <= n
       then (aux n (contor + 1))
    else []

-- Ex 2

prim n = if length(factori n) == 2 then True else False

-- Ex 3
numerePrime :: Int -> [Int]
numerePrime n = [x | x <- [2..n], prim x]

-- L3.2 myZip3

myZip3 :: [Int] -> [Int] -> [Int] -> [(Int, Int, Int)]
myZip3 [] _ _ = []
myZip3 _ [] _ = []
myZip3 _ _ [] = []
myZip3 (h1:t1) (h2:t2) (h3:t3) = (h1,h2,h3) : (myZip3 t1 t2 t3)

-- Exercitii
-- ex 1
firstEl list = map(\(a, _) -> a) list

-- ex 2
sumList list = map (sum) list

sumList' list = [sum l | l <- list]

-- ex 3
auxPrel2 x = if mod x 2 == 0 then div x 2 else x * 2
prel2 list = map auxPrel2 list
prel2' lista = map(\x -> if mod x 2 == 0 then div x 2 else x * 2) lista


-- Exercitii (pagina 4) L3.4 ?????????????????????/



-- Exercitii (pagina 5)
--ex 1
-- ordonataNat [] = True 
-- ordonataNat [x] = True
-- ordonataNat (x:xs) = and [x <= pairFst | let (pairFst : _) = zip [x] xs ] NU MERGE
-- ordonataNat (x:xs) = 
--     let (pair:_) = zip [x] xs
--     in if fst pair <= snd pair 
--         then ordonataNat xs
--         else
--         False

-- ex 2
ordonataNat1 [] = True 
ordonataNat1 [x] = True
ordonataNat1 (x:xs) = 
    let (pair:_) = zip [x] xs
    in if fst pair <= snd pair 
        then ordonataNat1 xs
        else
        False

-- ex 3
