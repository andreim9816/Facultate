semn n
    | n < 0 = -1
    | n == 0 = 0
    | otherwise = 1

fact n
    | n <= 1 = 1
    | otherwise = n * fact(n - 1)

map1 :: (a -> b) -> [a] -> [b]
map1 f l = [f x | x <- l]

fibo_pereche 1 = (1, 1)
fibo_pereche 2 = (1, 2)
fibo_pereche n = (b, a + b)
    where (a, b) = fibo_pereche (n-1)

fibo_liniar n = snd (fibo_pereche n)

semiPare1 [] = []
semiPare1 (h:t) = if mod h 2 == 0 then h : semiPare1(t) else semiPare1(t)

semiPare2 l = [x | x <- l, even x ]

-- var 1
inInterval :: Integer -> Integer -> [Integer] -> [Integer]
inInterval _ _ [] = [] 
inInterval a b (h:t) = if a <= h && b >= h then (h : (inInterval a b t)) else (inInterval a b t)

-- comprehension
inIntervalComp a b l = [x | x <- l , a <= x , x <= b]

