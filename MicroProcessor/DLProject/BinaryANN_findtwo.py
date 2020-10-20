import numpy as np
from openpyxl import load_workbook

load_wb = load_workbook("./procedures1.xlsx", data_only=True)
load_ws = load_wb['Sheet1']

alphas = [0.001]
sums = 0

# compute sigmoid nonlinearity
def sigmoid(x):
    output = 1/(1+np.exp(-x))
    return output

# convert output of sigmoid function to its derivative
def sigmoid_output_to_derivative(output):
    return output*(1-output)
    
X_train = np.array([[55007, 55007]])
y_train = np.array([[0]])
ref_cells = load_ws['I1':'I77']
one_cells = load_ws['A1':'A77']
two_cells = load_ws['C1':'C77']
three_cells = load_ws['D1':'D77']

for ref, row in zip(ref_cells, one_cells):
    for refcell, cell in zip(ref,row):
        item = np.array([[refcell.value, cell.value]])
        y1 = np.array([[0]])
        X_train = np.append(X_train, item, axis=0)
        y_train = np.append(y_train, y1, axis=0)

for ref, row in zip(ref_cells, two_cells):
    for refcell, cell in zip(ref,row):
        item = np.array([[refcell.value, cell.value]])
        y1 = np.array([[1]])
        X_train = np.append(X_train, item, axis=0)
        y_train = np.append(y_train, y1, axis=0)
        
for ref, row in zip(ref_cells, three_cells):
    for refcell, cell in zip(ref,row):
        item = np.array([[refcell.value, cell.value]])
        y1 = np.array([[0]])
        X_train = np.append(X_train, item, axis=0)
        y_train = np.append(y_train, y1, axis=0)

X_train = X_train // 40000
print(X_train[78])

X_test = np.array([[56541, 56541]])
y_test = np.array([[0]])
ref_cell = load_ws['I78':'I119']
one_cell = load_ws['J1':'J42']
two_cell = load_ws['K1':'K41']
three_cell = load_ws['L1':'L40']

for ref, row in zip(ref_cell, one_cell):
    for refcell, cell in zip(ref,row):
        item = np.array([[refcell.value, cell.value]])
        y1 = np.array([[0]])
        X_test = np.append(X_test, item, axis=0)
        y_test = np.append(y_test, y1, axis=0)

for ref, row in zip(ref_cell, two_cell):
    for refcell, cell in zip(ref,row):
        item = np.array([[refcell.value, cell.value]])
        y1 = np.array([[1]])
        X_test = np.append(X_test, item, axis=0)
        y_test = np.append(y_test, y1, axis=0)
        
for ref, row in zip(ref_cell, three_cell):
    for refcell, cell in zip(ref,row):
        item = np.array([[refcell.value, cell.value]])
        y1 = np.array([[0]])
        X_test = np.append(X_test, item, axis=0)
        y_test = np.append(y_test, y1, axis=0)
        
X_test = X_test // 40000

for alpha in alphas:
    print ("\nTraining With Alpha:")
    print(str(alpha))
    np.random.seed(1)

    # randomly initialize our weights with mean 0
    synapse_0 = 2*np.random.random((2,5)) - 1
    synapse_1 = 2*np.random.random((5,1)) - 1

    for j in range(60000):

        # Feed forward through layers 0, 1, and 2
        layer_0 = X_train
        layer_1 = sigmoid(np.dot(layer_0,synapse_0))
        layer_2 = sigmoid(np.dot(layer_1,synapse_1))
        
        

        # how much did we miss the target value?
        layer_2_error = layer_2 - y_train

        if (j% 10000) == 0:
            print ("Train Error after ")
            print(str(j))
            print("iterations:")
            print(str(np.mean(np.abs(layer_3_error))))

        # in what direction is the target value?
        # were we really sure? if so, don't change too much.
        layer_2_delta = layer_2_error*sigmoid_output_to_derivative(layer_2)

        # how much did each l1 value contribute to the l2 error (according to the weights)?
        layer_1_error = layer_2_delta.dot(synapse_1.T)

        # in what direction is the target l1?
        # were we really sure? if so, don't change too much.
        layer_1_delta = layer_1_error * sigmoid_output_to_derivative(layer_1)

        
        synapse_1 -= alpha * (layer_1.T.dot(layer_2_delta))
        synapse_0 -= alpha * (layer_0.T.dot(layer_1_delta))

    print(X_test.shape[0])
    for ii in range(X_test.shape[0]):
        l0 = np.reshape(X_test[ii], (2,-1))   # l0 = 2x1 one by one
        l1 = sigmoid(np.dot(synapse_0.T,l0))  # l1 = 4x1
        l2 = sigmoid(np.dot(synapse_1.T,l1))  # l2 = 4x1
        
        sums = sums + np.abs(l2-y_test[ii])
    print("Test Error : ")
    print(sums/X_test.size)
    
    print('--------')
    print(synapse_0)
    print(synapse_1)
    print('--------')
