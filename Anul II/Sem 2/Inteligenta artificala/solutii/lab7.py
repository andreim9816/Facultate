import numpy as np 
import matplotlib.pyplot as plt
from sklearn.utils import shuffle
import pdb 
import matplotlib.pyplot as plt


def compute_y(x, W, bias): 
    # dreapta de decizie
    # [x, y] * [W[0], W[1]] + b = 0
    return (-x*W[0] - bias) / (W[1] + 1e-10)

def plot_decision(X_, W_1, W_2, b_1, b_2):
    # sterge continutul ferestrei
    plt.clf()
    # ploteaza multimea de antrenare 
    plt.ylim((-0.5, 1.5))
    plt.xlim((-0.5, 1.5)) 
    xx = np.random.normal(0, 1, (100000))   
    yy = np.random.normal(0, 1, (100000))  
    X = np.array([xx, yy]).transpose() 
    X = np.concatenate((X, X_)) 
    _, _, _, output = forward(X, W_1, b_1, W_2, b_2)
    y = np.squeeze(np.round(output))  
    plt.plot(X[y == 0, 0], X[y == 0, 1], 'b+')
    plt.plot(X[y == 1, 0], X[y == 1, 1], 'r+') 
    plt.show(block=False)
    plt.pause(0.1) 
    
def sigmoid(x):
    return 1.0/(1.0 + np.exp(-1.0 * x))
  
# derivata tanh
def tanh_derivative(x):
    return 1 - np.tanh(x) ** 2;
    
    
X = np.array([
            [0, 0],
            [0, 1],
            [1, 0],
            [1, 1]])
print('X.shape = ', X.shape) 
y = np.expand_dims(np.array([0, 1, 1, 0]), 1)
print('y.shape = ', y.shape) 