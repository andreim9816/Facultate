import Data.Char
import Data.List

fiboCazuri :: Integer -> Integer
fiboCazuri n
    | n < 2 = n
    | otherwise = fiboCazuri (n - 1) + fiboCazuri (n - 2)

fiboEcu :: Integer -> Integer
fiboEcu 0 = 0
fiboEcu 1 = 1
fiboEcu n = 
    fiboEcu (n - 1 ) + fiboEcu (n - 2)

fiboLiniar :: Integer -> Integer
fiboLiniar 0 = 0
fiboLiniar n = snd(fiboPereche n )
    where
        fiboPereche :: Integer -> (Integer, Integer)
        fiboPereche 1 = (0, 1)
        fiboPereche 2 = (1, 2)
        fiboPereche n = (b, a + b)
            where
                (a, b) = fiboPereche(n - 1)

-- Dintr-o lista sa se construiasca alta lista
-- doar cu elementele pare

semiPareRecDestr :: [Integer] -> [Integer]
semiPareRecDestr l
    | null l = l
    | even h = h : t'
    | otherwise = t'
    where
        h = head l
        t = tail l
        t' = semiPareRecDestr t

semiPareRecEq :: [Int] -> [Int]
semiPareRecEq [] = []
semiPareRecEq (h:t)
    | even h = h : t'
    | otherwise = t'
    where t' = semiPareRecEq t

semiPareComp :: [Integer] -> [Integer]
semiPareComp l = [x | x <- l, even x]

-- L2.2 
-- varianta RECURSIVA
inIntervalRec :: Integer -> Integer -> [Integer] -> [Integer]
inIntervalRec start stop list 
    | null list = []
    | start <= h && h <= stop = h : t'
    | otherwise = t'
    where
        h = head list
        t = tail list
        t' = inIntervalRec start stop t

-- descrieri de liste
inIntervalComp :: Integer -> Integer -> [Integer] -> [Integer]
inIntervalComp start stop list = [x | x <- list, start <= x && x <= stop]

-- L2.3
-- varianta recursiva
pozitiveRec :: [Int] -> Int
pozitiveRec list
    | null list = 0
    | h >= 0 = response + 1
    | otherwise = response
    where
        h = head list
        t = tail list
        response = pozitiveRec t

-- varianta pe liste
pozitiveComp :: [Int] -> Int
pozitiveComp xs = length [ 1 | x<-xs , x > 0]

-- L2.4
-- varianta RECURSIVA
pozitiiImpareRec :: [Int] -> [Int]
pozitiiImpareRec xs = pozitiiImpareAux xs 0

pozitiiImpareAux list a 
    | null list = []
    | odd h = a : t' 
    | otherwise = t'
    where 
        h = head list
        t = tail list
        t' = pozitiiImpareAux t (a + 1)

-- varianta pe liste
pozitiiImpareComp :: [Int] -> [Int]
pozitiiImpareComp xs = [b | (a,b) <- zip xs [0..] , odd a ]

-- L2.5
-- varianta RECURSIVA


multDigitsRec :: String -> Int
multDigitsRec string 
    | null string = 1
    | length string == 1 = digitToInt h
    | otherwise = (digitToInt h) * res
    where 
        h = head string
        t = tail string
        res = multDigitsRec t

-- varianta cu liste
multDigitsComp :: String -> Int
multDigitsComp number = product [digitToInt char | char <- number, isDigit char]

--L2.6
-- varianta RECURSIVA
discountRec :: [Double] -> [Double]
discountRec lista 
    | null lista = []
    | h < 200 = (h * 75 / 100.0) : t'
    | otherwise = t'
    where
        h = head lista
        t = tail lista
        t' = discountRec t

discountComp :: [Double] -> [Double]
discountComp lista = [h * 75 / 100.0 | h <- lista, h < 200]