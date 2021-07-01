--- Monada Writer

    

newtype WriterLS a = Writer { runWriter :: (a, [String]) } 


instance  Monad WriterLS where
  return va = Writer (va, [])
  ma >>= k = let (va, log1) = runWriter ma
                 (vb, log2) = runWriter (k va)
             in  Writer (vb, log1 ++ log2)


instance  Applicative WriterLS where
  pure = return
  mf <*> ma = do
    f <- mf
    a <- ma
    return (f a)       

instance  Functor WriterLS where              
  fmap f ma = pure f <*> ma 



tell :: String -> WriterLS () 
tell log = Writer ((), [log])
  
logIncrement :: Int  -> WriterLS Int
logIncrement x = Writer (x + 1, ["increment:" ++ show x])

logIncrementN :: Int -> Int -> WriterLS Int
logIncrementN x 1 = logIncrement x
logIncrementN x n = do  
    y <- logIncrement x
    logIncrementN y (n - 1)
                         
isPos :: Int -> WriterLS Bool
isPos x = if (x>= 0) then (Writer (True, ["poz"])) else (Writer (False, ["neg"]))                           

mapWriterLS :: (a -> WriterLS b) -> [a] -> WriterLS [b]
mapWriterLS f [] = return []
mapWriterLS f (h:t) = do  
    b_pentru_h <- f h 
    b_pentru_tail <- mapWriterLS f t 
    return (b_pentru_h : b_pentru_tail)

-- runWriter $ mapWriterLS isPos [1, -2, 3]

-- afisare ceva cu IO
-- afisare x 1 = printLn x
-- afisare x n = do 
--     printLn x 
--     afisare (x + 1) (n - 1 )