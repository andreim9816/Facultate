string1 = input("string = ")
string2 = input("string = ")

ok = 1
for i in range(len(string1)):
    char = string1[i]
    index = string2.find(char)
    if index != -1:
        string2 = string2[0 : index ] + string2[ index + 1 :]
    else:
        print("Nu sunt anagrame")
        ok = 0
        break

if ok == 1:
    print("Sunt anagrame")
