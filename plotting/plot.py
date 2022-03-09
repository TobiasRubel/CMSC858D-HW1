import pandas as pd
import matplotlib.pyplot as plt


def main():
    df = pd.read_csv("rank1.txt", sep = " ",names=['array','time'])
    print(df.to_latex(index=False))
    #df = df[df['array'].isin(["a1s3","a2s3","a3s3","a4s3"])]
    #df['time'].plot.scatter()
    #plt.show()
    #print(df)
    df = pd.read_csv("rs_overhead.txt",sep = " ", names = ['array','overhead'])
    #df = df[df['array'].isin(["a1s3","a2s3","a3s3","a4s3"])]
    #df['size'] = [1000,10000,100000,1000000]
    #df.plot.scatter(x='size',y='overhead')
    #plt.show()
    #print(df)
    df = pd.read_csv("ss_select1.txt",sep=" ",names=['array','time'])
    #df['size'] = [10000,100000,1000000]

    #df.plot.scatter(x='size',y='time')
    #plt.show()

    df = pd.read_csv("get_at_rank.txt", sep = " ",names=['array','time'])
    print(df.to_latex(index=False))

    df = pd.read_csv("get_at_index.txt", sep = " ",names=['array','time'])
    print(df.to_latex(index=False))

if __name__ == "__main__":
    main()
