---Monada Reader


newtype Reader env a = Reader { runReader :: env -> a }


instance Monad (Reader env) where
  return x = Reader (\_ -> x)
  ma >>= transformare = Reader f
    where f env = let am_citit = (runReader ma) env -- aplica pe environment
                  in  (runReader (transformare am_citit)) env



instance Applicative (Reader env) where
  pure = return
  mf <*> ma = do
    f <- mf
    a <- ma
    return (f a)

instance Functor (Reader env) where
  fmap f ma = pure f <*> ma


ask :: Reader env env
ask = Reader id

local :: (r -> r) -> Reader r a -> Reader r a
local f ma = Reader $ (\r -> (runReader ma)(f r))

-- Reader Person String

data Person = Person { name :: String, age :: Int }

showPersonN :: Person -> String
showPersonN Person {name = name, age = age} = "Name:"  ++  name

showPersonA :: Person -> String
showPersonA persoana = "Age:" ++  show(age persoana) -- getter definit automat


showPerson :: Person -> String
showPerson pers = "(" ++ (showPersonN pers ) ++ (showPersonA pers) ++ ")"

mshowPersonN ::  Reader Person String
mshowPersonN = Reader showPersonN

mshowPersonA ::  Reader Person String
mshowPersonA = Reader showPersonA

mshowPerson :: Reader Person String
mshowPerson = Reader showPerson

-- apeluri showPerson $ Person "ada" 20

show_mai_multe = do 
    name <- mshowPersonN
    age <- mshowPersonA
    total <- mshowPerson
    return (name ++ " " ++ age ++ " " ++ total)