import numpy as np
from sklearn import preprocessing
from sklearn import svm
import sklearn.metrics as metrics
import matplotlib.pyplot as plt
from sklearn.model_selection import GridSearchCV
import pdb

train_images = np.loadtxt("data/train_images.txt")
train_labels = np.loadtxt("data/train_labels.txt", "int")

test_images = np.loadtxt("data/test_images.txt")
test_labels = np.loadtxt("data/test_labels.txt", "int")

print(f"Train images shape: {train_images.shape}")
print(f"Train labels shape: {train_labels.shape}")
print(f"Test images shape: {test_images.shape}")
print(f"Test labels shape: {test_labels.shape}")


# -- 1 --
def normalize_data(train_data, test_data, type=None):
    scaled_train_data = train_data
    scaled_test_data = test_data

    if type == "standard":
        scaler = preprocessing.StandardScaler()
        scaler.fit(train_data)

        scaled_train_data = scaler.transform(train_data)
        scaled_test_data = scaler.transform(test_data)
    elif type == "min_max":
        scaler = preprocessing.MinMaxScaler(feature_range=(0, 1))
        scaler.fit(train_data)

        scaled_train_data = scaler.transform(train_data)
        scaled_test_data = scaler.transform(test_data)

    elif type == "l1":
        scaled_train_data = train_data / np.expand_dims(np.sum(abs(train_data), axis=1), axis=1)
        scaled_test_data = test_data / np.expand_dims(np.sum(abs(test_data), axis=1), axis=1)

    elif type == "l2":
        scaled_train_data = train_data / np.expand_dims(np.sqrt(np.sum(abs(train_data) ** 2, axis=1)), axis=1)
        scaled_test_data = test_data / np.expand_dims(np.sqrt(np.sum(test_data ** 2, axis=1)), axis=1)

    return scaled_train_data, scaled_test_data


# -- 2 --
def svm_classifier(train_data, train_labels, test_data, c):
    linear_svm_model = svm.SVC(C=c, kernel='linear')
    linear_svm_model.fit(train_data, train_labels)
    predicted_labels_train = linear_svm_model.predict(train_data)
    predicted_labels_test = linear_svm_model.predict(test_data)
    return predicted_labels_train, predicted_labels_test


# -- 3 --
accuracies_train = []
accuracies_test = []

Cs = [1e-2, 1e-1, 1, 100]
scaled_train_data, scaled_test_data = normalize_data(train_images, test_images, "l2")
for C in Cs:
    predicted_labels_train, predicted_labels_test = svm_classifier(scaled_train_data, train_labels, scaled_test_data, C)
    accuracy_train = metrics.accuracy_score(train_labels, predicted_labels_train)
    accuracy_test = metrics.accuracy_score(test_labels, predicted_labels_test)
    accuracies_train.append(accuracy_train)
    accuracies_test.append(accuracy_test)
print(accuracies_train)
print(accuracies_test)

plt.plot(np.log10(Cs), accuracies_train)
plt.plot(np.log10(Cs), accuracies_test)
plt.legend(["train", "test"])
plt.xlabel("C")
plt.ylabel("accuracy")
plt.show()


# -- 4 --
num_classes = max(test_labels) + 1
best_c = Cs[int(np.argmax(accuracies_test))]
predicted_labels_train, predicted_labels_test = svm_classifier(scaled_train_data, train_labels, scaled_test_data, best_c)
conf_matrix = metrics.confusion_matrix(test_labels, predicted_labels_test)
precision_per_class = [conf_matrix[x][x] / np.sum(conf_matrix[:, x]) for x in range(num_classes)]
print(precision_per_class)
recall_per_class = [conf_matrix[x][x] / np.sum(conf_matrix[x, :]) for x in range(num_classes)]
print(recall_per_class)

# -- 5 --
# raw data
rbf_model = svm.SVC(C=1e-8, gamma='auto', kernel='rbf')
rbf_model.fit(train_images, train_labels)
predicted_labels_train_rbf = rbf_model.predict(train_images)
predicted_labels_test_rbf = rbf_model.predict(test_images)
raw_rbf_model_train_accuracy = metrics.accuracy_score(train_labels, predicted_labels_train_rbf)
raw_rbf_model_test_accuracy = metrics.accuracy_score(test_labels, predicted_labels_test_rbf)
print(f"Raw RBF train accuracy: {raw_rbf_model_train_accuracy * 100}%")
print(f"Raw RBF test accuracy: {raw_rbf_model_test_accuracy * 100}%")

# scaled data
rbf_model = svm.SVC(C=1000, kernel='rbf', gamma="auto")
rbf_model.fit(scaled_train_data, train_labels)
predicted_labels_train_rbf = rbf_model.predict(scaled_train_data)
predicted_labels_test_rbf = rbf_model.predict(scaled_test_data)
rbf_model_train_accuracy = metrics.accuracy_score(train_labels, predicted_labels_train_rbf)
rbf_model_test_accuracy = metrics.accuracy_score(test_labels, predicted_labels_test_rbf)
print(f"L2 RBF train accuracy: {rbf_model_train_accuracy * 100}%")
print(f"L2 RBF test accuracy: {rbf_model_test_accuracy * 100}%")
