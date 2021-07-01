-- --- Monada Identity

newtype Identity a = Identity { runIdentity :: a }

instance Functor Identity where 
    fmap f cutie = Identity (f(runIdentity cutie))

instance Monad Identity where 
    return = Identity  
    cutie >>= f = f(runIdentity cutie)

instance Applicative Identity where  
    pure = return  
    cf <*> ce = do 
        f <- cf 
        e <- ce 
        return (f e)


type M = Identity
--- Limbajul si  Interpretorul



showM :: Show a => M a -> String
showM = undefined

type Name = String

data Term = Var Name
          | Con Integer
          | Term :+: Term
          | Lam Name Term
          | App Term Term
  deriving (Show)

pgm :: Term
pgm = App
  (Lam "y"
    (App
      (App
        (Lam "f"
          (Lam "y"
            (App (Var "f") (Var "y"))
          )
        )
        (Lam "x"
          (Var "x" :+: Var "y")
        )
      )
      (Con 3)
    )
  )
  (Con 4)


data Value = Num Integer
           | Fun (Value -> M Value)
           | Wrong

instance Show Value where
 show (Num x) = show x
 show (Fun _) = "<function>"
 show Wrong   = "<wrong>"

type Environment = [(Name, Value)]

interp :: Term -> Environment -> M Value
interp = undefined


-- test :: Term -> String
-- test t = showM $ interp t []

pgm1:: Term
pgm1 = App
          (Lam "x" ((Var "x") :+: (Var "x")))
          ((Con 10) :+:  (Con 11))
-- test pgm
-- test pgm


import Data.Maybe


-- type Name = String

-- data Term = Var Name
--            | Con Integer
--            | Term :+:  Term
--            | Lam Name Term -- lam "x" (..) (\x -> ...)
--            | App Term Term -- App x y = x y (aplicam functia x cu param y)
--         deriving (Show)


-- data Value = Num Integer
--             | Fun (Value -> Value)
--             | Wrong 


-- instance Show Value where
--     show (Num x) = show x
--     show (Fun _) = "<function>"
--     show Wrong = "<wrong>"

-- type Env = [(Name, Value)]
-- update :: Env -> Name -> Value -> Env
-- update env key value = if isNothing (lookup key env) 
--     then (key, value):env 
--     else map(\(k, v) -> if k == key then (k, value) else (k, v)) env

-- interp :: Term -> Env -> value
-- interp (Con x) _ = Num x
-- interp (Var s) env = calse lookup s env of Just valoare -> valoare
--                                            Nothing      -> Nothing  -- cauta in env pe s si returneaza valoarea
-- interp (x :+: y) e = 
--     let xx = interp x e in 
--     let yy = interp y e in  
--     case (xx, yy) of (Num a, Num b) -> Num (a + b)
--                       _             -> Wrong  

-- interp (Lam nume_variabile program_intern) e = Fun 
--     (\valoare -> let e2 = update e nume_variabila valoare in 
--                  interp program_intern e2)