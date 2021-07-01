import Data.Char
import Data.List

-- suma elementelor de pe poz pare si impare. se returneaza pereche
sum2 [] = (0,0)
sum2[x] = (x, 0)
sum2(a:b:t) = 
    let (x, y) = sum2 t in
    (a + x, b + y)

-- se da un sir de numere. sa se afiseze lista obtinuta din diferenta intre numere
diff [] = []
diff l = 
    let l2 = zip l (tail l) in
        [x - y | (x, y) <- l2]

diff' l = [x -y | (x, y) <- zip(tail l) l]

-- cu map si filter
divizori n = filter(\x -> mod n x == 0) [1..n]
-- suma patratelor diizorilor
sumdivsquare n = sum(map(^2) (divizori n))

-- cu foldr
sumdivsquarer n = 
    foldr(\elem accum -> accum + elem ^ 2) 0 (divizori n)

-- foldl
sumdivsquarel n = 
    foldl(\accum elem -> accum + elem ^2) 0 (divizori n)

-- Din laborator
-- ex 1 cu rotirea
rotate :: Int -> [Char ] -> [Char]
rotate n l =
    if n < 0 || n > (length l)
        then error "argument invalid!"
        else
            (drop n l ) ++ (take n l)

-- ex 3
makeKey n = zip ['A'..'Z'] (rotate n ['A' .. 'Z'])

-- ex 4
-- lookUp :: Char -> [(Char -> Char)] -> Char
lookUp c cifru = 
    let l = filter (\(x, y) -> x == c) cifru in
    if l == [] then c else snd (head l )

-- ex 5
encipher :: Int -> Char -> Char
encipher n c =
    let cifru = makeKey n in
        lookUp c cifru

-- ex 6
normalize :: String -> String
normalize text =
    let t2 = map toUpper text in
    let t3 = filter (\c -> isDigit c || isUpper c) t2 in 
    t3

-- ex 7
encipherStr :: Int -> String -> String
encipherStr n text =
    [encipher n x | x <- normalize text]

-- ex 8
reverseKey l = [(b, a) | (a,b) <- l]

-- ex 9
decipher n c =
    let cifru = reverseKey n in
        lookUp c cifru

decipherStr n text =
    let t2 = filter (\c -> isUpper c || isDigit c || c == ' ') text in
    [decipher n x | x <- t2]

-- ceva legat de piatra hartie foarfece
data Alegere = Piatra | Hartie | Foarfece deriving(Show)
data Rezultat = Castig | Infrangere | Egalitate deriving(Show)

joc Piatra Foarfece = Castig
joc Piatra Hartie = Infrangere

joc Foarfece Piatra = Infrangere
joc Foarfece Hartie = Castig

joc Hartie Piatra = Infrangere
joc Hartie Hartie = Castig
joc _  _ = Egalitate

-- supraincarcare !!
a % b = mod a b
a // b = div a b
a +-+ b = a ^ 2 + b ^ 2 

-- tipul Figura
data Figure = Cerc Float | Patrat Float | Dreptunghi Float Float deriving(Show)

