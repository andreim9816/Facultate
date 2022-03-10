import Data.List
import Data.Maybe

-- continuare lab 6

type Nume = String -- alias pt String
data Prop 
    = Var Nume
    | F
    | T
    | Not Prop
    | Prop :|: Prop
    | Prop :&: Prop
    deriving (Eq, Read)
infixr 2 :|:
infixr 3 :&:

p3 :: Prop
p3 = (Var "P" :&: (Var "Q" :|: Var "R")) :&: (Not (Var "Q"))

-- defineste Show pt Prop
instance Show Prop where
    show (Var x) = x
    show F = "False"
    show T = "True"
    show (a :|: b) = "(" ++ show a ++ ")"++ " V (" ++ show b ++ ")"
    show (a :&: b) = "(" ++ show a ++ ")"++ " ^ (" ++  show b ++ ")"
    show (Not x) = "!(" ++ show x ++ ")"
-- la apel scriem direct p3

--typless ~~~ interfata
class Figura a where
    aria :: a -> Float
    perimetru :: a -> Float

data Cerc = Cerc Float -- Cerc e propriul tip. La lab trecut, Cerc era constructor pt tipul Figura
instance Figura Cerc where
    aria (Cerc r) = r ^ 2 * pi
    perimetru (Cerc r) = 2 * pi * r

-- apel: aria (Cerc 5)

type Env = [(Nume, Bool)]
impureLookup :: Eq a => a -> [(a,b)] -> b
impureLookup a = fromJust . lookup a

eval :: Prop -> Env -> Bool
eval F _= False
eval T _= True
eval (Var x) env = impureLookup x env
eval (Not x) env = not (eval x env )
eval (x :|: y) env = (eval x env ) || (eval y env)
eval (x :&: y) env = (eval x env ) && (eval y env)

-- ex 4 care afiseaza toate variabilile dintr o expresie

variabile' F = []
variabile' T = []
variabile' (Var x) = [x]
variabile' (Not x) = variabile' x
variabile' (x :|: y) = variabile' x ++ variabile' y
variabile' (x :&: y) = variabile' x ++ variabile' y



variabile :: Prop -> [Nume]
variabile prop = nub (variabile' prop)

-- ex 5
envs :: [Nume] -> [Env]
envs [] = []
envs [nume] = [[(nume, True)], [(nume, False)]]
envs (nume:t) = 
    let restul = envs t in
    let alea_cu_true = [ (nume, True) : env | env <- restul] in
    let alea_cu_false = [(nume, False) : env | env <- restul] in 
    alea_cu_true ++ alea_cu_false

-- ex 6
-- o propozitie e satisfiabila daca macar o evaluare da True

satisfiabila :: Prop -> Bool
satisfiabila prop = 
    let v = variabile prop in -- pt toate variabilile o singura data 
    let e = envs v in -- pt toate evaluarile posibile pt variabile
    or [eval prop x | x <- e]
    -- la valida se pune pe AND
