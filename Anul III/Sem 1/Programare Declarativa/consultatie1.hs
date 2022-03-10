data Stiva a = Goala | Ocupat a (Stiva a)

push :: Stiva a -> a -> Stiva a
push stiva elem = Ocupat elem stiva 

pop :: Stiva a -> (a, Stiva a)
pop Goala = error "Stiva e goala"
pop(Ocupat elem tail) = (elem, tail)

instance Show a => Show (Stiva a) where
    show Goala = "[]"
    show (Ocupat elem tail) = show elem ++ ":" ++ show tail

plus :: Num a => Stiva a -> Stiva a
plus stiva =
    let (x, stiva2) = pop stiva in  
    let (y, stiva3) = pop stiva2 in  
    push stiva3 (x + y)


first :: (a -> Bool) -> Stiva a -> (a, Stiva a)
first conditie stiva = 
    let (x, stiva2) = pop stiva in  
    if conditie x then (x, stiva2)
                  else first conditie stiva2

convert [] = Goala
convert (h:t) = Ocupat h (convert t)

-- apel: first (\x -> mod x 2 == 0) (convert (5:7:9:3:4:1:[]))

--ia primele 3 elemente. Daca sum > 10, returneaza al 4-lea elem si restul stivei
-- altfel returneaza al 4-lea element si restul stivei

test stiva =
    let(x, stiva2) = pop stiva in
    let (y, stiva3) = pop stiva2 in
    let (z, stiva4) = pop stiva3 in
    if x + y + z > 10 then 
        pop stiva4
    else
        let (_, stiva5) = pop stiva4 in
        pop stiva5


-- tip care encapsuleaza o functie
newtype Plan a = P { runPlan :: Stiva String -> (a, Stiva String) }

pop' :: Plan String
pop' = P pop 

a = convert ["salut", "ce ", "mai ", "faci "]

instance Applicative Plan where
    pure x = P
        (\stiva -> (x, stiva))

    plan_de_functie <*> plan_de_elem = P  
        (\stiva -> let (, stiva2))
-- test' = do   
--     x <- pop
--     y <- pop
--     z <- pop
--     if x+y+z > 10 then 
--         pop
--     else do  
--         pop
--         pop

-- citeste n numere si face suma lor  
plan_de_lista 0 = return []
plan_de_lista n = do 
    x <- readInt'
    restul <- plan_de_lista (n - 1)
    return (x:restul)

suma_a_n = do 
    n <- readInt'
    list <- plan_de_lista n
    return (sum list)

