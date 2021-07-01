-- live coding 
-- suma elementelor pare
f [] = 0
f l = 
    if mod (head l) 2 == 0 then
        head l + (f (tail l))
    else 
        f (tail l)

f2 [] = 0
f2 (head : tail) = 
    if mod head 2 == 0 then
        head + (f tail)
    else 
        f tail


-- suma elementelor din 2 in 2
-- g [ ] = 0
-- g(cap1 : cap2 : cap3) l = 

-- SABLOANE / PATTERN MATCHING

data Alegere = Piatra | Foarfece | Hartie 
data FinalJoc = Primul | AlDoilea | Egalitate

joc :: Alegere -> Alegere -> FinalJoc
joc Piatra Foarfece = Primul
joc Piatra Hartie = AlDoilea
joc Foarfece Piatra = AlDoilea
joc Foarfece Hartie = Primul
joc Hartie Piatra = Primul
joc Hartie Foarfece = AlDoilea
joc _ _ = Egalitate

-- divizorii unui nr
-- list comprehension
divizori n = [x | x <- [1..n], mod n x == 0]

-- numar e prim
prim n = (divizori n) == [1, n]

-- toate numerele prime de la 1 la n
toatePrime n = [x | x <- [1..n], prim x]

-- zip pe 3 liste
myZip3 [] _ _ = []
myZip3 _ [] _ = []
myZip3 _ _ [] = []
myZip3(ha:ta) (hb:tb) (hc:tc) = (ha, hb, hc) : (myZip3 ta tb tc)

myZip3' l1 l2 l3 = 
    let l = zip (zip l1 l2) l3 in
        [(x, y, z) | ((x, y), z) <- l]

-- filter exemplu
-- filter prim [1..5]

-- map exemplu
-- map (*2) [1..20] --> [2,4,6,8,10, ... 40]

--firstEl [(1,2), (2,3), (3,4)]
firstEl l = map (\(x, _) -> x) l 

sumList l = map sum l
-- sumList l = [sum lista | lista <- l]

-- map functie lista
-- [functie x | x <- lista]

-- filter conditie lista
-- [x | x <- lista, conditie x]

aux x = if mod x 2 == 0 then div x 2 else x * 2
prel2 lista = map aux lista 
prel2' lista = map(\x -> if mod x 2 == 0 then div x 2 else x * 2) lista

-- ex 3 n am inteles ce face 
ex3 :: [Integer] -> [Integer]
ex3 l = 
    let lfilter = filter(\(_, y) -> odd y) (zip l [1..]) in
        map(\(x, _) -> x * x) lfilter

-- primeste ca parametru o lista si un nr si aduna elementul la toate elementele listei
-- v1) exextra l x = map (+x) l
-- v2) exextra l x = map(\y -> y + x ) l

