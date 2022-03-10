import Data.List
myInt = 555555555555555555555555555555
double  ::  Integer -> Integer
double x = x + x

triple :: Integer -> Integer
triple x = x * 3

maxim :: Integer -> Integer -> Integer
maxim x y = if (x > y) then x else y

maxim2 :: Integer -> Integer -> Integer
maxim2 x y =
    if (x > y )
        then x
else y

maxim3 :: Integer -> Integer -> Integer -> Integer
maxim3 x y z = maxim x (maxim (y) (z))

maxim33 :: Integer -> Integer -> Integer -> Integer
maxim33 x y z = if(x >= y && x >= z)
                    then x
                else if(y >= x && y >= z)
                    then y
                else z

maxim333 :: Integer -> Integer -> Integer -> Integer
maxim333 x y z = 
    let 
        u = maxim x y
    in 
        maxim u z

maxim4 :: Integer -> Integer -> Integer -> Integer -> Integer
maxim4 x y z t =
    let 
        u = maxim x y
    in
        let 
            v = maxim u z
        in 
            maxim v t

-- L1.6
-- i)
sumPat :: Integer -> Integer -> Integer
sumPat x y = x * x + y * y

-- ii)
par :: Integer -> String
par x = 
    if(mod x 2 == 0) 
        then "par"
    else "impar"

-- iii)
fact :: Integer -> Integer
fact x = 
    if (x <= 0) 
        then 1
    else x * fact (x - 1)

-- iiii)
fct :: Integer -> Integer -> Bool
fct x y = 
    x > 2 * y