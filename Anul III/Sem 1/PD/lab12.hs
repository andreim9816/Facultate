-- Maybe e tip
-- Just e constructor

nth :: Int -> [a] ->  Maybe a

nth _ []  = Nothing
nth 0 (h:t)  = Just h
nth n (h:t)  = nth (n - 1) t 

-- intoarce prmul divizor propriu

divaux nr div = if div >= nr then Nothing
                else if mod nr div == 0 then Just div
                else divaux nr (div + 1)

div' nr = divaux nr 2

a = [1,2,3,4,5]
ex = (nth 10 a) >>= div'

ex' = do 
    elem <- nth 3 [1..5]
    div' elem

produs_cartezian' a b = do 
    x <- a  
    y <- a 
    let z = x^2 + 2 * x * y + y ^ 2
    return z

--apel produs_cartezian' (Just5) (Jist 7) daca se facea return (x,y)


-- definim tipul expresie

data Expr a = Valoare a | (Expr a) :+: (Expr a) | (Expr a) :*: (Expr a)  | (Expr a) :-: (Expr a)

-- trebuie sa zic ca a e showable
instance Show a => Show (Expr a) where  
    show (Valoare x) = show x  
    show (x :-: y) =  "(" ++ show x ++ " - " ++ show y ++ ")"
    show (x :+: y) =  "(" ++ show x ++ " + " ++ show y ++ ")"
    show (x :*: y) =  "(" ++ show x ++ " * " ++ show y ++ ")"

-- apel: (Valoare 5 :+: Valoare 7) :*: Valoare 9

-- ca mai sus dar pe Numeric
instance Num a => Num (Expr a) where
    x + y = x :+: y
    -- (+) x y = ( x :+: y)
    x * y = x :+: y
    x - y = x :-: y
    abs x = x
    signum x = 1 
    fromInteger x = Valoare (fromInteger x)

--apel 5 + 7 * 5 - 8 :: (Expr Int )



-- de scris din video  












-- newType e ca data doar ca mai restrictiv 

data Persoana' = P' 
    {
        nume :: String,
        prenume :: String,
        nume_complet :: String,
        adresa :: String,
        varsta :: Int,
        copii :: Int 
    }

vlad = P'
    {
        nume = "Duncea",
        prenume = "Vlad",
        nume_complet = "Vlad Alexandru Duncea",
        varsta = 21,
        adresa = "Ascuns",
        copii = 0
    }
-- scot varsta 
-- P' {varsta=v} = vlad