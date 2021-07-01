executa_ceva_care_poata_esua = Just 10
altceva_care_poate_esua x = if x > 0 then Nothing else Just x

functie complexa = do
    x <- executa_ceva_care_poata_esua 
    y <- altceva_care_poate_esua x
    return y

suma l1 l2 = do  
    x <- l1
    y <- l2
    return (x + y )

-- apel: suma [1,2,3] [4,5,6]
-- apel: suma (Just 5) (Just 7)
--apel : plan_suma = suma readLn readLn. Dupa citesc 5 7, returneaza 12


newtype WriterS a = Writer { runWriter :: (a, String) } 


instance  Monad WriterS where
  return va = Writer (va, "")
  ma >>= k = let (va, log1) = runWriter ma
                 (vb, log2) = runWriter (k va)
             in  Writer (vb, log1 ++ log2)


instance  Applicative WriterS where
  pure = return
  mf <*> ma = do
    f <- mf
    a <- ma
    return (f a)       

instance  Functor WriterS where              
  fmap f ma = pure f <*> ma     

inceput = Writer(0, "inceput")

tell :: String -> WriterS () 
tell log = Writer ((), log)
  
logIncrement :: Integer  -> WriterS Integer
logIncrement state_vechi = Writer (state_vechi + 1, "increment: " ++ show state_vechi ++ "\n")

logIncrement2 state =
    (logIncrement state) >>= logIncrement

logIncrementN :: Integer -> Integer -> WriterS Integer
logIncrementN x 1 = logIncrement x
logIncrementN x n = do  
    y <- logIncrement x
    logIncrementN y (n - 1) 
-- apel runWriter $ logIncrementN 2 4

-- fara do notation

logIncrementN' x 1 = logIncrement x
logIncrementN' x n = logIncrement x >>= (\y -> logIncrementN y (n - 1))

newtype WriterLS a = WriterL {runWriterL :: (a, [String])}

instance Functor WriterLS where 
    fmap functie (WriterL (state, log)) = WriterL ((functie state), log)

-- isPos :: Integer -> WriterLS Bool 