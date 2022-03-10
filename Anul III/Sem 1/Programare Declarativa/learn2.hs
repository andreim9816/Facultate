-- data Maybe a = Nothing | Just a
-- import Control.Monad.Writer 
-- instance Functor Maybe where
--     fmap f Nothing = Nothing
--     fmap f (Just x) = Just (f x)

-- instance Applicative Maybe where
--     pure x = Just x
--     Nothing <*> _ = Nothing 
--     Just f <*> x = fmap f x
radical :: Float -> Maybe Float
radical x | x >= 0 = return (sqrt x)
          | x < 0 = Nothing


applyMaybe :: Maybe a -> (a -> Maybe b) -> Maybe b  
applyMaybe Nothing f  = Nothing  
applyMaybe (Just x) f = f x  

type Birds = Int
type Pole = (Birds, Birds)

landLeft :: Birds -> Pole -> Maybe Pole
landLeft n (left, right) 
    | abs ((left + n) - right) < 4 = Just (left + n, right)
    | otherwise                    = Nothing

landRight :: Birds -> Pole -> Maybe Pole
landRight n (left, right)  
    | abs(left - (n + right)) < 4 = Just (left, right + n)
    | otherwise                   = Nothing

x -: f = f x

banana :: Pole -> Maybe Pole
banana _ = Nothing

routine :: Maybe Pole
routine = do
    start <- return (0,0)
    first <- landLeft 2 start
    second <- landRight 2 first
    landLeft 1 second


applyLog(x, log) f = let (y, newLog) = f x in 
    (y, log ++ newLog)

-- newtype WriterS a = Writer {runWriter :: (a, [String])}

-- instance Monad WriterS  where
--     return va = Writer (va, [])
--     ma >>= k = let (va, log1) = runWriter ma 
--                    (vb, log2) = runWriter (k va)
--                in Writer(vb, log2 ++ log1  )


-- instance  Applicative WriterS where
--   pure = return
--   mf <*> ma = do
--     f <- mf
--     a <- ma
--     return (f a)       

-- instance  Functor WriterS where              
--   fmap f ma = pure f <*> ma     

-- tell :: String -> WriterS ()
-- tell log = Writer ((), [log])

-- logIncrement :: Int -> WriterS Int
-- logIncrement x = Writer(x + 1, ["Called increment with argument " ++ show x ++ " \n "])

-- logIncrement2 :: Int -> WriterS Int
-- logIncrement2 x = let (y, log1) = runWriter (logIncrement x) in 
--                   let (z, log2) = runWriter (logIncrement y) in
--                       Writer(z, log1 ++ log2)


-- logIncrementN :: Int -> Int -> WriterS Int 
-- logIncrementN x 1 = logIncrement x 
-- logIncrementN x n = do 
--     y <- logIncrement x
--     logIncrementN y (n - 1)


-- isPos :: Int -> WriterS Bool 
-- isPos x = if(x > 0) then (Writer (True, ["poz"])) else (Writer (False, ["neg"]))




-- mapWriterLS :: (a -> WriterS b) -> [a] -> WriterS [b]
-- mapWriterLS f xs = Writer(list2, list3) 
--     where
--         list1 = map runWriter (map f xs)
--         list2 = map fst list1
--         list3 = concat(map snd list1)

newtype State state a = State { runState :: state -> (a, state)}

instance Monad (State state) where
    return va = State (\s -> (va, s))
    ma >>= f =  State (\s -> let (va, news) = runState ma s in
                             let State h = f va in 
                                 (h news))

instance Applicative (State state) where
    pure = return 
    mf <*> ma = do 
        f <- mf 
        a <- ma 
        return (f a)

instance Functor (State state) where
    fmap f ma = pure f <*> ma


instance Monad Reader where
    return a = Reader (\x y -> a)
    mon >>= fun = Reader f 
                where f xs ys =
                        let v = runReader mon xs ys  in
                        runReader (fun v) xs ys 

eval (Plus e1 e2) = do
    rez1 <- eval e1
    rez2 <- eval e2
    return (rez1+ rez2)