import pandas as pd
import numpy as np
import sys
import ROOT
from array import array
from tqdm import tqdm
from sig_choice import sig_choice,sig_dict

file = sys.argv[1]

df = pd.read_csv(file)

ROOT.PyConfig.IgnoreCommandLineOptions = True
ROOT.gROOT.SetBatch(1)

f = ROOT.TFile("ML_classified.root", "RECREATE")
tree = ROOT.TTree("data", "ML Classified Data")
mc_energy = array('f', [0.])
subid = array('f', [0.])
n100 = array('f', [0.])
n100_prev = array('f', [0.])
mcid = array('f', [0.])
innerPE = array('f', [0.])
code = array('i', [0])
tree.Branch("mc_energy", mc_energy, 'mc_energy/F')
tree.Branch("subid", subid, 'subid/F')
tree.Branch("n100", n100, 'n100/F')
tree.Branch("n100_prev", n100_prev, 'n100_prev/F')
tree.Branch("mcid", mcid, 'mcid/F')
tree.Branch("innerPE", innerPE, 'innerPE/F')
tree.Branch("code", code, 'code/I')

fn = fn_tot = fn_keep = 0
heysham_2 = heysham_2_tot = heysham_2_keep = 0
torness = torness_tot = torness_keep = 0
sizewell_b = sizewell_b_tot = sizewell_b_keep = 0
hinkley_c = hinkley_c_tot = hinkley_c_keep = 0
gravelines = gravelines_tot = gravelines_keep = 0
world = world_tot = world_keep = 0
geo = geo_tot = geo_keep = 0
li9 = li9_tot = li9_keep = 0
n17 = n17_tot = n17_keep = 0
heysham_full = heysham_full_tot = heysham_full_keep = 0
hartlepool_1 = hartlepool_1_tot = hartlepool_1_keep = 0
hartlepool_2 = hartlepool_2_tot = hartlepool_2_keep = 0
energy = energy_tot = energy_keep = 0

df_fn = df_hey = df_tor = df_size = df_hink = df_grav = df_world = df_li9 = df_n17 = df_geo = pd.DataFrame()

for i in tqdm(range(len(df)-1)):
    if df['source'][i]==sig_dict['fn']:
        fn_tot+=1
        if df['classifier'][i]==1:
            fn+=1
        elif df['classifier'][i]==0 and df['classifier'][i-1]==1 and df['mcid'][i]==df['mcid'][i-1] and i>0:
            fn+=1
        elif df['classifier'][i]==0 and df['classifier'][i+1]==1 and df['mcid'][i]==df['mcid'][i+1] and i<len(df):
            fn+=1
        else:
            # df_fn = df_fn.append(df.loc[[i]])
            fn_keep+=1
            mc_energy[0] = df['mc_energy'][i]
            n100[0] = df['n100'][i]
            n100_prev[0] = df['n100_prev'][i]
            subid[0] = df['subid'][i]
            mcid[0] = df['mcid'][i]
            innerPE[0] = df['innerPE'][i]
            code[0] = df['source'][i]
            tree.Fill()
    elif df['source'][i]==sig_dict['geo']:
        geo_tot+=1
        if df['classifier'][i]==1:
            geo+=1
        elif df['classifier'][i]==0 and df['classifier'][i-1]==1 and df['mcid'][i]==df['mcid'][i-1] and i>0:
            geo+=1
        elif df['classifier'][i]==0 and df['classifier'][i+1]==1 and df['mcid'][i]==df['mcid'][i+1] and i<len(df):
            geo+=1
        else:
            geo_keep+=1
            # df_geo = df_geo.append(df.loc[[i]])
            mc_energy[0] = df['mc_energy'][i]
            n100[0] = df['n100'][i]
            n100_prev[0] = df['n100_prev'][i]
            subid[0] = df['subid'][i]
            mcid[0] = df['mcid'][i]
            innerPE[0] = df['innerPE'][i]
            code[0] = df['source'][i]
            tree.Fill()
    elif df['source'][i]==sig_dict['heysham_2']:
        heysham_2_tot+=1
        if df['classifier'][i]==1:
            heysham_2+=1
        elif df['classifier'][i]==0 and df['classifier'][i-1]==1 and df['mcid'][i]==df['mcid'][i-1] and i>0:
            heysham_2+=1
        elif df['classifier'][i]==0 and df['classifier'][i+1]==1 and df['mcid'][i]==df['mcid'][i+1] and i<len(df):
            heysham_2+=1
        else:
            heysham_2_keep+=1
            # df_hey = df_hey.append(df.loc[[i]])
            mc_energy[0] = df['mc_energy'][i]
            n100[0] = df['n100'][i]
            n100_prev[0] = df['n100_prev'][i]
            subid[0] = df['subid'][i]
            mcid[0] = df['mcid'][i]
            innerPE[0] = df['innerPE'][i]
            code[0] = df['source'][i]
            tree.Fill()
    elif df['source'][i]==sig_dict['hinkley_c']:
        hinkley_c_tot+=1
        if df['classifier'][i]==1:
            hinkley_c+=1
        elif df['classifier'][i]==0 and df['classifier'][i-1]==1 and df['mcid'][i]==df['mcid'][i-1] and i>0:
            hinkley_c+=1
        elif df['classifier'][i]==0 and df['classifier'][i+1]==1 and df['mcid'][i]==df['mcid'][i+1] and i<len(df):
            hinkley_c+=1
        else:
            hinkley_c_keep+=1
            # df_hink = df_hink.append(df.loc[[i]])
            mc_energy[0] = df['mc_energy'][i]
            n100[0] = df['n100'][i]
            subid[0] = df['subid'][i]
            mcid[0] = df['mcid'][i]
            innerPE[0] = df['innerPE'][i]
            code[0] = df['source'][i]
            tree.Fill()
    elif df['source'][i]==sig_dict['sizewell_b']:
        sizewell_b_tot+=1
        if df['classifier'][i]==1:
            sizewell_b+=1
        elif df['classifier'][i]==0 and df['classifier'][i-1]==1 and df['mcid'][i]==df['mcid'][i-1] and i>0:
            sizewell_b+=1
        elif df['classifier'][i]==0 and df['classifier'][i+1]==1 and df['mcid'][i]==df['mcid'][i+1] and i<len(df):
            sizewell_b+=1
        else:
            sizewell_b_keep+=1
            # df_size = df_size.append(df.loc[[i]])
            mc_energy[0] = df['mc_energy'][i]
            n100[0] = df['n100'][i]
            n100_prev[0] = df['n100_prev'][i]
            subid[0] = df['subid'][i]
            mcid[0] = df['mcid'][i]
            innerPE[0] = df['innerPE'][i]
            code[0] = df['source'][i]
            tree.Fill()
    elif df['source'][i]==sig_dict['gravelines']:
        gravelines_tot+=1
        if df['classifier'][i]==1:
            gravelines+=1
        elif df['classifier'][i]==0 and df['classifier'][i-1]==1 and df['mcid'][i]==df['mcid'][i-1] and i>0:
            gravelines+=1
        elif df['classifier'][i]==0 and df['classifier'][i+1]==1 and df['mcid'][i]==df['mcid'][i+1] and i<len(df):
            gravelines+=1
        else:
            gravelines_keep+=1
            # df_grav = df_grav.append(df.loc[[i]])
            mc_energy[0] = df['mc_energy'][i]
            n100[0] = df['n100'][i]
            n100_prev[0] = df['n100_prev'][i]
            subid[0] = df['subid'][i]
            mcid[0] = df['mcid'][i]
            innerPE[0] = df['innerPE'][i]
            code[0] = df['source'][i]
            tree.Fill()
    elif df['source'][i]==sig_dict['li9']:
        li9_tot+=1
        if df['classifier'][i]==1:
            li9+=1
        elif df['classifier'][i]==0 and df['classifier'][i-1]==1 and df['mcid'][i]==df['mcid'][i-1] and i>0:
            li9+=1
        elif df['classifier'][i]==0 and df['classifier'][i+1]==1 and df['mcid'][i]==df['mcid'][i+1] and i<len(df):
            li9+=1
        else:
            li9_keep+=1
            # df_li9 = df_li9.append(df.loc[[i]])
            mc_energy[0] = df['mc_energy'][i]
            n100[0] = df['n100'][i]
            n100_prev[0] = df['n100_prev'][i]
            subid[0] = df['subid'][i]
            mcid[0] = df['mcid'][i]
            innerPE[0] = df['innerPE'][i]
            code[0] = df['source'][i]
            tree.Fill()
    elif df['source'][i]==sig_dict['n17']:
        n17_tot+=1
        if df['classifier'][i]==1:
            n17+=1
        elif df['classifier'][i]==0 and df['classifier'][i-1]==1 and df['mcid'][i]==df['mcid'][i-1] and i>0:
            n17+=1
        elif df['classifier'][i]==0 and df['classifier'][i+1]==1 and df['mcid'][i]==df['mcid'][i+1] and i<len(df):
            n17+=1
        else:
            n17_keep+=1
            # df_n17 = df_n17.append(df.loc[[i]])
            mc_energy[0] = df['mc_energy'][i]
            n100[0] = df['n100'][i]
            n100_prev[0] = df['n100_prev'][i]
            subid[0] = df['subid'][i]
            mcid[0] = df['mcid'][i]
            innerPE[0] = df['innerPE'][i]
            code[0] = df['source'][i]
            tree.Fill()
    elif df['source'][i]==sig_dict['torness']:
        torness_tot+=1
        if df['classifier'][i]==1:
            torness+=1
        elif df['classifier'][i]==0 and df['classifier'][i-1]==1 and df['mcid'][i]==df['mcid'][i-1] and i>0:
            torness+=1
        elif df['classifier'][i]==0 and df['classifier'][i+1]==1 and df['mcid'][i]==df['mcid'][i+1] and i<len(df):
            torness+=1
        else:
            torness_keep+=1
            # df_tor = df_tor.append(df.loc[[i]])
            mc_energy[0] = df['mc_energy'][i]
            n100[0] = df['n100'][i]
            n100_prev[0] = df['n100_prev'][i]
            subid[0] = df['subid'][i]
            mcid[0] = df['mcid'][i]
            innerPE[0] = df['innerPE'][i]
            code[0] = df['source'][i]
            tree.Fill()
    elif df['source'][i]==sig_dict['world']:
        world_tot+=1
        if df['classifier'][i]==1:
            world+=1
        elif df['classifier'][i]==0 and df['classifier'][i-1]==1 and df['mcid'][i]==df['mcid'][i-1] and i>0:
            world+=1
        elif df['classifier'][i]==0 and df['classifier'][i+1]==1 and df['mcid'][i]==df['mcid'][i+1]:
            world+=1
        else:
            world_keep+=1
            # df_world = df_world.append(df.loc[[i]])
            mc_energy[0] = df['mc_energy'][i]
            n100[0] = df['n100'][i]
            n100_prev[0] = df['n100_prev'][i]
            subid[0] = df['subid'][i]
            mcid[0] = df['mcid'][i]
            innerPE[0] = df['innerPE'][i]
            code[0] = df['source'][i]
            tree.Fill()
    elif df['source'][i]==sig_dict['hartlepool_1']:
        hartlepool_1_tot+=1
        if df['classifier'][i]==1:
            hartlepool_1+=1
        elif df['classifier'][i]==0 and df['classifier'][i-1]==1 and df['mcid'][i]==df['mcid'][i-1] and i>0:
            hartlepool_1+=1
        elif df['classifier'][i]==0 and df['classifier'][i+1]==1 and df['mcid'][i]==df['mcid'][i+1]:
            hartlepool_1+=1
        else:
            hartlepool_1_keep+=1
            # df_hartlepool_1 = df_hartlepool_1.append(df.loc[[i]])
            mc_energy[0] = df['mc_energy'][i]
            n100[0] = df['n100'][i]
            n100_prev[0] = df['n100_prev'][i]
            subid[0] = df['subid'][i]
            mcid[0] = df['mcid'][i]
            innerPE[0] = df['innerPE'][i]
            code[0] = df['source'][i]
            tree.Fill()
    elif df['source'][i]==sig_dict['hartlepool_2']:
        hartlepool_2_tot+=1
        if df['classifier'][i]==1:
            hartlepool_2+=1
        elif df['classifier'][i]==0 and df['classifier'][i-1]==1 and df['mcid'][i]==df['mcid'][i-1] and i>0:
            hartlepool_2+=1
        elif df['classifier'][i]==0 and df['classifier'][i+1]==1 and df['mcid'][i]==df['mcid'][i+1]:
            hartlepool_2+=1
        else:
            hartlepool_2_keep+=1
            # df_hartlepool_2 = df_hartlepool_2.append(df.loc[[i]])
            mc_energy[0] = df['mc_energy'][i]
            n100[0] = df['n100'][i]
            n100_prev[0] = df['n100_prev'][i]
            subid[0] = df['subid'][i]
            mcid[0] = df['mcid'][i]
            innerPE[0] = df['innerPE'][i]
            code[0] = df['source'][i]
            tree.Fill()
    elif df['source'][i]==sig_dict['heysham_full']:
        heysham_full_tot+=1
        if df['classifier'][i]==1:
            heysham_full+=1
        elif df['classifier'][i]==0 and df['classifier'][i-1]==1 and df['mcid'][i]==df['mcid'][i-1] and i>0:
            heysham_full+=1
        elif df['classifier'][i]==0 and df['classifier'][i+1]==1 and df['mcid'][i]==df['mcid'][i+1]:
            heysham_full+=1
        else:
            heysham_full_keep+=1
            # df_heysham_full = df_heysham_full.append(df.loc[[i]])
            mc_energy[0] = df['mc_energy'][i]
            n100[0] = df['n100'][i]
            n100_prev[0] = df['n100_prev'][i]
            subid[0] = df['subid'][i]
            mcid[0] = df['mcid'][i]
            innerPE[0] = df['innerPE'][i]
            code[0] = df['source'][i]
            tree.Fill()
    elif df['source'][i]==sig_dict['energy']:
        energy_tot+=1
        if df['classifier'][i]==1:
            energy+=1
        elif i>0 and df['classifier'][i]==0 and df['classifier'][i-1]==1 and df['mcid'][i]==df['mcid'][i-1]:
            energy+=1
        elif df['classifier'][i]==0 and df['classifier'][i+1]==1 and df['mcid'][i]==df['mcid'][i+1]:
            energy+=1
        else:
            energy_keep+=1
            mc_energy[0] = df['mc_energy'][i]
            n100[0] = df['n100'][i]
            n100_prev[0] = df['n100_prev'][i]
            subid[0] = df['subid'][i]
            mcid[0] = df['mcid'][i]
            innerPE[0] = df['innerPE'][i]
            code[0] = df['source'][i]
            tree.Fill()
tree.Write("data", ROOT.TObject.kOverwrite)
f.Close()

# print("\nPost-ML:\n\n")
# print("Fn total:%i\nFn:%i"%(fn_tot,fn_keep))
# print("Heysham 2 total:%i\nHeysham 2:%i"%(heysham_2_tot,heysham_2_keep))
# print("Torness total:%i\nTorness:%i"%(torness_tot,torness_keep))
# print("Sizewell B total:%i\nSizewell B:%i"%(sizewell_b_tot,sizewell_b_keep))
# print("Hinkley C total:%i\nHinkley C:%i"%(hinkley_c_tot,hinkley_c_keep))
# print("Gravelines total:%i\nGravelines:%i"%(gravelines_tot,gravelines_keep))
# print("World total:%i\nWorld:%i"%(world_tot,world_keep))
# print("Geo total:%i\nGeo:%i"%(geo_tot,geo_keep))
# print("Li9 total:%i\nLi9:%i"%(li9_tot,li9_keep))
# print("N17 total:%i\nN17:%i"%(n17_tot,n17_keep))

sig='heysham_2'
signal_components,background_components = sig_choice(sig)
components = signal_components+background_components

tank = 22
file = 'results_learn.csv'
df = pd.read_csv(file)
df = df.set_index('Component')

keep_dict = {"fn":fn_keep,\
            "geo":geo_keep,\
            "heysham_2":heysham_2_keep,\
            "torness":torness_keep,\
            "sizewell_b":sizewell_b_keep,\
            "hinkley_c":hinkley_c_keep,\
            "gravelines":gravelines_keep,\
            "world":world_keep,\
            "li9":li9_keep,\
            "n17":n17_keep,\
            "energy":energy_keep,\
			"hartlepool_1":hartlepool_1_keep,\
			"hartlepool_2":hartlepool_2_keep,\
			"heysham_full":heysham_full_keep}
for i in components:
    keep = keep_dict[i]
    df.loc[i,"%i kept"%tank] = keep
print(df)
df.to_csv("results_ML.csv",sep=',',float_format='%.9e')