import csv
import re
from sklearn import preprocessing
from sklearn.kernel_ridge import KernelRidge
from sklearn.metrics import mean_squared_error, mean_absolute_error

from Bag_of_Words import *


def read_data(file_path):
    data = []
    scores = []

    with open(file_path, mode='r') as csv_file:
        csv_reader = csv.DictReader(csv_file)
        for row in csv_reader:
            data.append(re.sub("[-.,;:!?\"\'\/()_*=`]", "", row["essay"].lower()).split())
            scores.append(int(row["score"]))
    return data, scores

# -- 1 --
train_data, train_scores = read_data("Data/train_data.csv")
test_data, test_scores = read_data("Data/test_data.csv")

print(f"Train data length: texts: {len(train_data)}, scores: {len(train_scores)}")
print(f"Test data length: texts: {len(test_data)}, scores: {len(test_scores)}")

# -- 2 --
bow_model = Bag_of_words()
bow_model.build_vocabulary(train_data)
print(f"Vocabulary length: {len(bow_model.vocabulary)}")

# -- 3 --
train_features = bow_model.get_features(train_data)
test_features = bow_model.get_features(test_data)

# -- 4 --
scaler = preprocessing.Normalizer(norm='l2')
scaler.fit(train_features)
train_features = scaler.transform(train_features)
test_features = scaler.transform(test_features)

# -- 5 --
krr_model = KernelRidge(kernel="rbf", alpha=pow(10, -4.25))
krr_model.fit(train_features, train_scores)

predicted_scores_train = krr_model.predict(train_features)
predicted_scores_test = krr_model.predict(test_features)

print("MSE train: ", mean_squared_error(train_scores, predicted_scores_train))  # 0.643
print("MSE test: ", mean_squared_error(test_scores, predicted_scores_test))     # 1.080

print("MAE train: ", mean_absolute_error(train_scores, predicted_scores_train)) # 0.630
print("MAE test: ", mean_absolute_error(test_scores, predicted_scores_test))    # 0.832
