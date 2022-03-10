data Punct = Pt [Int] deriving(Show)

data Arb = Vid | FF Int | N Arb Arb deriving(Show)

class ToFromArb a where
    toArb :: a -> Arb
    fromArb :: Arb -> a


instance ToFromArb Punct where
    toArb (Pt []) = Vid
    toArb (Pt (h:t)) = N (FF h) (toArb (Pt t))

    fromArb Vid = (Pt [])
    fromArb (FF val) = (Pt [val])
    fromArb (N arb1 arb2) = 
        let (Pt st) = fromArb arb1 in
        let (Pt dr) = fromArb arb2 in
        Pt (st ++ dr)

-- toArb (Pt [1,2,3])
-- fromArb $ N (F 1 ) (N (F 2 ) (N (F 3 ) Vid ) ) :: Punct

data Btree a = Leaf a | Node (Btree a) (Btree a)

-- showBt :: Show a -> Btree a -> String
showBt(Leaf a) = show a
showBt(Node t1 t2) = "(" ++ (showBt t1) ++ " , " ++ (showBt t2) ++ ")"

instance (Show a) => Show (Btree a) where
    show = showBt

exTree = Node (Node (Leaf 'a') (Leaf 'b')) (Leaf 'c') 

data Season = Spring | Summer 
eqSeason :: Season -> Season -> Bool
eqSeason Spring Spring = True
eqSeason Summer Summer = True
eqSeason _ _ = False

instance Eq Season where 
    (==) = eqSeason