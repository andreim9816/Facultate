import numpy as np
import sklearn
num_epoch = 70
lr = 0.1
x = [ [0 ,0] , [0 , 1 ] , [1 , 0] , [1 , 1]]
y = [-1 , 1, 1 , 1]

W = np.zeros((2 , 1))
B = 0
x = np.array(x)
y = np.array(y)


for ep in range(num_epoch):
    x , y = sklearn.utils.shuffle(x ,y)

    for idx in range(len(y)):
        yh = np.dot(x[idx] , W) + B
        loss = (yh - y[idx])**2 /2
        W = W -lr * (yh - y[idx]) * x[idx]
        B = B - lr * (yh - y[idx])

    accuracy = (np.sign(np.dot(x , W) + B) == y).mean()
    print("epoch: " + str(ep))
    print('accuracy: ' , str(accuracy))