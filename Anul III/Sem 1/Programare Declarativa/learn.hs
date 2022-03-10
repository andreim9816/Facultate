-- import Data.Char
-- import Data.List
-- -- import Data.Map
-- import Data.Bool

-- -- suma patratelor numerelor pozitive
-- f list = foldr (+) 0 (map (\x -> x * x) (filter (> 0) list))

-- litera (f:l) = f == toUpper(f)

-- -- selecteaza dintr o lista de cuvinte pe cele care incep cu litera mare 
-- literaMare list = [cuvant | cuvant <- list,  let litera(f:l) = f == toUpper(f) in litera cuvant]


-- fiboPereche 1 = (0, 1)
-- fiboPereche n = let (a, b) = fiboPereche(n - 1) in (b, a + b)
  
-- fibo n = snd (fiboPereche n)

-- factori n = [el | el <- [1..n], mod n el == 0]

-- prim n = if factori n == [1,n] then True else False

-- numereePrime n = [x | x <- [2..n], prim x]

-- myZip3 _ _ [] = []
-- myZip3 _ [] _ = []
-- myZip3 [] _ _ = []
-- myZip3 (h1:t1) (h2:t2) (h3:t3) = [(h1,h2,h3)] ++ (myZip3 t1 t2 t3)

-- firstEl list = map (\(x, _) -> x) list

-- sumList list = map sum list

-- prel2 list = map (\x -> if mod x 2 == 0 then div x 2 else (x * 2)) list 

-- -- ex 1 din lab 3 pag 4
-- -- 'e' ['mare', 'tare', 'mama']
-- func1 char list = filter (elem char) list

-- -- ex 2
-- func2 list = map (^2) (filter odd list)

-- -- ex 3
-- -- [1,2,3,4,5,6,7,8] => 1 9 25 49
-- func3 list = map (\(x,_) -> (x^2)) (filter (\(_,y) -> (odd y)) (zip list [1..]))

-- -- ex 4
-- func4 list = map (\prop -> filter (`elem` "aeiouAEIOU") prop) list 

-- -- L3.5
-- myMap _ [] = []
-- myMap f (head:tail) = (f head) : (myMap f tail)

-- myFilter _ [] = []
-- myFilter f (head:tail) = if(f head) then (head : (myFilter f tail)) else (myFilter f tail)

-- -- pag 5 ex 1
-- ordonataNat [] = True
-- ordonataNat [_] = True
-- ordonataNat (a:xs) = and [a < y | (a,y) <- zip(a:xs) (xs)]

-- -- pag 5 ex 2
-- ordonataNatRec list 
--     | list == [] = True
--     | length list == 1 = True
--     | otherwise = let x = head list in
--                 let y = head (tail list) in
--                 if (x > y) then False
--                 else ordonataNatRec (tail list)


-- -- myzip3
-- myzip3  list1 list2 list3 = map (\((x,y),z) -> (x,y,z)) (zip (zip list1 list2) list3)

-- --------------------------------------- Lab 4 -----------------------------------------

-- produsRec [] = 1
-- produsRec [x] = x
-- produsRec (x:xs) = x * produsRec xs

-- produsFold list = let op accum el = el * accum in
--     foldl op 1 list

-- fct list = let op x accum = if(mod x 2 == 0) then (div x 2) + accum else (x * 2) + accum in
--     foldr op 0 list

-- -- ex 2
-- andFold list = let op x accum = if (x == True) then accum else False in
--     foldr op True list

-- -- ex 3
-- concatRec [] = []
-- concatRec (h:t) = h ++ (concatRec t)

-- concatFold list = let op x accum = x ++ accum in
--     foldr op [] list

-- -- ex 4

-- rmChar _ [] = []
-- rmChar ch (h:t) = if (ch == h) then rmChar ch t else h : (rmChar ch t)

-- rmCharFold c l = let op el accum = if (c == el) then accum else el : accum in
--     foldr op "" l

-- rmCharsRec _ [] = []
-- rmCharsRec [] x = x
-- rmCharsRec (x:xs) list = let rez = rmCharsRec xs list in
--     rmChar x rez


-- ---------------------------- Lab 5 --------------------------------

-- -- ex 1
-- rotate n l = 
--     (drop n l) ++ (take n l)

-- -- ex 3
-- makeKey n = let rotit = rotate n ['A'..'Z'] in
--     zip ['A' .. 'Z'] rotit

-- -- ex 4
-- lookUp x [] = x
-- lookUp key (h : t) = if (key == fst h) then (snd h) else (lookUp key t)

-- -- ex 5
-- encipher n char = 
--     let cifru = makeKey n in
--     lookUp char cifru
                  
-- -- ex 6 

-- data Point = Point Float Float deriving(Show)
-- data Shape = Circle Point Float | Rectangle Point Point deriving(Show)

-- surface :: Shape -> Float
-- surface (Circle _ r) = pi * r ^ 2
-- surface (Rectangle (Point x1 y1) (Point x2 y2)) = (abs (x2 - x1)) * (abs(y2 - y1))

-- data Season = Spring | Summer | Autumn | Winter deriving(Show)

-- data StrInt = String | Int

-- type FirstName = String
-- type LastName = String
-- type Age = Int 
-- type Height = Float

-- -- data Person = Person FirstName LastName Age Height deriving(Show)

-- -- firstName (Person firstName _ _ _) = firstName
-- -- lastName (Person _ lsat _ _ ) = lsat
-- -- age (Person _ _ age _ ) = age
-- -- height(Person _ _ _ h) = h


-- data Fruct = Mar String Bool | Portocala String Int deriving(Show)

-- ionatanFaraVierme = Mar "Ionatan" False
-- goldenCuVierme = Mar "Golden Delicious" True
-- portocalaSicilia10 = Portocala "Sanguinello" 10
-- listaFructe = [Mar "Ionatan" False,
--                 Portocala "Sanguinello" 10,
--                 Portocala "Valencia" 22,
--                 Mar "Golden Delicious" True,
--                 Portocala "Sanguinello" 15,
--                 Portocala "Moro" 12,
--                 Portocala "Tarocco" 3,
--                 Portocala "Moro" 12,
--                 Portocala "Valencia" 2,
--                 Mar "Golden Delicious" False,
--                 Mar "Golden" False,
--                 Mar "Golden" True
--                 ]

-- -- a)
-- ePortocalaDeSicilia (Portocala s _) = if (s == "Tarocco" || 
--     s == "Moro" ||  
--     s == "Sanguinello") 
--     then True else False

-- ePortocalaDeSicilia _ = False

-- -- b)
 
-- nrFeliiSicilia lista = sum (map(\(Portocala _ f) -> f) (filter(\x -> ePortocalaDeSicilia x) lista))

-- -- c)
-- marCuViermi (Mar _ adev) = if(adev) then True else False
-- marCuViermi(Portocala _ _) = False

-- nrMereViermi lista = length( filter marCuViermi lista )
-- nrMereViermi2 lista = sum ( map(\x -> if(marCuViermi x) then 1 else 0) lista )


-- type NumeA = String
-- type Rasa = String
-- data Animal = Pisica NumeA | Caine NumeA Rasa


-- vorbeste (Pisica _) = "Meow!"
-- vorbeste (Caine _ _) = "Woof!"

-- rasa :: Animal -> Maybe String
-- rasa (Caine _ rasa) = Just rasa
-- rasa (Pisica _) = Nothing


-- type Nume = String
-- data Prop = Var Nume | F | T| Not Prop | Prop :|: Prop | Prop :&: Prop deriving(Eq, Read)
-- infixr 2 :|:
-- infixr 3 :&:

-- -- 1 (P V Q) ^ (NOT P ^ NOT Q)
-- p1 = (Var "P" :|: Var "Q" ) :&: ((Var "P") :&: (Var "Q"))

-- p2 = (Var "P" :|: Var "Q" ) :&: (Not (Var "P") :&: Not (Var "Q"))

-- p3 = ( Var "P" :&: (Var "Q" :|: Var "R")) :&: ( ((Not (Var "P")) :|: (Not (Var "Q"))) :&: ((Not (Var "P")) :|: (Not (Var "R"))))

-- instance Show Prop where
--     show (Var x) = x
--     show F = "False"
--     show T = "True"
--     show (a :|: b) = "(" ++ show a ++ ")"++ " V (" ++ show b ++ ")"
--     show (a :&: b) = "(" ++ show a ++ ")"++ " ^ (" ++  show b ++ ")"
--     show (Not x) = "~(" ++ show x ++ ")"

-- --------------------- Model test ------------------------

-- --ex 1
-- sfChar [] = 0
-- sfChar (x:xs) = if(x == '.' || x == '?' || x == '!') then (1 + sfChar xs) else sfChar xs

-- sfCharComph lista = length [x | x <- lista, x == '!' || x == '.' || x == '?']

-- sfCharFold lista = let op el accum = if el == '!' || el == '?' || el == '.' then 1 + accum else accum in
--     foldr op 0 lista
-- -- ex 2

-- elemPoz :: [Int] -> Bool
-- elemPoz list = let op x = if x > 0 then True else False in 
--     list == (filter op list)

-- --v1
-- liniiN matrix n = and (map (\x -> elemPoz x )  (filter (\x -> (length x) == n) matrix ))

-- -- v2
-- liniiN matrix n = let op el accum = if((length el) == n) then ((elemPoz el) && accum) else accum in 
--     foldr op True matrix  

-- -- v3 facut de prof
-- liniiN [] _ = True
-- liniiN lista n = 
--     let alea = filter(\c -> length c == n) lista in
--     filter( \c -> (foldr min 1 c) > 0) alea == alea

-- and' lista = foldr (&&) True lista

-- -- ex 3 ????????????????????????????? 

-- -- ex 1 inversare 
-- inversare [] = []
-- inversare [x] = [x]
-- inversare (x:y:[]) = [y,x]
-- inversare (x:y:t) = [y,x] ++ inversare t

-- -- ex 2 lista_pozitii
-- lista_pozitii n list = [poz | (x, poz) <- zip list [1..], x == n]

-- ------------------------------------------------------------------------------------------------ pd_restanta.pdf

-- -- ex 1
-- fRec [] = True
-- fRec ((p1,p2) : t) = if ((even p1) && (even p2)) then
--     let prod = p1 * p2 in
--     if prod <= 10 then
--         False
--     else (fRec t)
--     else (fRec t)

-- fMap lista = and ( map (\(x,y) -> x * y > 10) (filter(\(x,y) -> (even x) && (even y)) lista) )

-- -- ex 2

-- ex2 [] _ _ = []
-- ex2 (h:t) (listaInit) (contor) = 
--     let elemente = take (contor - 1) listaInit in
--     let produs = if((length elemente) == 0) then 1 else product (filter (\x -> even x) elemente) in
--     (produs) : (ex2 t listaInit (contor + 1))

-- p list = ex2 list list 1
    

-- --------------------------------------------------------------------------------- examen 10 februarie 2019

-- -- ex 1
-- aux list1 list2 = 
--     let l1 = length list1 in
--     let l2 = length list2 in
--     if(l1 < l2)
--         then (list1, take l1 list2)
--     else (take l2 list1, list2)

-- -- test1 list1 list2 = 
-- --     let (aux1, aux2) = aux list1 list2 in
-- --     let op elem accum 

-- zip2 xs ys = foldr step done xs ys
--   where done ys = []
--         step x zipsfn []     = []
--         step x zipsfn (y:ys) = (x, y) : (zipsfn ys)
    
-- fcts list1 list2 = [n | (x,y) <- zip list1 list2, n <- [x,y]  ]


-- data Exp = Lit Int | Add Exp Exp | Mul Exp Exp 

-- showExp :: Exp -> String
-- showExp (Lit n) = show n
-- showExp (Add e1 e2) = "(" ++ ( showExp e1 ++ " + " ++ showExp e2) ++ ")"
-- showExp(Mul e1 e2) = "(" ++ ( showExp e1 ++ " * " ++ showExp e2) ++ ")"

-- instance Show Exp where 
--     show = showExp 

-- ex0 = Add (Lit 2) (Mul (Lit 3) (Lit 3))
-- ex1 = Mul (Add (Lit 2) (Lit 3)) (Lit 3)

-- evalExp :: Exp -> Int
-- evalExp (Lit n) = n
-- evalExp(Add e1 e2) = ((evalExp e1) + (evalExp e2))
-- evalExp(Mul e1 e2) = ((evalExp e1) * (evalExp e2))

-- data ExpOp = LitOp Int | ExpOp :+: ExpOp | ExpOp :*: ExpOp | ExpOp :-: ExpOp

-- evalExpOp :: ExpOp -> Int
-- evalExpOp (LitOp n) = n
-- evalExpOp (e :+: f) = evalExpOp e + evalExpOp f
-- evalExpOp (e :-: f) = evalExpOp e - evalExpOp f
-- evalExpOp (e :*: f) = evalExpOp e * evalExpOp f

-- showExpOp :: ExpOp -> String
-- showExpOp (LitOp n) = show n
-- showExpOp (e :+: f) = "(" ++ (showExpOp e) ++ " + " ++ (showExpOp f) ++ ")"
-- showExpOp (e :-: f) = "(" ++ (showExpOp e) ++ " - " ++ (showExpOp f) ++ ")"
-- showExpOp (e :*: f) = "(" ++ (showExpOp e) ++ " * " ++ (showExpOp f) ++ ")"

-- exp0 = LitOp 2 :+: (LitOp 3 :*: LitOp 4)

-- instance Show ExpOp where 
--     show = showExpOp

-- -- restanta ex 3

-- data Binar a = Leaf a | Node (Binar a) (Binar a)

-- encoding' (Leaf a) path = [(a, path)]
-- encoding'(Node arb1 arb2) path = (encoding' arb1 (True:path)) ++ (encoding' arb2 (False:path))

-- encoding arb = encoding' arb []
-- tree = (Node (Node (Leaf 3) (Leaf 4)) (Node (Node (Leaf 1) (Leaf 2)) (Leaf 5)))

-- -- ex 3 din model
-- data Punct = Pt [Int] deriving(Show)

-- data Arb = Vid | FF Int | N Arb Arb deriving(Show)

-- class ToFromArb a where
--     toArb :: a -> Arb
--     fromArb :: Arb -> a


-- instance ToFromArb Punct where
--     toArb (Pt []) = Vid
--     toArb (Pt (h:t)) = N (FF h) (toArb (Pt t))


-- --   fromArb Vid = (Pt [])
-- --   fromArb (FF val) = (Pt [val])
-- --   fromArb (N arb1 arb2) = 
-- --     let (Pt st) = fromArb arb1 in
-- --     let (Pt dr) = fromArb arb2 in
-- --     Pt (st ++ dr)

-- --toArb (Pt [1,2,3])
-- --fromArb $ N (F 1 ) (N (F 2 ) (N (F 3 ) Vid ) ) :: Punct


-- -- lungimea celui mai lung cuvant care incepe cu litera 'c' dintr-o lista
-- maxLengthC list= 
--     foldr max 0 (map length ( filter (\x -> (head x) == 'c') list ) )


-- -- data Maybe a = Nothing | Just a
-- power :: Maybe Int -> Int -> Int
-- power Nothing n = 2 ^ n
-- power (Just m) n = m ^ n


------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------



--  (lookup 3 [(1,2), (3,4)]) >>= (\x -> if(x<0) then 
-- Nothing else (Just x))

-- f = (\x -> if(x>=0) then [sqrt x, -sqrt x] else [])

applyMaybe :: Maybe a -> (a -> Maybe b) -> Maybe b  
applyMaybe Nothing f  = Nothing  
applyMaybe (Just x) f = f x 