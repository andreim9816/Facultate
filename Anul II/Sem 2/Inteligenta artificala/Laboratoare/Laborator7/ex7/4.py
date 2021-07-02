num_ep = 70
lr = 0.5

def forward_pass(X , W_1 , b_1 , W_2 , b_2):

    z_1 = X.dow(W_1) + b_1

    a_1 - np.tanh(z_1)

    z_2 = a_1.dot(W_2) + b_2