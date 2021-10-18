import numpy as np
import pandas as pd
import os

file = "heysham2_rates.csv"
component = "Heysham 2"
tank = "22"
kept = 244252
MC = 1055000
rate = 0.000006894

def results_csv(file, component,tank,kept,MC,rate):

    path = os.getcwd() + "/" + file

    key_2_MC = tank + " MC"
    key_2_kept = tank + " kept"
    key_2_rate = tank + " rate"

    if os.path.isfile(path):
        print("%s found"%path)
        df = pd.read_csv(file)
        if key_2_MC in df.keys() and key_2_kept in df.keys() and key_2_rate in df.keys():
            print("%s m keys exists"%tank)
        else:
            print("%s m keys not found\nAdding new keys"%tank)
            df[key_2_MC] = ""
            df[key_2_kept] = ""
            df[key_2_rate] = ""

        if df['Component'].str.contains(component).any():
            print("%s found"%component)
        else:
            print("%s not found"%component)
            new_component = [component]
            for i in range(len(df.keys())-1):
                new_component.append("")
            df.loc[df.index.max() + 1, :] = new_component
        index = df.index
        condition = df["Component"] == component
        component_indices = index[condition]
        component_indices_list = component_indices.tolist()
        print(component_indices_list[0])
        df.at[component_indices_list[0],"%s MC"%tank] = MC
        df.at[component_indices_list[0],"%s kept"%tank] = kept
        df.at[component_indices_list[0],"%s rate"%tank] = rate
        print(df)
    else:
        print("%s not found"%path)

    return

results_csv(file,component,tank,kept,MC,rate)