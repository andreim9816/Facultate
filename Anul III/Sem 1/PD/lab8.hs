
import Test.QuickCheck

double x = 2 * x
triple x = 3 * x
penta 2 = 9
penta x = 5 * x

test x = (double x + triple x) == (penta x)