import numpy as np

# incarcam
train_images = np.loadtxt('data/train_images.txt')
test_images = np.loadtxt('data/test_images.txt')
train_labels = np.loadtxt('data/train_labels.txt' , 'int')
test_labels = np.loadtxt('data/test_labels.txt' , 'int')

# creez clasa KnnClassifier
class Knn_classifier:

    def __init__(self, train_images, train_labels):
        self.train_images = train_images
        self.train_labels = train_labels

    def classify_image(self, test_image, num_neighbors=3, metric='l2'):

        if (metric == 'l2'):
            distances = np.sqrt(np.sum( (self.train_images - test_image) ** 2, axis=1))
        elif (metric == 'l1'):
            distances = np.sum(abs(self.train_images - test_image), axis=1)
        else:
            print('Metric is unknown!')

        sort_index = np.argsort(distances)
        sort_index = sort_index[:num_neighbors]
        nearest_labels = self.train_labels[sort_index]
        histc = np.bincount(nearest_labels)

        return np.argmax(histc)

classifier = Knn_classifier(train_images , train_labels)
predicted_labels = classifier.classify_images(test_images , 3 , metric = 'l2')
