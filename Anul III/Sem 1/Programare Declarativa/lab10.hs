-- tipul nostru lista ceva cu zip
-- Lista cu elemente de tip a 
data Lista a = Gol | a ::: (Lista a)

infixr ::: 
instance Show a => Show (Lista a) where
    show Gol = "[]"
    show (head:::tail) = (show head) ++ ":" ++ (show tail)
-- scriem 1:::2:::3:::Gol obtinem 1:2:3:[]

instance Functor Lista where
    fmap _ Gol = Gol
    fmap f (head:::tail) = (f head) ::: (fmap f tail)
-- apel fmap (+2) (1:::2:::3:::4:::Gol)

instance Applicative Lista where
    pure x = x ::: (pure x)
    Gol <*> _ = Gol
    _ <*> Gol = Gol
    (headf ::: tailf) <*> (heade ::: taile) =
        (headf heade) ::: (tailf <*> taile)

-- apel [(2+), (3-), (5*)] <*> [1,2,3,7]
-- altfel:
-- a = (2+) ::: (3-) ::: (5*) ::: Gol
-- b = 1 ::: 2 ::: 3 ::: 7 ::: Gol
-- apel a <*> b

-- instance Monad Lista where
    -- Gol >>= _ = Gol
    -- (head ::: tail) >>= op =
        -- let alta_cutie = op head in
        -- case alta_cutie of Gol      -> tail >>= op
                        --  (h ::: _ ) -> h ::: (tail >>= op)

----------------------------- exercitii din lab 10  ----------------------------------------------------------------

-- compunere de functii
(<=<) :: (a -> Maybe b) -> (c -> Maybe a) -> (c -> Maybe b)
(f <=< g) x = do
    a' <- g x
    f a'

-- h = head' <=< divisori
-- h 10 returneaza Just 2
-- h 9 returneaza just 3
-- h 1 returenaza Nting

-- problema cu DO notation este ca nu poti sa combini mai multe cutii. Pot sa mai fac intr un do un let z = do ..., dau return si dupa continui cu do-ul initial

divisori 0 = Nothing
divisori x = Just [y | y <- [1..x], mod x y == 0]

head' [] = Nothing
head' (h:_) = Just h

aduna cutie1 cutie2 = do
    x <- cutie1
    y <- cutie2
    return (x+y)

asoc :: (Int -> Maybe Int) -> (Int -> Maybe Int) -> (Int -> Maybe Int) -> Int -> Bool
asoc a b c x = ((a <=< b) <=< c) x == (a <=< (b <=< c)) x

-- ex 2
-- functia Foo ia un Maybe si il duce in - daca ai Norhing, atunci in Nothing, daca e pozitiv, Just True, altfel Just False

pos x = x >= 0
foo mx = mx >>= (\x -> Just (pos x))

-- foo mx = do
--      x <- mx
--    return (pos x)

foo mx = mx >>= (\x -> Just(pos x))

addM :: Maybe Int -> Maybe Int -> Maybe Int
addM mx my = mx >>= (\x -> my >>= (\y -> Just(x + y)))

-- definire cu pattern matching
addM' (Just x) (Just y) = Just(x + y)
addM' _ _ = Nothing

-- test ca 2 cutii dau la fel si cu sabloane si cu monade
check_equal ma mb = (addM ma mb) == (addM' ma mb)

--check_equal((Just 2) (Just 3)) ((Just 3) (Just 2)) nu merge apelul
-- quickCheck check_equal

readNonEmptyLn :: (Read a) => IO a
readNonEmptyLn = do
    linie <- getLine
    if linie == "" then
        readNonEmptyLn
    else
        let x = read linie in
        return x

----- alt ex cred
citeste_numere :: (Num a, Read a) => Int -> IO [a]
citeste_numere 0 = return []
citeste_numere n = do
    x <- readNonEmptyLn -- citeste un numbar. Nu e musai sa pun ::IO Int pt ca se prinde el singur ca sunt numere ca le adun
    tail <- citeste_numere (n - 1)
    return (x:tail)

plan_suma :: (Num a, Read a) => IO a
plan_suma = do
    n <- readNonEmptyLn :: IO Int
    lista_numere <- citeste_numere n
    return (sum lista_numere)

-- scriere FARA DO
citeste_numere' 0 = return [] 
citeste_numere' n = 
    readLn >>= (\x -> 
        citeste_numere (n - 1) >>= (\tail -> return (x : tail)))

plan_suma' = 
    readNonEmptyLn >>= (\n -> citeste_numere' n >>= (\lista_numere -> return (sum lista_numere)))