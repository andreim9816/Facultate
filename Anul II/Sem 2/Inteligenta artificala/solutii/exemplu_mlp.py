import pdb 
import timeit 
from sklearn import preprocessing
import random 
from sklearn.neural_network import MLPClassifier # importul clasei 
import numpy as np


# ------- Clasificare multiclass -------

num_samples = 100 # numarul de exemple de antrenare

train_data = np.random.random(size=(num_samples, 5)) # generam data de antrenare random, o matrice de num_samples x 5 
labels = [random.randint(0, 5) for i in range(num_samples)] # generam etichetele, numere naturale intre 0 si 5 => 6 clase

num_neurons = [7, 8] # numarul de perceptroni de pe primul si al doilea strat
net = MLPClassifier(hidden_layer_sizes=num_neurons, activation='tanh', solver='sgd', learning_rate_init=0.01, max_iter=1) 
net.fit(train_data, labels) 
print('numarul de straturi:', net.n_layers_) # 1 - stratul de intrare, fara ponderi
                                             # 2 - primul strat ascuns, cu 7 perceptroni
                                             # 3 - al doilea strat ascuns cu 8 perceptroni
                                             # 4 - stratul de iesire
                                             
print('numarul de perceptroni de pe ultimul strat:', net.n_outputs_) # stratul de iesire a fost adaugat automat 
                                                                     # numarul de perceptroni de pe ultimul strat = numarul de clase - pentru clasificare multiclass
                                                                     # 1 perceptron pentru clasificare binara
                                                                     
print('functia de activare de pe ultimul strat:', net.out_activation_) # functie de activare a fost adaugata automant in functie de numarul de clase
                                                                       # softmax -  pentru clasificare multiclass
                                                                       # logistic (=sigmoid) - pentru clasificare binara
  
# ------- Clasificare binara ------- 

num_samples = 100 # numarul de exemple de antrenare

train_data = np.random.random(size=(num_samples, 5)) # generam data de antrenare random, o matrice de num_samples x 5
labels = np.round(np.random.random(size=(num_samples))) # generam etichetele, 0 sau 1 => 2 clase

num_neurons = [7, 8] # numarul de perceptroni de pe primul si al doilea strat
net = MLPClassifier(hidden_layer_sizes=num_neurons, activation='tanh', solver='sgd', learning_rate_init=0.01, max_iter=1) 
net.fit(train_data, labels) 
print('numarul de straturi:', net.n_layers_) # 1 - stratul de intrare, fara ponderi
                                             # 2 - primul strat ascuns, cu 7 perceptroni
                                             # 3 - al doilea strat ascuns cu 8 perceptroni
                                             # 4 - stratul de iesire
                                             
print('numarul de perceptroni de pe ultimul strat:', net.n_outputs_) # numarul de perceptroni de pe ultimul strat = numarul de clase - pentru clasificare multiclass
                                                                     # 1 perceptron pentru clasificare binara
                                                                     
print('functia de activare de pe ultimul strat:', net.out_activation_) # functie de activare a fost adaugata automant in functie de numarul de clase
                                                                       # softmax -  pentru clasificare multiclass
                                                                       # logistic (=sigmoid) - pentru clasificare binara
 