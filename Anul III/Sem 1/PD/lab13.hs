import Control.Monad.State
-- model

type Input = String
type Output = String 
type InOutWorld = (Input, Output)
type MyIOState a = State InOutWorld a

myGetChar :: MyIOState Char
myGetChar = state
    (\(input, output) -> if input == "" then error "Input is over!"
                                else let (head:tail) = input in 
                                    (head, (tail, output)))


myPutChar :: Char -> MyIOState ()
myPutChar c = state (\(input, output) -> ((), (input, output ++ [c])))

-- plan care citeste 3 caracter si le afieaza in ordine inversa

ex1 = do
    c1 <- myGetChar
    c2 <- myGetChar
    c3 <- myGetChar

    myPutChar c3
    myPutChar c2
    myPutChar c1

-- apel: runState ex1("salut ce mai faci", "")

myPutStrLn "" =  myPutChar '\n'
myPutStrLn (h:t) = myPutChar h >> myPutStrLn t  

myGetLine = do 
    c <- myGetChar 
    if c == '\n' then return "" 
                 else do  
                     ramas <- myGetLine 
                     return (c:ramas)


-- apel, ctieste 2 linii si afiseaza invers 
-- runState ex2 ("Salut\nCe\nMai\nFaci\n", "")
ex2 = do 
    linie1 <- myGetLine
    linie2 <- myGetLine 
    myPutStrLn linie2 
    myPutStrLn linie1

-- aceeasi chestie dar fara do: 
myGetLine' = myGetChar >>= (\c -> if c == '\n' then return ""
                                               else myGetLine >>= (\ramas -> return (c:ramas)))



runIO plan input = let ((), (input, output)) = runState plan (input, "") in output

myReadLn :: Read a => MyIOState a 
myReadLn = do 
    x <- myGetLine 
    return (read x)

--apel: runIO ex2 "Salut\nCe\nMai\nFaci\n"