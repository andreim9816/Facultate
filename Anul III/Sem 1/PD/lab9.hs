import Data.List

divisori x = [ y | y <- [1..x], mod x y == 0]
toti_divisorii lista = [d| x<- lista, d <- divisori x]
-- toti_divisorii [1,2,3,4,5,6]
-- cu monade: [1,2,3,4,5,6] >>= divisori

data Optional a = None | Some a deriving(Show)

instance Functor Optional where
    fmap _ None = None
    fmap f (Some a) = Some (f a)

instance Applicative Optional where
    pure x = Some x
    (Some f) <*> (Some x) = Some (f x)
    _ <*> _ = None

instance Monad Optional where
    None  >>= _ = None
    (Some x) >>= f = f x

head' [] = None
head' (h:_) = Some h

inv 0 = None
inv x = Some (1.0 / x)

-- do notation
f cutie = do
    x <- cutie
    y <- head' x
    z <- inv y
    let t = z * z
    return t

aduna cutie1 cutie2 = do
    x <- cutie1
    y <- cutie2
    return (x + y)

-- aduna [1,2,3] [4,5,6] -> [5,7,9]
-- aduna (Just 2) Nothing -> NOthing
-- aduna (Some 5) (Some 3) -> Some 8

aduna' cutie1 cutie2 = [x + y | x <- cutie1, y <- cutie2]
h cutie = do
    x <- cutie 
    -- y <- [1,2,3,4]
    -- z <- (Some 5)
    return x

---------------------- laborator citire

-- main = do
--     -- sau folosesc readLn si o sa i faca singur cast din acel x + y
--     linia1 <- getLine
--     linia2 <- getLine
--     let x = (read linia1) :: Int
--     let y = (read linia2) :: Int
--     print (x+y)

main = do
    x <- readLn
    let plan_intermediar = do -- do deci e monada 
        z <- readLn -- IO
        t <- readLn
        u <- readLn
        return (z + t + u) -- probabil numar
    t <- plan_intermediar
    y <- readLn
    print(x + y)

citeste 0 = return []
citeste n = do
    nume <- getLine
    varsta <- readLn :: (IO Int)
    restul <- citeste (n - 1)
    return ((varsta, nume) : restul)

ex1 = do
    n <- readLn :: (IO Int)
    oamenii <- citeste n
    let (varsta, nume) = maximum oamenii
    putStrLn nume
    print varsta

aux [] [] elem = []
aux buffer [] elem = [buffer]
aux buffer (h:t) elem = if elem == h then buffer : (aux [] t elem) 
                                     else aux (buffer ++ [h]) t elem

splitOn lista elem = aux [] lista elem

ex2 = do
    date <- readFile "ex2.in"
    let linii =splitOn date '\n'
    let oameni = map (\linie -> let [nume, varsta] = splitOn linie ',' in ((read varsta) :: Int, nume)) linii
    let (vasta, nume) = maximum oameni
    putStrLn nume

-- citirea unei matrice de la tastatura

citire_linie 0 = return []
citire_linie n = do
    x <- readLn :: (IO Int)
    restul <- citire_linie (n - 1)
    return (x : restul)

citire_matrice 0  _ = return []
citire_matrice n m = do
    linie <- citire_linie n
    restul_liniilor <- citire_matrice (n - 1) m
    return (linie : restul_liniilor)

ex3 = do
    n <- readLn :: (IO Int)
    m <- readLn :: (IO Int)
    matrice <- citire_matrice n m
    return matrice


citeste_rand = do
    