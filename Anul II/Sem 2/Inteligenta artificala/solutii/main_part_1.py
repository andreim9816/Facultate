import numpy as np
import matplotlib.pyplot as plt
from sklearn.utils import shuffle
import pdb


def compute_y(x, W, bias):
    return (-x * W[0] - bias) / (W[1] + 1e-10)


def plot_decision_boundary(X, y, W, b, current_x, current_y):
    x1 = -1
    y1 = compute_y(x1, W, b)
    x2 = 2
    y2 = compute_y(x2, W, b)

    # sterge continutul ferestrei
    plt.clf()

    # ploteaza multimea de antrenare
    color = 'r'
    if (current_y == -1):
        color = 'b'

    plt.plot(X[y == -1, 0], X[y == -1, 1], 'b+')
    plt.plot(X[y == 1, 0], X[y == 1, 1], 'r+')

    # ploteaza exemplul curent
    plt.plot(current_x[0], current_x[1], color + 's')

    # afisarea dreptei de decizie
    plt.plot([x1, x2], [y1, y2], 'black')
    plt.show(block=False)
    plt.pause(0.3)


def compute_accuracy(x, y, w, b):
    accuracy = (np.sign(np.dot(x, w) + b) == y).mean()
    return accuracy

def widrow_hoff(x, y, num_epochs, learning_rate):
    num_samples = x.shape[0]
    num_features = x.shape[1]

    w = np.zeros(num_features)
    b = 0
    for epoch_idx in range(num_epochs):
        x, y = shuffle(x, y)
        for sample_idx in range(num_samples):
            y_hat = np.dot(x[sample_idx, :], w) + b
            w = w - learning_rate * (y_hat - y[sample_idx]) * x[sample_idx, :]
            b = b - learning_rate * (y_hat - y[sample_idx])

            loss = (y_hat - y[sample_idx]) ** 2
            print(f"epoch: {epoch_idx}, sample: {sample_idx}: sample_loss = {loss}, set_accuracy = {compute_accuracy(x, y, w, b)}")
            plot_decision_boundary(x, y, w, b,  x[sample_idx, :], y[sample_idx])
    return w, b


# -- 2 --
x = np.array([[0, 0], [0, 1], [1, 0], [1, 1]])
y = np.array([-1, 1, 1, 1])

# -- 3 --
# x = np.array([[0, 0], [0, 1], [1, 0], [1, 1]])
# y = np.array([-1, 1, 1, -1])

num_epochs = 70
learning_rate = 0.1

w, b = widrow_hoff(x, y, num_epochs, learning_rate)
accuracy = compute_accuracy(x, y, w, b)
print(f"Final accuracy is: {accuracy * 100}%")
print(f"w = {w}, b = {b}")



