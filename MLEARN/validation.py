import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
import uproot
from sklearn.metrics import classification_report, ConfusionMatrixDisplay, roc_curve, roc_auc_score, confusion_matrix, auc
import joblib
import sys
import os.path
import glob
import readline
import shutil

#load the model
clf_route = sys.argv[1]#input('\n\n Enter path to the classifier to begin: \n\n')
clf = joblib.load(clf_route)
#load the validation data
input = sys.argv[2]+"/*.root" #input('\n\nEnter the path to the validation data directory.\n\n *** End the file path with "/*.root ***.\n\n')
location = os.path.join(input)
filenames = sorted(glob.glob(location))
d = {}
z = {}

var = ['n100','n100_prev','n9', 'n9_prev', 'innerPE', 'dt_prev_us', 'drPrevr', 'x', 'y', 'z', 'closestPMT', 'good_pos', 'good_pos_prev', 'subid']
ext_var = ['mcid','mc_energy']
cond = '(n100>0)&(n100_prev>0)'#&(subid==0)'

for f in filenames:
  with uproot.open(f) as f1:
    data = f1["data"]
    b, a = f.rsplit('/',1)
    c, e = a.split('_',1)
    d[c] = data.arrays(var,cond,library='pd')
    z[c] = data.arrays(ext_var,cond,library='pd')
    #d[c] = data.arrays(['n100', 'n100_prev', 'innerPE', 'dt_prev_us', 'drPrevr', 'x', 'y', 'z', 'good_pos', 'good_pos_prev','subid'], '(n100>0)&(n100_prev>0)',library='pd')

for x, y in d.items():
  if (x == 'fn'):
    y['label'] = 1
    y['source'] = 1
  elif (x == 'geo'):
    y['label'] = 0
    y['source'] = 2
  elif (x == 'heysham'):
    y['label'] = 0
    y['source'] = 3
  elif (x == 'hinkley'):
    y['label'] = 0
    y['source'] = 4
  elif (x == 'sizewell'):
    y['label'] = 0
    y['source'] = 5
  elif (x == 'gravelines'):
    y['label'] = 0
    y['source'] = 6
  elif (x == 'li9'):
    y['label'] = 0
    y['source'] = 7
  elif (x == 'n17'):
    y['label'] = 0
    y['source'] = 8
  elif (x == 'torness'):
    y['label'] = 0
    y['source'] = 9
  elif (x == 'world'):
    y['label'] = 0
    y['source'] = 10
  elif (x == 'energy'):
    y['label'] = 0
    y['source'] = 11
  else:
    print('Please rename your root files!')
    sys.exit()

#neutron model
X = pd.concat(d.values(), ignore_index=True, keys=d.keys())
y = X[['label']]
y = y.to_numpy()
y = y.flatten()
Z = pd.concat(z.values(), ignore_index=True, keys=z.keys())
#print(y)

source = X[['source']]
source = source.to_numpy()
source = source.flatten()
X = X.drop(['label', 'source'], axis=1)
#print('\n\nData:')
#print(X)
print('\n\nApplying the model ...')
pred = clf.predict(X.values)
prob = clf.predict_proba(X.values)
scores = clf.decision_function(X.values)
print ('\n\nClassification Report:')
print (classification_report(y, pred))
cm = confusion_matrix(y, pred, labels=clf.classes_)
print ('\n\nConfusion Matrix: ')
print(cm)
print ('\n\nCreating figures ...')
ConfusionMatrixDisplay.from_predictions(y, pred)
plt.title("Fast Neutron finder Validation")
plt.savefig('cm_fnfinder_validation.pdf')
#plt.show(block=False)
#plt.pause(3)
plt.clf()

signal=prob[:,1]
fpr, tpr, _ = roc_curve(y,signal)
auc = auc(fpr, tpr)
plt.plot(fpr, tpr, marker=',', label='Fast Neutrons (area = {:.2f})'.format(auc))
plt.xlabel('False Positive Rate')
plt.ylabel('True Positive Rate')
plt.legend(loc='best')
plt.title('Fast Neutron finder Validation')
plt.savefig('roc_fnfinder_validation.pdf')
#plt.show(block=False)
#plt.pause(3)
plt.clf()

X.loc[:,'classifier'] = pred
X.loc[:,'label'] = y
X.loc[:,'scores'] = scores
ts = X.loc[(X.classifier==0) & (X.label==0)]
tb = X.loc[(X.classifier==1) & (X.label==1)]
fs = X.loc[(X.classifier==0) & (X.label==1)]
fb = X.loc[(X.classifier==1) & (X.label==0)]
#plot the events by their decision function score
plt.hist(ts.scores.values.flatten(), bins=50, label='True Other', alpha=.5)
plt.hist(tb.scores.values.flatten(), bins=50, label='True Fast Neutron', alpha=.5)
plt.hist(fs.scores.values.flatten(), bins=50, label='False Other', alpha=.5)
plt.hist(fb.scores.values.flatten(), bins=50, label='False Fast Neutron', alpha=.5)
plt.yscale('log')
plt.title('Fast Neutron Finder scores, validation')
plt.legend(loc='best')
plt.xlabel('Decision scores')
plt.ylabel('Frequency (log)')
plt.savefig('df_fnfinder_validation.pdf')
#plt.show(block=False)
#plt.pause(3)
plt.clf()

X.loc[:,'source'] = source
X.loc[:,'prob_fn'] = prob[:,1]
X.loc[:,'prob_other'] = prob[:,0]
for i in ext_var:
  X.loc[:,i] = Z[i]
# X_dup = X[X.duplicated(keep=False)]
# X_dup = X_dup.iloc[::2,:]
# X = pd.concat([X, X_dup, X_dup]).drop_duplicates(keep=False)
# X = pd.concat([X,X_dup],ignore_index=False)
# X = X.sort_index()
print ('Added ML data:\n\n',X, '\n\n')
print('Outputting X to a csv...\n\n')
X.to_csv('classified_valdata.csv')

# df1 = X.loc[X.source==1]
# df2 = X.loc[X.source==2]
# df3 = X.loc[X.source==3]
# df4 = X.loc[X.source==4]
# df5 = X.loc[X.source==5]
# df6 = X.loc[X.source==6]
# df7 = X.loc[X.source==7]
# df8 = X.loc[X.source==8]
# df9 = X.loc[X.source==9]
# df10 = X.loc[X.source==10]
# df11 = X.loc[X.source==11]
# print('Copying and updating ROOT files...\n\n')
# d1 = [df1,df2,df3,df4,df5,df6,df7,df8,df9,df10]
# for df in d1:
#   df = df.drop(['source', 'label'], axis=1)
#   for file in filenames:
#     fil = shutil.copy(file, os.getcwd())
#     with uproot.update(fil) as f3:
#       f3.mktree("M",{"prediction":"i8","score":"f8","fn_prob":"f8","other_prob":"f8"} ,"ML_data")
#       f3["M"].extend({"prediction":df.loc[:,"classifier"], "score":df.loc[:,"scores"], "fn_prob":df.loc[:,"prob_fn"], "other_prob":df.loc[:,"prob_other"]})

# print ('END')
