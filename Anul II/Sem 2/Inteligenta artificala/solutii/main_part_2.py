import numpy as np
import matplotlib.pyplot as plt
from sklearn.utils import shuffle
import pdb
import matplotlib.pyplot as plt

# y_hat = sigmoid(tanh(X * W_1 + b_1) * W_2 + b_2)


def sigmoid(x):
    return 1.0 / (1.0 + np.exp(-1.0 * x))


def tanh_derivative(x):
    return 1 - np.tanh(x) ** 2


def forward(x, w_1, b_1, w_2, b_2):
    z_1 = np.matmul(x, w_1) + b_1
    a_1 = np.tanh(z_1)

    z_2 = np.matmul(a_1, w_2) + b_2
    a_2 = sigmoid(z_2)
    return z_1, a_1, z_2, a_2


def backward(a_1, a_2, z_1, W_2, X, y, num_samples):
    dz_2 = a_2 - y

    dw_2 = np.matmul(a_1.T, dz_2) / num_samples
    db_2 = np.sum(dz_2, axis=0) / num_samples

    da_1 = np.matmul(dz_2, W_2.T)
    dz_1 = np.multiply(da_1, tanh_derivative(z_1))
    dw_1 = np.matmul(X.T, dz_1) / num_samples
    db_1 = np.sum(dz_1, axis=0) / num_samples

    return dw_1, db_1, dw_2, db_2


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
    xx = np.random.normal(0, 1, (400000))
    yy = np.random.normal(0, 1, (400000))
    X = np.array([xx, yy]).transpose()
    X = np.concatenate((X, X_))
    _, _, _, output = forward(X, W_1, b_1, W_2, b_2)
    y = np.squeeze(np.round(output))
    plt.plot(X[y == 0, 0], X[y == 0, 1], 'b+')
    plt.plot(X[y == 1, 0], X[y == 1, 1], 'r+')
    plt.show(block=False)
    plt.pause(0.1)


X = np.array([
            [0, 0],
            [0, 1],
            [1, 0],
            [1, 1]])
print('X.shape = ', X.shape)
y = np.expand_dims(np.array([0, 1, 1, 0]), 1)
print('y.shape = ', y.shape)

num_hidden_neurons = 2
num_output_neurons = 1

W_1 = np.random.normal(0, 1, (2, num_hidden_neurons))
b_1 = np.zeros(num_hidden_neurons)
W_2 = np.random.normal(0, 1, (num_hidden_neurons, num_output_neurons))
b_2 = np.zeros(num_output_neurons)

num_samples = X.shape[0]

num_epochs = 250
lr = 0.5
for epoch_idx in range(num_epochs):
    X, y = shuffle(X, y)

    z_1, a_1, z_2, a_2 = forward(X, W_1, b_1, W_2, b_2)

    loss = (-y * np.log(a_2) - (1 - y) * np.log(1 - a_2)).mean()
    accuracy = (np.round(a_2) == y).mean()
    print(f"epoch_idx: {epoch_idx}: loss = {loss}, accuracy = {accuracy}")

    plot_decision(X, W_1, W_2, b_1, b_2)

    dw_1, db_1, dw_2, db_2 = backward(a_1, a_2, z_1, W_2, X, y, num_samples)
    W_1 = W_1 - lr * dw_1
    b_1 = b_1 - lr * db_1
    W_2 = W_2 - lr * dw_2
    b_2 = b_2 - lr * db_2

