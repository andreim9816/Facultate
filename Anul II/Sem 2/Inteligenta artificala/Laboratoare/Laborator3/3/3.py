import numpy as np
import matplotlib.pyplot as plt
from sklearn.naive_bayes import MultinomialNB # importa modelul naive Bayes
naive_bayes_model = MultinomialNB() # modelul naive Bayes

# incarcam imaginile si labels-urile
trainImages = np.loadtxt('data/train_images.txt')
trainLabels = np.loadtxt('data/train_labels.txt' , 'int')
testImages = np.loadtxt('data/test_images.txt')
testLabels = np.loadtxt('data/test_labels.txt' , 'int')



# b) Functie care returneaza pentru fiecare pixel al imaginii indexul intervalului din bins
def valuesToBins(matrix , bins):
    x = np.digitize(matrix , bins)
    return x - 1


"""
image = trainImages[0][:] # prima imagine, toata linia
image = np.reshape(image , (28 , 28))

plt.imshow(image.astype(np.uint8), cmap='gray')
plt.show()
"""
# c) Calculati acuratetea pe MULTIMEA DE TESTARE a clasificatorului NB

# definim numBins, generam un vector impartit in numBins intervale
numBins = 5
bins = np.linspace(start = 0 , stop = 255 , num = numBins)
# fiecare imagine este impartita in bins

trainBins = valuesToBins(trainImages , bins)
testBins = valuesToBins(testImages, bins)

naive_bayes_model.fit(trainBins , trainLabels) # antreneaza modelul
naive_bayes_model.predict(testBins)
print(naive_bayes_model.score(testBins , testLabels)) # calculeaza acuratetea

# d) Testati clasificatorul NB pe subsetul MNIST pt num_bins = {3 , 5 , 7 , 9 , 11}

num_bins = [3 , 5 , 7 , 9 , 11]
for value in num_bins:
    bins = np.linspace(start = 0 , stop = 255 , num = value)
    trainBins = valuesToBins(trainImages, bins)
    testBins = valuesToBins(testImages , bins)

    naive_bayes_model.fit(trainBins , trainLabels)
    print(naive_bayes_model.score(testBins , testLabels))

# e) Folosind num_bins cu cea mai buna acuratete, afisati cel putin 10 imagini clasificate gresit

bins = np.linspace(start = 0 , stop = 255 , num = 9)
trainBins = valuesToBins(trainImages , bins)
testBins = valuesToBins(testImages , bins)

naive_bayes_model.fit(trainBins , trainLabels)
contor = 10
predictedLabels = naive_bayes_model.predict(testBins)

for i in range(500):
    if predictedLabels[i] != testLabels[i]:
        contor-=1
        image = testImages[i][:]
        image = np.reshape(image , (28 , 28))
        plt.imshow(image.astype(np.uint8), cmap='gray')
        plt.title('Aceasta imagine a fost clasificata ca %d.' % predictedLabels[i])
        plt.show()

        if contor == 0:
            i = 501

# f) Determinati matricea de confuzie

def confussionMatrix(y_pred , y_true):
    matrix = np.zeros((10 , 10))

    for index in range(len(y_pred)):
        matrix[y_pred[index]][y_true[index]]+=1
    return matrix

print(confussionMatrix(testLabels , predictedLabels))
