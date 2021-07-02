import numpy as np
from sklearn.utils import shuffle
from sklearn import preprocessing

# load training data
training_data = np.load('data/training_data.npy')
prices = np.load('data/prices.npy')
# print the first 4 samples
print('The first 4 samples are:\n ', training_data[:4])
print('The first 4 prices are:\n ', prices[:4])
# shuffle
#asa se face la cross validare
#nu vrem sa avem mereu aceleasi grupe
#facem o amestecare a datelor ca sa avem folduri diferite

training_data, prices = shuffle(training_data, prices, random_state=0)

# --- 1 ---
def normalize_data(training , testing = None):
      scaler = preprocessing.StandardScaler()
      scaler.fit(training)
      scaled_x_train = scaler.transform(training)
      if testing is None:
          return scaled_x_train
      scaled_x_test = scaler.transform(testing)
      return scaled_x_train , scaled_x_test
      scaled_test_data = scaler.transform(test_data)
      return (scaled_train_data, scaled_test_data)

# --- 2 ---


num_samples_fold = len(training_data) // 3
training_data_1 , prices_1 = training_data[:num_samples_fold] , prices[:num_samples_fold]
training_data_2 , prices_2 = training_data[num_samples_fold : 2 * num_samples_fold] , prices[num_samples_fold : 2 * num_samples_fold]
training_data_3 , prices_3 = training_data[2 * num_samples_fold:] , prices[2 * num_samples_fold:]

from sklearn.metrics import mean_squared_error , mean_absolute_error
from sklearn.linear_model import LinearRegression , Ridge , Lasso

def normalize_train_model(model , training_samples , labels , testing_data , testing_labels):
    training_samples , testing_data = normalize_data(training_samples , testing_data)
    model.fit(training_samples , labels)
    return mean_absolute_error(testing_labels , model.predict(testing_data)) , mean_squared_error(testing_labels , model.predict(testing_data))

model = LinearRegression()
mae_1 , mse_1 = normalize_train_model(model , np.concatenate((training_data_1 , training_data_2)) ,
                                      np.concatenate((prices_1 , prices_2)) , training_data_3 , prices_3)
mae_2 , mse_2 = normalize_train_model(model , np.concatenate((training_data_1 , training_data_3)) ,
                                      np.concatenate((prices_1 , prices_3)) , training_data_2 , prices_2)
mae_3 , mse_3 = normalize_train_model(model , np.concatenate((training_data_2 , training_data_3)) ,
                                      np.concatenate((prices_2 , prices_3)) , training_data_1 , prices_1)
print("Mean MAE " , (mae_1 + mae_2 + mae_3) / 3)
print("Mean MSE " , (mse_1 + mse_2 + mse_3) / 3)

########### 3

alpha = [1 , 10 , 100 ,1000]


