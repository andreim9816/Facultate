-- FOLDR

-- suma produsului a cate 2 nr
f [ ] = 0
f [_] = error "numar impar de elemente!"
f(a:b:l) = a * b + (f l)

-- divizorii unui numar cu list cocmprehension
diviz n = [x | x <- [1..n], mod n x == 0]
prim n = diviz n == [1,n]

primele n = filter prim [1..n]

-- filter conidite lista 
-- [x | x <- lista, conditie x]
--
-- map transformare lista
-- [transformare x | x <- lista]

-- op elem accum = 
--     if even elem then elem : accum
--     else accum

-- contains x lista = 
--     let op elem accum = if elem  == x then True else accum in 
--     foldr op False lista

sumpapatrat elem accum = elem ^ 2 + accum 

-- la nr pare adun /2 si la impare *2 cu foldr
op' elem accum = if odd elem then 2 * elem + accum
                             else div elem 2 + accum

h lista = foldr op' 0 lista 

-- concat recursiv 
concatRec [] = [] 
concatRec(lista:tail) = lista ++ (concatRec tail)

concatFold lista = foldr (++) [] lista 

sumaLengthRec [] = 0
sumaLengthRec (lista:tail) = (length lista) + (sumaLengthRec tail)

sumaLengthFold lista =
    -- op :: [a] -> Int -> Int
    let op elem accum = (length elem) + accum in
    foldr op 0 lista 

-- sau 
-- sumaLengthFold lista = 
    -- let nou = map Length lista in
    -- foldr (+) 0 nou 

reverse' lista =
    let op accum elem = elem : accum in
        foldl op [] lista 

-- ex 4. Functie care elimina un caracter din sir de caractere

--v1 recursiv
rmCharRec c [] = []
rmCharRec c (h:t) = if c == h then rmCharRec c t else h : (rmCharRec c t)

-- list comprehension
rmCharComp c lista = [x | x <- lista, x /= c ]

-- cu foldr 
rmCharFold c lista =
    foldr (\x accum -> if x == c then accum else x:accum) [] lista 

contains c lista = length [x | x <- lista, c == x] > 0
rmCharsFold rele lista = 
    foldr (\x accum -> if contains x rele then accum else x : accum) [] lista

-- simulare map cu foldr 
map' functie lista =
    let operator elem accum = (functie elem) : accum in
    foldr operator [] lista 

filter' conditie lista =
    let operator elem accum = if conditie elem then elem : accum else accum in 
    foldr operator [] lista 
