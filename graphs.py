import pandas as pd
import numpy as np
from icecream import ic
import matplotlib.pyplot as plt

df_build = pd.read_csv("build_times.csv")
df_build.loc[df_build['k'] == -1, 'k'] = 0
fig, ax = plt.subplots()

for key, grp in df_build.groupby(['ref_percent']):
    ax = grp.plot(ax=ax, kind='line', x='k', y='time', label=key, title="Build Time (ms) by % of Reference Data Used", marker='o', ylabel="Time (ms)", xlabel="k")

plt.legend(loc='best')
plt.show()

df_build['filesize'] = df_build['filesize'].div(1000000)
fig, ax = plt.subplots()
for key, grp in df_build.groupby(['ref_percent']):
    ax = grp.plot(ax=ax, kind='line', x='k', y='filesize', label=key, title="File Size (MB) by % of Reference Data Used", marker='o', ylabel="MB", xlabel="k")

plt.legend(loc='best')
plt.show()
df_query = pd.read_csv('query_times.csv')
df_naive = df_query[df_query.search_type != "simpaccel"]
df_simpaccel = df_query[df_query.search_type != "naive"]

fig, ax = plt.subplots()

for key, grp in df_naive.groupby(['ref_percent']):
    ax = grp.plot(ax=ax, kind='line', x='k', y='time', label=key, title="Total Query Time (ms) by % of Reference Data Used, All Queries, Naive", marker='o', ylabel="Time (ms)", xlabel="k")

plt.legend(loc='best')
plt.show()

fig, ax = plt.subplots()

for key, grp in df_simpaccel.groupby(['ref_percent']):
    ax = grp.plot(ax=ax, kind='line', x='k', y='time', label=key, title="Total Query Time (ms) by % of Reference Data Used, All Queries, Simpaccel", marker='o', ylabel="Time (ms)", xlabel="k")

plt.legend(loc='best')
plt.show()

df_custom_query = pd.read_csv('custom_query_times.csv')
fig, ax = plt.subplots()

for key, grp in df_custom_query.groupby(['search_type']):
    ax = grp.plot(ax=ax, kind='line', x='query_len', y='time', label=key, title="Total Query Time (ms) by Query Length, 1000 Random Queries Each", marker='o', ylabel="Time (ms)", xlabel="Query Length")

plt.legend(loc='best')
plt.show()



#df_custom_query = pd.read_csv('custom_query_times.csv')
#df_custom_naive = df_custom_query[df_custom_query.search_type != "simpaccel"]
#df_custom_simpaccel = df_custom_query[df_custom_query.search_type != "naive"]
#
#fig, ax = plt.subplots()
#
#for key, grp in df_custom_naive.groupby(['query_len']):
#    ax = grp.plot(ax=ax, kind='line', x='query_len', y='time', label=key, title="Total Query Time (ms) by % of Reference Data Used, All Queries, Naive", marker='o', ylabel="Time (ms)", xlabel="k")
#
#plt.legend(loc='best')
#plt.show()
#
#fig, ax = plt.subplots()
#
#for key, grp in df_custom_simpaccel.groupby(['query_len']):
#    ax = grp.plot(ax=ax, kind='line', x='query_len', y='time', label=key, title="Total Query Time (ms) by % of Reference Data Used, All Queries, Simpaccel", marker='o', ylabel="Time (ms)", xlabel="k")
#
#plt.legend(loc='best')
#plt.show()

ic(df_naive)

#p1_crea
#p1_create_pd = pd.read_csv("p1_create.csv")
#p1_query_pd = pd.read_csv("p1_query.csv")
#p1_overhead_pd = pd.read_csv("p1_overhead.csv")
#p1_plots = [p1_create_pd, p1_query_pd, p1_overhead_pd]
#
#p1_create_final_pd = pd.DataFrame(columns=['Size', 'Time'])
#p1_query_final_pd = pd.DataFrame(columns=['Size', 'Time'])
#p1_overhead_final_pd = pd.DataFrame(columns=['Size', 'Overhead'])
#p1_final_plots = [p1_create_final_pd, p1_query_final_pd, p1_overhead_final_pd]
#
#sizes = [1000, 10000, 100000, 1000000]
#
#
#for size in sizes:
#    time_avg = p1_create_pd.loc[p1_create_pd['Size'] == size]["Time"].mean()
#    p1_create_final_pd.loc[len(p1_create_final_pd.index)] = [size, time_avg]
#ic(p1_create_final_pd)
#p1_create_final_pd.plot(x='Size', y='Time', kind = 'line', marker='o', ylabel = 'Time (milliseconds)', title="Creation of Rank Support (Time x Size)", logx=True)
#plt.show()
