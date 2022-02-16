import pandas as pd
import numpy as np
import sys

file = sys.argv[1]

df = pd.read_csv(file)

fn = fn_tot = 0
heysham_2 = heysham_2_tot = 0
torness = torness_tot = 0
sizewell_b = sizewell_b_tot = 0
hinkley_c = hinkley_c_tot = 0
gravelines = gravelines_tot = 0
world = world_tot = 0
geo = geo_tot = 0
li9 = li9_tot = 0
n17 = n17_tot = 0

for i in range(len(df)-1):
    if df['source'][i]==1:
        fn_tot+=1
        if df['classifier'][i]==1:
            fn+=1
        elif df['classifier'][i]==0 and df['classifier'][i-1]==1 and df['mcid'][i]==df['mcid'][i-1] and i>0:
            fn+=1
        elif df['classifier'][i]==0 and df['classifier'][i+1]==1 and df['mcid'][i]==df['mcid'][i+1] and i<len(df):
            fn+=1
    elif df['source'][i]==2:
        geo_tot+=1
        if df['classifier'][i]==1:
            geo+=1
        elif df['classifier'][i]==0 and df['classifier'][i-1]==1 and df['mcid'][i]==df['mcid'][i-1] and i>0:
            geo+=1
        elif df['classifier'][i]==0 and df['classifier'][i+1]==1 and df['mcid'][i]==df['mcid'][i+1] and i<len(df):
            geo+=1
    elif df['source'][i]==3:
        heysham_2_tot+=1
        if df['classifier'][i]==1:
            heysham_2+=1
        elif df['classifier'][i]==0 and df['classifier'][i-1]==1 and df['mcid'][i]==df['mcid'][i-1] and i>0:
            heysham_2+=1
        elif df['classifier'][i]==0 and df['classifier'][i+1]==1 and df['mcid'][i]==df['mcid'][i+1] and i<len(df):
            heysham_2+=1
    elif df['source'][i]==4:
        hinkley_c_tot+=1
        if df['classifier'][i]==1:
            hinkley_c+=1
        elif df['classifier'][i]==0 and df['classifier'][i-1]==1 and df['mcid'][i]==df['mcid'][i-1] and i>0:
            hinkley_c+=1
        elif df['classifier'][i]==0 and df['classifier'][i+1]==1 and df['mcid'][i]==df['mcid'][i+1] and i<len(df):
            hinkley_c+=1
    elif df['source'][i]==5:
        sizewell_b_tot+=1
        if df['classifier'][i]==1:
            sizewell_b+=1
        elif df['classifier'][i]==0 and df['classifier'][i-1]==1 and df['mcid'][i]==df['mcid'][i-1] and i>0:
            sizewell_b+=1
        elif df['classifier'][i]==0 and df['classifier'][i+1]==1 and df['mcid'][i]==df['mcid'][i+1] and i<len(df):
            sizewell_b+=1
    elif df['source'][i]==6:
        gravelines_tot+=1
        if df['classifier'][i]==1:
            gravelines+=1
        elif df['classifier'][i]==0 and df['classifier'][i-1]==1 and df['mcid'][i]==df['mcid'][i-1] and i>0:
            gravelines+=1
        elif df['classifier'][i]==0 and df['classifier'][i+1]==1 and df['mcid'][i]==df['mcid'][i+1] and i<len(df):
            gravelines+=1
    elif df['source'][i]==7:
        li9_tot+=1
        if df['classifier'][i]==1:
            li9+=1
        elif df['classifier'][i]==0 and df['classifier'][i-1]==1 and df['mcid'][i]==df['mcid'][i-1] and i>0:
            li9+=1
        elif df['classifier'][i]==0 and df['classifier'][i+1]==1 and df['mcid'][i]==df['mcid'][i+1] and i<len(df):
            li9+=1
    elif df['source'][i]==8:
        n17_tot+=1
        if df['classifier'][i]==1:
            n17+=1
        elif df['classifier'][i]==0 and df['classifier'][i-1]==1 and df['mcid'][i]==df['mcid'][i-1] and i>0:
            n17+=1
        elif df['classifier'][i]==0 and df['classifier'][i+1]==1 and df['mcid'][i]==df['mcid'][i+1] and i<len(df):
            n17+=1
    elif df['source'][i]==9:
        torness_tot+=1
        if df['classifier'][i]==1:
            torness+=1
        elif df['classifier'][i]==0 and df['classifier'][i-1]==1 and df['mcid'][i]==df['mcid'][i-1] and i>0:
            torness+=1
        elif df['classifier'][i]==0 and df['classifier'][i+1]==1 and df['mcid'][i]==df['mcid'][i+1] and i<len(df):
            torness+=1
    elif df['source'][i]==10:
        world_tot+=1
        if df['classifier'][i]==1:
            world+=1
        elif df['classifier'][i]==0 and df['classifier'][i-1]==1 and df['mcid'][i]==df['mcid'][i-1] and i>0:
            world+=1
        elif df['classifier'][i]==0 and df['classifier'][i+1]==1 and df['mcid'][i]==df['mcid'][i+1]:
            world+=1

print("Fn total:%i\nFn:%i"%(fn_tot,fn_tot-fn))
print("Heysham 2 total:%i\nHeysham 2:%i"%(heysham_2_tot,heysham_2_tot-heysham_2))
print("Torness total:%i\nTorness:%i"%(torness_tot,torness_tot-torness))
print("Sizewell B total:%i\nSizewell B:%i"%(sizewell_b_tot,sizewell_b_tot-fn))
print("Hinkley C total:%i\nHinkley C:%i"%(hinkley_c_tot,hinkley_c_tot-hinkley_c))
print("Gravelines total:%i\nGravelines:%i"%(gravelines_tot,gravelines_tot-gravelines))
print("World total:%i\nWorld:%i"%(world_tot,world_tot-world))
print("Geo total:%i\nGeo:%i"%(geo_tot,geo_tot-geo))
print("Li9 total:%i\nLi9:%i"%(li9_tot,li9_tot-li9))
print("N17 total:%i\nN17:%i"%(n17_tot,n17_tot-n17))