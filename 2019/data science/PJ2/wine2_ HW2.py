import math
import numpy as np
print("[Student ID: 1816148]")
print("[Name: 김지현]")

while 1:
    print("1.Evaluate classifiers")
    print("2.Input the information about a wine")
    print("3.Predict wine quality")
    print("4.Cluster wines")
    print("5.Quit")
    ans=int(input())
    if ans==5:
        break
    elif ans==2:
        print("[ Wine information ]")
        a=float(input("1.fixed acidity: "))
        b=float(input("2.volatile acidity: "))
        c=float(input("3.citric acid: "))
        d=float(input("4.residual sugar: "))
        e=float(input("5.chlorides: "))
        f=float(input("6.free sulfur dioxide: "))
        g=float(input("7.total sulfur dioxide: "))
        h=float(input("8.density: "))
        i=float(input("9.pH: "))
        j=float(input("10.sulphates: "))
        k=float(input("11.alcohol: "))
        print("\n")
    elif ans==3:
        print("[ Predicted wine quality ]")
        from sklearn import tree
        data = np.genfromtxt("./winequality-red.csv", dtype= np.float32, delimiter = ";", skip_header= 1)
        X = data[:, 0:11] 
        Y = data[:, 11] 
        
        classifier = tree.DecisionTreeClassifier(random_state=0)
        classifier = classifier.fit(X, Y)
        test_sample= [[a, b, c, d, e, f, g, h, i, j, k]]
        
        predicted_class= classifier.predict(test_sample)
        predicted_proba= classifier.predict_proba(test_sample)
        print("1.Decision tree: ", int(predicted_class))
        

        from sklearn import svm
        data = np.genfromtxt("./winequality-red.csv", dtype= np.float32, delimiter = ";", skip_header= 1)
        X = data[:, 0:11]
        Y = data[:, 11] 
        
        classifier = svm.SVC(random_state=0)
        classifier = classifier.fit(X, Y)
        test_sample= [[a, b, c, d, e, f, g, h, i, j, k]]
        
        predicted_class= classifier.predict(test_sample)
        support_vectors= classifier.support_vectors_
        print("2.Support vector machine: ", int(predicted_class))
        

        from sklearn import linear_model
        data = np.genfromtxt("./winequality-red.csv", dtype= np.float32, delimiter = ";", skip_header= 1)
        X = data[:, 0:11]
        Y = data[:, 11] 
   
        classifier = linear_model.LogisticRegression(random_state=0)
        classifier = classifier.fit(X, Y)
        test_sample= [[a, b, c, d, e, f, g, h, i, j, k]]
 
        predicted_class= classifier.predict(test_sample)
        predicted_proba= classifier.predict_proba(test_sample)
        print("3.Logistic regression: ",   int(predicted_class))
        

        from sklearn import neighbors
        data = np.genfromtxt("./winequality-red.csv", dtype= np.float32, delimiter = ";", skip_header= 1)
        X = data[:, 0:11]
        Y = data[:, 11] 
        
        classifier = neighbors.KNeighborsClassifier(n_neighbors= 5)
        classifier = classifier.fit(X, Y)
        test_sample= [[a, b, c, d, e, f, g, h, i, j, k]]
        
        predicted_class= classifier.predict(test_sample)
        predicted_proba= classifier.predict_proba(test_sample)
        print("4.k-NN classifier: ",  int(predicted_class))
        print("\n")
    elif ans==1:
        print("[ Accuracy estimation ]")
        from sklearn import tree
        from sklearn.model_selection import cross_val_score
        data = np.genfromtxt("./winequality-red.csv", dtype= np.float32, delimiter = ";", skip_header= 1)
        sum = 0
        X = data[:, 0:11] 
        Y = data[:, 11]
        
        classifier = tree.DecisionTreeClassifier(random_state=0)
        scores = cross_val_score(classifier, X, Y, cv=5)
        for i in scores:
            sum += i
        accuracy= sum / 5*100
        print("1. Decision tree: ", round(accuracy, 1), "%")
        
        
        from sklearn import svm
        from sklearn.model_selection import cross_val_score
        data = np.genfromtxt("./winequality-red.csv", dtype= np.float32, delimiter = ";", skip_header= 1)
        sum = 0
        X = data[:, 0:11] 
        Y = data[:, 11]
        
        classifier = svm.SVC(random_state=0)
        scores = cross_val_score(classifier, X, Y, cv=5)
        for i in scores:
            sum += i
        accuracy= sum / 5*100
        print("2.Support vector machine: ", round(accuracy, 1), "%")
        
        from sklearn import linear_model
        from sklearn.model_selection import cross_val_score
        data = np.genfromtxt("./winequality-red.csv", dtype= np.float32, delimiter = ";", skip_header= 1)
        sum = 0
        X = data[:, 0:11] 
        Y = data[:, 11]
        
        classifier = linear_model.LogisticRegression(random_state=0)
        scores = cross_val_score(classifier, X, Y, cv=5)
        for i in scores:
            sum += i
        accuracy= sum / 5*100
        print("3.Logistic regression: ", round(accuracy, 1), "%")
      
        
        from sklearn import neighbors
        from sklearn.model_selection import cross_val_score
        data = np.genfromtxt("./winequality-red.csv", dtype= np.float32, delimiter = ";", skip_header= 1)
        sum = 0
        X = data[:, 0:11] 
        Y = data[:, 11]
        
        classifier = neighbors.KNeighborsClassifier(n_neighbors= 5)
        scores = cross_val_score(classifier, X, Y, cv=5)
        for i in scores:
            sum += i
        accuracy= sum / 5*100
        print("4.k-NN classifier: ", round(accuracy, 1), "%")
        
        
        print("[ Confusion matrix ]")
        
        from sklearn import tree
        from sklearn.metrics import confusion_matrix
        data = np.genfromtxt("./winequality-red.csv", dtype= np.float32, delimiter = ";", skip_header= 1)
        
        classifier = tree.DecisionTreeClassifier(random_state=0)
        classifier = classifier.fit(data[:, 0:11], data[:, 11])
        y_true= data[:, 11]
        y_pred= classifier.predict(data[:, 0:11])
        cm = confusion_matrix(y_true, y_pred)
        
        print("1. Decision tree: \n", cm)
        
        
        from sklearn import svm
        from sklearn.metrics import confusion_matrix
        data = np.genfromtxt("./winequality-red.csv", dtype= np.float32, delimiter = ";", skip_header= 1)
        
        classifier = svm.SVC(random_state=0)
        classifier = classifier.fit(data[:, 0:11], data[:, 11])
        y_true= data[:, 11]
        y_pred= classifier.predict(data[:, 0:11])
        cm = confusion_matrix(y_true, y_pred)
        
        print("2.Support vector machine: \n", cm)
        
        
        from sklearn import linear_model
        from sklearn.metrics import confusion_matrix
        data = np.genfromtxt("./winequality-red.csv", dtype= np.float32, delimiter = ";", skip_header= 1)

        classifier = linear_model.LogisticRegression(random_state=0)
        classifier = classifier.fit(data[:, 0:11], data[:, 11])
        y_true= data[:, 11]
        y_pred= classifier.predict(data[:, 0:11])
        cm = confusion_matrix(y_true, y_pred)
        
        print("3.Logistic regression: \n", cm)
        
    
        from sklearn import neighbors
        from sklearn.metrics import confusion_matrix
        data = np.genfromtxt("./winequality-red.csv", dtype= np.float32, delimiter = ";", skip_header= 1)
        
        classifier = neighbors.KNeighborsClassifier(n_neighbors= 5)
        classifier = classifier.fit(data[:, 0:11], data[:, 11])
        y_true= data[:, 11]
        y_pred= classifier.predict(data[:, 0:11])
        cm = confusion_matrix(y_true, y_pred)
        
        print("4.k-NN classifier: \n", cm)
        
        print("[ Precision ]")
        
        
        from sklearn import tree
        from sklearn.metrics import precision_score
        data = np.genfromtxt("./winequality-red.csv", dtype= np.float32, delimiter = ";", skip_header= 1)

        classifier = tree.DecisionTreeClassifier(random_state=0)
        classifier = classifier.fit(data[:, 0:11], data[:, 11])
        y_true= data[:, 11]
        y_pred= classifier.predict(data[:, 0:11])
        
        
        print("1. Decision tree: \n", precision_score(y_true, y_pred, average=None))
        
        
        from sklearn import svm
        from sklearn.metrics import precision_score
        data = np.genfromtxt("./winequality-red.csv", dtype= np.float32, delimiter = ";", skip_header= 1)

        classifier = svm.SVC(random_state=0)
        classifier = classifier.fit(data[:, 0:11], data[:, 11])
        y_true= data[:, 11]
        y_pred= classifier.predict(data[:, 0:11])
        
        print("2.Support vector machine: \n", precision_score(y_true, y_pred, average=None))
        
        
        from sklearn import linear_model
        from sklearn.metrics import precision_score
        data = np.genfromtxt("./winequality-red.csv", dtype= np.float32, delimiter = ";", skip_header= 1)

        classifier = linear_model.LogisticRegression(random_state=0)
        classifier = classifier.fit(data[:, 0:11], data[:, 11])
        y_true= data[:, 11]
        y_pred= classifier.predict(data[:, 0:11])
        
        print("3.Logistic regression: \n", precision_score(y_true, y_pred, average=None))
        
    
        from sklearn import neighbors
        from sklearn.metrics import precision_score
        data = np.genfromtxt("./winequality-red.csv", dtype= np.float32, delimiter = ";", skip_header= 1)
        
        classifier = neighbors.KNeighborsClassifier(n_neighbors= 5)
        classifier = classifier.fit(data[:, 0:11], data[:, 11])
        y_true= data[:, 11]
        y_pred= classifier.predict(data[:, 0:11])
        
        
        print("4.k-NN classifier: \n", precision_score(y_true, y_pred, average=None))
        
        
        print("[ Recall ]")
        
        from sklearn import tree
        from sklearn.metrics import recall_score
        data = np.genfromtxt("./winequality-red.csv", dtype= np.float32, delimiter = ";", skip_header= 1)
        
        classifier = tree.DecisionTreeClassifier(random_state=0)
        classifier = classifier.fit(data[:, 0:11], data[:, 11])
        y_true= data[:, 11]
        y_pred= classifier.predict(data[:, 0:11])
        
        
        print("1. Decision tree: \n", recall_score(y_true, y_pred, average=None))
        
        
        from sklearn import svm
        from sklearn.metrics import recall_score
        data = np.genfromtxt("./winequality-red.csv", dtype= np.float32, delimiter = ";", skip_header= 1)
        
        classifier = svm.SVC(random_state=0)
        classifier = classifier.fit(data[:, 0:11], data[:, 11])
        y_true= data[:, 11]
        y_pred= classifier.predict(data[:, 0:11])
        
        print("2.Support vector machine: \n", recall_score(y_true, y_pred, average=None))
        
        
        from sklearn import linear_model
        from sklearn.metrics import recall_score
        data = np.genfromtxt("./winequality-red.csv", dtype= np.float32, delimiter = ";", skip_header= 1)

        classifier = linear_model.LogisticRegression(random_state=0)
        classifier = classifier.fit(data[:, 0:11], data[:, 11])
        y_true= data[:, 11]
        y_pred= classifier.predict(data[:, 0:11])
        
        print("3.Logistic regression: \n", recall_score(y_true, y_pred, average=None))
        
    
        from sklearn import neighbors
        from sklearn.metrics import recall_score
        data = np.genfromtxt("./winequality-red.csv", dtype= np.float32, delimiter = ";", skip_header= 1)
        
        classifier = neighbors.KNeighborsClassifier(n_neighbors= 5)
        classifier = classifier.fit(data[:, 0:11], data[:, 11])
        y_true= data[:, 11]
        y_pred= classifier.predict(data[:, 0:11])
        
        
        print("4.k-NN classifier: \n", recall_score(y_true, y_pred, average=None))
    
    elif ans==4:
        
        sel=input("Select the algorithm ((h)ierarchicalor (k)-means): ")
        if sel=='h':
            from sklearn.cluster import AgglomerativeClustering
            data = np.genfromtxt("./winequality-red.csv", dtype= np.float32, delimiter = ";", skip_header= 1)
            X=data[:, 0:11]
            
            cluster=int(input("Input the number of clusters: "))
            model = AgglomerativeClustering(n_clusters= cluster)
            model.fit(X)
            first=int(input("Input the number of the first wine: "))
            second=int(input("Input the number of the second wine: "))
            
    
            if model.labels_[first]== model.labels_[second]:
                print("Result : %d and %d are in the same cluster"%(first,second))
            else:
                print("Result : %d and %d are in the different cluster"%(first,second))
        if sel=='k':
            
            from sklearn.cluster import KMeans
            data = np.genfromtxt("./winequality-red.csv", dtype= np.float32, delimiter = ";", skip_header= 1)
            X=data[:, 0:11]
        
            cluster=int(input("Input the number of clusters: "))
            model = KMeans(n_clusters = cluster, random_state=0)
            model.fit(X)
            first=int(input("Input the number of the first wine: "))
            second=int(input("Input the number of the second wine: "))
            
            if model.predict([data[first, 0:11]])== model.predict([data[second, 0:11]]):
                print("Result : %d and %d are in the same cluster"%(first,second))
            else:
                print("Result : %d and %d are in the different cluster"%(first,second))
                